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

void Game::DrawBoard ()
{

// Calculate the limits of the board in pixels
int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

// Check that the vertical margin is not to small
//assert (mY > MIN_VERTICAL_MARGIN);

// Rectangles that delimits the board
mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);

mIO->DrawRectangle (mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

// Check that the horizontal margin is not to small
//assert (mX1 > MIN_HORIZONTAL_MARGIN);

// Drawing the blocks that are already stored in the board
mX1 += 1;
for (int i = 0; i < BOARD_WIDTH; i++)
{
for (int j = 0; j < BOARD_HEIGHT; j++)
{
// Check if the block is filled, if so, draw it
if (!mBoard->IsFreeBlock(i, j))
mIO->DrawRectangle ( mX1 + i * BLOCK_SIZE,
mY + j * BLOCK_SIZE,
(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
RED);
}
}
}

void Game::DrawScene ()
{
DrawBoard (); // Draw the delimitation lines and blocks stored in the board
DrawPiece (mPosX, mPosY, mPiece, mRotation); // Draw the playing piece
DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation); // Draw the next piece
}