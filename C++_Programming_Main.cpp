// includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // for setw

// print matrix function that prints a matrix with aligned columns
void printMatrix(const std::vector<std::vector<int>> &matrix, const std::string &title = "") {
    if (!title.empty()) {
        std::cout << title << "\n";
    }
    if (matrix.empty()) {
        std::cout << "(empty matrix)\n";
        return;
    }

    int size = int (matrix.size());
    int maxWidth = 0;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            int digitCount = 0;
            int value = matrix[row][column];
            if (value == 0) {
                digitCount = 1;
            } 
            else {
                int tempAbsolute = (value < 0) ? -value : value;
                while (tempAbsolute > 0) {
                    tempAbsolute /= 10;
                    ++digitCount;
                }
                if (value < 0) {
                    ++digitCount;
                }
            }
            if (digitCount > maxWidth) {
                maxWidth = digitCount;
            }
        }
    }

    if (maxWidth < 2) {
        maxWidth = 2;
    }

    int columnWidth = maxWidth + 2;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            std::cout << std::setw(columnWidth) << matrix[row][column];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// load matrices function which gets the matrices from the given file
bool loadMatrices(const std::string &filename, int &size, std::vector<std::vector<int>> &firstMatrix, std::vector<std::vector<int>> &secondMatrix) {
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error: cannot open file '" << filename << "'\n";
        return false;
    }

    if (!(inputFile >> size)) {
        std::cerr << "Error: first item must be matrix size\n";
        return false;
    }

    if (size <= 0) {
        std::cerr << "Error: size must be positive\n";
        return false;
    }

    firstMatrix.assign(size, std::vector<int>(size, 0));
    secondMatrix.assign(size, std::vector<int>(size, 0));

    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if (!(inputFile >> firstMatrix[row][column])) {
                std::cerr << "Error: incorrect format for first matrix\n";
                return false;
            }
        }
    }

    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if (!(inputFile >> secondMatrix[row][column])) {
                std::cerr << "Error: incorrect format for second matrix\n";
                return false;
            }
        }
    }

    inputFile.close();
    return true;
}

// add two matrices function
std::vector<std::vector<int>> addMatrices(const std::vector<std::vector<int>> &firstMatrix, const std::vector<std::vector<int>> &secondMatrix) {
    int size = int (firstMatrix.size());
    std::vector<std::vector<int>> resultMatrix = firstMatrix;
    
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            resultMatrix[row][column] = firstMatrix[row][column] + secondMatrix[row][column];
        }
    }
    return resultMatrix;
}

// multiply two matrices function
std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>> &firstMatrix, const std::vector<std::vector<int>> &secondMatrix) {
    int size = int (firstMatrix.size());
    std::vector<std::vector<int>> resultMatrix(size, std::vector<int>(size, 0));
    
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            int sum = 0;
            for (int innerIndex = 0; innerIndex < size; ++innerIndex) {
                sum += firstMatrix[row][innerIndex] * secondMatrix[innerIndex][column];
            }
            resultMatrix[row][column] = sum;
        }
    }
    return resultMatrix;
}

// diagonal sums function that gets the sum of matrix diagonals
void diagonalSums(const std::vector<std::vector<int>> &matrix) {
    int size = int (matrix.size());
    int DiagonalSum1 = 0;
    int DiagonalSum2 = 0;

    for (int index = 0; index < size; ++index) {
        DiagonalSum1 += matrix[index][index];
        DiagonalSum2 += matrix[index][size - 1 - index];
    }

    std::cout << "Main diagonal sum:      " << DiagonalSum1 << "\n";
    std::cout << "Second diagonal sum: " << DiagonalSum2 << "\n";
    int combinedSum = DiagonalSum1 + DiagonalSum2;

    if (size % 2 == 1) {
        int centerValue = matrix[size / 2][size / 2];
        combinedSum -= centerValue;
    }

    std::cout << "Combined sum:  " << combinedSum << "\n";
    std::cout << "\n";
}

