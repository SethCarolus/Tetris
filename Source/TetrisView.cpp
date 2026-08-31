#include "TetrisView.hpp"

#include "Tetromino.hpp"
#include "raylib.h"
#include <cstdint>

TetrisView::TetrisView()
    : width(500), height(800), title("Tetris")
{
    if (!IsWindowReady()) {
        InitWindow(width, height, title.c_str()),
        SetTargetFPS(60);
    } 
}

TetrisView::~TetrisView() {
   CloseWindow();
}

void TetrisView::render(const Playfield& playfield, const Piece& activePiece, const Piece& nextPiece, const uint32_t score) {
    int bw = height / playfield.TOTAL_HEIGHT;
    int bh = height / playfield.TOTAL_HEIGHT;    
    const int p = (width - bw * playfield.WIDTH) / 2; 

    BeginDrawing();
    ClearBackground(ColorFromHSV(167, 0.67f, 0.67f));

    // Display Wall
    for (int y = playfield.HIDDEN_ROWS; y < playfield.TOTAL_HEIGHT; y++) {
        for(int x = 0; x < playfield.WIDTH; x++) {
            auto cell = playfield.getCell(x, y);
            uint8_t type = static_cast<uint8_t>(cell);
            DrawRectangle(p + x * bw,  y * bh, bw - 2, bh - 2, ColorLUT[type]);
        }
    }

    // Display Actice Pice
    const auto& offets = activePiece.getCurrentOffets();

    for(const auto& point : offets) {
        int x = activePiece.x + point.x;
        int y = activePiece.y + point.y;

        uint8_t type = static_cast<uint8_t>(activePiece.type);
        DrawRectangle(p + x * bw,  y * bh, bw - 2, bh - 2, ColorLUT[type]);
    }

    for(int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            DrawRectangle(1 + x * bw * 0.5, 1 + y * bh * 0.5, bw * 0.5l - 2, bh * 0.5 - 2, ColorLUT[0]);
        }
    }
    
    for (const auto& point : nextPiece.getCurrentOffets()) {
        int x = 1 + point.x;
        int y =  1 + point.y;
        uint8_t type = static_cast<uint8_t>(nextPiece.type);
        
        DrawRectangle(1 + x * bw * 0.5, 1 + y * bh * 0.5, bw * 0.5l - 2, bh * 0.5 - 2, ColorLUT[type]);
    }
    
    DrawText("Next", 1, 80, 20, BLACK);
    
    // Display Score
    DrawText((("Score: " + std::to_string(score))).c_str(), width - p * 2,
             0, 20, BLACK);

    EndDrawing();
}

void TetrisView::handleInput() {
    if (WindowShouldClose()) {
        onQuit();
    }

    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
        onMoveLeft();
    }

    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
        onMoveRight();
    }

    if (IsKeyPressed(KEY_R)) {
        onRotate();
    }
}

void TetrisView::setOnQuit(Callback callback) {
    onQuit = std::move(callback);
}

void TetrisView::setOnMoveLeft(Callback callback) {
    onMoveLeft = std::move(callback);
}

void TetrisView::setOnMoveRight(Callback callback) {
    onMoveRight = std::move(callback);
}

void TetrisView::setOnRotate(Callback callback) {
    onRotate = std::move(callback);
}