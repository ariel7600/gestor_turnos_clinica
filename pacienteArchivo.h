#ifndef PACIENTEARCHIVO_H_INCLUDED
#define PACIENTEARCHIVO_H_INCLUDED

#include "Paciente.h"

class PacienteArchivo {
private:
    char nombreArchivo[50];

public:
    PacienteArchivo(const char* n = "paciente.dat");

    bool guardar(Paciente reg);
    bool guardar(Paciente reg, int pos);
    Paciente leer(int pos);
    int getCantidadRegistros();
    int buscarPorId(int idPaciente);
    int buscarPorDni(int dni);
};

#endif // PACIENTEARCHIVO_H_INCLUDED
