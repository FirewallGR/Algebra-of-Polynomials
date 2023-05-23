#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ChainMethodTable.h"
#include "OpenShuffleTable.h"
#include "LinearListTable.h"
#include "LinearArrayTable.h"
#include "SortedArrayTable.h"
#include "AVLTreeTable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_linearArrayTable_clicked();
    void on_pushButton_linearListTable_clicked();
    void on_pushButton_sortedArrayTable_clicked();
    void on_pushButton_AVLTreeTable_clicked();
    void on_pushButton_chainMethodTable_clicked();
    void on_pushButton_openShuffleTable_clicked();
    void on_pushButton_atPoint_clicked();
    void on_pushButton_multConst_clicked();
    void on_pushButton_addPol_clicked();
    void on_pushButton_removePol_clicked();
    void on_pushButton_addPolFromExisting_clicked();
private:
    Ui::MainWindow *ui;

    LinearArrayTable<std::string, Polynom> linearArrayTable;
    LinearListTable<std::string, Polynom> linearListTable;
    SortedArrayTable<std::string, Polynom> sortedArrayTable;
    AVLTreeTable<std::string, Polynom> avlTreeTable;
    ChainMethodTable<std::string, Polynom> chainTable;
    OpenShuffleTable<std::string, Polynom> openShuffleTable;

    void clearWidgets();
};
#endif // MAINWINDOW_H
