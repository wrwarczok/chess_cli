#include <ctype.h>

enum Figure
{
    king,queen,rook,bishop,knight,pawn
};

class Piece
{
    bool isBlack;
    Figure figure_type;
    public:
    Piece() {};
    Piece(bool new_isBlack, Figure new_figure_type)
    {
        isBlack=new_isBlack;
        figure_type=new_figure_type;
    }
    void setPiece(bool new_isBlack, Figure new_figure_type)
    {
        isBlack=new_isBlack;
        figure_type=new_figure_type;
    }
    bool getBlackness()
    {
        return isBlack;
    }
    char renderPiece()
    {
        char c='?';
        switch(figure_type)
        {
            case king:  c='k';
                        break;
            case queen: c='q';
                        break;
            case rook:  c='r';
                        break;
            case bishop:c='b';
                        break;
            case knight:c='n';
                        break;
            case pawn:  c='p';
                        break;
        }
        if(isBlack)
            c=toupper(c);
        return c;
    }
    Figure getType()
    {
        return figure_type;
    }
};