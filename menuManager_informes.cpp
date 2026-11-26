#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include "MenuManager.h"
#include "medico.h"
#include "medicoArchivo.h"
#include "agenda.h"
#include "agendaArchivo.h"
#include "paciente.h"
#include "pacienteArchivo.h"
#include "turnos.h"
#include "turnosArchivos.h"
#include "estadoTurno.h"
#include "especialidadArchivo.h"
#include "MenuManager.h"

using namespace std;

void porcentajeFmt(int parte, int total) {
    double p = (total > 0) ? (100.0 * parte / total) : 0.0;
    cout << setw(10) << fixed << setprecision(1) << p << "%"; //muestra solo 1 decimal
}

void informeRecaudacionMes() {
    system("cls");
    cout << "=== RECAUDACION POR MES ===" << endl;
    TurnoArchivo tArch("datos/turnos.dat");
    AgendaArchivo aArch("datos/agendas.dat");

    int cant = tArch.getCantidadRegistros();
    if (cant <= 0) {
        cout << "No hay turnos registrados." << endl;
        system("pause");
        return;
    }

    int anio;
    cout << "Ingrese el anio a consultar (ej. 2026): ";
    cin >> anio;

    float rec[12] = {0};
    float total = 0;

    for (int i = 0; i < cant; i++) {
        Turno t = tArch.leer(i);
        if (t.getEstado() && t.getEstadoTurno() == EstadoTurno::ATENDIDO) {
            int posAg = aArch.buscarPorId(t.getIdAgenda());
            if (posAg >= 0) {
                Agenda ag = aArch.leer(posAg);
                int mes = ag.getFecha().getMes();
                if (ag.getFecha().getAnio() == anio && mes >= 1 && mes <= 12) {
                    rec[mes - 1] += t.getCostoConsulta();
                    total += t.getCostoConsulta();
                }
            }
        }
    }

    string meses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                      "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    cout << "\n" << string(40, '=') << endl;
    cout << "      RECAUDACION POR MES - " << anio << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(20) << "MES" << right << setw(18) << "RECAUDACION" << endl;
    cout << string(40, '-') << endl;
    cout << fixed << setprecision(2);
    for (int m = 0; m < 12; m++) {
        cout << left << setw(20) << meses[m] << right << "$" << setw(17) << rec[m] << endl;
    }
    cout << string(40, '-') << endl;
    cout << left << setw(20) << "TOTAL" << right << "$" << setw(17) << total << endl;
    cout << string(40, '=') << endl;

    system("pause");
}

void informeRecaudacionMedico() {
    system("cls");
    cout << "=== RECAUDACION POR MEDICO ===" << endl;
    TurnoArchivo tArch("datos/turnos.dat");
    AgendaArchivo aArch("datos/agendas.dat");
    MedicoArchivo mArch("datos/medico.dat");

    int cantTurnos = tArch.getCantidadRegistros();
    int cantMedicos = mArch.getCantidadRegistros();

    if (cantTurnos <= 0 || cantMedicos <= 0) {
        cout << "No hay suficientes datos registrados para generar el informe." << endl;
        system("pause");
        return;
    }

    float* rec = new float[cantMedicos]();
    float total = 0;

    for (int i = 0; i < cantTurnos; i++) {
        Turno t = tArch.leer(i);
        if (t.getEstado() && t.getEstadoTurno() == EstadoTurno::ATENDIDO) {
            int posAg = aArch.buscarPorId(t.getIdAgenda());
            if (posAg >= 0) {
                Agenda ag = aArch.leer(posAg);
                int posMed = mArch.buscarPorId(ag.getIdMedico());
                if (posMed >= 0) {
                    rec[posMed] += t.getCostoConsulta();
                    total += t.getCostoConsulta();
                }
            }
        }
    }

    cout << "\n" << string(60, '=') << endl;
    cout << "      RECAUDACION POR MEDICO (turnos atendidos)" << endl;
    cout << string(60, '=') << endl;
    cout << left << setw(8) << "ID" << setw(32) << "MEDICO" << right << setw(18) << "RECAUDACION" << endl;
    cout << string(60, '-') << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < cantMedicos; i++) {
        Medico med = mArch.leer(i);
        string nombre = string(med.getApellido()) + ", " + med.getNombre();
        cout << left << setw(8) << med.getIdMedico() << setw(32) << nombre
             << right << "$" << setw(17) << rec[i] << endl;
    }
    cout << string(60, '-') << endl;
    cout << left << setw(40) << "TOTAL" << right << "$" << setw(17) << total << endl;
    cout << string(60, '=') << endl;

    delete[] rec;
    system("pause");
}

