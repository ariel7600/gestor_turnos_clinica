#include "historialArchivo.h"
#include <cstdio>
#include <cstring>

HistorialArchivo::HistorialArchivo(const char* n) {
    strcpy(nombreArchivo, n);
}

bool HistorialArchivo::guardar(HistorialMedico reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(HistorialMedico), 1, p);
    fclose(p);
    return escribio;
}

bool HistorialArchivo::guardar(HistorialMedico reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(HistorialMedico), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(HistorialMedico), 1, p);
    fclose(p);
    return escribio;
}

HistorialMedico HistorialArchivo::leer(int pos) {
    HistorialMedico reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(HistorialMedico), SEEK_SET);
    fread(&reg, sizeof(HistorialMedico), 1, p);
    fclose(p);
    return reg;
}

int HistorialArchivo::getCantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(HistorialMedico);
    fclose(p);
    return cant;
}

int HistorialArchivo::buscarPorId(int idHistorial) {
    HistorialMedico reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(HistorialMedico), 1, p)) {
        if (reg.getIdHistorial() == idHistorial) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
