#include "MedicoArchivo.h"
#include <cstdio>
#include <cstring>

MedicoArchivo::MedicoArchivo(const char* ruta) {
    strcpy(nombreArchivo, ruta);
}

bool MedicoArchivo::guardar(Medico reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool resultado = fwrite(&reg, sizeof(Medico), 1, p);
    fclose(p);
    return resultado;
}

bool MedicoArchivo::guardar(Medico reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Medico), SEEK_SET);
    bool resultado = fwrite(&reg, sizeof(Medico), 1, p);
    fclose(p);
    return resultado;
}

Medico MedicoArchivo::leer(int pos) {
    Medico reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(Medico), SEEK_SET);
    fread(&reg, sizeof(Medico), 1, p);
    fclose(p);
    return reg;
}

int MedicoArchivo::getCantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Medico);
    fclose(p);
    return cant;
}

int MedicoArchivo::buscarPorId(int idMedico) {
    Medico reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Medico), 1, p)) {
        if (reg.getIdMedico() == idMedico) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
