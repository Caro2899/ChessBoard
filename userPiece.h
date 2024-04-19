#ifndef __USERPIECE_H__
#define __USERPIECE_H__

#include "piece.h"

bool isRoyal(const Piece* piece);

// The following 2 classes are given as example
using Knight = OmniLeaper<'N', 2, 1>;

using Rook = OmniRider<'R', 1, 0>;

// TASK 4.1: Define the 3 classes Bishop, Queen, King similar to above
// TODO
using Bishop = OmniRider<'B', 1, 1>;

using Queen = Compound<'Q',Rook,Bishop>;

using King = Compound<'K', OmniLeaper<'T', 1, 1>, OmniLeaper<'L',1,0>>;



// TASK 4.3: Define the Pawn class
// TODO

class Pawn : public Divergent<'P',Leaper<'O',0,1>, Compound<'P',Leaper<'P',1,1>,Leaper<'P',-1,1>>>{
    public:
        Pawn(Color color);
        Piece* clone() const override;
        BooleanMap getMoves(const Board& board) const override;
};

#endif // __USERPIECE_H__