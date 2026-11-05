#include "Medico.h"

Medico::Medico() : Persona() {
    idMedico = 0;
    matricula = 0;
    idEspecialidad = 0;
    estado = false;
}

int Medico::getIdMedico() const { return idMedico; }
int Medico::getMatricula() const { return matricula; }
int Medico::getIdEspecialidad() const { return idEspecialidad; }
bool Medico::getEstado() const { return estado; }

void Medico::setIdMedico(int id) { idMedico = id; }
void Medico::setMatricula(int mat) { matricula = mat; }
void Medico::setIdEspecialidad(int idEsp) { idEspecialidad = idEsp; }
void Medico::setEstado(bool est) { estado = est; }

void Medico::cargar() {
    cout << "ID Medico: ";
    cin >> idMedico;
    cout << "Matricula: ";
    cin >> matricula;
    cout << "ID Especialidad: ";
    cin >> idEspecialidad;
    cin.ignore();
    Persona::cargar();
    estado = true;
}

void Medico::mostrar() const {
    if (estado) {
        cout << "ID Medico: " << idMedico << " | Matricula: " << matricula
                  << " | ID Especialidad: " << idEspecialidad << "\n";
        Persona::mostrar();
        cout << "--------------------------------------------------\n";
    }
}
