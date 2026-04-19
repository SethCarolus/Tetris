#pragma once

#include "Piece.h"
#include <vector>

class Bag {
public:
    Bag();
    std::vector<Piece>& getPieces();
    Piece& operator[](const int index);
private:
  std::vector<Piece> pieces;
};
