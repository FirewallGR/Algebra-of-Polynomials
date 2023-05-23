#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "atpoint.h"
#include "multonconst.h"

#include "Parser.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::clearWidgets() {
    ui->listWidget_name->clear();
    ui->listWidget_value->clear();
}

void MainWindow::on_pushButton_linearArrayTable_clicked() {
    TTableRecord<std::string, Polynom>* data = linearArrayTable.getData();
    size_t count = linearArrayTable.getCount();

    clearWidgets();
    
    ui->nameLabel->setText("Имя (Линейная таблица на массиве)");
    ui->valueLabel->setText("Значение (Линейная таблица на массиве)");

    for (size_t index = 0; index < count; index++) {
        ui->listWidget_name->addItem((data[index].key).c_str());
        ui->listWidget_value->addItem((data[index].value.toString()).c_str());
    }
}

void MainWindow::on_pushButton_linearListTable_clicked() {
    List<TTableRecord<std::string, Polynom>> data = linearListTable.getData();

    clearWidgets();

    ui->nameLabel->setText("Имя (Линейная таблица на листе)");
    ui->valueLabel->setText("Значение (Линейная таблица на листе)");

    for (int i = 0; i < data.size(); i++) {
        ui->listWidget_name->addItem((data.get(i).key).c_str());
        ui->listWidget_value->addItem((data.get(i).value.toString()).c_str());
    }
}

void MainWindow::on_pushButton_sortedArrayTable_clicked() {
    TTableRecord<std::string, Polynom>* data = sortedArrayTable.getData();
    size_t count = sortedArrayTable.getCount();

    clearWidgets();

    ui->nameLabel->setText("Имя (Упорядоченная таблица на массиве)");
    ui->valueLabel->setText("Значение (Упорядоченная таблица на массиве)");

    for (size_t index = 0; index < count; index++) {
        ui->listWidget_name->addItem((data[index].key).c_str());
        ui->listWidget_value->addItem((data[index].value.toString()).c_str());
    }
}

void MainWindow::on_pushButton_AVLTreeTable_clicked() {
    std::vector<TTableRecord<std::string, Polynom>*> array = avlTreeTable.toArray();

    clearWidgets();

    ui->nameLabel->setText("Имя (Таблица на АВЛ дереве)");
    ui->valueLabel->setText("Значение (Таблица на АВЛ дереве)");

    for (const auto& record : array) {
        ui->listWidget_name->addItem((record->key).c_str());
        ui->listWidget_value->addItem((record->value.toString()).c_str());
    }

    for (const auto& record : array) {
        delete record;
    }
}

void MainWindow::on_pushButton_chainMethodTable_clicked() {
    std::vector<std::vector<TTableRecord<std::string, Polynom>>> data = chainTable.getData();
    int size = chainTable.getSize();

    clearWidgets();

    ui->nameLabel->setText("Имя (Хеш-таблица с методом цепочек)");
    ui->valueLabel->setText("Значение (Хеш-таблица с методом цепочек)");

    for (int i = 0; i < size; i++) {
        std::vector<TTableRecord<std::string, Polynom>>& chain = data[i];

        if (!chain.empty()) {
            for (auto it = chain.begin(); it != chain.end(); it++) {
                ui->listWidget_name->addItem((it->key).c_str());
                ui->listWidget_value->addItem((it->value.toString()).c_str());
            }
        }
    }
}

void MainWindow::on_pushButton_openShuffleTable_clicked() {
    TTableRecord<std::string, Polynom>* data = openShuffleTable.getData();
    int size = openShuffleTable.getSize();

    clearWidgets();

    ui->nameLabel->setText("Имя (Хеш-таблица с открытым перемешиванием)");
    ui->valueLabel->setText("Значение (Хеш-таблица с открытым перемешиванием)");

    for (int i = 0; i < size; i++) {
        if (data[i].isDeafult() == false) {
            ui->listWidget_name->addItem((data[i].key).c_str());
            ui->listWidget_value->addItem((data[i].value.toString()).c_str());
        }
    }
}

void MainWindow::on_pushButton_atPoint_clicked() {
    QString selectedText;
    QListWidgetItem* selectedItem = ui->listWidget_name->currentItem();

    if (selectedItem) {
        selectedText = selectedItem->text();

        std::string key = selectedText.toStdString();
        Polynom polynom = linearArrayTable.find(key);

        atPoint dialog(this, polynom);
        dialog.exec();
    }
}

void MainWindow::on_pushButton_multConst_clicked() {
    QString selectedText;
    QListWidgetItem* selectedItem = ui->listWidget_name->currentItem();

    if (selectedItem) {
        selectedText = selectedItem->text();

        std::string key = selectedText.toStdString();
        Polynom polynom = linearArrayTable.find(key);

        MultOnConst dialog(this, polynom);
        dialog.exec();
    }
}

void MainWindow::on_pushButton_addPol_clicked() {
    QString Qkey = ui->lineEdit_key->text();
    QString Qpol = ui->lineEdit_value->text();

    std::string key = Qkey.toStdString();
    std::string pol = Qpol.toStdString();

    ui->lineEdit_key->clear();
    ui->lineEdit_value->clear();

    Polynom polynom = Polynom(pol);

    chainTable.insert(key, polynom);
    openShuffleTable.insert(key, polynom);
    sortedArrayTable.insert(key, polynom);
    linearArrayTable.insert(key, polynom);
    linearListTable.insert(key, polynom);
    avlTreeTable.insert(key, polynom);

    std::string str = key + " = " + polynom.toString() + "  добавился во все таблицы! ";

    QMessageBox::information(this, "Algebra of Polynomials", str.c_str());
}

void MainWindow::on_pushButton_addPolFromExisting_clicked() {
    QString Qkey = ui->lineEdit_key->text();
    QString Qpol = ui->lineEdit_value->text();

    std::string key = Qkey.toStdString();
    std::string pol = Qpol.toStdString();

    ui->lineEdit_key->clear();
    ui->lineEdit_value->clear();

    Parser parser(pol, &sortedArrayTable);
    parser.toPostfix(pol);
    Polynom polynom = parser.calculate();

    chainTable.insert(key, polynom);
    openShuffleTable.insert(key, polynom);
    sortedArrayTable.insert(key, polynom);
    linearArrayTable.insert(key, polynom);
    linearListTable.insert(key, polynom);
    avlTreeTable.insert(key, polynom);

    std::string str = key + " = " + polynom.toString() + "  добавился во все таблицы! ";

    QMessageBox::information(this, "Algebra of Polynomials", str.c_str());
}

void MainWindow::on_pushButton_removePol_clicked() {
    QString selectedText;
    QListWidgetItem* selectedItem = ui->listWidget_name->currentItem();

    if (selectedItem) {
        selectedText = selectedItem->text();

        std::string key = selectedText.toStdString();
        Polynom polynom = linearArrayTable.find(key);
        std::string str = key + " = " + polynom.toString() + "  удалился из всех таблиц! ";

        QMessageBox::information(this, "Algebra of Polynomials", str.c_str());

        chainTable.remove(key);
        openShuffleTable.remove(key);
        sortedArrayTable.remove(key);
        linearArrayTable.remove(key);
        linearListTable.remove(key);
        avlTreeTable.remove(key);
    }
}