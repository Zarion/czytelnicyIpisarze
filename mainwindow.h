#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "biblioteka.h"

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Biblioteka *biblioteka;
    QList<Pisarz*> *listaPisarzy;
    QList<Czytelnik*> *listaCzytelnikow;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
