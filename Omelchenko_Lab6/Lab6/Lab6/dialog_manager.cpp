#include "framework.h"

#include "resource1.h"
#include "dialog_manager.h"

static TCHAR buf_n[BUF_SIZE];
static TCHAR buf_min[BUF_SIZE];
static TCHAR buf_max[BUF_SIZE];

static LPARAM CALLBACK DialogWin(HWND, UINT, WPARAM, LPARAM);

//------------
bool DialogManager::LaunchDialog(HINSTANCE hInst, HWND hWnd, double* dest_n, double* dest_min, double* dest_max)
{
    DialogBoxW(hInst, MAKEINTRESOURCE(IDD_DLG_DEFINE_VECTOR), hWnd, (DLGPROC)DialogWin);

    if (!ConvertBuffersToNums()) return FALSE;

    *dest_n = (double) n_res;
    *dest_min = min_res;
    *dest_max = max_res;
   
    return TRUE; 
}

bool DialogManager::ConvertBuffersToNums()
{
    n_res = _wtoi(buf_n);
    if (n_res < 1) return FALSE;

    min_res = _wtof(buf_min);
    max_res = _wtof(buf_max);

    if (min_res > max_res)
    {
        MessageBox(NULL, 
            L"¬в≥дне максимальне значенн€ б≥льше м≥н≥мального!\nѕрограма автоматично пом≥н€Ї значенн€ м≥н≥мального ≥ максимального чисел м≥сц€ми.",
            L"¬в≥дне максимальне значенн€ манше м≥н≥мального!", 
            NULL);

        double tmp = min_res;
        min_res = max_res;
        max_res = tmp;
    }

    return TRUE;
}
//------------

//----------------
//dialog window callback function
LPARAM CALLBACK DialogWin(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    //static DialogManager::
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        int command = LOWORD(wParam);

        switch (command)
        {
        case IDEXEC:
            GetDlgItemText(hDlg, IDC_VECTOR_SIZE, buf_n,   BUF_SIZE);
            GetDlgItemText(hDlg, IDC_NUM_MIN,     buf_min, BUF_SIZE);
            GetDlgItemText(hDlg, IDC_NUM_MAX,     buf_max, BUF_SIZE);

            EndDialog(hDlg, 1);
            break;
        case IDCANCEL:
            EndDialog(hDlg, 0);
            break;
        }

        break;
    }

    return (INT)FALSE;
}
//--------------