#include <iostream>
#include <cstdlib>
#include "ShipBoard.h"

bool tryPlaceShip(ShipBoard* shipBoard, int shipLength, char shipSymbol, int row, int column);

int main() {
    const int BOARD_LENGTH = 8;
    const int BOARD_HEIGHT = 8;
    const int BLANK_CHARACTER = 32;

    const int BATTLESHIP_LENGTH = 4; const char BATTLESHIP_SYMBOL = 'B'; int REMAINING_BATTLESHIPS = 1;
    const int CRUISER_LENGTH = 3; const char CRUISER_SYMBOL = 'C'; int REMAINING_CRUISER = 2;
    const int CARGO_SHIP_LENGTH = 2; const char CARGO_SHIP_SYMBOL = 'S'; int REMAINING_CARGOSHIPS = 5;
    const int SUBMARINE_LENGTH = 1; const char SUBMARINE_SYMBOL = '_'; int REMAINING_SUBMARINE = 10;

    const int BATTLESHIP_QUANTITY = 1;
    const int CRUISER_QUANTITY = 2;
    const int CARGO_SHIP_QUANTITY = 5;
    const int SUBMARINE_QUANTITY = 10;

    const int BOARDS_TO_GENERATE = 100;

    int randomRow;
    int randomColumn;
    bool foundFit = false;

    ShipBoard* gameBoard = new ShipBoard(BOARD_LENGTH, BOARD_HEIGHT, char(BLANK_CHARACTER));

    for(int i = 0; i<BOARDS_TO_GENERATE; i++) {
        while(REMAINING_BATTLESHIPS + REMAINING_CARGOSHIPS + REMAINING_CRUISER + REMAINING_SUBMARINE > 0) {
            randomRow = rand() % BOARD_HEIGHT;
            randomColumn = rand() % BOARD_LENGTH;
            foundFit = false;

            if(REMAINING_BATTLESHIPS > 0) {
                foundFit = tryPlaceShip(gameBoard, BATTLESHIP_LENGTH, BATTLESHIP_SYMBOL, randomRow, randomColumn);
                if (foundFit) REMAINING_BATTLESHIPS--;
            }

            if (!foundFit && REMAINING_CARGOSHIPS > 0) {
                foundFit = tryPlaceShip(gameBoard, CARGO_SHIP_LENGTH, CARGO_SHIP_SYMBOL, randomRow, randomColumn);
                if(foundFit) REMAINING_CARGOSHIPS--;
            }

            if (!foundFit && REMAINING_CRUISER > 0) {
                foundFit = tryPlaceShip(gameBoard, CRUISER_LENGTH, CRUISER_SYMBOL, randomRow, randomColumn);
                if(foundFit) REMAINING_CRUISER--;
            }

            if (!foundFit && REMAINING_SUBMARINE > 0) {
                foundFit = tryPlaceShip(gameBoard, SUBMARINE_LENGTH, SUBMARINE_SYMBOL, randomRow, randomColumn);
                if(foundFit) REMAINING_SUBMARINE--;
            }
        }
        gameBoard->printCurrentBoard();
        gameBoard->resetBoard();
        REMAINING_BATTLESHIPS = BATTLESHIP_QUANTITY;
        REMAINING_CRUISER = CRUISER_QUANTITY;
        REMAINING_CARGOSHIPS = CARGO_SHIP_QUANTITY;
        REMAINING_SUBMARINE = SUBMARINE_QUANTITY;
        std::cout << std::endl;
    }

    delete gameBoard;
    return 0;
}

// Try to place the ship at a coordinate in any direction necessary.
// Only places the ships in the vertical direction (UP/DOWN)
bool tryPlaceShip(ShipBoard* shipBoard, int shipLength, char shipSymbol, int row, int column) {
    for(int i = 0; i < 2; i++) {
        if (shipBoard->canPlaceItem(shipLength, row, column, FaceDirection(i))) {
            shipBoard->placeItemOnBoard(shipLength, shipSymbol, row, column, FaceDirection(i));
            return true;
        }
    }
    return false;
}

