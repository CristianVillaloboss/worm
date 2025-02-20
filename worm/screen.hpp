#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <vector>
#include <iostream>
#include "worm.hpp"


class ScreenDS {
public:
    ScreenDS(int, int);
    void setFreeCell(int, int);
    void setOccupiedCell(int, int);
    int getTotalScore();
    std::pair<int, int> getMunchie();
    int getMunchieValue();
    bool isGrowing();
    Worm getWorm();
    std::pair<int, int> getRandomCell();
    int getRandomCellValue();
    void initializeScreen(int, int);
    bool checkCollision();



private:
    std::vector<std::pair<int, int> > freePool;
    std::vector<std::vector<int> > screen;
    int lastIndex;
    Worm wormBoy;
    bool collisionIndicator;
    int currMunchieValue;
    std::pair<int, int> currMunchieLoc;
    int totalMunch;
    int score = 0;


};


#endif // SCREEN_HPP
