#include "Pawn.h"

bool inRange(const int& i, const int& j);

Pawn::Pawn(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {
    cout << &this->grid << endl;
}

Pawn::~Pawn() {}

void Pawn::move(const int& i, const int& j) {
    // if (isValid(i, j)) {
    //     this->grid[i][j] = this->grid[this->i][this->j];
    //     this->grid[this->i][this->j] = nullptr;
    //     this->i = i;
    //     this->j = j;
    //     this->moved = true;
    // }
}

vector<pair<int,int>> Pawn::getValidMoves() const {

    vector<pair<int,int>> validMoves{};

    if (inRange(this->i - (this->white ? 1 : -1), this->j)) {
        // Condition where pawn moves forward
        if (this->grid[this->i - (this->white ? 1 : -1)][j] == nullptr) {
            // Condition where square in front is empty
            validMoves.push_back({this->i - (this->white ? 1 : -1), this->j});
            if (inRange(this->i - (this->white ? 2 : -2), j) && this->getNumMoves() == 0) {
                if (this->grid[this->i - (this->white ? 2 : -2)][j] == nullptr) {
                    // Condition where square two spaces ahead is empty
                    validMoves.push_back({this->i - (this->white ? 2 : -2), j});
                }
            }
        }
        // Conditions where pawn attacks upper diagonal squares
        if (inRange(this->i - (this->white ? 1 : -1), this->j + 1)) {
            Piece* piece{this->grid[this->i - (this->white ? 1 : -1)][this->j + 1]};
            if (piece != nullptr && piece->white != this->white) {
                validMoves.push_back({this->i - (this->white ? 1 : -1), this->j + 1});
            }
        }
        if (inRange(this->i - (this->white ? 1 : -1), this->j - 1)) {
            Piece* piece{this->grid[this->i - (this->white ? 1 : -1)][this->j - 1]};
            if (piece != nullptr && piece->white != this->white) {
                validMoves.push_back({this->i - (this->white ? 1 : -1), this->j - 1});
            }
        }
    }

    return validMoves;

}

bool Pawn::isValid(const int&i, const int& j) const {
    if (!(i >= 0 && i <= 7 && j >= 0 && j <= 7)) {
        // Condition where pawn is outside of board range
        return false;
    }

    // if () king is exposed, return false

    // en passant

    if (this->j == j) {
        // Condition where pawn moves vertically
        if (this->i - i == (this->white ? 2 : -2) && this->getNumMoves() == 0) {
            // Condition where pawn moves 2 steps forward and hasn't moved before
            if (this->grid[i][j] == nullptr && this->grid[i - (this->white ? 1 : -1)][j] == nullptr) {
                // Condition that nothing is blocking the pawn's way
                return true;
            }
        } else if (this->i - i == (this->white ? 1 : -1)) {
            // Condition where pawn moves 1 step forward
            if (this->grid[i][j] == nullptr) {
                // Condition where nothing is blocking pawn's way
                return true;
            }
        }
    } else if (abs(this->j - j) == 1) {
        // Condition where pawn moves left or right by 1
        if (this->i - i == (this->white ? 1 : -1)) {
            // Condition where pawn moves forward by 1
            return true;
        }
    }
    return false;
}


string Pawn::getName() const {
    return "Pawn";
}

string Pawn::getSHName() const {
    return "p";
}