#pragma once

class ShapeObjectsEditor
{
private:
	const int MAX_OBJ = 118;
	int counter = 0;

	ShapeEditor* sEditor;
	Shape** sObject;

public:
	ShapeObjectsEditor();
	~ShapeObjectsEditor();

	void StartPointEditor();
	void StartLineEditor();
	void StartRectEditor();
	void StartEllipseEditor();

	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

