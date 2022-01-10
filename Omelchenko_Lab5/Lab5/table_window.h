#pragma once

class TableWindow
{
private:
	MSG msg;
	HANDLE hdlgTable;
	BYTE* pdlgHDR;
	DLGTEMPLATE dlgHeader;

	static TableWindow* twpInstance;

	TableWindow() = default;
	TableWindow(const TableWindow&) = delete;
	TableWindow& operator=(TableWindow&) = delete;

	Table table;

public:
	HWND hwndTableWin;

	~TableWindow() = default;

	static TableWindow* GetInstance();

	void InitTableWindowData(HWND);
	void ShowTableWindow();

	void AddTableRow(std::string, long, long, long, long);
	void ClearTable();

	void OnInit(HWND);
	void OnPaint(HDC);
};
