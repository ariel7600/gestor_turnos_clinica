#ifndef HORARIOATENCIONARCHIVO_H_INCLUDED
#define HORARIOATENCIONARCHIVO_H_INCLUDED

#include "HorarioAtencion.h"

class HorarioAtencionArchivo {
private:
    char nombreArchivo[50];

public:
    HorarioAtencionArchivo(const char* n = "horarioAtencion.dat");

    bool guardar(HorarioAtencion reg);
    bool guardar(HorarioAtencion reg, int pos);
    HorarioAtencion leer(int pos);
    int getCantidadRegistros();
    int buscarPorId(int idHorario);
};

#endif // HORARIOATENCIONARCHIVO_H_INCLUDED
