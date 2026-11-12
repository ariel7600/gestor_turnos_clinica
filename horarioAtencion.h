#ifndef HORARIOATENCION_H_INCLUDED
#define HORARIOATENCION_H_INCLUDED

#include <cstring>
#include <iostream>
#include "horaMin.h"
#include "diaSemana.h"
using namespace std;

class HorarioAtencion {
private:
    int idHorario;
    int idMedico;
    DiaSemana dia;
    HoraMin horario; //composicion con horaMin
    int duracion;
    bool estado;

public:
    HorarioAtencion();

    // Getters
    int getIdHorario() const;
    int getIdMedico() const;
    DiaSemana getDia() const;
    HoraMin getHorario() const;
    int getDuracion() const;
    bool getEstado() const;

    // Setters
    void setIdHorario(int id);
    void setIdMedico(int idMed);
    void setDia(DiaSemana d);
    void setHorario(HoraMin h);
    void setDuracion(int dur);
    void setEstado(bool est);

    const char* diaSemanaTexto(DiaSemana dia) const ;
    void cargar();
    void mostrar() const;
};

#endif
