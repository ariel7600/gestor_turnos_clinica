#include "Persona.h"

Persona::Persona() {
    strcpy(nombre, "");
    strcpy(apellido, "");
    dni = 0;
    strcpy(telefono, "");
    strcpy(mail, "");
}

const char* Persona::getNombre() const { return nombre; }
const char* Persona::getApellido() const { return apellido; }
int Persona::getDni() const { return dni; }
Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }
const char* Persona::getTelefono() const { return telefono; }
const char* Persona::getMail() const { return mail; }

void Persona::setNombre(const char* nom) { strcpy(nombre, nom); }
void Persona::setApellido(const char* ape) { strcpy(apellido, ape); }
void Persona::setDni(int d) { dni = d; }
void Persona::setFechaNacimiento(Fecha f) { fechaNacimiento = f; }
void Persona::setTelefono(const char* tel) { strcpy(telefono, tel); }
void Persona::setMail(const char* m) { strcpy(mail, m); }

void Persona::cargar() {
    cout << "Nombre: "; cin.getline(nombre, 50);
    cout << "Apellido: "; cin.getline(apellido, 50);
    cout << "DNI: "; cin >> dni;
    cout << "Fecha de Nacimiento:\n"; fechaNacimiento.cargar();
    cin.ignore();
    cout << "Telefono: "; cin.getline(telefono, 20);
    cout << "Mail: "; cin.getline(mail, 50);
}

void Persona::mostrar() const {
    cout << "Nombre completo: " << apellido << ", " << nombre << "\n"
              << "DNI: " << dni << " | Nacimiento: " << fechaNacimiento.toString() << "\n"
              << "Tel: " << telefono << " | Mail: " << mail << "\n";
}
