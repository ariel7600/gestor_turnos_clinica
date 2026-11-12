#include "Especialidad.h"
#include "EspecialidadArchivo.h"

Especialidad::Especialidad() {
    idEspecialidad = 0;
    strcpy(nombreEspecialidad, "");
    strcpy(descripcion, "");
    estado = false;
}

int Especialidad::getIdEspecialidad() const { return idEspecialidad; }
const char* Especialidad::getNombreEspecialidad() const { return nombreEspecialidad; }
const char* Especialidad::getDescripcion() const { return descripcion; }
bool Especialidad::getEstado() const { return estado; }

void Especialidad::setIdEspecialidad(int id) { idEspecialidad = id; }
void Especialidad::setNombreEspecialidad(const char* nom) { strcpy(nombreEspecialidad, nom); }
void Especialidad::setDescripcion(const char* desc) { strcpy(descripcion, desc); }
void Especialidad::setEstado(bool est) { estado = est; }

string normalizarTexto(string texto) {  //normaliza textos
    string resultado = texto;
    for (char &c : resultado) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return resultado;
}

void Especialidad::cargar() {
    EspecialidadArchivo archivo("especialidad.dat");
    int maxID = archivo.getUltimoIdesp();
    int nuevoIdEspecialidad = maxID + 1;
    setIdEspecialidad(nuevoIdEspecialidad);
    cout << "ID Especialidad: " << nuevoIdEspecialidad << endl;
    bool nombreDuplicado=false;
    do{
        nombreDuplicado=false;
        cout << "Nombre de Especialidad: ";
        cin.getline(nombreEspecialidad, 30);
        string normNuevo = normalizarTexto(nombreEspecialidad);
        int cantEsp = archivo.getCantidadRegistros();
        for (int i = 0; i < cantEsp; i++) {
                Especialidad r = archivo.leer(i);
                if (normalizarTexto(r.getNombreEspecialidad()) == normNuevo) {
                    nombreDuplicado = true;
                    cout << "Error: La especialidad '" << r.getNombreEspecialidad() << "' ya existe (ID: " << r.getIdEspecialidad() << "). Ingrese otra diferente.\n";
                    break;
                }
        }
    } while (nombreDuplicado);
    cout << "Descripcion: ";
    cin.getline(descripcion, 100);
    setNombreEspecialidad(nombreEspecialidad); //se guarda en especialidad.dat
    setDescripcion(descripcion);
    setEstado(true);

    if (archivo.guardar(*this)) {
            cout << "Especialidad creada y guardada con exito.\n";
            idEspecialidad = nuevoIdEspecialidad;
    } else {
            cout << "Error al guardar la nueva especialidad.\n";
            idEspecialidad = 0;
     }
}

void Especialidad::mostrar() const {
    if (estado) {
        cout << "ID: " << idEspecialidad << " | Especialidad: " << nombreEspecialidad << "\n"
             << "Descripcion: " << descripcion << "\n"
             << "--------------------------------------------------\n";
    }
}
