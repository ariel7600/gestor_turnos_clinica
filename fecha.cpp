#include "Fecha.h"
#include <sstream>

using namespace std;

Fecha::Fecha() : _dia(0), _mes(0), _anio(0) {}

Fecha::Fecha(int dia, int mes, int anio) : _dia(dia), _mes(mes), _anio(anio) {}

int Fecha::getDia() const { return _dia; }
int Fecha::getMes() const { return _mes; }
int Fecha::getAnio() const { return _anio; }

void Fecha::setDia(int dia) { _dia = dia; }
void Fecha::setMes(int mes) { _mes = mes; }
void Fecha::setAnio(int anio) { _anio = anio; }

void Fecha::cargar() {
    cout << "Dia: ";
    cin >> _dia;
    cout << "Mes: ";
    cin >> _mes;
    cout << "Anio: ";
    cin >> _anio;
}

void Fecha::mostrar() const {
    cout << toString();
}

string Fecha::toString() const {
    stringstream ss;
    ss << (_dia < 10 ? "0" : "") << _dia << "/"
       << (_mes < 10 ? "0" : "") << _mes << "/"
       << _anio;
    return ss.str();
}

bool Fecha::operator==(const Fecha& otra) const {
    return (_dia == otra._dia && _mes == otra._mes && _anio == otra._anio);
}

bool Fecha::operator<(const Fecha& otra) const {
    if (_anio != otra._anio) return _anio < otra._anio;
    if (_mes != otra._mes) return _mes < otra._mes;
    return _dia < otra._dia;
}

bool Fecha::operator<=(const Fecha& otra) const {
    return (*this < otra) || (*this == otra);
}
