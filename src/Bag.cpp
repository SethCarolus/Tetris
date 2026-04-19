#include "Bag.h"
Bag::Bag() {
    pieces.clear();
    pieces.reserve(7);
        for (int i = 0; i < 7; i++) {
            PieceType type = PieceType::I;
            auto isInBag = [&type](std::vector<Piece>& bag) {
               for(auto& piece : bag) {
                  if (piece.type == type) {
                      return true;
                  }
               }
               return false;
            };
            do
            {
               type =  static_cast<PieceType>(GetRandomValue(0, 6));
            } while (isInBag(pieces));
            pieces.push_back(Piece(type, PieceOrientation::POINT_DOWN_FLAT_UP));
        }
}

Piece& Bag::operator[](int index) {
    if (index < 0 || index >= pieces.size()) {
    }
    return pieces[index];
}
std::vector<Piece>& Bag::getPieces() {
   return pieces;
}