void informeTurnosEspecialidad() {
    system("cls");
    cout << "=== CANTIDAD DE TURNOS POR ESPECIALIDAD ===" << endl;
    TurnoArchivo tArch("datos/turnos.dat");
    AgendaArchivo aArch("datos/agendas.dat");
    MedicoArchivo mArch("datos/medico.dat");
    EspecialidadArchivo eArch("datos/especialidad.dat");

    int cantTurnos = tArch.getCantidadRegistros();
    int cantEsp = eArch.getCantidadRegistros();

    if (cantTurnos <= 0) {
        cout << "No hay turnos registrados." << endl;
        system("pause");
        return;
    }
    if (cantEsp <= 0) {
        cout << "No hay especialidades registradas." << endl;
        system("pause");
        return;
    }

    int* cont = new int[cantEsp]();
    int total = 0;

    for (int i = 0; i < cantTurnos; i++) {
        Turno t = tArch.leer(i);
        if (!t.getEstado()) continue;

        int posAg = aArch.buscarPorId(t.getIdAgenda());
        if (posAg < 0) continue;
        Agenda ag = aArch.leer(posAg);

        int posMed = mArch.buscarPorId(ag.getIdMedico());
        if (posMed < 0) continue;
        Medico med = mArch.leer(posMed);

        int posEsp = eArch.buscarPorId(med.getIdEspecialidad());
        if (posEsp >= 0) {
            cont[posEsp]++;
            total++;
        }
    }

    cout << "\n" << string(55, '=') << endl;
    cout << "      CANTIDAD DE TURNOS POR ESPECIALIDAD" << endl;
    cout << string(55, '=') << endl;
    cout << left << setw(25) << "ESPECIALIDAD" << right << setw(10) << "CANTIDAD"
         << setw(14) << "PORCENTAJE" << endl;
    cout << string(55, '-') << endl;
    for (int i = 0; i < cantEsp; i++) {
        Especialidad esp = eArch.leer(i);
        cout << left << setw(25) << esp.getNombreEspecialidad()
             << right << setw(10) << cont[i];
        porcentajeFmt(cont[i], total);
        cout << endl;
    }
    cout << string(55, '-') << endl;
    cout << left << setw(25) << "TOTAL" << right << setw(10) << total;
    porcentajeFmt(total, total);
    cout << endl << string(55, '=') << endl;

    delete[] cont;
    system("pause");
}

void informeTurnosEstado() {
    system("cls");
    cout << "=== CANTIDAD DE TURNOS POR ESTADO ===" << endl;
    TurnoArchivo tArch("datos/turnos.dat");
    int cant = tArch.getCantidadRegistros();

    if (cant <= 0) {
        cout << "No hay turnos registrados." << endl;
        system("pause");
        return;
    }

    int contAsignado = 0, contAtendido = 0, contCancelado = 0, contAusente = 0;

    for (int i = 0; i < cant; i++) {
        Turno t = tArch.leer(i);
        if (t.getEstado()) {
            switch (t.getEstadoTurno()) {
                case EstadoTurno::ASIGNADO:  contAsignado++;  break;
                case EstadoTurno::ATENDIDO:  contAtendido++;  break;
                case EstadoTurno::CANCELADO: contCancelado++; break;
                case EstadoTurno::AUSENTE:   contAusente++;   break;
            }
        }
    }
    int total = contAsignado + contAtendido + contCancelado + contAusente;

    cout << "\n" << string(45, '=') << endl;
    cout << "      CANTIDAD DE TURNOS POR ESTADO" << endl;
    cout << string(45, '=') << endl;
    cout << left << setw(20) << "ESTADO" << right << setw(10) << "CANTIDAD"
         << setw(14) << "PORCENTAJE" << endl;
    cout << string(45, '-') << endl;

    string nombres[4] = {"Asignado", "Atendido", "Cancelado", "Ausente"};
    int valores[4] = {contAsignado, contAtendido, contCancelado, contAusente};
    for (int i = 0; i < 4; i++) {
        cout << left << setw(20) << nombres[i] << right << setw(10) << valores[i];
        porcentajeFmt(valores[i], total);
        cout << endl;
    }
    cout << string(45, '-') << endl;
    cout << left << setw(20) << "TOTAL" << right << setw(10) << total;
    porcentajeFmt(total, total);
    cout << endl << string(45, '=') << endl;

    system("pause");
}

