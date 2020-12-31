#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

#include "open-gl.h"

OpenGL::OpenGL(int size_pixels, int size_meters, const char* name) :
    size_meters(size_meters)
{
    int argc = 0;
    char** argv = NULL;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(size_pixels, size_pixels);
    glutCreateWindow(name);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

float OpenGL::m_to_pix(float m)
{
    return m / size_meters;
}

void OpenGL::draw_square(Colour colour, float x, float y, float size)
{
    set_colour(colour);

    float bl_x = m_to_pix(x - size / 2.0);
    float bl_y = m_to_pix(y - size / 2.0);
    float tr_x = m_to_pix(x + size / 2.0);
    float tr_y = m_to_pix(y + size / 2.0);

    glRectf(bl_x, bl_y, tr_x, tr_y);
}

void OpenGL::draw_circle(Colour colour, float x, float y, float r)
{
    set_colour(colour);

    x = m_to_pix(x);
    y = m_to_pix(y);
    r = m_to_pix(r);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180.0;
        glVertex2f(x + r * cos(theta), y + r * sin(theta));
    }
    glEnd();
}

void OpenGL::set_colour(Colour colour)
{
    float r = ((colour >> 16) & 0xFF) / (float) 0xFF;
    float g = ((colour >>  8) & 0xFF) / (float) 0xFF;
    float b = ((colour >>  0) & 0xFF) / (float) 0xFF;
    glColor3f(r, g, b);
}

void OpenGL::update()
{
    glutSwapBuffers();
}

void OpenGL::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
