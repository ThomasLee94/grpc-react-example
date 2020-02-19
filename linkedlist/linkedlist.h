#define LINKEDLIST_H_

namespace linkedlist{ 

class LinkedList {
  private:
    LinkedList(data);
    Node *head;
    Node *tail;
    int size;
    bool is_empty();
    void append(item);
    void prepend(item);
    void insert(item);
    
}
} // namespace linkedlist
