#pragma once
#include <string>
#include <inttypes.h>
#include "Piece.h"
#include "Bag.h"
struct ApplicationSpecification {
    int width = 500;
    int height = 800;
    std::string title = "Tetris";
};

class Application {
public:
    Application(const ApplicationSpecification spec = ApplicationSpecification());
    void init();
    void run();
    void shutdown();
private:
    ApplicationSpecification spec;
    size_t currentPieceIndex;
    Piece* currentPiece;
    Bag bag;
    Bag nextBag;
    uint32_t score;
    std::array<std::array<Block, 8>, 20> blocks;
    std::array<std::array<Block, 4>, 4> nextPieceDisplayBlocks;
};
