#include "Drawer.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include "MathUtil.h"
#include <utility>



#define FOV (M_PI/2)


#define TO_MAP_COORDS(v) Vector2f(v.x + mw/2, -v.y + mh/2)



void Drawer::render(Vector2f pos, float angle) {
    window->clear(sf::Color::Black);

    std::fill(zbuffer, zbuffer+this->w, MAXFLOAT);
    sf::VertexArray lines(sf::Lines, w*2);

    for (int i = 0; i < mapSize; i++){
        Vector2f v1 = map[i].segment.v1 - pos;
        Vector2f v2 = map[i].segment.v2 - pos;

        float a1, a2;

        a1 = v1.getAngle();
        a2 = v2.getAngle();

        a1 -= angle;
        a2 -= angle;



        PREPARE_ANGLE(a1);
        PREPARE_ANGLE(a2);

        if((abs(a1) > FOV/2) && (abs(a2) > FOV/2))continue;

        if (a1 < a2){
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

        if(c1 < 0){
            d1 += ((d2-d1)/(c2-c1))*(-c1);
            c1 = 0;
        }
        if(c2 >= w){
            d2 += ((d2-d1)/(c2-c1))*(w-c2);
            c2 = w-1;
        }



        int base = h/2;

        for(int c = c1; c <= c2; c++){
            float cdst = d1 + (d2-d1)/(c2-c1)*(c-c1);
            if (cdst < zbuffer[c]){
                zbuffer[c] = cdst;
                int lh = h/2 * 1/cdst;
                lines[2*c].position = Vector2f(c,base-lh);
                lines[2*c+1].position = Vector2f(c,base+lh);
                lines[2*c].color = map[i].color;
                lines[2*c+1].color = map[i].color;
            }
        }

//        sf::VertexArray pol(sf::Quads, 4);
//        pol[0].position = Vector2f(c1, base - lh1);
//        pol[1].position = Vector2f(c1, base + lh1);
//        pol[2].position = Vector2f(c2, base + lh2);
//        pol[3].position = Vector2f(c2, base - lh2);
//
//        window->draw(pol);

    }


    window->draw(lines);

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

    for(int i = 0; i < mapSize; i++){
        auto wp = map[i];
        pols[i*2].position = TO_MAP_COORDS(wp.segment.v1);
        pols[i*2+1].position = TO_MAP_COORDS(wp.segment.v2);
        for(int j = 0; j < 2; j++){
            pols[i*2+j].color = wp.color;
        }
    }

    window->draw(pols);


    std::cout << pos.x << '\t' <<  pos.y << '\t' << angle << std::endl;
    window->display();
}



//void Drawer::render(Vector2f pos, float angle) {
//    window->clear(sf::Color::Black);
//
//    sf::VertexArray lines(sf::Lines, w*2);
//
//    float step = FOV / w;
//    for (int col = 0; col < this->w; col++){
//        float rayAngle = angle + (w - col - w/2)*step;
//        float mindst = MAXFLOAT;
//        for (int i = 0; i < mapSize; i++){
//            float dst = getDistance(map[i], pos, rayAngle);
//            if (dst < mindst)mindst = dst;
//        }
//
//        mindst *= cos(angle - rayAngle);
//
//        int lh = h/2 * 1/mindst;
//
//        int base = h/2;
//
//        lines[col*2].position=sf::Vector2f(col, base-lh);
//        lines[col*2+1].position=sf::Vector2f(col, base+lh);
//    }
//
//
//    window->draw(lines);
//
//    window->display();
//}

//float Drawer::getDistance(Segment s, Vector2f pos, float angle) {
//    float ko, mo, kr, mr;
//
//    ko = (s.v1.y - s.v2.y) / (s.v1.x - s.v2.x);
//    mo = s.v1.y - s.v1.x * ko;
//
//    kr = tan(angle);
//    mr = pos.y - pos.x*kr;
//
//    float xi = (mr - mo) / (ko - kr);
//    float yi = ko*xi + mo;
//
//    if (((s.v1.x <= xi && xi <= s.v2.x) || (s.v1.x >= xi && xi >= s.v2.x)) &&
//        ((s.v1.y <= yi && yi <= s.v2.y) || (s.v1.y >= yi && yi >= s.v2.y)) &&
//        (abs((Vector2f(xi, yi) - pos).getAngle() - angle) < 0.01)){
//        return sqrt(pow(xi - pos.x, 2) + pow(yi - pos.y, 2));
//    }
//    return MAXFLOAT;
//
//}

Drawer::Drawer(sf::RenderWindow *w) : window(w) {
    this->w = w->getSize().x;
    this->h = w->getSize().y;

    zbuffer = new float[this->w];

//    std::cout << TTF_GetError() << std::endl;
//    std::cout << std::endl;
}



//void Drawer::renderDebug() {
//    SDL_SetRenderDrawColor(r, 50, 50, 50, 0);
//    SDL_Rect bg = {0, 0, 100, 100};
//    SDL_RenderFillRect(r, &bg);
//
//    SDL_Color white = {255, 255, 255};
//
////    drawText(std::string("shit"), white, 0, 0);
//
//
//
//}

Drawer::~Drawer() {
}

sf::VertexArray Drawer::generateRect(int x, int y, int w, int h, sf::Color color) {
    sf::VertexArray ret(sf::Quads, 4);
    ret[0].position = sf::Vector2f(x,y);
    ret[1].position = sf::Vector2f(x+w,y);
    ret[2].position = sf::Vector2f(x+w,y+h);
    ret[3].position = sf::Vector2f(x,y+h);
    for(int i =0; i < 4; i++){
        ret[i].color = color;
    }

    return ret;
}



//SDL_Texture *Drawer::drawText(std::string msg, SDL_Color &color, int tox, int toy) {
//    auto surf = TTF_RenderText_Blended(font, msg.c_str(), color);
//    auto texture = SDL_CreateTextureFromSurface(r, surf);
//    int tw, th;
//
//    SDL_QueryTexture(texture, nullptr, nullptr, &tw, &th);
//
//    SDL_Rect srcRect = {0, 0, tw, th};
//    SDL_Rect dstRect = {tox, toy, tw, th};
//
//    SDL_RenderCopy(r, texture, &srcRect, &dstRect);
//    SDL_FreeSurface(surf);
//    SDL_DestroyTexture(texture);
//    return texture;
//}

