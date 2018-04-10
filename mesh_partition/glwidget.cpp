#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    settings_ = new GLWidgetSettings;
}

GLWidget::~GLWidget()
{
    delete settings_;
}

/************************************************************************/
/* Protected functions
*/
/************************************************************************/
void GLWidget::initializeGL()
{
    //initLighting();
    glEnable(GL_DEPTH_TEST);
    //glPointSize(5.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_POINT_SMOOTH);
    setCursor(QCursor(Qt::ArrowCursor));

    glDisable(GL_LIGHTING);
    //glDisable(GL_TEXTURE_2D);
    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
//    glClearColor(0, 0, 0, 0);
}

void GLWidget::paintGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_ONE, GL_ZERO);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    //glEnable(GL_LIGHTING);

    glPushMatrix();
    glMultMatrixf((GLfloat*)settings_->transformation_);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float residue = 20.0;

    // orthogonal projection
    // Note: the last parameter zFar should not be very large, or the front of the model
    // is very likely to be transparent. Here I use 100.
    glOrtho((-residue - settings_->xshift_ - settings_->zshift_) / residue * render_range_, // left
            (residue - settings_->xshift_ + settings_->zshift_) / residue * render_range_,      // right
            (-residue - settings_->yshift_ - settings_->zshift_) / residue * render_range_,     // bottom
            (residue - settings_->yshift_ + settings_->zshift_) / residue * render_range_,      // top
            (-2 * residue - settings_->zshift_ - settings_->clipping) / (residue)* render_range_,       // zNear
            100);                                                               // zFar

    glMatrixMode(GL_MODELVIEW);
    renderModel();
    glPopMatrix();
    glFlush();

}
void GLWidget::resizeGL(int width, int height)
{
    int max = width > height ? width : height;
    glViewport((width - max) / 2, (height - max) / 2, max, max);
    //   int side = qMin(width, height);
    //   //glViewport((width - side) / 2, (height - side) / 2, side, side);
    //glViewport(0,0, width, height);
    /*QRect rect = QApplication::desktop()->availableGeometry();*/
    //gluPerspective(90, (GLdouble)(width/height), 5, 5+viewSpeed);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, +1.0, -1.0, 1.0, 5.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -40.0);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_lastpos2d_ = event->pos();
    if (event->button() == Qt::MidButton)
    {
        mouse_mode_ = TRANSLATE;
        setCursor(QCursor(Qt::SizeAllCursor));
    }
    if (event->button() == Qt::LeftButton)
    {
        mouse_mode_ = ROTATE;
        point2Triple(mouse_lastpos2d_.x(), mouse_lastpos2d_.y(), mouse_lastpos3d_);
        setCursor(QCursor(Qt::CrossCursor));
    }
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x(), y = event->y();

    // --------------------------------------------------
    // Show the 3D coordinates in real time
    //coordTransformation(x,y,lastPos3D);
    //mouse2DPosStr = tr("2D Coordinates: (%1, %2)").arg(x).arg(y);
    //mouse3DPosStr = tr("OpenGL Coordinates: (%1, %2, %3)").arg(lastPos3D[0])
    //  .arg(lastPos3D[1]).arg(lastPos3D[2]);
    //updateGL();   // Must be added in order to flush
    // ---------------------------------------------------

    switch (mouse_mode_)
    {
    case ROTATE:
        float currentPosition[3], angle, dx, dy, dz;

        point2Triple(x, y, currentPosition);

        dx = currentPosition[0] - mouse_lastpos3d_[0];
        dy = currentPosition[1] - mouse_lastpos3d_[1];
        dz = currentPosition[2] - mouse_lastpos3d_[2];

        angle = 180.0 * sqrt(dx * dx + dy * dy + dz * dz);

        float rotate_axis[3];
        rotate_axis[0] = mouse_lastpos3d_[1] * currentPosition[2] - mouse_lastpos3d_[2] * currentPosition[1];
        rotate_axis[1] = mouse_lastpos3d_[2] * currentPosition[0] - mouse_lastpos3d_[0] * currentPosition[2];
        rotate_axis[2] = mouse_lastpos3d_[0] * currentPosition[1] - mouse_lastpos3d_[1] * currentPosition[0];
        mouse_lastpos3d_[0] = currentPosition[0];
        mouse_lastpos3d_[1] = currentPosition[1];
        mouse_lastpos3d_[2] = currentPosition[2];

        glPushMatrix();
        glLoadIdentity();
        glRotatef(angle, rotate_axis[0], rotate_axis[1], rotate_axis[2]);
        glMultMatrixf((GLfloat*)settings_->transformation_);
        glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)settings_->transformation_);
        glPopMatrix();
        updateGL();
        break;

    case TRANSLATE:
        settings_->xshift_ += (x - mouse_lastpos2d_.x()) / (float)width() * 10;
        settings_->yshift_ -= (y - mouse_lastpos2d_.y()) / (float)height() * 10;
        mouse_lastpos2d_ = event->pos();
        updateGL();
        break;

    default:
        //lastPos = event->pos();
        updateGL();
        break;
    }
}

void GLWidget::resizeEvent(QResizeEvent* event)
{
    QSize size = event->size();
    resizeGL(size.width(), size.height());
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton)
        cout << "Translation end point: ";
    if (event->button() == Qt::LeftButton)
        cout << "Rotation end point: ";
    cout << event->pos().x() << "," << event->pos().y() << endl;
    mouse_mode_ = NONE;
    setCursor(QCursor(Qt::ArrowCursor));
    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    int degree = event->delta() / 120;
    settings_->zshift_ += degree * 0.8;
    updateGL();
}

// Convert a 2D pixel point (clicked by the mouse) to 3D point in OpenGL coordinate space
void GLWidget::point2Triple(int x, int y, float triplef[3])
{
    float df, a;
    triplef[0] = (2.0 * x - width()) / width();
    triplef[1] = (height() - 2.0 * y) / height();
    df = sqrt(triplef[0] * triplef[0] + triplef[1] * triplef[1]);
    triplef[2] = cos((kPi / 2) * ((df < 1.0) ? df : 1.0));
    a = 1.0 / sqrt(triplef[0] * triplef[0] + triplef[1] * triplef[1] + triplef[2] * triplef[2]);
    triplef[0] *= a;
    triplef[1] *= a;
    triplef[2] *= a;
}

/************************************************************************/
/* Data I/O
*/
/************************************************************************/




/************************************************************************/
/* Display functions
*/
/************************************************************************/
void GLWidget::renderModel()
{
//    switch (target_type_)
//    {
//    case NOTHING:
//        break;
//    case ORIGINAL_MESH:
//        displayOriginModel();
//        break;
//    case RGBD_POINT_CLOUD:
//        displayRGBDPointCloud();
//        break;
//    case GLOBAL_PLANES:
//        break;
//    case PROJECTED_POINTS_ON_PLANES:
//        break;
//    default:
//        break;
//    }
}


