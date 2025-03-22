/*
 * arquivo: reserva.h
 * resumo: contém o tipo reserva_t e as enums prioridade_t
 *         e tipo_quarto_t.
 */

#ifndef RESERVA_H
#define RESERVA_H

#include "data.h" /* para data_t */

typedef enum prioridade {
    VIP = 1,
    PADRAO,
    ECONOMICO
} prioridade_t;

typedef enum tipo_quarto {
    SINGLE = 0,
    DUPLO,
    SUITE
} tipo_quarto_t;

typedef struct reserva {
    int id;
    char nome_hospede[64];
    data_t data_checkin;
    prioridade_t prioridade;
    tipo_quarto_t tipo_quarto;
} reserva_t;

#endif /* RESERVA_H */