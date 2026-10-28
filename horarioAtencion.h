#ifndef HORARIOATENCION_H_INCLUDED
#define HORARIOATENCION_H_INCLUDED

#include <cstring>
#include <iostream>
using namespace std;

class HorarioAtencion {
private:
    int idHorario;
    int idMedico;
    char dia[10];
    int horaInicio;
    int minInicio;
    int horaFin;
    int minFin;
    int duracion;
    bool estado;

public:
    HorarioAtencion();

    // Getters
    int getIdHorario() const;
    int getIdMedico() const;
    const char* getDia() const;
    int getHoraInicio() const;
    int getMinInicio() const;
    int getHoraFin() const;
    int getMinFin() const;
    int getDuracion() const;
    bool getEstado() const;

    // Setters
    void setIdHorario(int id);
    void setIdMedico(int idMed);
    void setDia(const char* d);
    void setHoraInicio(int h);
    void setMinInicio(int m);
    void setHoraFin(int h);
    void setMinFin(int m);
    void setDuracion(int dur);
    void setEstado(bool est);

    void cargar();
    void mostrar() const;
};

#endif // HORARIOATENCION_H_INCLUDED
