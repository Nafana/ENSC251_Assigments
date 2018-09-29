#include <iostream>

enum FaceDirection {UP, DOWN, LEFT, RIGHT};

class ShipBoard {
public:
    ShipBoard(const int boardLength, const int boardHeight, const int blankCharacter);
    ~ShipBoard();

    void resetBoard();
    void printCurrentBoard();
    
    void placeItemOnBoard(int itemLength, char itemSymbol, int row, int column, FaceDirection itemDirection);
    bool canPlaceItem(int itemLength, int row, int column, FaceDirection itemDirection);

    int getBoardLength() {return boardLength;}
    int getBoardHeight() {return boardHeight;}
private:
    int boardLength;
    int boardHeight;
    char blankCharacter;
    char** characterBoard;
};