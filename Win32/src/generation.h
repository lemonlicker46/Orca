#ifndef GENERATION_H
#define GENERATION_H

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

void CreateMainToolbar(HWND hwnd);
void CreateCodeToolbar(HWND hwnd);
void InsertCodeTemplate(HWND hwndEdit, int templateId);
void ShowManipulationToolbar(BOOL show);

#endif /* GENERATION_H */
