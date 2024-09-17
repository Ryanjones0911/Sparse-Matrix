#include<iostream>
#include<fstream>
#include<sstream>


//A circularly linked list is just a normal doubly linked list
//where the last node points to the head of the list.
//NOTE** This will not be a feature complete circularly linked list, as I will only be implementing the functionality
//required to complete this assignment
class CircularlyLinkedList {
    /*class for the individual nodes of the list. All standard fare expect for cursor, which exists to constantly point to tail of list
    to allow for constant time access to both sides of this list*/

    public: class Node {
        public: int data;
        int col;
        int row;
        Node * next;
        Node * cursor;
        Node(int col, int row, int data) {
            this -> data = data;
            this -> next = nullptr;
            this -> col = col;
            this -> row = row;
            this -> cursor = nullptr;
        }
    };
    Node * head;
    Node * cursor;
    CircularlyLinkedList() {
        head = nullptr;
        cursor = nullptr;
    }

    //insert a new node, either at the head or the current last position
    void insert(int col, int row, int data) {
        //initialize memory for new node
        Node * newNode = new Node(col, row, data);

        //if list is currently empty, add new node as the new head. Otherwise add it to the end and set cursor to point to new tail
        if (head == nullptr) {
            head = newNode;
            newNode -> next = newNode;
            cursor = newNode;
        } else {
            Node * current = head;

            while (current -> next != head) {
                current = current -> next;
            }
            current -> next = newNode;
            newNode -> next = head;
            cursor = newNode;
        }
    }

    //allows for searching of specific values in the list. This will be useful in our SparseMatrix class
    Node * access(int row, int col, int findData) {
        Node * current = head;

        while (current -> data != findData) {
            current = current -> next;
        }

        return current;
    }

    //Just a function I've been using to verify proper functionality. I'll try to remember to remove it, but if
    //it's still here at time of submission just know it's not intended
    void viewList() const {
        Node * current = head;
        if (current == nullptr) {
            std::cout << "List is empty\n";
            return;
        }

        do {
            std::cout << current -> data << " -> ";
            current = current -> next;
        } while (current != head);

        std::cout << std::endl;
    }
};

class SparseMatrix {
    private: CircularlyLinkedList * row;
    CircularlyLinkedList * column;
    int matrixSize;

    public: SparseMatrix(int matrixSize) {
        this -> matrixSize = matrixSize;
        row = new CircularlyLinkedList[matrixSize];
        column = new CircularlyLinkedList[matrixSize];
    }

    //this will be rewriten to accomodate CSV functionality, but for now I'm just filling matrices 
    //manually for testing purposes
    void addData(int rowIndex, int colIndex, int data) {
        row[rowIndex].insert(colIndex, rowIndex, data);
        column[colIndex].insert(colIndex, rowIndex, data);

    }

    void viewMatrix() {

        for (int i = 0; i < matrixSize; i++) {
            std::cout << "Row " << i << ": ";
            row[i].viewList();
        }

        std::cout << std::endl;

    }

    int getElement(int rowIndex, int colIndex) {

        CircularlyLinkedList::Node * current = row[rowIndex].head;
        if (current != nullptr) {
            do {
                if (current -> col == colIndex) {
                    return current -> data;
                }
                current = current -> next;
            } while (current != row[rowIndex].head);
        }

        return 0; // default value if not found, meaning the element is not in the list
    }

    SparseMatrix scalarMultiply(SparseMatrix matrix, int scalar) {
        SparseMatrix resultant(matrixSize);
        for (int i = 0; i < matrixSize; i++) {
            CircularlyLinkedList::Node * current = matrix.row[i].head;
            if (current != nullptr) {
                do {
                    resultant.addData(current -> row, current -> col, (current -> data * scalar));
                    current = current -> next;
                } while (current != matrix.row[i].head);

            }
        }
        return resultant;
    }

    SparseMatrix transposeMatrix(SparseMatrix matrix) {
        //to transpose a square matrix all we need to do
        //is swap the rows and columns

        SparseMatrix resultant(matrixSize);

        for (int i = 0; i < matrixSize; i++) {
            CircularlyLinkedList::Node * current = matrix.row[i].head;
            if (current != nullptr) {
                do {
                    resultant.addData(current -> col, current -> row, current -> data);
                    current = current -> next;
                } while (current != matrix.row[i].head);

            }
        }
        return resultant;
    }

