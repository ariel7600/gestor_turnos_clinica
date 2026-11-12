#include "especialidadArchivo.h"
#include <cstdio>
#include <cstring>

EspecialidadArchivo::EspecialidadArchivo(const char* n) {
    strcpy(nombreArchivo, n);
}

bool EspecialidadArchivo::guardar(Especialidad reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(Especialidad), 1, p);
    fclose(p);
    return escribio;
}

bool EspecialidadArchivo::guardar(Especialidad reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Especialidad), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Especialidad), 1, p);
    fclose(p);
    return escribio;
}

Especialidad EspecialidadArchivo::leer(int pos) {
    Especialidad reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(Especialidad), SEEK_SET);
    fread(&reg, sizeof(Especialidad), 1, p);
    fclose(p);
    return reg;
}

int EspecialidadArchivo::getCantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Especialidad);
    fclose(p);
    return cant;
}

int EspecialidadArchivo::buscarPorId(int idEspecialidad) {
    Especialidad reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Especialidad), 1, p)) {
        if (reg.getIdEspecialidad() == idEspecialidad) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int EspecialidadArchivo::getUltimoIdesp() {
    Especialidad reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0; // Si no existe el archivo el 1er ID será 1 por defecto

    int maxId = 0;
    while (fread(&reg, sizeof(Especialidad), 1, p)) {
        if (reg.getIdEspecialidad() > maxId) {
            maxId = reg.getIdEspecialidad();
        }
    }
    fclose(p);
    return maxId;
}
