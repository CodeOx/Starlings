#include "glwidget.h"
#include <QtOpenGL>
#include <qmath.h>
#include <iostream>

#define timePerFrame 0.05

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    elapsed = 0;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glColor3f(1, 0, 0);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    drawAxis();
    draw();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void GLWidget::draw()
{

    for(int i = 0; i < s.getSwarmSize(); i++){

        Boid b = s.getBoid(i);
        Vector b_location = b.getLocation();

        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);

        //std::cout<<i;

        //float newPosX = 15.0 * qCos(elapsed*6.28319/4000);
        //float newPosY = 10.0 * qSin(elapsed*6.28319/4000);
        //float newPosZ = 15.0 * qSin(elapsed*6.28319/4000);

        //float deltaX = newPosX - posX;
        //float deltaY = newPosY - posY;
        //float deltaZ = newPosZ - posZ;

        //float normalize = qSqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ));

        glScalef(0.08, 0.08, 0.08);

        //glRotatef(57.29 * qAcos(deltaX/normalize), 1.0, qAcos(deltaY/normalize), qAcos(deltaZ/normalize));
        //glRotatef(57.29 * (deltaX/normalize), 1.0, 0.0, 0.0);

        glTranslatef(b_location.getFirst(), b_location.getSecond(), b_location.getThird());

        //posX = newPosX;
        //posY = newPosY;
        //posZ = newPosZ;


        glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glNormal3f(0,0,-1);
            glVertex3f(-1,-1,0);
            glVertex3f(-1,1,0);
            glVertex3f(1,1,0);
            glVertex3f(1,-1,0);

        glEnd();
        glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0.5, 0.5);
            glNormal3f(0,-1,0.707);
            glVertex3f(-1,-1,0);
            glVertex3f(1,-1,0);
            glVertex3f(0,0,1.2);
        glEnd();
        glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0.5, 0.5);
            glNormal3f(1,0, 0.707);
            glVertex3f(1,-1,0);
            glVertex3f(1,1,0);
            glVertex3f(0,0,1.2);
        glEnd();
        glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0.5, 0.5);
            glNormal3f(0,1,0.707);
            glVertex3f(1,1,0);
            glVertex3f(-1,1,0);
            glVertex3f(0,0,1.2);
        glEnd();
        glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0.5, 0.5);
            glNormal3f(-1,0,0.707);
            glVertex3f(-1,1,0);
            glVertex3f(-1,-1,0);
            glVertex3f(0,0,1.2);
        glEnd();
        glPopMatrix();
    }
}

void GLWidget::drawAxis()
{
    glPushMatrix();
    glLineWidth(1.5);
    glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, -0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, -0.5);
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glPopMatrix();
}

void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 4000;
    update();
    s.update(timePerFrame);
}

void GLWidget::addBoid()
{
    Boid b;
    s.addBoid(b);
}

