#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <commctrl.h>
#include <string.h>

/* Control IDs reused from main.c */
#define IDC_TOOLBAR_MAIN   1003
#define IDC_TOOLBAR_CODE   1004

/* Menu and toolbar command IDs used by the top toolbar */
#define IDM_FILE_NEW       1101
#define IDM_FILE_OPEN      1102
#define IDM_FILE_SAVE      1103
#define IDM_EDIT_UNDO      1201
#define IDM_EDIT_REDO      1202
#define IDM_PROJECT_SETTINGS 1302

/* Code insertion toolbar button IDs */
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

static HWND hwndToolbarMain = NULL;
static HWND hwndToolbarCode = NULL;

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

    TBBUTTON codeTbb[11];
    memset(codeTbb, 0, sizeof(codeTbb));
    int cmdIds[] = {IDT_INSERT_FUNC, IDT_INSERT_IF, IDT_INSERT_FOR, IDT_INSERT_WHILE, IDT_INSERT_SWITCH,
                    IDT_INSERT_STRUCT, IDT_INSERT_UNION, IDT_INSERT_ENUM, IDT_INSERT_TYPEDEF, IDT_INSERT_INCLUDE, IDT_INSERT_DEFINE};
    for (int i = 0; i < 11; i++) {
        codeTbb[i].iBitmap = 0;
        codeTbb[i].idCommand = cmdIds[i];
        codeTbb[i].fsState = TBSTATE_ENABLED;
        codeTbb[i].fsStyle = BTNS_BUTTON;
        codeTbb[i].iString = -1;
    }

    SendMessage(hwndToolbarCode, TB_ADDBUTTONS, 11, (LPARAM)codeTbb);
    SendMessage(hwndToolbarCode, TB_AUTOSIZE, 0, 0);
    ShowWindow(hwndToolbarCode, SW_HIDE);
}

void InsertCodeTemplate(HWND hwndEdit, int templateId) {
    int index = templateId - IDT_INSERT_FUNC;
    int templateCount = sizeof(codeTemplates) / sizeof(codeTemplates[0]);
    if (index >= 0 && index < templateCount) {
        SendMessage(hwndEdit, EM_REPLACESEL, TRUE, (LPARAM)codeTemplates[index]);
        SetFocus(hwndEdit);
    }
}

void ShowManipulationToolbar(BOOL show) {
    if (!hwndToolbarCode) {
        return;
    }

    ShowWindow(hwndToolbarCode, show ? SW_SHOW : SW_HIDE);
}
