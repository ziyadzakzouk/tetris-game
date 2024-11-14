#include "Game.h"
#include "Board.h"
#include "Pieces.h"
#include <iostream>
#ifndef LINUX
#include <windows.h>
#endif

/*
==================
Main
==================
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
// —– Vars —–
// Initialize SDL

// Class for drawing staff, it uses SDL for the rendering. Change the methods of this class
// in order to use a different renderer
IO mIO;
int mScreenHeight = mIO.GetScreenHeight();

// Pieces
Pieces mPieces;

// Board
Board mBoard (&mPieces, mScreenHeight);

// Game
Game mGame (&mBoard, &mPieces, &mIO, mScreenHeight);

// Get the actual clock milliseconds (SDL)
unsigned long mTime1 = SDL_GetTicks();

while (!mIO.IsKeyDown (SDLK_ESCAPE))
{
// —– Draw —–

mIO.ClearScreen (); // Clear screen
mGame.DrawScene (); // Draw staff
mIO.UpdateScreen (); // Put the graphic context in the screen

int mKey = mIO.Pollkey();

switch(mKey)
{
case (SDLK_RIGHT):
{
if (mBoard.IsPossibleMovement (mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
mGame.mPosX++;
break;
}

case (SDLK_LEFT):
{
if (mBoard.IsPossibleMovement (mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
mGame.mPosX--;
break;
}

case (SDLK_DOWN):
{
if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
mGame.mPosY++;
break;
}
case (SDLK_z):
{
if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
mGame.mRotation = (mGame.mRotation + 1) % 4;

break;
}
case (SDLK_x):
{
// Check collision from up to down
while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

mBoard.DeletePossibleLines ();

if (mBoard.IsGameOver())
{
mIO.Getkey();
exit(0);
}

mGame.CreateNewPiece();

break;
}
}
unsigned long mTime2 = SDL_GetTicks();

if ((mTime2 - mTime1) > WAIT_TIME)
{
if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
{
mGame.mPosY++;
}
else
{
mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

mBoard.DeletePossibleLines ();

if (mBoard.IsGameOver())
{
mIO.Getkey();
exit(0);
SDL_Quit();
}

mGame.CreateNewPiece();
}

mTime1 = SDL_GetTicks();
}
}

return 0;
}