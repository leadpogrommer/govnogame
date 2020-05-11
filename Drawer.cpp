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

void Drawer::renderWalls(Vector2f pos, float angle) {

    std::fill(zbuffer, zbuffer+this->w, MAXFLOAT);

    for (auto & i : map) {
        Vector2f v1 = i.segment.v1 - pos;
        Vector2f v2 = i.segment.v2 - pos;

        bool reversed = false;

        float a1, a2;

        a1 = v1.getAngle();
        a2 = v2.getAngle();

        a1 -= angle;
        a2 -= angle;

        PREPARE_ANGLE(a1);
        PREPARE_ANGLE(a2);

        if((std::abs(a1) > M_PI_2) && (std::abs(a2) > M_PI_2)) continue;



        v1.setAngle(a1);
        v2.setAngle(a2);


        if (a1 < a2){
            reversed = true;
            std::swap(a1, a2);
            std::swap(v1, v2);
        }

        float magickNum = getMagickNum(v1, v2);
        if(magickNum >0 ){
            reversed = !reversed;
            std::swap(a1, a2);
            std::swap(v1, v2);
            if(a1 < -M_PI_2)a1 += 2*M_PI;
            if(a2 > M_PI_2)a2 -= 2*M_PI;
        }





        int c1, c2;


        if(a1 >= M_PI_2){
            c1=0;
        }else{
            c1 = w/2 - (w/2)*tan(a1)/tan(FOV/2);
        }

        if(a2 <=-M_PI_2){
            c2 = w-1;
        }else{
            c2 = w/2 - (w/2)*tan(a2)/tan(FOV/2);
        }

        if(c1 < 0){
            c1 = 0;
        }
        if(c2 >= w) {
            c2 = w-1;
        }

        int base = h/2;


        for(int c = c1; c <= c2; c++) {
            float ca = angleFromCol(c);

            float columnDistance = getDistance(Segment(v1, v2), Vector2f(0, 0), ca);

            if (columnDistance < zbuffer[c]){
                zbuffer[c] = columnDistance;
                columnDistance *= cosf(ca);
                float lh = (float)h / columnDistance;
                Wall* wall = &i;
                sf::Sprite* sp = &i.sprite;
                auto textureSize = wall->texture.getSize();

                float ea = angleFromCol(c+1);

                float rl = (getIntersectionPoint(Segment(v1, v2), Vector2f(0, 0), ca) - v1).getLength() / (v2-v1).getLength() * (float)textureSize.x;
                float rr = (getIntersectionPoint(Segment(v1, v2), Vector2f(0, 0), ea) - v1).getLength() / (v2-v1).getLength() * (float)textureSize.x;


                if (!reversed){
                    sp->setTextureRect(sf::Rect<int>(ceilf(rl), 0, ceilf(rr - rl), textureSize.y));
                } else{
                    sp->setTextureRect(sf::Rect<int>(textureSize.x - rr, 0, ceilf(rr - rl), textureSize.y));
                }
                sp->setScale(1.0f/(rr-rl), lh / ((float)textureSize.y));

                sp->setPosition((float)c, (float)base-lh/2);
                window->draw(*sp);

            }
        }
    }
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

    playerTexture.loadFromFile("res/dickman.png");

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

float Drawer::angleFromCol(int c) {
    return atan(tanf(FOV/2)*(window->getSize().x/2.0 - c ) / (window->getSize().x / 2.0)) ;
}

void Drawer::renderFloorAndCeiling(Vector2f pos, float angle) {
    window->draw(generateRect(0, 0, w, h/2, sf::Color::White));
    window->draw(generateRect(0, h/2, w, h/2, sf::Color(0xdc, 0x55, 0x39)));

}

void Drawer::render(Vector2f pos, float angle, std::map<uint16_t, Player> &entities) {
    renderFloorAndCeiling(pos, angle);
    renderWalls(pos, angle);
    renderEntities(pos, angle, entities);
    renderDebug(pos, angle);

    window->display();
}

float Drawer::getMagickNum(Vector2f v1, Vector2f v2) {
    Vector2f c(0, 0);
    return (v2.x-v1.x)*(c.y-v2.y) - (v2.y-v1.y)*(c.x-v2.x);

}

void Drawer::renderEntities(Vector2f pos, float angle, std::map<uint16_t, Player> &es) {
    std::vector<Player> entities;

    for(auto & e : es){
        entities.push_back(e.second);
    }

    std::sort(entities.begin(), entities.end(), [&](const Entity &a, const Entity &b)-> bool{
        return (a.pos - pos).getLength() >= (b.pos - pos).getLength();
    });

    for(auto const& e: entities){
        Vector2f v = e.position - pos;
        float a = v.getAngle() - angle;
        PREPARE_ANGLE(a);

        if(std::abs(a) > M_PI_2)continue;

        v.setAngle(a);


        float c = w/2 - (w/2)*tan(a)/tan(FOV/2);

        if(c < 0 or c > w-1)continue;

        sf::Sprite sp;
        sp.setTexture(playerTexture);
        auto textureSize = playerTexture.getSize();

        float distance = v.getLength();
        distance*=cosf(a);
        if(zbuffer[(int)c] < distance)continue;


        sp.setOrigin(playerTexture.getSize().x / 2,playerTexture.getSize().y/2);

        float coeff = (1/distance) * ((float)h/textureSize.y);
        sp.scale(coeff, coeff);
        sp.setPosition(c, (float)h/2);

        window->draw(sp);


    }



}
