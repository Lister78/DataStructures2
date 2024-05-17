#include <iostream>
#include <vector>
#include "LinkedList.h"

// Konstruktor węzła
Node::Node() {
    node_value = 0; 
    priority = 0;  
    next_value_ptr = nullptr; 
    prev_value_ptr = nullptr;  
}

// Konstruktor listy LinkedList
LinkedList::LinkedList() {
    head = nullptr;  
    tail = nullptr;  
    size = 0;  
    maxPriorityNode = nullptr;  
}

// Metoda do wstawiania węzła do listy
void LinkedList::Insert(int value, int priority) {
    Node* node = new Node;  
    node->node_value = value; 
    node->priority = priority;  

    // Jeśli lista jest pusta, ustawienie wskaźnika na początek, koniec i węzeł o najwyższym priorytecie na nowy węzeł
    if (size == 0) {
        head = node;
        tail = node;
        maxPriorityNode = node;
    } else {
        // Jeśli priorytet nowego węzła jest większy niż priorytet pierwszego węzła, wstawienie go na początek
        if (priority > head->priority) {
            node->next_value_ptr = head;
            head->prev_value_ptr = node;
            head = node;
        } else {
            // W przeciwnym razie wstawienie go na koniec
            tail->next_value_ptr = node;
            node->prev_value_ptr = tail;
            tail = node;
        }
        // Jeśli priorytet nowego węzła jest większy niż priorytet obecnego węzła o najwyższym priorytecie, aktualizacja maxPriorityNode
        if (priority > maxPriorityNode->priority) {
            maxPriorityNode = node;
        }
    }
    size++;  // Zwiększenie rozmiaru listy
}

// Metoda do pobierania rozmiaru listy
int LinkedList::get_size() {
    return size;  
}

// Metoda do podglądania pierwszego węzła listy, czyli węzła o najwyższym priorytecie
Node* LinkedList::peek() {
    return head;  
}

// Metoda do wyodrębniania węzła o najwyższym priorytecie
Node* LinkedList::extract_max() {

    if (maxPriorityNode == nullptr) {
        std::cout << "Kolejka jest pusta.\n";
        return nullptr;
    }

    Node* maxNode = maxPriorityNode;  // Zapis węzeła o najwyższym priorytecie

    // Jeśli maxNode to pierwszy węzeł, aktualizacja pierwszego węzeła
    if (maxNode == head) {
        head = head->next_value_ptr;
        if (head != nullptr) {
            head->prev_value_ptr = nullptr;
        } else {
            tail = nullptr;
        }
    } else if (maxNode == tail) {  // Jeśli maxNode to ostatni węzeł, aktualizacja ostatniegp węzeła
        tail = tail->prev_value_ptr;
        tail->next_value_ptr = nullptr;
    } else {  // Jeśli maxNode jest w środku, aktualizacja następnego i poprzedniego węzeła
        maxNode->prev_value_ptr->next_value_ptr = maxNode->next_value_ptr;
        maxNode->next_value_ptr->prev_value_ptr = maxNode->prev_value_ptr;
    }

    // Znajdź nowy węzeł o najwyższym priorytecie
    Node* curr = head;
    maxPriorityNode = head;
    while (curr != nullptr) {
        if (curr->priority > maxPriorityNode->priority) {
            maxPriorityNode = curr;
        }
        curr = curr->next_value_ptr;
    }

    size--;  // Zmniejszenie rozmiaru listy
    return maxNode;  
}

// Metoda do modyfikacji priorytetu węzła
void LinkedList::modify_key(int looking_value, int new_prio) {
    Node* curr = head;  // Zacznij od początku listy
    while (curr != nullptr) {
        // Jeśli wartość obecnego węzła odpowiada looking_value, aktualizacja jego priorytet
        if (curr->node_value == looking_value) {
            curr->priority = new_prio;
            return;
        }
        curr = curr->next_value_ptr;  
    }

    std::cout << "Nie znaleziono elementu o wartości " << looking_value << std::endl;
}

// Metoda do przesunięcia węzła po zmodyfikowaniu jego priorytetu
void LinkedList::move_after_modify(Node* curr, int new_prio) {

}

// Metoda do czyszczenia listy
void LinkedList::clear() {

    while (head != nullptr) {
        Node* temp = head;
        head = head->next_value_ptr;
        delete temp;
    }
    tail = nullptr;  
    size = 0;  
    maxPriorityNode = nullptr;  
}
