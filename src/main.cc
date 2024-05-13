#include <iostream>
#include <cstdlib> 
#include "LinkedList.h"

int main() {
    int choice;
    LinkedList Lista;

    while (1) {
        std::cout << "Wybierz strukturę:\n1. Lista wiązana\n2. Kopiec\n";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                while (1) {
                    std::cout << "1. Dodaj element\n"
                                 "2. Usuń i zwróć element o największym priorytecie\n"
                                 "3. Zwróć element o największym priorytecie\n"
                                 "4. Zmień priorytet\n"
                                 "5. Zwróć rozmiar\n"
                                 "6. Wyjdź\n"
                                 "7. Dodaj losowe elementy\n"
                                 "8. Usuń i zwróć wiele elementów\n";

                    std::cin >> choice;

                    switch (choice) {
                        case 1: {
                            int value, priority;
                            std::cout << "Podaj wartość: ";
                            std::cin >> value;
                            std::cout << "Podaj priorytet: ";
                            std::cin >> priority;
                            Lista.Insert(value, priority);
                            break;
                        }
                        case 2: {
                            Node* maxNode = Lista.extract_max();
                            if (maxNode != nullptr) {
                                std::cout << "Usunięty element o największym priorytecie: "
                                          << maxNode->node_value << " (priorytet: " << maxNode->priority << ")\n";
                                delete maxNode;
                            } else {
                                std::cout << "Lista jest pusta.\n";
                            }
                            break;
                        }
                        case 3: {
                            Node* maxNode = Lista.peek();
                            if (maxNode != nullptr) {
                                std::cout << "Element o największym priorytecie: "
                                          << maxNode->node_value << " (priorytet: " << maxNode->priority << ")\n";
                            } else {
                                std::cout << "Lista jest pusta.\n";
                            }
                            break;
                        }
                        case 4: {
                            int value, newPriority;
                            std::cout << "Podaj wartość elementu do zmiany priorytetu: ";
                            std::cin >> value;
                            std::cout << "Podaj nowy priorytet: ";
                            std::cin >> newPriority;
                            Lista.modify_key(value, newPriority);
                            break;
                        }
                        case 5: {
                            std::cout << "Rozmiar listy: " << Lista.get_size() << "\n";
                            break;
                        }
                        case 6: {
                            break; // Wyjście z wewnętrznej pętli
                        }
                        case 7: {
                            int numElements;
                            std::cout << "Podaj liczbę losowych elementów do dodania: ";
                            std::cin >> numElements;
                            for (int i = 0; i < numElements; ++i) {
                                int value = rand() % 10000;
                                int priority = rand() % 15000; 
                                Lista.Insert(value, priority);
                            }
                            std::cout << "Dodano losowe elementy.\n";
                            break;
                        }
                        case 8: {
                            int numElements;
                            std::cout << "Podaj liczbę elementów do usunięcia: ";
                            std::cin >> numElements;
                            std::cout << "Usunięte elementy o największym priorytecie:\n";
                            for (int i = 0; i < numElements; ++i) {
                                Node* maxNode = Lista.extract_max();
                                if (maxNode != nullptr) {
                                    std::cout << "  " << maxNode->node_value << " (priorytet: " << maxNode->priority << ")\n";
                                    delete maxNode;
                                } else {
                                    std::cout << "Lista jest pusta.\n";
                                    break;
                                }
                            }
                            break;
                        }
                        default: {
                            std::cout << "Niepoprawny wybór.\n";
                            break;
                        }
                    }
                }
                break; 
            }
            case 2: {
                std::cout << "Funkcjonalność dla kopca nie została jeszcze zaimplementowana.\n";
                break;
            }
            default: {
                std::cout << "Niepoprawny wybór.\n";
                break;
            }
        }

        if (choice == 6)
            break;
    }

    return 0;
}
