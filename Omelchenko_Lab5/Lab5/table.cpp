#include "framework.h"
#include <list>
#include <string>
#include "commdlg.h"
#include "colors.h"
#include "table.h"

//---------------------
//file system
void FileSystem::CreateFileStream(HeaderRow header)
{
	fopen_s(&filestream, filename, "wt");

	fprintf_s(filestream, "%s\t%s\t%s\t%s\t%s\n",
		header.type.c_str(), header.xs.c_str(), header.ys.c_str(), header.xe.c_str(), header.ye.c_str());
}

void FileSystem::AddToFileStream(ShapeRow row)
{
	fprintf_s(filestream, "%s", row.type.c_str());
	fprintf_s(filestream , "\t%d\t%d\t%d\t%d\n", row.xs, row.ys, row.xe, row.ye);
}

void FileSystem::ClearFileStream(HeaderRow header)
{
	fclose(filestream);
	CreateFileStream(header);
}


//-------------------------------------------
//ititializing table, column sizes and header
void Table::InitTable(HWND hwndTableWin)
{
	RECT parentRect;
	GetClientRect(hwndTableWin, &parentRect);

	tableWidth = parentRect.right - parentRect.left;
	tableHeight = rowHeight;

	hwndTable = CreateWindowEx(
		NULL,
		L"STATIC",
		NULL,
		WS_CHILD | WS_VISIBLE,
		tableStartX,
		tableStartY,
		tableWidth,
		tableHeight,
		hwndTableWin,
		(HMENU)NULL,
		NULL,
		0
	);

	SetColumnSizes();
	InitHeader();

	fs.CreateFileStream(header);
}

void Table::SetColumnSizes()
{
	int colSize = tableWidth / 5;
	int nameColSize = (int)(colSize * 2.5);
	int coordColSize = (int)( (tableWidth - nameColSize) / 4 );

	xs_columnX = nameColSize;
	ys_columnX = xs_columnX + coordColSize;
	xe_columnX = ys_columnX + coordColSize;
	ye_columnX = xe_columnX + coordColSize;
}

void Table::InitHeader()
{
	header.type = "Фігура";
	header.xs = "xs";
	header.ys = "ys";
	header.xe = "xe";
	header.ye = "ye";

	header.topY = tableStartY;
	header.bottomY = tableStartY + rowHeight;

	header.rgn = CreateRectRgn(tableStartX, header.topY, tableWidth, header.bottomY);
}

//adding rows and adjusting table to fit new ones
void Table::AddRow(std::string type, long xs, long ys, long xe, long ye)
{
	if (!hwndTable) return;

	AdjustTable();

	ShapeRow row;
	row.type = type;
	row.xs = xs;
	row.ys = ys;
	row.xe = xe;
	row.ye = ye;

	row.id = shapeID;
	shapeID++;

	row.topY = curRowY;
	row.bottomY = curRowY + rowHeight;
	curRowY += rowHeight;

	row.rgn = CreateRectRgn(tableStartX, row.topY, tableWidth, row.bottomY);

	fs.AddToFileStream(row);

	rows.push_back(row);
}

void Table::AdjustTable()
{
	tableHeight += rowHeight;

	SetWindowPos(hwndTable, HWND_TOP, tableStartX, tableStartY, tableWidth, tableHeight, SWP_NOMOVE | SWP_SHOWWINDOW);
}

//clearing list
void Table::ClearRowList()
{
	ClearTable();

	rows.clear();
	InvalidateRect(hwndTable, NULL, TRUE);
}

void Table::ClearTable()
{
	tableHeight = rowHeight;
	curRowY = 30;

	SetWindowPos(hwndTable, HWND_TOP, tableStartX, tableStartY, tableWidth, tableHeight, SWP_NOMOVE | SWP_SHOWWINDOW);

	fs.ClearFileStream(header);
}

//painting table
void Table::PaintTable()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwndTable, &ps);

	SetBkMode(hdc, TRANSPARENT);

	PaintHeader(hdc);
	PaintRows(hdc);

	EndPaint(hwndTable, &ps);
}

void Table::PaintHeader(HDC hdc)
{
	FillRgn(hdc, header.rgn, (HBRUSH)CreateSolidBrush(WHITE));
	FrameRgn(hdc, header.rgn, CreateSolidBrush(BLACK), 1, 1);

	MoveToEx(hdc, xs_columnX, header.topY, NULL);
	LineTo(hdc, xs_columnX, header.bottomY);
	MoveToEx(hdc, ys_columnX, header.topY, NULL);
	LineTo(hdc, ys_columnX, header.bottomY);
	MoveToEx(hdc, xe_columnX, header.topY, NULL);
	LineTo(hdc, xe_columnX, header.bottomY);
	MoveToEx(hdc, ye_columnX, header.topY, NULL);
	LineTo(hdc, ye_columnX, header.bottomY);

	int captionY = (int)( (header.bottomY + header.topY) / 4 );
	TextOutA(hdc, tableStartX + 10, captionY, header.type.c_str(), header.type.length());
	TextOutA(hdc, xs_columnX + 10,  captionY, header.xs.c_str(),   header.xs.length());
	TextOutA(hdc, ys_columnX + 10,  captionY, header.ys.c_str(),   header.ys.length());
	TextOutA(hdc, xe_columnX + 10,  captionY, header.xe.c_str(),   header.xe.length());
	TextOutA(hdc, ye_columnX + 10,  captionY, header.ye.c_str(),   header.ye.length());
}

void Table::PaintRows(HDC hdc)
{
	for (ShapeRow row : rows)
	{
		FillRgn(hdc, row.rgn, (HBRUSH)CreateSolidBrush(RGB(245, 245, 245)));
		FrameRgn(hdc, row.rgn, CreateSolidBrush(BLACK), 1, 1);

		MoveToEx(hdc, xs_columnX, row.topY, NULL);
		LineTo(hdc, xs_columnX, row.bottomY);
		MoveToEx(hdc, ys_columnX, row.topY, NULL);
		LineTo(hdc, ys_columnX, row.bottomY);
		MoveToEx(hdc, xe_columnX, row.topY, NULL);
		LineTo(hdc, xe_columnX, row.bottomY);
		MoveToEx(hdc, ye_columnX, row.topY, NULL);
		LineTo(hdc, ye_columnX, row.bottomY);

		std::string xs = std::to_string(row.xs);
		std::string ys = std::to_string(row.ys);
		std::string xe = std::to_string(row.xe);
		std::string ye = std::to_string(row.ye);

		int captionY = (int)((row.bottomY + row.topY) / 2 - 7);
		TextOutA(hdc, tableStartX + 10, captionY, row.type.c_str(), row.type.length());
		TextOutA(hdc, xs_columnX + 10,  captionY, xs.c_str(),       xs.length());
		TextOutA(hdc, ys_columnX + 10,  captionY, ys.c_str(),       ys.length());
		TextOutA(hdc, xe_columnX + 10,  captionY, xe.c_str(),       xe.length());
		TextOutA(hdc, ye_columnX + 10,  captionY, ye.c_str(),       ye.length());
	}
}