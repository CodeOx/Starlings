#include "glwidget.h"
#include <QtOpenGL>
#include <qmath.h>
#include <QVector3D>
#include <iostream>

#define timePerFrame 0.05
#define radianToDegree 57.296

float magnitude(Vector v){
    float x = v.getFirst();
    float y = v.getSecond();
    float z = v.getThird();

    float mag = qPow((x*x)+(y*y)+(z*z),0.5);

    return mag;
}

float dotProduct(Vector v1, Vector v2){
    return (v1.getFirst() * v2.getFirst()) + (v1.getSecond() * v2.getSecond()) + (v1.getThird() * v2.getThird());
}

float getRotationAngle(Vector v1, Vector v2){
    if (magnitude(v1) != 0 && magnitude(v2)!= 0){
        return qAbs((dotProduct(v1,v2))/((magnitude(v1)*magnitude(v2))));
    }
    return 0.0;
}

Vector getRotationAxis(Vector v1, Vector v2){
    QVector3D qV1(v1.getFirst(),v1.getSecond(),v1.getThird());
    QVector3D qV2(v2.getFirst(),v2.getSecond(),v2.getThird());
    QVector3D qV = QVector3D::crossProduct(qV1,qV2);
    Vector v(qV.x(),qV.y(),qV.z());
    float v_mag = magnitude(v);
    if (v_mag != 0){
        return Vector(v.getFirst()/v_mag,v.getSecond()/v_mag,v.getThird()/v_mag);
    }
    return Vector(0.0,0.0,0.0);
}

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
        Vector b_velocity = b.getVelocity();

        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);

        glScalef(0.06, 0.06, 0.06);

        glTranslatef(b_location.getFirst(), b_location.getSecond(), b_location.getThird());

        //boid originially points towards z -axis
        Vector z_axis(0.0,0.0,1.0);
        float rotationAngle = getRotationAngle(z_axis, b_velocity);
        Vector rotationAxis = getRotationAxis(z_axis, b_velocity);
        glRotatef(radianToDegree * rotationAngle,rotationAxis.getFirst(),rotationAxis.getSecond(),rotationAxis.getThird());

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

