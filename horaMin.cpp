#include "horaMin.h"
#include <sstream>

HoraMin::HoraMin() : horaInicio(0), minInicio(0), horaFin(0), minFin(0) {}

HoraMin::HoraMin(int hIni, int mIni, int hFin, int mFin)
    : horaInicio(hIni), minInicio(mIni), horaFin(hFin), minFin(mFin) {}

int HoraMin::getHoraInicio() const { return horaInicio; }
int HoraMin::getMinInicio() const { return minInicio; }
int HoraMin::getHoraFin() const { return horaFin; }
int HoraMin::getMinFin() const { return minFin; }

void HoraMin::setHoraInicio(int h) { horaInicio = h; }
void HoraMin::setMinInicio(int m) { minInicio = m; }
void HoraMin::setHoraFin(int h) { horaFin = h; }
void HoraMin::setMinFin(int m) { minFin = m; }

void HoraMin::cargar() {
    bool horarioValido = false;
    int hInicio, mInicio, hFin, mFin;

    do {
        do {
            cout << "Hora inicio (0-23): ";
            if (!(cin >> hInicio) || hInicio < 0 || hInicio > 23) {
                cout << "Error: La hora de inicio debe estar entre 0 y 23.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            break;
        } while (true);

        do {
            cout << "Minuto inicio (0-59): ";
            if (!(cin >> mInicio) || mInicio < 0 || mInicio > 59) {
                cout << "Error: El minuto de inicio debe estar entre 0 y 59.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            break;
        } while (true);

        do {
            cout << "Hora fin (0-23): ";
            if (!(cin >> hFin) || hFin < 0 || hFin > 23) {
                cout << "Error: La hora de fin debe estar entre 0 y 59.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            break;
        } while (true);
        do {
            cout << "Minuto fin (0-59): ";
            if (!(cin >> mFin) || mFin < 0 || mFin > 59) {
                cout << "Error: El minuto de fin debe estar entre 0 y 59.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            break;
        } while (true);

        int totalMinutosInicio = (hInicio * 60) + mInicio;
        int totalMinutosFin = (hFin * 60) + mFin;

        if (totalMinutosInicio >= totalMinutosFin) {
            cout << "Error: El horario de inicio debe ser estrictamente menor al horario de fin.\n";
            horarioValido = false;
        } else {
            horaInicio = hInicio;
            minInicio = mInicio;
            horaFin = hFin;
            minFin = mFin;
            horarioValido = true;
        }

    } while (!horarioValido);

    cin.ignore(10000, '\n');
}

string HoraMin::toString() const {
    stringstream ss;
    ss << (horaInicio < 10 ? "0" : "") << horaInicio << ":"
       << (minInicio < 10 ? "0" : "") << minInicio << " hs a "
       << (horaFin < 10 ? "0" : "") << horaFin << ":"
       << (minFin < 10 ? "0" : "") << minFin << " hs";
    return ss.str();
}

void HoraMin::mostrar() const {
    cout << toString();
}


bool HoraMin::operator<(const HoraMin& b) const {

    int totalMinutosA = (this->horaInicio * 60) + this->minInicio;

    int totalMinutosB = (b.horaInicio * 60) + b.minInicio;

    return totalMinutosA < totalMinutosB;
}


HoraMin HoraMin::sumarMinutos(int minutosASumar) const {
    int totalMinutos = (horaInicio * 60) + minInicio + minutosASumar;
    int nuevaHora = (totalMinutos / 60) % 24;
    int nuevoMinuto = totalMinutos % 60;


    return HoraMin(nuevaHora, nuevoMinuto, nuevaHora, nuevoMinuto + 30);
}
