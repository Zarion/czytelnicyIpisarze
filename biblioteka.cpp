#include "biblioteka.h"

Biblioteka::Biblioteka()
{
    this->czytelnicy = 0;
    this->pisarze = 0;
    qDebug() << this->pisarze;
}

Biblioteka::Biblioteka(int liczbaKsiazek)
{
    qDebug() << this->pisarze;
    Biblioteka();
    qDebug() << this->pisarze;
    for ( int i = 0; i < liczbaKsiazek; i++ ){
        this->listaKsiazek << i;
    }

    qDebug() << this->pisarze;
}

Biblioteka::~Biblioteka()
{

}
int Biblioteka::getCzytelnicy() const
{
    return czytelnicy;
}

void Biblioteka::setCzytelnicy(int value)
{
    czytelnicy = value;
}
int Biblioteka::getPisarze() const
{
    return pisarze;
}

void Biblioteka::setPisarze(int value)
{
    pisarze = value;
}


//========================================================================

void Biblioteka::slot_freeSlotCzytelnik()
{
    this->czytelnicy -= 1;
}

void Biblioteka::slot_freeSlotPisarz()
{
    this->pisarze = 0;
}

void Biblioteka::slot_requestedSlotByPisarz(Pisarz *pisarz)
{
    requestSlotByPisarz(pisarz);
}

void Biblioteka::slot_requestedSlotByCzytelnik(Czytelnik *czytelnik)
{
    requestSlotByCzytelnik(czytelnik);
}

void Biblioteka::requestSlotByCzytelnik(Czytelnik *czytelnik)
{
    qDebug() << this->pisarze;
    if ( this->pisarze == 0 ){
        czytelnik->setCzyta(true);
        this->czytelnicy += 1;
        int book = randomBook(czytelnik->getId());
        czytelnik->setKsiazka(book+1);
        int wartosc = this->listaKsiazek[book];
        czytelnik->setZawartosc(wartosc);
    }
}

void Biblioteka::requestSlotByPisarz(Pisarz *pisarz)
{
    if ( this->czytelnicy == 0 && this->pisarze == 0 ){
        pisarz->setPisze(true);
        this->pisarze = 1;
        int book = randomBook(pisarz->getId());
        pisarz->setKsiazka(book+1);
        int wartosc = this->listaKsiazek[book];
        pisarz->setStaraZawartosc(wartosc);

        int now = QTime::currentTime().msec() * book;
        qsrand(now);
        wartosc = qrand() % (this->listaKsiazek.length()*10);
        this->listaKsiazek[book] = wartosc;
    }
}

int Biblioteka::randomBook(int id){
    int now = QTime::currentTime().msec() * id;
    qsrand(now);
    int result = qrand() % this->listaKsiazek.length();

    return result;
}






