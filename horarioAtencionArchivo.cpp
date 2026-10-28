#include "HorarioAtencionArchivo.h"
#include <cstdio>
#include <cstring>

HorarioAtencionArchivo::HorarioAtencionArchivo(const char* n) {
    strcpy(nombreArchivo, n);
}

bool HorarioAtencionArchivo::guardar(HorarioAtencion reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(HorarioAtencion), 1, p);
    fclose(p);
    return escribio;
}

bool HorarioAtencionArchivo::guardar(HorarioAtencion reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(HorarioAtencion), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(HorarioAtencion), 1, p);
    fclose(p);
    return escribio;
}

HorarioAtencion HorarioAtencionArchivo::leer(int pos) {
    HorarioAtencion reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(HorarioAtencion), SEEK_SET);
    fread(&reg, sizeof(HorarioAtencion), 1, p);
    fclose(p);
    return reg;
}

int HorarioAtencionArchivo::getCantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(HorarioAtencion);
    fclose(p);
    return cant;
}

int HorarioAtencionArchivo::buscarPorId(int idHorario) {
    HorarioAtencion reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(HorarioAtencion), 1, p)) {
        if (reg.getIdHorario() == idHorario) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
