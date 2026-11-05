#ifndef HISTORIALARCHIVO_H_INCLUDED
#define HISTORIALARCHIVO_H_INCLUDED

#include "historialMedico.h"

class HistorialArchivo {
private:
    char nombreArchivo[50];

public:
    HistorialArchivo(const char* n = "historialMedico.dat");

    bool guardar(HistorialMedico reg);
    bool guardar(HistorialMedico reg, int pos);
    HistorialMedico leer(int pos);
    int getCantidadRegistros();
    int buscarPorId(int idHistorial);
};

#endif
