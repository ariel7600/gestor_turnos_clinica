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
    cout << "Hora inicio (0-23): "; cin >> horaInicio;
    cout << "Minuto inicio (0-59): "; cin >> minInicio;
    cout << "Hora fin (0-23): "; cin >> horaFin;
    cout << "Minuto fin (0-59): "; cin >> minFin;
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
