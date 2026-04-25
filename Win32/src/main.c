
#define _WIN32_WINNT 0x0501
#define _WIN32_IE 0x0501
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>

/* Control IDs */
#define IDC_CODE_INPUT     1001
#define IDC_CODE_OUTPUT    1002
#define IDC_TOOLBAR_MAIN   1003
#define IDC_TOOLBAR_CODE   1004
#define IDC_STATUSBAR      1005
#define IDC_PROJECT_TREE   1006
#define IDC_PROPERTIES     1007

/* Menu IDs */
#define IDM_FILE_NEW       1101
#define IDM_FILE_OPEN      1102
#define IDM_FILE_SAVE      1103
#define IDM_FILE_SAVEAS    1104
#define IDM_FILE_SAVEALL   1105
#define IDM_FILE_EXIT      1106
#define IDM_EDIT_UNDO      1201
#define IDM_EDIT_REDO      1202
#define IDM_EDIT_CUT       1203
#define IDM_EDIT_COPY      1204
#define IDM_EDIT_PASTE     1205
#define IDM_EDIT_SELECTALL 1206
#define IDM_PROJECT_NEW    1301
#define IDM_PROJECT_SETTINGS 1302
#define IDM_BUILD_COMPILE  1401
#define IDM_BUILD_RUN      1402

/* Toolbar button IDs */
#define IDT_INSERT_FUNC    2001
#define IDT_INSERT_IF      2002
#define IDT_INSERT_FOR     2003
#define IDT_INSERT_WHILE   2004
#define IDT_INSERT_SWITCH  2005
#define IDT_INSERT_STRUCT  2006
#define IDT_INSERT_UNION   2007
#define IDT_INSERT_ENUM    2008
#define IDT_INSERT_TYPEDEF 2009
#define IDT_INSERT_INCLUDE 2010
#define IDT_INSERT_DEFINE  2011

/* Manipulation toolbar button IDs */
#define IDM_WRAP_IF        3001
#define IDM_WRAP_WHILE     3002
#define IDM_WRAP_FOR       3003
#define IDM_CONVERT_FUNC   3004
#define IDM_EXTRACT_FUNC   3005
#define IDM_ADD_COMMENT   3006
#define IDM_REMOVE_COMMENT 3007
#define IDM_FORMAT_CODE   3008
#define IDM_CONVERT_TO_MACRO 3009
#define IDM_EXTRACT_MACRO 3010

/* Global state */
static HWND hwndMain;
static HWND hwndInput, hwndOutput;
static HWND hwndToolbarMain, hwndToolbarCode;
static HWND hwndStatusBar;
static HWND hwndProjectTree;
static HWND hwndProperties;

/* Project settings */
static char g_platform[64] = "Windows";
static char g_compiler[64] = "GCC";
static char g_architecture[64] = "x86";

/* File tracking */
#define MAX_OPENED_FILES 256
static char g_openedFiles[MAX_OPENED_FILES][MAX_PATH];
static int g_openedFileCount = 0;
static BOOL g_isFolderBased = FALSE;
static BOOL g_projectOpened = FALSE;

/* Enable/disable save menu items */
void UpdateSaveMenuState(BOOL enable) {
    HMENU hMenu = GetMenu(hwndMain);
    HMENU hFileMenu = GetSubMenu(hMenu, 0);
    UINT flags = enable ? MF_ENABLED : MF_GRAYED;
    EnableMenuItem(hFileMenu, IDM_FILE_SAVE, flags);
    EnableMenuItem(hFileMenu, IDM_FILE_SAVEAS, flags);
    EnableMenuItem(hFileMenu, IDM_FILE_SAVEALL, flags);
}

/* Forward declarations for file operations */
void OpenFilesWithDialog(HWND hwnd);
void OpenFolder(HWND hwnd, const char* folderPath);
void PopulateProjectTree(HWND hwndTree, const char* rootPath, BOOL isFlat);
void LoadFileIntoEditor(const char* filePath);
void SaveFileWithDialog(HWND hwnd, BOOL saveAs);
void SaveAllFiles(HWND hwnd);
BOOL IsCOrHFile(const char* ext);
void AddFileToProject(const char* filePath);

/* Forward declarations */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateMainLayout(HWND hwnd);
void CreateMenus(HWND hwnd);
void CreateMainToolbar(HWND hwnd);
void CreateCodeToolbar(HWND hwnd);
void CreateStatusBar(HWND hwnd);
void InsertCodeTemplate(int templateId);
void ShowManipulationToolbar(BOOL show);
void UpdateStatusBar(LPCTSTR text);

