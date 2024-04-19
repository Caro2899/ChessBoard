#include <iostream>
#include "utility.h"
using namespace std;

ostream& operator<<(ostream& os, const Position& pos)
{
    os << static_cast<char>(pos.file + 'a') << static_cast<char>(pos.rank + '1');
    return os;
}

// TASK 1: Implement the 6 operator overloading functions of Position, Vector and BooleanMap
// You need to write the full function prototypes and implementations

// TODO 1.1: Position::operator==(const Position&) const
bool Position::operator==(const Position& pos) const{
    return(file == pos.file && rank == pos.rank);
}

// TODO 1.2: Vector::operator+(const Position&) const
Position Vector::operator+(const Position& pos) const{
    Position NewPos;
    int f = pos.file+file;
    int r= pos.rank+rank;
    if(f < 0 || f >7 || r < 0|| r >7){
        return pos;
    }
    NewPos.file = static_cast<_FILE>(pos.file + file);
    NewPos.rank = static_cast<_RANK>(pos.rank + rank);
    return NewPos;
}
// TODO 1.3: Vector::operator*(int) const
Vector Vector::operator*(int mul) const{
    Vector NewVector;
    NewVector.file = file*mul;
    NewVector.rank  = rank*mul;
    return NewVector;
}
// TODO 1.4: BooleanMap::operator|=(const BooleanMap&)
BooleanMap& BooleanMap::operator|=(const BooleanMap& other){
    for(int i = 0; i<NUM_RANKS; i++){
        for(int j = 0; j<NUM_FILES; j++){
            cells[i][j] = cells[i][j] || other.cells[i][j];
        }
    }
    return *this;
}
// TODO 1.5: BooleanMap::operator&=(const BooleanMap&)
BooleanMap& BooleanMap::operator&=(const BooleanMap& other){
    for(int i = 0; i<NUM_RANKS; i++){
        for(int j = 0; j<NUM_FILES; j++){
            cells[i][j] = cells[i][j] && other.cells[i][j];
        }
    }
    return *this;
}
// TODO 1.6: BooleanMap::operator~() const
BooleanMap BooleanMap::operator~() const{
    BooleanMap UpdatedMap;
    for(int i = 0; i<NUM_RANKS; i++){
        for(int j = 0; j<NUM_FILES; j++){
            UpdatedMap.cells[i][j] = !cells[i][j];
        }
    }
    return UpdatedMap;
}
