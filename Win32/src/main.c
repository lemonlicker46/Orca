#define _WIN32_WINNT 0x0501
#define _WIN32_IE 0x0501
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>
#include <string.h>

#ifndef TCN_RCLICK
#define TCN_RCLICK (TCN_FIRST - 5)
#endif
#include <errno.h>

/* Control IDs */
#define IDC_CODE_INPUT     1001
#define IDC_CODE_OUTPUT    1002
#define IDC_TOOLBAR_MAIN   1003
#define IDC_TOOLBAR_CODE   1004
#define IDC_STATUSBAR      1005
#define IDC_PROJECT_TREE   1006
#define IDC_PROPERTIES     1007
#define IDC_CODE_TAB       1008
#define IDC_TAB_CLOSE      1009
/* Tab navigation buttons */
#define IDC_TAB_PREV       1010
#define IDC_TAB_NEXT       1011
#define IDC_CODE_SPLITTER  1012

/* Tab context menu IDs */
#define IDM_TAB_CLOSE_SINGLE 4001
#define IDM_TAB_CLOSE_OTHERS 4002
#define IDM_TAB_CLOSE_RIGHT  4003

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
static HWND hwndLineNumbers;
static HWND hwndProperties;
static HWND hwndCodeTab;
static HWND hwndTabClose;  /* Close button for tabs */
static HWND hwndTabPrev;   /* Previous-tab button */
static HWND hwndTabNext;   /* Next-tab button */
static HWND hwndCodeSplitter; /* Vertical splitter between code and properties */
static HWND hwndDebugConsole;  /* Debug console window */
static WNDPROC hwndOldEditorProc;
static HFONT g_codeFont;
static int g_lineNumberWidth = 35;
static int g_propertiesWidth = 150;
static int g_currentInputWidth = 0;
static int g_splitterWidth = 2;
static BOOL g_isDraggingSplitter = FALSE;
static int g_splitterDragStartX = 0;
static int g_splitterStartPropertiesWidth = 0;
static int g_dragInitialInputWidth = 0;
static char g_configPath[MAX_PATH] = "";
static int g_rightClickedTab = -1; /* last tab index right-clicked */

/* Layout helper functions */
void RepositionCodeArea(int clientWidth, int clientHeight);
void UpdateLineNumbers(HWND hwndEditor, HWND hwndGutter);
LRESULT CALLBACK EditorSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void InitializeConfigPath(void);
void LoadConfig(void);
void SaveConfig(void);

/* Debug console functions */
void InitDebugConsole() {
    /* Create a console window for debugging */
    if (AllocConsole()) {
        /* Redirect stdout to the new console */
        freopen("CONOUT$", "w", stdout);
        freopen("CONIN$", "r", stdin);
        
        printf("=== Orca Debug Console ===\n");
        printf("GUI interactions will be logged here.\n\n");
        fflush(stdout);
    }
}

void DebugLog(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    /* Print to console */
    printf("%s", buffer);
    fflush(stdout);
    
    /* Also write to debug.log file */
    /* Ensure debug.log is written into the Win32 folder (parent of exe's parent) */
    char modulePath[MAX_PATH];
    char logPath[MAX_PATH];
    GetModuleFileNameA(NULL, modulePath, MAX_PATH);
    /* Strip executable name */
    char* p = strrchr(modulePath, '\\');
    if (p) *p = '\0';
    /* Now modulePath is ..\...\Win32\build -> strip one more component to get Win32 */
    p = strrchr(modulePath, '\\');
    if (p) *p = '\0';
    /* modulePath now points to Win32 root */
    snprintf(logPath, MAX_PATH, "%s\\debug.log", modulePath);
    FILE* logFile = fopen(logPath, "a");
    if (logFile) {
        fprintf(logFile, "%s", buffer);
        fclose(logFile);
    }
}

void InitializeConfigPath(void) {
    char modulePath[MAX_PATH];
    if (GetModuleFileNameA(NULL, modulePath, MAX_PATH)) {
        char* p = strrchr(modulePath, '\\');
        if (p) *p = '\0';
        snprintf(g_configPath, MAX_PATH, "%s\\config.ini", modulePath);
    } else {
        strcpy(g_configPath, "config.ini");
    }
}

void LoadConfig(void) {
    if (g_configPath[0] == '\0') {
        InitializeConfigPath();
    }
    int width = GetPrivateProfileIntA("Layout", "CodePaneWidth", 0, g_configPath);
    if (width > 0) {
        g_currentInputWidth = width;
    }
    DebugLog("[CONFIG] Loaded config from %s, CodePaneWidth=%d\n", g_configPath, g_currentInputWidth);
}

void SaveConfig(void) {
    if (g_configPath[0] == '\0') {
        InitializeConfigPath();
    }
    if (g_currentInputWidth > 0) {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%d", g_currentInputWidth);
        WritePrivateProfileStringA("Layout", "CodePaneWidth", buffer, g_configPath);
        DebugLog("[CONFIG] Saved CodePaneWidth=%d to %s\n", g_currentInputWidth, g_configPath);
    } else {
        DebugLog("[CONFIG] No CodePaneWidth to save, skipping\n");
    }
}

/* Integrated debug viewer removed: using console/debug.log only */

/* Tab management */
#define MAX_TABS 32
typedef struct {
    char filePath[MAX_PATH];
    char title[MAX_PATH];
    BOOL isModified;
    HWND editorWnd;
} TabInfo;

static TabInfo g_tabs[MAX_TABS];
static int g_tabCount = 0;
static int g_activeTab = -1;
static int g_tabScrollIndex = 0; /* highest-priority visible tab for scroll buttons */
static BOOL g_ignoreTabSelectionChange = FALSE;

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
void PositionTabCloseButton();
static BOOL TabControlNeedsScroll(void);
static void UpdateTabNavigationButtons(void);
static void EnsureTabVisible(int tabIndex);

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

/* Tab management functions */
int FindTabByPath(const char* filePath) {
    for (int i = 0; i < g_tabCount; i++) {
        if (strcmp(g_tabs[i].filePath, filePath) == 0) {
            return i;
        }
    }
    return -1;
}

int CreateNewTab(const char* filePath, const char* title) {
    if (g_tabCount >= MAX_TABS) {
        MessageBox(hwndMain, "Too many tabs open", "Error", MB_ICONWARNING);
        return -1;
    }
    
    int idx = g_tabCount++;
    strcpy(g_tabs[idx].filePath, filePath);
    strcpy(g_tabs[idx].title, title);
    g_tabs[idx].isModified = FALSE;
    g_tabs[idx].editorWnd = NULL;
    
    return idx;
}

void CloseTab(int tabIdx) {
    if (tabIdx < 0 || tabIdx >= g_tabCount) return;
    
    /* Shift remaining tabs */
    for (int i = tabIdx; i < g_tabCount - 1; i++) {
        g_tabs[i] = g_tabs[i + 1];
    }
    g_tabCount--;
    
    if (g_activeTab >= g_tabCount) {
        g_activeTab = g_tabCount - 1;
    }
}

