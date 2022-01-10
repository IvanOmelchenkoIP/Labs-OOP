#include "framework.h"
#include <string>
#include <list>
#include "data_processor.h"

std::list<double> DataProcessor::GetListFromClipboard(HWND hWnd)
{
    CopyClipboardData(hWnd);
        
    ParseBufferData();
    return lst;
}

int DataProcessor::CopyClipboardData(HWND hWnd)
{
    HGLOBAL hglb;
    WCHAR* pTmp;
    //MessageBox(NULL, L"1", L"1", NULL);
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) return 0;
    //MessageBox(NULL, L"2", L"2", NULL);
    if (!OpenClipboard(hWnd)) return 0;

    hglb = GetClipboardData(CF_UNICODETEXT);
    if (hglb)
    {
        //MessageBox(NULL, L"3", L"3", NULL);
        pTmp = (WCHAR*)GlobalLock(hglb);
        if (pTmp)
        {
            //MessageBox(NULL, L"4", L"4", NULL);
            std::wstring wstr_tmp(&pTmp[0]);
            wstr_buf = wstr_tmp;
            GlobalUnlock(hglb);
            CloseClipboard();
        }
    }

    return 0;
}

void DataProcessor::ParseBufferData()
{
    std::string tmp;
    std::string str_buf(wstr_buf.begin(), wstr_buf.end());

    for (int i = 0; i < str_buf.size(); i++)
    {
        std::string symbol = str_buf.substr(i, 1);
        if (symbol == "\n")
        {
            lst.push_back(std::stof(tmp));
            tmp.erase();
        }
        else {
            tmp += symbol;
        }
    }
    lst.sort();
}