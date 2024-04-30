class Node
{
	public:
		int node_value;
		int priority;
		Node* next_value_ptr;
		Node* prev_value_ptr;
		Node();
};

class LinkedList
{
	private:
		Node* head;
		Node* tail;
		int size;
	public:
		LinkedList();
		void Insert(int, int);
		int get_size();
		void find_max_prio();
		Node* peek();

};



