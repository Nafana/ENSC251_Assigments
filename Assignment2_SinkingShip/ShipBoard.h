#include <iostream>

enum FaceDirection {UP=0, DOWN=1, LEFT=2, RIGHT=3};

class ShipBoard {
public:
    // Constructs the ShipBoard class, initializes the game board.
    ShipBoard(const int &boardLength, const int &boardHeight, const char &blankCharacter);
    // Destructs the ShipBoard de-allocating memory 
    ~ShipBoard();

    // Resets the board by filling it with blank characters
    void resetBoard();
    // Prints the current board to the screen
    void printCurrentBoard();
    
    // Places the item on the board, assumes you checked that you can place the item.
    void placeItemOnBoard(int &itemLength, char &itemSymbol, int &row, int &column, FaceDirection itemDirection);
    // Checks if you can place the item in the up direction
    bool canPlaceItem(int &itemLength, int &row, int &column, FaceDirection itemDirection);
    // Checks if you can place the item up
    bool canPlaceItemUp(int &itemLength, int &row, int &column);
    // Checks if you can place the item down
    bool canPlaceItemDown(int &itemLength, int &row, int &column);
    // Checks if you can place the item right
    bool canPlaceItemRight(int &itemLength, int &row, int &column);
    // Checks if you can place the item left
    bool canPlaceItemLeft(int &itemLength, int &row, int &column);

    int getBoardLength() {return boardLength;}
    int getBoardHeight() {return boardHeight;}
private:
    int boardLength;
    int boardHeight;
    char blankCharacter; // The character used to fill empty spots with no items
    char** characterBoard; // The board where items are placed
};