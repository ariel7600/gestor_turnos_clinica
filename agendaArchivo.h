#ifndef AGENDAARCHIVO_H_INCLUDED
#define AGENDAARCHIVO_H_INCLUDED

#include "agenda.h"

class AgendaArchivo {
private:
    char nombreArchivo[50];

public:
    AgendaArchivo(const char* n = "agenda.dat");

    bool guardar(Agenda reg);
    bool guardar(Agenda reg, int pos);
    Agenda leer(int pos);
    int getCantidadRegistros();
    int buscarPorId(int idAgenda);

    int buscarPorMedicoFechaHora(int idMedico, Fecha f, HoraMin h);
};

#endif
