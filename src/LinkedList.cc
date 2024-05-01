#include <iostream>
#include <stdlib.h>
#include <vector>
#include "LinkedList.h"
Node::Node()
{
	node_value=0;
	priority=0;
	next_value_ptr=nullptr;
	prev_value_ptr=nullptr;
}

LinkedList::LinkedList()
{
	head=nullptr;
	tail=nullptr;
	size =0;
}

void LinkedList::Insert(int value, int priority)
{
	Node* node = new Node;
	if(size==0)
	{
		head=node;
		tail=node;
	}
	else
	{
		if(priority>head->priority)
		{
			node->next_value_ptr=head;
			head->prev_value_ptr=node;
			head=node;

		}
		else
		{
			tail->next_value_ptr=node;
			node->prev_value_ptr=tail;
			tail=node;
		}
	}
	node->node_value=value;
	node->priority=priority;
	size++;
}

int LinkedList::get_size()
{
	return size;
}

Node* LinkedList::find_max_prio() //szukanie wezla z najwieszkym prio poza headem
{
	Node* curr = new Node;
	curr = head;
	int max_prio = head->next_value_ptr->priority;
	Node* node_to_return = new Node;	
	node_to_return = curr->next_value_ptr; 
	for(int i=0;i<size-1;i++)
	{ 
		curr=curr->next_value_ptr;
		if(curr->priority>node_to_return->priority)
			node_to_return=curr;

	}
	return node_to_return;
		

}

Node* LinkedList::peek()
{
	return head;
}

Node* LinkedList::extract_max()
{
	Node* curr = new Node;
	curr = find_max_prio();
	if(size==1)
	{	
		return head;
		head=nullptr; //TODO: wyciek pamieci???
		size--;
	}
	else if(size==0)
	{
		std::cout<<"Kolejka jest pusta";
		return nullptr;
	}
	if(size>1&&curr==tail)
	{
		return head;
		tail->prev_value_ptr->next_value_ptr=nullptr;
		tail->next_value_ptr=head->next_value_ptr;
		head=tail;
		tail->prev_value_ptr=tail;
		head->prev_value_ptr=nullptr;
		size--;
	}
	else
	{	
		return head;
		curr->prev_value_ptr->next_value_ptr = curr->next_value_ptr;
		curr->next_value_ptr->prev_value_ptr = curr->prev_value_ptr;
		curr->prev_value_ptr=nullptr;
		curr->next_value_ptr=head->next_value_ptr;
		head=curr;
		size--;
		//nie wiem co sie dzieje juz
		
	}
}


void LinkedList::modify_key(int looking_value, int new_prio)
{
	Node* temp = new Node;
	int count_of_elements;
	temp = head;
	int position=1;
	if(size==1)
	{
		if(looking_value==head->node_value)
		{
			std::cout<<"Znaleziono: "<<looking_value<<" na 1 pozycji. Stary priorytet: "<< head->priority<<" nowy priorytet: "<<new_prio<<std::endl; 
			count_of_elements++;
			head->priority=new_prio;
		} 
	}
	else if(size>1)
	{
		std::vector<Node*> nodes_with_looking_value;
		for(int i=1;i<size;i++)
		{
			if(looking_value==temp->node_value)
			{
				nodes_with_looking_value.push_back(temp);
				count_of_elements++;
				std::cout<<count_of_elements<<".Znaleziono wezel z podana wartoscia na pozycji: "<<position<<" o priorytecie";
			}
			temp=temp->next_value_ptr;
			position++;
		}
		std::cout<<"Priorytet ktorego wezla chcesz zmienic?";
		std::cin>>position;
		temp=nodes_with_looking_value[position-1];
		if(new_prio>=head->priority&&temp==head)
			head->priority=new_prio;
		else if(new_prio<head->priority&&temp==tail)
			tail->priority=new_prio;
		else
			move_after_modify(temp,new_prio);
	}
	//TODO rest     Jak znajdziesz i wybierzesz do zmiany heada to sprawdzasz funkcja przed zmiana jaki jest 2 najwieksza prio i sprawdzasz czy jest ona wieksza niz nowe prio jak nie to zmieniasz prio, ale nie zmieniasz heada jak tak to przerzucasz heada na taila i robisz juz normalnie //wiadomosc dla mnie zebym skumal jutro ocb
	
	if(count_of_elements==0)
		std::cout<<"Nie znaleziono elementu o takiej wartosci"<<std::endl;
}

void LinkedList::move_after_modify(Node* curr, int new_prio)
{
	if(new_prio>head->priority&&curr!=head)
	{
		if(curr==tail)
		{
			tail->prev_value_ptr->next_value_ptr=nullptr;
			tail->next_value_ptr=head;
			head=tail;
			tail->prev_value_ptr=tail;
			head->prev_value_ptr=nullptr; 
		}
		else
		{
			curr->prev_value_ptr->next_value_ptr = curr->next_value_ptr;
			curr->next_value_ptr->prev_value_ptr = curr->prev_value_ptr;
			curr->prev_value_ptr=nullptr;
			curr->next_value_ptr=head;
			head=curr;
		}
	}
	else if(curr==head)
	{
			Node* temp = new Node;
			temp = find_max_prio();
			if(temp==tail)
			{
				tail->next_value_ptr=head->next_value_ptr;
				head->prev_value_ptr=tail->prev_value_ptr;
				tail->prev_value_ptr->next_value_ptr=head;
				head=tail;
				tail=tail->prev_value_ptr->next_value_ptr;//xDDDDDDDDDDDDDDDD
				tail->next_value_ptr->prev_value_ptr=head;
				head->prev_value_ptr=nullptr;
				tail->next_value_ptr=nullptr;  //PO CZASIE USWIADOMOLEM SOBIE ZE MOZNA BYLO TO ROBIC INACZEJ BO JESZCZE CURR MI WSKAZUJE NA HEAD I NIE MUSIALEM TAKIEJ PAJACERKI ROBIC
			}
			else
			{
				temp->prev_value_ptr->next_value_ptr = temp->next_value_ptr;
				temp->next_value_ptr->prev_value_ptr = temp->prev_value_ptr;
				head->prev_value_ptr=tail;
				tail->next_value_ptr=head;
				tail=head;
				temp->next_value_ptr=head->next_value_ptr;
				head->next_value_ptr->prev_value_ptr=temp;
				head=temp;
				tail->next_value_ptr=nullptr;
				temp->prev_value_ptr=nullptr; 					//nie wiem juz co sie dizeje do sprawdzenia TODO

			}
	}
	else
	{
		curr->next_value_ptr->prev_value_ptr = curr->prev_value_ptr;
		curr->prev_value_ptr->next_value_ptr = curr->next_value_ptr;
		tail->next_value_ptr = curr;
		curr->prev_value_ptr = tail;
		tail=curr;

	}
	curr->priority=new_prio;
}

