#ifndef ESTADOTURNO_H_INCLUDED
#define ESTADOTURNO_H_INCLUDED

#include <cstring>
#include <iostream>
using namespace std;

class EstadoTurno {
private:
    int idEstadoTurno;
    char estado[20]; // "Asignado", "Atendido", "Cancelado", "Ausente"
    bool estadoRegistro;

public:
    EstadoTurno();

    int getIdEstadoTurno() const;
    const char* getEstado() const;
    bool getEstadoRegistro() const;

    void setIdEstadoTurno(int id);
    void setEstado(const char* est);
    void setEstadoRegistro(bool estReg);

    void cargar();
    void mostrar() const;
};

#endif
