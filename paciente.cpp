#include "Paciente.h"

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
    std::cout << "ID Paciente: "; std::cin >> idPaciente;
    std::cin.ignore();
    Persona::cargar(); // Reutiliza la carga de datos personales
    std::cout << "Obra Social: "; std::cin.getline(obraSocial, 20);
    std::cout << "Numero de Afiliado: "; std::cin >> numAfiliado;
    estado = true;
}

void Paciente::mostrar() const {
    if (estado) {
        std::cout << "ID Paciente: " << idPaciente << "\n";
        Persona::mostrar();
        std::cout << "Obra Social: " << obraSocial << " (Nº Afiliado: " << numAfiliado << ")\n"
                  << "--------------------------------------------------\n";
    }
}


