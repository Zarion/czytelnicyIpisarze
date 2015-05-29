#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int lPisarzy = 2;
    int lCzytelnikow = 5;
    int lKsiazek = 3;

    biblioteka = new Biblioteka(lKsiazek);

    qDebug() << biblioteka->getPisarze();

    for (int i = 0 ; i < lPisarzy ; i++ ){
        listaPisarzy << new Pisarz(i+1);

        QObject::connect(listaPisarzy[i], SIGNAL(stoppedDoNothing()), listaPisarzy[i], SLOT(slot_stoppedDoNothing()), Qt::DirectConnection);
        QObject::connect(listaPisarzy[i], SIGNAL(stoppedWriting()), listaPisarzy[i], SLOT(slot_stoppedWriting()), Qt::DirectConnection);
        QObject::connect(listaPisarzy[i], SIGNAL(boredToDeath()), listaPisarzy[i], SLOT(slot_boredToDeath()), Qt::DirectConnection);
        QObject::connect(listaPisarzy[i], SIGNAL(startDoNothingAgain()), listaPisarzy[i], SLOT(doNothing()), Qt::DirectConnection);

        QObject::connect(listaPisarzy[i], SIGNAL(freeSlot()), biblioteka, SLOT(slot_freeSlotPisarz()), Qt::DirectConnection);
        QObject::connect(listaPisarzy[i], SIGNAL(meWantsWrite(Pisarz*)), biblioteka, SLOT(slot_requestedSlotByPisarz(Pisarz*)), Qt::DirectConnection);
    }

    for (int i = 0 ; i < lCzytelnikow ; i++ ){
        listaCzytelnikow << new Czytelnik(i+1);

        QObject::connect(listaCzytelnikow[i], SIGNAL(stoppedDoNothing()), listaCzytelnikow[i], SLOT(slot_stoppedDoNothing()), Qt::DirectConnection);
        QObject::connect(listaCzytelnikow[i], SIGNAL(stoppedReading()), listaCzytelnikow[i], SLOT(slot_stoppedReading()), Qt::DirectConnection);
        QObject::connect(listaCzytelnikow[i], SIGNAL(boredToDeath()), listaCzytelnikow[i], SLOT(slot_boredToDeath()), Qt::DirectConnection);
        QObject::connect(listaCzytelnikow[i], SIGNAL(startDoNothingAgain()), listaCzytelnikow[i], SLOT(doNothing()), Qt::DirectConnection);

        QObject::connect(listaCzytelnikow[i], SIGNAL(freeSlot()), biblioteka, SLOT(slot_freeSlotCzytelnik()), Qt::DirectConnection);
        QObject::connect(listaCzytelnikow[i], SIGNAL(meWantsRead(Czytelnik*)), biblioteka, SLOT(slot_requestedSlotByCzytelnik(Czytelnik*)), Qt::DirectConnection);
    }

    qDebug() << biblioteka->getPisarze();

    for ( int i = 0 ; i < listaCzytelnikow.length() ; i++ ){
        listaCzytelnikow[i]->startThread();
    }

    for ( int i = 0 ; i < listaPisarzy.length() ; i++ ){
        listaPisarzy[i]->startThread();
    }

    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete biblioteka;
    for ( int i = 0 ; i < listaCzytelnikow.length() ; i++ ){
        delete listaCzytelnikow[i];
    }

    for ( int i = 0 ; i < listaPisarzy.length() ; i++ ){
        delete listaPisarzy[i];
    }
    delete ui;
}
