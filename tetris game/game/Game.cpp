#include "Game.h"
#include <cstdlib>

int Game::GetRand (int pA, int pB){
return pA + rand() % pB;
}

void Game::InitGame()
{

srand ((unsigned int) time(NULL));

// First piece
mPiece = GetRand (0, 6);
mRotation = GetRand (0, 3);
mPosX = (BOARD_WIDTH / 2) + mPieces->getXInitialPosition (mPiece, mRotation);
mPosY = mPieces->getYInitialPosition (mPiece, mRotation);

// Next piece
mNextPiece = GetRand (0, 6);
mNextRotation = GetRand (0, 3);
mNextPosX = BOARD_WIDTH + 5;
mNextPosY = 5;
}

void Game::CreateNewPiece (){
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH / 2) + mPieces->getXInitialPosition (mPiece, mRotation);
    mPosY = mPieces->getYInitialPosition (mPiece, mRotation);
    mNextPiece = GetRand (0, 6);
    mNextRotation = GetRand (0, 3);
}

void Game::DrawPiece (int pX, int pY, int pPiece, int pRotation){
color mColor; 

// Obtain the position in pixel in the screen of the block we want to draw
int mPixelsX = mBoard->GetXPosInPixels (pX);
int mPixelsY = mBoard->GetYPosInPixels (pY);

// Travel the matrix of blocks of the piece and draw the blocks that are filled
for (int i = 0; i < PIECE_BLOCKS; i++)
{
for (int j = 0; j < PIECE_BLOCKS; j++)
{
// Get the type of the block and draw it with the correct color
switch (mPieces->getBlockType (pPiece, pRotation, j, i))
{
case 1: mColor = GREEN; break; // For each block of the piece except the pivot
case 2: mColor = BLUE; break; // For the pivot
}

if (mPieces->getBlockType (pPiece, pRotation, j, i) != 0)
mIO->DrawRectangle (mPixelsX + i * BLOCK_SIZE,
mPixelsY + j * BLOCK_SIZE,
(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
mColor);
}
}

}