void UpdateTabTitle(int tabIdx, BOOL isModified) {
    if (tabIdx < 0 || tabIdx >= g_tabCount) return;
    
    g_tabs[tabIdx].isModified = isModified;
    
    /* Truncate long titles to 14 chars */
    char title[MAX_PATH];
    char* src = g_tabs[tabIdx].title;
    int len = strlen(src);
    if (len > 14) {
        /* Copy first 11 chars + "..." = 14 total */
        strncpy(title, src, 11);
        title[11] = '\0';
        strcat(title, "...");
    } else {
        strcpy(title, src);
    }
    
    if (isModified) {
        sprintf(title, "* %s", title);
    }
    
    TCITEM tci;
    tci.mask = TCIF_TEXT;
    tci.pszText = title;
    TabCtrl_SetItem(hwndCodeTab, tabIdx, &tci);
}

void RefreshTabControl() {
    /* Clear all tabs */
    TabCtrl_DeleteAllItems(hwndCodeTab);
    
    /* Re-add all tabs */
    TCITEM tci;
    tci.mask = TCIF_TEXT;
    
    for (int i = 0; i < g_tabCount; i++) {
        char title[MAX_PATH];
        char* src = g_tabs[i].title;
        int len = strlen(src);
        if (len > 14) {
            strncpy(title, src, 11);
            title[11] = '\0';
            strcat(title, "...");
        } else {
            strcpy(title, src);
        }
        
        if (g_tabs[i].isModified) {
            sprintf(title, "* %s", title);
        }
        tci.pszText = title;
        TabCtrl_InsertItem(hwndCodeTab, i, &tci);
    }
    
    /* Select active tab */
    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
        TabCtrl_SetCurSel(hwndCodeTab, g_activeTab);
        EnsureTabVisible(g_activeTab);
    }
    
    UpdateTabNavigationButtons();
    
    /* Position close button next to active tab */
    PositionTabCloseButton();
}

/* Position the close button next to the active tab */
void PositionTabCloseButton() {
    if (g_activeTab < 0 || g_activeTab >= g_tabCount) {
        ShowWindow(hwndTabClose, SW_HIDE);
        return;
    }
    
    /* Get the bounding rectangle of the active tab */
    RECT tabRect;
    if (TabCtrl_GetItemRect(hwndCodeTab, g_activeTab, &tabRect)) {
        /* Get tab control position */
        RECT tabCtrlRect;
        GetWindowRect(hwndCodeTab, &tabCtrlRect);
        
        /* Calculate close button position - to the right of the tab text */
        int btnX = tabCtrlRect.left + tabRect.right - 5;
        int btnY = tabCtrlRect.top + 3;
        
        /* Only show if there's room */
        if (btnX + 20 < tabCtrlRect.right) {
            SetWindowPos(hwndTabClose, HWND_TOP, btnX, btnY, 16, 16, SWP_SHOWWINDOW);
            ShowWindow(hwndTabClose, SW_SHOW);
        } else {
            ShowWindow(hwndTabClose, SW_HIDE);
        }
    }
}

static BOOL TabControlNeedsScroll(void) {
    if (g_tabCount < 2 || !hwndCodeTab) return FALSE;
    RECT rc;
    GetClientRect(hwndCodeTab, &rc);
    HDC hdc = GetDC(hwndCodeTab);
    HFONT hFont = (HFONT)SendMessage(hwndCodeTab, WM_GETFONT, 0, 0);
    HFONT hOld = (HFONT)SelectObject(hdc, hFont ? hFont : GetStockObject(SYSTEM_FONT));
    int totalWidth = 0;
    for (int i = 0; i < g_tabCount; i++) {
        char title[MAX_PATH];
        char* src = g_tabs[i].title;
        int len = strlen(src);
        if (len > 14) {
            strncpy(title, src, 11);
            title[11] = '\0';
            strcat(title, "...");
        } else {
            strcpy(title, src);
        }
        if (g_tabs[i].isModified) {
            char temp[MAX_PATH];
            sprintf(temp, "* %s", title);
            strcpy(title, temp);
        }
        SIZE size;
        GetTextExtentPoint32(hdc, title, strlen(title), &size);
        totalWidth += size.cx + 30;
        if (totalWidth > rc.right - rc.left) {
            SelectObject(hdc, hOld);
            ReleaseDC(hwndCodeTab, hdc);
            return TRUE;
        }
    }
    SelectObject(hdc, hOld);
    ReleaseDC(hwndCodeTab, hdc);
    return FALSE;
}

static void UpdateTabNavigationButtons(void) {
    BOOL needScroll = TabControlNeedsScroll();
    if (hwndTabPrev) ShowWindow(hwndTabPrev, needScroll ? SW_SHOW : SW_HIDE);
    if (hwndTabNext) ShowWindow(hwndTabNext, needScroll ? SW_SHOW : SW_HIDE);
}

static void EnsureTabVisible(int tabIndex) {
    if (tabIndex >= 0 && tabIndex < g_tabCount && hwndCodeTab) {
        int currentSel = TabCtrl_GetCurSel(hwndCodeTab);
        if (currentSel != tabIndex) {
            g_ignoreTabSelectionChange = TRUE;
            TabCtrl_SetCurSel(hwndCodeTab, tabIndex);
            if (currentSel >= 0) {
                TabCtrl_SetCurSel(hwndCodeTab, currentSel);
            }
            g_ignoreTabSelectionChange = FALSE;
        }
        g_tabScrollIndex = tabIndex;
    }
}

int PromptSaveTab(int tabIdx) {
    if (tabIdx < 0 || tabIdx >= g_tabCount) return IDYES;
    
    if (!g_tabs[tabIdx].isModified) return IDYES;
    
    char msg[MAX_PATH + 64];
    sprintf(msg, "Save changes to %s?", g_tabs[tabIdx].title);
    
    int result = MessageBox(hwndMain, msg, "Save", MB_YESNOCANCEL | MB_ICONQUESTION);
    
    if (result == IDYES) {
        /* Save the file */
        FILE* fp = fopen(g_tabs[tabIdx].filePath, "w");
        if (fp) {
            char content[65536];
            SendMessage(hwndInput, WM_GETTEXT, sizeof(content), (LPARAM)content);
            fputs(content, fp);
            fclose(fp);
            g_tabs[tabIdx].isModified = FALSE;
            UpdateTabTitle(tabIdx, FALSE);
        } else {
            MessageBox(hwndMain, "Failed to save file", "Error", MB_ICONERROR);
            return IDCANCEL;
        }
    }
    
    return result;
}

int PromptSaveAllTabs() {
    for (int i = 0; i < g_tabCount; i++) {
        int result = PromptSaveTab(i);
        if (result == IDCANCEL) return IDCANCEL;
    }
    return IDYES;
}

