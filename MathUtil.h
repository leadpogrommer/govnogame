#pragma once

#include <cmath>
#include <SFML/System.hpp>

#define PREPARE_ANGLE(a) if((a) > M_PI) (a)-= 2*M_PI; else if((a) < - M_PI) (a) += 2*M_PI;

class Vector2f{
public:
    Vector2f(float _x, float _y): y(_y), x(_x) {}
    float x, y;

    Vector2f operator+(const Vector2f &v){
        return Vector2f(this->x + v.x, this->y + v.y);
    }

    Vector2f operator-(){
        return Vector2f(-this->x, -this->y);
    };

    Vector2f operator-(Vector2f const &v) const{
        return Vector2f(this->x - v.x, this->y - v.y);
    }

    Vector2f& operator+=(Vector2f & v){
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vector2f operator*(float s){
        return Vector2f(this->x*s, this->y*s);
    }

    float dot(Vector2f &v1){
        return this->x*v1.x + this->y*v1.y;
    }

    float getAngle(){
        return atan2f(y, x);
    }

    float getLength(){
        return sqrtf(x*x + y*y);
    }

    void normalize(){
        float l = getLength();
        x /= l;
        y /= l;
    }

    void scale(float s){
        x *= s;
        y *= s;
    }

    void setAngle(float a){
        float l = getLength();
        x = cosf(a)*l;
        y = sinf(a)*l;

    }


    operator sf::Vector2f(){
        return sf::Vector2f(this->x, this->y);
    }
};


class Segment{
public:
    Vector2f v1, v2;

    Segment(Vector2f _v1, Vector2f _v2): v1(_v1), v2(_v2) {}
    Segment(float x1, float y1, float x2, float y2): v1(Vector2f(x1, y1)), v2(Vector2f(x2, y2)) {}
};
