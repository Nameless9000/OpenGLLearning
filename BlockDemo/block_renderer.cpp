#include <GL/glut.h>
#include <GLES/gl.h>
#include "block_renderer.h"

// block creation
std::vector<Block> blocks;

void create_block(v3 position, BlockColor color) {
    blocks.push_back(Block { position, color });
}

// rendering
static void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    double aspect = (double)viewport[2] / (double)viewport[3];
    gluPerspective(25, aspect, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // move back a bit
    glTranslatef(0, 0, -35);

    static float angle = 0;
    angle += 1.0f;

    glRotatef(angle, 0.1f, 0.2f, 0.5f);

    // draw blocks
    for (Block block : blocks) {
        glPushMatrix();
        glTranslatef(block.position.x, block.position.y, block.position.z);
        glColor3ub(block.color.r, block.color.g, block.color.b);
        glutSolidCube(1);
        glPopMatrix();
    }

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

static void timer(int extra) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void render_init(const char* window_name, int* argc, char** argv) {
    glutInit(argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow(window_name);
}

void render_blocks() {
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
}