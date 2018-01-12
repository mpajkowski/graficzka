#include <GL/freeglut.h>
#include <cmath>

namespace ex1
{

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //kolor tła

    glEnable(GL_DEPTH_TEST);
    GLfloat pozycja[] = { -1.0, 1.0, 0.0, 1.0 }; //światło świeci z góry, z lewej
    glLightfv(GL_LIGHT0, GL_POSITION, pozycja); //położenie światła 0
    glEnable(GL_COLOR_MATERIAL); //włącz materiał obiektu
    glEnable(GL_LIGHT0); //włącz światło 0
    glEnable(GL_LIGHTING); //włącz obliczenia oświetlenia
    glutSetOption(GLUT_MULTISAMPLE, 4);
}

void resize(int w, int h)
{
    if (h == 0) h = 1;
    if (w == 0) w = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    gluPerspective(45.0, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void renderTeapot()
{
    glPushMatrix();
    glTranslatef(-1, 0.9, -1);
    glColor3f(1, 1, 0);
    glutSolidTeapot(0.4);
    glPopMatrix();
}

void renderTree()
{
    glPushMatrix();
    glColor3f(0.3, 0.15, 0.15);
    glTranslatef(2, 0.5, 1);
    glutSolidCube(0.2);

    glColor3f(0.0, 0.8, 0.0);
    glTranslatef(0, 0.1, 0);
    glRotated(90, -1.0, 0.0, 0.0);
    glutSolidCone(0.5, 2.0, 50, 50);
    glPopMatrix();
}

void renderSnowman()
{
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-0.85, 1.4, -5.0);
    glutSolidSphere(1.2, 100, 100);
    glTranslatef(0, 1.5, 0);
    glutSolidSphere(0.6, 100, 100);
    glPopMatrix();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(1.0, 1.5, 6.5,
              1.0, 1.5, 5.5,
              0.0, 1.0, 0.0);

    glColor3f(0.8, 0.6, 0.8);
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.8, 0.5);
    glVertex3f(-50.0, 0.0, -50.0);
    glVertex3f(-50.0, 0.0,  50.0);
    glVertex3f( 50.0, 0.0,  50.0);
    glVertex3f( 50.0, 0.0, -50.0);
    glEnd();

    renderTree();
    renderTeapot();
    renderSnowman();
    glutSwapBuffers();
}

int execute(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    int window = glutCreateWindow("Zadanie 1");

    glutDisplayFunc(render);
    glutReshapeFunc(resize);

    init();

    glutKeyboardFunc([](unsigned char key, int x, int y)
                     {
                         if (key == 27)
                             exit(0);
                     }
    );

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    glutDestroyMenu(window);

    return 0;
}

} // namespace v1
