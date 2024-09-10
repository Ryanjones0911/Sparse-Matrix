//All implementation details of the circularly linked list data structure will go here
#include"CircularlyLinkedList.h"

//A circularly  linked list is just a normal doubly linked list
//where the last node points to the head of the list.
//NOTE** This will not be a feature complete circularly linked list, as I will only be implementing the functionality
//required to complete the assignment
class Node
{
    public:
        int data;
        Node* next;
        Node(int data)
        {
            data = data;
            next = nullptr;
        }
};

class CircularlyLinkedList
{
    private:
        Node* head;

    public:
        CircularlyLinkedList()
        {
            head = nullptr;
        }
    
    //insert a new node, either at the head or the current last position
    void insert(int data)
    {
        //initialize memory for new node
        Node* newNode = new Node(data);

        //if list is currently empty, add new node as the new head
        if(head == nullptr)
        {
            head = newNode;
            newNode->next = head;
        }
    }
};