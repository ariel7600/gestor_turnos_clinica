#include "PacienteArchivo.h"
#include <cstdio>
#include <cstring>

PacienteArchivo::PacienteArchivo(const char* n) {
    strcpy(nombreArchivo, n);
}

bool PacienteArchivo::guardar(Paciente reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(Paciente), 1, p);
    fclose(p);
    return escribio;
}

bool PacienteArchivo::guardar(Paciente reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Paciente), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Paciente), 1, p);
    fclose(p);
    return escribio;
}

Paciente PacienteArchivo::leer(int pos) {
    Paciente reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(Paciente), SEEK_SET);
    fread(&reg, sizeof(Paciente), 1, p);
    fclose(p);
    return reg;
}

int PacienteArchivo::getCantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Paciente);
    fclose(p);
    return cant;
}

int PacienteArchivo::buscarPorId(int idPaciente) {
    Paciente reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Paciente), 1, p)) {
        if (reg.getIdPaciente() == idPaciente) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int PacienteArchivo::buscarPorDni(int dni) {
    Paciente reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Paciente), 1, p)) {
        if (reg.getDni() == dni) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
