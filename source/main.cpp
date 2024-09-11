
#include<iostream>


//A circularly linked list is just a normal doubly linked list
//where the last node points to the head of the list.
//NOTE** This will not be a feature complete circularly linked list, as I will only be implementing the functionality
//required to complete this assignment
class CircularlyLinkedList

{
    /*class for the individual nodes of the list. All standard fare expect for cursor, which exists to constantly point to tail of list
    to allow for constant time access to both sides of this list*/
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
    
    //we dont want people to be able to access these directly and get to messing with our node pointers
    private:
        Node* head;
        Node* cursor;

    public:
        CircularlyLinkedList()
        {
            head = nullptr;
            cursor = nullptr;
        }
    
    //insert a new node, either at the head or the current last position
    void insert(int data)
    {
        //initialize memory for new node
        Node* newNode = new Node(data);

        //if list is currently empty, add new node as the new head. Otherwise add it to the end and set cursor to point to new tail
        if(head == nullptr)
        {
            head = newNode;
            newNode->next = newNode;
            cursor = newNode;
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
            cursor = newNode;

        }
    }

    //allows for searching of specific values in the list. This will be useful in our SparseMatrix class
    Node* access(int findData)
    {
        Node* current = head;

        while(current->data != findData)
        {
            current = current->next;
        }

        return current;
    }

    //Just a function I've been using to verify proper functionality. I'll try to remember to remove it, but if
    //it's still here at time of submission just know it's not intended
    void viewList()
    {
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
            std::cout << " back to head -> " << current->data;
            
        }
    }
};

class SparseMatrix
{
    private:
        CircularlyLinkedList row;
        CircularlyLinkedList column;

    public:
        SparseMatrix(CircularlyLinkedList row)
        {

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