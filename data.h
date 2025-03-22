/*
 * arquivo: data.h
 * resumo: contém a estrutura data
 *         e a função de comparação.
 */

#ifndef DATA_H
#define DATA_H

typedef struct data {
    int dia;
    int mes;
    int ano;
} data_t;

int data_comparar(const data_t* const d1, const data_t* const d2);
void testar_data_comparar();

#endif /* DATA_H */