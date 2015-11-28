#ifndef RESTONCE_POINT_H
#define RESTONCE_POINT_H

namespace restonce {

class Point
{
public:
    Point() = default;
    Point(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
private:
    int m_x=0;
    int m_y=0;
};

bool operator== (const Point& p1, const Point& p2);

} // namespace restonce

#endif // RESTONCE_POINT_H
