#include "TetrisController.hpp"
#include "TetrisModel.hpp"
#include "TetrisView.hpp"

int main() {
    TetrisModel model {};
    TetrisView view {};
    TetrisController controller { model, view };
    controller.run(); 
}