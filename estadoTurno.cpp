#include "EstadoTurno.h"

EstadoTurno::EstadoTurno() {
    idEstadoTurno = 0;
    strcpy(estado, "");
    estadoRegistro = false;
}

int EstadoTurno::getIdEstadoTurno() const { return idEstadoTurno; }
const char* EstadoTurno::getEstado() const { return estado; }
bool EstadoTurno::getEstadoRegistro() const { return estadoRegistro; }

void EstadoTurno::setIdEstadoTurno(int id) { idEstadoTurno = id; }
void EstadoTurno::setEstado(const char* est) { strcpy(estado, est); }
void EstadoTurno::setEstadoRegistro(bool estReg) { estadoRegistro = estReg; }

void EstadoTurno::cargar() {
    cout << "ID Estado Turno: ";
    cin >> idEstadoTurno;
    cin.ignore();
    cout << "Nombre Estado (ej. Atendido): ";
    cin.getline(estado, 20);
    estadoRegistro = true;
}

void EstadoTurno::mostrar() const {
    if (estadoRegistro) {
        cout << "ID: " << idEstadoTurno << " | Estado: " << estado << "\n";
    }
}
