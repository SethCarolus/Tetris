#pragma once

#include "TetrisModel.hpp"
#include "TetrisView.hpp"

class TetrisController {
public:
    TetrisController(TetrisModel& model, TetrisView& view);
    void run();
private:
    void bindCallbacks();

    TetrisModel& model;
    TetrisView& view; 
};