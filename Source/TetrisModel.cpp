#include "TetrisModel.hpp"
#include "Tetromino.hpp"
#include <cstdint>

TetrisModel::TetrisModel() {
    activePieceIndex = 0;
    activePiece = bag[activePieceIndex];
}

Playfield& TetrisModel::getPlayfield() {
    return  playfield;
}
Piece& TetrisModel::getActivePiece() {
    return  activePiece;
};

void TetrisModel::update(float dt) {
    lastTime += dt;

    if (lastTime < interval) {
        return;
    }

    if (!playfield.checkCollisions(activePiece, 0, 1)) {
        activePiece.y++;
    }
    else {
        playfield.lockPiece(activePiece);
        auto lines = playfield.clearLines();
        score += lines * 67;
        if (activePieceIndex == 6) {
            bag = nextBag;
            nextBag = Bag();
            activePieceIndex = -1;
        }
        activePiece = bag[++activePieceIndex];
    }

    lastTime = 0;
}

void TetrisModel::handleQuit() {
    running = false;
}


void TetrisModel::handleMoveLeft() {
    if (playfield.checkCollisions(activePiece, -1, 0, 0)) {
        return;
    }
    activePiece.x--;
}

void TetrisModel::handleMoveRight() {
    if (playfield.checkCollisions(activePiece, 1, 0, 0)) {
        return;
    }
    activePiece.x++;
}

void TetrisModel::handleRotate() {
    if (playfield.checkCollisions(activePiece, 0, 0, 1)) {
        return;
    }
    activePiece.rotateClockwise();
}

uint32_t TetrisModel::getScore() {
    return score;
}


Piece& TetrisModel::getNextPiece() {
    return activePieceIndex != 6 ? bag[activePieceIndex + 1] : nextBag[0];
}