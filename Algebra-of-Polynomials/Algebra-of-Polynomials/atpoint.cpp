#include "atpoint.h"
#include "ui_atpoint.h"

#include <QMessageBox>

atPoint::atPoint(QWidget *parent) : QDialog(parent), ui(new Ui::atPoint) {
    ui->setupUi(this);
}

atPoint::atPoint(QWidget* parent, Polynom pol) : QDialog(parent), ui(new Ui::atPoint) {
    ui->setupUi(this);
    polynom = pol;
}

atPoint::~atPoint() {
    delete ui;
}

void atPoint::on_pushButton_ok_clicked() {
    QString Qx = ui->lineEdit_X->text();
    QString Qy = ui->lineEdit_Y->text();
    QString Qz = ui->lineEdit_Z->text();

    double x = Qx.toDouble();
    double y = Qy.toDouble();
    double z = Qz.toDouble();

    double result = polynom.evaluate(x, y, z);

    ui->label_result->setText((std::to_string(result)).c_str());
}
