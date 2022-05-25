#pragma once

struct Color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

class Shape
{
public:
    Shape(){};
    int m_x = 0;
    int m_y = 0;
    Color m_color{0, 0, 0, 0};
    virtual void Draw() { };
};

class Triangle : public Shape
{
    SDL_Point m_p1, m_p2, m_p3;

public:
    Triangle(const SDL_Point &p1, const SDL_Point &p2, const SDL_Point &p3, const Color &color) : m_p1(p1), m_p2(p2), m_p3(p3)
    {
        m_color = color;
    };

    void Draw() override;
};

class Circle : public Shape
{
    float m_radius;

public:
    Circle(int x, int y, float radius, const Color &color) : m_radius(radius)
    {
        m_x = x;
        m_y = y;
        m_color = color;
    };

    void Draw() override;
};

class Rectangle : public Shape
{
    int m_width;
    int m_height;

public:
    Rectangle(int x, int y, int width, int height, const Color &color) : m_width(width), m_height(height)
    {
        m_x = x;
        m_y = y;
        m_color = color;
    };
    void Draw() override;
};