#include <iostream>
#include <stdlib.h>
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

Node* LinkedList::find_max_prio() //szukanie wezla z 2 najwieszkym prio poza headem
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
	if(size==1)
	{	
		return head;
		head=nullptr; //TODO: wyciek pamieci???
	}
	else if(size==0)
	{
		std::cout<<"Kolejka jest pusta";
		return nullptr;
	}
	if(size>1&&curr==tail)
	{
		tail->prev_value_ptr->next_value_ptr=nullptr;
		tail->next_value_ptr=head->next_value_ptr;
		head=tail;
		tail->prev_value_ptr=tail;
		head->prev_value_ptr=nullptr; 
		
	}
	else
	{	
		curr = find_max_prio();
		return head;
		curr->prev_value_ptr->next_value_ptr = curr->next_value_ptr;
		curr->next_value_ptr->prev_value_ptr = curr->prev_value_ptr;
		curr->prev_value_ptr=nullptr;
		curr->next_value_ptr=head->next_value_ptr;
		head=curr;
		//nie wiem co sie dzieje juz
		
	}
}






