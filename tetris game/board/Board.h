#include "Pieces.h"
#ifndef _BOARD_

#define BOARD_LINE_WIDTH 6 
#define BLOCK_SIZE 16 
#define BOARD_POSITION 320 
#define BOARD_WIDTH 10 
#define BOARD_HEIGHT 20 
#define MIN_VERTICAL_MARGIN 20 
#define MIN_HORIZONTAL_MARGIN 20 
#define PIECE_BLOCKS 5 

class Board
{
public:

Board (Pieces *pieces, int ScreenHeight);

int GetXPosInPixels (int pPos);
int GetYPosInPixels (int pPos);
bool IsFreeBlock (int pX, int pY);
bool IsPossibleMovement (int pX, int pY, int pPiece, int pRotation);
void StorePiece (int pX, int pY, int pPiece, int pRotation);
void DeletePossibleLines ();
bool IsGameOver ();

private:

enum {POS_FREE, POS_FILLED};
int board[BOARD_WIDTH][BOARD_HEIGHT]; 
Pieces *pieces;
int screenHeight;

void InitBoard();
void DeleteLine (int pY);
};

#endif