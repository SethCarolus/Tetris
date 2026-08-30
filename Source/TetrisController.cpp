#include "TetrisController.hpp"

TetrisController::TetrisController(TetrisModel& model, TetrisView& view)
    : model(model), view(view) 
{
    bindCallbacks();
}

void TetrisController::run() {
    while (model.getRunning()) {
        view.handleInput();
        model.update();
        view.render();
    }
}

void TetrisController::bindCallbacks() {
    view.setOnQuit([this]() {
        model.handleQuit();
    });
}