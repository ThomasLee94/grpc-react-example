#define LINKEDLIST_H_

namespace linkedlist{ 

class LinkedList {
  private:
    LinkedList(data);
    Node *head;
    Node *tail;
    int size;
    bool is_empty();
    int get_at_index();
    Node get_index_node();
    void append(item);
    void prepend(item);
    void insert(item);
    
}
} // namespace linkedlist
