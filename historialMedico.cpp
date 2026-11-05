#include "historialMedico.h"

HistorialMedico::HistorialMedico() {
    idHistorial = 0;
    idPaciente = 0;
    strcpy(diagnostico, "");
    strcpy(tratamiento, "");
    strcpy(anotacionMedica, "");
    estado = false;
}

int HistorialMedico::getIdHistorial() const { return idHistorial; }
int HistorialMedico::getIdPaciente() const { return idPaciente; }
Fecha HistorialMedico::getFechaHistorial() const { return fechaHistorial; }
const char* HistorialMedico::getDiagnostico() const { return diagnostico; }
const char* HistorialMedico::getTratamiento() const { return tratamiento; }
const char* HistorialMedico::getAnotacionMedica() const { return anotacionMedica; }
bool HistorialMedico::getEstado() const { return estado; }

void HistorialMedico::setIdHistorial(int id) { idHistorial = id; }
void HistorialMedico::setIdPaciente(int idPac) { idPaciente = idPac; }
void HistorialMedico::setFechaHistorial(Fecha f) { fechaHistorial = f; }
void HistorialMedico::setDiagnostico(const char* diag) { strcpy(diagnostico, diag); }
void HistorialMedico::setTratamiento(const char* trat) { strcpy(tratamiento, trat); }
void HistorialMedico::setAnotacionMedica(const char* anot) { strcpy(anotacionMedica, anot); }
void HistorialMedico::setEstado(bool est) { estado = est; }

void HistorialMedico::cargar() {
    cout << "ID Historial: ";
    cin >> idHistorial;
    cout << "ID Paciente: ";
    cin >> idPaciente;
    cout << "Fecha del registro clinico:\n";
    fechaHistorial.cargar();
    cin.ignore();
    cout << "Diagnostico: ";
    cin.getline(diagnostico, 150);
    cout << "Tratamiento: ";
    cin.getline(tratamiento, 150);
    cout << "Anotaciones medicas: ";
    cin.getline(anotacionMedica, 150);
    estado = true;
}

void HistorialMedico::mostrar() const {
    if (estado) {
        cout << "ID Historial: " << idHistorial << " | ID Paciente: " << idPaciente << "\n"
                  << "Fecha: " << fechaHistorial.toString() << "\n"
                  << "Diagnostico: " << diagnostico << "\n"
                  << "Tratamiento: " << tratamiento << "\n"
                  << "Anotacion Medica: " << anotacionMedica << "\n"
                  << "--------------------------------------------------\n";
    }
}
