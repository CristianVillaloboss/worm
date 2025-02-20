#include "worm.hpp"

Worm::Worm(int x, int y) {
    q.resize((x-2) * (y-2));
    head = 0;
    tail = 0;

}

std::pair<int,int> Worm::getHead() {
    return q.at(head);
}

std::pair<int, int> Worm::getTail() {
    return q.at(tail);
}


void Worm::addHead(std::pair<int, int> p) {
    int nxt = head + 1;
    if (head == q.size() -1)
        nxt =0;
    q.at(nxt) = p;
    head = nxt;
}

void Worm::removeTail() {
    int nxt = tail + 1;
    if (tail == q.size() - 1)
        nxt =0;
    tail = nxt;
}



