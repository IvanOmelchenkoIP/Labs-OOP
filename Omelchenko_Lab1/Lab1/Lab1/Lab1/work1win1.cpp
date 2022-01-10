#include "framework.h"

#include "work1states.h"

#include "resource1.h"
#include "work1win1.h"

static INT CALLBACK DialogWin1(HWND, UINT, WPARAM, LPARAM);

int LaunchWin1(HINSTANCE hInst, HWND hWnd)
{
    return DialogBoxW(hInst, MAKEINTRESOURCE(IDD_WORK1WIN1), hWnd, (DLGPROC)DialogWin1);
}

INT CALLBACK DialogWin1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        int command = LOWORD(wParam);

        if (command == IDGOFORWARD)
        {
            return EndDialog(hDlg, FORWARD);
        }
        else if (command == IDCANCEL)
        {
            return EndDialog(hDlg, COMPLETE_DENY);
        }

        break;
    }

    return COMPLETE_DENY;
}