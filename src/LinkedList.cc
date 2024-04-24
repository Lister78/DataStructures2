#include "LinkedList.h"
Node::Node()
{
	node_value=0;
	priority=0;
	next_value_ptr=nullptr;
}

LinkedList::LinkedList()
{
	head=nullptr;
}

