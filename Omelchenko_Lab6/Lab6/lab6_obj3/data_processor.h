#pragma once
#define BUF_SIZE 32

class DataProcessor
{
private:
	std::wstring wstr_buf;
	std::list<double> lst;

	int CopyClipboardData(HWND);
	void ParseBufferData();
public:
	std::list<double> GetListFromClipboard(HWND);
};

