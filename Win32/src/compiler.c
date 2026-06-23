/* Compiler configuration and linking module for Orca */

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Compiler path settings */
static char g_compilerPathC[MAX_PATH] = "";

/* Forward declaration - from main.c */
extern char g_configPath[MAX_PATH];
extern void DebugLog(const char* fmt, ...);

/* Function prototypes for this module */
void LoadCompilerPathC(void);
void SaveCompilerPathC(void);
BOOL ValidateCompilerPath(const char* compilerPath);
const char* GetCompilerPathC(void);
void SetCompilerPathC(const char* path);
BOOL CompileProjectSources(HWND hwndParent, char sourceFiles[][MAX_PATH], int fileCount, const char* outputPath);
BOOL CompileSelectionFromStdin(HWND hwndParent, const char* sourceCode);

/* Load compiler C path from config */
void LoadCompilerPathC(void) {
    if (g_configPath[0] == '\0') {
        DebugLog("[COMPILER] Config path not set, skipping compiler path load\n");
        return;
    }

    GetPrivateProfileStringA("Compiler", "CompilerPathC", "", g_compilerPathC, sizeof(g_compilerPathC), g_configPath);
    DebugLog("[COMPILER] Loaded CompilerPathC: %s\n", g_compilerPathC[0] ? g_compilerPathC : "(empty)");
}

/* Save compiler C path to config */
void SaveCompilerPathC(void) {
    if (g_configPath[0] == '\0') {
        DebugLog("[COMPILER] Config path not set, skipping compiler path save\n");
        return;
    }

    WritePrivateProfileStringA("Compiler", "CompilerPathC", g_compilerPathC, g_configPath);
    DebugLog("[COMPILER] Saved CompilerPathC: %s\n", g_compilerPathC[0] ? g_compilerPathC : "(empty)");
}

/* Validate compiler path - check if the file exists */
BOOL ValidateCompilerPath(const char* compilerPath) {
    if (!compilerPath || compilerPath[0] == '\0') {
        DebugLog("[COMPILER] Compiler path is empty\n");
        return FALSE;
    }

    DWORD attribs = GetFileAttributesA(compilerPath);
    if (attribs == INVALID_FILE_ATTRIBUTES) {
        DebugLog("[COMPILER] Compiler path not found: %s\n", compilerPath);
        return FALSE;
    }

    if (attribs & FILE_ATTRIBUTE_DIRECTORY) {
        DebugLog("[COMPILER] Compiler path is a directory, not a file: %s\n", compilerPath);
        return FALSE;
    }

    DebugLog("[COMPILER] Compiler path validated: %s\n", compilerPath);
    return TRUE;
}

/* Get the current compiler C path */
const char* GetCompilerPathC(void) {
    return g_compilerPathC;
}

/* Set the compiler C path */
void SetCompilerPathC(const char* path) {
    if (!path) {
        g_compilerPathC[0] = '\0';
        DebugLog("[COMPILER] Cleared CompilerPathC\n");
        return;
    }

    strncpy(g_compilerPathC, path, sizeof(g_compilerPathC) - 1);
    g_compilerPathC[sizeof(g_compilerPathC) - 1] = '\0';
    DebugLog("[COMPILER] Set CompilerPathC: %s\n", g_compilerPathC);
    SaveCompilerPathC();
}

static BOOL CompilerIsCSourceFile(const char* filePath) {
    if (!filePath) return FALSE;
    const char* ext = strrchr(filePath, '.');
    if (!ext) return FALSE;
    const char* candidate = ext + 1;
    return (candidate[0] == 'c' || candidate[0] == 'C') && candidate[1] == '\0';
}

