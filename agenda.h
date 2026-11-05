#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

#include <iostream>
#include "fecha.h"
#include "horaMin.h"
using namespace std;

class Agenda {
private:
    int idAgenda;
    int idMedico;
    Fecha fecha;
    HoraMin horario;
    bool disponibilidad; // true: libre, false: ocupado
    bool estado;         // baja lógica

public:
    Agenda();
    Agenda(int idAg, int idMed, Fecha f, HoraMin h, bool disp = true, bool est = true);

    // Getters
    int getIdAgenda() const;
    int getIdMedico() const;
    Fecha getFecha() const;
    HoraMin getHorario() const;
    bool getDisponibilidad() const;
    bool getEstado() const;

    // Setters
    void setIdAgenda(int idAg);
    void setIdMedico(int idMed);
    void setFecha(Fecha f);
    void setHorario(HoraMin h);
    void setDisponibilidad(bool disp);
    void setEstado(bool est);


    void cargar();
    void mostrar() const;
};

#endif
