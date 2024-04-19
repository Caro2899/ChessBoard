# ChessBoard
Chess Game

We will make use of the C++ concepts: inheritance, polymorphism, templates and operator overloading to create different pieces in the game of chess. We will create not only the basic 6 pieces used in international chess, but also other [fairy chess pieces](https://en.wikipedia.org/wiki/Fairy_chess_piece) used in chess variants. While there are numerous variant pieces with different complexity of moves and rules, many of the simple pieces fall into a few categories which we will implement using C++ template classes.

If you are not familiar with the basic rules of chess, you may read the rules [here](https://en.wikipedia.org/wiki/Chess). Brief explanations of the relevant concepts will also be included where necessary.

Brief overview: The class Board is a chessboard representing an 8x8 grid of squares, which are pointers that may point to Piece-derived objects. The classes deriving Piece will be implemented to represent different movement categories of chess pieces, utilizing several custom data types such as Position, Vector and BooleanMap for convenient calculation.

Utilities

The files utility.h and utility.cpp define some constants, structs and classes that will be helpful for processing chess piece classes.
enum _FILE { _A, _B, _C, _D, _E, _F, _G, _H };
enum _RANK { _1, _2, _3, _4, _5, _6, _7, _8 };
The enums _FILE and _RANK represent the coordinates of the chessboard, which is an 8x8 grid. For example, arr[_8][_A] is the same as arr[7][0], and represents the following cell on the board:
---------------------------------
| x |   |   |   |   |   |   |   | 8
---------------------------------
|   |   |   |   |   |   |   |   | 7
---------------------------------
|   |   |   |   |   |   |   |   | 6
---------------------------------
|    |   |   |   |   |   |   |   | 5
---------------------------------
|   |   |   |   |   |   |   |   | 4
---------------------------------
|   |   |   |   |   |   |   |   | 3
---------------------------------
|   |   |   |   |   |   |   |   | 2
---------------------------------
|   |   |   |   |   |   |   |   | 1
---------------------------------
  a   b   c   d   e   f   g   h
  //
  
Note that the board is displayed in a similar orientation as an actual chessboard (starting from rank 8).
struct Position {
    _FILE file;
    _RANK rank;

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);

    bool operator==(const Position& pos) const;
};
The struct Position encodes the position of a cell on the chessboard - therefore, it contains the coordinates file and rank. The friend operator<< is implemented for cout operations - this is already implemented for you. The function operator== will need to be implemented to check whether 2 Positions are the same.
struct Vector {
    int file;
    int rank;

    Position operator+(const Position& pos) const;
    Vector operator*(int mul) const;
};
The struct Vector represents an arrow from one Position to another. Because an arrow can go backwards, the file and rank components are signed integers. You will need to implement 2 operators: one to add a Vector with a Position to get a new Position, and one to multiply a Vector with a number.
class BooleanMap {
    private:
        bool cells[NUM_RANKS][NUM_FILES] {};

    public:
        bool& cell(_FILE f, _RANK r) { return cells[r][f]; }
        bool& cell(const Position& pos) { return cells[pos.rank][pos.file]; }
        bool cell(_FILE f, _RANK r) const { return cells[r][f]; }
        bool cell(const Position& pos) const { return cells[pos.rank][pos.file]; }

        BooleanMap& operator|=(const BooleanMap& other);
        BooleanMap& operator&=(const BooleanMap& other);
        BooleanMap operator~() const;
};
The class BooleanMap is an 8x8 array of booleans, which is used for several chess piece calculations (e.g. the map represents which cells the current piece can move to). It is initialized to be all false, and the cells can be modified afterwards. The function cell is provided for convenient access and modification of the array; instead of directly accessing the array, you can call this function e.g. cell(_A, _8) and not have to worry about out-of-bound index or confusing rows and columns.
You will need to implement 3 operators (these are similar to basic operators such as + or +=) to perform bitwise operations with another BooleanMap (bitwise OR and bitwise AND), or to negate all values in a 2D array.


Piece
The files piece.h and pieceToImplement.h define the base classes of the different chess pieces.

class Piece {
    private:
        virtual char name() const = 0;

    protected:
        Position position;
        Color color;

    public:
        Piece(Color color): color(color) {}
        virtual ~Piece() = default;

        virtual Piece* clone() const = 0;

        char getName() const { return name() - (isWhite() ? 0 : 'A' - 'a'); }
        Position getPosition() const { return position; }
        Color getColor() const { return color; }

        bool isWhite() const { return color == WHITE; }
        bool isOpponent(const Piece& other) const { return color != other.color; }

        void setPosition(const Position& pos) { position = pos; }

        virtual BooleanMap getMoves(const Board& board) const = 0;
};
The class Piece is the base class of all chess pieces. It is an abstract base class, since it contains pure virtual functions that will need to be implemented by the derived classes. Its data members include:
position: The piece's current Position. It needs to be updated whenever the piece is moved on the Board.
color: The piece's Color, which is an enum indicating whether the piece is WHITE or BLACK.
This class contains the following 3 pure virtual functions:
name: Return the character representing the piece type. For example, 'R' is typically used to represent a Rook piece.
clone: Return a dynamic-allocated instance of the concrete derived class. Since Board contains pointers to Piece-derived objects but cannot know what concrete classes will be implemented, it needs to use this function when copying pieces in the copy constructor.
getMoves: Return a BooleanMap indicating where this piece can move to (including captures).
The remaining member functions are provided for accessing the data members, or to modify the piece's Position.

template <char N>
class NamedPiece : public Piece {
	private:
		virtual char name() const override { return N; }
	
	public:
		NamedPiece(Color color): Piece(color) {}
};

NamedPiece is a template class that inherits the Piece class. It implements the name function, which returns the template parameter N. The purpose of this class is for the further-derived classes to inherit this class and not have to re-implement the name function.

template <char N, int F, int R>
class Leaper;

template <char N, int F, int R, int RANGE = MAX_RANGE>
class Rider;

template <char N, typename P1, typename P2>
class Compound;

template <char N, typename M, typename C>
class Divergent;

These 4 classes are the categories of chess pieces that you will need to implement in pieceToImplement.h. These classes will inherit the NamedPiece template class and implement the remaining 2 pure virtual functions, such that instantiations of them will behave as fully-functional chess pieces. The Tasks section will describe in detail what each class should represent.

User-defined Pieces
The files userPiece.h and userPiece.cpp are where the user can define the actual concrete Piece-derived classes. With the templates defined above and the using keyword, we can define most pieces here without having to write a new class definition. Some special cases will still need a class/function definition, which is described in the Tasks section.


Board
The files board.h, board.cpp and boardToImplement.cpp define the class representing a chessboard.

class Board {
    friend class BoardTester;
    
    protected: 
        Piece* pieces[NUM_RANKS][NUM_FILES];
        bool isWhiteTurn {true};
        Piece* selectedPiece {nullptr};
        BooleanMap moveMap;
        Piece* royalPieces[2] {nullptr, nullptr};

        Piece*& piece(_FILE f, _RANK r) { return pieces[r][f]; }
        Piece*& piece(const Position& pos) { return pieces[pos.rank][pos.file]; }

        virtual void move(const Position& destPos);
        BooleanMap getAttackingMap() const;
        void validateMoveMap();

    public:
        Board(): pieces{nullptr} {}
        Board(const Board& board);
        virtual ~Board();

        const Piece* piece(_FILE f, _RANK r) const { return pieces[r][f]; }
        const Piece* piece(const Position& pos) const { return pieces[pos.rank][pos.file]; }

        void addPiece(Piece* piece, const Position& pos);

        bool select(const Position& pos);

        Board getTempBoard(Piece* newPiece, const Position& pos) const;
        BooleanMap getOpponentMap(bool white) const;

        void display() const;
};

The class Board represents the chessboard, containing pointers to Piece objects and other attributes. Here is the list of all Board data members:
pieces: A 2D array of pointers to dynamic-allocated Piece-derived objects. nullptr represents a square with no piece on it (an empty board would therefore be all nullptr). We suggest using the provided piece function to access this array using _FILE, _RANK or Position, similar to BooleanMap.
isWhiteTurn: A boolean representing whether the current turn is White's or Black's. By default, this is set to true as White moves first. This boolean should be toggled whenever a move is made.
selectedPiece: A pointer to the "selected" Piece. The user selects a piece in order to move it each turn. If the pointer is nullptr, no piece is selected.
moveMap: When a piece is selected, this BooleanMap indicates which square the piece can move to. When no piece is selected, the map becomes all false.
royalPieces: An array of 2 pointers to the "royal" pieces, one for each player. Royal pieces cannot be captured, and therefore affects the movement of other pieces. For example, in international chess, you cannot move a piece if it allows your King to be captured.
Note that the class contains some inheritance keywords such as protected and virtual, since we will extend this class with another class later. However, it is outside of the requirements for this assignment, so you can treat them as private members and non-virtual functions. Additionally, we declare the class BoardTester to be a friend of this class. Its purpose is for main_test.cpp to be able to access Board's private members.
The public member functions have been implemented in board.cpp. You can read the comments in board.h or board.cpp to understand what they do, as you may need to use them for other tasks. The protected member functions, copy constructor and destructor will need to be implemented in boardToImplement.cpp.


User-defined Board
There are several rules in chess that cannot be represented using simple piece movesets, but rather some special attributes of the board. Therefore, the class WesternBoard is given in userBoard.h to implement (most of) the remaining special rules, by inheriting the Board class. You don't need to handle this class, it is given to you so that once you finish the tasks, you can play a (mostly) complete game of international chess after compiling with main.cpp. Feel free to take a look at it to get references on how to write your functions.


main.cpp
The main code used in the sample program. To compile with this file, run make in the terminal. You can play with it and compare the behaviour with the sample program; however all tasks must be completed for the code to compile.


main_test.cpp
Most of the code are disabled at the beginning, which can be enabled by uncommenting corresponding lines in taskProgress.h. After completing each task, follow the described steps to enable the test cases and compare your output with the given sample outputs. To compile with this file, run make test in the terminal.

Important: The file taskProgress.h is one of the files to be submitted. You need to uncomment the corresponding tasks as you finish them. If you cannot complete a task, leave it commented and submit to ZINC - your program should still be able to compile and you can run the other test cases, but you will lose points for the unimplemented tasks.