static BOOL BuildCommandLine(char* commandLine, int maxLen, char sourceFiles[][MAX_PATH], int fileCount, const char* outputPath) {
    if (!commandLine || !sourceFiles || fileCount <= 0 || !outputPath) return FALSE;

    int written = snprintf(commandLine, maxLen, "\"%s\"", g_compilerPathC);
    if (written < 0 || written >= maxLen) return FALSE;

    for (int i = 0; i < fileCount; i++) {
        if (CompilerIsCSourceFile(sourceFiles[i])) {
            written += snprintf(commandLine + written, maxLen - written, " \"%s\"", sourceFiles[i]);
            if (written < 0 || written >= maxLen) return FALSE;
        }
    }

    written += snprintf(commandLine + written, maxLen - written, " -o \"%s\"", outputPath);
    return written >= 0 && written < maxLen;
}

static int ReadPipeToString(HANDLE hPipe, char** outBuffer) {
    if (!hPipe || !outBuffer) return -1;

    size_t capacity = 8192;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    if (!buffer) return -1;

    for (;;) {
        DWORD bytesRead = 0;
        BOOL result = ReadFile(hPipe, buffer + length, (DWORD)(capacity - length), &bytesRead, NULL);
        if (!result || bytesRead == 0) break;

        length += bytesRead;
        if (capacity - length < 4096) {
            size_t newCapacity = capacity + 8192;
            char* temp = (char*)realloc(buffer, newCapacity);
            if (!temp) break;
            buffer = temp;
            capacity = newCapacity;
        }
    }

    if (length == 0) {
        free(buffer);
        *outBuffer = NULL;
        return 0;
    }

    buffer[length] = '\0';
    *outBuffer = buffer;
    return (int)length;
}

#define COMPILER_ERROR_EDIT_ID 1001
#define COMPILER_ERROR_OK_ID   1002

typedef struct {
    char* message;
    BOOL* running;
} CompilerErrorDialogParams;

static LRESULT CALLBACK CompilerErrorDialogWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    CompilerErrorDialogParams* params = (CompilerErrorDialogParams*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);

    switch (msg) {
        case WM_CREATE: {
            CREATESTRUCTA* cs = (CREATESTRUCTA*)lParam;
            params = (CompilerErrorDialogParams*)cs->lpCreateParams;
            SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)params);

            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;

            HWND hwndEdit = CreateWindowExA(
                WS_EX_CLIENTEDGE,
                "EDIT",
                NULL,
                WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                10,
                10,
                width - 20,
                height - 55,
                hwnd,
                (HMENU)COMPILER_ERROR_EDIT_ID,
                GetModuleHandle(NULL),
                NULL
            );

            CreateWindowA(
                "BUTTON",
                "OK",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                (width - 80) / 2,
                height - 35,
                80,
                24,
                hwnd,
                (HMENU)COMPILER_ERROR_OK_ID,
                GetModuleHandle(NULL),
                NULL
            );

            if (hwndEdit && params && params->message) {
                SetWindowTextA(hwndEdit, params->message);
                SendMessageA(hwndEdit, EM_SETSEL, 0, 0);
                SendMessageA(hwndEdit, EM_SCROLLCARET, 0, 0);
            }
        }
        return 0;

        case WM_COMMAND:
            if (LOWORD(wParam) == COMPILER_ERROR_OK_ID) {
                if (params && params->running) {
                    *params->running = FALSE;
                }
                DestroyWindow(hwnd);
            }
            return 0;

        case WM_SIZE: {
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            HWND hwndEdit = GetDlgItem(hwnd, COMPILER_ERROR_EDIT_ID);
            HWND hwndButton = GetDlgItem(hwnd, COMPILER_ERROR_OK_ID);
            if (hwndEdit) MoveWindow(hwndEdit, 10, 10, width - 20, height - 55, TRUE);
            if (hwndButton) MoveWindow(hwndButton, (width - 80) / 2, height - 35, 80, 24, TRUE);
        }
        return 0;

        case WM_CLOSE:
            if (params && params->running) {
                *params->running = FALSE;
            }
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            if (params) {
                if (params->message) free(params->message);
                free(params);
            }
            return 0;
    }

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

