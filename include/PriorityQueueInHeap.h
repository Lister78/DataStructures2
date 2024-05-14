#ifndef PRIORITY_QUEUE_IN_HEAP_H
#define PRIORITY_QUEUE_IN_HEAP_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <functional>

template<typename E, typename C>
class PriorityQueueInHeap {
private:
    std::vector<std::pair<E, C>> heap;

    void heapifyDown(size_t idx);
    void heapifyUp(size_t idx);

public:
    static PriorityQueueInHeap<E, C> randomGenerate(int size, C minPriority, C maxPriority);

    void insert(E elem, C p);
    bool isEmpty() const;
    E peek() const;
    void extract_max();
    int size() const;
    void modify_key(const E& element, C newPriority);
    void clear();
};

#endif // PRIORITY_QUEUE_IN_HEAP_H
