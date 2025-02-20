#ifndef WORM_HPP
#define WORM_HPP

#include <iostream>
#include <queue>
#include <vector>

class Worm {
public:
    Worm(int, int);
    std::pair<int, int> getHead();
    std::pair<int, int> getTail();
    void addHead(std::pair<int, int>);
    void removeTail();
private:
    std::vector<std::pair<int, int> > q;
    int head;
    int tail;

};

#endif // WORM_HPP
