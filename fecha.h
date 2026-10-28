#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>
#include <string>

class Fecha {
private:
    int _dia;
    int _mes;
    int _anio;

public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Setters
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    void cargar();
    void mostrar() const;
    std::string toString() const;

    // Operadores de comparación para comparar fechas
    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
};

#endif // FECHA_H_INCLUDED
