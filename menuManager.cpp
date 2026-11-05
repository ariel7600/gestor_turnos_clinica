#include "MenuManager.h"
#include <iostream>
using namespace std;

void MenuManager::ejecutarMenuPrincipal() {
    int opcion;
    do {
        cout << "\n========================================\n";
        cout << "     SISTEMA DE GESTION CLINICA\n";
        cout << "========================================\n";
        cout << "1 - Gestion de Medicos\n";
        cout << "2 - Gestion de Pacientes\n";
        cout << "3 - Horarios de Atencion y Agenda\n";
        cout << "4 - Gestion de Turnos\n";
        cout << "5 - Consultas\n";
        cout << "6 - Informes y Reportes\n";
        cout << "0 - Salir del Sistema\n";
        cout << "----------------------------------------\n";

        int opcion=0;
        cout<< "Ingrese un valor (0-6): ";
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
                menuConsultas();
                break;
            case 6:
                menuInformes();
                break;
            case 0:
                cout << "\nGracias por utilizar el sistema.\n";
                break;
        }
    } while (opcion != 0);
}

void MenuManager::menuMedicos() {
    int opcion;
    do {
        cout << "\n--- GESTION DE MEDICOS ---\n"
                  << "1 - Alta de Medico\n"
                  << "2 - Modificar Medico\n"
                  << "3 - Baja Logica de Medico\n"
                  << "4 - Listar todos los Medicos\n"
                  << "0 - Volver al Menu Principal\n";
        int opcion=0;
        cout<<"Ingrese una opcion (0-4): ";
        cin>>opcion;

        switch (opcion) {
            case 1: /* alta de médico */ break;
            case 2: /* modificar */ break;
            case 3: /* baja lógica */ break;
            case 4: /* Mostrar a listado */ break;
        }
    } while (opcion != 0);
}

void MenuManager::menuPacientes() { /* Submenú similar */ }
void MenuManager::menuHorarios() { /* Submenú similar */ }
void MenuManager::menuTurnos() { /* Submenú similar */ }
void MenuManager::menuConsultas() { /* Llama al módulo de Consultas */ }
void MenuManager::menuInformes() { /* Llama al módulo de Informes */ }
