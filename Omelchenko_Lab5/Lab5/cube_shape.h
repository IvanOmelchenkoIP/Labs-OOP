#pragma once

class CubeShape :
    public RectShape, public LineShape
{
public:
    void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
    void GiveOutData(void AddNodeCallback(std::string, long, long, long, long));
};

