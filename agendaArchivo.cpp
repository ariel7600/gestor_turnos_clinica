#include "agendaArchivo.h"
#include "fecha.h"
#include <cstdio>
#include <cstring>
#include <ctime>

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

std::vector<Fecha> calcularProximasFechasDesdeHoy(int diaSemanaObjetivo, int cantidadSemanas) {
    std::vector<Fecha> listaFechas;

    time_t t = time(0); //fecha actual
    tm* now = localtime(&t);

    int anioActual = now->tm_year + 1900;
    int mesActual = now->tm_mon + 1;
    int diaActual = now->tm_mday;

    Fecha fechaIter(diaActual, mesActual, anioActual);

    int semanasEncontradas = 0;
    int diasBuscadosMaximo = cantidadSemanas * 7 + 7;
    int diasIterados = 0;


    while (semanasEncontradas < cantidadSemanas && diasIterados < diasBuscadosMaximo) {

       if (fechaIter.esDia(diaSemanaObjetivo)) {

            listaFechas.push_back(fechaIter);
            semanasEncontradas++;


            for (int i = 0; i < 6; ++i) {
                fechaIter.siguiente(); // Asumiendo que tenés un método para avanzar al día siguiente
                diasIterados++;
            }
        }

        fechaIter.siguiente();
        diasIterados++;
    }

    return listaFechas;
}

bool AgendaArchivo::generarDesdeHorario(const HorarioAtencion& horarioMed, int cantidadSemanas) {
    AgendaArchivo archivoAgenda("datos/agendas.dat");

    DiaSemana diaEnum = horarioMed.getDia();

    std::vector<Fecha> fechas = calcularProximasFechasDesdeHoy(static_cast<int>(diaEnum), cantidadSemanas);

    int ultimoId = 0;
    int cantRegistros = archivoAgenda.getCantidadRegistros();
    if (cantRegistros > 0) {
        ultimoId = archivoAgenda.leer(cantRegistros - 1).getIdAgenda();
    }

    int hInicio = horarioMed.getHorario().getHoraInicio();
    int mInicio = horarioMed.getHorario().getMinInicio();
    int hFin = horarioMed.getHorario().getHoraFin();
    int mFin = horarioMed.getHorario().getMinFin();

    int minutosActuales = (hInicio * 60) + mInicio;
    int minutosFinTotal = (hFin * 60) + mFin;

    int duracionMinutos = horarioMed.getDuracion();

    for (const Fecha& f : fechas) {
        int minutosSlot = minutosActuales;

        while (minutosSlot + duracionMinutos <= minutosFinTotal) {
            int hInicioSlot = minutosSlot / 60;
            int mInicioSlot = minutosSlot % 60;

            int minutosFinSlot = minutosSlot + duracionMinutos;
            int hFinSlot = minutosFinSlot / 60;
            int mFinSlot = minutosFinSlot % 60;


            HoraMin horaSlot(hInicioSlot, mInicioSlot, hFinSlot, mFinSlot);

            int posExistente = archivoAgenda.buscarPorMedicoFechaHora(horarioMed.getIdMedico(), f, horaSlot);

            if (posExistente == -1) {
                ultimoId++;
                Agenda nuevoSlot(ultimoId, horarioMed.getIdMedico(), f, horaSlot, true, true);

                if (!archivoAgenda.guardar(nuevoSlot)) {
                    return false;
                }
            }

            minutosSlot += duracionMinutos;
        }
    }

    return true;
}

int AgendaArchivo::getUltimoIdAg() {
    Agenda reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return 0;

    int maxId = 0;
    while (fread(&reg, sizeof(Agenda), 1, p)) {
        if (reg.getIdAgenda() > maxId) {
            maxId = reg.getIdAgenda();
        }
    }
    fclose(p);
    return maxId;
}
