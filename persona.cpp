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

bool Persona::esTextoValido(const char* texto) {
    if (texto == nullptr || texto[0] == '\0') return false;
    for (int i = 0; texto[i] != '\0'; i++) {
        unsigned char c = static_cast<unsigned char>(texto[i]);
        if (!isalpha(c) && c != ' ' && c != 'ñ' && c != 'Ñ') {
            return false;
        }
    }
    return true;
}

bool Persona::validarTelefono(const char* tel) {
    for (int i = 0; i < strlen(tel); i++) {
        if (!isdigit((unsigned char) tel[i])) {
            return false;
        }
    }

    return true;
}

bool Persona::esMailValido(const string& mail) {

    if (mail.empty()) return false;

    if (mail.find(' ') != string::npos) return false; //no puede contener espacios

    size_t arroba = mail.find('@'); //debe contener un unico arroba

    if (arroba == string::npos) return false;

    if (mail.find('@', arroba + 1) != string::npos)
        return false;

    if (arroba == 0 || arroba == mail.length() - 1) //no puede comenzar ni terminar en arroba
        return false;

    // Buscar el punto despues del @
    size_t punto = mail.find('.', arroba + 1);

    if (punto == string::npos) return false;


    if (punto == arroba + 1) return false; //dominio no vacio

    // La extension no puede estar vacia
    if (punto == mail.length() - 1) return false;

    if (mail.find("..") != string::npos) return false; // no puede tener ..

    if (mail[arroba + 1] == '.' || mail.back() == '.') //no puede empezar o terminar con .
        return false;

    return true;
}

void Persona::cargar() {
    do {
        cout << "Nombre: ";
        cin.getline(nombre, 50);
        if (!esTextoValido(nombre)) {
            cout << "Error: El nombre solo debe contener letras y espacios.\n";
        } else {
            break;
        }
    } while (true);
    do {
        cout << "Apellido: ";
        cin.getline(apellido, 50);
        if (!esTextoValido(apellido)) {
            cout << "Error: El apellido solo debe contener letras y espacios.\n";
        } else {
            break;
        }
    } while (true);
    do {
        cout << "DNI (sin puntos): ";
        if (!(cin >> dni) || dni < 1000000 || dni > 99999999) {
            cout << "Error: DNI invalido.\n";
            cin.clear();
            cin.ignore();
        } else {
            cin.ignore();
            break;
        }
    } while (true);
    do{
        cout << "Fecha de Nacimiento:\n"; fechaNacimiento.cargar();
        cin.ignore();
        int anio=fechaNacimiento.getAnio();
        if(anio>2026){
            cout<<"Error: año ingresado invalido. \n";
        } else {
            break;
        }
    } while (true);
    do {
        cout << "Telefono (sin guiones ni signos): ";
        cin.getline(telefono, 20);
        if (!validarTelefono(telefono)){
            cout<<"Error: Debe ingresar solo numeros sin signos. \n";
            continue;
        } else if (strlen(telefono)<6){
            cout<<"Error: Telefono con pocos digitos. \n";
        } else {
            break;
        }
    } while (true);
    do {
        cout << "Mail: ";
        cin.getline(mail, 50);
        if (!esMailValido(mail)) {
            cout << "Error: Formato del mail invalido.\n";
        } else {
            break;
        }
    } while (true);
}

void Persona::mostrar() const {
    cout << "Nombre completo: " << apellido << ", " << nombre << "\n"
              << "DNI: " << dni << " | Nacimiento: " << fechaNacimiento.toString() << "\n"
              << "Tel: " << telefono << " | Mail: " << mail << "\n";
}
