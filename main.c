#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"           /* para data_t */
#include "vetor_reservas.h" /* para vetor_reservas_t, e todos os procedimentos */

int menu_principal();
void input_nome(char* nome, size_t tamanho);

int main() {
    vetor_reservas_t* arr = vetor_criar();
    int menu;
    
    for (;;) {
		menu = menu_principal();
		
        switch(menu) {
			/* Cadastrar nova reserva */
            case 1: {
                char nome[128];
                int quarto;
                data_t checkin;
                int prio;
				
				input_nome(nome, 128);
                
                printf("\nInsira o tipo do quarto (SINGLE = 0, DOUBLE = 1, SUITE = 2): ");
                scanf("%d", &quarto);

                printf("\nInsira o dia de check in: ");
                scanf("%d", &checkin.dia);

                printf("\nInsira o mes de check in: ");
                scanf("%d", &checkin.mes);

                printf("\nInsira o ano de check in: ");
                scanf("%d", &checkin.ano);

                printf("\nInsira a prioridade de atendimento do hospede (VIP = 1, PADRAO = 2, ECONOMICO = 3): ");
                scanf("%d", &prio);

                vetor_adicionar(arr, nome, checkin, quarto, prio);
                break;
            }
            /* Buscar reserva por ID */
            case 2: {
                int search;
                reserva_t* r;

                printf("\nInsira o numero do ID que quer procurar: ");
                scanf("%d", &search);

                r = vetor_buscar(arr, search);
                if (r == NULL) {
                    puts("Reserva nao encontrada.");
                } else {
                    printf("ID: %d - Nome: %s Data de Check-In: %d/%d/%d - Prioridade: ", r->id, r->nome_hospede,
                           r->data_checkin.dia, r->data_checkin.mes, r->data_checkin.ano);
                }

                switch(r->prioridade) {
                    case 1:
                        printf("VIP\n");
                        break;
                    case 2:
                        printf("PADRAO\n");
                        break;
                    case 3:
                        printf("ECONOMICO\n");
                        break;
                }
                break;
            }
            /* Remover reserva por ID */
            case 3: {
                int removv;

                printf("\nInsira o numero do ID que quer remover: ");
                scanf("%d", &removv);

                if (vetor_remover(arr, removv)) {
                    printf("Removido com sucesso !\n");
                }
                else {
                    printf("Hospede nao foi encontrado. Tente outro ID.\n");
                }
                break;
            }
            
            case 4:
                vetor_listar(arr);
                break;
            
            case 5:
                vetor_ordenar(arr);
                break;
            
            case 6:
                printf("Obrigado por usar nosso programa !");
                exit(0);
            
            default:
                printf("Digite um valor correto, por favor.");
                break;
        }
    }
    vetor_destruir(&arr);
    
    return 0;
}

/*
 *  Menu de navegação do sistema.
 *
 *  Recebe:  void
 *  Retorna: int 	(resposta do usuário)
 */
int
menu_principal() {
	int resposta;
	
	printf("--- SISTEMA DE GERENCIAMENTO DE RESERVAS ---\n\n");
	printf("\033[0;34m");
	printf("1 - Cadastre uma nova reserva\n2 - Busque uma reserva\n3 - Remova uma reserva\n");
	printf("4 - Liste as reservas\n5 - Ordene as reservas\n6 - Encerre o programa\n");
	printf("\033[0m");
	
	scanf("%d", &resposta);
	getchar();
	
	return resposta;
}

/*
 *  Recebe como input o nome do hóspede da nova reserva.
 *
 *  Recebe:  char* 	(cadeia de char para armazenar o nome)
 *  Retorna: void
 */
void
input_nome(char* nome, size_t tamanho) {
	printf("\nInsira o nome do hospede: ");
	fgets(nome, tamanho, stdin);
	if ((strlen(nome) > 0) && (nome[strlen (nome) - 1] == '\n')) {
		nome[strlen (nome) - 1] = '\0';
	}
}