// swap matrix rows function
bool swapRows(std::vector<std::vector<int>> &matrix, int rowIndex1, int rowIndex2) {
    int size = int (matrix.size());

    if (rowIndex1 < 0 || rowIndex1 >= size || rowIndex2 < 0 || rowIndex2 >= size) {
        std::cerr << "swapRows: index out of bounds\n";
        return false;
    }

    std::vector<int> tempRow = matrix[rowIndex1];
    matrix[rowIndex1] = matrix[rowIndex2];
    matrix[rowIndex2] = tempRow;
    return true;
}

// swap matrix columns function
bool swapCols(std::vector<std::vector<int>> &matrix, int colIndex1, int colIndex2) {
    int size = int (matrix.size());

    if (colIndex1 < 0 || colIndex1 >= size || colIndex2 < 0 || colIndex2 >= size) {
        std::cerr << "swapCols: index out of bounds\n";
        return false;
    }

    for (int row = 0; row < size; ++row) {
        int tempValue = matrix[row][colIndex1];
        matrix[row][colIndex1] = matrix[row][colIndex2];
        matrix[row][colIndex2] = tempValue;
    }

    return true;
}

// update matrix element function
bool updateElement(std::vector<std::vector<int>> &matrix, int rowIndex, int columnIndex, int newValue) {
    int size = int (matrix.size());

    if (rowIndex < 0 || rowIndex >= size || columnIndex < 0 || columnIndex >= size) {
        std::cerr << "updateElement: index out of bounds\n";
        return false;
    }

    matrix[rowIndex][columnIndex] = newValue;
    return true;
}

// print menu function
void printMenu() {
    std::cout << "Menu:\n";
    std::cout << "  1 - Print matrices A and B\n";
    std::cout << "  2 - Add A + B and print result\n";
    std::cout << "  3 - Multiply A * B and print result\n";
    std::cout << "  4 - Diagonal sums of a matrix (choose A or B)\n";
    std::cout << "  5 - Swap rows in a chosen matrix\n";
    std::cout << "  6 - Swap columns in a chosen matrix\n";
    std::cout << "  7 - Update an element in a chosen matrix\n";
    std::cout << "  8 - Reset A and B to original read-from-file copies\n";
    std::cout << "  0 - Exit\n";
    std::cout << "Enter choice:\n";
    std::cout << "\n";
}

