#include "Drawer.h"
#include <cmath>
#include <iostream>
#include "MathUtil.h"
#include <utility>

#define FOV (M_PI/2)

#define TO_MAP_COORDS(v) Vector2f(v.x + mw/2, -v.y + mh/2)

void Drawer::render(Vector2f pos, float angle) {
    window->clear(sf::Color::Black);

    std::fill(zbuffer, zbuffer+this->w, MAXFLOAT);

    for (int i = 0; i < mapSize; i++) {
        Vector2f v1 = map[i].segment.v1 - pos;
        Vector2f v2 = map[i].segment.v2 - pos;

        float a1, a2;

        a1 = v1.getAngle();
        a2 = v2.getAngle();

        a1 -= angle;
        a2 -= angle;

        PREPARE_ANGLE(a1);
        PREPARE_ANGLE(a2);

        if((abs(a1) > FOV/2) && (abs(a2) > FOV/2)) continue;


        bool reversed = false;

        if (a1 < a2){
            reversed = true;
            std::swap(a1, a2);
            std::swap(v1, v2);
        }

        v1.setAngle(a1);
        v2.setAngle(a2);


        int c1, c2;
        float d1, d2;

        c1 = (-(a1-(FOV/2))/FOV)*w;
        c2 = (-(a2-(FOV/2))/FOV)*w;

        d1 = v1.getLength();
        d2 = v2.getLength();

//        d1 *= cos(a1);
//        d2 *= cos(a2);

        int rc1 = c1;
        int rc2 = c2;

        if(c1 < 0){
//            d1 += ((d2-d1)/(c2-c1))*(-c1);
            c1 = 0;
        }
        if(c2 >= w) {
//            d2 += ((d2-d1)/(c2-c1))*(w-c2);
            c2 = w-1;
        }

        int base = h/2;

        std::cout << pos.x << '\t' <<  pos.y << '\t' << angle << std::endl;
        for(int c = c1; c <= c2; c++) {

//            Vector2f clvec = v2-v1;
//            clvec.scale((float)(c-rc1)/(float)(rc2-rc1));
//            Vector2f nvect = v1 + clvec;

            float completness = (float)(c-rc1)/(float)(rc2-rc1);
            Vector2f nvect = v1*completness + v2*(1.0-completness);


            float cdst = nvect.getLength();


            if (cdst <  zbuffer[c]){
                zbuffer[c] = cdst;
                float lh = h/cdst;
                Wall* wall = &map[i];
                sf::Sprite* sp = &map[i].sprite;
                auto tsize = wall->texture.getSize();
                float rl = ((float)tsize.x)/(rc2-rc1)*(c-rc1);
                float rr = ((float)tsize.x)/(rc2-rc1)*(c-rc1 + 1);
                if (!reversed){
                    sp->setTextureRect(sf::Rect<int>(rl, 0, rr - rl, tsize.y));
                } else{
                    sp->setTextureRect(sf::Rect<int>(tsize.x - rr, 0, rr - rl, tsize.y));
                }
                sp->setScale(1.0/(rr-rl), ((float)lh)/((float)tsize.y));

                sp->setPosition(c, base-lh/2);
                window->draw(*sp);

            }
        }
    }
    window->display();
}

void Drawer::renderDebug(Vector2f pos, float angle) {
    const float mw = 100;
    const float mh = 100;

    window->draw(generateRect(0, 0, mw, mh, sf::Color(100, 100, 100)));

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

    std::cout << pos.x << '\t' <<  pos.y << '\t' << angle << std::endl;
    window->display();
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
