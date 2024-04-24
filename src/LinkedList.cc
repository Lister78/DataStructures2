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

