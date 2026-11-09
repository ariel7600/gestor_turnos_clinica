#ifndef ESTADOTURNO_H_INCLUDED
#define ESTADOTURNO_H_INCLUDED

enum class EstadoTurno : int {
    ASIGNADO = 1,
    ATENDIDO = 2,
    CANCELADO = 3,
    AUSENTE = 4
};

#endif