/* Code templates */
static const char* codeTemplates[] = {
    "void function_name(void) {\n    \n}",                           /* IDT_INSERT_FUNC */
    "if (condition) {\n    \n}",                                      /* IDT_INSERT_IF */
    "for (int i = 0; i < n; i++) {\n    \n}",                           /* IDT_INSERT_FOR */
    "while (condition) {\n    \n}",                                     /* IDT_INSERT_WHILE */
    "switch (value) {\n    case 1:\n        break;\n    default:\n        break;\n}",                                              /* IDT_INSERT_SWITCH */
    "typedef struct {\n    \n} StructName;",                                 /* IDT_INSERT_STRUCT */
    "typedef union {\n    \n} UnionName;",                                  /* IDT_INSERT_UNION */
    "typedef enum {\n    \n} EnumName;",                                    /* IDT_INSERT_ENUM */
    "typedef existing_type new_type;",                                   /* IDT_INSERT_TYPEDEF */
    "#include \"header.h\"",                                             /* IDT_INSERT_INCLUDE */
    "#define NAME value",                                                /* IDT_INSERT_DEFINE */
};

void InsertCodeTemplate(int templateId) {
    int index = templateId - IDT_INSERT_FUNC;
    if (index >= 0 && index < 12) {
        SendMessage(hwndInput, EM_REPLACESEL, TRUE, (LPARAM)codeTemplates[index]);
        SetFocus(hwndInput);
    }
}

/* Project Settings Dialog */
INT_PTR CALLBACK ProjectSettingsDlg(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hPlatform, hCompiler, hArch;
    switch (msg) {
    case WM_INITDIALOG:
        hPlatform = GetDlgItem(hdlg, 100);
        hCompiler = GetDlgItem(hdlg, 101);
        hArch = GetDlgItem(hdlg, 102);
        /* Populate combo boxes */
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"Windows");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"Linux");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"macOS");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"Embedded");
        SendMessage(hPlatform, CB_ADDSTRING, 0, (LPARAM)"FreeBSD");
        
        SendMessage(hCompiler, CB_ADDSTRING, 0, (LPARAM)"GCC");
        SendMessage(hCompiler, CB_ADDSTRING, 0, (LPARAM)"Clang");
        SendMessage(hCompiler, CB_ADDSTRING, 0, (LPARAM)"MSVC");
        
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"x86");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"x64");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"ARM");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"ARM64");
        SendMessage(hArch, CB_ADDSTRING, 0, (LPARAM)"RISC-V");
        
        /* Set defaults */
        SendMessage(hPlatform, CB_SETCURSEL, 0, 0);
        SendMessage(hCompiler, CB_SETCURSEL, 0, 0);
        SendMessage(hArch, CB_SETCURSEL, 0, 0);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            char buf[64];
            SendMessage(hPlatform, WM_GETTEXT, 64, (LPARAM)buf);
            strcpy(g_platform, buf);
            SendMessage(hCompiler, WM_GETTEXT, 64, (LPARAM)buf);
            strcpy(g_compiler, buf);
            SendMessage(hArch, WM_GETTEXT, 64, (LPARAM)buf);
            strcpy(g_architecture, buf);
            EndDialog(hdlg, IDOK);
        } else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hdlg, IDCANCEL);
        }
        break;
    }
    return FALSE;
}

void ShowProjectSettings(HWND parent) {
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(1), parent, ProjectSettingsDlg);
    char status[256];
    sprintf(status, "Platform: %s | Compiler: %s | Architecture: %s", g_platform, g_compiler, g_architecture);
    UpdateStatusBar(status);
}