    SparseMatrix addMatrix(SparseMatrix a, SparseMatrix b) {
        SparseMatrix resultant(matrixSize);

        // Traverse matrix B and add its elements to the resultant matrix
        for (int i = 0; i < matrixSize; i++) {
            CircularlyLinkedList::Node * currentB = b.row[i].head;

            if (currentB != nullptr) {
                do {
                    // Add elements from matrix B, summing with any existing elements from A
                    int existingData = a.getElement(currentB -> row, currentB -> col);

                    if (existingData == 0) {
                        resultant.addData(currentB -> row, currentB -> col, currentB -> data);
                    } else {
                        resultant.addData(currentB -> row, currentB -> col, currentB -> data + existingData);
                    }
                    currentB = currentB -> next;
                } while (currentB != b.row[i].head);
            }
        }

        // Ensure matrix A's elements are included if they were not covered by matrix B
        for (int i = 0; i < matrixSize; i++) {
            CircularlyLinkedList::Node * currentA = a.row[i].head;

            if (currentA != nullptr) {
                do {
                    // If matrix B does not already include this element, add it to the resultant matrix
                    int existingData = resultant.getElement(currentA -> row, currentA -> col);

                    if (existingData == 0) {
                        resultant.addData(currentA -> row, currentA -> col, currentA -> data);
                    }

                    currentA = currentA -> next;
                } while (currentA != a.row[i].head);
            }
        }

        return resultant;
    }

SparseMatrix multiplyMatrix(SparseMatrix a, SparseMatrix b) {
    SparseMatrix resultant(matrixSize);
    //NOTE: I don't like this being 3 nested for loops, but I'm out of time to find a better solution and this does function

    // Iterate through each row of matrix A
    for (int i = 0; i < matrixSize; i++) {
        // For each row in A, iterate through each column in matrix B
        for (int j = 0; j < matrixSize; j++) {
            int sum = 0;
            // Multiply corresponding elements in the row of A and the column of B
            for (int k = 0; k < matrixSize; k++) {
                int elementA = a.getElement(i, k);  // Get element A[i][k]
                int elementB = b.getElement(k, j);  // Get element B[k][j]
                sum += elementA * elementB;         // Accumulate the product
            }
            // If the resulting sum is non-zero, add it to the resultant matrix
            if (sum != 0) {
                resultant.addData(i, j, sum);
            }
        }
    }
    
    return resultant;
    }


#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

static void readFromCSV(const std::string& filename, char& operation, int& matrixSize, SparseMatrix& matrix1, SparseMatrix& matrix2, int& scalar) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    std::string line;

    // Read the first line that contains both operation and matrix size
    if (std::getline(fin, line)) {
        std::istringstream iss(line);

        // Parse operation and matrix size
        if (!(iss >> operation >> matrixSize)) {
            std::cerr << "Error parsing operation or matrix size from the line: " << line << std::endl;
            return;
        }
        std::cout << "Operation: " << operation << "\nMatrix Size: " << matrixSize << std::endl;
    } else {
        std::cerr << "Failed to read operation and matrix size from CSV." << std::endl;
        return;
    }

    // Initialize the matrices with the matrix size
    matrix1 = SparseMatrix(matrixSize);
    matrix2 = SparseMatrix(matrixSize);

    // Read the matrix data
    while (std::getline(fin, line)) {
        std::istringstream ss(line);
        int row, col, data;

        if (!(ss >> row >> col >> data)) {
            std::cerr << "Error parsing matrix data: " << line << std::endl;
            continue;  // Skip this line if it's malformed
        }

        matrix1.addData(row, col, data);  // You might need to adjust this if it's the second matrix
    }

    fin.close();
}

static void writeToCSV(const std::string& filename, SparseMatrix& result, char operation, int matrixSize) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }
    
    fout << operation << "\n";
    fout << matrixSize << "\n";
    
    // Output the data in (row, col, data) format
    for (int i = 0; i < matrixSize; i++) {
        CircularlyLinkedList::Node* current = result.row[i].head;
        if (current != nullptr) {
            do {
                fout << current->row << "," << current->col << "," << current->data << "\n";
                current = current->next;
            } while (current != result.row[i].head);
        }
    }
    
    fout.close();
}

};

int main() {
    std::string inputFilename, outputFilename;
    std::cout << "Enter input CSV filename: ";
    std::cin >> inputFilename;

    char operation;
    int matrixSize;
    int scalar = 0;  // Scalar for scalar multiplication
    SparseMatrix matrix1(0), matrix2(0);

    // Read data from the CSV file
    SparseMatrix::readFromCSV(inputFilename, operation, matrixSize, matrix1, matrix2, scalar);

    SparseMatrix result(matrixSize);

    // Perform the appropriate operation
    if (operation == 'A') {
        result = matrix1.addMatrix(matrix1, matrix2);
    } else if (operation == 'M') {
        result = matrix1.multiplyMatrix(matrix1, matrix2);
    } else if (operation == 'T') {
        result = matrix1.transposeMatrix(matrix1);  // Transpose the left matrix
    } else if (operation == 'S') {
        result = matrix1.scalarMultiply(matrix1, scalar);  // Scalar multiplication
    }

    // Output the result to a CSV file
    std::cout << "Enter output CSV filename: ";
    std::cin >> outputFilename;
    SparseMatrix::writeToCSV(outputFilename, result, operation, matrixSize);

    return 0;
}
