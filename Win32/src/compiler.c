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
    SECURITY_ATTRIBUTES saProcess = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    SECURITY_ATTRIBUTES saThread = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    BOOL created = CreateProcessA(
        NULL,
        commandLine,
        &saProcess,
        &saThread,
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
        return FALSE;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        DebugLog("[COMPILER] Failed to get exit code\n");
        exitCode = (DWORD)-1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode != 0) {
        DebugLog("[COMPILER] Compiler exited with code %lu\n", exitCode);
        char msg[256];
        sprintf(msg, "Compiler returned exit code %lu.", exitCode);
        MessageBoxA(hwndParent, msg, "Compile Failed", MB_ICONERROR);
        return FALSE;
    }

    DebugLog("[COMPILER] Compilation succeeded, output: %s\n", outputPath);
    return TRUE;
}
