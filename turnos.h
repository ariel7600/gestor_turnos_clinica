#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED

#include <cstring>
#include <iostream>
#include "estadoTurno.h"
using namespace std;

class Turno {
private:
    int idTurno;
    int idPaciente;
    int idAgenda;
    char motivo[50];
    char observacionPrevia[50];
    float costoConsulta;
    EstadoTurno estadoTurno;
    bool estado;

public:
    Turno();

    // Getters
    int getIdTurno() const;
    int getIdPaciente() const;
    int getIdAgenda() const;
    const char* getMotivo() const;
    const char* getObservacionPrevia() const;
    float getCostoConsulta() const;
    EstadoTurno getEstadoTurno() const;
    bool getEstado() const;

    // Setters
    void setIdTurno(int id);
    void setIdPaciente(int idPac);
    void setIdAgenda(int idAg);
    void setMotivo(const char* m);
    void setObservacionPrevia(const char* obs);
    void setCostoConsulta(float costo);
    void setEstadoTurno(EstadoTurno estado);
    void setEstado(bool est);
    //Metodos
    void cargar();
    void mostrar() const;
};

#endif
