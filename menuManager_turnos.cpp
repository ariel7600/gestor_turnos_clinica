#include "menuManager.h"
#include "turnos.h"
#include "turnosArchivos.h"
#include "historialArchivo.h"
#include "historialMedico.h"
#include "agendaArchivo.h"
#include "pacienteArchivo.h"
#include "historialArchivo.h"
#include<iostream>
using namespace std;

void MenuManager::menuTurnos() {
    int opcion=-1;
    TurnoArchivo archivo("datos/turnos.dat");
    do {
        system("cls");
        cout << "\n========================================\n";
        cout << "        GESTION DE TURNOS\n";
        cout << "========================================\n"
                  << "1 - Alta de Turno\n"
                  << "2 - Modificar Turno\n"
                  << "3 - Baja Logica de Turno\n"
                  << "4 - Listar todos los Turnos\n"
                  << "5 - Consultas\n"
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
            case 1: {
                system("cls");
                cout << "=== ALTA DE TURNO ===" << endl;
                Turno reg;

                reg.cargar();
                reg.setEstado(true);

                if (archivo.guardar(reg)) {
                    cout << "\nTurno guardado exitosamente con ID: " << reg.getIdTurno()<< endl;
                } else {
                    cout << "\nError al guardar el turno en el archivo." << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "=== MODIFICAR TURNO ===" << endl;
                int id;
                cout << "Ingrese el ID del turno a modificar: ";
                cin >> id;
                char respuesta='s';
                char nuevoTexto[100];
                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    Turno reg = archivo.leer(pos);
                    cout << "\nID del paciente actual: " << reg.getIdPaciente();
                    cout << "\nDesea modificarla? (S/N): ";
                    cin >> respuesta;
                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo ID paciente: ";
                        int idP=0;
                        cin>>idP;
                        reg.setIdPaciente(idP);
                    }
                    cout << "\nId agenda: " << reg.getIdAgenda();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo ID agenda: ";
                        int n=0;
                        cin>>n;
                        reg.setIdAgenda(n);
                    }
                    cout << "\nMotivo turno: " << reg.getMotivo();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo motivo: ";
                        cin.getline(nuevoTexto, 50);
                        reg.setMotivo(nuevoTexto);
                    }

                    cout << "\nObservacion del turno: " << reg.getObservacionPrevia();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nueva observacion: ";
                        cin.getline(nuevoTexto, 50);
                        reg.setObservacionPrevia(nuevoTexto);
                    }

                    cout << "\nCosto de la consulta: " << reg.getCostoConsulta();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Costo de la consulta: ";
                        float cost=0;
                        cin>> cost;
                        reg.setCostoConsulta(cost);
                    }
                    cout << "\nDesea modificar el estado del turno? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    EstadoTurno estadoAnterior = reg.getEstadoTurno();
                    bool registrarHistorialPendiente = false;
                    HistorialMedico historialTemp;

                    if (toupper(respuesta) == 'S') {
                        int opEstado = 0;
                        do {
                            cout << "Nuevo Estado (1: Asignado, 2: Atendido, 3: Cancelado, 4: Ausente): ";
                            if (!(cin >> opEstado)) {
                                cout << "Entrada invalida. Ingrese un numero.\n";
                                cin.clear();
                                cin.ignore(10000, '\n');
                                opEstado = 0;
                            }
                        } while (opEstado < 1 || opEstado > 4);
                        cin.ignore();

                        if (estadoAnterior == EstadoTurno::ATENDIDO && opEstado != 2) {
                            cout << "\nError: Un turno que ya fue ATENDIDO no puede pasar a otro estado.\n";
                            system("pause");
                            break;
                        }

                        switch (opEstado) {
                            case 1:
                                reg.setEstadoTurno(EstadoTurno::ASIGNADO);
                                break;
                            case 2: {
                                reg.setEstadoTurno(EstadoTurno::ATENDIDO);

                                if (estadoAnterior == EstadoTurno::ATENDIDO) {
                                    cout << "\nEl turno ya se encontraba atendido.\n";
                                } else {
                                    cout << "\n--- EL TURNO FUE ATENDIDO. REGISTRE EL HISTORIAL MEDICO ---" << endl;

                                    HistorialArchivo histArch("datos/historialMedico.dat");
                                    int ultimoIdHist = histArch.getCantidadRegistros();

                                    historialTemp.setIdHistorial(ultimoIdHist + 1);
                                    historialTemp.setIdPaciente(reg.getIdPaciente());

                                    AgendaArchivo agendaArch("datos/agendas.dat");
                                    int posAgenda = agendaArch.buscarPorId(reg.getIdAgenda());
                                    if (posAgenda >= 0) {
                                        Agenda agendaTurno = agendaArch.leer(posAgenda);
                                        historialTemp.setFechaHistorial(agendaTurno.getFecha());
                                    }

                                    cout << "Paciente ID asignado automaticamente: " << reg.getIdPaciente() << endl;
                                    historialTemp.cargar();
                                    historialTemp.setEstado(true);

                                    registrarHistorialPendiente = true;
                                }
                                break;
                            }
                            case 3:
                                reg.setEstadoTurno(EstadoTurno::CANCELADO);
                                break;
                            case 4:
                                reg.setEstadoTurno(EstadoTurno::AUSENTE);
                                break;
                        }
                    }

                    cout << "\nModificacion de datos finalizada." << endl;

                    if (archivo.guardar(reg, pos)) {
                        cout << "\nTurno modificado exitosamente." << endl;

                        if (registrarHistorialPendiente) {
                            HistorialArchivo histArch("datos/historialMedico.dat");
                            if (histArch.guardar(historialTemp)) {
                                cout << "¡Historial medico creado y guardado exitosamente con ID: " << historialTemp.getIdHistorial() << "!\n";
                            } else {
                                cout << "¡Atencion! El turno se actualizo, pero hubo un error al guardar el historial medico en el archivo.\n";
                            }
                        }

                    } else {
                        cout << "\nError al actualizar el registro del turno. No se realizaron cambios.\n";
                    }
                }
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                cout << "=== BAJA LOGICA DE TURNO ===" << endl;
                int id;
                cout << "Ingrese el ID del turno para dar de baja: ";
                cin >> id;

                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    Turno reg = archivo.leer(pos);
                    if (reg.getEstado()) {
                        cout << "\nDatos del turno:" << endl;
                        reg.mostrar();

                        char confirma;
                        cout << "\nConfirma la baja logica? (s/n): ";
                        cin >> confirma;

                        if (confirma == 's' || confirma == 'S') {
                            reg.setEstado(false);
                            if (archivo.guardar(reg, pos)) {
                                cout << "\nBaja logica realizada con exito." << endl;
                            } else {
                                cout << "\nError al guardar los cambios." << endl;
                            }
                        } else {
                            cout << "\nOperacion cancelada." << endl;
                        }
                    } else {
                        cout << "\nEl turno ya se encuentra dado de baja." << endl;
                    }
                } else {
                    cout << "\nNo existe un turno registrado con el ID ingresado." << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                cout << "=== LISTADO DE TURNOS (Ordenados por Fecha y Paciente) ===" << endl;
                int cant = archivo.getCantidadRegistros();

                if (cant <= 0) {
                    cout << "No hay turnos registrados." << endl;
                    system("pause");
                    break;
                }

                Turno* vec = new Turno[cant];
                if (vec == nullptr) {
                    cout << "Error de asignacion de memoria." << endl;
                    system("pause");
                    break;
                }

                for (int i = 0; i < cant; i++) {
                    vec[i] = archivo.leer(i);
                }

                AgendaArchivo agendaArch("datos/agendas.dat");
                PacienteArchivo pacienteArch("datos/pacientes.dat");

                for (int i = 0; i < cant - 1; i++) {
                    for (int j = 0; j < cant - i - 1; j++) {
                        bool intercambiar = false;


                        int posAgenda1 = agendaArch.buscarPorId(vec[j].getIdAgenda());
                        int posAgenda2 = agendaArch.buscarPorId(vec[j+1].getIdAgenda());

                        Fecha f1 = (posAgenda1 >= 0) ? agendaArch.leer(posAgenda1).getFecha() : Fecha();
                        Fecha f2 = (posAgenda2 >= 0) ? agendaArch.leer(posAgenda2).getFecha() : Fecha();


                        int posPac1 = pacienteArch.buscarPorId(vec[j].getIdPaciente());
                        int posPac2 = pacienteArch.buscarPorId(vec[j+1].getIdPaciente());

                        string apNom1 = "";
                        string apNom2 = "";

                        if (posPac1 >= 0) {
                            Paciente p1 = pacienteArch.leer(posPac1);
                            apNom1 = string(p1.getApellido()) + " " + p1.getNombre();
                        }
                        if (posPac2 >= 0) {
                            Paciente p2 = pacienteArch.leer(posPac2);
                            apNom2 = string(p2.getApellido()) + " " + p2.getNombre();
                        }

                        if (f2 < f1) {
                            intercambiar = true;
                        }
                        else if (!(f1 < f2) && !(f2 < f1)) {

                            if (apNom1 > apNom2) {
                                intercambiar = true;
                            }
                        }

                        if (intercambiar) {
                            Turno aux = vec[j];
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
            case 5: {
                int subOpcion = -1;
                do {
                    system("cls");
                    cout << "=== CONSULTAS DE TURNOS ===" << endl;
                    cout << "1. Buscar por Rango de Fechas" << endl;
                    cout << "2. Buscar por Paciente (ID)" << endl;
                    cout << "3. Buscar por Medico (ID)" << endl;
                    cout << "4. Buscar por Estado de Turno" << endl;
                    cout << "0. Volver al Submenu Turnos" << endl;
                    cout << "----------------------------" << endl;
                    cout << "Ingrese una opcion: ";
                    cin >> subOpcion;

                    int cant = archivo.getCantidadRegistros();
                    if (cant <= 0 && subOpcion != 0) {
                        cout << "No hay turnos registrados en el archivo." << endl;
                        system("pause");
                        continue;
                    }

                    AgendaArchivo agendaArch("datos/agendas.dat");

                    switch (subOpcion) {
                        case 1: {
                            system("cls");
                            cout << "=== CONSULTA DE TURNOS POR RANGO DE FECHAS ===" << endl;

                            Fecha fechaDesde, fechaHasta;
                            cout << "--- FECHA DESDE ---" << endl;
                            fechaDesde.cargar();

                            cout << "\n--- FECHA HASTA ---" << endl;
                            fechaHasta.cargar();

                            bool encontrado = false;
                            cout << "\nResultados de turnos en el rango:" << endl;
                            cout << "-----------------------------------" << endl;

                            for (int i = 0; i < cant; i++) {
                                Turno reg = archivo.leer(i);

                                int posAgenda = agendaArch.buscarPorId(reg.getIdAgenda());
                                if (posAgenda >= 0) {
                                    Agenda ag = agendaArch.leer(posAgenda);
                                    Fecha fAgenda = ag.getFecha();

                                    bool esMayorOIgualDesde = !(fAgenda < fechaDesde);
                                    bool esMenorOIgualHasta = (fAgenda <= fechaHasta);

                                    if (esMayorOIgualDesde && esMenorOIgualHasta) {
                                        reg.mostrar();
                                        cout << "-----------------------------------" << endl;
                                        encontrado = true;
                                    }
                                }
                            }

                            if (!encontrado) {
                                cout << "No se encontraron turnos dentro de ese rango de fechas." << endl;
                            }
                            system("pause");
                            break;
                        }
                        case 2: {
                            system("cls");
                            cout << "=== CONSULTA DE TURNOS POR PACIENTE ===" << endl;
                            int pacienteBuscado;
                            cout << "Ingrese el ID del paciente a buscar: ";
                            cin >> pacienteBuscado;

                            bool encontrado = false;
                            cout << "\nResultados para el paciente ID " << pacienteBuscado << ":" << endl;
                            cout << "-----------------------------------" << endl;

                            for (int i = 0; i < cant; i++) {
                                Turno reg = archivo.leer(i);
                                if (reg.getIdPaciente() == pacienteBuscado) {
                                    reg.mostrar();
                                    cout << "-----------------------------------" << endl;
                                    encontrado = true;
                                }
                            }

                            if (!encontrado) {
                                cout << "No se encontraron turnos para ese paciente." << endl;
                            }
                            system("pause");
                            break;
                        }
                        case 3: {
                            system("cls");
                            cout << "=== CONSULTA DE TURNOS POR MEDICO ===" << endl;
                            int medicoBuscado;
                            cout << "Ingrese el ID del medico a buscar: ";
                            cin >> medicoBuscado;

                            bool encontrado = false;
                            cout << "\nResultados para el medico ID " << medicoBuscado << ":" << endl;
                            cout << "-----------------------------------" << endl;

                            for (int i = 0; i < cant; i++) {
                                Turno reg = archivo.leer(i);


                                int posAgenda = agendaArch.buscarPorId(reg.getIdAgenda());
                                if (posAgenda >= 0) {
                                    Agenda ag = agendaArch.leer(posAgenda);
                                    if (ag.getIdMedico() == medicoBuscado) {
                                        reg.mostrar();
                                        cout << "-----------------------------------" << endl;
                                        encontrado = true;
                                    }
                                }
                            }

                            if (!encontrado) {
                                cout << "No se encontraron turnos para ese medico." << endl;
                            }
                            system("pause");
                            break;
                        }
                        case 4: {
                            system("cls");
                            cout << "=== CONSULTA DE TURNOS POR ESTADO ===" << endl;
                            int opEstado = 0;
                            cout << "Seleccione el Estado a buscar:\n";
                            cout << "1: Asignado\n2: Atendido\n3: Cancelado\n4: Ausente\n";
                            cout << "Opcion: ";
                            cin >> opEstado;

                            EstadoTurno estadoFiltro;
                            switch (opEstado) {
                                case 1: estadoFiltro = EstadoTurno::ASIGNADO; break;
                                case 2: estadoFiltro = EstadoTurno::ATENDIDO; break;
                                case 3: estadoFiltro = EstadoTurno::CANCELADO; break;
                                case 4: estadoFiltro = EstadoTurno::AUSENTE; break;
                                default:
                                    cout << "Opcion de estado invalida.\n";
                                    system("pause");
                                    continue;
                            }

                            bool encontrado = false;
                            cout << "\nResultados para el estado seleccionado:" << endl;
                            cout << "-----------------------------------" << endl;

                            for (int i = 0; i < cant; i++) {
                                Turno reg = archivo.leer(i);

                                if (reg.getEstadoTurno() == estadoFiltro) {
                                    reg.mostrar();
                                    cout << "-----------------------------------" << endl;
                                    encontrado = true;
                                }
                            }

                            if (!encontrado) {
                                cout << "No se encontraron turnos con ese estado." << endl;
                            }
                            system("pause");
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opcion invalida.\n";
                            system("pause");
                            break;
                    }
                } while (subOpcion != 0);
                break;
            }
            default:
                cout << "\nOpcion invalida. Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
        }
    } while (opcion != 0);
}
