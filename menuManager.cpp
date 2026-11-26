#include "MenuManager.h"
#include <iostream>
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


