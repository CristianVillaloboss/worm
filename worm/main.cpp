#include <curses.h>
#include "getChar.hpp"
#include "screen.hpp"
#include "worm.hpp"
#include <string>
#include <vector>
#include <iostream>

void setupScreen(int rows, int columns) { //draws the screen border
    for (int i = 0; i < columns - 1; ++i) {
        move(1, i);
        addch('*');
        move(rows , i);
        addch('*');
    }
    for (int i = 1; i <= rows; ++i) {
        move(i, 0);
        addch('*');
        move(i, columns - 1);
        addch('*');
    }
}

//must have 2 arguments, row and column, will prompt at terminal
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " num1 num2" << std::endl;
        return 1;
    }

    int rows = std::atoi(argv[1]);
    int columns = std::atoi(argv[2]);

    if(rows < 9 || rows > 25) { //rows must be between 9 and 25!
        std::cout << "enter a value for rows between 9 and 25!";
        exit(5);
    }
    if(columns < 9 || columns > 80) { //columns must be between 9 and 80! inclusive!
        std::cout << "enter a value for rows between 9 and 25!";
        exit(5);
    }

    int currRow = ((rows - 2) / 2) + 1;
    int currColumn = ((columns - 2) / 2);
    int x = 0;
    int y = 0;
    int munchieValue = 0;
    int score = 0;
    ScreenDS myScreen = ScreenDS(rows, columns);
    myScreen.initializeScreen(rows, columns);

    initscr();
    curs_set(0);
    clear();
    noecho();
    cbreak();

    move(0, 0);
    addstr("Worm");
    setupScreen(rows, columns);
    move(currRow, currColumn);
    addch('@');

    int tailX;
    int tailY;
    int headX;
    int headY;
    std::pair<int, int> munchLoc = myScreen.getMunchie();
    x = munchLoc.first + 1; //adjusting curses to match 2d screen vector
    y = munchLoc.second;
    munchieValue = myScreen.getMunchieValue();
    std::string munchieValToStrin = std::to_string(munchieValue);
    move(x, y);
    addstr(munchieValToStrin.c_str());

    refresh();
    bool amGrowing;
    char get = ' ';

    while (!myScreen.checkCollision()) {
        move(currRow, currColumn);
        addch('o');

        if (get == 27) {
            mvcur(0, COLS - 1, LINES - 1, 0);
            clear();
            refresh();
            endwin();
            std::cout <<"You escaped the program since you pressed the esc key!! " << std::endl;
            exit(0);
        }

        if (get == 'w' || get == 'k') {
            currRow--;
            amGrowing = myScreen.isGrowing();
            std::pair<int, int> tailLocation = myScreen.getWorm().getTail();
            myScreen.setOccupiedCell(currRow - 1, currColumn);

            tailX = tailLocation.first + 1; //adjusting curses to match 2d screen vector since allignment is off
            tailY = tailLocation.second;
            if (!amGrowing) {
                move(tailX, tailY);
                addch(' ');
            }

            move(currRow, currColumn);
            addch('@');
            std::pair<int, int> headLocation = myScreen.getWorm().getHead();
            headX = headLocation.first + 1;
            headY = headLocation.second;
            move(headX, headY);
            addch('@');
        }
        else if (get == 's' || get == 'j') {
            currRow++;
            amGrowing = myScreen.isGrowing();
            std::pair<int, int> tailLocation = myScreen.getWorm().getTail();

            myScreen.setOccupiedCell(currRow - 1 , currColumn);
            tailX = tailLocation.first + 1;
            tailY = tailLocation.second;

            if (!amGrowing) {
                move(tailX, tailY);
                addch(' ');
            }

            move(currRow, currColumn);
            addch('@');
            std::pair<int, int> headLocation = myScreen.getWorm().getHead();
            headX = headLocation.first + 1;
            headY = headLocation.second;
            move(headX, headY);
            addch('@');
        }
        else if (get == 'a' || get == 'h') {
            currColumn--;
            amGrowing = myScreen.isGrowing();
            std::pair<int, int> tailLocation = myScreen.getWorm().getTail();
            myScreen.setOccupiedCell(currRow - 1, currColumn);

            tailX = tailLocation.first + 1;
            tailY = tailLocation.second;
            if (!amGrowing) {
                move(tailX, tailY);
                addch(' ');
            }

            move(currRow, currColumn);
            addch('@');
            std::pair<int, int> headLocation = myScreen.getWorm().getHead();
            headX = headLocation.first + 1;
            headY = headLocation.second;
            move(headX, headY);
            addch('@');
        }
        else if (get == 'd' || get == 'l') {
            currColumn++;
            amGrowing = myScreen.isGrowing();
            std::pair<int, int> tailLocation = myScreen.getWorm().getTail();

            myScreen.setOccupiedCell(currRow - 1 , currColumn);
            tailX = tailLocation.first + 1;
            tailY = tailLocation.second;

            if (!amGrowing) {
                move(tailX, tailY);
                addch(' ');
            }
            move(currRow, currColumn);
            addch('@');
            std::pair<int, int> headLocation = myScreen.getWorm().getHead();
            headX = headLocation.first + 1;
            headY = headLocation.second;
            move(headX, headY);
            addch('@');
        }

        move(headX, headY);
        addch('@');

        move(0, 30);
        addstr("Score ");
        score = myScreen.getTotalScore();
        std::string totalScore = std::to_string(score);
        move(0, 36);
        addstr(totalScore.c_str());
        std::pair<int, int> munchieLocation = myScreen.getMunchie();
        x = munchieLocation.first + 1;
        y = munchieLocation.second;
        munchieValue = myScreen.getMunchieValue();
        std::string munchieValToString = std::to_string(munchieValue);
        move(x, y);
        addstr(munchieValToString.c_str());

        move(0,0);
        addch('W');
        refresh();
        get = getChar();
    }

    mvcur(0, COLS - 1, LINES - 1, 0);
    clear();
    refresh();
    endwin();
    std::cout << "The worm died since it ran into something!" << std::endl;
    std::cout << "Your final score was:" << score << "!";
    return 0;
}