/* Get selected text from edit control */
void GetSelectedText(HWND hwndEdit, char* buffer, int bufsize) {
    int start, end;
    SendMessage(hwndEdit, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
    if (start == end) {
        buffer[0] = '\0';
        return;
    }
    int len = end - start;
    if (len >= bufsize) len = bufsize - 1;
    /* Get all text and extract selection */
    char* allText = (char*)GlobalAlloc(GPTR, len + 1);
    if (allText) {
        SendMessage(hwndEdit, WM_GETTEXT, len + 1, (LPARAM)allText);
        int i, j = 0;
        for (i = start; i < end && allText[i]; i++) {
            buffer[j++] = allText[i];
        }
        buffer[j] = '\0';
        GlobalFree((HGLOBAL)allText);
    } else {
        buffer[0] = '\0';
    }
}

/* Manipulation functions */
void ManipulateSelection(int manipId) {
    int start, end;
    SendMessage(hwndInput, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
    if (start == end) return;
    
    char sel[4096] = {0};
    GetSelectedText(hwndInput, sel, 4096);
    
    char result[8192] = {0};
    char* out = result;
    
    switch (manipId) {
    case IDM_WRAP_IF:
        sprintf(result, "if (%s) {\n    %s\n}", sel, sel);
        break;
    case IDM_WRAP_WHILE:
        sprintf(result, "while (%s) {\n    %s\n}", sel, sel);
        break;
    case IDM_WRAP_FOR:
        sprintf(result, "for (int i = 0; i < %s; i++) {\n    %s\n}", sel, sel);
        break;
    case IDM_CONVERT_FUNC:
        sprintf(result, "void %s_function(void) {\n    %s\n}", sel, sel);
        break;
    case IDM_EXTRACT_FUNC:
        sprintf(result, "void extracted_function(void) {\n    %s\n}", sel);
        break;
    case IDM_ADD_COMMENT:
        sprintf(result, "/* %s */", sel);
        break;
    case IDM_REMOVE_COMMENT:
        if (sel[0] == '/' && sel[1] == '*') {
            strcpy(result, sel + 2);
            int len = strlen(result);
            if (len >= 2 && result[len-2] == '*' && result[len-1] == '/') {
                result[len-2] = '\0';
            }
        } else {
            strcpy(result, sel);
        }
        break;
    case IDM_FORMAT_CODE:
        strcpy(result, sel);
        break;
    case IDM_CONVERT_TO_MACRO:
        sprintf(result, "#define %s", sel);
        break;
    case IDM_EXTRACT_MACRO:
        sprintf(result, "#define MACRO_%s", sel);
        break;
    default:
        strcpy(result, sel);
    }
    
    SendMessage(hwndInput, EM_SETSEL, start, end);
    SendMessage(hwndInput, EM_REPLACESEL, TRUE, (LPARAM)result);
}

void ShowManipulationToolbar(BOOL show) {
    if (show) {
        ShowWindow(hwndToolbarCode, SW_SHOW);
    } else {
        ShowWindow(hwndToolbarCode, SW_HIDE);
    }
}

void UpdateStatusBar(LPCTSTR text) {
    SendMessage(hwndStatusBar, SB_SETTEXT, 0, (LPARAM)text);
}

/* Check if file extension is .c or .h */
BOOL IsCOrHFile(const char* ext) {
    return (stricmp(ext, ".c") == 0 || stricmp(ext, ".h") == 0 || stricmp(ext, ".cpp") == 0 || stricmp(ext, ".hpp") == 0);
}

/* Add file to project tracking */
void AddFileToProject(const char* filePath) {
    if (g_openedFileCount < MAX_OPENED_FILES) {
        strcpy(g_openedFiles[g_openedFileCount++], filePath);
    }
}

/* Load file content into editor - preserve all formatting */
void LoadFileIntoEditor(const char* filePath) {
    FILE* fp = fopen(filePath, "rb");
    if (!fp) {
        MessageBox(hwndMain, "Failed to open file", "Error", MB_ICONERROR);
        return;
    }
    
    /* Get file size */
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    if (fileSize <= 0) {
        fclose(fp);
        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
        return;
    }
    
    /* Allocate buffer and read raw bytes */
    char* buffer = (char*)GlobalAlloc(GPTR, fileSize + 1);
    if (!buffer) {
        fclose(fp);
        MessageBox(hwndMain, "Out of memory", "Error", MB_ICONERROR);
        return;
    }
    
    size_t bytesRead = fread(buffer, 1, fileSize, fp);
    buffer[bytesRead] = '\0';
    fclose(fp);
    
    /* Set the text - this preserves all whitespace */
    SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)buffer);
    
    GlobalFree((HGLOBAL)buffer);
    UpdateStatusBar(filePath);
}

/* Recursively scan folder for C/H files */
void ScanFolderForFiles(const char* folderPath, char files[][MAX_PATH], int* count, int maxCount) {
    WIN32_FIND_DATA fd;
    char searchPath[MAX_PATH];
    char fullPath[MAX_PATH];
    
    sprintf(searchPath, "%s\\*", folderPath);
    HANDLE hFind = FindFirstFile(searchPath, &fd);
    
    if (hFind == INVALID_HANDLE_VALUE) return;
    
    do {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;
        
        sprintf(fullPath, "%s\\%s", folderPath, fd.cFileName);
        
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            ScanFolderForFiles(fullPath, files, count, maxCount);
        } else {
            char* ext = strrchr(fd.cFileName, '.');
            if (ext && IsCOrHFile(ext) && *count < maxCount) {
                strcpy(files[(*count)++], fullPath);
            }
        }
    } while (FindNextFile(hFind, &fd) && *count < maxCount);
    
    FindClose(hFind);
}

