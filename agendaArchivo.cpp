#include "agendaArchivo.h"
#include <cstdio>
#include <cstring>

AgendaArchivo::AgendaArchivo(const char* n) {
    strcpy(nombreArchivo, n);
}

bool AgendaArchivo::guardar(Agenda reg) {
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(Agenda), 1, p);
    fclose(p);
    return escribio;
}

bool AgendaArchivo::guardar(Agenda reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Agenda), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Agenda), 1, p);
    fclose(p);
    return escribio;
}

Agenda AgendaArchivo::leer(int pos) {
    Agenda reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(Agenda), SEEK_SET);
    fread(&reg, sizeof(Agenda), 1, p);
    fclose(p);
    return reg;
}

int AgendaArchivo::getCantidadRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Agenda);
    fclose(p);
    return cant;
}

int AgendaArchivo::buscarPorId(int idAgenda) {
    Agenda reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Agenda), 1, p)) {
        if (reg.getIdAgenda() == idAgenda) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int AgendaArchivo::buscarPorMedicoFechaHora(int idMedico, Fecha f, HoraMin h) {
    Agenda reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return -1;

    int pos = 0;
    while (fread(&reg, sizeof(Agenda), 1, p)) {
        if (reg.getEstado() &&
            reg.getIdMedico() == idMedico &&
            reg.getFecha() == f &&
            reg.getHorario().getHoraInicio() == h.getHoraInicio() &&
            reg.getHorario().getMinInicio() == h.getMinInicio()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}
