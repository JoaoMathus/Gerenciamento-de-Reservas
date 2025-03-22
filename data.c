/*
 * arquivo: data.c
 * resumo: implementação da função de comparação.
 */

#include <stdio.h>

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

void
testar_data_comparar() {
	data_t cobaias[7][2] = {
		{ { 1, 2, 2002 }, { 1, 2, 2002 } },
		{ { 1, 1, 2001 }, { 1, 1, 2002 } },
		{ { 1, 1, 2001 }, { 1, 2, 2001 } },
		{ { 1, 1, 2001 }, { 2, 1, 2001 } },
		{ { 1, 1, 2002 }, { 1, 1, 2001 } },
		{ { 1, 2, 2001 }, { 1, 1, 2001 } },
		{ { 2, 1, 2001 }, { 1, 1, 2001 } }
	};
	int esperados[7] = { 0, -1, -1, -1, 1, 1, 1};
	int resultados[7] = { -2, -2, -2, -2, -2, -2, -2 };
	int todos_passaram = 1;
	
	for (int i = 0; i < (sizeof(esperados) / sizeof(int)); ++i) {
		resultados[i] = data_comparar(&cobaias[i][0], &cobaias[i][1]);
		if (resultados[i] == esperados[i]) {
			putchar('.');
		} else {
			putchar('*');
		}
	}
	putchar('\n');
	
	for (int i = 0; i < (sizeof(resultados) / sizeof(int)); ++i) {
		if (resultados[i] != esperados[i]) {
			printf("Teste [%d] NAO passou! Argumentos: {%d/%d/%d}, {%d/%d/%d}. Esperado: %d. Recebido: %d.\n",
				i, cobaias[i][0].dia, cobaias[i][0].mes, cobaias[i][0].ano, cobaias[i][1].dia, cobaias[i][1].mes,
				cobaias[i][1].ano, esperados[i], resultados[i]);
			
			todos_passaram = 0;
		}
	}
	
	if (todos_passaram) {
		printf("Todos os testes passaram!\n");
	}
}