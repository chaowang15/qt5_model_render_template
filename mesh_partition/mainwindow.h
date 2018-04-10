#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QGridLayout>
#include <QKeyEvent>
#include <iostream>
#include "glwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:


protected:
    void keyPressEvent(QKeyEvent *e);

private:
	Ui::MainWindowClass ui;
    GLWidget* glwidget_;
    QScrollArea *scrollarea_;
    QGridLayout *centralayout_;
};

#endif // MAINWINDOW_H
