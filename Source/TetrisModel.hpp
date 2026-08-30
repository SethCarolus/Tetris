#pragma once

class TetrisModel {
public: 
    TetrisModel();
    bool getRunning() { return running;}
    void update();
    void handleQuit();
private:
    bool running;
};