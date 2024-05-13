#include <iostream>
#include <vector>
#include "LinkedList.h"

Node::Node() {
    node_value = 0;
    priority = 0;
    next_value_ptr = nullptr;
    prev_value_ptr = nullptr;
}

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
    maxPriorityNode = nullptr;
}

void LinkedList::Insert(int value, int priority) {
    Node* node = new Node;
    node->node_value = value;
    node->priority = priority;

    if (size == 0) {
        head = node;
        tail = node;
        maxPriorityNode = node;
    } else {
        if (priority > head->priority) {
            node->next_value_ptr = head;
            head->prev_value_ptr = node;
            head = node;
        } else {
            tail->next_value_ptr = node;
            node->prev_value_ptr = tail;
            tail = node;
        }
        if (priority > maxPriorityNode->priority) {
            maxPriorityNode = node;
        }
    }
    size++;
}

int LinkedList::get_size() {
    return size;
}

Node* LinkedList::peek() {
    return head;
}

Node* LinkedList::extract_max() {
    if (maxPriorityNode == nullptr) {
        std::cout << "Kolejka jest pusta.\n";
        return nullptr;
    }

    Node* maxNode = maxPriorityNode;
    if (maxNode == head) {
        head = head->next_value_ptr;
        if (head != nullptr) {
            head->prev_value_ptr = nullptr;
        } else {
            tail = nullptr;
        }
    } else if (maxNode == tail) {
        tail = tail->prev_value_ptr;
        tail->next_value_ptr = nullptr;
    } else {
        maxNode->prev_value_ptr->next_value_ptr = maxNode->next_value_ptr;
        maxNode->next_value_ptr->prev_value_ptr = maxNode->prev_value_ptr;
    }

    Node* curr = head;
    maxPriorityNode = head;
    while (curr != nullptr) {
        if (curr->priority > maxPriorityNode->priority) {
            maxPriorityNode = curr;
        }
        curr = curr->next_value_ptr;
    }

    size--;
    return maxNode;
}

void LinkedList::modify_key(int looking_value, int new_prio) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->node_value == looking_value) {
            curr->priority = new_prio;
            return;
        }
        curr = curr->next_value_ptr;
    }
    std::cout << "Nie znaleziono elementu o wartości " << looking_value << std::endl;
}

void LinkedList::move_after_modify(Node* curr, int new_prio) {
}
