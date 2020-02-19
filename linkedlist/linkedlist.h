#define LINKEDLIST_H_

namespace linkedlist{ 

class LinkedList {
  private:
    LinkedList(data);
    Node *head;
    Node *tail;
    int size;
    bool is_empty();
    int get_at_index(int index);
    Node get_index_node(int index);
    void append(int item);
    void prepend(int item);
    void insert(int item, int index);
    
}
} // namespace linkedlist
