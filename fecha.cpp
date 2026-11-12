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
    bool fechaValida = false;
    int d, m, a;

    do {
        cout << "Anio: ";
        if (!(cin >> a) || a < 1900) {
            cout << "Error: Anio invalido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        //ValidaciOn del mes
        cout << "Mes (1 - 12): ";
        if (!(cin >> m) || m < 1 || m > 12) {
            cout << "Error: Mes invalido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int diasMaximos = 31;

        if (m == 4 || m == 6 || m == 9 || m == 11) { //SOLO ALGUNOS MESES TIENEN 31 DIAS
            diasMaximos = 30;
        }
        else if (m == 2) {
            bool esBisiesto = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
            diasMaximos = esBisiesto ? 29 : 28;
        }

        cout << "Dia (1 - " << diasMaximos << "): ";
        if (!(cin >> d) || d < 1 || d > diasMaximos) {
            cout << "Error: Dia invalido para el mes y anio ingresados.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        _anio = a;
        _mes = m;
        _dia = d;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar búfer
        fechaValida = true;

    } while (!fechaValida);
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
