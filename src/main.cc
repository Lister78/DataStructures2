#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <chrono>
#include "LinkedList.h"
#include "PriorityQueueInHeap.h"

// Funkcji do pomiaru czasu wykonania operacji
template<typename Func>
double measureExecutionTime(Func&& func) {
    auto start = std::chrono::steady_clock::now();
    func();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}



// Funkcja przygotowująca dane testowe dla listy oraz kopca
void prepareData(int choice, int size, LinkedList& Lista, PriorityQueueInHeap<int, int>& Kopiec) {
    if (choice == 1){
    	// Tworzenie listy wiązanej
    	for (int i = 0; i < size; ++i) {
        	int value = rand() % 10000;
        	int priority = rand() % (2 * size);
        	Lista.Insert(value, priority);
    	} 
    }else if (choice == 2){
    	// Tworzenie kopca
    	for (int i = 0; i < size; ++i) {
        	int value = rand() % 10000;
        	int priority = rand() % (2 * size);
        	Kopiec.insert(value, priority);
        }
    }
}

int main() {
    int choice;
    LinkedList Lista;
    PriorityQueueInHeap <int, int> Kopiec;
    
    std::vector<int> sizes = {6000, 8000, 10000, 20000, 40000, 60000, 80000, 100000};

    // Menu
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
                            for (int size : sizes) {
                            	Lista.clear();
                                prepareData(1, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Lista.Insert(value, priority); });
                                }
                                std::cout << "Średni czas operacji Insert na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                                
                        }break;
                        }
                        
                        case 2: {
                            for (int size : sizes) {
                                Lista.clear();
                                prepareData(1, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Lista.extract_max(); });
                                    Node* maxNode = Lista.extract_max();
                                    if (maxNode != nullptr) {
                                delete maxNode;
                            	} 
                                }
                                std::cout << "Średni czas operacji extract_max na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                                
                            
                        }break;
                        }
                        
                        case 3: {
                            for (int size : sizes) {
                            	Lista.clear();
                                prepareData(1, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Lista.peek(); });
                            
                                }
                                Node* maxNode = Lista.peek();
                                if (maxNode != nullptr) {
                                std::cout << "Element o największym priorytecie: "
                                          << maxNode->node_value << " (priorytet: " << maxNode->priority << ")\n";
                            } else {
                                std::cout << "Lista jest pusta.\n";
                            }
                                std::cout << "Średni czas operacji peek na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                            
                            
                        }break;
                        }
                        case 4: {
                            int value, newPriority;
                            std::cout << "Podaj wartość elementu do zmiany priorytetu: ";
                            std::cin >> value;
                            std::cout << "Podaj nowy priorytet: ";
                            std::cin >> newPriority;
                            for (int size : sizes) {
                                Lista.clear();
                                prepareData(1, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Lista.modify_key(value, newPriority); });
                                }
                                std::cout << "Średni czas operacji modify_key na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                                
                        }
                            
                            break;
                        }
                        case 5: {
                        for (int size : sizes) {
                        	Lista.clear();
                                prepareData(1, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Lista.get_size(); });
                                }
                                std::cout << "Średni czas operacji get_size na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                                std::cout << "Rozmiar listy: " << Lista.get_size() << "\n";
                           
                                
                        }
                            
                            break;
                        }
                        case 6: {
                            break; 
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
                while (1) {
                    std::cout << "1. Dodaj element\n"
                                 "2. Usuń i zwróć element o największym priorytecie\n"
                                 "3. Zwróć element o największym priorytecie\n"
                                 "4. Zmień priorytet\n"
                                 "5. Zwróć rozmiar\n"
                                 "6. Wyjdź\n"
                                 "7. Dodaj losowe elementy\n";

                    std::cin >> choice;

                    switch (choice) {
                        case 1: {
                            int value, priority;
                            std::cout << "Podaj wartość: ";
                            std::cin >> value;
                            std::cout << "Podaj priorytet: ";
                            std::cin >> priority;
                            for (int size : sizes) {
                            	Kopiec.clear();
                                prepareData(2, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Kopiec.insert(value, priority); });
                                }
                                std::cout << "Średni czas operacji Insert na Kopcu" << size << ": " << totalTime / 100 << " microseconds\n";
                                
                        }   
                            
                            break;
                        }
                        case 2: {
                        	for (int size : sizes) {
                        	Kopiec.clear();
                                prepareData(2, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Kopiec.extract_max(); });
                                }
                                std::cout << "Średni czas operacji extract_max na Kopcu" << size << ": " << totalTime / 100 << " microseconds\n";
                                
                        }
                            if (!Kopiec.isEmpty()) {
                                int maxElement = Kopiec.peek();
                                Kopiec.extract_max();
                                std::cout << "Usunięty element o największym priorytecie: "
                                          << maxElement << "\n";
                            } else {
                                std::cout << "Kopiec jest pusty.\n";
                            }
                            break;
                        }
                        case 3: {
                            for (int size : sizes) {
                            	Kopiec.clear();
                            	prepareData(2, size, Lista, Kopiec);
                                double totalTime = 0;
                            	for (int i = 0; i < 100; ++i) {    
                            	    totalTime += measureExecutionTime([&]() { Kopiec.peek(); });
                            	    }
                            	    std::cout << "Średni czas operacji peek na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                            	if (!Kopiec.isEmpty()) {
                            	    int maxElement = Kopiec.peek();
                            	    std::cout << "Element o największym priorytecie: "
                            	              << maxElement << "\n";
                            }	 else {
 	                               std::cout << "Kopiec jest pusty.\n";
                            }
                        }
                        break;
                        }
                        case 4: {
                            int element, newPriority;
                            std::cout << "Podaj stary priorytet elementu: ";
                            std::cin >> element;
                            std::cout << "Podaj nowy priorytet: ";
                            std::cin >> newPriority;
                            for (int size : sizes) {
                            	Kopiec.clear();
                                prepareData(2, size, Lista, Kopiec);
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Kopiec.modify_key(element, newPriority); });
                                }
                                std::cout << "Średni czas operacji size na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                                
                        }
                            
                            break;
                        }
                        case 5: {
                            for (int size : sizes) {
                                prepareData(2, size, Lista, Kopiec);
                                Kopiec.clear();
                                double totalTime = 0;
                                for (int i = 0; i < 100; ++i) {
                                    totalTime += measureExecutionTime([&]() { Kopiec.size(); });
                                }
                                std::cout << "Średni czas operacji size na Liście" << size << ": " << totalTime / 100 << " microseconds\n";
                                
                        }

                            break;
                        }
                        case 6: {
                            break; 
                        }
                        case 7: {
                            int numElements;
                            std::cout << "Podaj liczbę losowych elementów do dodania: ";
                            std::cin >> numElements;
                            Kopiec = PriorityQueueInHeap<int, int>::randomGenerate(numElements, 0, 15000);
                            std::cout << "Dodano losowe elementy do kopca.\n";
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
