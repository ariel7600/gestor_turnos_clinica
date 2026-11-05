#ifndef HORARIOATENCION_H_INCLUDED
#define HORARIOATENCION_H_INCLUDED

#include <cstring>
#include <iostream>
#include "horaMin.h"
using namespace std;

class HorarioAtencion {
private:
    int idHorario;
    int idMedico;
    char dia[10];
    HoraMin horario; //composicion con horaMin
    int duracion;
    bool estado;

public:
    HorarioAtencion();

    // Getters
    int getIdHorario() const;
    int getIdMedico() const;
    const char* getDia() const; // pasar a enumerado
    HoraMin getHorario() const;
    int getDuracion() const;
    bool getEstado() const;

    // Setters
    void setIdHorario(int id);
    void setIdMedico(int idMed);
    void setDia(const char* d);
    void setHorario(HoraMin h);
    void setDuracion(int dur);
    void setEstado(bool est);

    void cargar();
    void mostrar() const;
};

#endif
