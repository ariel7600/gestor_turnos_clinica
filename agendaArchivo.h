#ifndef AGENDAARCHIVO_H_INCLUDED
#define AGENDAARCHIVO_H_INCLUDED

#include "agenda.h"
#include "HorarioAtencion.h"

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
    int getUltimoIdAg();
    int buscarPorMedicoFechaHora(int idMedico, Fecha f, HoraMin h);
    static bool generarDesdeHorario(const HorarioAtencion& horarioMed, int cantidadSemanas = 2);
};

#endif
