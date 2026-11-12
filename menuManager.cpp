#include "MenuManager.h"
#include "medico.h"
#include "medicoArchivo.h"
#include "horaMin.h"
#include "horarioAtencion.h"
#include "horarioAtencionArchivo.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void MenuManager::MenuPrincipal() {
    int opcion=-1;
    do {
        system("cls");
        cout << "\n========================================\n";
        cout << "     SISTEMA DE GESTION CLINICA\n";
        cout << "========================================\n";
        cout << "1 - Gestion de Medicos\n";
        cout << "2 - Gestion de Pacientes\n";
        cout << "3 - Horarios de Atencion y Agenda\n";
        cout << "4 - Gestion de Turnos\n";
        cout << "5 - Informes y Reportes\n";
        cout << "0 - Salir del Sistema\n";
        cout << "----------------------------------------\n";

        cout<< "Ingrese un valor (0-5): ";
        cin>>opcion;

        switch (opcion) {
            case 1:
                menuMedicos();
                break;
            case 2:
                menuPacientes();
                break;
            case 3:
                menuHorarios();
                break;
            case 4:
                menuTurnos();
                break;
            case 5:
                menuInformes();
                break;
            case 0:
                cout << "\nGracias por utilizar el sistema.\n";
                break;
            default:{
                cout << "\nOpcion invalida. Presione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            }
        }
    } while (opcion != 0);
}

void MenuManager::menuMedicos() {

    int opcion=-1;
    MedicoArchivo archivo("medico.dat");
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
        cin>>opcion;

        switch (opcion) {
            case 1:{
                system("cls");
                cout << "=== ALTA DE MEDICO ===" << endl;
                Medico reg;

                // Asigna ID
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
                int id;
                cout << "Ingrese el ID del medico para dar de baja: ";
                cin >> id;

                int pos = archivo.buscarPorId(id);
                if (pos >= 0) {
                    Medico reg = archivo.leer(pos);
                    if (reg.getEstado()) {
                        cout << "\nDatos del medico:" << endl;
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
                cout << "=== LISTADO DE MEDICOS (Ordenados por Apellido y Especialidad) ===" << endl;
                int cant = archivo.getCantidadRegistros();

                if (cant <= 0) {
                    cout << "No hay medicos registrados." << endl;
                    system("pause");
                    break;
                }

                Medico* vec = new Medico[cant];
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
                        string ap1 = vec[j].getApellido();
                        string ap2 = vec[j+1].getApellido();

                        if (ap1 > ap2) {
                            intercambiar = true;
                        } else if (ap1 == ap2) {
                            if (vec[j].getIdEspecialidad() > vec[j+1].getIdEspecialidad()) {
                                intercambiar = true;
                            }
                        }

                        if (intercambiar) {
                            Medico aux = vec[j];
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
                    cin >> subOpcion;

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

void MenuManager::menuPacientes() {
    int opcion=-1;
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
        cin>>opcion;

        switch (opcion) {
            case 1: /* alta de paciente */ break;
            case 2: /* modificar */ break;
            case 3: /* baja lógica */ break;
            case 4: /* Mostrar a listado */ break;
            case 5: /* consulta por dni, obra social o estado, mostrar historial Medico*/ break;
        }
    } while (opcion != 0);
}
void MenuManager::menuHorarios() {
     int opcion;
     HorarioAtencionArchivo archivo("horarios.dat");
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
        cin>>opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:{
                system("cls");
                cout << "=== ALTA DE HORARIO MEDICO ===" << endl;
                HorarioAtencion reg;

                // Asigna ID
                int nuevoId = archivo.getCantidadRegistros() + 1;
                reg.setIdHorario(nuevoId);

                reg.cargar();
                reg.setEstado(true);

                if (archivo.guardar(reg)) {
                    cout << "\nHorario medico guardado exitosamente con ID: " << nuevoId << endl;
                } else {
                    cout << "\nError al guardar el horario medico en el archivo." << endl;
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
                char nuevoTexto[100];
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
                            cin >> opcion;
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
                        cout << "\nMedico modificado exitosamente." << endl;
                    } else {
                        cout << "\nError al actualizar el registro." << endl;
                    }
                } else {
                     cout << "\nNo existe un Horario medico registrado con el ID ingresado." << endl;
                }

                system("pause");
                break;
            }
            case 3: {system("cls");
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
            };
            case 5: /* consulta DE AGENDA por matricula medico, rango de fecha*/ break;
        }
    } while (opcion != 0);
}
void MenuManager::menuTurnos() {
    int opcion;
    do {
        cout << "\n========================================\n";
        cout << "        GESTION DE TURNOS\n";
        cout << "========================================\n"
                  << "1 - Alta de Turno\n"
                  << "2 - Modificar Turno\n"
                  << "3 - Baja Logica de Turno\n"
                  << "4 - Listar todos los Turnos\n"
                  << "5 - Consultas\n"
                  << "0 - Volver al Menu Principal\n";
        int opcion=0;
        cout<<"Ingrese una opcion (0-5): ";
        cin>>opcion;

        switch (opcion) {
            case 1: /* alta de turno */ break;
            case 2: /* modificar */ break;
            case 3: /* baja lógica */ break;
            case 4: /* Mostrar a listado */ break;
            case 5: /* consulta por rango de fechas, por paciente, por medico, por estado Turno*/ break;
        }
    } while (opcion != 0);
}
void MenuManager::menuInformes() {
   int opcion;
    do {
        cout << "\n========================================\n";
        cout << "           INFORMES\n";
        cout << "========================================\n"
                  << "1 - Recaudacion por mes\n"
                  << "2 - Recaudacion por medico\n"
                  << "3 - Cantidad de turnos por especialidad\n"
                  << "4 - Cantidad de turnos por Estado\n"
                  << "5 - Cantidad de turnos por Obra Social\n"
                  << "0 - Volver al Menu Principal\n";
        int opcion=0;
        cout<<"Ingrese una opcion (0-5): ";
        cin>>opcion;

        switch (opcion) {
            case 1: /* recaudacion mes */ break;
            case 2: /* recaudacion medico */ break;
            case 3: /* cantidad de turnos especialidad */ break;
            case 4: /* cantidad de turnos por estado */ break;
            case 5: /* cantidad de turnos por OS*/ break;
        }
    } while (opcion != 0);
}
