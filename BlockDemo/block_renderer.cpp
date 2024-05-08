#include "block_renderer.h"
#include <GL/glut.h>
#include <GLES/gl.h>
#include <tuple>
#include <vector>
#include <iostream>

// block creation
std::vector<Block> blocks;
std::vector<Block> pblocks;

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

GLdouble distance = 15;
GLdouble centerx = 0.0;
GLdouble centery = 0.0;
GLdouble centerz = 0.0;
static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    double aspect = (double)viewport[2] / (double)viewport[3];
    gluPerspective(60, aspect, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLdouble eyeY = distance * std::sin(3.14 / 5);
    GLdouble eyeZ = distance * std::cos(3.14 / 5);

    static float angle = 0;
    angle += 1.0f;

    gluLookAt(0, eyeY, eyeZ,
        0, 0, 0,
        0, 1, 0);

    glRotatef(angle, 0.0f, 0.1f, 0.0f);

    // draw blocks
    for (Block block : blocks) {
        glPushMatrix();
        glTranslatef(
            block.position.x - (float)centerx,
            block.position.y - (float)centery,
            block.position.z - (float)centerz);
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

void render_init(const char* window_name) {
    {
        int argc = 1;
        char* argv[1] = { (char*)"" };
        glutInit(&argc, argv);
    }
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow(window_name);
}

bool rendered = false;
void render_blocks(double camera_distance)
{
    if (rendered)
        return;
    rendered = true;

    distance = camera_distance;

    GLdouble sum_X = 0.0, sum_Y = 0.0, sum_Z = 0.0;
    for (Block block : blocks) {
        sum_X += block.position.x;
        sum_Y += block.position.y;
        sum_Z += block.position.z;
    }

    centerx = sum_X / blocks.size();
    centery = sum_Y / blocks.size();
    centerz = sum_Z / blocks.size();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
}