#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED
#include <cstring>
#include <iostream>
#include "Fecha.h"

class Paciente {
private:
    int idPaciente;
    char nombrePaciente[50];
    char apellidoPaciente[50];
    int dni;
    char obraSocial[20];
    int numAfiliado;
    Fecha fechaNacimiento;
    int telefono;
    char mail[50];
    bool estado;

public:
    Paciente();

    // Getters
    int getIdPaciente() const;
    const char* getNombrePaciente() const;
    const char* getApellidoPaciente() const;
    int getDni() const;
    const char* getObraSocial() const;
    int getNumAfiliado() const;
    Fecha getFechaNacimiento() const;
    int getTelefono() const;
    const char* getMail() const;
    bool getEstado() const;

    // Setters
    void setIdPaciente(int id);
    void setNombrePaciente(const char* nom);
    void setApellidoPaciente(const char* ape);
    void setDni(int d);
    void setObraSocial(const char* os);
    void setNumAfiliado(int num);
    void setFechaNacimiento(Fecha f);
    void setTelefono(int tel);
    void setMail(const char* m);
    void setEstado(bool est);


    void cargar();
    void mostrar() const;
};

#endif // PACIENTE_H_INCLUDED
