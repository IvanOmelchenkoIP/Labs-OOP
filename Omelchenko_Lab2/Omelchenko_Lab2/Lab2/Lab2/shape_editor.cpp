#include "framework.h"

#include "shape.h"
#include "editor.h"
#include "shape_editor.h"

ShapeObjectsEditor::ShapeObjectsEditor()
{
	sEditor = NULL;
	sObject = new Shape * [MAX_OBJ]();
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < counter; i++) 
		if (sObject[i]) delete sObject[i];

	delete []sObject;
	
	if (sEditor) delete sEditor;
}

void ShapeObjectsEditor::StartPointEditor()
{
	if (sEditor) delete sEditor;
	sEditor = new PointEditor;
}
void ShapeObjectsEditor::StartLineEditor() 
{
	if (sEditor) delete sEditor; 
	sEditor = new LineEditor;
}
void ShapeObjectsEditor::StartRectEditor() 
{
	if (sEditor) delete sEditor;
	sEditor = new RectEditor;
}
void ShapeObjectsEditor::StartEllipseEditor() 
{
	if (sEditor) delete sEditor;
	sEditor = new EllipseEditor;
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

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam) 
{
	if (sEditor) sEditor->OnInitMenuPopup(hWnd, wParam);
}