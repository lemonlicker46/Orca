#define _WIN32_WINNT 0x0501
#define _WIN32_IE 0x0501

#include "generation.h"
#include <windowsx.h>
#include <stdio.h>
#include <string.h>

static HWND hwndToolbarMain = NULL;
static HWND hwndToolbarCode = NULL;
static HWND hwndTypeTooltip = NULL;
static HWND g_hwndTypeButtons[32] = {0};

typedef struct {
    int id;
    const char* label;
    const char* insertText;
    char* tooltip;
} TypeButtonInfo;

static const TypeButtonInfo g_typeButtons[] = {
    {IDT_INSERT_TYPE_C,   "C",   "char",                    "char"},
    {IDT_INSERT_TYPE_sC,  "sC",  "signed char",             "signed char"},
    {IDT_INSERT_TYPE_uC,  "uC",  "unsigned char",           "unsigned char"},
    {IDT_INSERT_TYPE_S,   "S",   "short",                   "short"},
    {IDT_INSERT_TYPE_Si,  "Si",  "short int",               "short int"},
    {IDT_INSERT_TYPE_sS,  "sS",  "signed short",            "signed short"},
    {IDT_INSERT_TYPE_sSi, "sSi", "signed short int",        "signed short int"},
    {IDT_INSERT_TYPE_uS,  "uS",  "unsigned short",          "unsigned short"},
    {IDT_INSERT_TYPE_uSi, "uSi", "unsigned short int",      "unsigned short int"},
    {IDT_INSERT_TYPE_I,   "I",   "int",                     "int"},
    {IDT_INSERT_TYPE_sI,  "sI",  "signed int",              "signed int"},
    {IDT_INSERT_TYPE_uI,  "uI",  "unsigned int",            "unsigned int"},
    {IDT_INSERT_TYPE_L,   "L",   "long",                    "long"},
    {IDT_INSERT_TYPE_LI,  "LI",  "long int",                "long int"},
    {IDT_INSERT_TYPE_sL,  "sL",  "signed long",             "signed long"},
    {IDT_INSERT_TYPE_sLI, "sLI", "signed long int",         "signed long int"},
    {IDT_INSERT_TYPE_uL,  "uL",  "unsigned long",           "unsigned long"},
    {IDT_INSERT_TYPE_uLI, "uLI", "unsigned long int",       "unsigned long int"},
    {IDT_INSERT_TYPE_LL,  "LL",  "long long",               "long long"},
    {IDT_INSERT_TYPE_LLI, "LLI", "long long int",           "long long int"},
    {IDT_INSERT_TYPE_sLL, "sLL", "signed long long",        "signed long long"},
    {IDT_INSERT_TYPE_sLLI,"sLLI","signed long long int",    "signed long long int"},
    {IDT_INSERT_TYPE_uLL, "uLL", "unsigned long long",      "unsigned long long"},
    {IDT_INSERT_TYPE_uLLI,"uLLI","unsigned long long int",  "unsigned long long int"},
};

static const int g_typeButtonCount = sizeof(g_typeButtons) / sizeof(g_typeButtons[0]);

const char* GetTypeInsertString(int cmdId);
static void CreateTypeToolbarButtons(HWND hwndParent);
static void CreateTypeToolbarTooltip(HWND hwndParent);
static void UpdateTypeToolbarLayout(HWND hwndParent, int width);

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
    /* Old main-toolbar buttons removed per user request; toolbar remains as an empty container. */
    SendMessage(hwndToolbarMain, TB_AUTOSIZE, 0, 0);
}

const char* GetTypeInsertString(int cmdId) {
    for (int i = 0; i < g_typeButtonCount; i++) {
        if (g_typeButtons[i].id == cmdId) {
            return g_typeButtons[i].insertText;
        }
    }
    return NULL;
}

static void CreateTypeToolbarButtons(HWND hwndParent) {
    HDC hdc = GetDC(hwndParent);
    HFONT font = (HFONT)SendMessage(hwndParent, WM_GETFONT, 0, 0);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    int x = 4;
    int y = 4;
    SIZE textSize = {0};
    const int buttonHeight = 24;
    const int buttonSpacing = 4;

    for (int i = 0; i < g_typeButtonCount; i++) {
        const TypeButtonInfo* info = &g_typeButtons[i];
        GetTextExtentPoint32A(hdc, info->label, (int)strlen(info->label), &textSize);
        int width = textSize.cx + 16;
        if (width < 28) width = 28;

        g_hwndTypeButtons[i] = CreateWindowExA(0, "BUTTON", info->label,
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            x, y, width, buttonHeight,
            hwndParent, (HMENU)info->id, GetModuleHandle(NULL), NULL);
        SendMessageA(g_hwndTypeButtons[i], WM_SETFONT, (WPARAM)font, FALSE);

        x += width + buttonSpacing;
    }

    SelectObject(hdc, oldFont);
    ReleaseDC(hwndParent, hdc);
    CreateTypeToolbarTooltip(hwndParent);
}

