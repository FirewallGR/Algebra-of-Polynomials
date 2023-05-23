// Algebra-of-Polynomials.cpp: определяет точку входа для приложения.
//
#include "Algebra-of-Polynomials.h"

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}