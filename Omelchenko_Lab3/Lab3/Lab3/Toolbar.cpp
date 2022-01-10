#pragma comment(lib, "comctl32.lib")

#include "framework.h"
#include <CommCtrl.h>

#include "tb_definition.h"
#include "Toolbar.h"

void Toolbar::OnCreate(HWND hWnd)
{
    InitCommonControls();

    TBBUTTON tbb[4];
    HIMAGELIST imageList;
    HBITMAP tbBitmap = (HBITMAP)LoadImage(NULL, TEXT("Bitmap.bmp"), IMAGE_BITMAP, 120, 30, LR_LOADFROMFILE);

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
    tbb[0].idCommand = ID_TOOL_POINT;

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;

    SendMessage(hwndToolBar, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
};

void Toolbar::OnSize()
{
    SendMessage(hwndToolBar, TB_AUTOSIZE, 0, 0);
}

void Toolbar::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_POINT:
            lstrcpy(lpttt->szText, L"Крапка");
            break;
        case ID_TOOL_LINE:
            lstrcpy(lpttt->szText, L"Лінія");
            break;
        case ID_TOOL_RECT:
            lstrcpy(lpttt->szText, L"Прямокутник");
            break;
        case ID_TOOL_ELLIPSE:
            lstrcpy(lpttt->szText, L"Еліпс");
            break;
        default: lstrcpy(lpttt->szText, L"Невідомо");
        }
    }
}

void Toolbar::PickToolPoint()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, PRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, UNPRESSED);
}

void Toolbar::PickToolLine()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, PRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, UNPRESSED);
}

void Toolbar::PickToolRect()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, PRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, UNPRESSED);
}

void Toolbar::PickToolEllipse()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, PRESSED);    
}

void Toolbar::UnpressAll()
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, UNPRESSED);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, UNPRESSED);
}