#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QObject>
#include <QGLWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QSurfaceFormat>
#include <GL/glu.h>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void animate();
    void addBoid();

private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLfunctions;

    void draw();
    void drawAxis();

    int xRot;
    int yRot;
    int zRot;

    int elapsed;
    int numBoids;

    QPoint lastPos;
};

#endif // GLWIDGET_H
