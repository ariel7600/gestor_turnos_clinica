#include "Paciente.h"
using namespace std;
Paciente::Paciente() {
    idPaciente = 0;
    strcpy(nombrePaciente, "");
    strcpy(apellidoPaciente, "");
    dni = 0;
    strcpy(obraSocial, "");
    numAfiliado = 0;
    telefono = 0;
    strcpy(mail, "");
    estado = false;
}

int Paciente::getIdPaciente() const { return idPaciente; }
const char* Paciente::getNombrePaciente() const { return nombrePaciente; }
const char* Paciente::getApellidoPaciente() const { return apellidoPaciente; }
int Paciente::getDni() const { return dni; }
const char* Paciente::getObraSocial() const { return obraSocial; }
int Paciente::getNumAfiliado() const { return numAfiliado; }
Fecha Paciente::getFechaNacimiento() const { return fechaNacimiento; }
int Paciente::getTelefono() const { return telefono; }
const char* Paciente::getMail() const { return mail; }
bool Paciente::getEstado() const { return estado; }

void Paciente::setIdPaciente(int id) { idPaciente = id; }
void Paciente::setNombrePaciente(const char* nom) { strcpy(nombrePaciente, nom); }
void Paciente::setApellidoPaciente(const char* ape) { strcpy(apellidoPaciente, ape); }
void Paciente::setDni(int d) { dni = d; }
void Paciente::setObraSocial(const char* os) { strcpy(obraSocial, os); }
void Paciente::setNumAfiliado(int num) { numAfiliado = num; }
void Paciente::setFechaNacimiento(Fecha f) { fechaNacimiento = f; }
void Paciente::setTelefono(int tel) { telefono = tel; }
void Paciente::setMail(const char* m) { strcpy(mail, m); }
void Paciente::setEstado(bool est) { estado = est; }

void Paciente::cargar() {
    cout << "ID Paciente: ";
    cin >> idPaciente;
    cin.ignore();
    cout << "Nombre: ";
    cin.getline(nombrePaciente, 50);
    cout << "Apellido: ";
    cin.getline(apellidoPaciente, 50);
    cout << "DNI: ";
    cin >> dni;
    cin.ignore();
    cout << "Obra Social: ";
    cin.getline(obraSocial, 20);
    cout << "Numero de Afiliado: ";
    cin >> numAfiliado;
    cout << "Fecha de Nacimiento:\n";
    fechaNacimiento.cargar();
    cout << "Telefono: ";
    cin >> telefono;
    cin.ignore();
    cout << "Mail: ";
    cin.getline(mail, 50);
    estado = true;
}

void Paciente::mostrar() const {
    if (estado) {
        cout << "ID: " << idPaciente << endl;
        cout<<"DNI: " << dni <<endl;
        cout<< "Paciente:" << apellidoPaciente << ", " << nombrePaciente <<endl;
        cout<< "Obra Social: " << obraSocial <<endl;
        cout<< "N° Afiliado: " << numAfiliado <<endl;
        cout<< "Fecha Nacimiento: "<< fechaNacimiento.getDia() <<"/" << fechaNacimiento.getMes() << "/" << fechaNacimiento.getAnio() << endl;
        cout<< "Tel: "<< telefono <<endl;
        cout<< "Mail: "<< mail <<endl;
        cout<< "--------------------------------------------------\n";
    }
}
