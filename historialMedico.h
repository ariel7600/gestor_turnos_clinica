#ifndef HISTORIALMEDICO_H_INCLUDED
#define HISTORIALMEDICO_H_INCLUDED

#include <cstring>
#include <iostream>
#include "Fecha.h"
using namespace std;

class HistorialMedico {
private:
    int idHistorial;
    int idPaciente;
    Fecha fechaHistorial;
    char diagnostico[150];
    char tratamiento[150];
    char anotacionMedica[150];
    bool estado;

public:
    HistorialMedico();

    // Getters
    int getIdHistorial() const;
    int getIdPaciente() const;
    Fecha getFechaHistorial() const;
    const char* getDiagnostico() const;
    const char* getTratamiento() const;
    const char* getAnotacionMedica() const;
    bool getEstado() const;

    // Setters
    void setIdHistorial(int id);
    void setIdPaciente(int idPac);
    void setFechaHistorial(Fecha f);
    void setDiagnostico(const char* diag);
    void setTratamiento(const char* trat);
    void setAnotacionMedica(const char* anot);
    void setEstado(bool est);

    // Métodos
    void cargar();
    void mostrar() const;
};

#endif
