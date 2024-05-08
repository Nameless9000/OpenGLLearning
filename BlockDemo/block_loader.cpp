#include "block_loader.h"
#include <sstream>

BlockColor block_colors[] = {
    { 255, 9, 0 }, // NOR
    { 0, 121, 255 }, // AND
    { 0, 241, 29 }, // OR
    { 168, 0, 255 }, // XOR
    { 255, 127, 0 }, // BUTTON
    { 30, 30, 30 }, // FLIPFLOP
    { 175, 175, 175 }, // LED
    { 175, 131, 76 }, // SOUND
    { 73, 185, 255 }, // CONDUCTOR
    { 255, 72, 72 }, // CUSTOM
    { 0, 42, 89 }, // NAND
    { 213, 0, 103 }, // XNOR
    { 84, 54, 35 }, // RANDOM
    { 25, 71, 84 }, // TEXT
    { 75, 75, 75 }, // TILE
    { 165, 177, 200 }, // NODE
    { 98, 24, 148 }, // DELAY
    { 235, 233, 183 }, // ANTENNA
    { 73, 185, 255 } // CONDUCTORV2
};

void load_blocks(std::string save) {
    std::stringstream save_stream(save);
    std::string item;

    std::getline(save_stream, item, '?');
    std::stringstream blocks_stream(item);

    while (std::getline(blocks_stream, item, ';')) {
        std::stringstream block_stream(item);
        std::vector<std::string> block_values;

        while (std::getline(block_stream, item, ',')) {
            block_values.push_back(item);
        }

        unsigned char block_number = std::stoi(block_values[0]);
        BlockColor color = block_colors[block_number];

        v3 position = { 0, 0, 0 };

        if (!block_values[2].empty()) {
            position.x = static_cast<short>(std::stoi(block_values[2]));
        }
        if (!block_values[3].empty()) {
            position.y = static_cast<short>(std::stoi(block_values[3]));
        }
        if (!block_values[4].empty()) {
            position.z = static_cast<short>(std::stoi(block_values[4]));
        }

        std::vector<short> properties;
        if (block_number == 13)
            properties = { 75, 75, 75 };

        if (block_values.size() == 6 && !block_values[5].empty()) {
            std::stringstream properties_stream(block_values[5]);

            while (std::getline(properties_stream, item, '+')) {
                properties.push_back(std::stoi(item));
            }
        }

        if (block_number == 13) {
            color.r = (unsigned char)properties[0];
            color.g = (unsigned char)properties[1];
            color.b = (unsigned char)properties[2];
        }

        create_block(position, color);
    }
}