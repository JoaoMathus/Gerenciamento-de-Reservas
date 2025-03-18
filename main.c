#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CAPACIDADE_INICIAL 8
#define CAPACIDADE_ADICIONAL 16

/**
 *  Macro para economizar linhas de códigos.
 * 
 *  Parâmetros: o tipo do que vai ser alocado,
 *              o símbolo (variável) ponteiro,
 *              número de elementos para alocar.
 * 
 *  Aloca memória e verifica se deu tudo certo.
 *  A sintaxe é meio estranha, mas confia em mim.
 * 
 *  Exemplo: alocar 5 inteiros:
 *      int *ptr;
 *      ALOCAR_MEMORIA(int, ptr, 5);
 */
#define ALOCAR_MEMORIA(tipo, simbolo, numero_de_elementos) \
    do { \
        if ((numero_de_elementos) == 0) { \
            fprintf(stderr, "ERRO: alocacao de zero elementos.\n"); \
            exit(1); \
        } \
        if ((numero_de_elementos) < 0) { \
            fprintf(stderr, "ERRO: alocacao de um numero negativo de elementos.\n"); \
            exit(1); \
        } \
        (simbolo) = (tipo *)malloc(sizeof(tipo) * (numero_de_elementos)); \
        if (simbolo == NULL) { \
            fprintf(stderr, "ERRO: falha ao alocar memoria.\n"); \
            exit(1); \
        } \
    } while (0)

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

/**
 *  Registro de reserva
 * 
 *  Campos: id,
 *          nome do hóspede que fez a reserva,
 *          tipo do quarto reservado,
 *          data na qual o check-in foi feito,
 *          prioridade do hóspede.
 */
typedef struct
{
    int id;
    char nomeHospede[124];
    enum TipoQuarto tipoQuarto;
    char dataCheckIn[124];
    enum Prioridade prioridade;
} Reserva;

/**
 *  Registro para um arranjo dinâmico de reservas
 * 
 *  Campos: um arranjo dinâmico para as reservas,
 *          tamanho atual do arranjo,
 *          capicade máxima atual do arranjo.
 */
typedef struct
{
    Reserva *reservas;
    size_t tamanho;
    size_t capacidade;
} arranjo_reservas;

// AMALDIÇOADO: usando variável global para a lógica dos IDs
static long long contador_de_id = 0;

arranjo_reservas *criar_arranjo();
void destruir_arranjo(arranjo_reservas **p_arranjo);
void printar_todas(arranjo_reservas *arranjo);
void ordernar_reservas(arranjo_reservas *arranjo);
int comparar_reservas(Reserva *r1, Reserva *r2);
void cadastrar_reserva(
    arranjo_reservas *ar,
    char *nome,
    enum TipoQuarto tipo,
    char *data,
    enum Prioridade prioridade
);

int main()
{
    arranjo_reservas *arr = criar_arranjo();

    cadastrar_reserva(arr, "Alomomola", SINGLE, "02/03/2003", VIP);
    cadastrar_reserva(arr, "Gabodor", DOUBLE, "02/03/2200", ECONOMICO);

    printar_todas(arr);
    printf("%d\n", arr->tamanho);

    destruir_arranjo(&arr);
    
    return 0;
}

/**
 *  Cria um novo arranjo alocando memória para ele e para
 *  o arranjo interior.
 * 
 *  Recebe: void
 *  Retorna: arranjo_reservas* (um ponteiro para o arranjo alocado).
 */
arranjo_reservas *criar_arranjo()
{
    arranjo_reservas *arr;
    ALOCAR_MEMORIA(arranjo_reservas, arr, 1); // alocando a estrutura que encapsula o arranjo

    ALOCAR_MEMORIA(Reserva, arr->reservas, CAPACIDADE_INICIAL); // alocando o arranjo em si
    
    /* Preenchendo os dados da estrutura */
    arr->capacidade = CAPACIDADE_INICIAL; // capacidade máxima atual
    arr->tamanho = 0; // tamanho atual

    return arr;
}

/**
 *  Libera memória alocada para um arranjo de reservas.
 * 
 *  Recebe: arranjo_reservas** (ponteiro para um ponteiro para o arranjo).
 *  Retorna: void
 */
void destruir_arranjo(arranjo_reservas **referencia_ao_arranjo)
{
    if (referencia_ao_arranjo && *referencia_ao_arranjo)
    {
        free((*referencia_ao_arranjo)->reservas);
        free(*referencia_ao_arranjo);
        *referencia_ao_arranjo = NULL; // evitar acesso após o free()
    }
}

void printar_todas(arranjo_reservas *arranjo)
{
    for (size_t i = 0; i < arranjo->tamanho; i++)
    {
        printf("ID: %d - Nome: %s\n", arranjo->reservas[i].id, arranjo->reservas[i].nomeHospede);
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

// TODO: Modificar essa função para comparar prioridade ou data.
/**
 *  Compara duas reservas com base no ID
 * 
 *  Recebe: Reserva* (ponteiro/referência a uma struct Reserva)
 *          Reserva* (ponteiro/referência a uma struct Reserva)
 *  Retorna: int     (int < 0 => r1 é menor que r2,
 *                    int == 0 -> r1 é igual a r2,
 *                    int > 0 => r1 é maior que r2)
 */
int comparar_reservas(Reserva *r1, Reserva *r2)
{
    if (r1->id < r2->id) return -1;
    else if (r1->id == r2->id) return 0;
    else return 1;
}

/**
 *  Adiciona uma nova reserva no arranjo dinâmico
 * 
 *  Recebe: arranjo_reservas* (ponteiro/referência para o arranjo dinâmico)
 *          const char*       (nome do hóspede)
 *          enum TipoQuarto   (tipo do quarto: SINGLE, DOUBLE, SUITE)
 *          const char*       (data da reserva)
 *          enum Prioridade   (prioridade da reserva: VIP, PADRAO, ECONOMICO)
 *  Retorna: void
 */
void cadastrar_reserva(
    arranjo_reservas *ar,
    char *nome,
    enum TipoQuarto tipo,
    char *data,
    enum Prioridade prioridade)
{
    // Variável local pra deixar o código mais legível
    int i;

    if (ar->tamanho == ar->capacidade)
    {
        ar->reservas = realloc(ar->reservas, (CAPACIDADE_ADICIONAL + ar->capacidade) * sizeof(Reserva));
        ar->capacidade += CAPACIDADE_ADICIONAL;
    }

    ar->tamanho += 1;
    i = ar->tamanho - 1;
    ar->reservas[i].id = contador_de_id++;

    // Sendo o mais seguro possível
    // Copiando a string nome para o campo nomeHospede
    strncpy(ar->reservas[i].nomeHospede, nome, sizeof(ar->reservas[i].nomeHospede) - 1);
    ar->reservas[i].nomeHospede[sizeof(ar->reservas[i].nomeHospede) - 1] = '\0';

    ar->reservas[i].tipoQuarto = tipo;

    // Sendo o mais seguro possível novamente
    // Copiando a string data para o campo dataCheckIn
    strncpy(ar->reservas[i].dataCheckIn, data, sizeof(ar->reservas[i].dataCheckIn) - 1);
    ar->reservas[i].dataCheckIn[sizeof(ar->reservas[i].dataCheckIn) - 1] = '\0';
    ar->reservas[i].prioridade = prioridade;
}
