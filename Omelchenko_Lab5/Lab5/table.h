#pragma once

class Row
{
public:
	std::string type;

	long topY;
	long bottomY;

	HRGN rgn;
};

class HeaderRow :
	public Row
{
public:
	std::string xs;
	std::string ys;
	std::string xe;
	std::string ye;
};

class ShapeRow :
	public Row
{
public:
	int id;

	long xs;
	long ys;
	long xe;
	long ye;
};

class FileSystem
{
private:
	FILE* filestream;
	const char* filename = "table.txt";
public:
	void CreateFileStream(HeaderRow);
	void AddToFileStream(ShapeRow);
	void ClearFileStream(HeaderRow);
};

class Table 
{
private:
	HWND hwndTable;

	FileSystem fs;

	HeaderRow header;
	std::list<ShapeRow> rows;
	
	int shapeID = 0;

	long curRowY = 30;
	const long rowHeight = 30;

	const long tableStartX = 0;
	const long tableStartY = 0;
	long tableWidth;
	long tableHeight;

	long xs_columnX;
	long ys_columnX;
	long xe_columnX;
	long ye_columnX;

	void SetColumnSizes();
	void InitHeader();

	void AdjustTable();
	void ClearTable();

	void PaintHeader(HDC);
	void PaintRows(HDC);

public:
	void InitTable(HWND);

	void AddRow(std::string, long, long, long, long);
	void ClearRowList();

	void PaintTable();
};

