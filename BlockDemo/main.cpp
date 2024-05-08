#include "block_renderer.h"
#include "block_loader.h"

int main(int argc, char** argv) {
    render_init("Block Demo", &argc, argv);

    load_blocks("0,,,,,?");

    render_blocks();
    return 0;
}
