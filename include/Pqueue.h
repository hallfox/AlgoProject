#ifndef _CONTESTANT_HEAP_H
#define _CONTESTANT_HEAP_H

#include <string>

#include "Contestant.h"

class ContestantHeap
{
    public:
        ContestantHeap(int size);
        ~ContestantHeap();
        std::string findContestant(int id);
        std::string insertContestant(int id, int score);
        std::string eliminateWeakest();
        std::string earnPoints(int id, int points);
        std::string losePoints(int id, int points);
        std::string showContestants();
        std::string showHandles();
        std::string showLocation(int id);
        std::string crownWinner();
        bool isEmpty();
    private:
        Contestant* extractMin();
        void swap(int a, int b);
        Contestant** heap;
        int* handle;
        int heapSize;
        int heapCap;
        void heapify(int loc);
        static const int ROOT = 1;
};

#endif
