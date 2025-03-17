#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
enum TipoQuarto
{
    SINGLE = 0,
    DOUBLE,
    SUITE
};
enum Prioridade
{
    VIP = 1,
    PADRAO,
    ECONOMICO
};
typedef struct
{
    int id;
    char nomeHospede[124];
    enum TipoQuarto tipoQuarto;
    char dataCheckIn[124];
    enum Prioridade prioridade;
} Reserva;

typedef struct
{
    Reserva reservas[1024];
    size_t tamanho;
    size_t capacidade;
} arranjo_reservas;

void printar_todas(arranjo_reservas arranjo);
void ordernar_reservas(arranjo_reservas *arranjo);

int main()
{

    arranjo_reservas arranjo;
    arranjo.tamanho = 0;
    arranjo.capacidade = 1024;

    arranjo.reservas[0].id = 0;
    strcpy(arranjo.reservas[0].nomeHospede, "Alomomola");
    arranjo.reservas[0].tipoQuarto = SINGLE;
    strcpy(arranjo.reservas[0].dataCheckIn, "02/02/2020");
    arranjo.reservas[0].prioridade = PADRAO;
    arranjo.tamanho++;

    arranjo.reservas[1].id = 2;
    strcpy(arranjo.reservas[1].nomeHospede, "Travis");
    arranjo.reservas[1].tipoQuarto = SINGLE;
    strcpy(arranjo.reservas[1].dataCheckIn, "07/08/2021");
    arranjo.reservas[1].prioridade = PADRAO;
    arranjo.tamanho++;

    arranjo.reservas[2].id = 1;
    strcpy(arranjo.reservas[2].nomeHospede, "Lixo");
    arranjo.reservas[2].tipoQuarto = SINGLE;
    strcpy(arranjo.reservas[2].dataCheckIn, "04/05/2022");
    arranjo.reservas[2].prioridade = PADRAO;
    arranjo.tamanho++;

    printar_todas(arranjo);
    ordernar_reservas(&arranjo);
    puts("-----------------------------------------------");
    printar_todas(arranjo);

    return 0;
}

void printar_todas(arranjo_reservas arranjo)
{
    for (size_t i = 0; i < arranjo.tamanho; i++)
    {
        printf("ID: %d - Nome: %s\n", arranjo.reservas[i].id, arranjo.reservas[i].nomeHospede);
    }
}

void ordernar_reservas(arranjo_reservas *arranjo)
{
    for (int i = 0; i < arranjo->tamanho - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < arranjo->tamanho; j++)
        {
            if (arranjo->reservas[j].id < arranjo->reservas[min].id)
                min = j;
        }
        Reserva temp = arranjo->reservas[i];
        arranjo->reservas[i] = arranjo->reservas[min];
        arranjo->reservas[min] = temp;
    }
}
