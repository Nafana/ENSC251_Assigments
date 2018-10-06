#include "ShipBoard.h"

// Constructs the ShipBoard class, initializes the game board.
ShipBoard::ShipBoard(const int &boardLength, const int &boardHeight, const char &blankCharacter) {
    ShipBoard::boardLength = boardLength;
    ShipBoard::boardHeight = boardHeight;
    ShipBoard::blankCharacter = blankCharacter;
    ShipBoard::characterBoard = new char*[boardHeight];
    for(int i=0; i<boardHeight; i++) {
        ShipBoard::characterBoard[i] = new char[boardLength];
    }
    ShipBoard::resetBoard();
}

// Destructs the ShipBoard de-allocating memory 
ShipBoard::~ShipBoard() {
    for(int i=0; i<ShipBoard::boardHeight; i++) {
        delete [] ShipBoard::characterBoard[i];
        ShipBoard::characterBoard[i] = nullptr;
    }
    delete [] ShipBoard::characterBoard;
    ShipBoard::characterBoard = nullptr;
}

// Resets the board by filling it with blank characters
void ShipBoard::resetBoard() {
    for(int i=0; i<ShipBoard::boardHeight; i++) {
        for(int j=0; j<ShipBoard::boardLength; j++) {
            ShipBoard::characterBoard[i][j] = ShipBoard::blankCharacter;
        }
    }
}

// Checks if you can place the item in the up direction
bool ShipBoard::canPlaceItemUp(int &itemLength, int &row, int &column) {
    if ((row + 1) - itemLength < 0) return false; 
        for(int i=row; i>row-itemLength; i--) {
            if (ShipBoard::characterBoard[i][column] != ShipBoard::blankCharacter) {
                return false;
            }
        }
    return true;
}

// Checks if you can place the item down
bool ShipBoard::canPlaceItemDown(int &itemLength, int &row, int &column) {
    if (row + itemLength > ShipBoard::boardHeight) return false;
        for(int i=row; i<row+itemLength; i++) {
            if (ShipBoard::characterBoard[i][column] != ShipBoard::blankCharacter) {
                return false;
            }
        } 
    return true;
}

// Checks if you can place the item right
bool ShipBoard::canPlaceItemRight(int &itemLength, int &row, int &column) {
    if (column + itemLength > ShipBoard::boardLength) return false;
        for(int i=column; i<column+itemLength; i++) {
            if (ShipBoard::characterBoard[row][i] != ShipBoard::blankCharacter) {
                return false;
            }
        }
    return true;
}

// Checks if you can place the item left
bool ShipBoard::canPlaceItemLeft(int &itemLength, int &row, int &column) {
    if ((column + 1) - itemLength < 0) return false;
        for(int i=column; i>column-itemLength; i--) {
            if (ShipBoard::characterBoard[row][i] != ShipBoard::blankCharacter) {
                return false;
            }
        }
    return true;
}

// Checks if you can place an item with a specified length, at a coordinate with a direction.
bool ShipBoard::canPlaceItem(int &itemLength, int &row, int &column, FaceDirection itemDirection) {
    switch(itemDirection) {
        case UP:
            return ShipBoard::canPlaceItemUp(itemLength, row, column);
        case DOWN:
            return ShipBoard::canPlaceItemDown(itemLength, row, column);
        case RIGHT:
            return ShipBoard::canPlaceItemRight(itemLength, row, column);
        case LEFT:
            return ShipBoard::canPlaceItemLeft(itemLength, row, column);
        default:
            return false;
    }
}

// Places the item on the board, assumes you checked that you can place the item.
void ShipBoard::placeItemOnBoard(int &itemLength, char &itemSymbol, int &row, int &column, FaceDirection itemDirection) {
    switch(itemDirection) {
        case UP: {
            for(int i=row; i>row-itemLength; i--) {
                ShipBoard::characterBoard[i][column] = itemSymbol;
            }
            return;
        }
        case DOWN: {
            for(int i=row; i<row+itemLength; i++) {
                ShipBoard::characterBoard[i][column] = itemSymbol;
            }
            return;
        }
        case LEFT: {
            for(int i=column; i<column+itemLength; i++) {
                ShipBoard::characterBoard[row][i] = itemSymbol;
            }
            return;
        }
        case RIGHT: {
            for(int i=column; i>column-itemLength; i--) {
                ShipBoard::characterBoard[row][i] = itemSymbol;
            }
            return;
        }
        default: 
            return;
    }
}

// Prints the current board to the screen
void ShipBoard::printCurrentBoard() {
    for(int i=0; i<ShipBoard::boardHeight; i++) {
        for(int j=0; j<ShipBoard::boardLength; j++) {
            std::cout << ShipBoard::characterBoard[i][j];
        }
        std::cout << std::endl;
    }
}