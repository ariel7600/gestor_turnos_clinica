#ifndef MENUMANAGER_H_INCLUDED
#define MENUMANAGER_H_INCLUDED

class MenuManager {
public:
    void ejecutarMenuPrincipal();

private:
    void menuMedicos();
    void menuPacientes();
    void menuHorarios();
    void menuTurnos();
    void menuConsultas();
    void menuInformes();

};

#endif
