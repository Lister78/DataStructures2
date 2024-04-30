#include <iostream>
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

void LinkedList::find_max_prio() //szukanie wezla z 2 najwieszkym prio poza headem
{
	Node* curr = new Node;
/*	if(size==1)
	{
		
	}
*/
}

Node* LinkedList::peek()
{
	return head;
}



