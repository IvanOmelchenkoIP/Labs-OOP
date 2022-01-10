#include "framework.h"

#include <string>
#include <tchar.h>

#include "resource3.h"
#include "work2.h"

#ifndef UNICODE
#define UNICODE
#endif

#define BUF_SIZE 8
#define LST_SIZE 112

extern LRESULT cursorIdx;
extern TCHAR choice[BUF_SIZE];

static const std::wstring groups[LST_SIZE] = { L"²Ï-11", L"²Ï-12", L"²Ï-13", L"²Ï-14", L"²Ï-15", L"²Ï-ç11",
                                               L"²Ï-01", L"²Ï-02", L"²Ï-03", L"²Ï-04", L"²Ï-05", L"²Ï-ç01",
                                               L"²Ï-91", L"²Ï-92", L"²Ï-93", L"²Ï-94", L"²Ï-95", L"²Ï-96", L"²Ï-ç91",
                                               L"²Ï-81", L"²Ï-82", L"²Ï-83", L"²Ï-84", L"²Ï-ç81", L"²Ï-ç82",
                                               L"²Ò-01", L"²Ò-02", L"²Ò-03", L"²Ò-04",
                                               L"²Ò-91", L"²Ò-92", L"²Ò-93", L"²Ò-94", L"²Ò-ç91",
                                               L"²Ò-81", L"²Ò-82", L"²Ò-83", L"²Ò-84", L"²Ò-ç81",
                                               L"²Ñ-11", L"²Ñ-12", L"²Ñ-13", L"²Ñ-ç11",
                                               L"²Ñ-01", L"²Ñ-02", L"²Ñ-03", L"²Ñ-ç01",
                                               L"²Ñ-91", L"²Ñ-92", L"²Ñ-93", L"²Ñ-ç91",
                                               L"²Ñ-81", L"²Ñ-82", L"²Ñ-83",
                                               L"²Î-11", L"²Î-12", L"²Î-13", L"²Î-14", L"²Î-15", L"²Î-16", L"²Î-ç11",
                                               L"²Î-01", L"²Î-02", L"²Î-03", L"²Î-04", L"²Î-05", L"²Î-06", L"²Î-ç01",
                                               L"²Î-91", L"²Î-92", L"²Î-93", L"²Î-ç91",
                                               L"²Î-81", L"²Î-82", L"²Î-83", L"²Î-ç82",
                                               L"²Â-91", L"²Â-92", L"²Â-93",
                                               L"²Â-81", L"²Â-82", L"²Â-83",
                                               L"²À-11", L"²À-12", L"²À-13", L"²À-14", L"²À-ç11",
                                               L"²À-01", L"²À-02", L"²À-03", L"²À-04", L"²À-ç01",
                                               L"²À-91", L"²À-92", L"²À-93", L"²À-94", L"²À-ç91",
                                               L"²À-81", L"²À-82", L"²À-83",
                                               L"²Ê-11", L"²Ê-12", L"²Ê-13",
                                               L"²Ê-01", L"²Ê-02", L"²Ê-03",
                                               L"²Ê-91", L"²Ê-92", L"²Ê-93",
                                               L"²Ê-81", L"²Ê-82", L"²Ê-83" };

static void FillList(HWND hDlg);
static INT CALLBACK DialogWork2(HWND, UINT, WPARAM, LPARAM);

int Work2(HINSTANCE hInst, HWND hWnd) {
    return DialogBoxW(hInst, MAKEINTRESOURCE(IDD_WORK2), hWnd, (DLGPROC)DialogWork2);
}

INT CALLBACK DialogWork2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        FillList(hDlg);
        return (INT)TRUE;
    case WM_COMMAND:
        int command = LOWORD(wParam);

        switch (command)
        {
        case IDOK:
            cursorIdx = SendDlgItemMessageW(hDlg, ID_LISTWORK2, LB_GETCURSEL, 0, 0);
            if (cursorIdx != LB_ERR)
                SendDlgItemMessageW(hDlg, ID_LISTWORK2, LB_GETTEXT, cursorIdx, (LPARAM)choice);
            
            EndDialog(hDlg, 1);
            break;
        case IDCANCEL:
            cursorIdx = LB_ERR;
            EndDialog(hDlg, 0);
            break;
        }

        break;
    }

    return (INT)FALSE;
}

void FillList(HWND hDlg)
{
    for (size_t i = 0; i < LST_SIZE; i++)
    {
        SendDlgItemMessageW(hDlg, ID_LISTWORK2, LB_ADDSTRING, 0, (LPARAM)groups[i].c_str());
    }
}

/*void PaintWork2(HDC hdc) 
{
    TextOutW(hdc, 10, 40, _T("Âèáðàíà ãðóïà Ô²ÎÒ:"), 20);

    if (cursorIdx != LB_ERR)
    {
        TextOutW(hdc, 160, 40, choice, BUF_SIZE);
        choice[0] = 0;
    }
    else {
        TextOutW(hdc, 160, 40, _T("Ãðóïó íå âèáðàíî."), 18);
    }
}*/