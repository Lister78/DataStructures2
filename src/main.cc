#include <iostream>
#include "LinkedList.h"
int main()
{
	LinkedList lista;
	Node* wezel;
	lista.Insert(10,20);
	lista.Insert(20,30);
	lista.Insert(40,50);
	lista.Insert(1,2);
	std::cout<<"Wielkosc struktury: "<<lista.get_size()<<std::endl;
	wezel=lista.peek();
	std::cout<<"wartosc: "<<wezel->node_value<<" prio: "<<wezel->priority;
	std::cout<<"\nInitializatione went good";

	return 0;
}
