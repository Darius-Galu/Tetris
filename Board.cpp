#include "Board.h"
#include <iostream>
#include <cstdlib>
using namespace std;
struct node{
    node *next=NULL;
    int height=0;
    int i=0;
};
typedef struct node Node;
struct lista{
    Node* head=NULL;
};
typedef struct lista List;
Board::coloane *head=NULL;
void addNode(Board::coloane* x){
    Board::coloane *temp;
    temp=(Board::coloane*)malloc(sizeof(Board::coloane));
    if (head==NULL){//primul nod; verifica daca lista e nula
        temp->next=NULL;
        temp->i=1;
        head=temp;
    }
    else{
        Board::coloane* traverse=head;//parcurge lista pana la capat
        traverse->i=1;
        while(traverse->next!=NULL){
            traverse=traverse->next;
            traverse->i++;
        }

        temp->i=traverse->i++;
        traverse->next=temp;
        temp->next=NULL;
    }
}

void addNode2(Board::coloane* x){
    Board::inaltimi *temp;
    temp=(Board::inaltimi*)malloc(sizeof(Board::inaltimi));
    if (x->head==NULL){//primul nod; verifica daca lista e nula
        temp->next=NULL;
        temp->h=1;
        x->head=temp;
    }
    else{
        Board::inaltimi* traverse=x->head;//parcurge lista pana la capat
        traverse->h=1;
        while(traverse->next!=NULL){
            traverse=traverse->next;
            traverse->h++;
        }

        temp->h=traverse->h++;
        traverse->next=temp;
        temp->next=NULL;
    }
}
Board::Board (Pieces *pPieces, int pScreenHeight)
{
	// Inaltimea ecranului
	mScreenHeight = pScreenHeight;
	listaCol=(coloane*)malloc(sizeof(coloane));
	listaTop=(coloane*)malloc(sizeof(coloane));
	mPieces = pPieces;
    //platforma goala
	InitBoard();
}

void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			mBoard[i][j] = POS_FREE;
}


//Inlocuirea spatiului liber cu piese

void Board::StorePiece (int pX, int pY, int pPiece, int pRotation)
{
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{
			if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
				mBoard[i1][j1] = POS_FILLED;
		}
	}
}

bool Board::IsGameOver()
{
    for(int k=0;k<BOARD_WIDTH;k++){
        addNode(this->listaCol);
    }
    inaltimi *listaH=(inaltimi*)malloc(sizeof(inaltimi));
    for(int j=0;j<BOARD_HEIGHT;j++){
        addNode2(this->listaCol);
    }

	//daca ultima linie de sus are bloc, jocul se termina
    int i=0,h=0;
    this->listaTop=head;
	while(i<BOARD_WIDTH)
	{
	    this->listaTop->i=i;
	    this->listaTop->heights->h=0;
		if (this->listaTop->heights->h == POS_FILLED) return true;
		this->listaTop=this->listaTop->next;
		i++;
		h++;
	}
    std::cout<<"Game Over";
	return false;
}

void Board::DeleteLine (int pY)
{
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j-1];
		}
	}
}

void Board::DeletePossibleLines ()
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}

		if (i == BOARD_WIDTH) DeleteLine (j);
	}
}


bool Board::IsFreeBlock (int pX, int pY)
{
	if (mBoard [pX][pY] == POS_FREE) return true; else return false;
}


//pPos:	Pozitia orizontala a blocului in platforma
int Board::GetXPosInPixels (int pPos)
{
	return  ( ( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (pPos * BLOCK_SIZE) );
}


int Board::GetYPosInPixels (int pPos)
{
	return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE) );
}

//Verificam daca putem pozitiona piesa fara sa se loveasca de alte piese pozitionate deja
bool Board::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{
			// Verificam ca piesa sa nu fie afara din platforma
			if (i1 < 0 	||  i1 > BOARD_WIDTH  - 1	||    j1 > BOARD_HEIGHT - 1)
			{
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
					return 0;
			}

			// Verificam daca piesa s-a lovit de o piesa deja plasata
			if (j1 >= 0)
			{
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock (i1, j1))	)
					return false;
			}
		}
	}
	return true;
}