void informeTurnosObraSocial() {
    system("cls");
    cout << "=== CANTIDAD DE TURNOS POR OBRA SOCIAL ===" << endl;
    TurnoArchivo tArch("datos/turnos.dat");
    PacienteArchivo pArch("datos/pacientes.dat");

    int cantTurnos = tArch.getCantidadRegistros();
    int cantPac = pArch.getCantidadRegistros();

    if (cantTurnos <= 0 || cantPac <= 0) {
        cout << "No hay suficientes datos registrados para generar el informe." << endl;
        system("pause");
        return;
    }

    string* nombres = new string[cantPac];
    int* cont = new int[cantPac]();
    int distintas = 0;

    for (int i = 0; i < cantPac; i++) {
        Paciente pac = pArch.leer(i);
        string os = pac.getObraSocial();
        bool existe = false;
        for (int k = 0; k < distintas && !existe; k++) {
            if (nombres[k] == os) existe = true;
        }
        if (!existe) nombres[distintas++] = os;
    }

    int total = 0;
    for (int i = 0; i < cantTurnos; i++) {
        Turno t = tArch.leer(i);
        if (!t.getEstado()) continue;

        int posPac = pArch.buscarPorId(t.getIdPaciente());
        if (posPac < 0) continue;
        Paciente pac = pArch.leer(posPac);
        string os = pac.getObraSocial();

        for (int k = 0; k < distintas; k++) {
            if (nombres[k] == os) {
                cont[k]++;
                total++;
                break;
            }
        }
    }

    for (int i = 0; i < distintas - 1; i++) {
        for (int j = 0; j < distintas - i - 1; j++) {
            if (nombres[j] > nombres[j + 1]) {
                string auxN = nombres[j];
                nombres[j] = nombres[j + 1];
                nombres[j + 1] = auxN;
                int auxC = cont[j];
                cont[j] = cont[j + 1];
                cont[j + 1] = auxC;
            }
        }
    }

    cout << "\n" << string(55, '=') << endl;
    cout << "      CANTIDAD DE TURNOS POR OBRA SOCIAL" << endl;
    cout << string(55, '=') << endl;
    cout << left << setw(25) << "OBRA SOCIAL" << right << setw(10) << "CANTIDAD"
         << setw(14) << "PORCENTAJE" << endl;
    cout << string(55, '-') << endl;
    for (int i = 0; i < distintas; i++) {
        cout << left << setw(25) << nombres[i] << right << setw(10) << cont[i];
        porcentajeFmt(cont[i], total);
        cout << endl;
    }
    cout << string(55, '-') << endl;
    cout << left << setw(25) << "TOTAL" << right << setw(10) << total;
    porcentajeFmt(total, total);
    cout << endl << string(55, '=') << endl;

    delete[] nombres;
    delete[] cont;
    system("pause");
}


void MenuManager::menuInformes() {
    int opcion = -1;
    do {
        system("cls");
        cout << "\n========================================\n";
        cout << "           INFORMES\n";
        cout << "========================================\n"
             << "1 - Recaudacion por mes\n"
             << "2 - Recaudacion por medico\n"
             << "3 - Cantidad de turnos por especialidad\n"
             << "4 - Cantidad de turnos por Estado\n"
             << "5 - Cantidad de turnos por Obra Social\n"
             << "0 - Volver al Menu Principal\n";
        cout << "----------------------------------------\n";
        cout << "Ingrese una opcion (0-5): ";
        if (!(cin >> opcion)) {
            cout << "\nError: Entrada invalida. Por favor, ingrese un numero entero.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("pause");
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1:
                informeRecaudacionMes();
                break;
            case 2:
                informeRecaudacionMedico();
                break;
            case 3:
                informeTurnosEspecialidad();
                break;
            case 4:
                informeTurnosEstado();
                break;
            case 5:
                informeTurnosObraSocial();
                break;
            case 0:
                break;
            default:
                cout << "\nOpcion invalida. Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
        }
    } while (opcion != 0);
}