/* Populate project tree with folder structure or flat list */
void PopulateProjectTree(HWND hwndTree, const char* rootPath, BOOL isFlat) {
    TVINSERTSTRUCT tvis;
    HTREEITEM hRoot;
    char files[MAX_OPENED_FILES][MAX_PATH];
    int fileCount = 0;
    
    TreeView_DeleteAllItems(hwndTree);
    
    if (isFlat) {
        /* Flat mode - just list files */
        tvis.hParent = TVI_ROOT;
        tvis.hInsertAfter = TVI_LAST;
        tvis.item.mask = TVIF_TEXT;
        tvis.item.pszText = "Project Files";
        hRoot = TreeView_InsertItem(hwndTree, &tvis);
        
        for (int i = 0; i < g_openedFileCount; i++) {
            char* filename = strrchr(g_openedFiles[i], '\\');
            if (!filename) filename = g_openedFiles[i];
            else filename++;
            
            tvis.hParent = hRoot;
            tvis.item.pszText = filename;
            TreeView_InsertItem(hwndTree, &tvis);
        }
    } else {
        /* Folder-based mode - show tree structure */
        char folders[MAX_PATH][MAX_PATH];
        int folderCount = 0;
        
        tvis.hParent = TVI_ROOT;
        tvis.hInsertAfter = TVI_LAST;
        tvis.item.mask = TVIF_TEXT;
        
        char rootName[MAX_PATH];
        strcpy(rootName, strrchr(rootPath, '\\') + 1);
        tvis.item.pszText = rootName;
        hRoot = TreeView_InsertItem(hwndTree, &tvis);
        
        /* Scan folder recursively */
        ScanFolderForFiles(rootPath, files, &fileCount, MAX_OPENED_FILES);
        
        /* Add files to tree */
        for (int i = 0; i < fileCount; i++) {
            char* filename = strrchr(files[i], '\\');
            if (filename) filename++;
            else filename = files[i];
            
            tvis.hParent = hRoot;
            tvis.item.pszText = filename;
            TreeView_InsertItem(hwndTree, &tvis);
        }
    }
    
    TreeView_Expand(hwndTree, TreeView_GetRoot(hwndTree), TVE_EXPAND);
}

/* Open folder and populate tree */
void OpenFolder(HWND hwnd, const char* folderPath) {
    g_isFolderBased = TRUE;
    g_openedFileCount = 0;
    
    /* Scan for all C/H files in folder */
    ScanFolderForFiles(folderPath, g_openedFiles, &g_openedFileCount, MAX_OPENED_FILES);
    
    PopulateProjectTree(hwndProjectTree, folderPath, FALSE);
    
    char status[256];
    sprintf(status, "Opened folder: %s (%d files)", folderPath, g_openedFileCount);
    UpdateStatusBar(status);
}

/* Open files with dialog */
void OpenFilesWithDialog(HWND hwnd) {
    OPENFILENAME ofn;
    char fileBuffer[65536] = {0};
    char files[MAX_OPENED_FILES][MAX_PATH];
    int fileCount = 0;
    
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileBuffer;
    ofn.nMaxFile = sizeof(fileBuffer);
    ofn.lpstrFilter = "C/H Files (*.c;*.h)\0*.c;*.h\0All Files (*.*)\0*.*\0";
    ofn.lpstrDefExt = "c";
    ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileName(&ofn)) {
        char* p = fileBuffer;
        
        /* Check if single folder selected or multiple files */
        if (strlen(p) > 0 && p[strlen(p)-1] == '\\') {
            /* Single folder selected */
            OpenFolder(hwnd, p);
        } else {
            /* Multiple files selected */
            g_isFolderBased = FALSE;
            g_openedFileCount = 0;
            
            while (*p) {
                if (fileCount < MAX_OPENED_FILES) {
                    strcpy(files[fileCount++], p);
                    AddFileToProject(p);
                }
                p += strlen(p) + 1;
            }
            
            /* If only one file, also load it */
            if (fileCount == 1) {
                LoadFileIntoEditor(files[0]);
            }
            
            PopulateProjectTree(hwndProjectTree, "", TRUE);
            
            char status[256];
            sprintf(status, "Opened %d files", fileCount);
            UpdateStatusBar(status);
        }
    }
}

/* Save file with dialog */
void SaveFileWithDialog(HWND hwnd, BOOL saveAs) {
    OPENFILENAME ofn;
    char fileBuffer[MAX_PATH] = {0};
    
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileBuffer;
    ofn.nMaxFile = sizeof(fileBuffer);
    ofn.lpstrFilter = "C Files (*.c)\0*.c\0Header Files (*.h)\0*.h\0All Files (*.*)\0*.*\0";
    ofn.lpstrDefExt = "c";
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;
    
    if (saveAs) {
        if (GetSaveFileName(&ofn)) {
            char content[65536];
            SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
            
            FILE* fp = fopen(fileBuffer, "w");
            if (fp) {
                fputs(content, fp);
                fclose(fp);
                UpdateStatusBar(fileBuffer);
            } else {
                MessageBox(hwnd, "Failed to save file", "Error", MB_ICONERROR);
            }
        }
    } else {
        /* Simple save - just save current content */
        char content[65536];
        SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
        
        if (g_openedFileCount > 0) {
            FILE* fp = fopen(g_openedFiles[0], "w");
            if (fp) {
                fputs(content, fp);
                fclose(fp);
                UpdateStatusBar(g_openedFiles[0]);
            }
        } else {
            /* No file open, do Save As */
            SaveFileWithDialog(hwnd, TRUE);
        }
    }
}

