#ifndef _Pieces_
#include "Blocks.cpp"

class Pieces
{
public:
    int getBlockType(int kind,int rotation,int Px,int Py);
    int getXInitialPosition (int kind, int rotation);
    int getYInitialPosition (int kind, int rotation);

};

#endif