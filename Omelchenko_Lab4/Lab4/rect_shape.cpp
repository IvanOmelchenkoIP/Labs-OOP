#include "framework.h"
#include "colors.h"
#include "shape.h"
#include "rect_shape.h"

void RectShape::Show(HDC hdc, bool isTrace)
{
	HBRUSH hBrush, hBrushOld;

	hBrush = (HBRUSH)CreateSolidBrush(GREEN);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	if (!isTrace)
	{
		RECT pRect;
		SetRect(&pRect, xs, ys, xe, ye);
		FillRect(hdc, &pRect, hBrush);
	}


	MoveToEx(hdc, xs, ys, NULL);
	LineTo(hdc, xs, ye);
	MoveToEx(hdc, xs, ye, NULL);
	LineTo(hdc, xe, ye);
	MoveToEx(hdc, xe, ye, NULL);
	LineTo(hdc, xe, ys);
	MoveToEx(hdc, xe, ys, NULL);
	LineTo(hdc, xs, ys);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void RectShape::MakeNewInstance(Shape*& targetShape)
{
	if (targetShape) delete targetShape;
	targetShape = new RectShape;
}