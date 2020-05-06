#include "Drawer.h"
#include <cmath>
#include <iostream>
#include <SDL2/SDL_ttf.h>

#define FOV M_PI/2

void Drawer::render(Vector2f pos, float angle) {
    SDL_SetRenderDrawColor(this->r, 0, 0, 0, 0);
    SDL_RenderClear(this->r);

    SDL_SetRenderDrawColor(this->r, 228, 0, 0, 0);
    float step = FOV / w;
    for (int col = 0; col < this->w; col++){
        float rayAngle = angle + (w - col - w/2)*step;
        float mindst = MAXFLOAT;
        for (int i = 0; i < mapSize; i++){
            float dst = getDistance(map[i], pos, rayAngle);
            if (dst < mindst)mindst = dst;
        }

        mindst *= cos(angle - rayAngle);

        int lh = h/2 * 1/mindst;

        int base = h/2;
        SDL_RenderDrawLine(this->r, col, base - lh, col, base+lh);
    }

    renderDebug();

    SDL_RenderPresent(this->r);
}

float Drawer::getDistance(Segment s, Vector2f pos, float angle) {
    float ko, mo, kr, mr;

    ko = (s.v1.y - s.v2.y) / (s.v1.x - s.v2.x);
    mo = s.v1.y - s.v1.x * ko;

    kr = tan(angle);
    mr = pos.y - pos.x*kr;

    float xi = (mr - mo) / (ko - kr);
    float yi = ko*xi + mo;

    if (((s.v1.x <= xi && xi <= s.v2.x) || (s.v1.x >= xi && xi >= s.v2.x)) &&
        ((s.v1.y <= yi && yi <= s.v2.y) || (s.v1.y >= yi && yi >= s.v2.y)) &&
        (abs((Vector2f(xi, yi) - pos).getAngle() - angle) < 0.01)){
        return sqrt(pow(xi - pos.x, 2) + pow(yi - pos.y, 2));
    }
    return MAXFLOAT;

}

Drawer::Drawer(SDL_Window *w) : window(w) {
    r = SDL_GetRenderer(w);
    SDL_GetWindowSize(w, &(this->w), &h);

    font = TTF_OpenFont("/home/ilya/.fonts/c/comic.ttf", 24);
//    std::cout << TTF_GetError() << std::endl;
//    std::cout << std::endl;
}



void Drawer::renderDebug() {
    SDL_SetRenderDrawColor(r, 50, 50, 50, 0);
    SDL_Rect bg = {0, 0, 100, 100};
    SDL_RenderFillRect(r, &bg);

    SDL_Color white = {255, 255, 255};

//    drawText(std::string("shit"), white, 0, 0);



}

Drawer::~Drawer() {
    TTF_CloseFont(font);
}

SDL_Texture *Drawer::drawText(std::string msg, SDL_Color &color, int tox, int toy) {
    auto surf = TTF_RenderText_Blended(font, msg.c_str(), color);
    auto texture = SDL_CreateTextureFromSurface(r, surf);
    int tw, th;

    SDL_QueryTexture(texture, nullptr, nullptr, &tw, &th);

    SDL_Rect srcRect = {0, 0, tw, th};
    SDL_Rect dstRect = {tox, toy, tw, th};

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    return texture;
}

