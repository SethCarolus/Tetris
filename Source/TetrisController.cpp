#include "TetrisController.hpp"

TetrisController::TetrisController(TetrisModel& model, TetrisView& view)
    : model(model), view(view) 
{
    bindCallbacks();
}

void TetrisController::run() {
    while (model.getRunning()) {
        view.handleInput();
        model.update(view.getDeltaTime());
        view.render(model.getPlayfield(), model.getActivePiece());
    }
}

void TetrisController::bindCallbacks() {
    view.setOnQuit([this]() {
        model.handleQuit();
    });

    view.setOnMoveLeft([this]()  {
        model.handleMoveLeft();
    });

    view.setOnMoveRight([this]() {
        model.handleMoveRight();
    });

    view.setOnRotate([this] () {
        model.handleRotate();
    });
}