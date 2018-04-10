#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtGui/QtGui>
#include <QFileDialog>
#include <iostream>
#include <string>
#include "glwidgetsettings.h"

using namespace std;

enum MouseAtionMode { NONE = 0, SELECT, ROTATE, TRANSLATE };

class GLWidget : public QGLWidget
{
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    /* Rendering */
    void renderModel();


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void point2Triple(int x, int y, float triplef[3]);

public:
    /* Render related */
    const double kPi = 3.141592653589793;
    GLWidgetSettings *settings_;
    float render_range_;
    float mouse_lastpos3d_[3];
    QPoint mouse_lastpos2d_;
    QPoint mouse_curpos2d_;
    MouseAtionMode mouse_mode_;

    /* Partition */

};


#endif // GLWIDGET_H
