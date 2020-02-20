#define LINKEDLIST_H_

namespace linkedlist{ 

class LinkedList {
  private:
    LinkedList(int data);
    Node *head;
    Node *tail;
    int size;
    bool is_empty(); // checks if ll is empty
    int get_at_index(int index); // returns data of node at given index
    Node get_index_node(int index); // returns node obj at given index
    void append(int item); // appends given item to the end of the ll
    void prepend(int item); // prepends the given item to the beginning of the ll
    void insert(int item, int index); // inserts the given item at the given index of ll
    void delete_(int item); // deletes node containing given item, throws error otherwise.
    
}
} // namespace linkedlist
