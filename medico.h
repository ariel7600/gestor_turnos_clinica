#ifndef MEDICO_H_INCLUDED
#define MEDICO_H_INCLUDED
#include "Persona.h"
#include <limits>


using namespace std;

class Medico : public Persona {
private:
    int idMedico;
    int matricula;
    int idEspecialidad;
    bool estado;

public:
    Medico();

    int getIdMedico() const;
    int getMatricula() const;
    int getIdEspecialidad() const;
    bool getEstado() const;

    void setIdMedico(int id);
    void setMatricula(int mat);
    void setIdEspecialidad(int idEsp);
    void setEstado(bool est);
    void cargar();
    void mostrar() const;
};

#endif
