#include "TetrisView.hpp"

#include "raylib.h"

TetrisView::TetrisView() {
    if (!IsWindowReady()) {
        InitWindow(800, 800, "Tetris"),
        SetTargetFPS(60);
    } 
}

TetrisView::~TetrisView() {
   CloseWindow();
}

void TetrisView::render() {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}

void TetrisView::handleInput() {
    if (WindowShouldClose()) {
        onQuit();
    }
}

void TetrisView::setOnQuit(Callback callback) {
    onQuit = std::move(callback);
}
