#ifndef MULTONCONST_H
#define MULTONCONST_H

#include <QDialog>

#include "Polynom.h"

namespace Ui { class MultOnConst; }

class MultOnConst : public QDialog {
    Q_OBJECT
public:
    MultOnConst(QWidget *parent = nullptr);
    MultOnConst(QWidget* parent, Polynom polynom);
    ~MultOnConst();
private slots:
    void on_pushButton_ok_clicked();
private:
    Polynom polynom;
    Ui::MultOnConst *ui;
};

#endif // MULTONCONST_H
