#include "Paciente.h"
#include "pacienteArchivo.h"

Paciente::Paciente() : Persona() {
    idPaciente = 0;
    strcpy(obraSocial, "");
    numAfiliado = 0;
    estado = false;
}

int Paciente::getIdPaciente() const { return idPaciente; }
const char* Paciente::getObraSocial() const { return obraSocial; }
int Paciente::getNumAfiliado() const { return numAfiliado; }
bool Paciente::getEstado() const { return estado; }

void Paciente::setIdPaciente(int id) { idPaciente = id; }
void Paciente::setObraSocial(const char* os) { strcpy(obraSocial, os); }
void Paciente::setNumAfiliado(int num) { numAfiliado = num; }
void Paciente::setEstado(bool est) { estado = est; }

void Paciente::cargar() {
    PacienteArchivo arch("datos/pacientes.dat");
    int ultimoId = arch.getUltimoId();
    idPaciente = ultimoId + 1;
    cout << "ID Paciente asignado automaticamente: " << idPaciente << endl; //id autoincremental
    Persona::cargar();
    do {
        cout << "Obra Social (Escribe el nombre sin puntos ni otros signos, ej: OSDE): ";
        cin.getline(obraSocial, 20);

        if (obraSocial[0] == '\0') {
            cout << "Error: La obra social no puede estar vacia. Reintente.\n";
        } else {
            //normalizo todo en mayusculas
            for (int i = 0; obraSocial[i] != '\0'; i++) {
                obraSocial[i] = toupper(obraSocial[i]);
            }
            break;
        }
    } while (true);
    do {
        cout << "Numero de Afiliado (Ingresa solo numeros, sin guiones ni barras): ";
        if (!(cin >> numAfiliado) || numAfiliado <= 0) {
            cout << "Error: Formato invalido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    } while (true);
    estado = true;
    cout << "--> Paciente cargado con exito!\n";
}

void Paciente::mostrar() const {
    if (estado) {
        std::cout << "ID Paciente: " << idPaciente << "\n";
        Persona::mostrar();
        std::cout << "Obra Social: " << obraSocial << " (Num Afiliado: " << numAfiliado << ")\n"
                  << "--------------------------------------------------\n";
    }
}


