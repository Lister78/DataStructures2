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
		Node* find_max_prio();
		Node* peek();
		Node* extract_max();
		void modify_key(int,int);
		void move_after_modify(Node*, int);
};



