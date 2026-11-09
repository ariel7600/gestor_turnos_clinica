#include "turnos.h"

Turno::Turno() {
    idTurno = 0;
    idPaciente = 0;
    idAgenda = 0;
    strcpy(motivo, "");
    strcpy(observacionPrevia, "");
    costoConsulta = 0.0f;
    estadoTurno = EstadoTurno::ASIGNADO;
    estado = false;
}

int Turno::getIdTurno() const { return idTurno; }
int Turno::getIdPaciente() const { return idPaciente; }
int Turno::getIdAgenda() const { return idAgenda; }
const char* Turno::getMotivo() const { return motivo; }
const char* Turno::getObservacionPrevia() const { return observacionPrevia; }
float Turno::getCostoConsulta() const { return costoConsulta; }
EstadoTurno Turno::getEstadoTurno() const { return estadoTurno;}
bool Turno::getEstado() const { return estado; }

void Turno::setIdTurno(int id) { idTurno = id; }
void Turno::setIdPaciente(int idPac) { idPaciente = idPac; }
void Turno::setIdAgenda(int idAg) { idAgenda = idAg; }
void Turno::setMotivo(const char* m) { strcpy(motivo, m); }
void Turno::setObservacionPrevia(const char* obs) { strcpy(observacionPrevia, obs); }
void Turno::setCostoConsulta(float costo) { costoConsulta = costo; }
void Turno::setEstadoTurno(EstadoTurno estado) { estadoTurno = estado; }
void Turno::setEstado(bool est) { estado = est; }

const char* estadoTurnoTexto(EstadoTurno estado) {
    switch (estado) {
        case EstadoTurno::ASIGNADO:
            return "Asignado";
        case EstadoTurno::ATENDIDO:
            return "Atendido";
        case EstadoTurno::CANCELADO:
            return "Cancelado";
        case EstadoTurno::AUSENTE:
            return "Ausente";
        default:
            return "Desconocido";
    }
}


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
    cout << "Estado Turno (1: Asignado, 2: Atendido, 3: Cancelado, 4: Ausente): ";
    int opcion=0;
    cin >> opcion;

    switch (opcion) {
        case 1:
            estadoTurno = EstadoTurno::ASIGNADO;
            break;

        case 2:
            estadoTurno = EstadoTurno::ATENDIDO;
            break;

        case 3:
            estadoTurno = EstadoTurno::CANCELADO;
            break;

        case 4:
            estadoTurno = EstadoTurno::AUSENTE;
            break;

        default:
            cout << "Opcion invalida. Se asignara el estado ASIGNADO.\n";
            estadoTurno = EstadoTurno::ASIGNADO;
            break;
        }
    estado = true;
}

void Turno::mostrar() const {
    if (estado) {
        cout << "ID Turno: " << idTurno << " | ID Paciente: " << idPaciente
                  << " | ID Agenda: " << idAgenda << "\n"
                  << "Motivo: " << motivo << "\n"
                  << "Observacion previa: " << observacionPrevia << "\n"
                  << "Costo: $" << costoConsulta << "| " << "Estado: "
                  << estadoTurnoTexto(estadoTurno) << "\n"
                  << "--------------------------------------------------\n";
    }
}
