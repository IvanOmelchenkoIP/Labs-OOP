#include "framework.h"
#include "resource.h"

#include "colors.h"
#include "shape.h"
#include "editor.h"

//========
void ShapeEditor::OnLBdown(HWND hWnd) 
{ 
	POINT coords;

	GetCursorPos(&coords);
	ScreenToClient(hWnd, &coords);

	SetStartCoords(coords);

	isTrace = true;
	SetCapture(hWnd);
}

void ShapeEditor::OnLBup(HWND hWnd)
{
	isTrace = false;
	ReleaseCapture();
}

void ShapeEditor::OnMouseMove(HWND hWnd)
{
	if (!isTrace) return;

	POINT coords;
	HPEN hPen, hOldPen;
	HDC hdc;

	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, BLUE);

	hOldPen = (HPEN)SelectObject(hdc, hPen);

	GetCursorPos(&coords);
	ScreenToClient(hWnd, &coords);

	DrawRubberTrace(hWnd, hdc, coords);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam) 
{
	HMENU hMenu, hSubMenu, curSubMenu;

	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, OBJ_MENU);

	curSubMenu = (HMENU)wParam;
	if (curSubMenu != hSubMenu) return;
	SetActiveMenu(hSubMenu);
}

void ShapeEditor::SetStartCoords(POINT coords)
{
	xs = xe = coords.x;
	ys = ye = coords.y;
}
//==========


//=========
void PointEditor::CreateShape(Shape*& shape)
{
	shape = new PointShape;
	shape->Set(xs, ys, xe, ye);
}

void PointEditor::DrawRubberTrace(HWND hWnd, HDC hdc, POINT coords)
{
	xs = xe = coords.x;
	ys = ye = coords.y;
}

void PointEditor::SetActiveMenu(HMENU hSubMenu)
{
	CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
	CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
}
//=========


//=======
void LineEditor::CreateShape(Shape*& shape)
{
	shape = new LineShape;
	shape->Set(xs, ys, xe, ye);
}

void LineEditor::DrawRubberTrace(HWND hWnd, HDC hdc, POINT coords)
{
	MoveToEx(hdc, xs, ys, NULL);
	LineTo(hdc, xe, ye);

	xe = coords.x;
	ye = coords.y;

	MoveToEx(hdc, xs, ys, NULL);
	LineTo(hdc, xe, ye);
}

void LineEditor::SetActiveMenu(HMENU hSubMenu)
{
	CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
	CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
}
//==========

//==========
void RectEditor::CreateShape(Shape*& shape)
{
	shape = new RectShape;
	shape->Set(xs, ys, xe, ye);
}

void RectEditor::DrawRubberTrace(HWND hWnd, HDC hdc, POINT coords)
{
	Rectangle(hdc, xs, ys, xe, ye);

	xe = coords.x;
	ye = coords.y;

	Rectangle(hdc, xs, ys, xe, ye);
}

void RectEditor::SetActiveMenu(HMENU hSubMenu)
{
	CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_RECT, MF_CHECKED);
	CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
}
//==========

//==========
void EllipseEditor::SetStartCoords(POINT coords)
{
	xs = xe = xm = coords.x;
	ys = ye = ym = coords.y;
}

void EllipseEditor::CreateShape(Shape*& shape)
{
	shape = new EllipseShape;
	shape->Set(xs, ys, xe, ye);
}

void EllipseEditor::DrawRubberTrace(HWND hWnd, HDC hdc, POINT coords)
{
	int radX, radY;

	Ellipse(hdc, xs, ys, xe, ye);

	xe = coords.x;
	ye = coords.y;

	radX = xe - xm;
	radY = ye - ym;

	xs = xm - radX;
	ys = ym - radY;

	Ellipse(hdc, xs, ys, xe, ye);
}

void EllipseEditor::SetActiveMenu(HMENU hSubMenu)
{
	CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
	CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
}
//==========
