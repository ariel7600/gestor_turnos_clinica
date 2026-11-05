#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED

#include "Persona.h"

class Paciente : public Persona {
private:
    int idPaciente;
    char obraSocial[20];
    int numAfiliado;
    bool estado;

public:
    Paciente();

    int getIdPaciente() const;
    const char* getObraSocial() const;
    int getNumAfiliado() const;
    bool getEstado() const;

    void setIdPaciente(int id);
    void setObraSocial(const char* os);
    void setNumAfiliado(int num);
    void setEstado(bool est);

    void cargar();
    void mostrar() const;
};

#endif
