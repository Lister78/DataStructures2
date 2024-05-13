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

    if (size == 0) {			//Przy dodawaniu do listy 1 elementu, wszytstkie wskazniku ustwiane, sa na 1 wezel
        head = node;
        tail = node;
        maxPriorityNode = node;
    } else {						//Jezeli lista ma wiecej niz 0 elementow, przed dodaniem sprawdzany jest priorytet dodawanego wezla oraz priorytet heada (head zawsze wskazuje na element z najwiekszym priorytetem)
        if (priority > head->priority) {
            node->next_value_ptr = head; //Jezeli priorytet dodwanego wezla jest wiekszy niz heada to wskaznik head jest przestawiany na nowy wezel, jezeli nie wezel trafia na taila
            head->prev_value_ptr = node;
            head = node;
        } else {
            tail->next_value_ptr = node;
            node->prev_value_ptr = tail;
            tail = node;
        }
        if (priority > maxPriorityNode->priority) {
            maxPriorityNode = node;			//Jezeli wartosc dodawanego wezla jest wieksza od najwiekszego dotychczasowego prioytetu, wskaznik na najwiekszy priorytet
        }
    }
    size++;
}

int LinkedList::get_size() {
    return size;			//Zwracanie rozmiaru
}

Node* LinkedList::peek() {
    return maxPriorityNode;			//Zwracanie najwiekszego priorytetu
}

Node* LinkedList::extract_max() {		//Funkcja Zwracajaca najwiekszy prio i usuwajca ten wezel
    if (maxPriorityNode == nullptr) {								//Jezeli kolejka jest pusta wyswietlany jest komunikat
        std::cout << "Kolejka jest pusta.\n";
        return nullptr;
    }

    Node* maxNode = maxPriorityNode;		
    if (maxNode == head) {		// Zachowuje węzeł o najwyższym priorytecie	
        head = head->next_value_ptr;	//Jezeli wezel z najwiekszym prio jest headem
        if (head != nullptr) {		//To wskaznik przesuwany jest na nastepny element
            head->prev_value_ptr = nullptr; //Sprawdzane jest czy lista nie byla pusta
        } else {
            tail = nullptr;
        }
    } else if (maxNode == tail) {	//Jezeli wezel o najwikszym prio jest tailem
        tail = tail->prev_value_ptr; //tail jest usuwany
        tail->next_value_ptr = nullptr;
    } else {
        maxNode->prev_value_ptr->next_value_ptr = maxNode->next_value_ptr; 
        maxNode->next_value_ptr->prev_value_ptr = maxNode->prev_value_ptr;//Jezeli wyzsze warunki sie nie spelnia to wezel o najwiekszym prio jest usuwany, a wskazinki sa odpowiedno przesuwane
    }j

    Node* curr = head;
    maxPriorityNode = head;
    while (curr != nullptr) {
        if (curr->priority > maxPriorityNode->priority) { //Petla przechodzi po liscie zaczynajac od heada i aktualizuje wskaznik na element o najwiekszym priorytecie po usunieciu wczesniejszego
            maxPriorityNode = curr;
        }
        curr = curr->next_value_ptr;
    }

    size--;
    return maxNode;//Zwracany jest najwiekszy priorytet a rozmiar zmniejszany
}

void LinkedList::modify_key(int looking_value, int new_prio) {
    Node* curr = head;
    while (curr != nullptr) {//Jezeli lista nie jest pusta
        if (curr->node_value == looking_value) { //a podana wartosc zgadza sie z wartoscia w danym wezle to priorytet jest zmieniany
            curr->priority = new_prio;
            return;
        }
        curr = curr->next_value_ptr;
    }
    std::cout << "Nie znaleziono elementu o wartości " << looking_value << std::endl; //Jezeli nie to wyswietlany jest odpowiedni komunikat
}

//Kod zostal znacznie zmieniony, sprawe ulatwilo dodanie jeszcze jednego wskaznika (na najwieksze prio) i kod zostal przepisany i uprosczony. We wczseniejszym zamysle najwiekszy priorytet mial zawsze wskazywac head co powodowalo wiele problemow i niezbedne bylo rozpatrywnie wielu przypadkow. Wczesniejszy kod byl ciezki do czytania(mozna sprawdzic commity na gicie)

