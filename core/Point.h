#ifndef RESTONCE_POINT_H
#define RESTONCE_POINT_H

namespace restonce {

/**
 * @brief The Point class 对应游戏逻辑里面的一个点
 */
class Point
{
public:
    Point() = default;
    Point(int x, int y); // 构造函数
    int getX() const; // 获取X
    int getY() const; // 获取Y
    void setX(int x); // 设置X
    void setY(int y); // 设置Y
private:
    int m_x=0; // x坐标
    int m_y=0; // y坐标
};

/**
 * @brief operator == 比较2个点是否相等
 * @param p1 第一个点
 * @param p2 第二个点
 * @return true -> 两点相等, false -> 两点不等
 */
bool operator== (const Point& p1, const Point& p2);

} // namespace restonce

#endif // RESTONCE_POINT_H
