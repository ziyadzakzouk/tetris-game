#include "Pieces.h"


int Pieces::getBlockType(int kind,int rotation,int Px,int Py){
 return pieces[kind][rotation][Px][Py];
}

int Pieces::getYInitialPosition(int kind,int rotation){
 return piecesInitialPosition[kind][rotation][1];
}

int Pieces::getXInitialPosition(int kind,int rotation){
 return piecesInitialPosition[kind][rotation][0];
}