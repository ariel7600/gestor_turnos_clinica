#include "turnosArchivos.h"
#include <cstdio>
#include <cstring>

TurnoArchivo::TurnoArchivo(const char* n) {
    strcpy(nombreArchivo, n);
}

bool TurnoArchivo::guardar(Turno reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(Turno), 1, p);
    fclose(p);
    return escribio;
}

bool TurnoArchivo::guardar(Turno reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Turno), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Turno), 1, p);
    fclose(p);
    return escribio;
}

Turno TurnoArchivo::leer(int pos) {
    Turno reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(Turno), SEEK_SET);
    fread(&reg, sizeof(Turno), 1, p);
    fclose(p);
    return reg;
}

int TurnoArchivo::getCantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Turno);
    fclose(p);
    return cant;
}

int TurnoArchivo::buscarPorId(int idTurno) {
    Turno reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Turno), 1, p)) {
        if (reg.getIdTurno() == idTurno) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int TurnoArchivo::buscarPorAgenda(int idAgenda) {
    Turno reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Turno), 1, p)) {
        if (reg.getEstado() && reg.getIdAgenda() == idAgenda) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
