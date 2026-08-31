#pragma once

#include <cstdint>
#include <inttypes.h>
#include <array>

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

constexpr TetrominoData I_PIECE = {{
    {{{ -1,  0 }, {  0,  0 }, {  1,  0 }, {  2,  0 }}}, // Rot 0 (Spawn horizontal)
    {{{  1, -1 }, {  1,  0 }, {  1,  1 }, {  1,  2 }}}, // Rot 1 (Vertical right)
    {{{ -1,  1 }, {  0,  1 }, {  1,  1 }, {  2,  1 }}}, // Rot 2 (Horizontal down)
    {{{  0, -1 }, {  0,  0 }, {  0,  1 }, {  0,  2 }}}  // Rot 3 (Vertical left)
}};

// J-Piece: Central pivot at (0, 0)
constexpr TetrominoData J_PIECE = {{
    {{{ -1, -1 }, { -1,  0 }, {  0,  0 }, {  1,  0 }}}, // Rot 0
    {{{  0, -1 }, {  1, -1 }, {  0,  0 }, {  0,  1 }}}, // Rot 1
    {{{ -1,  0 }, {  0,  0 }, {  1,  0 }, {  1,  1 }}}, // Rot 2
    {{{  0, -1 }, {  0,  0 }, { -1,  1 }, {  0,  1 }}}  // Rot 3
}};

// L-Piece: Central pivot at (0, 0)
constexpr TetrominoData L_PIECE = {{
    {{{  1, -1 }, { -1,  0 }, {  0,  0 }, {  1,  0 }}}, // Rot 0
    {{{  0, -1 }, {  0,  0 }, {  0,  1 }, {  1,  1 }}}, // Rot 1
    {{{ -1,  0 }, {  0,  0 }, {  1,  0 }, { -1,  1 }}}, // Rot 2
    {{{ -1, -1 }, {  0, -1 }, {  0,  0 }, {  0,  1 }}}  // Rot 3
}};

// O-Piece: Fixed shape, all rotation states are identical
constexpr TetrominoData O_PIECE = {{
    {{{  0, -1 }, {  1, -1 }, {  0,  0 }, {  1,  0 }}}, // Rot 0
    {{{  0, -1 }, {  1, -1 }, {  0,  0 }, {  1,  0 }}}, // Rot 1
    {{{  0, -1 }, {  1, -1 }, {  0,  0 }, {  1,  0 }}}, // Rot 2
    {{{  0, -1 }, {  1, -1 }, {  0,  0 }, {  1,  0 }}}  // Rot 3
}};

// S-Piece: Central pivot at (0, 0)
constexpr TetrominoData S_PIECE = {{
    {{{  0, -1 }, {  1, -1 }, { -1,  0 }, {  0,  0 }}}, // Rot 0
    {{{  0, -1 }, {  0,  0 }, {  1,  0 }, {  1,  1 }}}, // Rot 1
    {{{  0,  0 }, {  1,  0 }, { -1,  1 }, {  0,  1 }}}, // Rot 2
    {{{ -1, -1 }, { -1,  0 }, {  0,  0 }, {  0,  1 }}}  // Rot 3
}};

// T-Piece: Central pivot at (0, 0)
constexpr TetrominoData T_PIECE = {{
    {{{  0, -1 }, { -1,  0 }, {  0,  0 }, {  1,  0 }}}, // Rot 0
    {{{  0, -1 }, {  0,  0 }, {  1,  0 }, {  0,  1 }}}, // Rot 1
    {{{ -1,  0 }, {  0,  0 }, {  1,  0 }, {  0,  1 }}}, // Rot 2
    {{{  0, -1 }, { -1,  0 }, {  0,  0 }, {  0,  1 }}}  // Rot 3
}};

// Z-Piece: Central pivot at (0, 0)
constexpr TetrominoData Z_PIECE = {{
    {{{ -1, -1 }, {  0, -1 }, {  0,  0 }, {  1,  0 }}}, // Rot 0
    {{{  1, -1 }, {  0,  0 }, {  1,  0 }, {  0,  1 }}}, // Rot 1
    {{{ -1,  0 }, {  0,  0 }, {  0,  1 }, {  1,  1 }}}, // Rot 2
    {{{  0, -1 }, { -1,  0 }, {  0,  0 }, { -1,  1 }}}  // Rot 3
}};

// Master Lookup Array indexed by PieceType enum:
// TetrominoDataLUT[static_cast<std::size_t>(PieceType::T)]
constexpr std::array<TetrominoData, 8> TETROMINO_LUT = {
    TetrominoData{}, // Index 0: None
    I_PIECE,         // Index 1: PieceType::I
    J_PIECE,         // Index 2: PieceType::J
    L_PIECE,         // Index 3: PieceType::L
    O_PIECE,         // Index 4: PieceType::O
    S_PIECE,         // Index 5: PieceType::S
    T_PIECE,         // Index 6: PieceType::T
    Z_PIECE          // Index 7: PieceType::Z
};

struct CurrentPiece {
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