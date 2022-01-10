#include "framework.h"
#include "colors.h"
#include "shape.h"
#include "ellipse_shape.h"

void EllipseShape::Show(HDC hdc, bool isTrace)
{
	if (isTrace)
	{
		Arc(hdc, xs, ys, xe, ye, 0, 0, 0, 0);
	}
	else
	{
		HBRUSH hBrush, hBrushOld;

		hBrush = (HBRUSH)CreateSolidBrush(YELLOW);
		hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

		Ellipse(hdc, xs, ys, xe, ye);

		SelectObject(hdc, hBrushOld);
		DeleteObject(hBrush);		
	}	
}

void EllipseShape::MakeNewInstance(Shape*& targetShape)
{
	if (targetShape) delete targetShape;
	targetShape = new EllipseShape;
}