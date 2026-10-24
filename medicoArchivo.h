#ifndef MEDICOARCHIVO_H_INCLUDED
#define MEDICOARCHIVO_H_INCLUDED
#include "Medico.h"

class MedicoArchivo {
private:
    char nombreArchivo[50];

public:
    MedicoArchivo(const char* ruta = "medico.dat");

    bool guardar(Medico reg);             // Agrega nuevo medico
    bool guardar(Medico reg, int pos);    // Sobrescribe en una posición (para bajas o modificaciones)
    Medico leer(int pos);
    int getCantidadRegistros();
    int buscarPorId(int idMedico);
};

#endif // MEDICOARCHIVO_H_INCLUDED


