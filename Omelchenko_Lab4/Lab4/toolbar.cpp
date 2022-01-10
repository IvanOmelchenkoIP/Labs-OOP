#pragma comment(lib, "comctl32.lib")

#include "framework.h"
#include <CommCtrl.h>

#include "tbb_definition.h"
#include "toolbar.h"

void Toolbar::OnCreate(HWND hWnd)
{
    InitCommonControls();

    TBBUTTON tbb[TB_TOOL_NUM];
    HIMAGELIST imageList;
    HBITMAP tbBitmap = (HBITMAP)LoadImage(NULL, TEXT("Bitmap.bmp"), IMAGE_BITMAP, 180, 30, LR_LOADFROMFILE);

    hwndToolBar = CreateWindow(TOOLBARCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        0, 0, 0, 0, hWnd, (HMENU)IDC_TOOLBAR, NULL, 0);

    SendMessage(hwndToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    SendMessage(hwndToolBar, TB_SETBITMAPSIZE, (WPARAM)0, (LPARAM)MAKELONG(30, 30));

    imageList = ImageList_Create(30, 30, ILC_COLOR8 | ILC_MASK, 4, 0);
    ImageList_Add(imageList, tbBitmap, NULL);

    SendMessage(hwndToolBar, TB_SETIMAGELIST, 0, (LPARAM)imageList);

    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_TB_POINT;

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TB_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TB_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TB_ELLIPSE;

    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_BUTTON;
    tbb[4].idCommand = ID_TB_CUBE;

    tbb[5].iBitmap = 5;
    tbb[5].fsState = TBSTATE_ENABLED;
    tbb[5].fsStyle = TBSTYLE_BUTTON;
    tbb[5].idCommand = ID_TB_ELLIPSELINE;

    SendMessage(hwndToolBar, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
};

void Toolbar::OnSize()
{
    SendMessage(hwndToolBar, TB_AUTOSIZE, 0, 0);
}

void Toolbar::OnNotify(LPARAM lParam)
{
    LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
    if (lpttt->hdr.code == TTN_NEEDTEXT) 
    {
        lpttt->hinst = GetModuleHandle(NULL);
        lpttt->lpszText = MAKEINTRESOURCE(lpttt->hdr.idFrom);
    }
}

void Toolbar::PickTool(WPARAM tbToolID)
{
    UnpressAll();
    SendMessage(hwndToolBar, TB_PRESSBUTTON, tbToolID, PRESSED);
}

void Toolbar::UnpressAll()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TB_POINT,       UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TB_LINE,        UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TB_RECT,        UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TB_ELLIPSE,     UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TB_CUBE,        UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TB_ELLIPSELINE, UNPRESSED);
}