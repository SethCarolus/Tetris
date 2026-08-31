#include "TetrisModel.hpp"
#include "Tetromino.hpp"

TetrisModel::TetrisModel() {
    activePiece.type = PieceType::J;
    activePiece.Data = J_PIECE;
    activePiece.x += 4;
    activePiece.y += 4;
    activePiece.rotation = 1;
}

Playfield& TetrisModel::getPlayfield() {
    return  playfield;
}
ActivePiece& TetrisModel::getActivePiece() {
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
        playfield.clearLines();
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