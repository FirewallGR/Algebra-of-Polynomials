#include "multonconst.h"
#include "ui_multonconst.h"

MultOnConst::MultOnConst(QWidget *parent) : QDialog(parent), ui(new Ui::MultOnConst) {
    ui->setupUi(this);
}

MultOnConst::MultOnConst(QWidget* parent, Polynom pol) : QDialog(parent), ui(new Ui::MultOnConst) {
    ui->setupUi(this);
    polynom = pol;
}

MultOnConst::~MultOnConst() {
    delete ui;
}

void MultOnConst::on_pushButton_ok_clicked() {
    QString QtmpConst = ui->lineEdit_const->text();

    double tmpConst = QtmpConst.toDouble();

    std::string result = (polynom * tmpConst).toString();

    ui->label_result->setText((result).c_str());
}
