#include "HorarioAtencion.h"

HorarioAtencion::HorarioAtencion() {
    idHorario = 0;
    idMedico = 0;
    strcpy(dia, "");
    horaInicio = 0;
    minInicio = 0;
    horaFin = 0;
    minFin = 0;
    duracion = 0;
    estado = false;
}

int HorarioAtencion::getIdHorario() const { return idHorario; }
int HorarioAtencion::getIdMedico() const { return idMedico; }
const char* HorarioAtencion::getDia() const { return dia; }
int HorarioAtencion::getHoraInicio() const { return horaInicio; }
int HorarioAtencion::getMinInicio() const { return minInicio; }
int HorarioAtencion::getHoraFin() const { return horaFin; }
int HorarioAtencion::getMinFin() const { return minFin; }
int HorarioAtencion::getDuracion() const { return duracion; }
bool HorarioAtencion::getEstado() const { return estado; }

void HorarioAtencion::setIdHorario(int id) { idHorario = id; }
void HorarioAtencion::setIdMedico(int idMed) { idMedico = idMed; }
void HorarioAtencion::setDia(const char* d) { strcpy(dia, d); }
void HorarioAtencion::setHoraInicio(int h) { horaInicio = h; }
void HorarioAtencion::setMinInicio(int m) { minInicio = m; }
void HorarioAtencion::setHoraFin(int h) { horaFin = h; }
void HorarioAtencion::setMinFin(int m) { minFin = m; }
void HorarioAtencion::setDuracion(int dur) { duracion = dur; }
void HorarioAtencion::setEstado(bool est) { estado = est; }

void HorarioAtencion::cargar() {
    cout << "ID Horario de Atencion: ";
    cin >> idHorario;
    cout << "ID Medico: ";
    cin >> idMedico;
    cin.ignore();
    cout << "Dia de la semana (ej. Lunes): ";
    cin.getline(dia, 10);
    cout << "Hora inicio (0-23): ";
    cin >> horaInicio;
    cout << "Minuto inicio (0-59): ";
    cin >> minInicio;
    cout << "Hora fin (0-23): ";
    cin >> horaFin;
    cout << "Minuto fin (0-59): ";
    cin >> minFin;
    cout << "Duracion estimada de cada turno (minutos): ";
    cin >> duracion;
    estado = true;
}

void HorarioAtencion::mostrar() const {
    if (estado) {
        cout<< "ID: " << idHorario << endl;
        cout<< "ID Medico: " << idMedico <<endl;
        cout<< "Dia:" << dia <<endl;
        cout<< "Horario: "<< (horaInicio < 10 ? "0" : "") << horaInicio << ":" << (minInicio < 10 ? "0" : "") << minInicio << " hs a "
        << (horaFin < 10 ? "0" : "") << horaFin << ":"<< (minFin < 10 ? "0" : "") << minFin <<endl;
        cout<< "Duracion del turno: " << duracion <<" min"<<endl;
        cout<< "--------------------------------------------------\n";

    }
}
