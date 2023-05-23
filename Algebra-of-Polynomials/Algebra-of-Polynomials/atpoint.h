#ifndef ATPOINT_H
#define ATPOINT_H

#include <QDialog>
#include <mainwindow.h>

#include "Polynom.h"

namespace Ui { class atPoint; }

class atPoint : public QDialog {
    Q_OBJECT
public:
    atPoint(QWidget *parent = nullptr);
    atPoint(QWidget* parent, Polynom pol);
    ~atPoint();
private slots:
    void on_pushButton_ok_clicked();
private:
    Polynom polynom;
    Ui::atPoint *ui;
};

#endif // ATPOINT_H
