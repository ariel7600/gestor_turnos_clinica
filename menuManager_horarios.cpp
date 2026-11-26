#include "menuManager.h"
#include "horarioAtencionArchivo.h"
#include "agendaArchivo.h"
#include "turnosArchivos.h"
#include<iostream>
using namespace std;

void MenuManager::menuHorarios() {
     int opcion=-1;
     HorarioAtencionArchivo archivo("datos/horarios.dat");
     AgendaArchivo arch("datos/agendas.dat");
     do {
        system("cls");
        cout << "\n========================================\n";
        cout << "        GESTION DE HORARIOS Y AGENDA\n";
        cout << "========================================\n"
                  << "1 - Alta de Horario Medico\n"
                  << "2 - Modificar Horario Medico\n"
                  << "3 - Baja Logica de Horario Medico\n"
                  << "4 - Listar todos los Horarios Medicos\n"
                  << "5 - Consultas de Agenda.\n"
                  << "0 - Volver al Menu Principal\n";
        cout<<"Ingrese una opcion (0-5): ";
        if (!(cin >> opcion)) {
            cout << "\nError: Entrada invalida. Por favor, ingrese un numero entero.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            system("pause");
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1:{
                system("cls");
                cout << "=== ALTA DE HORARIO MEDICO ===" << endl;
                HorarioAtencion reg;

                int nuevoId = archivo.getCantidadRegistros() + 1;
                reg.setIdHorario(nuevoId);

                reg.cargar();
                reg.setEstado(true);

                if (archivo.guardar(reg)) {

                    cout << "\nHorario medico guardado exitosamente con ID: "<< nuevoId << endl;

                    if (arch.generarDesdeHorario(reg, 4)) {
                        cout << "¡Agendas generadas con exito!\n";
                    } else {
                        cout << "Error al generar las agendas.\n";
                    }

                } else {
                    cout << "\nError al guardar el horario medico en el archivo."<< endl;
                }
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "=== MODIFICAR HORARIO MEDICO ===" << endl;
                int id;
                cout << "Ingrese el ID del horario medico a modificar: ";
                cin >> id;
                char respuesta='s';
                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    HorarioAtencion reg = archivo.leer(pos);
                    cout << "\nID medico actual: " << reg.getIdMedico();
                    cout << "\nDesea modificarla? (S/N): ";
                    cin >> respuesta;
                    if (toupper(respuesta) == 'S') {
                        cout << "Nueva matricula: ";
                        int idm=0;
                        cin>>idm;
                        reg.setIdMedico(idm);
                    }
                    cout << "\nDia actual: " << reg.diaSemanaTexto(reg.getDia());
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        int opcion = 0;
                        do {
                            cout << "\nSeleccione el dia:\n";
                            cout << "1-Lunes, 2- Martes, 3- Miercoles, 4- Jueves \n";
                            cout << "5-Viernes, 6-Sabado, 7-Domingo. \n";
                            cout << "Opcion: ";
                            if (!(cin >> opcion)) {
                                cout << "\nError: Entrada invalida. Por favor, ingrese un numero entero.\n";
                                cin.clear();
                                cin.ignore(10000, '\n');
                                system("pause");
                                opcion = -1;
                                continue;
                            }
                            if (opcion < 1 || opcion > 7) {
                                cout << "Opcion invalida.\n";
                            }
                        } while (opcion < 1 || opcion > 7);

                        reg.setDia(static_cast<DiaSemana>(opcion));
                    }
                    cout << "\nHorario actual: " << reg.getHorario().toString();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        HoraMin nuevoHorario;
                        nuevoHorario.cargar();
                        reg.setHorario(nuevoHorario);
                    }

                    cout << "\nDuracion actual: " << reg.getDuracion();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nueva duracion: ";
                        int d=0;
                        cin>>d;
                        reg.setDuracion(d);
                    }

                    cout << "\nModificacion de datos finalizada." << endl;
                    if (archivo.guardar(reg, pos)) {
                        cout << "\nHorario modificado exitosamente." << endl;
                    } else {
                        cout << "\nError al actualizar el registro." << endl;
                    }
                } else {
                     cout << "\nNo existe un Horario medico registrado con el ID ingresado." << endl;
                }

                system("pause");
                break;
            }
            case 3: {
                system("cls");
                cout << "=== BAJA LOGICA DE HORARIO MEDICO ===" << endl;
                int id;
                cout << "Ingrese el ID del horario medico para dar de baja: ";
                cin >> id;

                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    HorarioAtencion reg = archivo.leer(pos);
                    if (reg.getEstado()) {
                        cout << "\nDatos del horario medico:" << endl;
                        reg.mostrar();

                        char confirma;
                        cout << "\nConfirma la baja logica? (s/n): ";
                        cin >> confirma;

                        if (confirma == 's' || confirma == 'S') {
                            reg.setEstado(false);
                            if (archivo.guardar(reg, pos)) {
                                cout << "\nBaja logica realizada con exito." << endl;
                                // Baja logica a las agendas asociadas y cancelacion de turnos
                                AgendaArchivo agendaArch("datos/agendas.dat");
                                TurnoArchivo turnoArch("datos/turnos.dat");

                                int cantAgendas = agendaArch.getCantidadRegistros();
                                int cantTurnos = turnoArch.getCantidadRegistros();
                                int agendasModificadas = 0;
                                int turnosCancelados = 0;
                                for (int i = 0; i < cantAgendas; i++) {
                                    Agenda ag = agendaArch.leer(i);

                                    if (ag.getIdMedico() == reg.getIdMedico() && ag.getEstado()) {
                                        bool coincideDia = ag.getFecha().esDia(static_cast<int>(reg.getDia()));

                                        bool horaInicioValida = !(ag.getHorario().getHoraInicio() < reg.getHorario().getHoraInicio());
                                        bool horaFinValida = (ag.getHorario().getHoraFin() < reg.getHorario().getHoraFin());

                                        if (coincideDia && horaInicioValida && horaFinValida) {
                                            ag.setEstado(false);

                                            if (agendaArch.guardar(ag, i)) {
                                                agendasModificadas++;

                                                for (int j = 0; j < cantTurnos; j++) {
                                                    Turno t = turnoArch.leer(j);
                                                    if (t.getIdAgenda() == ag.getIdAgenda() && t.getEstado() && t.getEstadoTurno() == EstadoTurno::ASIGNADO) {
                                                        t.setEstadoTurno(EstadoTurno::CANCELADO);

                                                        if (turnoArch.guardar(t, j)) {
                                                            turnosCancelados++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                cout << "-> Agendas dadas de baja: " << agendasModificadas << endl;
                                cout << "-> Turnos afectados cancelados: " << turnosCancelados << endl;
                            } else {
                                cout << "\nError al guardar los cambios." << endl;
                            }
                        } else {
                            cout << "\nOperacion cancelada." << endl;
                        }
                    } else {
                        cout << "\nEl horario medico ya se encuentra dado de baja." << endl;
                    }
                } else {
                    cout << "\nNo existe un horario medico registrado con el ID ingresado." << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                cout << "=== LISTADO DE HORARIOS MEDICOS (Ordenados por medico y dia) ===" << endl;
                int cant = archivo.getCantidadRegistros();

                if (cant <= 0) {
                    cout << "No hay Horarios medicos registrados." << endl;
                    system("pause");
                    break;
                }

                HorarioAtencion* vec = new HorarioAtencion[cant];
                if (vec == nullptr) {
                    cout << "Error de asignacion de memoria." << endl;
                    system("pause");
                    break;
                }


                for (int i = 0; i < cant; i++) {
                    vec[i] = archivo.leer(i);
                }

                for (int i = 0; i < cant - 1; i++) {
                    for (int j = 0; j < cant - i - 1; j++) {
                        bool intercambiar = false;
                        int ap1 = vec[j].getIdMedico();
                        int ap2 = vec[j+1].getIdMedico();

                        if (ap1 > ap2) {
                            intercambiar = true;
                        } else if (ap1 == ap2) {
                            if (vec[j].getDia() > vec[j+1].getDia()) {
                                intercambiar = true;
                            }
                        }

                        if (intercambiar) {
                            HorarioAtencion aux = vec[j];
                            vec[j] = vec[j+1];
                            vec[j+1] = aux;
                        }
                    }
                }


                for (int i = 0; i < cant; i++) {
                    vec[i].mostrar();
                    cout << "-----------------------------------" << endl;
                }

                delete[] vec;
                system("pause");
                break;
            }
            case 5:{
                int subOpcion=-1;
                do {
                    system("cls");
                    cout << "=== CONSULTAS DE AGENDA ===" << endl;
                    cout << "1. Buscar por medico" << endl;
                    cout << "2. Buscar por Rango de Fechas." << endl;
                    cout << "0. Volver al Submenu Horarios" << endl;
                    cout << "----------------------------" << endl;
                    cout << "Ingrese una opcion: ";
                    cin >> subOpcion;

                    int cant = arch.getCantidadRegistros();
                    if (cant <= 0 && subOpcion != 0) {
                        cout << "No hay agendas registradas en el archivo." << endl;
                        system("pause");
                        continue;
                    }

                    switch (subOpcion) {
                        case 1: {
                            int medicoBuscado;
                            cout << "=== BUSCAR AGENDA POR ID MEDICO ===" << endl;
                            cout << "Ingrese ID del medico a buscar: ";
                            cin >> medicoBuscado;
                            bool encontrado = false;

                            for (int i = 0; i < cant; i++) {
                                Agenda reg = arch.leer(i);
                                if (reg.getIdMedico() == medicoBuscado) {
                                    reg.mostrar();
                                    cout << "-----------------------" << endl;
                                    encontrado = true;
                                }
                            }
                            if (!encontrado) cout << "No se encontro ningun medico con esa ID." << endl;
                            system("pause");
                            break;
                        }
                        case 2: {
                            system("cls");
                            cout << "=== BUSCAR AGENDA POR RANGO DE FECHAS ===" << endl;

                            Fecha fechaDesde, fechaHasta;
                            cout << "--- FECHA DESDE ---" << endl;
                            fechaDesde.cargar();

                            cout << "\n--- FECHA HASTA ---" << endl;
                            fechaHasta.cargar();

                            bool encontrado = false;
                            cout << "\nResultados en el rango de fechas:" << endl;
                            cout << "-----------------------------------" << endl;

                            for (int i = 0; i < cant; i++) {
                                Agenda reg = arch.leer(i);
                                Fecha fAgenda = reg.getFecha();

                                bool esMayorOIgualDesde = !(fAgenda < fechaDesde);
                                bool esMenorOIgualHasta = (fAgenda <= fechaHasta);

                                if (esMayorOIgualDesde && esMenorOIgualHasta) {
                                    reg.mostrar();
                                    cout << "-----------------------------------" << endl;
                                    encontrado = true;
                                }
                            }

                            if (!encontrado) {
                                    cout << "No se encontraron agendas dentro de ese rango de fechas." << endl;
                            }
                            system("pause");
                            break;
                        }
                    }
                } while (subOpcion != 0);
                break;
            }
        }
    } while (opcion != 0);

}