/* Save all files (placeholder) */
void SaveAllFiles(HWND hwnd) {
    UpdateStatusBar("Save All - Not implemented yet");
}

/* Line number gutter window */
static HWND hwndLineNumbers;

/* Update line numbers based on editor content */
void UpdateLineNumbers(HWND hwndEditor, HWND hwndGutter) {
    char text[65536];
    SendMessage(hwndEditor, WM_GETTEXT, sizeof(text), (LPARAM)text);
    
    int lineCount = 1;
    for (int i = 0; text[i]; i++) {
        if (text[i] == '\n') lineCount++;
    }
    
    char lineNums[65536] = {0};
    for (int i = 1; i <= lineCount; i++) {
        char buf[16];
        sprintf(buf, "%d\n", i);
        strcat(lineNums, buf);
    }
    
    SendMessage(hwndGutter, WM_SETTEXT, 0, (LPARAM)lineNums);
}

/* Subclass procedure for line number gutter */
LRESULT CALLBACK LineNumberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        /* Get editor text and count lines */
        char text[65536] = {0};
        SendMessage(hwndInput, WM_GETTEXT, sizeof(text), (LPARAM)text);
        
        int lineCount = 1;
        for (int i = 0; text[i]; i++) {
            if (text[i] == '\n') lineCount++;
        }
        
        /* Draw line numbers */
        HFONT hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(128, 128, 128));
        
        TEXTMETRIC tm;
        GetTextMetrics(hdc, &tm);
        int lineHeight = tm.tmHeight + tm.tmExternalLeading;
        
        char buf[16];
        int y = 0;
        for (int i = 1; i <= lineCount && y < ps.rcPaint.bottom; i++) {
            sprintf(buf, "%d", i);
            RECT rc = {0, y, ps.rcPaint.right, y + lineHeight};
            DrawText(hdc, buf, -1, &rc, DT_RIGHT | DT_VTOP);
            y += lineHeight;
        }
        
        SelectObject(hdc, hOldFont);
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CreateMenus(HWND hwnd) {
    HMENU hMenuBar = CreateMenu();
    HMENU hFile = CreateMenu();
    HMENU hEdit = CreateMenu();
    HMENU hProject = CreateMenu();
    HMENU hBuild = CreateMenu();
    
    /* File menu with keyboard shortcuts */
    AppendMenu(hFile, MF_STRING, IDM_FILE_NEW, "&New Project\tCtrl+Shift+N");
    AppendMenu(hFile, MF_STRING, IDM_FILE_OPEN, "&Open Project...\tCtrl+O");
    AppendMenu(hFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFile, MF_STRING, IDM_FILE_SAVE, "&Save\tCtrl+S");
    AppendMenu(hFile, MF_STRING, IDM_FILE_SAVEAS, "Save &As...\tCtrl+Shift+S");
    AppendMenu(hFile, MF_STRING, IDM_FILE_SAVEALL, "Save A&ll\tCtrl+Shift+A");
    AppendMenu(hFile, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFile, MF_STRING, IDM_FILE_EXIT, "E&xit\tAlt+F4");
    
    /* Edit menu with keyboard shortcuts */
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_UNDO, "&Undo\tCtrl+Z");
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_REDO, "&Redo\tCtrl+Y");
    AppendMenu(hEdit, MF_SEPARATOR, 0, NULL);
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_CUT, "Cu&t\tCtrl+X");
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_COPY, "&Copy\tCtrl+C");
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_PASTE, "&Paste\tCtrl+V");
    AppendMenu(hEdit, MF_SEPARATOR, 0, NULL);
    AppendMenu(hEdit, MF_STRING, IDM_EDIT_SELECTALL, "Select &All\tCtrl+A");
    
    /* Project menu with keyboard shortcuts */
    AppendMenu(hProject, MF_STRING, IDM_PROJECT_NEW, "New &Project\tCtrl+Shift+P");
    AppendMenu(hProject, MF_STRING, IDM_PROJECT_SETTINGS, "&Settings...\tF9");
    
    /* Build menu with keyboard shortcuts */
    AppendMenu(hBuild, MF_STRING, IDM_BUILD_COMPILE, "&Compile\tF5");
    AppendMenu(hBuild, MF_STRING, IDM_BUILD_RUN, "&Run\tF6");
    
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, "&File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, "&Edit");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hProject, "&Project");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hBuild, "&Build");
    
    SetMenu(hwnd, hMenuBar);
}

