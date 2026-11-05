#ifndef ESPECIALIDAD_H_INCLUDED
#define ESPECIALIDAD_H_INCLUDED

#include <cstring>
#include <iostream>
using namespace std;

class Especialidad {
private:
    int idEspecialidad;
    char nombreEspecialidad[30];
    char descripcion[100];
    bool estado;

public:
    Especialidad();

    int getIdEspecialidad() const;
    const char* getNombreEspecialidad() const;
    const char* getDescripcion() const;
    bool getEstado() const;

    void setIdEspecialidad(int id);
    void setNombreEspecialidad(const char* nom);
    void setDescripcion(const char* desc);
    void setEstado(bool est);

    void cargar();
    void mostrar() const;
};

#endif
