#include "mainwindow.hpp"

QWidget* createMainWindow()
{
    QWidget* window = new QWidget;

    window->setWindowTitle("Qt 6.10.1 - No Classes Test");
    window->resize(500, 350);

    return window;
}