void CreateMainToolbar(HWND hwnd) {
    hwndToolbarMain = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | CCS_TOP,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TOOLBAR_MAIN, GetModuleHandle(NULL), NULL);
    
    TBBUTTON tbb[8];
    memset(tbb, 0, sizeof(tbb));
    tbb[0].iBitmap = 0; tbb[0].idCommand = IDM_FILE_NEW; tbb[0].fsState = TBSTATE_ENABLED; tbb[0].fsStyle = BTNS_BUTTON; tbb[0].iString = -1;
    tbb[1].iBitmap = 0; tbb[1].idCommand = IDM_FILE_OPEN; tbb[1].fsState = TBSTATE_ENABLED; tbb[1].fsStyle = BTNS_BUTTON; tbb[1].iString = -1;
    tbb[2].iBitmap = 0; tbb[2].idCommand = IDM_FILE_SAVE; tbb[2].fsState = TBSTATE_ENABLED; tbb[2].fsStyle = BTNS_BUTTON; tbb[2].iString = -1;
    tbb[3].iBitmap = 0; tbb[3].idCommand = 0; tbb[3].fsState = 0; tbb[3].fsStyle = BTNS_SEP; tbb[3].iString = -1;
    tbb[4].iBitmap = 0; tbb[4].idCommand = IDM_EDIT_UNDO; tbb[4].fsState = TBSTATE_ENABLED; tbb[4].fsStyle = BTNS_BUTTON; tbb[4].iString = -1;
    tbb[5].iBitmap = 0; tbb[5].idCommand = IDM_EDIT_REDO; tbb[5].fsState = TBSTATE_ENABLED; tbb[5].fsStyle = BTNS_BUTTON; tbb[5].iString = -1;
    tbb[6].iBitmap = 0; tbb[6].idCommand = 0; tbb[6].fsState = 0; tbb[6].fsStyle = BTNS_SEP; tbb[6].iString = -1;
    tbb[7].iBitmap = 0; tbb[7].idCommand = IDM_PROJECT_SETTINGS; tbb[7].fsState = TBSTATE_ENABLED; tbb[7].fsStyle = BTNS_BUTTON; tbb[7].iString = -1;
    
    SendMessage(hwndToolbarMain, TB_ADDBUTTONS, 8, (LPARAM)tbb);
    SendMessage(hwndToolbarMain, TB_AUTOSIZE, 0, 0);
}

void CreateCodeToolbar(HWND hwnd) {
    hwndToolbarCode = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | CCS_TOP,
        0, 40, 0, 0, hwnd, (HMENU)IDC_TOOLBAR_CODE, GetModuleHandle(NULL), NULL);
    
    /* Code insertion buttons */
    TBBUTTON codeTbb[11];
    memset(codeTbb, 0, sizeof(codeTbb));
    int i;
    int cmdIds[] = {IDT_INSERT_FUNC, IDT_INSERT_IF, IDT_INSERT_FOR, IDT_INSERT_WHILE, IDT_INSERT_SWITCH,
                    IDT_INSERT_STRUCT, IDT_INSERT_UNION, IDT_INSERT_ENUM, IDT_INSERT_TYPEDEF, IDT_INSERT_INCLUDE, IDT_INSERT_DEFINE};
    for (i = 0; i < 11; i++) {
        codeTbb[i].iBitmap = 0; codeTbb[i].idCommand = cmdIds[i]; codeTbb[i].fsState = TBSTATE_ENABLED; codeTbb[i].fsStyle = BTNS_BUTTON; codeTbb[i].iString = -1;
    }
    
    SendMessage(hwndToolbarCode, TB_ADDBUTTONS, 11, (LPARAM)codeTbb);
    SendMessage(hwndToolbarCode, TB_AUTOSIZE, 0, 0);
    
    /* Initially hidden until selection */
    ShowWindow(hwndToolbarCode, SW_HIDE);
}

void CreateStatusBar(HWND hwnd) {
    hwndStatusBar = CreateWindowEx(0, STATUSCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
        0, 0, 0, 0, hwnd, (HMENU)IDC_STATUSBAR, GetModuleHandle(NULL), NULL);
    
    int parts[] = {200, 400, 600, -1};
    SendMessage(hwndStatusBar, SB_SETPARTS, 4, (LPARAM)parts);
    SendMessage(hwndStatusBar, SB_SETTEXT, 0, (LPARAM)"Ready");
    SendMessage(hwndStatusBar, SB_SETTEXT, 1, (LPARAM)"Platform: Windows");
    SendMessage(hwndStatusBar, SB_SETTEXT, 2, (LPARAM)"Compiler: GCC");
    SendMessage(hwndStatusBar, SB_SETTEXT, 3, (LPARAM)"Arch: x86");
}

