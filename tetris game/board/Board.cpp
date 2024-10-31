#include "Board.h"

void Board::InitBoard()
{
     for (int i = 0; i < BOARD_HEIGHT; i++)
     {
          for (int j = 0; j < BOARD_WIDTH; j++)
               board[j][i] = POS_FREE;
     }
}
void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
     // Store each block of the piece into the board
     for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
     {
          for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
          {
               // Store only the blocks of the piece that are not holes
               if (pieces->getBlockType(pPiece, pRotation, j2, i2) != 0)
                    board[i1][j1] = POS_FILLED;
          }
     }
}

bool Board::IsGameOver()
{
     bool flag = false;
     for (int i = 0; i < BOARD_WIDTH; i++)
     {
          if (board[i][0] == POS_FILLED)
               flag = true;
     }
     return flag;
}

void Board::DeleteLine(int pY){
     // Moves all the upper lines one row down
 for (int j = pY; j > 0; j--){
     for (int i = 0; i < BOARD_WIDTH; i++){
          board[i][j] = board[i][j - 1];
      }
  }
}

void Board::DeletePossibleLines (){
  for (int j = 0; j < BOARD_HEIGHT; j++)
     {
          int i = 0;
          while(i < BOARD_WIDTH){
            if (board[i][j] != POS_FILLED) 
             break;
             i++;
          }
             if(i==BOARD_WIDTH)
             DeleteLine(j);  
     }

}