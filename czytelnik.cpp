#include "czytelnik.h"

#define CZAS_CZYTANIA 15000
#define KONIEC_CIERPLIWOSCI 60000

Czytelnik::Czytelnik(int id)
{
    this->chceCzytac = false;
    this->czyta = false;
    this->zawartosc = 0;
    this->ksiazka = 0;
    this->id = id;
}

Czytelnik::~Czytelnik()
{

}
int Czytelnik::getId() const
{
    return id;
}

void Czytelnik::setId(int value)
{
    id = value;
}

bool Czytelnik::getChceCzytac() const
{
    return chceCzytac;
}

void Czytelnik::setChceCzytac(bool value)
{
    chceCzytac = value;
}
bool Czytelnik::getCzyta() const
{
    return czyta;
}

void Czytelnik::setCzyta(bool value)
{
    czyta = value;
}
int Czytelnik::getKsiazka() const
{
    return ksiazka;
}

void Czytelnik::setKsiazka(int value)
{
    ksiazka = value;
}
int Czytelnik::getZawartosc() const
{
    return zawartosc;
}

void Czytelnik::setZawartosc(int value)
{
    zawartosc = value;
}






//===================================================================================



int Czytelnik::getCurrentTimeInSeconds()
{
    int result = (QTime::currentTime().hour() * 3600) + (QTime::currentTime().minute() * 60) + QTime::currentTime().second();

    return result;
}

void Czytelnik::doNothing()
{
    qDebug() << QString("Czytelnik ") + QString::number(this->id) + QString(" nic nie robi.");
    QTest::qSleep(getTimeOfDoNothing());

    qDebug() << QString("Czytelnik ") + QString::number(this->id) + QString(" chce coś przeczytać.");

    stoppedDoNothing();
}

int Czytelnik::getTimeOfDoNothing()
{
    int a = 2000;
    int b = 30000;
    int now = QTime::currentTime().msec() * this->id;
    qsrand(now);
    int result = (qrand() % (b - a)) + a;

    qDebug() << QString("Czytelnik ") + QString::number(this->id) + QString(" nie będzie nic robił przez ") + QString::number(result);

    return result;
}

void Czytelnik::startThread(){
    this->future = QtConcurrent::run(this,&Czytelnik::doNothing);
    watcher.setFuture(future);
}

void Czytelnik::slot_stoppedDoNothing()
{
    this->chceCzytac = true;
    qDebug() << QString("Czytelnik ") + QString::number(this->id) + QString(" chce czytać.");
    int currentTime = getCurrentTimeInSeconds();

    while (!this->czyta)
    {
        if (getCurrentTimeInSeconds() - currentTime < KONIEC_CIERPLIWOSCI)
            emit meWantsRead(this);
        else
        {
            emit boredToDeath();
            break;
        }
    }

    if (!this->czyta)
    {
        qDebug() << QString("Czytelnik ") + QString::number(this->id) + QString(" zaczyna czytać książkę o tytule ") + QString::number(this->ksiazka) + QString("o treści ") + QString::number(this->zawartosc);
        QTest::qSleep(CZAS_CZYTANIA);
        emit stoppedReading();
    }
}

void Czytelnik::slot_stoppedReading()
{
    this->chceCzytac = false;
    this->zawartosc = 0;
    this->ksiazka = 0;
    this->czyta = false;
    emit freeSlot();
    emit startDoNothingAgain();
}

void Czytelnik::slot_boredToDeath()
{
    qDebug() << QString("Czytelnik ") + QString::number(this->id) + QString(" zanudził się na śmierć.");
}