void CreateMainLayout(HWND hwnd) {
    /* Main toolbar */
    CreateMainToolbar(hwnd);
    
    /* Code toolbar (initially hidden) */
    CreateCodeToolbar(hwnd);
    
    /* Project explorer (left pane) - with buttons for expand/collapse */
    hwndProjectTree = CreateWindowEx(WS_EX_CLIENTEDGE, "SysTreeView32", NULL,
        WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
        10, 50, 200, 500, hwnd, (HMENU)IDC_PROJECT_TREE, GetModuleHandle(NULL), NULL);
    
    /* Line number gutter */
    hwndLineNumbers = CreateWindowEx(0, "STATIC", NULL,
        WS_CHILD | WS_VISIBLE | SS_RIGHT,
        220, 50, 35, 500, hwnd, (HMENU)5001, GetModuleHandle(NULL), NULL);
    
    /* Set font for line numbers */
    HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, FIXED_PITCH | FF_DOSDEFAULT, "Courier New");
    SendMessage(hwndLineNumbers, WM_SETFONT, (WPARAM)hFont, TRUE);
    
    /* Input code pane */
    hwndInput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_NOHIDESEL,
        255, 50, 415, 500, hwnd, (HMENU)IDC_CODE_INPUT, GetModuleHandle(NULL), NULL);
    
    /* Set monospace font for code editor */
    HFONT hCodeFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, FIXED_PITCH | FF_DOSDEFAULT, "Courier New");
    SendMessage(hwndInput, WM_SETFONT, (WPARAM)hCodeFont, TRUE);
    
    /* Output code pane */
    hwndOutput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        680, 50, 450, 500, hwnd, (HMENU)IDC_CODE_OUTPUT, GetModuleHandle(NULL), NULL);
    SendMessage(hwndOutput, WM_SETFONT, (WPARAM)hCodeFont, TRUE);
    
    /* Properties window (right pane) */
    hwndProperties = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", NULL,
        WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOINTEGRALHEIGHT,
        1140, 50, 200, 500, hwnd, (HMENU)IDC_PROPERTIES, GetModuleHandle(NULL), NULL);
    
    /* Status bar */
    CreateStatusBar(hwnd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_BAR_CLASSES };
    InitCommonControlsEx(&icex);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "OrcaMainWnd";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    /* Load custom icon for high resolution displays */
    HICON hIcon = (HICON)LoadImage(hInstance, "res\\MainProgramIconLarge.ico",
        IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
    if (!hIcon) {
        /* Fallback to system icon if custom icon not found */
        hIcon = LoadIcon(NULL, IDI_APPLICATION);
    }
    wc.hIcon = hIcon;
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    RegisterClass(&wc);

    hwndMain = CreateWindow("OrcaMainWnd", "Orca - C Code Generator & Manipulator", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1400, 800, NULL, NULL, hInstance, NULL);
    
    /* Set custom icon for window (titlebar, taskbar, alt+tab) */
    if (hIcon) {
        SendMessage(hwndMain, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwndMain, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }
    
    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateMenus(hwnd);
        CreateMainLayout(hwnd);
        /* Gray out save menu items initially */
        UpdateSaveMenuState(FALSE);
        break;
        
    case WM_SIZE: {
        RECT rc;
        GetClientRect(hwnd, &rc);
        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;
        
        /* Resize main toolbar */
        MoveWindow(GetDlgItem(hwnd, IDC_TOOLBAR_MAIN), 0, 0, width, 40, TRUE);
        
        /* Resize code toolbar */
        MoveWindow(GetDlgItem(hwnd, IDC_TOOLBAR_CODE), 0, 40, width, 40, TRUE);
        
        /* Resize project tree */
        MoveWindow(GetDlgItem(hwnd, IDC_PROJECT_TREE), 10, 90, 200, height-150, TRUE);
        
        /* Resize line numbers gutter */
        MoveWindow(GetDlgItem(hwnd, 5001), 220, 90, 35, height-150, TRUE);
        
        /* Resize input pane */
        int inputWidth = (width - 290) / 2;
        MoveWindow(GetDlgItem(hwnd, IDC_CODE_INPUT), 255, 90, inputWidth, height-150, TRUE);
        
        /* Resize output pane */
        MoveWindow(GetDlgItem(hwnd, IDC_CODE_OUTPUT), 265 + inputWidth, 90, inputWidth, height-150, TRUE);
        
        /* Resize properties */
        MoveWindow(GetDlgItem(hwnd, IDC_PROPERTIES), width - 220, 90, 200, height-150, TRUE);
        
        /* Resize status bar */
        MoveWindow(GetDlgItem(hwnd, IDC_STATUSBAR), 0, height-30, width, 30, TRUE);
        break;
    }
    
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        /* File menu */
        case IDM_FILE_NEW:
            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(hwndOutput, WM_SETTEXT, 0, (LPARAM)"");
            g_openedFileCount = 0;
            g_projectOpened = TRUE;
            TreeView_DeleteAllItems(hwndProjectTree);
            UpdateSaveMenuState(TRUE);
            UpdateStatusBar("New project created");
            break;
        case IDM_FILE_OPEN:
            OpenFilesWithDialog(hwnd);
            g_projectOpened = TRUE;
            UpdateSaveMenuState(TRUE);
            break;
        case IDM_FILE_SAVE:
            SaveFileWithDialog(hwnd, FALSE);
            break;
        case IDM_FILE_SAVEAS:
            SaveFileWithDialog(hwnd, TRUE);
            break;
        case IDM_FILE_SAVEALL:
            SaveAllFiles(hwnd);
            break;
        case IDM_FILE_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
            
        /* Edit menu */
        case IDM_EDIT_UNDO:
            SendMessage(hwndInput, EM_UNDO, 0, 0);
            break;
        case IDM_EDIT_REDO:
            SendMessage(hwndInput, EM_UNDO, 1, 0);
            break;
        case IDM_EDIT_CUT:
            SendMessage(hwndInput, WM_CUT, 0, 0);
            break;
        case IDM_EDIT_COPY:
            SendMessage(hwndInput, WM_COPY, 0, 0);
            break;
        case IDM_EDIT_PASTE:
            SendMessage(hwndInput, WM_PASTE, 0, 0);
            break;
        case IDM_EDIT_SELECTALL:
            SendMessage(hwndInput, EM_SETSEL, 0, -1);
            break;
            
        /* Build menu */
        case IDM_BUILD_COMPILE:
            {
                /* Get current code and compile with GCC */
                char content[65536];
                SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
                if (strlen(content) == 0) {
                    MessageBox(hwnd, "No code to compile", "Compile", MB_ICONINFORMATION);
                } else {
                    /* Save to temp file and compile */
                    FILE* fp = fopen("build\temp.c", "w");
                    if (fp) {
                        fputs(content, fp);
                        fclose(fp);
                        UpdateStatusBar("Compiling...");
                        /* Note: Actual compilation would require running GCC */
                        MessageBox(hwnd, "Compile feature ready. GCC would compile build\temp.c", "Compile", MB_ICONINFORMATION);
                    }
                }
            }
            break;
        case IDM_BUILD_RUN:
            {
                /* Check if there's an executable to run */
                if (GetFileAttributes("build\temp.exe") != INVALID_FILE_ATTRIBUTES) {
                    UpdateStatusBar("Running executable...");
                    /* Would run the executable here */
                    MessageBox(hwnd, "Run feature ready. Would execute build\temp.exe", "Run", MB_ICONINFORMATION);
                } else {
                    MessageBox(hwnd, "No executable found. Please compile first.", "Run", MB_ICONWARNING);
                }
            }
            break;
            
        /* Project menu */
        case IDM_PROJECT_SETTINGS:
            ShowProjectSettings(hwnd);
            break;
            
        /* Code insertion toolbar */
        case IDT_INSERT_FUNC:
        case IDT_INSERT_IF:
        case IDT_INSERT_FOR:
        case IDT_INSERT_WHILE:
        case IDT_INSERT_SWITCH:
        case IDT_INSERT_STRUCT:
        case IDT_INSERT_UNION:
        case IDT_INSERT_ENUM:
        case IDT_INSERT_TYPEDEF:
        case IDT_INSERT_INCLUDE:
        case IDT_INSERT_DEFINE:
            InsertCodeTemplate(LOWORD(wParam));
            break;
        }
        break;
        
    case WM_NOTIFY:
        if (wParam == IDC_CODE_INPUT) {
            LPNMHDR pnmh = (LPNMHDR)lParam;
            if (pnmh->code == EN_UPDATE) {
                int start, end;
                SendMessage(hwndInput, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
                if (start != end) {
                    ShowManipulationToolbar(TRUE);
                } else {
                    ShowManipulationToolbar(FALSE);
                }
            }
        }
        /* Handle TreeView double-click to open file */
        else if (wParam == IDC_PROJECT_TREE) {
            LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)lParam;
            if (pnmtv->hdr.code == NM_DBLCLK) {
                HTREEITEM hItem = TreeView_GetSelection(hwndProjectTree);
                if (hItem) {
                    TVITEM tvi;
                    char buffer[MAX_PATH];
                    tvi.mask = TVIF_TEXT;
                    tvi.hItem = hItem;
                    tvi.pszText = buffer;
                    tvi.cchTextMax = MAX_PATH;
                    TreeView_GetItem(hwndProjectTree, &tvi);
                    
                    /* Find the full path from our opened files */
                    for (int i = 0; i < g_openedFileCount; i++) {
                        char* filename = strrchr(g_openedFiles[i], '\\');
                        if (filename && strcmp(filename + 1, buffer) == 0) {
                            LoadFileIntoEditor(g_openedFiles[i]);
                            break;
                        }
                    }
                }
            }
        }
        break;
        
    case WM_KEYDOWN:
        /* Handle Ctrl+A for select all in code pane */
        if (wParam == 0x41 && (GetKeyState(VK_CONTROL) & 0x8000)) {
            /* Ctrl+A - select all text in input pane */
            if (GetFocus() == hwndInput) {
                SendMessage(hwndInput, EM_SETSEL, 0, -1);
                return 0;
            }
        }
        break;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
        
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
