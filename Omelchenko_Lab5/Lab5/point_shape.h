#pragma once

class PointShape :
    public Shape
{
public:
    void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
    void GiveOutData(void AddNodeCallback(std::string, long, long, long, long));
};

