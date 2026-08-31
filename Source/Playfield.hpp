#pragma once

#include "Tetromino.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <inttypes.h>

class Playfield {
public:
    Playfield() {
        for(auto& c : cells) {
            c = PieceType::None;
        }
    }
    static constexpr uint8_t WIDTH = 10;
    static constexpr uint8_t HEIGHT = 20;
    static constexpr uint8_t HIDDEN_ROWS = 2;
    static constexpr uint8_t TOTAL_HEIGHT = HEIGHT + HIDDEN_ROWS;

    [[nodiscard]] constexpr size_t getIndex(int8_t x, int8_t y) const noexcept {
        return static_cast<size_t>(y * WIDTH + x);
    }

    [[nodiscard]] constexpr bool isOutOfBounds(int8_t x, int8_t y) const noexcept {
        return x < 0 || x >= WIDTH || y < 0 || y >= TOTAL_HEIGHT;
    }

    [[nodiscard]] PieceType getCell(int8_t x, int8_t y) const noexcept {
        return cells[getIndex(x, y)];
    }

    [[nodiscard]] bool checkCollisions(const Piece& piece, int8_t offsetX = 0, int8_t offsetY = 0, int8_t rotationDelta = 0) {
        uint8_t targetRotation = (piece.rotation + rotationDelta + 4) % 4;
        const auto& offets = piece.Data.rotations[targetRotation];

        for (const auto& point: offets) {
            int targetX = piece.x + offsetX + point.x;
            int targetY = piece.y + offsetY + point.y;

            if (isOutOfBounds(targetX, targetY)) {
                return true;
            }

            if (cells[getIndex(targetX, targetY)] != PieceType::None) {
                return true;
            }
        }
        return false;
    }

    void lockPiece(Piece piece) {
        const auto& offsets = piece.getCurrentOffets();
        for (const auto& point: offsets) {
            int targetX = piece.x + point.x;
            int targetY = piece.y + point.y;

            if (!isOutOfBounds(targetX, targetY)) {
                cells[getIndex(targetX,targetY)] = piece.type;
            }
        }
    }

    uint8_t clearLines() {
        uint8_t linesCleared = 0;

        for (int y = TOTAL_HEIGHT - 1; y >= 0; y--) {
            bool rowFull = true;
            for (int x = 0; x < WIDTH; x++) {
                if (cells[getIndex(x, y)] == PieceType::None) {
                    rowFull = false;
                    break;
                }
            }

            if (!rowFull) continue;;

            linesCleared++;

            for (int moveY = y; moveY > 0; moveY--) {
                for (int x = 0; x < WIDTH; x++) {
                    cells[getIndex(x, moveY)] = cells[getIndex(x, moveY - 1)];
                }
            }

            for (int x = 0; x < WIDTH; x++) {
                cells[getIndex(x, 0)] = PieceType::None;
            }
            y++;
        }

        return  linesCleared;
    }

private:
    std::array<PieceType,WIDTH * TOTAL_HEIGHT> cells;
};