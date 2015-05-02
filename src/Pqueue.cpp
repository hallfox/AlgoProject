#include <string>
#include <sstream>
#include <iostream>

#include "ContestantHeap.h"

ContestantHeap::ContestantHeap(int size) 
{
    //apparently we hate zero based indexing so don't use it
    heapCap = size + 1;
    heapSize = 1;
    heap = new Contestant*[heapCap];
    handle = new int[heapCap];

    for (int i = 0; i < heapCap; i++)
    {
        heap[i] = nullptr;
        handle[i] = -1;
    }
}
ContestantHeap::~ContestantHeap()
{
    for (int i = 0; i < heapCap; i++)
    {
        if (heap[i] != nullptr) delete heap[i];
    }
    delete[] heap;
    delete[] handle;
}

std::string ContestantHeap::findContestant(int id)
{
    std::stringstream sstm;
    sstm << "Contestant <" << id << "> ";

    if (handle[id] == -1)
    {
        sstm << "is not in the extended heap.\n";
    }
    else
    {
        sstm << "is in the extended heap with score <" <<  heap[handle[id]]->getScore() << ">.\n";
    }

    return sstm.str();
}

std::string ContestantHeap::insertContestant(int id, int score)
{
    std::stringstream sstm;
    sstm << "Contestant <" << id << "> ";

    if (heapSize >= heapCap)
    {
        sstm << "could not be inserted because the extended heap is full.\n";
    }
    else if (handle[id] != -1)
    {
        sstm << "is already in the extended heap: cannot insert.\n";
    }
    else
    {
        Contestant* cont = new Contestant(id, score);
        heap[heapSize] = cont;
        handle[id] = heapSize;

        //new element should swap with its parents until the heap
        //property is satisfied; assumes that heap already satisfies
        //the heap property
        for (int i = heapSize; i != ROOT && 
                heap[i/2]->getScore() > heap[i]->getScore(); i /= 2)
        {
            swap(i, i/2);
        }
        heapSize++;
        sstm << "inserted with initial score <" << score << ">.\n";
    }

	return sstm.str();
}

std::string ContestantHeap::eliminateWeakest()
{
    std::stringstream sstm;
    
    if (isEmpty())
    {
       sstm << "No contestant can be eliminated since the extended heap is empty.\n"; 
    }
    else
    {
        //DELETE LOSER, THEY'RE STILL FLOATING AROUND
        Contestant* loser = extractMin();
        int loserId = loser->getId(); 
        int loserScore = loser->getScore();
        sstm << "Contestant <" << loserId << "> with current lowest score <" << loserScore << "> eliminated.\n";
        delete loser;
    }
	return sstm.str();
}

std::string ContestantHeap::earnPoints(int id, int points)
{
    std::stringstream sstm;

    sstm << "Contestant <" << id << ">";
    int cont = handle[id];
    if (cont >= 0)
    {
        heap[cont]->setScore(heap[cont]->getScore() + points);
        heapify(cont);
        sstm << "'s score increased by <" << points << "> points to <" 
            << heap[cont]->getScore() << ">.\n";
    }
    else
    {
       sstm << " is not in the extended heap.\n"; 
    }
	return sstm.str();
}

std::string ContestantHeap::losePoints(int id, int points)
{
    std::stringstream sstm;

    sstm << "Contestant <" << id << ">";
    int cont = handle[id];
    if (cont >= 0)
    {
        heap[cont]->setScore(heap[cont]->getScore() - points);
        for (int i = id; i != ROOT && 
                heap[i/2]->getScore() > heap[i]->getScore(); i /= 2)
        {
            swap(i, i/2);
        }
        sstm << "'s score decreased by <" << points << "> points to <" 
            << heap[cont]->getScore() << ">.\n";
    }
    else
    {
       sstm << " is not in the extended heap.\n"; 
    }
	return sstm.str();
}

std::string ContestantHeap::showContestants()
{
    std::stringstream sstm;

    for (int i = 1; i < heapCap; i++)
    {
        if (handle[i] >= 0)
        {
            sstm << "Contestant <" << i << "> in extended heap location <" << 
                handle[i] << "> with score <" << heap[handle[i]]->getScore() << ">.\n";
        }
    }
	return sstm.str();
}

std::string ContestantHeap::showHandles()
{
    std::stringstream sstm;

    for (int i = 1; i < heapCap; i++)
    {
        sstm << showLocation(i);
    }
	return sstm.str();
}

std::string ContestantHeap::showLocation(int id)
{
    std::stringstream sstm;

    if (handle[id] >= 0)
    {
        sstm << "Contestant <" << id << "> in extended heap location <" << handle[id] << ">.\n";
    }
    else
    {
        sstm << "There is no Contestant <" << id << "> in the extended heap: handle[<" << id << ">] = -1.\n";
    }
	return sstm.str();
}

std::string ContestantHeap::crownWinner()
{
    std::stringstream sstm;

    while (heapSize > ROOT + 1)
    {
        Contestant* loser = extractMin();
        delete loser;
    }
    
    Contestant* winner = extractMin();
    sstm << "Contestant <" << winner->getId() << "> wins with score <" << winner->getScore() << ">!\n";
    delete winner;
	return sstm.str();
}

bool ContestantHeap::isEmpty()
{
    return heapSize <= ROOT;
}

//HEY DELETE WHAT THIS GUY RETURNS
//IF YOU TRULY LOVE THEM YOU'LL SET THEM FREE
//FOR THE LOVE OF VALGRIND FREE THEM
Contestant* ContestantHeap::extractMin()
{
    Contestant* min = heap[ROOT];

    heapSize -= 1;
    swap(ROOT, heapSize); 
    heap[heapSize] = nullptr;
    handle[min->getId()] = -1;

    heapify(ROOT);

    return min;
}

void ContestantHeap::swap(int a, int b)
{
    Contestant* t = heap[a];
    heap[a] = heap[b];
    heap[b] = t;
    if (heap[a] != nullptr) handle[heap[a]->getId()] = a;
    if (heap[b] != nullptr) handle[heap[b]->getId()] = b;
}

void ContestantHeap::heapify(int loc)
{
    int i = loc;
    int smallest = loc;
    while (i < heapSize)
    {
        smallest = i;

        int left = i * 2;
        int right = left + 1;

        if (left < heapSize && heap[left] != nullptr && 
                heap[left]->getScore() < heap[smallest]->getScore())
        {
            smallest = left;
        }
        if (right < heapSize && heap[right] != nullptr && 
                heap[right]->getScore() < heap[smallest]->getScore())
        {
            smallest = right;
        }
        if (smallest == i)
        {   
            break;
        }
        swap(smallest, i);
        i = smallest;
    }
}
