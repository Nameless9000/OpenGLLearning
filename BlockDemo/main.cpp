#include "block_renderer.h"
#include "block_loader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cout << argv[0] << " <file_path> [camera_distance] :: Renders a save file.\n";
        return -1;
    }

    double camera_distance = 15;
    if (argc == 3)
        camera_distance = std::stod(argv[2]);

    render_init("Save Viewer");

    std::ifstream file_input(argv[1]);

    if (!file_input.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file_input.rdbuf();

    std::string save = buffer.str();
    load_blocks(save);

    file_input.close();

    render_blocks(camera_distance);
    return 0;
}
