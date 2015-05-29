#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H

#include "pisarz.h"
#include "czytelnik.h"

#include <QObject>
#include <QList>
#include <QDebug>

namespace Ui
{
    class Biblioteka;
}

class Biblioteka : public QObject
{
    Q_OBJECT
public:
    Biblioteka(int liczbaKsiazek);
    ~Biblioteka();
    int getCzytelnicy() const;
    void setCzytelnicy(int value);

    int getPisarze() const;
    void setPisarze(int value);


    void requestSlotByPisarz(Pisarz *pisarz);
    void requestSlotByCzytelnik(Czytelnik *czytelnik);

private:
    QList<int> *listaKsiazek;
    int czytelnicy;
    int pisarze;

    int randomBook(int id);

signals:
    void showPisarze();
    void showCzytelnicy();

public slots:
    void slot_freeSlotCzytelnik();
    void slot_freeSlotPisarz();
    void slot_requestedSlotByPisarz(Pisarz *pisarz);
    void slot_requestedSlotByCzytelnik(Czytelnik *czytelnik);
};

#endif // BIBLIOTEKA_H
