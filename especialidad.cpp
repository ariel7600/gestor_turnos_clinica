#include "Especialidad.h"

Especialidad::Especialidad() {
    idEspecialidad = 0;
    strcpy(nombreEspecialidad, "");
    strcpy(descripcion, "");
    estado = false;
}

int Especialidad::getIdEspecialidad() const { return idEspecialidad; }
const char* Especialidad::getNombreEspecialidad() const { return nombreEspecialidad; }
const char* Especialidad::getDescripcion() const { return descripcion; }
bool Especialidad::getEstado() const { return estado; }

void Especialidad::setIdEspecialidad(int id) { idEspecialidad = id; }
void Especialidad::setNombreEspecialidad(const char* nom) { strcpy(nombreEspecialidad, nom); }
void Especialidad::setDescripcion(const char* desc) { strcpy(descripcion, desc); }
void Especialidad::setEstado(bool est) { estado = est; }

void Especialidad::cargar() {
    cout << "ID Especialidad: "; cin >> idEspecialidad;
    cin.ignore();
    cout << "Nombre de Especialidad: "; cin.getline(nombreEspecialidad, 30);
    cout << "Descripcion: "; cin.getline(descripcion, 100);
    estado = true;
}

void Especialidad::mostrar() const {
    if (estado) {
        cout << "ID: " << idEspecialidad << " | Especialidad: " << nombreEspecialidad << "\n"
             << "Descripcion: " << descripcion << "\n"
             << "--------------------------------------------------\n";
    }
}
