#include "block_renderer.h"

int main(int argc, char** argv)
{
    render_init("Block Demo", argc, argv);

    create_block({ 0, 0, 0 });
    create_block({ 0, 1, 0 });

    render_blocks();
    return 0;
}
