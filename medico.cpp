#include "Medico.h"
using namespace std;
Medico::Medico() {
    idMedico = 0;
    matricula = 0;
    strcpy(nombreMedico, "");
    strcpy(apellidoMedico, "");
    strcpy(especialidad, "");
    strcpy(mail, "");
    strcpy(telefono, "");
    estado = false;
}

int Medico::getIdMedico() const { return idMedico; }
int Medico::getMatricula() const { return matricula; }
const char* Medico::getNombreMedico() const { return nombreMedico; }
const char* Medico::getApellidoMedico() const { return apellidoMedico; }
const char* Medico::getEspecialidad() const { return especialidad; }
const char* Medico::getMail() const { return mail; }
const char* Medico::getTelefono() const { return telefono; }
bool Medico::getEstado() const { return estado; }

void Medico::setIdMedico(int id) { idMedico = id; }
void Medico::setMatricula(int mat) { matricula = mat; }
void Medico::setNombreMedico(const char* nom) { strcpy(nombreMedico, nom); }
void Medico::setApellidoMedico(const char* ape) { strcpy(apellidoMedico, ape); }
void Medico::setEspecialidad(const char* esp) { strcpy(especialidad, esp); }
void Medico::setMail(const char* m) { strcpy(mail, m); }
void Medico::setTelefono(const char* tel) { strcpy(telefono, tel); }
void Medico::setEstado(bool est) { estado = est; }

void Medico::cargar() {
    cout << "ID Medico: "; cin >> idMedico;
    cout << "Matricula: "; cin >> matricula;
    cin.ignore();
    cout << "Nombre: "; cin.getline(nombreMedico, 50);
    cout << "Apellido: "; cin.getline(apellidoMedico, 50);
    cout << "Especialidad: "; cin.getline(especialidad, 20);
    cout << "Mail: "; cin.getline(mail, 50);
    cout << "Telefono: "; cin.getline(telefono, 20);
    estado = true;
}

void Medico::mostrar() const {
    if (estado) {
        cout << "ID: " << idMedico << endl;
        cout<<"Matricula: " << matricula<<endl;
        cout<< "Dr/a.:" << apellidoMedico << ", " << nombreMedico <<endl;
        cout<< "Especialidad: " << especialidad <<endl;
        cout<< "Tel: " << telefono <<endl;
        cout<< "--------------------------------------------------\n";
    }
}
