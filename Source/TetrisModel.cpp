#include "TetrisModel.hpp"

TetrisModel::TetrisModel()
    : running(true)
{
}

void TetrisModel::update() {
}

void TetrisModel::handleQuit() {
    running = false;
};