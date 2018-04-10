#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    glwidget_ = new GLWidget;
    scrollarea_ = new QScrollArea(parent);
    scrollarea_->setWidget(glwidget_);
    scrollarea_->setWidgetResizable(true);
    scrollarea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollarea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollarea_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    scrollarea_->setMinimumSize(50, 50);
    centralayout_ = new QGridLayout;
    centralayout_->addWidget(scrollarea_, 0, 0);
    ui.centralWidget->setLayout(centralayout_);



}

MainWindow::~MainWindow()
{
    delete glwidget_;
    delete scrollarea_;
    delete centralayout_;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Q/* || Qt::Key::Key_Escape*/)
    {
        std::cout << "Closing window and Quiting..." << std::endl;
        this->close();
    }
}
