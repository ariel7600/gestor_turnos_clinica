#ifndef MEDICO_H_INCLUDED
#define MEDICO_H_INCLUDED
#include <cstring>
#include <iostream>

class Medico {
private:
    int idMedico;
    int matricula;
    char nombreMedico[50];
    char apellidoMedico[50];
    char especialidad[20];
    char mail[50];
    char telefono[20];
    bool estado;

public:
    Medico();

    // Getters
    int getIdMedico() const;
    int getMatricula() const;
    const char* getNombreMedico() const;
    const char* getApellidoMedico() const;
    const char* getEspecialidad() const;
    const char* getMail() const;
    const char* getTelefono() const;
    bool getEstado() const;

    // Setters
    void setIdMedico(int id);
    void setMatricula(int mat);
    void setNombreMedico(const char* nom);
    void setApellidoMedico(const char* ape);
    void setEspecialidad(const char* esp);
    void setMail(const char* m);
    void setTelefono(const char* tel);
    void setEstado(bool est);

    // Métodos
    void cargar();
    void mostrar() const;
};

#endif // MEDICO_H_INCLUDED
