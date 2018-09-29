#include <iostream>
#include <cstdlib>
#include "ShipBoard.h"

// BATTLESHIP: Length 4, Quantity: 1
// CRUISER: Length 3,  Quantity: 2
// CARGO_SHIP: Length 2, Quantity: 5
// SUBMARINE: Length 1, Quantity: 10

bool tryPlaceShip(ShipBoard* shipBoard, int shipLength, char shipSymbol, int row, int column);

int main() {
    const int BOARD_LENGTH = 8;
    const int BOARD_HEIGHT = 8;
    const int BLANK_CHARACTER = 39;

    const int BATTLESHIP_LENGTH = 4; const char BATTLESHIP_SYMBOL = 'B'; int REMAINING_BATTLESHIPS = 1;
    const int CRUISER = 3; const char CRUISER_SYMBOL = 'C'; int REMAINING_CRUISER = 2;
    const int CARGO_SHIP = 2; const char CARGO_SHIP_SYMBOL = 'S'; int REMAINING_CARGOSHIPS = 5;
    const int SUBMARINE = 1; const char SUBMARINE_SYMBOL = '_'; int REMAINING_SUBMARINE = 10;

    int randomRow;
    int randomColumn;
    bool foundFit = false;

    std::cout << "--BEGIN_BOARD--" << std::endl;
    ShipBoard gameBoard(BOARD_LENGTH, BOARD_HEIGHT, BLANK_CHARACTER);
    for(int i = 0; i<100; i++) {
        while(REMAINING_BATTLESHIPS + REMAINING_CARGOSHIPS + REMAINING_CRUISER + REMAINING_SUBMARINE > 0) {
            randomRow = rand() % BOARD_HEIGHT;
            randomColumn = rand() % BOARD_LENGTH;
            foundFit = false;

            if(REMAINING_BATTLESHIPS > 0) {
                foundFit = tryPlaceShip(&gameBoard, BATTLESHIP_LENGTH, BATTLESHIP_SYMBOL, randomRow, randomColumn);
                if (foundFit) REMAINING_BATTLESHIPS--;
            }

            if (!foundFit && REMAINING_CARGOSHIPS > 0) {
                foundFit = tryPlaceShip(&gameBoard, CARGO_SHIP, CARGO_SHIP_SYMBOL, randomRow, randomColumn);
                if(foundFit) REMAINING_CARGOSHIPS--;
            }

            if (!foundFit && REMAINING_CRUISER > 0) {
                foundFit = tryPlaceShip(&gameBoard, CRUISER, CRUISER_SYMBOL, randomRow, randomColumn);
                if(foundFit) REMAINING_CRUISER--;
            }

            if (!foundFit && REMAINING_SUBMARINE > 0) {
                foundFit = tryPlaceShip(&gameBoard, SUBMARINE, SUBMARINE_SYMBOL, randomRow, randomColumn);
                if(foundFit) REMAINING_SUBMARINE--;
            }
            //std::cout << REMAINING_BATTLESHIPS << " " << REMAINING_CARGOSHIPS << " " << REMAINING_CRUISER << " " << REMAINING_SUBMARINE << std::endl;
        }
        gameBoard.printCurrentBoard();
        gameBoard.resetBoard();
        REMAINING_BATTLESHIPS = 1;
        REMAINING_CARGOSHIPS = 2;
        REMAINING_CRUISER = 5;
        REMAINING_SUBMARINE = 10;
        std::cout << std::endl;
    }
    std::cout << "--END_BOARD--" << std::endl;

    return 0;
}

bool tryPlaceShip(ShipBoard* shipBoard, int shipLength, char shipSymbol, int row, int column) {
    if (shipBoard->canPlaceItem(shipLength, row, column, UP)) {
        shipBoard->placeItemOnBoard(shipLength, shipSymbol, row, column, UP);
        return true;
    } else if (shipBoard->canPlaceItem(shipLength, row, column, DOWN)) {
        shipBoard->placeItemOnBoard(shipLength, shipSymbol, row, column, DOWN);
        return true;
    } else if (shipBoard->canPlaceItem(shipLength, row, column, RIGHT)) {
        shipBoard->placeItemOnBoard(shipLength, shipSymbol, row, column, RIGHT);
        return true;
    } else if (shipBoard->canPlaceItem(shipLength, row, column, LEFT)) {
        shipBoard->placeItemOnBoard(shipLength, shipSymbol, row, column, LEFT);
        return true;
    }
    //std::cout << "COULDN'T PLACE SHIP OF LENGTH=" << shipLength << " AT row=" << row << " AT COLUMN=" << column << std::endl;
    return false;
}

