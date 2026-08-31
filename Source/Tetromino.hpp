#pragma once

#include "raylib.h"

#include <cstdint>
#include <inttypes.h>
#include <array>
#include <vector>

enum class PieceType: uint8_t{
    None = 0, I, J, L, O, S, T, Z
};

struct Point {
    int8_t x, y;
};

using PieceOffsets = std::array<Point, 4>;

struct TetrominoData {
    std::array<PieceOffsets, 4> rotations;
};

constexpr TetrominoData I_PIECE = {
    PieceOffsets{ Point{-1,  0}, Point{ 0,  0}, Point{ 1,  0}, Point{ 2,  0} },
    PieceOffsets{ Point{ 1, -1}, Point{ 1,  0}, Point{ 1,  1}, Point{ 1,  2} },
    PieceOffsets{ Point{-1,  1}, Point{ 0,  1}, Point{ 1,  1}, Point{ 2,  1} },
    PieceOffsets{ Point{ 0, -1}, Point{ 0,  0}, Point{ 0,  1}, Point{ 0,  2} }
};

constexpr TetrominoData J_PIECE = {
    PieceOffsets{ Point{-1, -1}, Point{-1,  0}, Point{ 0,  0}, Point{ 1,  0} },
    PieceOffsets{ Point{ 0, -1}, Point{ 1, -1}, Point{ 0,  0}, Point{ 0,  1} },
    PieceOffsets{ Point{-1,  0}, Point{ 0,  0}, Point{ 1,  0}, Point{ 1,  1} },
    PieceOffsets{ Point{ 0, -1}, Point{ 0,  0}, Point{-1,  1}, Point{ 0,  1} }
};

constexpr TetrominoData L_PIECE = {
    PieceOffsets{ Point{ 1, -1}, Point{-1,  0}, Point{ 0,  0}, Point{ 1,  0} },
    PieceOffsets{ Point{ 0, -1}, Point{ 0,  0}, Point{ 0,  1}, Point{ 1,  1} },
    PieceOffsets{ Point{-1,  0}, Point{ 0,  0}, Point{ 1,  0}, Point{-1,  1} },
    PieceOffsets{ Point{-1, -1}, Point{ 0, -1}, Point{ 0,  0}, Point{ 0,  1} }
};

constexpr TetrominoData O_PIECE = {
    PieceOffsets{ Point{ 0, -1}, Point{ 1, -1}, Point{ 0,  0}, Point{ 1,  0} },
    PieceOffsets{ Point{ 0, -1}, Point{ 1, -1}, Point{ 0,  0}, Point{ 1,  0} },
    PieceOffsets{ Point{ 0, -1}, Point{ 1, -1}, Point{ 0,  0}, Point{ 1,  0} },
    PieceOffsets{ Point{ 0, -1}, Point{ 1, -1}, Point{ 0,  0}, Point{ 1,  0} }
};

constexpr TetrominoData S_PIECE = {
    PieceOffsets{ Point{ 0, -1}, Point{ 1, -1}, Point{-1,  0}, Point{ 0,  0} },
    PieceOffsets{ Point{ 0, -1}, Point{ 0,  0}, Point{ 1,  0}, Point{ 1,  1} },
    PieceOffsets{ Point{ 0,  0}, Point{ 1,  0}, Point{-1,  1}, Point{ 0,  1} },
    PieceOffsets{ Point{-1, -1}, Point{-1,  0}, Point{ 0,  0}, Point{ 0,  1} }
};

constexpr TetrominoData T_PIECE = {
    PieceOffsets{ Point{ 0, -1}, Point{-1,  0}, Point{ 0,  0}, Point{ 1,  0} },
    PieceOffsets{ Point{ 0, -1}, Point{ 0,  0}, Point{ 1,  0}, Point{ 0,  1} },
    PieceOffsets{ Point{-1,  0}, Point{ 0,  0}, Point{ 1,  0}, Point{ 0,  1} },
    PieceOffsets{ Point{ 0, -1}, Point{-1,  0}, Point{ 0,  0}, Point{ 0,  1} }
};

constexpr TetrominoData Z_PIECE = {
    PieceOffsets{ Point{-1, -1}, Point{ 0, -1}, Point{ 0,  0}, Point{ 1,  0} },
    PieceOffsets{ Point{ 1, -1}, Point{ 0,  0}, Point{ 1,  0}, Point{ 0,  1} },
    PieceOffsets{ Point{-1,  0}, Point{ 0,  0}, Point{ 0,  1}, Point{ 1,  1} },
    PieceOffsets{ Point{ 0, -1}, Point{-1,  0}, Point{ 0,  0}, Point{-1,  1} }
};


//Master Lookup Array indexed by PieceType enum:
//TetrominoDataLUT[static_cast<std::size_t>(PieceType::T)]
const std::array<TetrominoData, 8> TETROMINO_LUT = {
    TetrominoData{}, // Index 0: None
    I_PIECE,         // Index 1: PieceType::I
    J_PIECE,         // Index 2: PieceType::J
    L_PIECE,         // Index 3: PieceType::L
    O_PIECE,         // Index 4: PieceType::O
    S_PIECE,         // Index 5: PieceType::S
    T_PIECE,         // Index 6: PieceType::T
    Z_PIECE          // Index 7: PieceType::Z
};

struct Piece {
    PieceType type {};
    TetrominoData Data {};
    int8_t x;
    int8_t y;
    uint8_t rotation;

    [[nodiscard]] PieceOffsets getCurrentOffets() const noexcept {
        return Data.rotations[rotation];
    }

    void rotateClockwise() noexcept {
        rotation = (rotation + 1) % 4; 
    }

    void rotateCounterClockwise() noexcept {
        rotation = (rotation + 3) % 4;
    }
    
};

class Bag {
public:
    Bag() {
        pieces.clear();
        pieces.reserve(7);

        for (int i = 0; i < 7; i++) {
            PieceType type = PieceType::I;
            auto isInBag = [&type](std::vector<Piece> &bag) {
                for (auto& piece : bag) {
                    if (piece.type == type) {
                        return  true;
                    }
                }
                return false;
            };
            do {
                type = static_cast<PieceType>(GetRandomValue(1, 7));
            } while (isInBag(pieces));
            pieces.push_back(  {
                .type = type,
                .Data = TETROMINO_LUT[static_cast<int>(type)],
                .x = 3,
                .y = 3,
                .rotation = 0,
            });
        }

    }

    [[nodiscard]] std::vector<Piece> &getPieces() noexcept {
        return  pieces;
    }
    Piece& operator[](const int index) {
        return  pieces[index];
    }
private:
    std::vector<Piece> pieces;
};