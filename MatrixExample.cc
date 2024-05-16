// Implementing a matrix using two arrays of linked lists.
// The first array is an array of rows where each row is a linked list.
// The second array is an array of columns where each column is a linked list.











#include <iostream>
#include <new>




// ==== Global Constants ====
const int ROWS = 3;
const int COLS = 3;




// ==== Structs & Classes ====
typedef struct Index {
    int _row = -1;
    int _col = -1;
} Index;



enum POINTER_TYPE {
    NEXT_ROW,
    NEXT_COL,
    //more pointers can be added here
    //PREV_ROW,
    //PREV_COL,
    //NEXT_DIAG_UP,
    //NEXT_DIAG_DOWN,



    //if adding more pointers, add them and update the TOTAL
    TOTAL = 2
};

typedef struct Node {
    double _value;
    Index _index;
    
    Node* _pointers[POINTER_TYPE::TOTAL];
    

}Node ;




// _value: value of the node
// _index: index of the node
// _next_row: pointer to the next node in the row
// _next_col: pointer to the next node in the column


// Matrix struct
// **_rows: pointer to the array of rows where each row is a linked list
// **_cols: pointer to the array of columns where each column is a linked list
// _num_rows: number of rows in the matrix
// _num_cols: number of columns in the matrix
typedef struct Matrix {
    Node** _rows;
    Node** _cols;
    int _num_rows;
    int _num_cols;
} Matrix;

// ==== Function Declarations ====
Matrix* createMatrix(int rows, int cols);
void insertNode(Matrix* matrix, double value, int row_index, int col_index);
Node* createNode(double value, int row_index, int col_index) ;
void printFullMatrix(Matrix* matrix,POINTER_TYPE type);

void insertNodeIntoRow(Node** head,Node* node);

void insertNodeIntoCol(Node** head,Node* node);

void printNonZeroElements(Matrix* matrix,POINTER_TYPE type);

void transponseExample(int row,int col);

void actualTransposeMatrix(Matrix* matrix);

//void printColumn(Node* head) ;

void transposeMatrix(Matrix* const matrix);


// ==== Main Function ====
int main() {
    // ==== Variable Declarations ====

    // ==== Code ====
    Matrix* matrix = createMatrix(ROWS, COLS);
    if(matrix == nullptr) {
        std::cerr << "Error: Matrix creation failed" << std::endl;
        return 1;
    }

    insertNode(matrix, 1.0, 0, 0);
    insertNode(matrix, 2.0, 0, 1);
    insertNode(matrix, 3.0, 0, 2);
    insertNode(matrix, 4.0, 1, 0);
    insertNode(matrix, 5.0, 1, 1);
    insertNode(matrix, 6.0, 1, 2);

    printFullMatrix(matrix,POINTER_TYPE::NEXT_ROW);
    printNonZeroElements(matrix,POINTER_TYPE::NEXT_ROW);

    //okay so far the matrix is created and the nodes are inserted
    //now something very cool this structure allows us is to
    //easily!!! transpose the matrix
    //we just need to swap the rows and columns
    //and the matrix is transposed
    // example:
    // 1 2 3
    // 4 5 6
    // transpose
    // 1 4
    // 2 0
    // 3 6
    // so let's do that
    //2 and 3 as row and col to simulate the above example
    transponseExample(2,3);
    return 0;
}

// ==== Function Definitions ====
void transponseExample(int row,int col)
{
    Matrix* matrix = createMatrix(row, col);
    if(matrix == nullptr) {
        std::cerr << "Error: Matrix creation failed" << std::endl;
        return;
    }

    insertNode(matrix, 1.0, 0, 0);
    insertNode(matrix, 2.0, 0, 1);
    insertNode(matrix, 3.0, 0, 2);
    insertNode(matrix, 4.0, 1, 0);
   // insertNode(matrix, 0.0, 1, 1);
    insertNode(matrix, 6.0, 1, 2);

    

    printFullMatrix(matrix,POINTER_TYPE::NEXT_ROW);
    printNonZeroElements(matrix,POINTER_TYPE::NEXT_ROW);
    transposeMatrix(matrix);
    
    printFullMatrix(matrix,POINTER_TYPE::NEXT_COL);
    printNonZeroElements(matrix,POINTER_TYPE::NEXT_COL);

}

void transposeMatrix(Matrix* const matrix) {
    std::cout << "Transposing the matrix" << std::endl;
    std::swap(matrix->_rows, matrix->_cols);
    std::swap(matrix->_num_rows, matrix->_num_cols);
    std::cout << "Matrix transposed" << std::endl;
}

