
//this is where we will run the actual program

#include<iostream>

//All implementation details of the circularly linked list data structure will go here


//A circularly linked list is just a normal doubly linked list
//where the last node points to the head of the list.
//NOTE** This will not be a feature complete circularly linked list, as I will only be implementing the functionality
//required to complete this assignment
class Node
{
    public:
        int data;
        Node* next;
        Node* cursor;
        Node(int data)
        {
            this->data = data;
            next = nullptr;
            cursor = nullptr;
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
            newNode->next = newNode;
        }
        else
        {
            Node* current = head;

            while(current->next != head)
            {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    void viewList()
    {
        //std::cout << "this at least works";

        Node* current = head;
        if(current == nullptr)
        {
            std::cout << "List is empty";
        }
        else
        {
            do
            {
                std::cout << current->data << " -> ";
                current = current->next;
            } while (current != head);
            std::cout << current->data;
            
        }
    }
};

int main()
{
    CircularlyLinkedList test;

    test.insert(5);
    test.insert(6);
    test.insert(7);
    test.insert(8);
    test.insert(9);
    test.insert(10);
    test.viewList();
}