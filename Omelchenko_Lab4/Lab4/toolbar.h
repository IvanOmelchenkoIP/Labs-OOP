#pragma once

class Toolbar
{
private:
	const int PRESSED = 1;
	const int UNPRESSED = 0;
	HWND hwndToolBar = NULL;

public:
	void OnCreate(HWND);
	void OnSize();
	void OnNotify(LPARAM);

	void PickTool(WPARAM);
	void UnpressAll();
};

