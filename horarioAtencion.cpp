#include "HorarioAtencion.h"

HorarioAtencion::HorarioAtencion() {
    idHorario = 0;
    idMedico = 0;
    strcpy(dia, "");
    duracion = 0;
    estado = false;
}

int HorarioAtencion::getIdHorario() const { return idHorario; }
int HorarioAtencion::getIdMedico() const { return idMedico; }
const char* HorarioAtencion::getDia() const { return dia; }
HoraMin HorarioAtencion::getHorario() const { return horario; }
int HorarioAtencion::getDuracion() const { return duracion; }
bool HorarioAtencion::getEstado() const { return estado; }

void HorarioAtencion::setIdHorario(int id) { idHorario = id; }
void HorarioAtencion::setIdMedico(int idMed) { idMedico = idMed; }
void HorarioAtencion::setDia(const char* d) { strcpy(dia, d); }
void HorarioAtencion::setHorario(HoraMin h) { horario = h; }
void HorarioAtencion::setDuracion(int dur) { duracion = dur; }
void HorarioAtencion::setEstado(bool est) { estado = est; }

void HorarioAtencion::cargar() {
    cout << "ID Horario de Atencion: \n ";
    cin >> idHorario;
    cout << "ID Medico: ";
    cin >> idMedico;
    cin.ignore();
    cout << "Dia de la semana (ej. Lunes): ";
    cin.getline(dia, 10);
    cout << "Rango horario de atencion:\n";
    horario.cargar();
    cout << "Duracion estimada de cada turno (minutos): ";
    cin >> duracion;
    estado = true;
}

void HorarioAtencion::mostrar() const {
    if (estado) {
        cout<< "ID: " << idHorario << endl;
        cout<< "ID Medico: " << idMedico <<endl;
        cout<< "Dia:" << dia <<endl;
        cout<< "Horario: " << horario.toString() << "\n";
        cout<< "Duracion del turno: " << duracion <<" min"<<endl;
        cout<< "--------------------------------------------------\n";

    }
}
