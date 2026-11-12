#include "HorarioAtencion.h"
#include "diaSemana.h"

HorarioAtencion::HorarioAtencion() {
    idHorario = 0;
    idMedico = 0;
    dia = DiaSemana::LUNES;
    duracion = 0;
    estado = false;
}

int HorarioAtencion::getIdHorario() const { return idHorario; }
int HorarioAtencion::getIdMedico() const { return idMedico; }
DiaSemana HorarioAtencion::getDia() const { return dia; }
HoraMin HorarioAtencion::getHorario() const { return horario; }
int HorarioAtencion::getDuracion() const { return duracion; }
bool HorarioAtencion::getEstado() const { return estado; }

void HorarioAtencion::setIdHorario(int id) { idHorario = id; }
void HorarioAtencion::setIdMedico(int idMed) { idMedico = idMed; }
void HorarioAtencion::setDia(DiaSemana d) { dia = d; }
void HorarioAtencion::setHorario(HoraMin h) { horario = h; }
void HorarioAtencion::setDuracion(int dur) { duracion = dur; }
void HorarioAtencion::setEstado(bool est) { estado = est; }

const char* HorarioAtencion::diaSemanaTexto(DiaSemana dia) const {
    switch (dia) {
        case DiaSemana::LUNES:
            return "Lunes";
        case DiaSemana::MARTES:
            return "Martes";
        case DiaSemana::MIERCOLES:
            return "Miercoles";
        case DiaSemana::JUEVES:
            return "Jueves";
        case DiaSemana::VIERNES:
            return "Viernes";
        case DiaSemana::SABADO:
            return "Sabado";
        case DiaSemana::DOMINGO:
            return "Domingo";
        default:
            return "Desconocido";
    }
}

void HorarioAtencion::cargar() {
    cout << "ID Medico: ";
    cin >> idMedico;
    cin.ignore();
    int opcion;
    do {
        cout << "\nSeleccione el dia:\n";
        cout << "1-Lunes, 2- Martes, 3- Miercoles, 4- Jueves \n";
        cout << "5-Viernes, 6-Sabado, 7-Domingo. \n";
        cout << "Opcion: ";
        cin >> opcion;
        if (opcion < 1 || opcion > 7) {
            cout << "Opcion invalida.\n";
        }

    } while (opcion < 1 || opcion > 7);
    dia = static_cast<DiaSemana>(opcion);
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
        cout << "Dia: " << diaSemanaTexto(dia) << "\n";
        cout<< "Horario: " << horario.toString() << "\n";
        cout<< "Duracion del turno: " << duracion <<" min"<<endl;
        cout<< "--------------------------------------------------\n";

    }
}
