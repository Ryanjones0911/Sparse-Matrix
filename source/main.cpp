
#include<iostream>


//A circularly linked list is just a normal doubly linked list
//where the last node points to the head of the list.
//NOTE** This will not be a feature complete circularly linked list, as I will only be implementing the functionality
//required to complete this assignment
class CircularlyLinkedList
{
    /*class for the individual nodes of the list. All standard fare expect for cursor, which exists to constantly point to tail of list
    to allow for constant time access to both sides of this list*/



    public:
         class Node
        {
            public:
                int data;
                int col;
                int row;
                Node* next;
                Node* cursor;
                Node(int col, int row, int data)
                {
                    this->data = data;
                    next = nullptr;
                    cursor = nullptr;
                }
        };
        Node* head;
        Node* cursor;
        CircularlyLinkedList()
        {
            head = nullptr;
            cursor = nullptr;
        }
    
    //insert a new node, either at the head or the current last position
    void insert(int col, int row, int data)
    {
        //initialize memory for new node
        Node* newNode = new Node(col, row, data);

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
    Node* access(int row, int col, int findData)
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
void viewList() const
    {
        Node* current = head;
        if (current == nullptr)
        {
            std::cout << "List is empty\n";
            return;
        }

        do
        {
            std::cout << current->data << " -> ";
            current = current->next;
        } while (current != head);

        std::cout << std::endl;
    }
};

class SparseMatrix
{
    private:
        CircularlyLinkedList* row;
        CircularlyLinkedList* column;
        int matrixSize;

    public:
        SparseMatrix(int matrixSize)
        {
            row = new CircularlyLinkedList[matrixSize+1];
            column = new CircularlyLinkedList[matrixSize+1];
        }

        //this will be rewriten to accomodate CSV functionality, but for now I'm just filling matrices 
        //manually for testing purposes
        void addData(int rowIndex, int colIndex, int data)
        {
            row[rowIndex-1].insert(rowIndex, colIndex, data);
            column[colIndex-1].insert(rowIndex, colIndex, data);

        }


    void viewMatrix() 
    {
        std::cout << "Matrix view:" << std::endl;

        for (int i = 0; i < matrixSize; i++)
        {
            std::cout << "Row " << i << ": ";
            row[i].viewList();
        }

        std::cout << std::endl;

        for (int i = 0; i < matrixSize; i++)
        {
            std::cout << "Column " << i << ": ";
            column[i].viewList();
        }
    }

    //SparseMatrix* scalarMultiply(int scalar)
    //{
        //all we do is multiply every element of the matrix by the scalar value
        //and return the resultant matrix

        
    //}
};

int main()
{
    CircularlyLinkedList test;
    SparseMatrix matrixTest(4);
    

  

    matrixTest.addData(1,3,11);
    matrixTest.addData(4,2,1);
    matrixTest.addData(3,2,8);
    matrixTest.addData(1,1,7);
    matrixTest.addData(1,2,-4);


    matrixTest.viewMatrix();
    


    //SparseMatrix* resultant = matrixTest.scalarMultiply(2);

   
}