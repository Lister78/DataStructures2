// Metoda do przemieszczania elementu w dół kopca
template<typename E, typename C>
void PriorityQueueInHeap<E, C>::heapifyDown(size_t idx) {
    size_t largest = idx;  
    size_t left = 2 * idx + 1;  
    size_t right = 2 * idx + 2;  
    size_t n = heap.size();  

    // Sprawdzanie, czy lewe dziecko jest większe od bieżącego elementu
    if (left < n && heap[left].second > heap[largest].second)
        largest = left;
    // Sprawdzanie, czy prawe dziecko jest większe od bieżącego elementu
    if (right < n && heap[right].second > heap[largest].second)
        largest = right;

    // Jeśli największy element nie jest bieżącym elementem, zamiana miejscami
    if (largest != idx) {
        std::swap(heap[idx], heap[largest]);
        heapifyDown(largest);  
    }
}

// Metoda do przemieszczania elementu w górę kopca
template<typename E, typename C>
void PriorityQueueInHeap<E, C>::heapifyUp(size_t idx) {
    // Jeśli bieżący element jest większy od jego rodzica, zamieniane są miejscami
    while (idx > 0 && heap[(idx - 1) / 2].second < heap[idx].second) {
        std::swap(heap[(idx - 1) / 2], heap[idx]);
        idx = (idx - 1) / 2;  // Aktualizacja indeksu na indeks rodzica
    }
}

// Metoda do generowania losowej kolejki priorytetowej
template<typename E, typename C>
PriorityQueueInHeap<E, C> PriorityQueueInHeap<E, C>::randomGenerate(int size, C minPriority, C maxPriority) {
    PriorityQueueInHeap<E, C> pq;  // Tworzenie nowej kolejki priorytetowej
    std::random_device rd;  // Generownaie losowych liczby
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minPriority, maxPriority);  // Ustalanie zakresu losowych liczb

    // Wstawianie do kolejki priorytetowej losowych elementów
    for (int i = 0; i < size; ++i) {
        E elem = static_cast<E>(i);
        C pri = dist(gen);
        pq.insert(elem, pri);
    }
    return pq;
}

// Metoda do wstawiania elementu do kolejki priorytetowej
template<typename E, typename C>
void PriorityQueueInHeap<E, C>::insert(E elem, C p) {
    heap.push_back(std::make_pair(elem, p));  // Wstawianie elementu do kopca
    heapifyUp(heap.size() - 1);  
}

// Metoda do sprawdzania, czy kolejka priorytetowa jest pusta
template<typename E, typename C>
bool PriorityQueueInHeap<E, C>::isEmpty() const {
    return heap.empty();
}

// Metoda do podglądania najwyższego elementu w kolejce priorytetowej
template<typename E, typename C>
E PriorityQueueInHeap<E, C>::peek() const {
    if (!isEmpty()) {
        return heap[0].first;  // Zwrócenie najwyższego elementu
    }
    throw std::runtime_error("Heap is empty"); 
}

// Metoda do usuwania najwyższego elementu z kolejki priorytetowej
template<typename E, typename C>
void PriorityQueueInHeap<E, C>::extract_max() {
    if (!isEmpty()) {
        std::swap(heap[0], heap.back());  // Zamiana miejscami: najwyższy element z ostatnim elementem
        heap.pop_back();  // Usunięcie ostatniego elementu
        if (!heap.empty()) {
            heapifyDown(0);  
        }
    } else {
        throw std::runtime_error("Heap is empty");  
    }
}

// Metoda do pobierania rozmiaru kolejki priorytetowej
template<typename E, typename C>
int PriorityQueueInHeap<E, C>::size() const {
    return heap.size();
}

// Metoda do modyfikacji priorytetu elementu
template<typename E, typename C>
void PriorityQueueInHeap<E, C>::modify_key(const E& element, C newPriority) {
    // Szukanie elementu w kopcu
    auto it = std::find_if(heap.begin(), heap.end(), [&](const std::pair<E, C>& item) {
        return item.first == element;
    });

    // Jeśli element został znaleziony, modyfikowany jest jego priorytet
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

// Metoda do czyszczenia kolejki priorytetowej
template<typename E, typename C>
void PriorityQueueInHeap<E, C>::clear() {
    heap.clear();
}


template class PriorityQueueInHeap<int, int>;  
