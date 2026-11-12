#include "Medico.h"
#include "MedicoArchivo.h"
#include "Especialidad.h"
#include "EspecialidadArchivo.h"

Medico::Medico() : Persona() {
    idMedico = 0;
    matricula = 0;
    idEspecialidad = 0;
    estado = false;
}

int Medico::getIdMedico() const { return idMedico; }
int Medico::getMatricula() const { return matricula; }
int Medico::getIdEspecialidad() const { return idEspecialidad; }
bool Medico::getEstado() const { return estado; }

void Medico::setIdMedico(int id) { idMedico = id; }
void Medico::setMatricula(int mat) { matricula = mat; }
void Medico::setIdEspecialidad(int idEsp) { idEspecialidad = idEsp; }
void Medico::setEstado(bool est) { estado = est; }

void Medico::cargar() {
    MedicoArchivo arch("medico.dat");
    int ultimoId = arch.getUltimoId();
    idMedico = ultimoId + 1;
    cout << "ID Medico asignado automaticamente: " << idMedico << endl; //id autoincremental
    do {
        cout << "Matricula: ";
        if (!(cin >> matricula) || matricula <= 0) {
            cout << "Error: Ingrese un numero positivo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else if (arch.existeMatricula(matricula)) {
            cout << "Error: La matricula ya fue registrada con anterioridad.\n";
            matricula = 0;
            continue;
        } else {
            cin.ignore();
            break;
        }
    } while (true);
    EspecialidadArchivo espArch("especialidad.dat");
    int cantEsp = espArch.getCantidadRegistros();

    cout << "\n--------------------------------------------------" << endl;
    cout << "           ESPECIALIDADES DISPONIBLES             " << endl;
    cout << "--------------------------------------------------" << endl;
    if (cantEsp == 0) {
        cout << "No hay especialidades registradas actualmente" << endl;
    } else {
        for (int i = 0; i < cantEsp; i++) {
            Especialidad regEsp = espArch.leer(i);
            cout << "ID: " << regEsp.getIdEspecialidad() << " | Nombre: " << regEsp.getNombreEspecialidad() << endl;
        }
    }
    cout << "--------------------------------------------------" << endl;
    cout << "Ingrese el ID de la especialidad " << endl;
    cout << "o ingrese 0 para crear una NUEVA especialidad. ";
    int opcionEsp;
    int pos = 0;
    while (!(cin >> opcionEsp) || opcionEsp < 0) {
        pos=espArch.buscarPorId(opcionEsp);
        if (pos <=0){
            cout<<"Id ya existente."<<endl;
            continue;
        }
        cout << "Opcion invalida. Reintente: ";
        cin.clear();
        cin.ignore();
    }
    cin.ignore();
    if (opcionEsp == 0){
        Especialidad esp;
        esp.cargar();
        idEspecialidad=esp.getIdEspecialidad();
    } else {
        idEspecialidad = opcionEsp;
        cout << "Especialidad seleccionada correctamente.\n";
    }
    cin.ignore();
    Persona::cargar();
    estado = true;
}

void Medico::mostrar() const {
    if (estado) {
        cout << "ID Medico: " << idMedico << " | Matricula: " << matricula
                  << " | ID Especialidad: " << idEspecialidad << "\n";
        Persona::mostrar();
        cout << "--------------------------------------------------\n";
    }
}
