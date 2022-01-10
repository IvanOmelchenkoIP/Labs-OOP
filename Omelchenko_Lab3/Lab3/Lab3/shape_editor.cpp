#include "framework.h"

#include "shape.h"
#include "editor.h"
#include "shape_editor.h"

ShapeObjectsEditor::ShapeObjectsEditor()
{
	sEditor = NULL;
	for (int i = 0; i < MAX_OBJ; i++) sObject[i] = NULL;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < counter; i++) 
		if (sObject[i]) delete sObject[i];
	
	if (sEditor) delete sEditor;
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd)
{
	if (sEditor) delete sEditor;
	sEditor = new PointEditor;

	SetWindowText(hWnd, L"Режим малювання - крапка");
}
void ShapeObjectsEditor::StartLineEditor(HWND hWnd) 
{
	if (sEditor) delete sEditor; 
	sEditor = new LineEditor;

	SetWindowText(hWnd, L"Режим малювання - лінія");
}
void ShapeObjectsEditor::StartRectEditor(HWND hWnd) 
{
	if (sEditor) delete sEditor;
	sEditor = new RectEditor;

	SetWindowText(hWnd, L"Режим малювання - чотирикутник");
}
void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd) 
{
	if (sEditor) delete sEditor;
	sEditor = new EllipseEditor;

	SetWindowText(hWnd, L"Режим малювання - еліпс");
}


void ShapeObjectsEditor::OnLBdown(HWND hWnd) 
{
	if (sEditor) sEditor->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd) 
{
	if (sEditor)
	{
		sEditor->OnLBup(hWnd);

		if (counter < MAX_OBJ)
		{
			sEditor->CreateShape(sObject[counter]);
			counter++;
		}

		InvalidateRect(hWnd, NULL, TRUE);
	}
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
	if (sEditor) sEditor->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd) 
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	for (int i = 0; i < counter; i++)
		if (sObject[i]) sObject[i]->Show(hdc);

	EndPaint(hWnd, &ps);
}

void ShapeObjectsEditor::OnClear(HWND hWnd)
{
	for (int i = 0; i < counter; i++)
		if (sObject[i]) delete sObject[i];
	counter = 0;

	sEditor = NULL;
	SetWindowText(hWnd, L"Лабораторна робота 3. Омельченко Іван. ІП-04");
	InvalidateRect(hWnd, NULL, TRUE);

}