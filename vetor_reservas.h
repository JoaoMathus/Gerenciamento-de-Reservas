/*
 * arquivo: vetor_reservas.h
 * resumo: contém o tipo vetor_reservas e
 *         procedimentos referentes a ele.
 */

#ifndef VETOR_RESERVAS_H
#define VETOR_RESERVAS_H

#include <stdlib.h>  /* para size_t */

#include "reserva.h" /* para reserva_t, tipo_quarto_t, prioridade_t */
#include "data.h"    /* para data_t */

#define CAPACIDADE_INICIAL 8
#define CAPACIDADE_ADICIONAL 16

typedef struct vetor_reservas {
    reserva_t* vec;
    size_t tamanho;
    size_t capacidade;
} vetor_reservas_t;

vetor_reservas_t* vetor_criar();
void vetor_destruir(vetor_reservas_t** v);
void vetor_listar(const vetor_reservas_t* const v);
void vetor_ordenar(vetor_reservas_t* const v);
int vetor_remover(vetor_reservas_t* const v, int id);
reserva_t* vetor_buscar(const vetor_reservas_t* cosnt, int id);
void vetor_adicionar(vetor_reservas_t* const v, const char* nome, data_t data, tipo_quarto_t quarto, prioridade_t prio);

#endif /* VETOR_RESERVAS_H */