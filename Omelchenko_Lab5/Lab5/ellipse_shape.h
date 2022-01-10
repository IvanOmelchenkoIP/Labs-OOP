#pragma once

class EllipseShape :
    virtual public Shape
{
public:
    virtual void Show(HDC, bool);
    void MakeNewInstance(Shape*&);
    void GiveOutData(void AddNodeCallback(std::string, long, long, long, long));
};

