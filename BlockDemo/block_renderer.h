#pragma once
#include "vector"

struct v3 {
    float x, y, z;
};

struct BlockColor {
    unsigned char r, g, b;
};

struct Block {
    v3 position;
    BlockColor color;
};

void render_init(const char* window_name);
void create_block(v3 position, BlockColor color = { 255, 0, 0 });
void render_blocks();