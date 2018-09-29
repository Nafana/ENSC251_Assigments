#include "ShipBoard.h"

ShipBoard::ShipBoard(const int boardLength, const int boardHeight, const int blankCharacter) {
    ShipBoard::boardLength = boardLength;
    ShipBoard::boardHeight = boardHeight;
    ShipBoard::blankCharacter = char(blankCharacter);
    ShipBoard::characterBoard = new char*[boardHeight];
    for(int i=0; i<boardHeight; i++) {
        ShipBoard::characterBoard[i] = new char[boardLength];
    }
    ShipBoard::resetBoard();
}

ShipBoard::~ShipBoard() {
    for(int i=0; i<ShipBoard::boardHeight; i++) {
        delete [] ShipBoard::characterBoard[i];
        ShipBoard::characterBoard[i] = nullptr;
    }
    delete [] ShipBoard::characterBoard;
    ShipBoard::characterBoard = nullptr;
}

void ShipBoard::resetBoard() {
    for(int i=0; i<ShipBoard::boardHeight; i++) {
        for(int j=0; j<ShipBoard::boardLength; j++) {
            ShipBoard::characterBoard[i][j] = ShipBoard::blankCharacter;
        }
    }
}

bool ShipBoard::canPlaceItem(int itemLength, int row, int column,  FaceDirection itemDirection) {
    if (itemDirection == UP) {
        if ((row + 1) - itemLength < 0) return false; 
        for(int i=row; i>row-itemLength; i--) {
            if (ShipBoard::characterBoard[i][column] != ShipBoard::blankCharacter) {
                return false;
            }
        }
        return true;
    } else if(itemDirection == DOWN) {
        if (row + itemLength > ShipBoard::boardHeight) return false;
        for(int i=row; i<row+itemLength; i++) {
            if (ShipBoard::characterBoard[i][column] != ShipBoard::blankCharacter) {
                return false;
            }
        } 
        return true;
    } else if (itemDirection == RIGHT) {
        if (column + itemLength > ShipBoard::boardLength) return false;
        for(int i=column; i<column+itemLength; i++) {
            if (ShipBoard::characterBoard[row][i] != ShipBoard::blankCharacter) {
                return false;
            }
        }
        return true;
    } else if (itemDirection == LEFT) {
        if ((column + 1) - itemLength < 0) return false;
        for(int i=column; i>column-itemLength; i--) {
            if (ShipBoard::characterBoard[row][i] != ShipBoard::blankCharacter) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void ShipBoard::placeItemOnBoard(int itemLength, char itemSymbol, int row, int column, FaceDirection itemDirection) {
    if (itemDirection == UP) {
        for(int i=row; i>row-itemLength; i--) {
            ShipBoard::characterBoard[i][column] = itemSymbol;
        }
    } else if (itemDirection == DOWN) {
        for(int i=row; i<row+itemLength; i++) {
            ShipBoard::characterBoard[i][column] = itemSymbol;
        } 
    } else if (itemDirection == RIGHT) {
        for(int i=column; i<column+itemLength; i++) {
            ShipBoard::characterBoard[row][i] = itemSymbol;
        }
    } else if (itemDirection == LEFT) {
        for(int i=column; i>column-itemLength; i--) {
            ShipBoard::characterBoard[row][i] = itemSymbol;
        }
    }
}

void ShipBoard::printCurrentBoard() {
    for(int i=0; i<ShipBoard::boardHeight; i++) {
        for(int j=0; j<ShipBoard::boardLength; j++) {
            std::cout << ShipBoard::characterBoard[i][j];
        }
        std::cout << std::endl;
    }
}