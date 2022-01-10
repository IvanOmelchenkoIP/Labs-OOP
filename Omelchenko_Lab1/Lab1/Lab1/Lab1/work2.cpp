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

static const std::wstring groups[LST_SIZE] = { L"��-11", L"��-12", L"��-13", L"��-14", L"��-15", L"��-�11",
                                               L"��-01", L"��-02", L"��-03", L"��-04", L"��-05", L"��-�01",
                                               L"��-91", L"��-92", L"��-93", L"��-94", L"��-95", L"��-96", L"��-�91",
                                               L"��-81", L"��-82", L"��-83", L"��-84", L"��-�81", L"��-�82",
                                               L"��-01", L"��-02", L"��-03", L"��-04",
                                               L"��-91", L"��-92", L"��-93", L"��-94", L"��-�91",
                                               L"��-81", L"��-82", L"��-83", L"��-84", L"��-�81",
                                               L"��-11", L"��-12", L"��-13", L"��-�11",
                                               L"��-01", L"��-02", L"��-03", L"��-�01",
                                               L"��-91", L"��-92", L"��-93", L"��-�91",
                                               L"��-81", L"��-82", L"��-83",
                                               L"��-11", L"��-12", L"��-13", L"��-14", L"��-15", L"��-16", L"��-�11",
                                               L"��-01", L"��-02", L"��-03", L"��-04", L"��-05", L"��-06", L"��-�01",
                                               L"��-91", L"��-92", L"��-93", L"��-�91",
                                               L"��-81", L"��-82", L"��-83", L"��-�82",
                                               L"��-91", L"��-92", L"��-93",
                                               L"��-81", L"��-82", L"��-83",
                                               L"��-11", L"��-12", L"��-13", L"��-14", L"��-�11",
                                               L"��-01", L"��-02", L"��-03", L"��-04", L"��-�01",
                                               L"��-91", L"��-92", L"��-93", L"��-94", L"��-�91",
                                               L"��-81", L"��-82", L"��-83",
                                               L"��-11", L"��-12", L"��-13",
                                               L"��-01", L"��-02", L"��-03",
                                               L"��-91", L"��-92", L"��-93",
                                               L"��-81", L"��-82", L"��-83" };

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
    TextOutW(hdc, 10, 40, _T("������� ����� Բ��:"), 20);

    if (cursorIdx != LB_ERR)
    {
        TextOutW(hdc, 160, 40, choice, BUF_SIZE);
        choice[0] = 0;
    }
    else {
        TextOutW(hdc, 160, 40, _T("����� �� �������."), 18);
    }
}*/