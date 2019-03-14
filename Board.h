#ifndef _BOARD_
#define _BOARD_

#include "Pieces.h"

#define BOARD_LINE_WIDTH 6			// Latimea fiecareia dintre cele doua linii care delimiteaza marginile
#define BLOCK_SIZE 16				// Latimea și inaltimea fiecarui bloc dintr-o piesa
#define BOARD_POSITION 320			// Pozitia centrala a pmarginii din stanga ecranului
#define BOARD_WIDTH 10				// Latimea platformei blocuri
#define BOARD_HEIGHT 20				// Inaltimea platformei blocuri
#define MIN_VERTICAL_MARGIN 20		// Minimul vertical
#define MIN_HORIZONTAL_MARGIN 20	// Minimul orizontal
#define PIECE_BLOCKS 5				// Numărul de blocuri orizontale și verticale ale unei matrice
#include <iostream>
using namespace std;
class Board
{
public:

	Board						(Pieces *pPieces, int pScreenHeight);

	int GetXPosInPixels			(int pPos);
	int GetYPosInPixels			(int pPos);
	bool IsFreeBlock			(int pX, int pY);
	bool IsPossibleMovement		(int pX, int pY, int pPiece, int pRotation);
	void StorePiece				(int pX, int pY, int pPiece, int pRotation);
	void DeletePossibleLines	();
	bool IsGameOver			();
	struct node{
        struct node* next=NULL;
        int h=0;
	};
	typedef struct node nod;
	struct hLista{
        struct hLista *next=NULL;
        int h=0;
	};
	typedef struct hLista inaltimi;
	struct colLista{
        struct colLista *next=NULL;
        int i=0;
        inaltimi *heights;
        inaltimi *head=NULL;
	};
	typedef colLista coloane;

	coloane *listaCol, *listaTop;

private:

	enum { POS_FREE, POS_FILLED };			// POS_FREE = spatiu liber in platforma; POS_FILLED = spatiu ocupat in platforma
	int mBoard [BOARD_WIDTH][BOARD_HEIGHT];	// spatiul ocupat de piese
	Pieces *mPieces;
	int mScreenHeight;

	void InitBoard();
	void DeleteLine (int pY);
};

#endif // _BOARD_