void actualTransposeMatrix(Matrix* matrix) {
    //swap the rows and columns
    Node** temp = matrix->_rows;
    matrix->_rows = matrix->_cols;
    matrix->_cols = temp;

    //swap the number of rows and columns
    int temp_num_rows = matrix->_num_rows;
    matrix->_num_rows = matrix->_num_cols;
    matrix->_num_cols = temp_num_rows;
}
/*
void printColumn(Node* head) {
    
    Node* temp = head;
    while(temp != nullptr) {
        std::cout << "index is:" << temp->_index._row << " "
        << temp->_index._col << " "
        <<"value is:"  << temp->_value << " " << std::endl;
        temp = temp->_pointers[NEXT_COL];
    }
    std::cout << std::endl;
}
*/


//print none zero elements
//printNonZeroElements
void printNonZeroElements(Matrix* matrix,POINTER_TYPE type) {
    std::cout << "Non-zero elements: " << std::endl;

    for(int i = 0; i < matrix->_num_rows; i++) {
        Node* temp = matrix->_rows[i];
        while(temp != nullptr) {
            std::cout << temp->_value << " ";
            temp = temp->_pointers[type];
        }
        std::cout << std::endl;
    }
}
//printMatrix
void printFullMatrix(Matrix* matrix,POINTER_TYPE type) {
    std::cout << "Full Matrix: " << std::endl;
    
    for(int i = 0; i < matrix->_num_rows; i++) {
        Node* temp = matrix->_rows[i];
        for(int j = 0; j < matrix->_num_cols; j++) {
            if(temp != nullptr) {
                std::cout << temp->_value << " ";
                temp = temp->_pointers[type];
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}
// createMatrix
Matrix* createMatrix(int rows, int cols) {
    
    Matrix* matrix = new Matrix;

    if(matrix == nullptr) {
        std::cerr << "Error: Matrix Memory allocation failed" << std::endl;
        return nullptr;
    }

    matrix->_num_rows = rows;
    matrix->_num_cols = cols;
    
    // each cell in each array is 
    //
    matrix->_rows = new Node*[rows];
    matrix->_cols = new Node*[cols];
    //
    // some check function after allocating
    
    // initialize the rows and columns to nullptr
    for (int i = 0; i < rows; i++) {
        matrix->_rows[i] = nullptr;
    }

    for (int i = 0; i < cols; i++) {
        matrix->_cols[i] = nullptr;
    }

    return matrix;
}
// ========================


//createNode
Node* createNode(double value, int row_index, int col_index) {
    Node* node = new Node;
    if(node == nullptr) {
        std::cerr << "Error: Node Memory allocation failed" << std::endl;
        return nullptr;
    }

    node->_value = value;
    node->_index._row = row_index;
    node->_index._col = col_index;
    node->_pointers[NEXT_ROW] = nullptr;
    node->_pointers[NEXT_COL] = nullptr;

    return node;
}
//insertNodeInto
void insertNodeIntoRow(Node** head,Node* node) {
    if(*head == nullptr) {
        *head = node;
        return;
    }
    Node* temp = *head;
    while(temp->_pointers[NEXT_ROW] != nullptr) {
        temp = temp->_pointers[NEXT_ROW];
    }
    temp->_pointers[NEXT_ROW] = node;
    
}
void insertNodeIntoCol(Node** head,Node* node) {
    // if the head is null, then the node is the first node in the column
    if(*head == nullptr) {
        *head = node;
        return;
    }
  
    Node* temp = *head;
    
    while(temp->_pointers[NEXT_COL] != nullptr) {
        temp = temp = temp->_pointers[NEXT_COL];
    }
    temp->_pointers[NEXT_COL] = node;
   
}
// insertNode
void insertNode(Matrix* matrix, double value, int row_index, int col_index) {
      if (row_index >= matrix->_num_rows || col_index >= matrix->_num_cols) {
        std::cerr << "Error: Index out of bounds" << std::endl;
        return;
    }
    // create a new node
    Node* node = createNode(value, row_index, col_index);
    if(node == nullptr) {
        std::cerr << "Error: Node Memory allocation failed" << std::endl;
        return;
    }
    insertNodeIntoRow(&matrix->_rows[row_index], node);
    insertNodeIntoCol(&matrix->_cols[col_index], node);

    }




