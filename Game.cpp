#ifndef LINUX
#include <windows.h>
#endif
#include "Game.h"

Game::Game(Board *pBoard, Pieces *pPieces,IO *pIO,int pScreenHeight)
{
	mScreenHeight = pScreenHeight;

	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;
    InitGame ();
}

int Game::GetRand (int pA, int pB)
{
	return rand () % (pB - pA + 1) + pA;
}

void Game::InitGame()
{
	// Piese random
	srand ((unsigned int) time(NULL));

	// Prima piesa
	mPiece			= GetRand (0, 6);
	mRotation		= GetRand (0, 3);
	mPosX 			= (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	//  Urmatoarea piesa
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
	mNextPosX 		= BOARD_WIDTH + 5;
	mNextPosY 		= 5;
}

void Game::CreateNewPiece()
{
	// Crearea unei noi piese
	mPiece			= mNextPiece;
	mRotation		= mNextRotation;
	mPosX 			= (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	// Urmatoarea piesa random
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
}

void Game::DrawPiece (int pX, int pY, int pPiece, int pRotation)
{
	color mColor;

	// Obtinerea locului pentru schimbarea de culoare
	int mPixelsX = mBoard->GetXPosInPixels (pX);
	int mPixelsY = mBoard->GetYPosInPixels (pY);

	// Deplasarea matricii blocurilor piesei și desenarea blocurilor care sunt umplute
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// Verificarea piesei si initializarea culorii care trebuie
			switch (mPieces->GetBlockType (pPiece, pRotation, j, i))
			{
				case 1: mColor = GREEN; break;	// Pentru fiecare piesa exceptand pivotul
				case 2: mColor = BLUE; break;	// Pentru pivot
			}

			if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0)
				mIO->DrawRectangle	(mPixelsX + i * BLOCK_SIZE,
									mPixelsY + j * BLOCK_SIZE,
									(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
									(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
									mColor);
		}
	}
}

void Game::DrawBoard ()
{
	// Calcularea limitei platformei: pozitie,inaltime, latime
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
	mIO->DrawRectangle (mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);


	// Colorarea pieselor deja stocate pe platforma
	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			// Verifica daca blockul este umplut, daca da atunci il coloreaza
			if (!mBoard->IsFreeBlock(i, j))
				mIO->DrawRectangle (mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE, (mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                    (mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED);
		}
	}
}

void Game::DrawScene ()
{
	DrawBoard ();
	DrawPiece (mPosX, mPosY, mPiece, mRotation);
	DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}