void ClearAllTabs() {
    g_tabCount = 0;
    g_activeTab = -1;
    TabCtrl_DeleteAllItems(hwndCodeTab);
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
    DebugLog("[EDITOR] LoadFileIntoEditor called with: %s\n", filePath);
    FILE* fp = fopen(filePath, "rb");
    if (!fp) {
        DebugLog("[ERROR] fopen failed for: %s (errno=%d)\n", filePath, errno);
        MessageBox(hwndMain, "Failed to open file", "Error", MB_ICONERROR);
        return;
    }
    
    DebugLog("[EDITOR] File opened successfully\n");
    
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
    fclose(fp);
    
    /* Strip UTF-8 BOM if present so ANSI edit control does not get weird characters */
    if (bytesRead >= 3 && (unsigned char)buffer[0] == 0xEF && (unsigned char)buffer[1] == 0xBB && (unsigned char)buffer[2] == 0xBF) {
        memmove(buffer, buffer + 3, bytesRead - 3);
        bytesRead -= 3;
        DebugLog("[EDITOR] Stripped UTF-8 BOM from file\n");
    }

    /* Normalize line endings to CRLF for Windows edit control compatibility */
    char* normalized = (char*)GlobalAlloc(GPTR, bytesRead * 2 + 1);
    if (!normalized) {
        GlobalFree((HGLOBAL)buffer);
        MessageBox(hwndMain, "Out of memory", "Error", MB_ICONERROR);
        return;
    }

    char* src = buffer;
    char* dst = normalized;
    for (size_t i = 0; i < bytesRead; i++) {
        if (src[i] == '\n') {
            if (i == 0 || src[i - 1] != '\r') {
                *dst++ = '\r';
            }
            *dst++ = '\n';
        } else if (src[i] == '\r') {
            *dst++ = '\r';
            if (i + 1 >= bytesRead || src[i + 1] != '\n') {
                *dst++ = '\n';
            }
        } else {
            *dst++ = src[i];
        }
    }
    *dst = '\0';

    /* Set the text - this preserves all whitespace */
    SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)normalized);
    /* Ensure the edit control does not auto-wrap lines */
    SendMessage(hwndInput, EM_FMTLINES, FALSE, 0);
    UpdateLineNumbers(hwndInput, hwndLineNumbers);

    GlobalFree((HGLOBAL)normalized);
    GlobalFree((HGLOBAL)buffer);
    
    /* Add to tab if not already open */
    char* filename = strrchr(filePath, '\\');
    if (filename) filename++;
    else filename = (char*)filePath;
    
    int tabIdx = FindTabByPath(filePath);
    if (tabIdx == -1) {
        tabIdx = CreateNewTab(filePath, filename);
        RefreshTabControl();
    }
    
    g_activeTab = tabIdx;
    TabCtrl_SetCurSel(hwndCodeTab, g_activeTab);
    EnsureTabVisible(g_activeTab);
    
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
            tvis.item.mask = TVIF_TEXT;
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
        
        /* Get folder name from path */
        char rootName[MAX_PATH];
        const char* lastSlash = strrchr(rootPath, '\\');
        if (lastSlash) {
            strcpy(rootName, lastSlash + 1);
        } else {
            strcpy(rootName, rootPath);
        }
        tvis.item.pszText = rootName;
        hRoot = TreeView_InsertItem(hwndTree, &tvis);
        
        /* Scan folder recursively */
        ScanFolderForFiles(rootPath, files, &fileCount, MAX_OPENED_FILES);
        
        /* Add files to tree under root */
        for (int i = 0; i < fileCount; i++) {
            char* filename = strrchr(files[i], '\\');
            if (filename) filename++;
            else filename = files[i];
            
            tvis.hParent = hRoot;
            tvis.item.mask = TVIF_TEXT;
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
    
    DebugLog("[DIALOG] OpenFilesWithDialog called\n");
    
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileBuffer;
    ofn.nMaxFile = sizeof(fileBuffer);
    ofn.lpstrFilter = "C/H Files (*.c;*.h)\0*.c;*.h\0All Files (*.*)\0*.*\0";
    ofn.lpstrDefExt = "c";
    ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileName(&ofn)) {
        DebugLog("[DIALOG] GetOpenFileName returned TRUE\n");
        char* p = fileBuffer;
        
        /* Check if single folder selected or multiple files */
        if (strlen(p) > 0 && p[strlen(p)-1] == '\\') {
            /* Single folder selected */
            DebugLog("[DIALOG] Folder mode: %s\n", p);
            OpenFolder(hwnd, p);
        } else {
            /* Multiple files selected - format: "dir\0file1\0file2\0\0" */
            DebugLog("[DIALOG] Multi-file mode\n");
            g_isFolderBased = FALSE;
            g_openedFileCount = 0;
            
            /* Determine whether a single file or multiple files were selected */
            char dirPath[MAX_PATH];
            strcpy(dirPath, p);
            p += strlen(p) + 1;
            
            if (*p == '\0') {
                /* Single file selected: full path is returned as the first string */
                if (fileCount < MAX_OPENED_FILES) {
                    strcpy(files[fileCount++], dirPath);
                    DebugLog("[DIALOG] Single file selected: %s\n", dirPath);
                    AddFileToProject(dirPath);
                }
            } else {
                /* Multiple files selected - first string is the directory */
                DebugLog("[DIALOG] Directory: %s\n", dirPath);
                while (*p) {
                    char fullPath[MAX_PATH];
                    sprintf(fullPath, "%s\\%s", dirPath, p);
                    
                    if (fileCount < MAX_OPENED_FILES) {
                        strcpy(files[fileCount++], fullPath);
                        DebugLog("[DIALOG] File %d: %s\n", fileCount, fullPath);
                        AddFileToProject(fullPath);
                    }
                    p += strlen(p) + 1;
                }
            }
            
            DebugLog("[DIALOG] Total files selected: %d\n", fileCount);
            
            /* Load the first file into editor */
            if (fileCount > 0) {
                DebugLog("[DIALOG] Loading first file: %s\n", files[0]);
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

/* Update line numbers based on editor content */
void RepositionCodeArea(int clientWidth, int clientHeight) {
    int codeLeft = 220 + g_lineNumberWidth;
    int availableCodeWidth = clientWidth - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
    if (availableCodeWidth < 240) availableCodeWidth = 240;
    int inputWidth = (g_currentInputWidth > 0) ? g_currentInputWidth : (availableCodeWidth * 85 / 100);
    if (g_currentInputWidth == 0) g_currentInputWidth = inputWidth;
    int splitterX = codeLeft + inputWidth;
    int outputX = splitterX + g_splitterWidth + 5;
    int outputWidth = clientWidth - outputX - g_propertiesWidth - 10;
    if (outputWidth < 100) outputWidth = 100;

    MoveWindow(hwndProjectTree, 10, 90, 200, clientHeight - 150, TRUE);
    MoveWindow(hwndLineNumbers, 220, 115, g_lineNumberWidth, clientHeight - 165, TRUE);
    MoveWindow(hwndCodeTab, codeLeft, 90, inputWidth, 25, TRUE);
    /* Position tab navigation buttons on the right side of the tab bar */
    if (hwndTabPrev) MoveWindow(hwndTabPrev, codeLeft + inputWidth - 50, 88, 22, 22, TRUE);
    if (hwndTabNext) MoveWindow(hwndTabNext, codeLeft + inputWidth - 26, 88, 22, 22, TRUE);
    MoveWindow(hwndInput, codeLeft, 115, inputWidth, clientHeight - 165, TRUE);
    MoveWindow(hwndCodeSplitter, splitterX, 90, g_splitterWidth, clientHeight - 150, TRUE);
    MoveWindow(hwndOutput, outputX, 90, outputWidth, clientHeight - 150, TRUE);
    MoveWindow(hwndProperties, clientWidth - g_propertiesWidth, 90, g_propertiesWidth, clientHeight - 150, TRUE);
    PositionTabCloseButton();
    UpdateTabNavigationButtons();
}

void UpdateLineNumbers(HWND hwndEditor, HWND hwndGutter) {
    int lineCount = (int)SendMessage(hwndEditor, EM_GETLINECOUNT, 0, 0);
    if (lineCount < 1) lineCount = 1;

    int digits = 1;
    for (int n = lineCount; n >= 10; n /= 10) digits++;

    HDC hdc = GetDC(hwndGutter);
    HFONT hFont = (HFONT)SendMessage(hwndGutter, WM_GETFONT, 0, 0);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    TEXTMETRIC tm;
    GetTextMetrics(hdc, &tm);
    int desiredWidth = digits * tm.tmAveCharWidth + 14;
    if (desiredWidth < 24) desiredWidth = 24;
    SelectObject(hdc, hOldFont);
    ReleaseDC(hwndGutter, hdc);

    if (desiredWidth != g_lineNumberWidth) {
        g_lineNumberWidth = desiredWidth;
        RECT rc;
        GetClientRect(hwndMain, &rc);
        RepositionCodeArea(rc.right - rc.left, rc.bottom - rc.top);
    }

    InvalidateRect(hwndGutter, NULL, TRUE);
    UpdateWindow(hwndGutter);
}

LRESULT CALLBACK EditorSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_VSCROLL || msg == WM_MOUSEWHEEL || msg == EM_SCROLL || msg == WM_KEYDOWN) {
        LRESULT result = CallWindowProc((WNDPROC)hwndOldEditorProc, hwnd, msg, wParam, lParam);
        UpdateLineNumbers(hwndInput, hwndLineNumbers);
        return result;
    }
    return CallWindowProc((WNDPROC)hwndOldEditorProc, hwnd, msg, wParam, lParam);
}

/* Subclass procedure for line number gutter */
LRESULT CALLBACK LineNumberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        int lineCount = (int)SendMessage(hwndInput, EM_GETLINECOUNT, 0, 0);
        if (lineCount < 1) lineCount = 1;
        
        /* Draw line numbers */
        HFONT hFont = g_codeFont;
        if (!hFont) {
            hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
        }
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(128, 128, 128));
        
        TEXTMETRIC tm;
        GetTextMetrics(hdc, &tm);
        int lineHeight = tm.tmHeight + tm.tmExternalLeading;
        
        RECT editRect = {0};
        SendMessage(hwndInput, EM_GETRECT, 0, (LPARAM)&editRect);
        
        int firstVisibleLine = (int)SendMessage(hwndInput, EM_GETFIRSTVISIBLELINE, 0, 0);
        int y = editRect.top + 1; /* shift down by 1px for better alignment */
        
        int startLine = firstVisibleLine + 1;
        char buf[16];
        for (int i = startLine; i <= lineCount && y < ps.rcPaint.bottom; i++) {
            sprintf(buf, "%d", i);
            RECT rc = {0, y, ps.rcPaint.right, y + lineHeight};
            DrawText(hdc, buf, -1, &rc, DT_RIGHT | DT_NOPREFIX | DT_SINGLELINE | DT_TOP);
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
    DebugLog("[FUNC] CreateMenus called\n");
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
    AppendMenu(hProject, MF_STRING, IDM_PROJECT_SETTINGS, "&Settings...\tF9");
    
    /* Build menu with keyboard shortcuts */
    AppendMenu(hBuild, MF_STRING, IDM_BUILD_COMPILE, "&Compile\tF5");
    AppendMenu(hBuild, MF_STRING, IDM_BUILD_RUN, "&Run\tF6");
    
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile, "&File");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEdit, "&Edit");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hProject, "&Project");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hBuild, "&Build");
    
    SetMenu(hwnd, hMenuBar);
    DebugLog("[FUNC] CreateMenus complete\n");
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
    hwndLineNumbers = CreateWindowEx(0, "OrcaLineNumberWnd", NULL,
        WS_CHILD | WS_VISIBLE,
        220, 115, g_lineNumberWidth, 500, hwnd, (HMENU)5001, GetModuleHandle(NULL), NULL);
    
    /* Set font for line numbers */
    SendMessage(hwndLineNumbers, WM_SETFONT, (WPARAM)g_codeFont, TRUE);
    
    /* Tab control for code files */
    hwndCodeTab = CreateWindowEx(0, WC_TABCONTROL, NULL,
        WS_CHILD | WS_VISIBLE | TCS_TABS,
        255, 50, 415, 25, hwnd, (HMENU)IDC_CODE_TAB, GetModuleHandle(NULL), NULL);
    
    /* Tab close button (hidden initially) */
    hwndTabClose = CreateWindowEx(0, "BUTTON", "x",
        WS_CHILD | BS_CENTER | BS_FLAT | WS_VISIBLE,
        0, 0, 20, 20, hwnd, (HMENU)IDC_TAB_CLOSE, GetModuleHandle(NULL), NULL);
    /* Tab navigation buttons (prev/next) */
    hwndTabPrev = CreateWindowEx(0, "BUTTON", "<",
        WS_CHILD | BS_CENTER | BS_PUSHBUTTON | WS_VISIBLE,
        0, 0, 22, 22, hwnd, (HMENU)IDC_TAB_PREV, GetModuleHandle(NULL), NULL);
    hwndTabNext = CreateWindowEx(0, "BUTTON", ">",
        WS_CHILD | BS_CENTER | BS_PUSHBUTTON | WS_VISIBLE,
        0, 0, 22, 22, hwnd, (HMENU)IDC_TAB_NEXT, GetModuleHandle(NULL), NULL);
    
    /* Input code pane - below tabs */
    hwndInput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_NOHIDESEL,
        255, 75, 415, 475, hwnd, (HMENU)IDC_CODE_INPUT, GetModuleHandle(NULL), NULL);
    
    /* Set monospace font for code editor */
    g_codeFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, "Courier New");
    SendMessage(hwndInput, WM_SETFONT, (WPARAM)g_codeFont, TRUE);
    SendMessage(hwndInput, EM_FMTLINES, FALSE, 0);
    hwndOldEditorProc = (WNDPROC)SetWindowLongPtr(hwndInput, GWLP_WNDPROC, (LONG_PTR)EditorSubclassProc);
    
    /* Output code pane */
    hwndOutput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY,
        680, 50, 450, 500, hwnd, (HMENU)IDC_CODE_OUTPUT, GetModuleHandle(NULL), NULL);
    SendMessage(hwndOutput, WM_SETFONT, (WPARAM)g_codeFont, TRUE);
    SendMessage(hwndOutput, EM_FMTLINES, FALSE, 0);
    
    /* Splitter handle between code output and properties */
    hwndCodeSplitter = CreateWindowEx(0, "STATIC", NULL,
        WS_CHILD | WS_VISIBLE,
        1140 - g_splitterWidth, 50, g_splitterWidth, 500, hwnd, (HMENU)IDC_CODE_SPLITTER, GetModuleHandle(NULL), NULL);

    /* Properties window (right pane) */
    hwndProperties = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", NULL,
        WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOINTEGRALHEIGHT,
        1140, 50, 200, 500, hwnd, (HMENU)IDC_PROPERTIES, GetModuleHandle(NULL), NULL);
    
    /* Status bar */
    CreateStatusBar(hwnd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    /* Initialize debug console - spawn separate window */
    STARTUPINFO si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    
    /* Initialize console logging */
    InitDebugConsole();
    DebugLog("[INIT] WinMain started\n");
    DebugLog("[DEBUG] Console initialized\n");
    
    INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_BAR_CLASSES };
    InitCommonControlsEx(&icex);
    DebugLog("[INIT] Common controls initialized\n");

    WNDCLASS lnwc = {0};
    lnwc.lpfnWndProc = LineNumberWndProc;
    lnwc.hInstance = hInstance;
    lnwc.lpszClassName = "OrcaLineNumberWnd";
    lnwc.hCursor = LoadCursor(NULL, IDC_ARROW);
    lnwc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    RegisterClass(&lnwc);

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

    LoadConfig();

    hwndMain = CreateWindow("OrcaMainWnd", "Orca - C Code Generator & Manipulator", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1400, 800, NULL, NULL, hInstance, NULL);
    
    /* Set custom icon for window (titlebar, taskbar, alt+tab) */
    if (hIcon) {
        SendMessage(hwndMain, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwndMain, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }
    
    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    HACCEL hAccel;
    
    /* Create accelerator table for keyboard shortcuts */
    ACCEL accels[] = {
        {FVIRTKEY | FCONTROL | FSHIFT, 0x4E, IDM_FILE_NEW},       /* Ctrl+Shift+N */
        {FVIRTKEY | FCONTROL, 0x4F, IDM_FILE_OPEN},                /* Ctrl+O */
        {FVIRTKEY | FCONTROL, 0x53, IDM_FILE_SAVE},                /* Ctrl+S */
        {FVIRTKEY | FCONTROL | FSHIFT, 0x53, IDM_FILE_SAVEAS},     /* Ctrl+Shift+S */
        {FVIRTKEY | FCONTROL | FSHIFT, 0x41, IDM_FILE_SAVEALL},    /* Ctrl+Shift+A */
        {FVIRTKEY | FCONTROL | FSHIFT, 0x50, IDM_PROJECT_NEW},     /* Ctrl+Shift+P */
        {FVIRTKEY | FCONTROL, 0x5A, IDM_EDIT_UNDO},                 /* Ctrl+Z */
        {FVIRTKEY | FCONTROL, 0x59, IDM_EDIT_REDO},                 /* Ctrl+Y */
        {FVIRTKEY | FCONTROL, 0x58, IDM_EDIT_CUT},                  /* Ctrl+X */
        {FVIRTKEY | FCONTROL, 0x43, IDM_EDIT_COPY},                 /* Ctrl+C */
        {FVIRTKEY | FCONTROL, 0x56, IDM_EDIT_PASTE},                /* Ctrl+V */
        {FVIRTKEY | FCONTROL, 0x41, IDM_EDIT_SELECTALL},            /* Ctrl+A */
        {FVIRTKEY, 0x70, IDM_PROJECT_SETTINGS},                    /* F9 */
        {FVIRTKEY, 0x74, IDM_BUILD_COMPILE},                        /* F5 */
        {FVIRTKEY, 0x75, IDM_BUILD_RUN},                            /* F6 */
    };
    hAccel = CreateAcceleratorTable(accels, 16);
    
    /* Parse command line parameters - load files passed as arguments */
    if (lpCmdLine && strlen(lpCmdLine) > 0) {
        DebugLog("[CMDLINE] Processing command line: %s\n", lpCmdLine);
        char cmdCopy[2048];
        strcpy(cmdCopy, lpCmdLine);
        
        /* Parse arguments separated by spaces/quotes */
        char filePaths[32][MAX_PATH];
        int fileCount = 0;
        
        char* p = cmdCopy;
        while (*p && fileCount < 32) {
            /* Skip whitespace */
            while (*p && (*p == ' ' || *p == '\t')) p++;
            if (!*p) break;
            
            /* Check if quoted */
            BOOL isQuoted = (*p == '"');
            if (isQuoted) p++;
            
            /* Extract filename */
            int idx = 0;
            while (*p && idx < MAX_PATH - 1) {
                if (isQuoted && *p == '"') break;
                if (!isQuoted && (*p == ' ' || *p == '\t')) break;
                filePaths[fileCount][idx++] = *p;
                p++;
            }
            filePaths[fileCount][idx] = '\0';
            
            if (idx > 0) {
                DebugLog("[CMDLINE] File %d: %s\n", fileCount + 1, filePaths[fileCount]);
                AddFileToProject(filePaths[fileCount]);
                fileCount++;
            }
            
            if (isQuoted && *p == '"') p++;
        }
        
        if (fileCount > 0) {
            g_isFolderBased = FALSE;
            g_projectOpened = TRUE;
            PopulateProjectTree(hwndProjectTree, "", TRUE);
            
            /* Load first file into editor */
            DebugLog("[CMDLINE] Loading first file: %s\n", filePaths[0]);
            LoadFileIntoEditor(filePaths[0]);
            
            UpdateSaveMenuState(TRUE);
            char status[256];
            sprintf(status, "Loaded %d files from command line", fileCount);
            UpdateStatusBar(status);
        }
    }
    
    MSG msg;
    DebugLog("[LOOP] Entering message loop\n");
    while (GetMessage(&msg, NULL, 0, 0)) {
        /* Only log important messages */
        if (msg.message == WM_COMMAND) {
            DebugLog("[LOOP] WM_COMMAND dispatching - ID: 0x%X\n", LOWORD(msg.wParam));
        } else if (msg.message == WM_NOTIFY) {
            DebugLog("[LOOP] WM_NOTIFY dispatching\n");
        } else if (msg.message == WM_KEYDOWN) {
            DebugLog("[LOOP] WM_KEYDOWN dispatching - Key: 0x%X\n", msg.wParam);
        } else if (msg.message == WM_LBUTTONDOWN) {
            DebugLog("[LOOP] WM_LBUTTONDOWN dispatching\n");
        } else if (msg.message == WM_LBUTTONUP) {
            DebugLog("[LOOP] WM_LBUTTONUP dispatching\n");
        }
        if (!TranslateAccelerator(hwndMain, hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    DebugLog("[LOOP] Exiting message loop\n");
    DestroyAcceleratorTable(hAccel);
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    /* Log all important messages at entry point */
    switch (msg) {
    case WM_CREATE:
        DebugLog("[MSG] WM_CREATE\n");
        DebugLog("[EVENT] WindowCreate\n");
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
        DebugLog("[MSG] WM_SIZE\n");
        DebugLog("[SIZE] Window resized to %dx%d\n", width, height);
        
        /* Resize main toolbar */
        MoveWindow(GetDlgItem(hwnd, IDC_TOOLBAR_MAIN), 0, 0, width, 40, TRUE);
        
        /* Resize code toolbar */
        MoveWindow(GetDlgItem(hwnd, IDC_TOOLBAR_CODE), 0, 40, width, 40, TRUE);
        
        /* Resize rest of layout */
        RepositionCodeArea(width, height);
        
        /* Resize status bar */
        MoveWindow(GetDlgItem(hwnd, IDC_STATUSBAR), 0, height-30, width, 30, TRUE);
        break;
    }
    
    case WM_COMMAND:
        DebugLog("[MSG] WM_COMMAND received (wParam=0x%X, lParam=0x%X)\n", wParam, lParam);
        switch (LOWORD(wParam)) {
        /* File menu */
        case IDM_FILE_NEW:
            DebugLog("[MENU] FileNewProjectMenuItemClick\n");
            /* Prompt to save before creating new project */
            if (PromptSaveAllTabs() == IDCANCEL) break;
            ClearAllTabs();
            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(hwndOutput, WM_SETTEXT, 0, (LPARAM)"");
            g_openedFileCount = 0;
            g_projectOpened = TRUE;
            TreeView_DeleteAllItems(hwndProjectTree);
            UpdateSaveMenuState(TRUE);
            UpdateStatusBar("New project created");
            break;
        case IDM_FILE_OPEN:
            DebugLog("[MENU] FileOpenProjectMenuItemClick\n");
            /* Prompt to save before opening new project */
            if (PromptSaveAllTabs() == IDCANCEL) break;
            ClearAllTabs();
            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(hwndOutput, WM_SETTEXT, 0, (LPARAM)"");
            OpenFilesWithDialog(hwnd);
            g_projectOpened = TRUE;
            UpdateSaveMenuState(TRUE);
            break;
        case IDM_FILE_SAVE:
            DebugLog("[MENU] FileSaveMenuItemClick\n");
            SaveFileWithDialog(hwnd, FALSE);
            break;
        case IDM_FILE_SAVEAS:
            DebugLog("[MENU] FileSaveAsMenuItemClick\n");
            SaveFileWithDialog(hwnd, TRUE);
            break;
        case IDM_FILE_SAVEALL:
            DebugLog("[MENU] FileSaveAllMenuItemClick\n");
            SaveAllFiles(hwnd);
            break;
        case IDM_FILE_EXIT:
            DebugLog("[MENU] FileExitMenuItemClick\n");
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
            
        case IDC_CODE_INPUT:
            if (HIWORD(wParam) == EN_CHANGE || HIWORD(wParam) == EN_VSCROLL) {
                UpdateLineNumbers(hwndInput, hwndLineNumbers);
            }
            break;

        /* Tab close button */
        case IDC_TAB_CLOSE:
            DebugLog("[TAB] TabCloseButtonClick(%s)\n", g_activeTab >= 0 ? g_tabs[g_activeTab].title : "none");
            if (g_activeTab >= 0) {
                /* Prompt to save if modified */
                int result = PromptSaveTab(g_activeTab);
                if (result != IDCANCEL) {
                    CloseTab(g_activeTab);
                    RefreshTabControl();
                    
                    /* Load the new active tab's content */
                    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                        LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                    } else {
                        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                    }
                }
            }
            break;
        /* Tab navigation buttons */
        case IDC_TAB_PREV:
            DebugLog("[TAB] Prev button clicked\n");
            if (g_tabScrollIndex > 0) {
                g_tabScrollIndex--;
                EnsureTabVisible(g_tabScrollIndex);
            }
            break;
        case IDC_TAB_NEXT:
            DebugLog("[TAB] Next button clicked\n");
            if (g_tabScrollIndex < g_tabCount - 1) {
                g_tabScrollIndex++;
                EnsureTabVisible(g_tabScrollIndex);
            }
            break;
            
        /* Edit menu */
        case IDM_EDIT_UNDO:
            DebugLog("[MENU] EditUndoMenuItemClick\n");
            SendMessage(hwndInput, EM_UNDO, 0, 0);
            break;
        case IDM_EDIT_REDO:
            DebugLog("[MENU] EditRedoMenuItemClick\n");
            SendMessage(hwndInput, EM_UNDO, 1, 0);
            break;
        case IDM_EDIT_CUT:
            DebugLog("[MENU] EditCutMenuItemClick\n");
            SendMessage(hwndInput, WM_CUT, 0, 0);
            break;
        case IDM_EDIT_COPY:
            DebugLog("[MENU] EditCopyMenuItemClick\n");
            SendMessage(hwndInput, WM_COPY, 0, 0);
            break;
        case IDM_EDIT_PASTE:
            DebugLog("[MENU] EditPasteMenuItemClick\n");
            SendMessage(hwndInput, WM_PASTE, 0, 0);
            break;
        case IDM_EDIT_SELECTALL:
            DebugLog("[MENU] EditSelectAllMenuItemClick\n");
            SendMessage(hwndInput, EM_SETSEL, 0, -1);
            break;
            
        /* Build menu */
        case IDM_BUILD_COMPILE:
            DebugLog("[MENU] BuildCompileMenuItemClick\n");
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
            DebugLog("[MENU] BuildRunMenuItemClick\n");
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
            DebugLog("[MENU] ProjectSettingsMenuItemClick\n");
            ShowProjectSettings(hwnd);
            break;
            
        /* Code insertion toolbar */
        case IDT_INSERT_FUNC:
            DebugLog("[TOOLBAR] Insert Function button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_IF:
            DebugLog("[TOOLBAR] Insert If statement button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_FOR:
            DebugLog("[TOOLBAR] Insert For loop button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_WHILE:
            DebugLog("[TOOLBAR] Insert While loop button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_SWITCH:
            DebugLog("[TOOLBAR] Insert Switch statement button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_STRUCT:
            DebugLog("[TOOLBAR] Insert Struct button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_UNION:
            DebugLog("[TOOLBAR] Insert Union button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_ENUM:
            DebugLog("[TOOLBAR] Insert Enum button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_TYPEDEF:
            DebugLog("[TOOLBAR] Insert Typedef button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_INCLUDE:
            DebugLog("[TOOLBAR] Insert Include button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        case IDT_INSERT_DEFINE:
            DebugLog("[TOOLBAR] Insert Define button clicked\n");
            InsertCodeTemplate(LOWORD(wParam));
            break;
        default:
            DebugLog("[COMMAND] Unknown command ID: 0x%X (wParam=0x%X, lParam=0x%X)\n", LOWORD(wParam), wParam, lParam);
            break;
        }
        break;
        
    case WM_NOTIFY:
        /* Handle TreeView single-click to open file */
        if (wParam == IDC_PROJECT_TREE) {
            LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)lParam;
            /* Skip paint and internal notifications - keep only user interactions */
            if ((int)pnmtv->hdr.code >= 0 || pnmtv->hdr.code == TVN_SELCHANGED) {
                DebugLog("[TREEVIEW] NM code: 0x%X\n", pnmtv->hdr.code);
            }
            if (pnmtv->hdr.code == TVN_SELCHANGED) {
                DebugLog("[TREEVIEW] TVN_SELCHANGED - selection changed\n");
                HTREEITEM hItem = TreeView_GetSelection(hwndProjectTree);
                if (hItem) {
                    TVITEM tvi;
                    char buffer[MAX_PATH];
                    tvi.mask = TVIF_TEXT | TVIF_HANDLE;
                    tvi.hItem = hItem;
                    tvi.pszText = buffer;
                    tvi.cchTextMax = MAX_PATH;
                    TreeView_GetItem(hwndProjectTree, &tvi);
                    DebugLog("[TREEVIEW] Selected: '%s'\n", buffer);
                    
                    /* Ignore the root "Project Files" folder */
                    if (strcmp(buffer, "Project Files") == 0) {
                        DebugLog("[TREEVIEW] Root folder selected, skipping\n");
                    } else {
                        DebugLog("[TREEVIEW] File selected, searching in %d files...\n", g_openedFileCount);
                        /* Find the full path from our opened files */
                        BOOL found = FALSE;
                        for (int i = 0; i < g_openedFileCount; i++) {
                            char* filename = strrchr(g_openedFiles[i], '\\');
                            if (filename) {
                                filename++;
                                if (strcmp(filename, buffer) == 0) {
                                    DebugLog("[TREEVIEW] FOUND: %s\n", g_openedFiles[i]);
                                    LoadFileIntoEditor(g_openedFiles[i]);
                                    found = TRUE;
                                    break;
                                }
                            }
                        }
                        if (!found) {
                            DebugLog("[TREEVIEW] File not found in g_openedFiles\n");
                        }
                    }
                }
            } else {
                DebugLog("[TREEVIEW] Unknown NM code: 0x%X\n", pnmtv->hdr.code);
            }
        }
        /* Handle tab selection changes and right-clicks */
        else if (wParam == IDC_CODE_TAB) {
            LPNMHDR pnmh = (LPNMHDR)lParam;
            if (pnmh->code == TCN_SELCHANGE) {
                if (g_ignoreTabSelectionChange) break;
                DebugLog("[TAB] TCN_SELCHANGE\n");
                int newTab = TabCtrl_GetCurSel(hwndCodeTab);
                DebugLog("[TAB] Selected tab: %d\n", newTab);
                if (newTab >= 0 && newTab < g_tabCount) {
                    g_activeTab = newTab;
                    EnsureTabVisible(newTab);
                    /* Load the file for this tab */
                    if (g_tabs[newTab].filePath[0]) {
                        DebugLog("[TAB] TabClick(%s)\n", g_tabs[newTab].title);
                        LoadFileIntoEditor(g_tabs[newTab].filePath);
                    }
                    /* Update close button position */
                    PositionTabCloseButton();
                }
            } else if (pnmh->code == TCN_RCLICK) {
                DebugLog("[TAB] TCN_RCLICK\n");
                POINT pt;
                GetCursorPos(&pt);
                POINT hitPt = pt;
                ScreenToClient(hwndCodeTab, &hitPt);
                TCHITTESTINFO tchi = {0};
                tchi.pt = hitPt;
                int tabIdx = TabCtrl_HitTest(hwndCodeTab, &tchi);
                if (tabIdx >= 0 && tabIdx < g_tabCount) {
                    DebugLog("[TAB] Right-clicked tab %d: %s\n", tabIdx, g_tabs[tabIdx].title);
                    g_rightClickedTab = tabIdx;
                    HMENU hMenu = CreatePopupMenu();
                    AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_SINGLE, "Close");
                    AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_OTHERS, "Close Others");
                    int cmd = TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x, pt.y, 0, hwndCodeTab, NULL);
                    DestroyMenu(hMenu);
                    if (cmd == IDM_TAB_CLOSE_SINGLE) {
                        int result = PromptSaveTab(g_rightClickedTab);
                        if (result != IDCANCEL) {
                            CloseTab(g_rightClickedTab);
                            RefreshTabControl();
                            if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                                LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                            } else {
                                SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                            }
                        }
                    } else if (cmd == IDM_TAB_CLOSE_OTHERS) {
                        for (int i = g_tabCount - 1; i >= 0; i--) {
                            if (i == g_rightClickedTab) continue;
                            int result = PromptSaveTab(i);
                            if (result != IDCANCEL) {
                                CloseTab(i);
                            }
                        }
                        RefreshTabControl();
                        if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                            LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                        } else {
                            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                        }
                    } else if (cmd == IDM_TAB_CLOSE_RIGHT) {
                        for (int i = g_tabCount - 1; i > g_rightClickedTab; i--) {
                            int result = PromptSaveTab(i);
                            if (result != IDCANCEL) {
                                CloseTab(i);
                            }
                        }
                        RefreshTabControl();
                        if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                            LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                        } else {
                            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                        }
                    }
                    g_rightClickedTab = -1;
                }
            }
        }
        break;
        
    case WM_KEYDOWN:
        DebugLog("[KEYBOARD] Key pressed: 0x%X (repeat=%d)\n", wParam, LOWORD(lParam));
        /* Handle Ctrl+A for select all in code pane */
        if (wParam == 0x41 && (GetKeyState(VK_CONTROL) & 0x8000)) {
            /* Ctrl+A - select all text in input pane */
            if (GetFocus() == hwndInput) {
                SendMessage(hwndInput, EM_SETSEL, 0, -1);
                return 0;
            }
        }
        break;
        
    case WM_SETCURSOR: {
        if (LOWORD(lParam) == HTCLIENT) {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc;
            GetClientRect(hwnd, &rc);
            int codeLeft = 220 + g_lineNumberWidth;
            int availableCodeWidth = rc.right - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
            if (availableCodeWidth < 240) availableCodeWidth = 240;
            int inputWidth = availableCodeWidth / 2;
            int splitterX = codeLeft + inputWidth;
            RECT splitterRect = { splitterX, 90, splitterX + g_splitterWidth, rc.bottom - 150 };
            if (PtInRect(&splitterRect, pt)) {
                SetCursor(LoadCursor(NULL, IDC_SIZEWE));
                return TRUE;
            }
        }
        break;
    }
    case WM_LBUTTONDOWN: {
        int x = (int)(short)LOWORD(lParam);
        int y = (int)(short)HIWORD(lParam);
        RECT rc;
        GetClientRect(hwnd, &rc);
        int codeLeft = 220 + g_lineNumberWidth;
        int availableCodeWidth = rc.right - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
        if (availableCodeWidth < 240) availableCodeWidth = 240;
        int inputWidth = (g_currentInputWidth > 0) ? g_currentInputWidth : (availableCodeWidth * 85 / 100);
        int splitterX = codeLeft + inputWidth;
        RECT splitterRect = { splitterX - 5, 115, splitterX + g_splitterWidth + 5, rc.bottom - 150 };
        if (x >= splitterRect.left && x < splitterRect.right && y >= splitterRect.top && y < splitterRect.bottom) {
            g_isDraggingSplitter = TRUE;
            g_splitterDragStartX = x;
            g_dragInitialInputWidth = inputWidth;
            g_splitterStartPropertiesWidth = g_propertiesWidth;
            SetCapture(hwnd);
            SetCursor(LoadCursor(NULL, IDC_SIZEWE));
            return 0;
        }
        DebugLog("[MOUSE] Left button DOWN at (%d, %d)\n", x, y);
        break;
    }
    case WM_LBUTTONUP:
        if (g_isDraggingSplitter) {
            g_isDraggingSplitter = FALSE;
            ReleaseCapture();
            return 0;
        }
        DebugLog("[MOUSE] Left button UP at (%d, %d)\n", (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam));
        break;
    case WM_MOUSEMOVE: {
        int x = (int)(short)LOWORD(lParam);
        int y = (int)(short)HIWORD(lParam);
        RECT rc;
        GetClientRect(hwnd, &rc);
        int codeLeft = 220 + g_lineNumberWidth;
        
        if (g_isDraggingSplitter) {
            int dx = x - g_splitterDragStartX;
            int newInputWidth = g_dragInitialInputWidth + dx;
            int minWidth = 150;
            int maxWidth = rc.right - codeLeft - 100 - g_propertiesWidth;
            if (newInputWidth < minWidth) newInputWidth = minWidth;
            if (newInputWidth > maxWidth) newInputWidth = maxWidth;
            
            g_currentInputWidth = newInputWidth;
            
            int newSplitterX = codeLeft + newInputWidth;
            int outputX = newSplitterX + g_splitterWidth + 5;
            int outputWidth = rc.right - outputX - g_propertiesWidth - 10;
            if (outputWidth < 100) outputWidth = 100;
            
            MoveWindow(hwndCodeTab, codeLeft, 90, newInputWidth, 25, TRUE);
            if (hwndTabPrev) MoveWindow(hwndTabPrev, codeLeft + newInputWidth - 50, 88, 22, 22, TRUE);
            if (hwndTabNext) MoveWindow(hwndTabNext, codeLeft + newInputWidth - 26, 88, 22, 22, TRUE);
            MoveWindow(hwndInput, codeLeft, 115, newInputWidth, rc.bottom - 165, TRUE);
            MoveWindow(hwndCodeSplitter, newSplitterX, 90, g_splitterWidth, rc.bottom - 150, TRUE);
            MoveWindow(hwndOutput, outputX, 90, outputWidth, rc.bottom - 150, TRUE);
            UpdateLineNumbers(hwndInput, hwndLineNumbers);
            return 0;
        }
        {
            int availableCodeWidth = rc.right - codeLeft - g_propertiesWidth - g_splitterWidth - 10;
            if (availableCodeWidth < 240) availableCodeWidth = 240;
            int inputWidth = (g_currentInputWidth > 0) ? g_currentInputWidth : (availableCodeWidth * 85 / 100);
            int splitterX = codeLeft + inputWidth;
            RECT splitterRect = { splitterX - 5, 115, splitterX + g_splitterWidth + 5, rc.bottom - 150 };
            POINT pt = { x, y };
            if (PtInRect(&splitterRect, pt)) {
                SetCursor(LoadCursor(NULL, IDC_SIZEWE));
                return 0;
            }
        }
        break;
    }
    case WM_CTLCOLORSTATIC: {
        if ((HWND)lParam == hwndCodeSplitter) {
            HDC hdc = (HDC)wParam;
            SetBkMode(hdc, OPAQUE);
            SetBkColor(hdc, RGB(140, 140, 140));
            return (LRESULT)CreateSolidBrush(RGB(140, 140, 140));
        }
        break;
    }
case WM_CONTEXTMENU: {
        HWND hWndCtrl = (HWND)wParam;
        if (hWndCtrl == hwndCodeTab) {
            POINT pt;
            if ((int)LOWORD(lParam) == -1 && (int)HIWORD(lParam) == -1) {
                GetCursorPos(&pt);
            } else {
                pt.x = (int)LOWORD(lParam);
                pt.y = (int)HIWORD(lParam);
            }
            POINT hitPt = pt;
            ScreenToClient(hwndCodeTab, &hitPt);
            TCHITTESTINFO tchi = {0};
            tchi.pt = hitPt;
            int tabIdx = TabCtrl_HitTest(hwndCodeTab, &tchi);
            if (tabIdx >= 0 && tabIdx < g_tabCount) {
                DebugLog("[TAB] Context menu on tab %d: %s\n", tabIdx, g_tabs[tabIdx].title);
                g_rightClickedTab = tabIdx;
                HMENU hMenu = CreatePopupMenu();
                AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_SINGLE, "Close");
                AppendMenu(hMenu, MF_STRING, IDM_TAB_CLOSE_OTHERS, "Close Others");
                int cmd = TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x, pt.y, 0, hwndCodeTab, NULL);
                DestroyMenu(hMenu);
                if (cmd == IDM_TAB_CLOSE_SINGLE) {
                    int result = PromptSaveTab(g_rightClickedTab);
                    if (result != IDCANCEL) {
                        CloseTab(g_rightClickedTab);
                        RefreshTabControl();
                        if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                            LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                        } else {
                            SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                        }
                    }
                } else if (cmd == IDM_TAB_CLOSE_OTHERS) {
                    for (int i = g_tabCount - 1; i >= 0; i--) {
                        if (i == g_rightClickedTab) continue;
                        int result = PromptSaveTab(i);
                        if (result != IDCANCEL) {
                            CloseTab(i);
                        }
                    }
                    RefreshTabControl();
                    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                        LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                    } else {
                        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                    }
                } else if (cmd == IDM_TAB_CLOSE_RIGHT) {
                    for (int i = g_tabCount - 1; i > g_rightClickedTab; i--) {
                        int result = PromptSaveTab(i);
                        if (result != IDCANCEL) {
                            CloseTab(i);
                        }
                    }
                    RefreshTabControl();
                    if (g_activeTab >= 0 && g_activeTab < g_tabCount) {
                        LoadFileIntoEditor(g_tabs[g_activeTab].filePath);
                    } else {
                        SendMessage(hwndInput, WM_SETTEXT, 0, (LPARAM)"");
                    }
                }
                g_rightClickedTab = -1;
            }
            return 0;
        }
        break;
    }
        
    case WM_CLOSE:
        DebugLog("[MSG] WM_CLOSE - Window close requested\n");
        /* Prompt to save all modified tabs before closing */
        if (PromptSaveAllTabs() == IDCANCEL) {
            DebugLog("[EVENT] Close cancelled by user\n");
            return 0;
        }
        DebugLog("[EVENT] Window closing\n");
        DestroyWindow(hwnd);
        break;
        
    case WM_DESTROY:
        SaveConfig();
        PostQuitMessage(0);
        break;
        
    default:
        /* Log unhandled messages occasionally */
        if (msg == WM_COMMAND || msg == WM_NOTIFY) {
            DebugLog("[UNHANDLED] msg=0x%X, wParam=0x%X, lParam=0x%X\n", msg, wParam, lParam);
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
