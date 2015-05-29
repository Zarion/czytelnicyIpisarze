#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int lPisarzy = 2;
    int lCzytelnikow = 5;
    int lKsiazek = 3;
    listaCzytelnikow = new QList<Czytelnik*>();
    listaPisarzy = new QList<Pisarz*>();

    biblioteka = new Biblioteka(lKsiazek);
    QObject::connect(biblioteka, SIGNAL(showCzytelnicy()), this, SLOT(slot_showCzytelicy()), Qt::DirectConnection);
    QObject::connect(biblioteka, SIGNAL(showPisarze()), this, SLOT(slot_showPisarze()), Qt::DirectConnection);

    for (int i = 0 ; i < lPisarzy ; i++ ){
        Pisarz *pisarz = new Pisarz(i+1);
        listaPisarzy->append(pisarz);

        QObject::connect(pisarz, SIGNAL(stoppedDoNothing()), pisarz, SLOT(slot_stoppedDoNothing()), Qt::DirectConnection);
        QObject::connect(pisarz, SIGNAL(stoppedWriting()), pisarz, SLOT(slot_stoppedWriting()), Qt::DirectConnection);
        QObject::connect(pisarz, SIGNAL(boredToDeath()), pisarz, SLOT(slot_boredToDeath()), Qt::DirectConnection);
        QObject::connect(pisarz, SIGNAL(startDoNothingAgain()), pisarz, SLOT(doNothing()), Qt::DirectConnection);

        QObject::connect(pisarz, SIGNAL(freeSlot()), biblioteka, SLOT(slot_freeSlotPisarz()), Qt::DirectConnection);
        QObject::connect(pisarz, SIGNAL(meWantsWrite(Pisarz*)), biblioteka, SLOT(slot_requestedSlotByPisarz(Pisarz*)), Qt::DirectConnection);
    }

    for (int i = 0 ; i < lCzytelnikow ; i++ ){
        Czytelnik *czytelnik = new Czytelnik(i+1);
        listaCzytelnikow->append(czytelnik);

        QObject::connect(czytelnik, SIGNAL(stoppedDoNothing()), czytelnik, SLOT(slot_stoppedDoNothing()), Qt::DirectConnection);
        QObject::connect(czytelnik, SIGNAL(stoppedReading()), czytelnik, SLOT(slot_stoppedReading()), Qt::DirectConnection);
        QObject::connect(czytelnik, SIGNAL(boredToDeath()), czytelnik, SLOT(slot_boredToDeath()), Qt::DirectConnection);
        QObject::connect(czytelnik, SIGNAL(startDoNothingAgain()), czytelnik, SLOT(doNothing()), Qt::DirectConnection);

        QObject::connect(czytelnik, SIGNAL(freeSlot()), biblioteka, SLOT(slot_freeSlotCzytelnik()), Qt::DirectConnection);
        QObject::connect(czytelnik, SIGNAL(meWantsRead(Czytelnik*)), biblioteka, SLOT(slot_requestedSlotByCzytelnik(Czytelnik*)), Qt::DirectConnection);
    }


    for ( int i = 0 ; i < listaCzytelnikow->size() ; i++ ){
        (*listaCzytelnikow)[i]->startThread();
    }

    for ( int i = 0 ; i < listaPisarzy->size() ; i++ ){
        (*listaPisarzy)[i]->startThread();
    }

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete biblioteka;
    listaCzytelnikow->clear();
    listaPisarzy->clear();

    delete listaCzytelnikow;
    delete listaPisarzy;
    delete ui;
}

void MainWindow::slot_showCzytelicy(){
    ui->label->setText( QString::number(biblioteka->getCzytelnicy()));
}

void MainWindow::slot_showPisarze(){
     ui->label_2->setText( QString::number(biblioteka->getPisarze()));
}
