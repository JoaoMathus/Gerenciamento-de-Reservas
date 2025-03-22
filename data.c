/*
 * arquivo: data.c
 * resumo: implementação da função de comparação.
 */

#include "data.h" /* para data_t, data_comparar() */

/*
 *  Compara duas datas
 * 
 *  Recebe: struct data* (ponteiro/referência a uma struct data)
 *          struct data* (ponteiro/referência a uma struct data)
 *  Retorna: int     (int <  0  =>  d1 é menor que d2,
 *                    int == 0  =>  d1 é igual a d2,
 *                    int >  0  =>  d1 é maior que d2)
 */
int
data_comparar(const data_t* const d1, const data_t* const d2) {
    if (d1->ano < d2->ano)
    {
        return -1;
    }
    if (d1->ano > d2->ano)
    {
        return 1;
    }

    if (d1->mes < d2->mes)
    {
        return -1;
    }
    if (d1->mes > d2->mes)
    {
        return 1;
    }

    if (d1->dia < d2->dia)
    {
        return -1;
    }
    if (d1->dia > d2->dia)
    {
        return 1;
    }
    
    return 0; // são iguais
}