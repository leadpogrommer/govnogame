#pragma once


#include <cmath>

#include <string>
#include <vector>
#include "MathUtil.h"
#include "Wall.h"
#include "Entity.h"
#include "Player.h"
#include <map>

#include <SFML/Graphics.hpp>

class Drawer {
public:
    explicit Drawer(sf::RenderWindow* w);
    ~Drawer();
    void render(Vector2f pos, float angle, std::map<uint16_t, Player> &entities);


    const static int mapSize = 7;
    Wall map[mapSize] = {Wall(Segment(-2, 5, 2, 2), "loh.jpeg"), Wall(Segment(-2, 3, 4, 3), "2.png"), Wall(Segment(0, 2, 2, 4), "1.png"),
                         Wall(Segment(-10,10,10,10), "res/bricks.jpg"),
                         Wall(Segment(10,10,10,-10), "res/bricks.jpg"),
                         Wall(Segment(10,-10,-10,-10), "res/bricks.jpg"),
                         Wall(Segment(-10,-10,-10,10), "res/bricks.jpg"),};
//    Wall map[mapSize] = {Wall(Segment(1, 1, 1, 4), "r.png"), Wall(Segment(1, 4, 4, 6), "g.png"), Wall(Segment(4, 6, 1, 1), "b.png"), Wall(Segment(0, 2, 4, 2), "1.png")};
//    Wall map[mapSize] = { Wall(Segment(-2, 3, 4, 3), "2.png")};
//    Wall map[mapSize] = {Wall(Segment(-2, 5, 2, 2), "1.png")};
//    Wall map[mapSize] = {Wall(Segment(-1, 1, 5, 4), "loh.jpeg")};

//    std::vector<Entity> entities = {Entity(Vector2f(-9, -9), 0, "res/dickman.png"),
//                                    Entity(Vector2f(5, 3), 0, "res/dickman.png"),
//                                    Entity(Vector2f(0, -1), 0, "res/dickman.png"),};


private:
    sf::RenderWindow* window;
    sf::Texture playerTexture;
    int w;
    int h;
    static sf::VertexArray generateRect(int x, int y, int w, int h, sf::Color color);

    float *zbuffer;

    void renderDebug(Vector2f, float);

    static float getDistance(Segment s, Vector2f pos, float angle);

    static Vector2f getIntersectionPoint(Segment s, Vector2f pos, float angle);

    float angleFromCol(int col);

    void renderWalls(Vector2f pos, float angle);

    void renderFloorAndCeiling(Vector2f pos, float angle);

    void renderEntities(Vector2f pos, float angle, std::map<uint16_t, Player> &es);

    float getMagickNum(Vector2f, Vector2f);
};




