#include "pacienteArchivo.h"
#include "MenuManager.h"
#include "turnosArchivos.h"
#include "agendaArchivo.h"
#include "historialArchivo.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void MenuManager::menuPacientes() {
    int opcion=-1;
    PacienteArchivo archivo("datos/pacientes.dat");
    do {
        system("cls");
        cout << "\n========================================\n";
        cout << "        GESTION DE PACIENTES\n";
        cout << "========================================\n"
                  << "1 - Alta de Paciente\n"
                  << "2 - Modificar Paciente\n"
                  << "3 - Baja Logica de Paciente\n"
                  << "4 - Listar todos los Pacientes\n"
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
                cout << "=== ALTA DE PACIENTE ===" << endl;
                Paciente reg;

                reg.cargar();
                reg.setEstado(true);

                if (archivo.guardar(reg)) {
                    cout << "\nPaciente guardado exitosamente con ID: " << reg.getIdPaciente() << endl;
                } else {
                    cout << "\nError al guardar el paciente en el archivo." << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "=== MODIFICAR PACIENTE ===" << endl;
                int id;
                cout << "Ingrese el ID del paciente a modificar: ";
                cin >> id;
                char respuesta='s';
                char nuevoTexto[100];
                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    Paciente reg = archivo.leer(pos);
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
                    cout << "\nObra social actual: " << reg.getObraSocial();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nueva Obra social: ";
                        cin.getline(nuevoTexto, 50);
                        reg.setObraSocial(nuevoTexto);
                    }
                    cout << "\nNumero de afiliado actual: " << reg.getNumAfiliado();
                    cout << "\nDesea modificarlo? (S/N): ";
                    cin >> respuesta;
                    cin.ignore();

                    if (toupper(respuesta) == 'S') {
                        cout << "Nuevo numero de afiliado: ";
                        int numAf=0;
                        cin>> numAf;
                        reg.setNumAfiliado(numAf);
                    }

                    cout << "\nModificacion de datos finalizada." << endl;
                    if (archivo.guardar(reg, pos)) {
                        cout << "\nPaciente modificado exitosamente." << endl;
                    } else {
                        cout << "\nError al actualizar el registro." << endl;
                    }
                } else {
                     cout << "\nNo existe un paciente registrado con el ID ingresado." << endl;
                }

                system("pause");
                break;
            }
            case 3: {
                system("cls");
                cout << "=== BAJA LOGICA DE PACIENTE ===" << endl;
                int id;
                cout << "Ingrese el ID del paciente para dar de baja: ";
                cin >> id;

                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    Paciente reg = archivo.leer(pos);
                    if (reg.getEstado()) {
                        cout << "\nDatos del paciente:" << endl;
                        reg.mostrar();

                        char confirma;
                        cout << "\nATENCION! Dar de baja al paciente cancelara sus turnos pendientes." << endl;
                        cout << "Confirma la baja logica? (s/n): ";
                        cin >> confirma;

                        if (confirma == 's' || confirma == 'S') {
                            reg.setEstado(false);
                            if (archivo.guardar(reg, pos)) {
                                cout << "\nBaja logica del paciente realizada con exito." << endl;

                                TurnoArchivo turnoArch("datos/turnos.dat");
                                AgendaArchivo agendaArch("datos/agendas.dat");

                                int cantTurnos = turnoArch.getCantidadRegistros();
                                int turnosCancelados = 0;

                                for (int i = 0; i < cantTurnos; i++) {
                                    Turno t = turnoArch.leer(i);

                                    if (t.getIdPaciente() == reg.getIdPaciente() &&
                                        t.getEstado() &&
                                        t.getEstadoTurno() == EstadoTurno::ASIGNADO) {

                                        t.setEstadoTurno(EstadoTurno::CANCELADO);
                                        if (turnoArch.guardar(t, i)) {
                                            turnosCancelados++;

                                            //agenda para turno vuelve a estar disponible
                                            int posAg = agendaArch.buscarPorId(t.getIdAgenda());
                                            if (posAg >= 0) {
                                                Agenda ag = agendaArch.leer(posAg);
                                                if (ag.getEstado()) {
                                                    ag.setDisponibilidad(true);
                                                    agendaArch.guardar(ag, posAg);
                                                }
                                            }
                                        }
                                    }
                                }

                                cout << "-> Turnos pendientes cancelados en cascada: " << turnosCancelados << endl;
                            } else {
                                cout << "\nError al guardar los cambios del paciente. No se modificaron los turnos." << endl;
                            }
                        } else {
                            cout << "\nOperacion cancelada." << endl;
                        }
                    } else {
                        cout << "\nEl paciente ya se encuentra dado de baja." << endl;
                    }
                } else {
                    cout << "\nNo existe un paciente registrado con el ID ingresado." << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                cout << "=== LISTADO DE PACIENTES ===" << endl;

                vector<Paciente> vecPacientes;
                int cant = archivo.getCantidadRegistros();

                for (int i = 0; i < cant; i++) {
                    Paciente p = archivo.leer(i);
                    if (p.getEstado()) {
                        vecPacientes.push_back(p);
                    }
                }

                if (vecPacientes.empty()) {
                    cout << "No hay pacientes registrados en el sistema." << endl;
                    system("pause");
                    return;
                }

                int opOrden = 0;
                cout << "\n--- SELECCIONE EL CRITERIO DE ORDENAMIENTO ---" << endl;
                cout << "1- Ordenar por Apellido" << endl;
                cout << "2- Ordenar por Edad (de mayor a menor)" << endl;
                cout << "3- Ordenar por Obra Social" << endl;
                cout << "0- Volver" << endl;
                cout << "---------------------------------------------" << endl;
                cout << "Ingrese una opcion: ";
                cin >> opOrden;

                if (opOrden == 0) return;

                if (opOrden == 1) {
                    sort(vecPacientes.begin(), vecPacientes.end(), [](const Paciente& a, const Paciente& b) {
                        return string(a.getApellido()) < string(b.getApellido());
                    });
                } else if (opOrden == 2) {
                    sort(vecPacientes.begin(), vecPacientes.end(), [](const Paciente& a, const Paciente& b) {
                        return a.getFechaNacimiento() < b.getFechaNacimiento();
                    });
                } else if (opOrden == 3) {
                    sort(vecPacientes.begin(), vecPacientes.end(), [](const Paciente& a, const Paciente& b) {
                        return string(a.getObraSocial()) < string(b.getObraSocial());
                    });
                } else {
                cout << "Opcion invalida. Se mostrara sin orden específico.\n";
                }

                system("cls");
                cout << "=== LISTADO DE PACIENTES ORDENADO ===" << endl;
                cout << "--------------------------------------------------" << endl;

                for (size_t i = 0; i < vecPacientes.size(); i++) {
                    vecPacientes[i].mostrar();
                    cout << "--------------------------------------------------" << endl;
                }

                system("pause");
                break;
            }
            case 5:{
                int subOpcion=-1;
                do {
                    system("cls");
                    cout << "=== CONSULTAS DE PACIENTES ===" << endl;
                    cout << "1- Buscar por DNI" << endl;
                    cout << "2- Buscar por Obra social" << endl;
                    cout << "3- Buscar por Estado (Activo/Inactivo)" << endl;
                    cout << "4- Mostrar el historial medico"<< endl;
                    cout << "0- Volver al Submenu Pacientes" << endl;
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
                        cout << "No hay pacientes registrados en el archivo." << endl;
                        system("pause");
                        continue;
                    }

                    switch (subOpcion) {
                        case 1: {
                            int dniBuscado;
                            cout << "Ingrese la DNI a buscar: ";
                            cin >> dniBuscado;
                            bool encontrado = false;

                            for (int i = 0; i < cant; i++) {
                                Paciente reg = archivo.leer(i);
                                if (reg.getDni() == dniBuscado) {
                                    reg.mostrar();
                                    cout << "-----------------------" << endl;
                                    encontrado = true;
                                }
                            }
                            if (!encontrado) cout << "No se encontro ningun paciente con ese DNI." << endl;
                            system("pause");
                            break;
                        }
                        case 2: {
                            char osBuscada[20];
                            cout << "Ingrese la obra social a buscar: ";
                            cin >> osBuscada;
                            bool encontrado = false;

                            for (int i = 0; i < cant; i++) {
                                Paciente reg = archivo.leer(i);
                                if (reg.getObraSocial() == osBuscada) {
                                    reg.mostrar();
                                    cout << "-----------------------" << endl;
                                    encontrado = true;
                                }
                            }
                            if (!encontrado) cout << "No se encontraron pacientes con esa obra social." << endl;
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
                                Paciente reg = archivo.leer(i);
                                if (reg.getEstado() == estadoBool) {
                                    reg.mostrar();
                                    cout << "-----------------------" << endl;
                                    encontrado = true;
                                }
                            }
                            if (!encontrado) cout << "No se encontraron pacientes con ese estado." << endl;
                            system("pause");
                            break;
                        }
                        case 4: {
                            int idPacienteBuscado;
                            cout << "Ingrese el ID del paciente para consultar su historial medico: ";
                            cin >> idPacienteBuscado;

                            int posPac = archivo.buscarPorId(idPacienteBuscado);
                            if (posPac < 0) {
                                cout << "No existe un paciente registrado con el ID ingresado.\n";
                                system("pause");
                                break;
                            }

                            Paciente p = archivo.leer(posPac);
                            cout << "\n" << string(50, '=') << endl;
                            cout << "   HISTORIAL MEDICO DE: " << p.getApellido() << ", " << p.getNombre() << endl;
                            cout << string(50, '=') << endl;

                            HistorialArchivo histArch("datos/historialMedico.dat");
                            int cantHist = histArch.getCantidadRegistros();
                            bool encontrado = false;

                            for (int i = 0; i < cantHist; i++) {
                                HistorialMedico h = histArch.leer(i);
                                if (h.getIdPaciente() == idPacienteBuscado && h.getEstado()) {
                                    h.mostrar();
                                    cout << "--------------------------------------------------\n";
                                    encontrado = true;
                                }
                            }

                            if (!encontrado) {
                                cout << "El paciente no registra historiales medicos asociados.\n";
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
         case 0:
            break;
         default:
            cout << "Opcion invalida.\n";
            system("pause");
            break;
        }
    } while (opcion != 0);
}
