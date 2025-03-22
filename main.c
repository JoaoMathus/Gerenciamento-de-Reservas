#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    arranjo_reservas *arr = criar_arranjo();
    
    int menu;
    
    while (true) {
        printf("--- SISTEMA DE GERENCIAMENTO DE RESERVAS ---\n\n");
        printf("\033[0;34m");
        printf("1 - Cadastre uma nova reserva\n2 - Busque uma reserva\n3 - Remova uma reserva\n");
        printf("4 - Liste as reservas\n5 - Ordene as reservas\n6 - Encerre o programa\n");
        printf("\033[0m");
        
        scanf("%d", &menu);
        getchar();

        switch(menu) {
            case 1:
            char nome[124];
            printf("\nInsira o nome do hospede: ");
            fgets(nome, sizeof(nome), stdin);
            if ((strlen(nome) > 0) && (nome[strlen (nome) - 1] == '\n'))
                nome[strlen (nome) -1] = '\0';
            int quarto;
            printf("\nInsira o tipo do quarto (SINGLE = 0, DOUBLE = 1, SUITE = 2): ");
            scanf("%d", &quarto);
            DataDeCheckIn check;
            printf("\nInsira o dia de check in: ");
            scanf("%d", &check.dia);
            printf("\nInsira o mês de check in: ");
            scanf("%d", &check.mes);
            printf("\nInsira o ano de check in: ");
            scanf("%d", &check.ano);
            int prio;
            printf("\nInsira a prioridade de atendimento do hospede (VIP = 1, PADRAO = 2, ECONOMICO = 3): ");
            scanf("%d", &prio);
            cadastrar_reserva(arr, nome, quarto, check, prio);
            break;
            
            case 2:
            int search;
            printf("\nInsira o numero do ID que quer procurar: ");
            scanf("%d", &search);
            Reserva *r = buscar_por_id(arr, 0, arr->tamanho, search);
            if (r == NULL)
                puts("Reserva nao encontrada");
            else
            printf("ID: %d - Nome: %s Data de Check-In: %d/%d/%d - Prioridade: ", r->id, r->nomeHospede,
                r->dataCheckIn.dia, r->dataCheckIn.mes, r->dataCheckIn.ano);
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
            
            case 3:
            int removv;
            printf("\nInsira o número do ID que quer remover: ");
            scanf("%d", &removv);
            if (remover_por_id(arr, removv)) {
                printf("Removido com sucesso !\n");
            }
            else {
                printf("Hospede não foi removido. Digite o ID novamente.\n");
            }
            break;
            
            case 4:
            printar_todas(arr);
            break;
            
            case 5:
            ordernar_reservas(arr);
            break;
            
            case 6:
            printf("Obrigado por usar nosso programa !");
            exit(0);
            
            default:
            printf("Digite um valor correto, por favor.");
        }
    }
    destruir_arranjo(&arr);
    
    return 0;
}
