#include "turnos.h"
#include "turnosArchivos.h"
#include "agendaArchivo.h"
#include "pacienteArchivo.h"
#include "medicoArchivo.h"
#include <iomanip>
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
    TurnoArchivo arch("datos/turnos.dat");
    int ultimoId = arch.getUltimoId();
    idTurno = ultimoId + 1;
    cout << "=== NUEVO TURNO (ID Asignado: " << idTurno << ") ===" << endl;

    PacienteArchivo pacArch("datos/pacientes.dat");
    bool pacienteEncontrado = false;

    do {
        int opcionBusqueda;
        cout << "\nComo desea buscar al paciente?\n";
        cout << "1. Ingresar ID de Paciente\n";
        cout << "2. Buscar por DNI\n";
        cout << "Opcion: ";
        cin >> opcionBusqueda;

        if (opcionBusqueda == 1) {
            cout << "Ingrese el ID del paciente: ";
            if (!(cin >> idPaciente)) {
                cout << "Entrada invalida.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            int pos = pacArch.buscarPorId(idPaciente);
            if (pos >= 0) {
                Paciente p = pacArch.leer(pos);
                if (p.getEstado()) {
                    cout << "--> Paciente seleccionado: " << p.getApellido() << ", " << p.getNombre() << " (OS: " << p.getObraSocial() << ")\n";
                    pacienteEncontrado = true;
                } else {
                    cout << "Error: El paciente se encuentra dado de baja.\n";
                }
            } else {
                cout << "No existe un paciente con ese ID.\n";
            }
        } else if (opcionBusqueda == 2) {
            int dniBuscado;
            cout << "Ingrese el DNI del paciente: ";
            if (!(cin >> dniBuscado)) {
                cout << "Entrada invalida.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            int cantPac = pacArch.getCantidadRegistros();
            for (int i = 0; i < cantPac; i++) {
                Paciente p = pacArch.leer(i);
                if (p.getDni() == dniBuscado && p.getEstado()) {
                    idPaciente = p.getIdPaciente();
                    cout << "--> Paciente encontrado: " << p.getApellido() << ", " << p.getNombre() << " (ID: " << idPaciente << ")\n";
                    pacienteEncontrado = true;
                    break;
                }
            }
            if (!pacienteEncontrado) {
                cout << "No se encontro un paciente activo con ese DNI.\n";
            }
        } else {
            cout << "Opcion invalida.\n";
        }
    } while (!pacienteEncontrado);

    AgendaArchivo agArch("datos/agendas.dat");
    MedicoArchivo medArch("datos/medico.dat");
    bool agendaSeleccionada = false;

    do {
        int matriculaBuscada;
        cout << "\n--- BUSQUEDA DE AGENDAS DISPONIBLES ---" << endl;
        cout << "Ingrese la matricula del medico: ";
        if (!(cin >> matriculaBuscada)) {
            cout << "Entrada invalida.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        int idMedEncontrado = -1;
        int cantMed = medArch.getCantidadRegistros();
        for (int i = 0; i < cantMed; i++) {
            Medico m = medArch.leer(i);
            if (m.getMatricula() == matriculaBuscada && m.getEstado()) {
                idMedEncontrado = m.getIdMedico();
                cout << "--> Medico: Dr/a. " << m.getApellido() << ", " << m.getNombre() << endl;
                break;
            }
        }

        if (idMedEncontrado == -1) {
            cout << "No se encontro un medico activo con esa matricula. Intente nuevamente.\n";
            continue;
        }

       cout << "\n" << string(62, '=') << endl;
        cout << "           AGENDAS DISPONIBLES DEL MEDICO" << endl;
        cout << string(62, '=') << endl;
        cout << left << setw(10) << "ID"
        << setw(14) << "FECHA"
        << setw(22) << "HORARIO"
        << right << setw(12) << "ESTADO" << endl;
        cout << string(62, '-') << endl;

        int cantAgendas = agArch.getCantidadRegistros();
        int agendasMostradas = 0;

        for (int i = 0; i < cantAgendas; i++) {
            Agenda ag = agArch.leer(i);
            if (ag.getIdMedico() == idMedEncontrado && ag.getEstado()) {
                string horarioStr = ag.getHorario().toString();
                string estadoStr = ag.getDisponibilidad() ? "Disponible" : "Ocupado";
                cout << left << setw(12) << ag.getIdAgenda()
                     << setw(15) << ag.getFecha().toString()
                     << right << setw(20) << horarioStr
                     << right << setw(15) << estadoStr << endl;
                agendasMostradas++;
            }
        }
        cout << string(52, '-') << endl;

        if (agendasMostradas == 0) {
            cout << "El medico no posee agendas disponibles actualmente.\n";
            char respuesta;
            cout << "Desea buscar otro medico? (S/N): ";
            cin >> respuesta;
            if (toupper(respuesta) != 'S') break;
            continue;
        }

        cout << "Ingrese el ID de la agenda elegida: ";
        if (!(cin >> idAgenda)) {
            cout << "Entrada invalida.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        int posAg = agArch.buscarPorId(idAgenda);
        if (posAg >= 0) {
            Agenda agElegida = agArch.leer(posAg);
            if (agElegida.getIdMedico() == idMedEncontrado && agElegida.getEstado() && agElegida.getDisponibilidad()) {
                agendaSeleccionada = true;

                agElegida.setDisponibilidad(false);
                agArch.guardar(agElegida, posAg);
            } else {
                cout << "El ID de agenda ingresado no es valido, no esta disponible o no corresponde al medico.\n";
            }
        } else {
            cout << "No existe una agenda con ese ID.\n";
        }

    } while (!agendaSeleccionada);

    cin.ignore();
    cout << "\nMotivo de la consulta: ";
    cin.getline(motivo, 50);
    cout << "Observacion previa: ";
    cin.getline(observacionPrevia, 50);

    do {
        cout << "Costo de la consulta: $";
        if (!(cin >> costoConsulta)) {
            cout << "Error: Debe ingresar un valor numerico valido.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            costoConsulta = -1;
        } else if (costoConsulta <= 0) {
            cout << "Error: El costo debe ser mayor a cero.\n";
        }
    } while (costoConsulta <= 0);

    // Por defecto al crear un turno nuevo queda ASIGNADO
    estadoTurno = EstadoTurno::ASIGNADO;
    cout << "Estado de turno: asignado\n";

    estado = true;
    cout << "¡Turno registrado con exito!\n";
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
