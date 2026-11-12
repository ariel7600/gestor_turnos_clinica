#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include <cstring>
#include <cctype>
#include <iostream>
#include "Fecha.h"
using namespace std;

class Persona {
protected:
    char nombre[50];
    char apellido[50];
    int dni;
    Fecha fechaNacimiento;
    char telefono[20];
    char mail[50];

public:
    Persona();

    // Getters
    const char* getNombre() const;
    const char* getApellido() const;
    int getDni() const;
    Fecha getFechaNacimiento() const;
    const char* getTelefono() const;
    const char* getMail() const;

    // Setters
    void setNombre(const char* nom);
    void setApellido(const char* ape);
    void setDni(int d);
    void setFechaNacimiento(Fecha f);
    void setTelefono(const char* tel);
    void setMail(const char* m);

    bool esTextoValido(const char* texto);
    bool validarTelefono(const char* tel);
    bool esMailValido(const string& mail);
    void cargar();
    void mostrar() const;
};

#endif
