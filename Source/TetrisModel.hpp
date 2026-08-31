#pragma once

#include "Playfield.hpp"
#include "Tetromino.hpp"

class TetrisModel {
public: 
    TetrisModel();
    bool getRunning() { return running;}
    void update(float dt);
    void handleQuit();
    void handleMoveLeft();
    void handleMoveRight();
    void handleRotate();
    Playfield& getPlayfield();
    Piece& getActivePiece();
private:
    bool running {true};

    float lastTime {0};
    constexpr static auto interval = 0.25f;


    Playfield playfield;
    Piece activePiece;
    Bag bag;
    Bag nextBag;
    size_t activePieceIndex;
};