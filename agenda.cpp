#include "Agenda.h"

Agenda::Agenda() {
    idAgenda = 0;
    idMedico = 0;
    disponibilidad = true;
    estado = false;
}

Agenda::Agenda(int idAg, int idMed, Fecha f, HoraMin h, bool disp, bool est)
    : idAgenda(idAg), idMedico(idMed), fecha(f), horario(h), disponibilidad(disp), estado(est) {}

int Agenda::getIdAgenda() const { return idAgenda; }
int Agenda::getIdMedico() const { return idMedico; }
Fecha Agenda::getFecha() const { return fecha; }
HoraMin Agenda::getHorario() const { return horario; }
bool Agenda::getDisponibilidad() const { return disponibilidad; }
bool Agenda::getEstado() const { return estado; }

void Agenda::setIdAgenda(int idAg) { idAgenda = idAg; }
void Agenda::setIdMedico(int idMed) { idMedico = idMed; }
void Agenda::setFecha(Fecha f) { fecha = f; }
void Agenda::setHorario(HoraMin h) { horario = h; }
void Agenda::setDisponibilidad(bool disp) { disponibilidad = disp; }
void Agenda::setEstado(bool est) { estado = est; }

void Agenda::cargar() {
    cout << "ID Agenda: ";
    cin >> idAgenda;
    cout << "ID Medico: ";
    cin >> idMedico;
    cout << "Fecha del turno en agenda:\n";
    fecha.cargar();
    cout << "Horario del turno:\n";
    horario.cargar();
    disponibilidad = true;
    estado = true;
}

void Agenda::mostrar() const {
    if (estado) {
        cout << "ID Agenda: " << idAgenda << " | ID Medico: " << idMedico << "\n"
             << "Fecha: " << fecha.toString() << "\n"
             << "Horario: " << horario.toString() << "\n"
             << "Estado turno: " << (disponibilidad ? "Disponible (Libre)" : "Ocupado (Asignado)") << "\n"
             << "--------------------------------------------------\n";
    }
}
