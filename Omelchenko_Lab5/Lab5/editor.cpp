#include "framework.h"
#include <string>
#include "colors.h"
#include "shape.h"
#include "editor.h"

EditorSingleton* EditorSingleton::epInstance = nullptr;

EditorSingleton* EditorSingleton::GetInstance()
{
	if (!epInstance) epInstance = new EditorSingleton();
	return epInstance;
}


EditorSingleton::EditorSingleton()
{
	xs = ys = xe = ye = 0;
	sObject = new Shape * [length]() ;
}

EditorSingleton::~EditorSingleton()
{
	for (int i = 0; i < counter; i++)
		if (sObject[i]) delete sObject[i];

	if (sObject) delete[]sObject;
}

void EditorSingleton::ChooseShape(Shape* shape)
{
	if (counter >= MAX_LENGTH)
	{
		delete shape;
		return;
	}

	if (sObject[counter]) delete sObject[counter];
	sObject[counter] = shape;
}

void EditorSingleton::OnLBdown(HWND hWnd)
{
	if (sObject[counter] && counter < MAX_LENGTH)
	{
		POINT coords;
		GetCursorPos(&coords);
		ScreenToClient(hWnd, &coords);

		xs = xe = coords.x;
		ys = ye = coords.y;

		sObject[counter]->Set(xs, ys, xe, ye);

		isTrace = true;
		SetCapture(hWnd);
	}
}

void EditorSingleton::OnLBup(HWND hWnd, void AddNodeCallback(std::string, long, long, long, long))
{
	if (isTrace)
	{
		sObject[counter]->GiveOutData(AddNodeCallback);

		isTrace = false;
		counter++;

		ReleaseCapture();
		InvalidateRect(hWnd, NULL, TRUE);

		if (counter < MAX_LENGTH)
		{
			if (counter >= length) ResizeArray();
			sObject[counter - 1]->MakeNewInstance(sObject[counter]);
		}
	}
}

void EditorSingleton::OnMouseMove(HWND hWnd)
{
	if (isTrace && sObject[counter])
	{
		POINT coords;
		HPEN hPen, hOldPen;
		HDC hdc;

		hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		hPen = CreatePen(PS_DOT, 1, BLACK);
		hOldPen = (HPEN)SelectObject(hdc, hPen);

		GetCursorPos(&coords);
		ScreenToClient(hWnd, &coords);

		sObject[counter]->Show(hdc, isTrace);

		xe = coords.x;
		ye = coords.y;

		sObject[counter]->Set(xs, ys, xe, ye);
		sObject[counter]->Show(hdc, isTrace);

		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);
		ReleaseDC(hWnd, hdc);
	}
}

void EditorSingleton::OnPaint(HWND hWnd, HDC hdc)
{
	for (int i = 0; i < counter; i++)
		if (sObject[i]) sObject[i]->Show(hdc, isTrace); 
}

void EditorSingleton::OnClear(HWND hWnd, void ClearTable())
{
	ClearTable();
	for (int i = 0; i < counter; i++)
	{
		if (sObject[i])
		{
			delete sObject[i];
			sObject[i] = NULL;
		}
	}
	length = counter = 0;
	ResizeArray();

	InvalidateRect(hWnd, NULL, TRUE);
}

void EditorSingleton::ResizeArray()
{
	length += 10;
	if (length > MAX_LENGTH) length = MAX_LENGTH;
	Shape** shapeTemp = new Shape * [length]();

	#pragma warning(push)
	#pragma warning(disable: 6386)
	for (int i = 0; i < counter; i++)
		shapeTemp[i] = sObject[i];
	#pragma warning(pop)
	delete[] sObject;
	sObject = shapeTemp;
}