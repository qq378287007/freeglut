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

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '\x1B':
    {
        exit(EXIT_SUCCESS);
        break;
    }

    case 'c':
    case 'C':
    {
        GLint viewPort[4];
        glGetIntegerv(GL_VIEWPORT, viewPort);
        printf("x: %d, y: %d, window width: %d, window height: %d \n", viewPort[0], viewPort[1], viewPort[2], viewPort[3]);

        int width = viewPort[2];
        int height = viewPort[3];
        
        unsigned char *colorArr = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 4);
        glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)colorArr);
        FILE *fp = fopen("out.txt", "wt");
        for (int i = 0; i < width * height; i++)
            fprintf(fp, "%03d, %03d, %03d, %03d\n", colorArr[i * 4], colorArr[i * 4 + 1], colorArr[i * 4 + 2], colorArr[i * 4 + 3]);
        fclose(fp);
        free(colorArr);

        break;
    }
    }
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
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return EXIT_SUCCESS;
}
