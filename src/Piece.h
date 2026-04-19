#pragma once

#include "raylib.h"
#include <array>

enum class PieceOrientation {
    POINT_UP_FLAT_DOWN,
    POINT_RIGHT_FLAT_LEFT,
    POINT_DOWN_FLAT_UP,
    POINT_LEFT_FLAT_RIGHT
};

enum class PieceType {
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

enum class Direction {
    DOWN,
    LEFT,
    RIGHT
};

enum class BlockType {
    VOID,
    PIECE,
};

struct Block {
    Block(int row, int column, BlockType type = BlockType::VOID, Color color = BLACK)
        :row(row), column(column), type(type), color(color){
    }
    Block()
        :row(-1), column(-1){
    }
    int row;
    int column;
    BlockType type;
    Color color;
};
struct Piece {
public:
    Piece(PieceType type, PieceOrientation orientation);
    Piece() {};
    void move(Direction direction, std::array<std::array<Block, 8>, 20>& wall);
    void fall(std::array<std::array<Block, 8>, 20>& wall);
    PieceType type;
    PieceOrientation orientation;
    Color color;
    bool bricked;
    std::array<Block, 4> blocks;
    private:
    std::array<std::array<Block, 4>,4> getBlocksMatrix();
};
