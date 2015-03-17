//rect.h
class Rect
{
private:
    double m_dblWidth;
    double m_dblHeight;

public:
    Rect(double dblWidth, double dblHeight);
    double GetWidth(){ return m_dblWidth; }
    double GetHeight(){ return m_dblHeight; }
    //Functions
    double CalcDiagonal();
    double CalcArea();
};
