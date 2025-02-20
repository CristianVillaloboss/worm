#include "screen.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

ScreenDS::ScreenDS(int a, int b) : wormBoy(a, b) {
    freePool.resize((a - 1) * (b - 1));
    screen.resize(a, std::vector<int>(b));
    collisionIndicator = false;
    lastIndex = 0;
    totalMunch = 0;
    score = 0;

}
int ScreenDS::getMunchieValue() {
    return currMunchieValue;
}

std::pair<int, int> ScreenDS::getMunchie() {
    return currMunchieLoc;
}

Worm ScreenDS::getWorm() {
    return wormBoy;
}

bool ScreenDS::isGrowing() {
    return totalMunch > 0;
}

int ScreenDS::getTotalScore() {
    return score;
}

void ScreenDS::setFreeCell(int n, int m) {
    freePool[lastIndex] = wormBoy.getTail();
    screen[wormBoy.getTail().first][wormBoy.getTail().second] = lastIndex;
    wormBoy.removeTail();
}

void ScreenDS::setOccupiedCell(int r, int c) {
    if (screen[r][c] < 0) {
        collisionIndicator = true;
        return;
    }
    int cell = screen[r][c];
    screen[freePool[lastIndex].first][freePool[lastIndex].second] = screen[r][c];
    screen[r][c] = -1;
    std::pair<int, int> npair = freePool[cell];
    wormBoy.addHead(npair);
    freePool[cell] = freePool[lastIndex];
    if (totalMunch == 0 ) {
        setFreeCell(wormBoy.getTail().first, wormBoy.getTail().second);
    } else {
        lastIndex--;
        totalMunch--;
    }

    if (screen[r][c] == screen[currMunchieLoc.first][currMunchieLoc.second]) {
        totalMunch += currMunchieValue;
        score += currMunchieValue;
        currMunchieValue = 0;
    }

    if (currMunchieValue == 0) {
        currMunchieValue = getRandomCellValue();
        currMunchieLoc = getRandomCell();
    }
}

std::pair<int, int> ScreenDS::getRandomCell() {
    int rn = rand() % lastIndex;
    return freePool[rn];
}

bool ScreenDS::checkCollision() {
    return collisionIndicator;
}

int ScreenDS::getRandomCellValue() {
    return rand() % 9 + 1;
}

void ScreenDS::initializeScreen(int row, int col) {
    int count = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
                screen[i][j] = -1;
            else {
                screen[i][j] = count;
                freePool[count].first = i;
                freePool[count].second = j;
                lastIndex = count;
                count++;
            }
        }
    }

    int cell = screen[(row - 2) / 2][(col - 2) / 2];
    screen[freePool[lastIndex].first][freePool[lastIndex].second] = screen[(row - 2) / 2][(col - 2) / 2];
    screen[(row - 2) / 2][(col - 2) / 2] = -1;
    std::pair<int, int> npair = freePool[cell];
    wormBoy.addHead(npair);
    wormBoy.removeTail();
    freePool[cell] = freePool[lastIndex];
    lastIndex--;

    currMunchieValue = getRandomCellValue();
    currMunchieLoc = getRandomCell();
}


