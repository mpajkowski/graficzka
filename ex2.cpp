//
// Created by marcin on 05.01.18.
//


#include <GL/freeglut.h>
#include <cmath>

namespace ex2
{
float angle = 0.0;
float lx = 0.0, lz = -1.0;
float x = 1.0, z = 6.5;

bool drawSnowman = true;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //kolor tła
    glEnable(GL_DEPTH_TEST);
    GLfloat pozycja[] = { -1.0, 1.0, 0.0, 1.0 }; //światło świeci z góry, z lewej
    glLightfv(GL_LIGHT0, GL_POSITION, pozycja); //położenie światła 0
    glEnable(GL_COLOR_MATERIAL); //włącz materiał obiektu
    glEnable(GL_LIGHT0); //włącz światło 0
    glEnable(GL_LIGHTING); //włącz obliczenia oświetlenia
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
    glutSetOption(GLUT_MULTISAMPLE, 4);
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
    gluLookAt(
        x     , 1.5,  z,
        x + lx, 1.5,  z+lz,
        0.0   , 1.5,  0.0
    );

    glBegin(GL_QUADS);
    glColor3f(0.4, 0.8, 0.5);
    glVertex3f(-50.0, 0.0, -50.0);
    glVertex3f(-50.0, 0.0,  50.0);
    glVertex3f( 50.0, 0.0,  50.0);
    glVertex3f( 50.0, 0.0, -50.0);
    glEnd();

    renderTree();
    renderTeapot();
    if (drawSnowman) renderSnowman();
    glutSwapBuffers();
    glutPostRedisplay();
}

void snowmanToggle(int selection)
{
    switch (selection) {
        case 1:
            drawSnowman = true;
            break;
        case 2:
            drawSnowman = false;
        default:
            break;
    }
    glutPostRedisplay();
}

void colorSelection(int color)
{
    switch(color) {
    case 1:
        glClearColor(0.0, 1.0, 1.0, 0.0);
        break;
    case 2:
        glClearColor(0.7, 0.7, 0.7, 0.0);
        break;
    case 3:
        glClearColor(0.0, 0.0, 0.0, 0.0);
    }
    glutPostRedisplay();
}

int execute(int argc, char **argv)
{
    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    int window = glutCreateWindow("Zadanie 2");

    // callback functions
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    init();

    glutKeyboardFunc([](unsigned char key, int x, int y)
                     {
                         if (key == 27) // if ESC
                             exit(0);
                     }
    );

    glutSpecialFunc([](int key, int xx, int yy)
                    {
                        float fraction = 0.5;

                        switch (key) {
                            case GLUT_KEY_LEFT:
                                angle -= 0.1;
                                lx = sin(angle);
                                lz = -cos(angle);
                                break;
                            case GLUT_KEY_RIGHT:
                                angle += 0.1;
                                lx = sin(angle);
                                lz = -cos(angle);
                                break;
                            case GLUT_KEY_UP:
                                x += lx * fraction;
                                z += lz * fraction;
                                break;
                            case GLUT_KEY_DOWN:
                                x -= lx * fraction;
                                z -= lz * fraction;
                                break;
                        }
                    }
    );

    int submenu1 = glutCreateMenu(colorSelection);
    glutAddMenuEntry("Niebieski", 1);
    glutAddMenuEntry("Szary", 2);
    glutAddMenuEntry("Czarny", 3);
    int submenu2 = glutCreateMenu(snowmanToggle);
    glutAddMenuEntry("Dodaj", 1);
    glutAddMenuEntry("Usun", 2);
    glutCreateMenu([](int c) -> void { static_cast<void>(c); });
    glutAddSubMenu("Kolor nieba", submenu1);
    glutAddSubMenu("Balwanek", submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    glutDestroyMenu(window);
    return 0;
}

} //namespace ex2