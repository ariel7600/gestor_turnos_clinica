#ifndef MENUMANAGER_H_INCLUDED
#define MENUMANAGER_H_INCLUDED
#include <limits>
class MenuManager {
public:
    void MenuPrincipal();

private:
    void menuMedicos();
    void menuPacientes();
    void menuHorarios();
    void menuTurnos();
    void menuInformes();

};

#endif
