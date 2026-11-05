#ifndef HORAMINUTO_H_INCLUDED
#define HORAMINUTO_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class HoraMin {
private:
    int horaInicio;
    int minInicio;
    int horaFin;
    int minFin;

public:
    HoraMin();
    HoraMin(int hIni, int mIni, int hFin, int mFin);

    int getHoraInicio() const;
    int getMinInicio() const;
    int getHoraFin() const;
    int getMinFin() const;

    void setHoraInicio(int h);
    void setMinInicio(int m);
    void setHoraFin(int h);
    void setMinFin(int m);

    void cargar();
    void mostrar() const;
    string toString() const;
};

#endif
