#include <stdio.h>
#include <GL/glut.h>

void errorCheck()
{
    GLenum code = glGetError();
    if (code != GL_NO_ERROR)
    {
        const GLubyte *string = gluErrorString(code);
        fprintf(stderr, "OpenGL error: %s\n", string);
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2i(180, 15);
    glVertex2i(10, 145);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("hello");

    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();

    return EXIT_SUCCESS;
}
