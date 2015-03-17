//rect.cpp
#include <cmath>
#include "rect.h"
using namespace std;

Rect::Rect(double dblWidth, double dblHeight)
{
    m_dblWidth = abs(dblWidth);
    m_dblHeight = abs(dblHeight);
}

double Rect::CalcDiagonal()
{
    return sqrt(m_dblWidth*m_dblWidth + m_dblHeight*m_dblHeight);
}

double Rect::CalcArea()
{
    return m_dblWidth * m_dblHeight;
}
