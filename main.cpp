#include<stdio.h>
#include<iostream>

#include"pieces.h"

void initChessboard(Piece* chessboard[8][8], Piece pieces[32])
{
    int tmp=0;
    bool isBlack = 1;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chessboard[i][j]=NULL;
            if(i==6)
                isBlack=0;
            if(i==0 || i==7)
            {
                switch(j)
                {
                    case 0:
                    case 7: chessboard[i][j]=&pieces[tmp];
                            pieces[tmp++].setPiece(isBlack,rook);
                            break;
                    case 1:
                    case 6: chessboard[i][j]=&pieces[tmp];
                            pieces[tmp++].setPiece(isBlack,knight);
                            break;
                    case 2:
                    case 5: chessboard[i][j]=&pieces[tmp];
                            pieces[tmp++].setPiece(isBlack,bishop);
                            break;
                    case 3: chessboard[i][j]=&pieces[tmp];
                            pieces[tmp++].setPiece(isBlack,king);
                            break;
                    case 4: chessboard[i][j]=&pieces[tmp];
                            pieces[tmp++].setPiece(isBlack,queen);
                            break;
                }
            }
            else if (i==1 || i==6)
            {
                chessboard[i][j]=&pieces[tmp];
                pieces[tmp++].setPiece(isBlack,pawn);
            }
        }
    }
}

void renderChessboard(Piece* chessboard[8][8], Piece pieces[32])
{
    for(int i=0; i<8; i++)
    {
        std::cout<<8-i<<'|';
        for(int j=0; j<8; j++)
        {
            if (chessboard[i][j]!=NULL)
                std::cout<<chessboard[i][j]->renderPiece();
            else
                if((i+j)%2)
                    std::cout<<'_';
                else
                    std::cout<<' ';
        }
        std::cout<<'|'<<std::endl;
    }
    std::cout<<" +--------+\n"<<"  abcdefgh\n";
}

