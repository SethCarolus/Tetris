#pragma once

#include "Playfield.hpp"
#include "Tetromino.hpp"
#include "raylib.h"

#include <functional>
#include <string>

class TetrisView {
public:
    using Callback = std::function<void()>;
    void setOnQuit(Callback callback);
    void setOnMoveLeft(Callback callback);
    void setOnMoveRight(Callback callback);
    void setOnRotate(Callback callback);

    float getDeltaTime() { return GetFrameTime(); }
    TetrisView();
    ~TetrisView();
    void render(const Playfield& playfield, const ActivePiece& activePiece);
    void handleInput();
private:
    Callback onQuit;
    Callback onMoveLeft;
    Callback onMoveRight;
    Callback onRotate;

    int width;
    int height;
    std::string title;
};