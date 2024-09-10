class Node
{
public:
    int data;
    Node* next;

    Node(int data);
};

class CircularlyLinkedList
{
private:
    Node* head;

public:
    CircularlyLinkedList();

    void insert(int data);
    };