bool move(Piece* chessboard[8][8], Piece pieces[], unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, bool blacksMove)
{
    if (chessboard[7-(y1-'1')][x1-'a'] != NULL)
    {
        bool isLegal;
        switch( chessboard[7-(y1-'1')][x1-'a']->getType() )
        {
            case king:  isLegal = (abs(x1-x2)<=1 && abs(y1-y2)<=1); //if target is 1 tile away both horizontally and vertically at most
                        break;
            case queen: isLegal = (x1==x2 || y1==y2) || (abs(x1-x2)==abs(y1-y2)); //rook or bishop
                        if(x1-x2>0) //checking spaces between origin and target for pieces
                        {
                            if (y1-y2>0)
                                for(unsigned int i=0; i<y1-y2-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')+i+1][x1-'a'-i-1] == NULL);
                            else if (y1-y2<0)
                                for(unsigned int i=0; i<y2-y1-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')-i-1][x1-'a'-i-1] == NULL);
                            else
                                for(unsigned int i=x2+1; i<x1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')][i-'a'] == NULL);
                        }
                        else if(x2-x1>0)
                        {
                            if (y1-y2>0)
                                for(unsigned int i=0; i<y1-y2-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')+i+1][x1-'a'+i+1] == NULL);
                            else if (y1-y2<0)
                                for(unsigned int i=0; i<y2-y1-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')-i-1][x1-'a'+i+1] == NULL);
                            else
                                for(unsigned int i=x1+1; i<x2; i++)
                                    isLegal &=(chessboard[7-(y1-'1')][i-'a'] == NULL);
                        }
                        else if(y1-y2>0)
                            for(unsigned int i=y2+1; i<y1; i++)
                                isLegal &=(chessboard[7-(i-'1')][x1-'a'] == NULL);
                        else
                            for(unsigned int i=y1+1; i<y2; i++)
                                isLegal &=(chessboard[7-(i-'1')][x1-'a'] == NULL);
                        break;
            case rook:  isLegal = (x1==x2 || y1==y2);
                        if(x1-x2>0) //checking spaces between origin and target for pieces
                            for(unsigned int i=x2+1; i<x1; i++)
                                isLegal &=(chessboard[7-(y1-'1')][i-'a'] == NULL);
                        else if(x2-x1>0)
                            for(unsigned int i=x1+1; i<x2; i++)
                                isLegal &=(chessboard[7-(y1-'1')][i-'a'] == NULL);
                        else if(y1-y2>0)
                            for(unsigned int i=y2+1; i<y1; i++)
                                isLegal &=(chessboard[7-(i-'1')][x1-'a'] == NULL);
                        else
                            for(unsigned int i=y1+1; i<y2; i++)
                                isLegal &=(chessboard[7-(i-'1')][x1-'a'] == NULL);
                        break;
            case bishop:isLegal = (abs(x1-x2)==abs(y1-y2));
                        if (x1-x2>0) //checking spaces between origin and target for pieces
                        {
                            if (y1-y2>0)
                                for(unsigned int i=0; i<y1-y2-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')+i+1][x1-'a'-i-1] == NULL);
                            else
                                for(unsigned int i=0; i<y2-y1-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')-i-1][x1-'a'-i-1] == NULL);
                        }
                        else
                        {
                            if (y1-y2>0)
                                for(unsigned int i=0; i<y1-y2-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')+i+1][x1-'a'+i+1] == NULL);
                            else
                                for(unsigned int i=0; i<y2-y1-1; i++)
                                    isLegal &=(chessboard[7-(y1-'1')-i-1][x1-'a'+i+1] == NULL);
                        }
                        break;
            case knight:isLegal = (abs(x1-x2)==2 && abs(y1-y2)==1)||(abs(x1-x2)==1 && abs(y1-y2)==2); //if target is 2 and 1 tiles away
                        break;
            case pawn:  if( chessboard[7-(y1-'1')][x1-'a']->getBlackness() )
                        {
                            isLegal = (y1-y2==1 && x1==x2) || (y1-y2==1 && abs(x1-x2)==1 && chessboard[7-(y2-'1')][x2-'a']!=NULL); //(moving) || (hitting)
                            if(y1-'1'==6)
                            {
                                isLegal|= ( (y1-y2)==2 && x1==x2 && chessboard[7-(y1-'1'-1)][x1-'a'] == NULL ); //double move
                            }
                        }
                        else
                        {
                            isLegal = (y2-y1==1 && x1==x2)|| (y2-y1==1 && abs(x1-x2)==1 && chessboard[7-(y2-'1')][x2-'a']!=NULL); //(moving) || (hitting)
                            if(y1-'1'==1)
                            {
                               isLegal|= ( (y2-y1)==2 && x1==x2  && chessboard[7-(y1-'1'+1)][x1-'a'] == NULL ); //double move
                            }
                        }
                        break;
        }
        if(blacksMove!=chessboard[7-(y1-'1')][x1-'a']->getBlackness()) //choosing piece of wrong colour
        {
            isLegal=0;
            std::cout<<"Piece of wrong colour. ";
        }
        if(chessboard[7-(y2-'1')][x2-'a']!=NULL)
        {
            isLegal&=chessboard[7-(y2-'1')][x2-'a']->getBlackness()!=chessboard[7-(y1-'1')][x1-'a']->getBlackness(); //can't hit piece of same color
            
        }
        if(isLegal)
        {
            chessboard[7-(y2-'1')][x2-'a'] = chessboard[7-(y1-'1')][x1-'a'];
            chessboard[7-(y1-'1')][x1-'a'] = NULL;
            return 1;
        }
        else
        {
            std::cout<<"Illegal move. Try again."<<std::endl;
            return 0;
        }
    }
    else
    {
        std::cout<<"There's no piece to move. Try again."<<std::endl;
        return 0;
    }
}

int main()
{
    unsigned char x1,y1,x2,y2;
    Piece* chessboard[8][8];
    Piece pieces[32];
    bool blacksMove=false;

    initChessboard(chessboard, pieces);
    while (true)
    {
        renderChessboard(chessboard, pieces);
        do
        {
            printf("Your move: ");
            scanf(" %c%c %c%c", &x1, &y1, &x2, &y2);
            getchar();
        }
        while( x1<'a' || x1>'h' || y1<'1' || y1>'8' || x2<'a' || x2>'h' || y2<'1' || y2>'8');
        if(move(chessboard, pieces, x1, y1, x2, y2, blacksMove))
            blacksMove=!blacksMove;
    }
    return 0;
}