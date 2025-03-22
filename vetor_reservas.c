/*
 * arquivo: vetor_reservas.c
 * resumo: implementação dos prcedimentos definidos no
 *         arquivo header.
 */

#include <stdlib.h> /* para exit(), malloc(), free() */
#include <stdio.h>  /* para printf(), fprintf() */

#include "vetor_reservas.h"
#include "data.h"    /* para data_t, data_comparar() */
#include "reserva.h" /* para reserva_t, tipo_quarto_t, prioridade_t */

/*
 *  Cria a estrutura vetor_reservas que encapsula o vetor dinâmico.
 * 
 *  Recebe:  void
 *  Retorna: vetor_reservas* (um ponteiro para a estrutura alocada).
 */
vetor_reservas_t*
vetor_criar() {
    vetor_reservas_t* vec;

    vec = malloc(sizeof(vetor_reservas_t));
    if (vec == NULL) {
        fprintf(stderr, "ERRO: alocacao da estrutura de vetor de reservas falhou.\n");
        exit(1);
    }

    vec->vec = malloc(sizeof(reserva_t) * CAPACIDADE_INICIAL);
    if (vec->vec == NULL) {
        fprintf(stderr, "ERRO: alocacao do vetor de reservas falhou.\n");
        exit(1);
    }
    
    /* Preenchendo os dados da estrutura */
    vec->capacidade = CAPACIDADE_INICIAL;
    vec->tamanho = 0;

    return vec;
}

/*
 *  Libera memória alocada para a estrutura e para o vetor interior.
 * 
 *  Recebe:  vetor_reservas_t** (referência para o ponteiro para a estrutura).
 *  Retorna: void
 */
void
vetor_destruir(vetor_reservas_t** v) {
    if (v != NULL && *v != NULL) {
        free((*v)->vec);
        free(*v);
        *v = NULL;
    }
}

/*
 * Lista todas as reservas no vetor dinâmico.
 * 
 * Recebe:  const vetor_reservas_t* const (referência à estrutura do vetor)
 * Retorna: void
 */
void
vetor_listar(const vetor_reservas_t* const v) {
    for (size_t i = 0; i < v->tamanho; ++i) {
        printf("ID: %d - Nome: %s Data de Check-In: %d/%d/%d - Prioridade: ", v->vec[i].id, v->vec[i].nome_hospede,
            v->vec[i].data_checkin.dia, v->vec[i].data_checkin.mes, v->vec[i].data_checkin.ano);
        switch(v->vec[i].prioridade) {
            case 1:
                printf("VIP\n");
                break;
            case 2:
                printf("PADRAO\n");
                break;
            case 3:
                printf("ECONOMICO\n");
                break;
            default:
                printf("DESCONHECIDA\n");
                break;
        }
    }
}

/*
 *  Ordena reservas pela prioridade, e se forem iguais, ordena pela data de check-in
 * 
 *  Recebe:  vetor_reservas_t*   (referência a uma estrutura de vetor)
 *  Retorna: void
 */
void
vetor_ordenar(vetor_reservas_t* const v) {
    for (size_t i = 0; i < v->tamanho - 1; ++i) {
        size_t min = i;
        for (size_t j = i + 1; j < v->tamanho; ++j) {
            if (v->vec[j].prioridade == v->vec[min].prioridade) {
                if (data_comparar(&(v->vec[j].data_checkin), &(v->vec[min].data_checkin)) < 0) {
                    min = j;
                }
            }

            if (v->vec[j].prioridade < v->vec[min].prioridade) {
                min = j;
            }
        }
        reserva_t temp = v->vec[i];
        v->vec[i] = v->vec[min];
        v->vec[min] = temp;
    }
}

/*
 *  Remove uma reserva do vetor dinâmico
 * 
 *  Recebe: vetor_reservas_t*   (referência à estrutura de vetor)
 *          int                 (id da reserva que se quer remover)
 *  Retorna: int                (1 se deu certo, 0 se não há esse elemento)
 */
int
vetor_remover(vetor_reservas_t* const v, int id) {
    /* Se está na última posição */
    if (v->vec[v->tamanho - 1].id == id) {
        v->tamanho--; /* simplesmente decresce o tamanho */
        return 1;
    }

    /* Se está entre o primeiro e o penúltimo */
    for (size_t i = 0; i < v->tamanho; ++i) {
        if (v->vec[i].id == id) {
            for (size_t j = i; j < v->tamanho - 1; ++j) {
                v->vec[j] = v->vec[j + 1]; /* mudando o que resta para a esquerda */
            }
            v->tamanho -= 1;
            return 1;
        }
    }

    return 0; /* caso último: não há esse elemento */
}

/*
 *  Busca uma reserva por id
 * 
 *  Recebe: vetor_reservas*     (referência a uma estrutura de vetor)
 *          int                 (id da reserva que se quer remover)
 *  Retorna: reserva_t*         (ponteiro para a reserva encontrada) ou
 *           NULL               (se não foi encontrada reserva com o ID)
 */
reserva_t*
vetor_buscar(const vetor_reservas_t* const v, int id) {
    for (size_t i = 0; i < v->tamanho; ++i) {
        if (v->vec[i].id == id) {
            return &(v->vec[i]);
        }
    }

    return NULL; /* não há reserva com esse id */
}

/*
 *  Adiciona uma nova reserva no vetor dinâmico
 * 
 *  Recebe:  vetor_reservas_t* (referência para a estrutura do vetor dinâmico)
 *           const char*       (nome do hóspede)
 *           tipo_quarto_t     (tipo do quarto: SINGLE, DOUBLE, SUITE)
 *           data_t            (data da reserva)
 *           prioridade_t      (prioridade da reserva: VIP, PADRAO, ECONOMICO)
 *  Retorna: void
 */
void
vetor_adicionar(vetor_reservas_t* const v, const char* nome, data_t data, tipo_quarto_t quarto, prioridade_t prio) {
    size_t i;
    static size_t contador_de_id = 0;

    if (v->tamanho >= v->capacidade) {
        v->vec = realloc(v->vec, (CAPACIDADE_ADICIONAL + v->capacidade) * sizeof(reserva_t));
        v->capacidade += CAPACIDADE_ADICIONAL;
    }

    v->tamanho += 1;
    i = v->tamanho - 1;
    v->vec[i].id = ++contador_de_id;

    snprintf(v->vec[i].nome_hospede, sizeof(v->vec[i].nome_hospede), nome);

    v->vec[i].tipo_quarto = quarto;

    v->vec[i].data_checkin = data;
    v->vec[i].prioridade = prio;
}