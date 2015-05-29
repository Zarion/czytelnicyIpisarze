#ifndef CZYTELNIK_H
#define CZYTELNIK_H

#include <QObject>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QtTest/QTest>

class Czytelnik : public QObject
{
     Q_OBJECT
public:
    Czytelnik();
    Czytelnik(int id);
    ~Czytelnik();
    int getId() const;
    void setId(int value);

    void startThread();

    bool getChceCzytac() const;
    void setChceCzytac(bool value);

    bool getCzyta() const;
    void setCzyta(bool value);

    int getKsiazka() const;
    void setKsiazka(int value);

    int getZawartosc() const;
    void setZawartosc(int value);

signals:
    void stoppedDoNothing();
    void meWantsRead(Czytelnik *czytelnik);
    void startDoNothingAgain();
    void boredToDeath();
    void stoppedReading();
    void freeSlot();

private:
    int id;
    bool chceCzytac;
    bool czyta;
    int ksiazka;
    int zawartosc;

    QFuture<void> future;
    QFutureWatcher<void> watcher;

    int getTimeOfDoNothing();
    int getCurrentTimeInSeconds();

public slots:
    void doNothing();
    void slot_stoppedDoNothing();
    void slot_stoppedReading();
    void slot_boredToDeath();
};

#endif // CZYTELNIK_H
