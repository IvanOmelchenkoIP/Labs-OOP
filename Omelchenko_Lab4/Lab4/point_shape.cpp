#include "framework.h"
#include "colors.h"
#include "shape.h"
#include "point_shape.h"

void PointShape::Show(HDC hdc, bool isTrace)
{
	xs = xe; ys = ye;
	
	SetPixel(hdc, xs - 1, ys, BLACK);
	SetPixel(hdc, xs + 1, ys, BLACK);
	SetPixel(hdc, xs, ys - 1, BLACK);
	SetPixel(hdc, xs, ys + 1, BLACK);
	SetPixel(hdc, xs - 1, ys + 1, BLACK);
	SetPixel(hdc, xs + 1, ys + 1, BLACK);
	SetPixel(hdc, xs + 1, ys - 1, BLACK);
	SetPixel(hdc, xs - 1, ys - 1, BLACK);

	SetPixel(hdc, xs, ys, BLACK);
}

void PointShape::MakeNewInstance(Shape*& targetShape)
{
	if (targetShape) delete targetShape;
	targetShape = new PointShape;
}