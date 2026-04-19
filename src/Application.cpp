#include "Application.h"

#include "Piece.h"
#include "raylib.h"

#include <inttypes.h>
#include <algorithm>
bool isRowFull(std::array<Block, 8> row) {
    for (int i = 0; i < 8; i++) {
        if (row[i].type == BlockType::VOID) {
            return false;
        }
    }
    return true;
}

bool isAnyRowFull(std::array<std::array<Block, 8>, 20>& blocks) {
    for (int i = 0; i < 20; i++) {
        if (isRowFull(blocks[i])) {
            return true;
        }
    }
    return false;
}

void handleRowDeletion(std::array<std::array<Block, 8>, 20>& blocks, uint32_t& score) {

    while (isAnyRowFull(blocks)) {
        for (int i = 19; i > 0; i--) {
            if (isRowFull(blocks[i])) {
                for (int j = 0; j < 8; j++) {
                    blocks[i][j].type = BlockType::VOID;
                    blocks[i][j].color =  BLACK;
                }

                for (int j = i - 1; j >= 0; j--) {
                    for (int k = 0; k < 8; k++) {
                        if (blocks[j][k].type != BlockType::VOID && blocks[j + 1][k].type == BlockType::VOID) {
                            blocks[j + 1][k] = blocks[j][k];
                            blocks[j + 1][k].row = j +1;
                            blocks[j][k] = Block(j, k);
                        }
                    }
                }
                score++;
            }
        }
    }
}

Application::Application(const ApplicationSpecification spec)
    :spec(std::move(spec)), bag(), nextBag()
    {
    }

void Application::init() {
    if (!IsWindowReady()) {
     InitWindow(spec.width, spec.height, spec.title.c_str());
     SetTargetFPS(60);
    }
    for (int i = 0; i < 20;i++) {
        for (int j = 0; j < 8; j++) {
            blocks[i][j] = Block(i, j);
        }
    }
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j++) {
           nextPieceDisplayBlocks[i][j] = Block(i, j);
        }
    }
    currentPieceIndex = 0;
    currentPiece = &bag[currentPieceIndex];

   for (auto& block : bag[currentPieceIndex + 1].blocks) {
       nextPieceDisplayBlocks[block.row][block.column] = block;
   }
    score = 0;
}
void Application::run() {
  const int width = spec.height / 20;
  const int height = spec.height / 20;

  const int padding = (spec.width - width * 8) / 2;

  auto lastTime = GetTime();
  const auto interval = 0.25f;

  while (!WindowShouldClose()) {
    if (currentPiece->bricked) {
      for (auto& block : currentPiece->blocks) {
        blocks[block.row][block.column] = block;
      }

    if (currentPieceIndex == 6) {
      bag = nextBag;
      nextBag = Bag();
      currentPieceIndex = -1;
    }
    else {
      currentPiece = &bag[++currentPieceIndex];
    }

    handleRowDeletion(blocks, score);

    for (int i = 0; i < 4; i ++) {
      for (int j = 0; j < 4; j++) {
        nextPieceDisplayBlocks[i][j] = Block(i, j);
      }
    }

         for (auto& block : bag[std::clamp<int>(currentPieceIndex + 1, 0, 6)].blocks) {
             if (block.row < 0 || block.row > 3 || block.column < 0 || block.column > 3)
                 break;
             nextPieceDisplayBlocks[block.row][block.column] = block;
         }
        }
        auto currentTime = GetTime();

        bool left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
        bool right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
        if ((currentTime - lastTime) >= interval) {
            lastTime = currentTime;
            currentPiece->move(Direction::DOWN, blocks);

            if (left) {
                currentPiece->move(Direction::LEFT, blocks);
            }
            if (right) {
                currentPiece->move(Direction::RIGHT, blocks);
            }
        }

        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
            currentPiece->fall(blocks);
            currentPiece->bricked = true;
        }
        BeginDrawing();
        ClearBackground(ColorFromHSV(167, 0.67f, 0.67f));
        DrawText(("Score: " + std::to_string(score)).c_str(), spec.width - padding, 0, 20, BLACK);

        for (auto& row : blocks) {
            for (auto& block : row) {
                DrawRectangle(padding + block.column * width, block.row * height, width - 2, height - 2, block.color);
            }
        }

        for (auto& row : nextPieceDisplayBlocks) {
            for (auto& block : row) {
                DrawRectangle(6  + block.column * width * 0.5, 6 +  block.row * height * 0.5 , width * 0.5 - 2, height * 0.5 - 2, block.color);
            }
        }
        DrawText("Next", 6, 100 , 20, BLACK);

        for (int k = 0; k < 4; k++ ) {
            DrawRectangle(padding + currentPiece->blocks[k].column * width, currentPiece->blocks[k].row * height, width - 2, height - 2, currentPiece->blocks[k].color);
        }

        EndDrawing();
    }

}

void Application::shutdown() {

}
