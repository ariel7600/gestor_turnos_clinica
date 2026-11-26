#include "menuManager.h"
#include "medico.h"
#include "medicoArchivo.h"
#include "horarioAtencionArchivo.h"
#include "agendaArchivo.h"
#include "turnosArchivos.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void MenuManager::menuMedicos() {
    int opcion=-1;
    MedicoArchivo archivo("datos/medico.dat");
    do {
        system("cls");
        cout << "\n========================================\n";
        cout << "        GESTION DE MEDICOS\n";
        cout << "========================================\n"
                  << "1 - Alta de Medico\n"
                  << "2 - Modificar Medico\n"
                  << "3 - Baja Logica de Medico\n"
                  << "4 - Listar todos los Medicos\n"
                  << "5 - Consultas\n"
                  << "0 - Volver al Menu Principal\n";
        cout << "----------------------------------------\n";

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
                cout << "=== ALTA DE MEDICO ===" << endl;
                Medico reg;

                int nuevoId = archivo.getCantidadRegistros() + 1;
                reg.setIdMedico(nuevoId);

                reg.cargar();
                reg.setEstado(true);

                if (archivo.guardar(reg)) {
                    cout << "\nMedico guardado exitosamente con ID: " << nuevoId << endl;
                } else {
                    cout << "\nError al guardar el medico en el archivo." << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "=== MODIFICAR MEDICO ===" << endl;
                int id;
                cout << "Ingrese el ID del medico a modificar: ";
                cin >> id;
                char respuesta='s';
                char nuevoTexto[100];
                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    Medico reg = archivo.leer(pos);
                    cout << "\nMatricula actual: " << reg.getMatricula();
                    cout << "\nDesea modificarla? (S/N): ";
                    cin >> respuesta;
                    if (toupper(respuesta) == 'S') {
                        cout << "Nueva matricula: ";
                        int mat=0;
                        cin>>mat;
                        reg.setMatricula(mat);
                    }
                    cout << "\nEspecialidad actual: " << reg.getIdEspecialidad();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nueva especialidad: ";
                        int n=0;
                        cin>>n;
                        reg.setIdEspecialidad(n);
                    }
                    cout << "\nNombre actual: " << reg.getNombre();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo nombre: ";
                        cin.getline(nuevoTexto, 50);
                        reg.setNombre(nuevoTexto);
                    }

                    cout << "\nApellido actual: " << reg.getApellido();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo apellido: ";
                        cin.getline(nuevoTexto, 50);
                        reg.setApellido(nuevoTexto);
                    }

                    cout << "\nDNI actual: " << reg.getDni();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo DNI: ";
                        int dni=0;
                        cin>> dni;
                        reg.setDni(dni);
                    }

                    cout << "\nTelefono actual: " << reg.getTelefono();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo telefono: ";
                        cin.getline(nuevoTexto, 20);
                        reg.setTelefono(nuevoTexto);
                    }

                    cout << "\nMail actual: " << reg.getMail();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo mail: ";
                        cin.getline(nuevoTexto, 50);
                        reg.setMail(nuevoTexto);
                    }

                    cout << "\nModificacion de datos finalizada." << endl;
                    if (archivo.guardar(reg, pos)) {
                        cout << "\nMedico modificado exitosamente." << endl;
                    } else {
                        cout << "\nError al actualizar el registro." << endl;
                    }
                } else {
                     cout << "\nNo existe un medico registrado con el ID ingresado." << endl;
                }

                system("pause");
                break;
            }
            case 3: {
                system("cls");
                cout << "=== BAJA LOGICA DE MEDICO ===" << endl;
                int id=0;
                cout << "Ingrese el ID del medico para dar de baja: ";
                cin >> id;

                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                Medico reg = archivo.leer(pos);
                if (reg.getEstado()) {
                        cout << "\nDatos del medico:" << endl;
                        reg.mostrar();

                        char confirma;

                        cout << "\nATENCION! Dar de baja a este medico desactivara sus horarios, agendas y cancelara sus turnos futuros." << endl;
                        cout << "Confirma la baja logica? (s/n): ";
                        cin >> confirma;

                        if (confirma == 's' || confirma == 'S') {

                            reg.setEstado(false);

                            if (archivo.guardar(reg, pos)) {

                                HorarioAtencionArchivo horarioArch("horarios.dat");
                                AgendaArchivo agendaArch("agendas.dat");
                                TurnoArchivo turnoArch("turnos.dat");

                                int cantHorarios = horarioArch.getCantidadRegistros();
                                int cantAgendas = agendaArch.getCantidadRegistros();
                                int cantTurnos = turnoArch.getCantidadRegistros();

                                int horariosModificados = 0;
                                int agendasModificadas = 0;
                                int turnosCancelados = 0;

                                int idMedicoBuscado = reg.getIdMedico();

                                for (int h = 0; h < cantHorarios; h++) {
                                    HorarioAtencion hor = horarioArch.leer(h);
                                    if (hor.getIdMedico() == idMedicoBuscado && hor.getEstado()) {
                                        hor.setEstado(false);
                                        if (horarioArch.guardar(hor, h)) {
                                            horariosModificados++;
                                        }
                                    }
                                }

                                for (int a = 0; a < cantAgendas; a++) {
                                    Agenda ag = agendaArch.leer(a);
                                    if (ag.getIdMedico() == idMedicoBuscado && ag.getEstado()) {
                                        ag.setEstado(false);
                                        if (agendaArch.guardar(ag, a)) {
                                            agendasModificadas++;

                                            for (int t = 0; t < cantTurnos; t++) {
                                                Turno turno = turnoArch.leer(t);
                                                if (turno.getIdAgenda() == ag.getIdAgenda() && turno.getEstado()) {
                                                    turno.setEstadoTurno(EstadoTurno::CANCELADO);
                                                    if (turnoArch.guardar(turno, t)) {
                                                        turnosCancelados++;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                cout << "\nBaja logica realizada con exito." << endl;
                                cout << "--- Resumen de acciones en cascada ---" << endl;
                                cout << "-> Horarios dados de baja: " << horariosModificados << endl;
                                cout << "-> Agendas dadas de baja: " << agendasModificadas << endl;
                                cout << "-> Turnos afectados cancelados: " << turnosCancelados << endl;

                            } else {
                                cout << "\nError al guardar los cambios del medico. No se aplico ninguna baja." << endl;
                            }
                        } else {
                            cout << "\nOperacion cancelada." << endl;
                        }
                    } else {
                        cout << "\nEl medico ya se encuentra dado de baja." << endl;
                    }
                } else {
                    cout << "\nNo existe un medico registrado con el ID ingresado." << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                    system("cls");
                    cout << "=== LISTADO DE MEDICOS ===" << endl;

                    vector<Medico> vecMedicos;
                    int cant = archivo.getCantidadRegistros();

                    for (int i = 0; i < cant; i++) {
                        Medico m = archivo.leer(i);
                        if (m.getEstado()) {
                            vecMedicos.push_back(m);
                        }
                    }

                    if (vecMedicos.empty()) {
                        cout << "No hay medicos registrados en el sistema." << endl;
                        system("pause");
                        return;
                    }

                    int opOrden = 0;
                    cout << "\n--- SELECCIONE EL CRITERIO DE LISTADO ---" << endl;
                    cout << "1- Listar por Apellido" << endl;
                    cout << "2- Listar solo por Especialidad" << endl;
                    cout << "3- Listar solo por Matricula" << endl;
                    cout << "0- Volver" << endl;
                    cout << "---------------------------------------------" << endl;
                    cout << "Ingrese una opcion: ";
                    cin >> opOrden;

                    if (opOrden == 0) return;

                       if (opOrden == 1) {
                            sort(vecMedicos.begin(), vecMedicos.end(), [](const Medico& a, const Medico& b) {
                            return string(a.getApellido()) < string(b.getApellido());
                        });
                    } else if (opOrden == 2) {
                        sort(vecMedicos.begin(), vecMedicos.end(), [](const Medico& a, const Medico& b) {
                            return a.getIdEspecialidad() < b.getIdEspecialidad();
                        });
                    } else if (opOrden == 3) {
                        sort(vecMedicos.begin(), vecMedicos.end(), [](const Medico& a, const Medico& b) {
                            return a.getMatricula() < b.getMatricula();
                        });
                    } else {
                        cout << "Opcion invalida. Se mostrara sin orden específico.\n";
                    }

                    system("cls");
                    cout << "=== LISTADO DE MEDICOS ORDENADO ===" << endl;
                    cout << "--------------------------------------------------" << endl;

                    for (size_t i = 0; i < vecMedicos.size(); i++) {
                        vecMedicos[i].mostrar();
                        cout << "--------------------------------------------------" << endl;
                    }

                    system("pause");
                    break;
            }
            case 5: {
                int subOpcion=-1;
                do {
                    system("cls");
                    cout << "=== CONSULTAS DE MEDICOS ===" << endl;
                    cout << "1. Buscar por Matricula" << endl;
                    cout << "2. Buscar por Especialidad (ID)" << endl;
                    cout << "3. Buscar por Estado (Activo/Inactivo)" << endl;
                    cout << "0. Volver al Submenu Medicos" << endl;
                    cout << "----------------------------" << endl;
                    cout << "Ingrese una opcion: ";
                    if (!(cin >> subOpcion)) {
                        cout << "\nError: Entrada invalida. Por favor, ingrese un numero entero.\n";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        system("pause");
                        subOpcion = -1;
                        continue;
                    }

                    int cant = archivo.getCantidadRegistros();
                    if (cant <= 0 && subOpcion != 0) {
                        cout << "No hay medicos registrados en el archivo." << endl;
                        system("pause");
                        continue;
                    }

                    switch (subOpcion) {
                        case 1: {
                            int matriculaBuscada;
                            cout << "Ingrese la matricula a buscar: ";
                            cin >> matriculaBuscada;
                            bool encontrado = false;

                            for (int i = 0; i < cant; i++) {
                                Medico reg = archivo.leer(i);
                                if (reg.getMatricula() == matriculaBuscada) {
                                    reg.mostrar();
                                    cout << "-----------------------" << endl;
                                    encontrado = true;
                                }
                            }
                            if (!encontrado) cout << "No se encontro ningun medico con esa matricula." << endl;
                            system("pause");
                            break;
                        }
                        case 2: {
                            int espBuscada;
                            cout << "Ingrese el ID de la especialidad a buscar: ";
                            cin >> espBuscada;
                            bool encontrado = false;

                            for (int i = 0; i < cant; i++) {
                                Medico reg = archivo.leer(i);
                                if (reg.getIdEspecialidad() == espBuscada) {
                                    reg.mostrar();
                                    cout << "-----------------------" << endl;
                                    encontrado = true;
                                }
                            }
                            if (!encontrado) cout << "No se encontraron medicos para dicha especialidad." << endl;
                            system("pause");
                            break;
                        }
                        case 3: {
                            int estadoBuscado;
                            cout << "Ingrese el estado (1 para Activos, 0 para Inactivos): ";
                            cin >> estadoBuscado;
                            bool encontrado = false;
                            bool estadoBool = (estadoBuscado != 0);

                            for (int i = 0; i < cant; i++) {
                                Medico reg = archivo.leer(i);
                                if (reg.getEstado() == estadoBool) {
                                    reg.mostrar();
                                    cout << "-----------------------" << endl;
                                    encontrado = true;
                                }
                            }
                            if (!encontrado) cout << "No se encontraron medicos con ese estado." << endl;
                            system("pause");
                            break;
                        }
                    }
                } while (subOpcion != 0);
                break;
            }
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
