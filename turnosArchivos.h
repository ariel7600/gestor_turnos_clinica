#ifndef TURNOARCHIVOS_H_INCLUDED
#define TURNOARCHIVOS_H_INCLUDED

#include "turnos.h"

class TurnoArchivo {
private:
    char nombreArchivo[50];

public:
    TurnoArchivo(const char* n = "turno.dat");

    bool guardar(Turno reg);
    bool guardar(Turno reg, int pos);
    Turno leer(int pos);
    int getCantidadRegistros();
    int buscarPorId(int idTurno);
    int buscarPorAgenda(int idAgenda);
};

#endif