static BOOL RegisterCompilerErrorDialogClass(HINSTANCE hInstance) {
    static BOOL registered = FALSE;
    if (registered) return TRUE;

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = CompilerErrorDialogWndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "OrcaCompilerErrorDialog";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassA(&wc)) {
        return FALSE;
    }

    registered = TRUE;
    return TRUE;
}

static BOOL ShowCompilerErrorDialog(HWND hwndParent, const char* title, const char* message) {
    if (!message) return FALSE;

    HINSTANCE hInstance = GetModuleHandle(NULL);
    if (!RegisterCompilerErrorDialogClass(hInstance)) return FALSE;

    int dialogWidth = 700;
    int dialogHeight = 420;
    RECT parentRect = {0};
    if (hwndParent) {
        GetWindowRect(hwndParent, &parentRect);
    } else {
        GetWindowRect(GetDesktopWindow(), &parentRect);
    }

    int x = parentRect.left + ((parentRect.right - parentRect.left) - dialogWidth) / 2;
    int y = parentRect.top + ((parentRect.bottom - parentRect.top) - dialogHeight) / 2;
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    BOOL keepRunning = TRUE;
    CompilerErrorDialogParams* params = (CompilerErrorDialogParams*)malloc(sizeof(CompilerErrorDialogParams));
    if (!params) return FALSE;
    size_t messageLen = strlen(message) + 1;
    params->message = (char*)malloc(messageLen);
    if (!params->message) {
        free(params);
        return FALSE;
    }
    memcpy(params->message, message, messageLen);
    params->running = &keepRunning;

    HWND hwndDlg = CreateWindowExA(
        WS_EX_DLGMODALFRAME,
        "OrcaCompilerErrorDialog",
        title,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
        x,
        y,
        dialogWidth,
        dialogHeight,
        hwndParent,
        NULL,
        hInstance,
        params
    );

    if (!hwndDlg) {
        free(params->message);
        free(params);
        return FALSE;
    }

    if (hwndParent) {
        EnableWindow(hwndParent, FALSE);
    }

    ShowWindow(hwndDlg, SW_SHOW);
    UpdateWindow(hwndDlg);

    MSG msg;
    while (keepRunning && GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    if (hwndParent) {
        EnableWindow(hwndParent, TRUE);
        SetActiveWindow(hwndParent);
    }

    return TRUE;
}

static void ExtractCompilerErrorSummary(const char* compilerOutput, char* outSummary, size_t maxSummary) {
    if (!compilerOutput || !outSummary || maxSummary == 0) {
        return;
    }

    const char* lineStart = compilerOutput;
    const char* bestLine = NULL;
    const char* fallbackLine = NULL;

    while (*lineStart) {
        const char* lineEnd = strchr(lineStart, '\n');
        size_t len = lineEnd ? (size_t)(lineEnd - lineStart) : strlen(lineStart);

        if (len > 0) {
            if (!fallbackLine && strncmp(lineStart, "In function", 11) != 0) {
                fallbackLine = lineStart;
            }
            if (strstr(lineStart, "error:") || strstr(lineStart, ": error:") || strstr(lineStart, "fatal error") || strstr(lineStart, "undefined reference") || strstr(lineStart, "undefined symbol")) {
                bestLine = lineStart;
                break;
            }
        }

        if (!lineEnd) break;
        lineStart = lineEnd + 1;
    }

    const char* selectedLine = bestLine ? bestLine : fallbackLine;
    if (!selectedLine) {
        outSummary[0] = '\0';
        return;
    }

    const char* selectedEnd = strchr(selectedLine, '\n');
    size_t selectedLen = selectedEnd ? (size_t)(selectedEnd - selectedLine) : strlen(selectedLine);
    if (selectedLen >= maxSummary) selectedLen = maxSummary - 1;
    memcpy(outSummary, selectedLine, selectedLen);
    outSummary[selectedLen] = '\0';
}

BOOL CompileProjectSources(HWND hwndParent, char sourceFiles[][MAX_PATH], int fileCount, const char* outputPath) {
    if (!ValidateCompilerPath(g_compilerPathC)) {
        MessageBoxA(hwndParent, "The configured C compiler path is invalid. Please set a valid compiler path.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    if (!sourceFiles || fileCount <= 0 || !outputPath) {
        DebugLog("[COMPILER] Invalid compile parameters\n");
        return FALSE;
    }

    char commandLine[16384];
    if (!BuildCommandLine(commandLine, sizeof(commandLine), sourceFiles, fileCount, outputPath)) {
        DebugLog("[COMPILER] Failed to build compiler command line\n");
        MessageBoxA(hwndParent, "Failed to build the compiler command line.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    DebugLog("[COMPILER] Running: %s\n", commandLine);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    HANDLE hStdOutRead = NULL;
    HANDLE hStdOutWrite = NULL;
    char* compilerOutput = NULL;

    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &saAttr, 0)) {
        DebugLog("[COMPILER] Failed to create pipe for compiler output\n");
        MessageBoxA(hwndParent, "Failed to capture compiler output.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    if (!SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0)) {
        DebugLog("[COMPILER] Failed to set pipe handle information\n");
        CloseHandle(hStdOutRead);
        CloseHandle(hStdOutWrite);
        MessageBoxA(hwndParent, "Failed to capture compiler output.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = hStdOutWrite;
    si.hStdError = hStdOutWrite;

    BOOL created = CreateProcessA(
        NULL,
        commandLine,
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!created) {
        DWORD error = GetLastError();
        DebugLog("[COMPILER] CreateProcess failed: %lu\n", error);
        char msg[256];
        sprintf(msg, "Failed to launch compiler. Error code %lu.", error);
        MessageBoxA(hwndParent, msg, "Compiler Error", MB_ICONERROR);
        CloseHandle(hStdOutRead);
        CloseHandle(hStdOutWrite);
        return FALSE;
    }

    CloseHandle(hStdOutWrite);

    WaitForSingleObject(pi.hProcess, INFINITE);
    ReadPipeToString(hStdOutRead, &compilerOutput);
    CloseHandle(hStdOutRead);

    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        DebugLog("[COMPILER] Failed to get exit code\n");
        exitCode = (DWORD)-1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0) {
        char errorSummary[1024] = "";
        ExtractCompilerErrorSummary(compilerOutput, errorSummary, sizeof(errorSummary));

        char debugLine[512];
        if (errorSummary[0]) {
            snprintf(debugLine, sizeof(debugLine), "[COMPILER] Compilation failed: %s", errorSummary);
        } else if (compilerOutput && compilerOutput[0]) {
            char* newline = strchr(compilerOutput, '\n');
            if (newline) *newline = '\0';
            snprintf(debugLine, sizeof(debugLine), "[COMPILER] Compilation failed: %s", compilerOutput);
        } else {
            snprintf(debugLine, sizeof(debugLine), "[COMPILER] Compilation failed with code %lu", exitCode);
        }
        DebugLog("%s\n", debugLine);
        DebugLog("[COMPILER] Exit code: %lu\n", exitCode);

        char msg[65536];
        if (compilerOutput && compilerOutput[0]) {
            snprintf(msg, sizeof(msg),
                "Compiler returned exit code %lu.\n\n"
                "Error summary:\n%s\n\n"
                "Full compiler output:\n%s",
                exitCode,
                errorSummary[0] ? errorSummary : compilerOutput,
                compilerOutput);
            ShowCompilerErrorDialog(hwndParent, "Compile Failed", msg);
        } else {
            snprintf(msg, sizeof(msg), "Compiler returned exit code %lu.\n\nNo compiler output was captured.", exitCode);
            MessageBoxA(hwndParent, msg, "Compile Failed", MB_ICONERROR);
        }
        free(compilerOutput);
        return FALSE;
    }

    DebugLog("[COMPILER] Compilation succeeded, output: %s\n", outputPath);
    free(compilerOutput);
    return TRUE;
}

BOOL CompileSelectionFromStdin(HWND hwndParent, const char* sourceCode) {
    if (!ValidateCompilerPath(g_compilerPathC)) {
        MessageBoxA(hwndParent, "The configured C compiler path is invalid. Please set a valid compiler path.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    if (!sourceCode || sourceCode[0] == '\0') {
        DebugLog("[COMPILER] No source code provided for stdin compile\n");
        MessageBoxA(hwndParent, "No code is selected for quick compile.", "Quick Compile", MB_ICONWARNING);
        return FALSE;
    }

    char modulePath[MAX_PATH];
    char rootPath[MAX_PATH] = {0};
    if (GetModuleFileNameA(NULL, modulePath, MAX_PATH)) {
        char* p = strrchr(modulePath, '\\');
        if (p) *p = '\0';
        p = strrchr(modulePath, '\\');
        if (p) *p = '\0';
        p = strrchr(modulePath, '\\');
        if (p) *p = '\0';
        strncpy(rootPath, modulePath, MAX_PATH - 1);
        rootPath[MAX_PATH - 1] = '\0';
    }

    if (rootPath[0] == '\0') {
        if (!GetCurrentDirectoryA(MAX_PATH, rootPath) || rootPath[0] == '\0') {
            MessageBoxA(hwndParent, "Failed to determine output path.", "Compiler Error", MB_ICONERROR);
            return FALSE;
        }
    }

    char sourceFilePath[MAX_PATH];
    char outputExePath[MAX_PATH];
    unsigned long pid = GetCurrentProcessId();
    unsigned long tick = GetTickCount();
    snprintf(sourceFilePath, sizeof(sourceFilePath), "%s\\orca_quick_compile_%lu_%lu.c", rootPath, pid, tick);
    snprintf(outputExePath, sizeof(outputExePath), "%s\\orca_quick_compile_%lu_%lu.exe", rootPath, pid, tick);

    FILE* srcFile = fopen(sourceFilePath, "wb");
    if (!srcFile) {
        DebugLog("[COMPILER] Failed to open temp source file: %s\n", sourceFilePath);
        MessageBoxA(hwndParent, "Failed to create temporary source file for quick compile.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    size_t sourceLength = strlen(sourceCode);
    size_t writtenBytes = fwrite(sourceCode, 1, sourceLength, srcFile);
    fclose(srcFile);
    if (writtenBytes != sourceLength) {
        DebugLog("[COMPILER] Failed to write source file: %s\n", sourceFilePath);
        MessageBoxA(hwndParent, "Failed to write temporary source file for quick compile.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    char commandLine[16384];
    int written = snprintf(
        commandLine,
        sizeof(commandLine),
        "cmd.exe /K \"\"%s\" -fno-lto -fno-use-linker-plugin -x c \"%s\" -o \"%s\" && \"%s\"\"",
        g_compilerPathC,
        sourceFilePath,
        outputExePath,
        outputExePath
    );
    if (written < 0 || written >= (int)sizeof(commandLine)) {
        DebugLog("[COMPILER] Failed to build compiler command line for stdin compile\n");
        MessageBoxA(hwndParent, "Failed to build the compiler command line.", "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    DebugLog("[COMPILER] Running: %s\n", commandLine);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    BOOL created = CreateProcessA(
        NULL,
        commandLine,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!created) {
        DWORD error = GetLastError();
        DebugLog("[COMPILER] CreateProcess failed: %lu\n", error);
        char msg[256];
        sprintf(msg, "Failed to launch compiler. Error code %lu.", error);
        MessageBoxA(hwndParent, msg, "Compiler Error", MB_ICONERROR);
        return FALSE;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    DebugLog("[COMPILER] Quick compile launched in new console: %s\n", outputExePath);
    return TRUE;
}
