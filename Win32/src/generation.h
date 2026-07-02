#ifndef GENERATION_H
#define GENERATION_H

#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif

#include <windows.h>
#include <commctrl.h>

#define IDC_TOOLBAR_MAIN   1003
#define IDC_TOOLBAR_CODE   1004

#define IDM_FILE_NEW       1101
#define IDM_FILE_OPEN      1102
#define IDM_FILE_SAVE      1103
#define IDM_EDIT_UNDO      1201
#define IDM_EDIT_REDO      1202
#define IDM_PROJECT_SETTINGS 1302

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

#define IDT_INSERT_TYPE_C    2021
#define IDT_INSERT_TYPE_sC   2022
#define IDT_INSERT_TYPE_uC   2023
#define IDT_INSERT_TYPE_S    2024
#define IDT_INSERT_TYPE_Si   2025
#define IDT_INSERT_TYPE_sS   2026
#define IDT_INSERT_TYPE_sSi  2027
#define IDT_INSERT_TYPE_uS   2028
#define IDT_INSERT_TYPE_uSi  2029
#define IDT_INSERT_TYPE_I    2030
#define IDT_INSERT_TYPE_sI   2031
#define IDT_INSERT_TYPE_uI   2032
#define IDT_INSERT_TYPE_L    2033
#define IDT_INSERT_TYPE_LI   2034
#define IDT_INSERT_TYPE_sL   2035
#define IDT_INSERT_TYPE_sLI  2036
#define IDT_INSERT_TYPE_uL   2037
#define IDT_INSERT_TYPE_uLI  2038
#define IDT_INSERT_TYPE_LL   2039
#define IDT_INSERT_TYPE_LLI  2040
#define IDT_INSERT_TYPE_sLL  2041
#define IDT_INSERT_TYPE_sLLI 2042
#define IDT_INSERT_TYPE_uLL  2043
#define IDT_INSERT_TYPE_uLLI 2044

void CreateMainToolbar(HWND hwnd);
void CreateCodeToolbar(HWND hwnd);
void InsertCodeTemplate(HWND hwndEdit, int templateId);
void InsertTextAtCursor(HWND hwndEdit, const char* text);
const char* GetTypeInsertString(int cmdId);
void ResizeTypeToolbar(HWND hwndToolbar, int width);
void ShowManipulationToolbar(BOOL show);

#endif /* GENERATION_H */
