#include "Piece.h"

Piece::Piece(PieceType type, PieceOrientation orientation = PieceOrientation::POINT_UP_FLAT_DOWN)
    : bricked(false), type(type), orientation(orientation) {
    switch (type) {
        case PieceType::I : {
            color = SKYBLUE;
            blocks[0] = Block(0, 0, BlockType::PIECE, color);
            blocks[1] = Block(0, 1, BlockType::PIECE, color);
            blocks[2] = Block(0, 2, BlockType::PIECE, color);
            blocks[3] = Block(0, 3, BlockType::PIECE, color);
            break;
        }
        case PieceType::O : {
            color = GOLD;
            blocks[1] = Block(1, 0, BlockType::PIECE, color);
            blocks[0] = Block(0, 0, BlockType::PIECE, color);
            blocks[2] = Block(0, 1, BlockType::PIECE, color);
            blocks[3] = Block(1, 1, BlockType::PIECE, color);
            break;
        }

       case PieceType::T : {
            color = MAGENTA;
            blocks[0] = Block(0, 1, BlockType::PIECE, color);
            blocks[1] = Block(1, 0, BlockType::PIECE, color);
            blocks[2] = Block(1, 1, BlockType::PIECE, color);
            blocks[3] = Block(1, 2, BlockType::PIECE, color);
            break;
        }

        case PieceType::S : {
            color = GREEN;
            blocks[0] = Block(0, 1, BlockType::PIECE, color);
            blocks[1] = Block(0, 2, BlockType::PIECE, color);
            blocks[2] = Block(1, 0, BlockType::PIECE, color);
            blocks[3] = Block(1, 1, BlockType::PIECE, color);
            break;
        }

        case PieceType::Z : {
            color = RED;
            blocks[0] = Block(0, 0, BlockType::PIECE, color);
            blocks[1] = Block(0, 1, BlockType::PIECE, color);
            blocks[2] = Block(1, 1, BlockType::PIECE, color);
            blocks[3] = Block(1, 2, BlockType::PIECE, color);
            break;
        }

        case PieceType::J : {
            color = DARKBLUE;
            blocks[0] = Block(0, 0, BlockType::PIECE, color);
            blocks[1] = Block(1, 0, BlockType::PIECE, color);
            blocks[2] = Block(1, 1, BlockType::PIECE, color);
            blocks[3] = Block(2, 1, BlockType::PIECE, color);
            break;
        }

        case PieceType::L : {
            color = ORANGE;
            blocks[0] = Block(0, 2, BlockType::PIECE, color);
            blocks[1] = Block(1, 0, BlockType::PIECE, color);
            blocks[2] = Block(1, 1, BlockType::PIECE, color);
            blocks[3] = Block(1, 2, BlockType::PIECE, color);
            break;
        }
    }
}

void Piece::move(Direction direction, std::array<std::array<Block, 8>, 20>& wall) {
    if (bricked) return;

    switch (direction) {
        case Direction::DOWN: {
            bool canMove = true;

            for (auto& block : blocks) {
                if (block.row + 1 >= 20 || wall[block.row + 1][block.column].type != BlockType::VOID) {
                    canMove = false;
                    bricked = true;
                    break;
                }
            }

            if (!canMove) {
                break;
            }

            for (int i = 0; i < 4; i++) {
                blocks[i].row++;
            }
            break;
            }

        case Direction::RIGHT: {
            bool canMove = true;

            for (auto& block : blocks) {
                if (block.column + 1 >= 8 || wall[block.row][block.column + 1].type != BlockType::VOID) {
                    canMove = false;
                    break;
                }
            }

            if (!canMove) {
                break;
            }

            for (int i = 0; i < 4; i++) {
                blocks[i].column++;
            }
            break;
        }

        case Direction::LEFT: {
            bool canMove = true;

            for (auto& block : blocks) {
                if (block.column - 1 < 0 || wall[block.row][block.column - 1].type != BlockType::VOID) {
                    canMove = false;
                    break;
                }
            }
            if (!canMove) {
                break;
            }

            for (int i = 0; i < 4; i++) {
                blocks[i].column--;
            }
            break;
        }
    }
}

std::array<std::array<Block, 4>,4> Piece::getBlocksMatrix() {
  std::array<std::array<Block, 4>, 4> matrix;
  for (auto& block : blocks) {
      matrix[block.row][block.column] = block;
  }
  return std::move(matrix);
};

void Piece::fall(std::array<std::array<Block, 8>, 20>& wall) {
  int maxFall = 20; // Max Distance in blocks that a piece can fall
  for (auto& block : blocks) {
    int fall = 0;
    for (int i = block.row +1; i < 20; i++) {
      if (wall[i][block.column].type != BlockType::VOID)
        break;
      fall++;
    }
    if (fall < maxFall) maxFall = fall;
  }
  for (auto& block : blocks){
      block.row += maxFall;
  }
}
