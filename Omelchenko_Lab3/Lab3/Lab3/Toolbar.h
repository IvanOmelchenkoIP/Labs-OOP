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
	void OnNotify(HWND, WPARAM, LPARAM);

	void PickToolPoint();
	void PickToolLine();
	void PickToolRect();
	void PickToolEllipse();

	void UnpressAll();
};

