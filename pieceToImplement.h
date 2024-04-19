// // TASK 3: Implement the 4 Piece-derived classes here
// // All classes will inherit the NamedPiece class 
// // and implement the remaining pure virtual functions


// // TODO 3.1: Leaper class
template <char N, int F, int R>
class Leaper: public NamedPiece<N>{
    public:
        Leaper(Color color): NamedPiece<N>(color){}
        Piece* clone() const override{
            return (new Leaper<N, F, R>(*this));
        }
        BooleanMap getMoves(const Board& board) const override{
            BooleanMap movesmap;
            Position pos = this->getPosition();
            Position newPos;
            if(board.piece(pos) ->isWhite() == true){
                if(pos.file + F < 0 || pos.file + F > 7 || pos.rank + R < 0 || pos.rank + R > 7){
                    return movesmap;
                }
                newPos.file = static_cast<_FILE>(pos.file + F);
                newPos.rank = static_cast<_RANK>(pos.rank + R);
            }
            else{
                if(pos.file - F < 0 || pos.file - F > 7 || pos.rank - R < 0 || pos.rank - R > 7){
                    return movesmap;
                }
                newPos.file = static_cast<_FILE>(pos.file - F);
                newPos.rank = static_cast<_RANK>(pos.rank - R);
            }
            if(!board.piece(newPos)|| board.piece(newPos)->getColor() != this->getColor()){
                movesmap.cell(newPos) = true;
            }
            return movesmap;
        }

};

// // TODO 3.2: Rider class
template <char N, int F, int R, int RANGE>
class Rider: public NamedPiece<N>{
    public:
        Rider(Color color): NamedPiece<N>(color){}
        Piece* clone() const override{
            return (new Rider<N, F, R, RANGE>(*this));
        }
        BooleanMap getMoves(const Board& board) const override{
            BooleanMap movesmap;
            Position pos = this->getPosition();
            Position newPos;
            if(board.piece(pos) ->isWhite() == true){
                for(int i = 1; i<=RANGE; i++){
                    newPos=Vector{F,R}*1+pos;  
                    pos= newPos;
                    if(!board.piece(newPos)){
                        movesmap.cell(newPos) = true;
                    }
                    else if(board.piece(newPos)->getColor() != this->getColor()){
                        movesmap.cell(newPos) = true;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
            else{
                for(int i = 1; i<=RANGE; i++){
                    newPos=Vector{F,R}*-1+pos;  
                    pos= newPos;
                    if(!board.piece(newPos)){
                        movesmap.cell(newPos) = true;
                    }
                    else if(board.piece(newPos)->getColor() != this->getColor()){
                        movesmap.cell(newPos) = true;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
            return movesmap;
        }
};
// // TODO 3.3: Compound class
template <char N, typename P1, typename P2>
class Compound: public NamedPiece<N>{
    public:
        Compound(Color color): NamedPiece<N>(color){}
        Piece* clone() const override{
            return (new Compound<N, P1, P2>(*this));
        }
        BooleanMap getMoves(const Board& board) const override{
            P1* piece1 = new P1(this->color);
            P2* piece2 = new P2(this->color);

            BooleanMap moves1 = piece1->getMoves(board.getTempBoard(piece1, this->getPosition()));
            BooleanMap moves2 = piece2->getMoves(board.getTempBoard(piece2, this->getPosition()));
            moves1 |= moves2;
            return moves1;
        }

        

};
// // TODO 3.4: Divergent class
template <char N, typename M, typename C>
class Divergent: public NamedPiece<N>{
    public:
        Divergent(Color color): NamedPiece<N>(color){}
        Piece* clone() const override{
            return (new Divergent<N, M, C>(*this));
        }
        BooleanMap getMoves(const Board& board) const override {
        M* mpiece = new M(this->color);
        C* cpiece = new C(this->color);

        BooleanMap movesm = mpiece->getMoves(board.getTempBoard(mpiece, this->getPosition()));
        BooleanMap movesc = cpiece->getMoves(board.getTempBoard(cpiece, this->getPosition()));

        BooleanMap opponentMap = board.getOpponentMap(this->getColor());

        movesc &= opponentMap;
        BooleanMap temp = ~opponentMap;
        movesm &= temp;

        movesc |= movesm;

        return movesc;
    }
};