static void CreateTypeToolbarTooltip(HWND hwndParent) {
    hwndTypeTooltip = CreateWindowEx(0, TOOLTIPS_CLASS, NULL,
        WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        hwndParent, NULL, GetModuleHandle(NULL), NULL);
    if (!hwndTypeTooltip) {
        return;
    }

    TOOLINFOA ti;
    ZeroMemory(&ti, sizeof(ti));
    ti.cbSize = sizeof(ti);
    ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
    ti.hwnd = hwndParent;

    for (int i = 0; i < g_typeButtonCount; i++) {
        ti.uId = (UINT_PTR)g_hwndTypeButtons[i];
        ti.lpszText = (LPSTR)(ULONG_PTR)g_typeButtons[i].tooltip;
        SendMessageA(hwndTypeTooltip, TTM_ADDTOOL, 0, (LPARAM)&ti);
    }
}

static void UpdateTypeToolbarLayout(HWND hwndParent, int width) {
    if (!hwndParent) {
        return;
    }

    if (width <= 0) {
        RECT rc;
        GetClientRect(hwndParent, &rc);
        width = rc.right - rc.left;
    }

    HDC hdc = GetDC(hwndParent);
    HFONT font = (HFONT)SendMessage(hwndParent, WM_GETFONT, 0, 0);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    const int buttonHeight = 24;
    const int buttonSpacing = 4;
    int x = 4;
    int y = 4;
    SIZE textSize = {0};
    int rowHeight = buttonHeight;

    for (int i = 0; i < g_typeButtonCount; i++) {
        const TypeButtonInfo* info = &g_typeButtons[i];
        GetTextExtentPoint32A(hdc, info->label, (int)strlen(info->label), &textSize);
        int buttonWidth = textSize.cx + 16;
        if (buttonWidth < 28) buttonWidth = 28;

        if (x + buttonWidth + buttonSpacing > width) {
            x = 4;
            y += rowHeight + buttonSpacing;
        }

        MoveWindow(g_hwndTypeButtons[i], x, y, buttonWidth, buttonHeight, TRUE);
        x += buttonWidth + buttonSpacing;
    }

    SelectObject(hdc, oldFont);
    ReleaseDC(hwndParent, hdc);

    int totalHeight = y + rowHeight + buttonSpacing;
    MoveWindow(hwndParent, 0, 40, width, totalHeight, TRUE);
}

void CreateCodeToolbar(HWND hwnd) {
    hwndToolbarCode = CreateWindowEx(0, "STATIC", NULL,
        WS_CHILD | WS_VISIBLE,
        0, 40, 0, 32, hwnd, (HMENU)IDC_TOOLBAR_CODE, GetModuleHandle(NULL), NULL);

    SendMessage(hwndToolbarCode, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE);
    CreateTypeToolbarButtons(hwndToolbarCode);
    UpdateTypeToolbarLayout(hwndToolbarCode, 0);
}

void InsertCodeTemplate(HWND hwndEdit, int templateId) {
    int index = templateId - IDT_INSERT_FUNC;
    int templateCount = sizeof(codeTemplates) / sizeof(codeTemplates[0]);
    if (index >= 0 && index < templateCount) {
        SendMessage(hwndEdit, EM_REPLACESEL, TRUE, (LPARAM)codeTemplates[index]);
        SetFocus(hwndEdit);
    }
}

void InsertTextAtCursor(HWND hwndEdit, const char* text) {
    if (!hwndEdit || !text) {
        return;
    }
    SendMessage(hwndEdit, EM_REPLACESEL, TRUE, (LPARAM)text);
    SetFocus(hwndEdit);
}

void ResizeTypeToolbar(HWND hwndToolbar, int width) {
    UpdateTypeToolbarLayout(hwndToolbar, width);
}

void ShowManipulationToolbar(BOOL show) {
    if (!hwndToolbarCode) {
        return;
    }

    ShowWindow(hwndToolbarCode, show ? SW_SHOW : SW_HIDE);
}
