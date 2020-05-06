#pragma once

#include <cmath>

class Vector2f{
public:
    Vector2f(float _x, float _y): y(_y), x(_x) {}
    float x, y;

    Vector2f operator+(Vector2f &v){
        return Vector2f(this->x + v.x, this->y + v.y);
    }

    Vector2f operator-(){
        return Vector2f(-this->x, -this->y);
    };

    Vector2f operator-(Vector2f &v){
        return Vector2f(this->x - v.x, this->y - v.y);
    }

    Vector2f& operator+=(Vector2f & v){
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    float getAngle(){
        return atan2(y, x);
    }
};

class Segment{
public:
    Vector2f v1, v2;

    Segment(Vector2f _v1, Vector2f _v2): v1(_v1), v2(_v2) {}
    Segment(float x1, float y1, float x2, float y2): v1(Vector2f(x1, y1)), v2(Vector2f(x2, y2)) {}
};
