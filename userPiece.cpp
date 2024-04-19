#include "userPiece.h"

// TASK 4.2: isRoyal(const Piece*)
// TODO

bool isRoyal(const Piece* piece){
    const King* king = dynamic_cast<const King*>(piece);
    return king != nullptr;
}

// TASK 4.3: Implement any Pawn function(s) here if needed
Pawn::Pawn(Color color) :Divergent<'P',Leaper<'O',0,1>, Compound<'P',Leaper<'P',1,1>,Leaper<'P',-1,1>>>(color) {
}

Piece* Pawn::clone() const {
    return new Pawn(*this);
}

BooleanMap Pawn::getMoves(const Board& board) const {
    BooleanMap moveMap = Divergent<'P',Leaper<'O',0,1>, Compound<'P',Leaper<'P',1,1>,Leaper<'P',-1,1>>>::getMoves(board);

    Position currentPosition = this->getPosition();
    _RANK currentRank = currentPosition.rank;

    // Determine the direction of movement based on the pawn's color
    int direction = (this->getColor() == WHITE) ? 1 : -1;

    // Check if the pawn has not moved yet
    if ((this->getColor() == WHITE && currentRank == _2) || (this->getColor() == BLACK && currentRank == _7)) {
        // Check if the next square is empty and add it to the moves
        Position nextPosition = currentPosition;
        nextPosition.rank = static_cast<_RANK>(currentRank + 2 * direction);
        if (board.piece(nextPosition) == nullptr) {
            moveMap.cell(nextPosition) = true;
        }
    }
    return moveMap;
}