// main function
int main() {
    std::cout << "EECS 348 - Lab 9: Matrix Operations\n";

    std::string filename;
    std::cout << "Enter input filename (e.g. input.txt):\n";
    std::getline(std::cin, filename);

    if (filename.empty()) {
        std::cout << "No filename entered. Exiting.\n";
        return 0;
    }

    int size;
    std::vector<std::vector<int>> firstMatrix;
    std::vector<std::vector<int>> secondMatrix;

    if (!loadMatrices(filename, size, firstMatrix, secondMatrix)) {
        std::cerr << "Failed to load matrices. Exiting.\n";
        return 1;
    }

    std::vector<std::vector<int>> originalFirstMatrix = firstMatrix;
    std::vector<std::vector<int>> originalSecondMatrix = secondMatrix;

    std::cout << "Loaded size = " << size << "\n";
    std::cout << "\n";
    printMatrix(firstMatrix, "Matrix A:");
    printMatrix(secondMatrix, "Matrix B:");

    bool running = true;
    int menuChoice = 0;

    while (running) {
        printMenu();

        if (!(std::cin >> menuChoice)) {
            std::cout << "Invalid input. Exiting.\n";
            running = false;
            continue;
        }

        if (menuChoice == 0) {
            std::cout << "Exiting.\n";
            running = false;
            continue;
        }

        if (menuChoice == 1) {
            printMatrix(firstMatrix, "Matrix A:");
            printMatrix(secondMatrix, "Matrix B:");
            continue;
        }

        if (menuChoice == 2) {
            std::vector<std::vector<int>> sumMatrix = addMatrices(firstMatrix, secondMatrix);
            printMatrix(sumMatrix, "A + B =");
            continue;
        }

        if (menuChoice == 3) {
            std::vector<std::vector<int>> productMatrix = multiplyMatrices(firstMatrix, secondMatrix);
            printMatrix(productMatrix, "A * B =");
            continue;
        }

        if (menuChoice == 4) {
            std::cout << "Which matrix? (A=1, B=2): \n";
            std::cout << "\n";
            int matrixChoice;
            std::cin >> matrixChoice;

            if (matrixChoice == 1) {
                printMatrix(firstMatrix, "Matrix A:");
                diagonalSums(firstMatrix);
            } 
            else if (matrixChoice == 2) {
                printMatrix(secondMatrix, "Matrix B:");
                diagonalSums(secondMatrix);
            } 
            else {
                std::cout << "Invalid choice\n";
                std::cout << "\n";
            }
            continue;
        }

        if (menuChoice == 5) {
            std::cout << "Which matrix? (A=1, B=2): \n";
            std::cout << "\n";
            int matrixChoice;
            std::cin >> matrixChoice;

            std::cout << "Enter first row (starting at 0): \n";
            int rowIndex1;
            std::cin >> rowIndex1;

            std::cout << "Enter second row (starting at 0): \n";
            std::cout << "\n";
            int rowIndex2;
            std::cin >> rowIndex2;

            bool swapped = false;
            if (matrixChoice == 1) {
                swapped = swapRows(firstMatrix, rowIndex1, rowIndex2);
            } 
            else if (matrixChoice == 2) {
                swapped = swapRows(secondMatrix, rowIndex1, rowIndex2);
            } 
            else {
                std::cout << "Invalid matrix choice\n";
                std::cout << "\n";
            }

            if (swapped) {
                std::cout << "Rows swapped. Result:\n";
                if (matrixChoice == 1) {
                    printMatrix(firstMatrix, "Matrix A:");
                } 
                else {
                    printMatrix(secondMatrix, "Matrix B:");
                }
            }
            continue;
        }

        if (menuChoice == 6) {
            std::cout << "Which matrix? (A=1, B=2): \n";
            std::cout << "\n";
            int matrixChoice;
            std::cin >> matrixChoice;

            std::cout << "Enter column (starting at 0): \n";
            int columnIndex1;
            std::cin >> columnIndex1;

            std::cout << "Enter second column (starting at 0): \n";
            int columnIndex2;
            std::cin >> columnIndex2;

            bool swapped = false;
            if (matrixChoice == 1) {
                swapped = swapCols(firstMatrix, columnIndex1, columnIndex2);
            } 
            else if (matrixChoice == 2) {
                swapped = swapCols(secondMatrix, columnIndex1, columnIndex2);
            } 
            else {
                std::cout << "Invalid matrix choice\n";
                std::cout << "\n";
            }

            if (swapped) {
                std::cout << "Columns swapped. Result:\n";
                if (matrixChoice == 1) {
                    printMatrix(firstMatrix, "Matrix A:");
                } 
                else {
                    printMatrix(secondMatrix, "Matrix B:");
                }
            }
            continue;
        }

        if (menuChoice == 7) {
            std::cout << "Which matrix? (A=1, B=2): \n";
            std::cout << "\n";
            int matrixChoice;
            std::cin >> matrixChoice;

            std::cout << "Enter row (starting at 0): \n";
            int rowIndex;
            std::cin >> rowIndex;

            std::cout << "Enter column (starting at 0): \n";
            int columnIndex;
            std::cin >> columnIndex;

            std::cout << "Enter new value: \n";
            int newValue;
            std::cin >> newValue;

            bool updated = false;
            if (matrixChoice == 1) {
                updated = updateElement(firstMatrix, rowIndex, columnIndex, newValue);
            } 
            else if (matrixChoice == 2) {
                updated = updateElement(secondMatrix, rowIndex, columnIndex, newValue);
            } 
            else {
                std::cout << "Invalid matrix choice\n";
                std::cout << "\n";
            }

            if (updated) {
                std::cout << "Element updated. Result:\n";
                if (matrixChoice == 1) {
                    printMatrix(firstMatrix, "Matrix A:");
                } 
                else {
                    printMatrix(secondMatrix, "Matrix B:");
                }
            }
            continue;
        }

        if (menuChoice == 8) {
            firstMatrix = originalFirstMatrix;
            secondMatrix = originalSecondMatrix;
            std::cout << "Matrices reset.\n";
            std::cout << "\n";
            continue;
        }

        std::cout << "Unknown choice.\n";
    }
    return 0;
}
