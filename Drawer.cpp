#include "Drawer.h"
#include <cmath>
#include <iostream>
#include "MathUtil.h"
#include <utility>

#ifndef MAXFLOAT
#include <cfloat>
#define MAXFLOAT FLT_MAX
#endif

#define FOV ((float)M_PI/2.0f)

#define TO_MAP_COORDS(v) Vector2f((v).x + mw/2, -(v).y + mh/2)

void Drawer::render(Vector2f pos, float angle) {
    window->clear(sf::Color::Black);

    std::fill(zbuffer, zbuffer+this->w, MAXFLOAT);

    for (auto & i : map) {
        Vector2f v1 = i.segment.v1 - pos;
        Vector2f v2 = i.segment.v2 - pos;

        float a1, a2;

        a1 = v1.getAngle();
        a2 = v2.getAngle();

        a1 -= angle;
        a2 -= angle;

        PREPARE_ANGLE(a1);
        PREPARE_ANGLE(a2);

        if((std::abs(a1) > FOV/2) && (std::abs(a2) > FOV/2)) continue;


        bool reversed = false;

        if (a1 < a2){
            reversed = true;
            std::swap(a1, a2);
            std::swap(v1, v2);
        }

        v1.setAngle(a1);
        v2.setAngle(a2);


        int c1, c2;

        c1 = (-(a1-(FOV/2))/FOV)*w;
        c2 = (-(a2-(FOV/2))/FOV)*w;

        int rc1 = c1;
        int rc2 = c2;

        if(c1 < 0){
            c1 = 0;
        }
        if(c2 >= w) {
            c2 = w-1;
        }

        int base = h/2;

//        std::cout << pos.x << '\t' <<  pos.y << '\t' << angle << std::endl;
        for(int c = c1; c <= c2; c++) {
            float ca = a1 - (float)(c-rc1)/(float)(rc2-rc1) * (a1-a2);

            float columnDistance = getDistance(Segment(v1, v2), Vector2f(0, 0), ca);

            if (columnDistance < zbuffer[c]){
                zbuffer[c] = columnDistance;
                columnDistance *= cosf(ca);
                float lh = (float)h / columnDistance;
                Wall* wall = &i;
                sf::Sprite* sp = &i.sprite;
                auto textureSize = wall->texture.getSize();

                float ea = a1 - (float)(c-rc1+1)/(float)(rc2-rc1) * (a1-a2);


//                std::cout << (getIntersectionPoint(Segment(v1, v2), Vector2f(0, 0), ca) - v1).getLength() << std::endl;
                float rl = (getIntersectionPoint(Segment(v1, v2), Vector2f(0, 0), ca) - v1).getLength() / (v2-v1).getLength() * (float)textureSize.x;
                float rr = (getIntersectionPoint(Segment(v1, v2), Vector2f(0, 0), ea) - v1).getLength() / (v2-v1).getLength() * (float)textureSize.x;


                if (!reversed){
                    sp->setTextureRect(sf::Rect<int>(ceilf(rl), 0, ceilf(rr - rl), textureSize.y));
                } else{
                    sp->setTextureRect(sf::Rect<int>(textureSize.x - rr, 0, rr - rl, textureSize.y));
                }
                sp->setScale(1.0f/(rr-rl), lh / ((float)textureSize.y));

                sp->setPosition((float)c, (float)base-lh/2);
                window->draw(*sp);

            }
        }
    }

    renderDebug(pos, angle);

    window->display();
}

void Drawer::renderDebug(Vector2f pos, float angle) {
    const float mw = 100;
    const float mh = 100;

    window->draw(generateRect(0, 0, (int)mw, (int)mh, sf::Color(100, 100, 100)));

    auto player = sf::CircleShape(5);
    player.setFillColor(sf::Color::Red);
    Vector2f omp  = TO_MAP_COORDS(pos);
    player.setPosition(omp.x - 5, omp.y - 5);
    window->draw(player);

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = omp;
    Vector2f l(10, 0);
    l.setAngle(angle);
    l = l + pos;
    line[1].position = TO_MAP_COORDS(l);

    window->draw(line);

    sf::VertexArray pols(sf::Lines, mapSize*2);

    for(int i = 0; i < mapSize; i++) {
        auto wp = map[i];
        pols[i*2].position = TO_MAP_COORDS(wp.segment.v1);
        pols[i*2+1].position = TO_MAP_COORDS(wp.segment.v2);
        for(int j = 0; j < 2; j++){
//            pols[i*2+j].color = wp.color;

        }
    }

    window->draw(pols);
}
Drawer::Drawer(sf::RenderWindow *w) : window(w) {
    this->w = w->getSize().x;
    this->h = w->getSize().y;

    zbuffer = new float[this->w];

}

Drawer::~Drawer() {
    delete zbuffer;
}

sf::VertexArray Drawer::generateRect(int x, int y, int w, int h, sf::Color color) {
    sf::VertexArray ret(sf::Quads, 4);
    ret[0].position = sf::Vector2f(x,y);
    ret[1].position = sf::Vector2f(x+w,y);
    ret[2].position = sf::Vector2f(x+w,y+h);
    ret[3].position = sf::Vector2f(x,y+h);
    for(int i =0; i < 4; i++) {
        ret[i].color = color;
    }

    return ret;
}

float Drawer::getDistance(Segment s, Vector2f pos, float angle) {
    return (getIntersectionPoint(s, pos, angle) - pos).getLength();


}


Vector2f Drawer::getIntersectionPoint(Segment s, Vector2f pos, float angle){
    float ao = s.v2.y - s.v1.y;
    float bo = s.v1.x - s.v2.x;
    float co = s.v2.x*s.v1.y - s.v1.x*s.v2.y;

    Vector2f adjv = Vector2f(0, 1);
    adjv.setAngle(angle);
    Segment r = Segment(pos, pos+adjv);

    float ar = r.v2.y - r.v1.y;
    float br = r.v1.x - r.v2.x;
    float cr = r.v2.x*r.v1.y - r.v1.x*r.v2.y;

    return Vector2f(-(cr*bo - co*br) / (ar*bo - ao*br), -(ar*co - ao*cr) / (ar*bo - ao * br));
}