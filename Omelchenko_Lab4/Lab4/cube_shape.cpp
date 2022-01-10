#include "framework.h"
#include "colors.h"
#include "shape.h"
#include "line_shape.h"
#include "rect_shape.h"
#include "cube_shape.h"

void CubeShape::Show(HDC hdc, bool isTrace)
{
	long xs_generic = xs;
	long ys_generic = ys;
	long xe_generic = xe;
	long ye_generic = ye;

	long xm = (xe_generic + xs_generic) / 2;
	long ym = (ys_generic + ye_generic) / 2;

	long xs1 = xs_generic;
	long ys1 = (ys_generic + ym) / 2;
	long xe1 = (xe_generic + xm) / 2;
	long ye1 = ye_generic;

	long xs2 = (xs_generic + xm) / 2;
	long ys2 = ys_generic;
	long xe2 = xe_generic;
	long ye2 = (ye_generic + ym) / 2;
	
	Set(xs1, ys1, xe1, ye1);
	RectShape::Show(hdc, true);
	Set(xs2, ys2, xe2, ye2);
	RectShape::Show(hdc, true);

	Set(xs1, ys1, xs2, ys2);
	LineShape::Show(hdc, true);
	Set(xs1, ye1, xs2, ye2);
	LineShape::Show(hdc, true);
	Set(xe1, ye1, xe2, ye2);
	LineShape::Show(hdc, true);
	Set(xe1, ys1, xe2, ys2);
	LineShape::Show(hdc, true);

	Set(xs_generic, ys_generic, xe_generic, ye_generic);
}

void CubeShape::MakeNewInstance(Shape*& targetShape)
{
	if (targetShape) delete targetShape;
	targetShape = new CubeShape;
}