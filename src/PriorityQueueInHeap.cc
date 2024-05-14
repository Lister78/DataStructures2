#include "PriorityQueueInHeap.h"
#include <algorithm>
#include <stdexcept>

template<typename E, typename C>
void PriorityQueueInHeap<E, C>::heapifyDown(size_t idx) {
    size_t largest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;
    size_t n = heap.size();

    if (left < n && heap[left].second > heap[largest].second)
        largest = left;
    if (right < n && heap[right].second > heap[largest].second)
        largest = right;

    if (largest != idx) {
        std::swap(heap[idx], heap[largest]);
        heapifyDown(largest);
    }
}

template<typename E, typename C>
void PriorityQueueInHeap<E, C>::heapifyUp(size_t idx) {
    while (idx > 0 && heap[(idx - 1) / 2].second < heap[idx].second) {
        std::swap(heap[(idx - 1) / 2], heap[idx]);
        idx = (idx - 1) / 2;
    }
}

template<typename E, typename C>
PriorityQueueInHeap<E, C> PriorityQueueInHeap<E, C>::randomGenerate(int size, C minPriority, C maxPriority) {
    PriorityQueueInHeap<E, C> pq;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minPriority, maxPriority);

    for (int i = 0; i < size; ++i) {
        E elem = static_cast<E>(i);
        C pri = dist(gen);
        pq.insert(elem, pri);
    }
    return pq;
}

template<typename E, typename C>
void PriorityQueueInHeap<E, C>::insert(E elem, C p) {
    heap.push_back(std::make_pair(elem, p));
    heapifyUp(heap.size() - 1);
}

template<typename E, typename C>
bool PriorityQueueInHeap<E, C>::isEmpty() const {
    return heap.empty();
}

template<typename E, typename C>
E PriorityQueueInHeap<E, C>::peek() const {
    if (!isEmpty()) {
        return heap[0].first;
    }
    throw std::runtime_error("Heap is empty");
}

template<typename E, typename C>
void PriorityQueueInHeap<E, C>::extract_max() {
    if (!isEmpty()) {
        std::swap(heap[0], heap.back());
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    } else {
        throw std::runtime_error("Heap is empty");
    }
}

template<typename E, typename C>
int PriorityQueueInHeap<E, C>::size() const {
    return heap.size();
}

template<typename E, typename C>
void PriorityQueueInHeap<E, C>::modify_key(const E& element, C newPriority) {
    auto it = std::find_if(heap.begin(), heap.end(), [&](const std::pair<E, C>& item) {
        return item.first == element;
    });

    if (it != heap.end()) {
        C oldPriority = it->second;
        if (newPriority != oldPriority) {
            it->second = newPriority;
            int idx = std::distance(heap.begin(), it);
            if (newPriority < oldPriority) {
                heapifyUp(idx);
            } else {
                heapifyDown(idx); 
            }
        }
    }
}

template<typename E, typename C>
void PriorityQueueInHeap<E, C>::clear() {
    heap.clear();
}

template class PriorityQueueInHeap<int, int>;
