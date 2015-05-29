#include "pisarz.h"

#define CZAS_PISANIA 15000
#define KONIEC_CIERPLIWOSCI 60000

Pisarz::Pisarz(int id)
{
    this->chcePisac = false;
    this->pisze = false;
    this->nowaZawartosc = 0;
    this->staraZawartosc = 0;
    this->ksiazka = 0;
    this->id = id;
}

Pisarz::~Pisarz()
{

}
int Pisarz::getId() const
{
    return id;
}

void Pisarz::setId(int value)
{
    id = value;
}
bool Pisarz::getChcePisac() const
{
    return chcePisac;
}

void Pisarz::setChcePisac(bool value)
{
    chcePisac = value;
}
bool Pisarz::getPisze() const
{
    return pisze;
}

void Pisarz::setPisze(bool value)
{
    pisze = value;
}
int Pisarz::getKsiazka() const
{
    return ksiazka;
}

void Pisarz::setKsiazka(int value)
{
    ksiazka = value;
}
int Pisarz::getNowaZawartosc() const
{
    return nowaZawartosc;
}

void Pisarz::setNowaZawartosc(int value)
{
    nowaZawartosc = value;
}
int Pisarz::getStaraZawartosc() const
{
    return staraZawartosc;
}

void Pisarz::setStaraZawartosc(int value)
{
    staraZawartosc = value;
}

//==================================================================


int Pisarz::getCurrentTimeInSeconds()
{
    int result = (QTime::currentTime().hour() * 3600) + (QTime::currentTime().minute() * 60) + QTime::currentTime().second();

    return result;
}

void Pisarz::doNothing()
{
    qDebug() << QString("Pisarz ") + QString::number(this->id) + QString(" nic nie robi.");
    QTest::qSleep(getTimeOfDoNothing());

    qDebug() << QString("Pisarz ") + QString::number(this->id) + QString(" chce coś napisać.");

    stoppedDoNothing();
}

int Pisarz::getTimeOfDoNothing()
{
    int a = 2000;
    int b = 30000;
    int now = QTime::currentTime().msec() * this->id;
    qsrand(now);
    int result = (qrand() % (b - a)) + a;

    qDebug() << QString("Pisarz ") + QString::number(this->id) + QString(" nie będzie nic robił przez ") + QString::number(result);

    return result;
}

void Pisarz::startThread(){
    this->future = QtConcurrent::run(this,&Pisarz::doNothing);
    watcher.setFuture(future);
}

void Pisarz::slot_stoppedDoNothing()
{
    this->chcePisac = true;
    qDebug() << QString("Pisarz ") + QString::number(this->id) + QString(" chce pisać.");
    int currentTime = getCurrentTimeInSeconds();

    while (!this->pisze)
    {
        if (getCurrentTimeInSeconds() - currentTime < KONIEC_CIERPLIWOSCI)
            emit meWantsWrite(this);
        else
        {
            qDebug() << "CHCE UMRZEC";
            emit boredToDeath();
            break;
        }
    }

    if (this->pisze)
    {
        qDebug() << QString("Pisarz ") + QString::number(this->id) + QString(" zmienia zawartość książki ") + QString::number(this->ksiazka) + QString("o zawartości ") + QString::number(this->staraZawartosc) + QString(" na nową zawartość ") + QString::number(this->nowaZawartosc);
        QTest::qSleep(CZAS_PISANIA);
        emit stoppedWriting();
    }
}

void Pisarz::slot_stoppedWriting()
{
    this->pisze = false;
    this->chcePisac = false;
    this->nowaZawartosc = 0;
    this->staraZawartosc;
    this->ksiazka = 0;
    emit freeSlot();
    emit startDoNothingAgain();
}

void Pisarz::slot_boredToDeath()
{
    qDebug() << QString("Pisarz ") + QString::number(this->id) + QString(" zanudził się na śmierć.");
}







