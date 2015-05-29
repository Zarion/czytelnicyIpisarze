#ifndef PISARZ_H
#define PISARZ_H

#include <QObject>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QtTest/QTest>

class Pisarz : public QObject
{
     Q_OBJECT
public:
    Pisarz();
    Pisarz(int id);
    ~Pisarz();

    void startThread();

    int getId() const;
    void setId(int value);

    bool getChcePisac() const;
    void setChcePisac(bool value);

    bool getPisze() const;
    void setPisze(bool value);

    int getKsiazka() const;
    void setKsiazka(int value);

    int getNowaZawartosc() const;
    void setNowaZawartosc(int value);

    int getStaraZawartosc() const;
    void setStaraZawartosc(int value);

signals:
    void stoppedDoNothing();
    void meWantsWrite(Pisarz *pisarz);
    void startDoNothingAgain();
    void boredToDeath();
    void stoppedWriting();
    void freeSlot();

private:
    int id;
    bool chcePisac;
    bool pisze;
    int ksiazka;
    int nowaZawartosc;
    int staraZawartosc;

    QFuture<void> future;
    QFutureWatcher<void> watcher;

    int getTimeOfDoNothing();
    int getCurrentTimeInSeconds();

public slots:
    void doNothing();
    void slot_stoppedDoNothing();
    void slot_stoppedWriting();
    void slot_boredToDeath();
};

#endif // PISARZ_H
