#ifndef ESPECIALIDADARCHIVO_H_INCLUDED
#define ESPECIALIDADARCHIVO_H_INCLUDED

#include "especialidad.h"

class EspecialidadArchivo {
private:
    char nombreArchivo[50];

public:
    EspecialidadArchivo(const char* n = "especialidad.dat");

    bool guardar(Especialidad reg);
    bool guardar(Especialidad reg, int pos);
    Especialidad leer(int pos);
    int getCantidadRegistros();
    int buscarPorId(int idEspecialidad);
};

#endif
