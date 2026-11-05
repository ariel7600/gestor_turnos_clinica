#include "turnos.h"

Turno::Turno() {
    idTurno = 0;
    idPaciente = 0;
    idAgenda = 0;
    strcpy(motivo, "");
    strcpy(observacionPrevia, "");
    costoConsulta = 0.0f;
    idEstadoTurno = 1;
    estado = false;
}

int Turno::getIdTurno() const { return idTurno; }
int Turno::getIdPaciente() const { return idPaciente; }
int Turno::getIdAgenda() const { return idAgenda; }
const char* Turno::getMotivo() const { return motivo; }
const char* Turno::getObservacionPrevia() const { return observacionPrevia; }
float Turno::getCostoConsulta() const { return costoConsulta; }
int Turno::getIdEstadoTurno() const { return idEstadoTurno; }
bool Turno::getEstado() const { return estado; }

void Turno::setIdTurno(int id) { idTurno = id; }
void Turno::setIdPaciente(int idPac) { idPaciente = idPac; }
void Turno::setIdAgenda(int idAg) { idAgenda = idAg; }
void Turno::setMotivo(const char* m) { strcpy(motivo, m); }
void Turno::setObservacionPrevia(const char* obs) { strcpy(observacionPrevia, obs); }
void Turno::setCostoConsulta(float costo) { costoConsulta = costo; }
void Turno::setIdEstadoTurno(int idEst) { idEstadoTurno = idEst; }
void Turno::setEstado(bool est) { estado = est; }

void Turno::cargar() {
    cout << "ID Turno: ";
    cin >> idTurno;
    cout << "ID Paciente: ";
    cin >> idPaciente;
    cout << "ID Agenda: ";
    cin >> idAgenda;
    cin.ignore();
    cout << "Motivo de la consulta: ";
    cin.getline(motivo, 50);
    cout << "Observacion previa: ";
    cin.getline(observacionPrevia, 50);
    cout << "Costo de la consulta: $";
    cin >> costoConsulta;
    cout << "ID Estado Turno (1: Asignado, 2: Atendido, 3: Cancelado, 4: Ausente): ";
    cin >> idEstadoTurno;
    estado = true;
}

void Turno::mostrar() const {
    if (estado) {
        cout << "ID Turno: " << idTurno << " | ID Paciente: " << idPaciente
                  << " | ID Agenda: " << idAgenda << "\n"
                  << "Motivo: " << motivo << "\n"
                  << "Observacion previa: " << observacionPrevia << "\n"
                  << "Costo: $" << costoConsulta << " | ID Estado: " << idEstadoTurno << "\n"
                  << "--------------------------------------------------\n";
    }
}
