// Lab6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"

#include "dialog_manager.h" 
#include "Lab6.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

DialogManager dm;

#define BUF_SIZE 32

double n;
double min;
double max;

HWND hwndObj2;
HWND hwndObj3;

void OnCreateWin(HWND);
void CreateVector(HWND);
int SendCopyData(HWND, HWND, void*, long);

void OnClipboardDataCopied(HWND hWnd);

void OnDestroy(HWND);


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB6);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:  
        OnCreateWin(hWnd);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_DEFINE_VECTOR:
            {
                CreateVector(hWnd);
                break;
            }
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                OnDestroy(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case MSG_NULL_OBJ2:
        hwndObj2 = NULL;
        break;
    case MSG_NULL_OBJ3:
        hwndObj3 = NULL;
        break;
    case MSG_COPIED_TO_CLIPBOARD:
        OnClipboardDataCopied(hWnd);
        break;
    case WM_DESTROY:
        OnDestroy(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//creating window
//---------------
void OnCreateWin(HWND hWnd)
{
    POINT screenSize;
    screenSize.x = GetSystemMetrics(SM_CXSCREEN);
    screenSize.y = GetSystemMetrics(SM_CYSCREEN);

    long xs = 0;
    long ys = 0;
    long width = screenSize.x / 2;
    long height = screenSize.y;

    MoveWindow(hWnd, xs, ys, width, height, TRUE);

    hwndObj2 = FindWindow(L"LAB6OBJ2", NULL);
    hwndObj3 = FindWindow(L"LAB6OBJ3", NULL);
}
//---------------


//processing vector
//---------------
void CreateVector(HWND hWnd)
{
    bool isSuccessful = dm.LaunchDialog(hInst, hWnd, &n, &min, &max);
    if (!isSuccessful) {
        MessageBox(NULL, L"Помилка при вводі даних!\nДані введено не коректно!", L"Помилка при вводі даних!", NULL);
        return;
    }

    double params[3] = {n, min, max};

    if (!hwndObj2)
    {
        WinExec("lab6_obj2.exe", SW_SHOW);
        hwndObj2 = FindWindow(L"LAB6OBJ2", NULL);
    }
    else
    {
        ShowWindow(hwndObj2, TRUE);
    }
    SendCopyData(hwndObj2, hWnd, params, sizeof(params));
}

int SendCopyData(HWND hwndDestination, HWND hWnd, void* lparams, long byteCount)
{
    COPYDATASTRUCT cds;

    cds.dwData = 1;
    cds.cbData = byteCount;
    cds.lpData = lparams;
    
    return SendMessage(hwndDestination, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);
}
//----------------

//on clipboard data copied
//----------------
void OnClipboardDataCopied(HWND hWnd)
{
    if (!hwndObj3)
    {
        WinExec("lab6_obj3.exe", SW_SHOW);
        hwndObj3 = FindWindow(L"LAB6OBJ3", NULL);
    }
    else
    {
        ShowWindow(hwndObj3, TRUE);
        SendMessage(hwndObj3, MSG_COPY_CLIPBOARD, (WPARAM)hWnd, NULL);
    }
}
//----------------

//on destroying main window
//----------------
void OnDestroy(HWND hWnd)
{
    if (hwndObj2) SendMessage(hwndObj2, WM_DESTROY, (WPARAM)hWnd, NULL);
    if (hwndObj3) SendMessage(hwndObj3, WM_DESTROY, (WPARAM)hWnd, NULL);
    PostQuitMessage(0);
};
//---------------