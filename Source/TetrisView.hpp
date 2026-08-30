#pragma once

#include <functional>

class TetrisView {
public:
    using Callback = std::function<void()>;
    void setOnQuit(Callback callback);

    TetrisView();
    ~TetrisView();
    void render();
    void handleInput();
private:
    Callback onQuit;
};