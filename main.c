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

typedef struct
{
    int dia;
    int mes;
    int ano;
} DataDeCheckIn;

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
    DataDeCheckIn dataCheckIn;
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
int comparar_reservas_por_data(Reserva *r1, Reserva *r2);
void cadastrar_reserva(
    arranjo_reservas *ar,
    char *nome,
    enum TipoQuarto tipo,
    DataDeCheckIn data,
    enum Prioridade prioridade
);
Reserva *buscar_por_id(arranjo_reservas *arr, int comeco, int fim, int id);
bool remover_por_id(arranjo_reservas *arr, int id);

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
        printf("\n");

        switch(menu) {
            case 1:
            /*Aqui vai a função cadastrar()*/
            printf("Não está feito.\n");
            break;
            
            case 2:
            /*Aqui vai a função buscar()*/
            printf("Não está feito também.\n");
            break;
            
            case 3:
            /*Aqui vai a função remover()*/
            printf("Dá pra acreditar? Não está feito.");
            break;
            
            case 4:
            printar_todas(arr);
            break;
            
            case 5:
            ordernar_reservas(arr);
            
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
        printf("ID: %d - Nome: %s Data de Check-In: %d/%d/%d\n", arranjo->reservas[i].id, arranjo->reservas[i].nomeHospede,
            arranjo->reservas[i].dataCheckIn.dia, arranjo->reservas[i].dataCheckIn.mes, arranjo->reservas[i].dataCheckIn.ano);
    }
}

/**
 *  Ordena reservas pela prioridade, e se forem iguais, ordena pela data de check-in
 * 
 *  Recebe: arranjo_reservas*   (ponteiro/referência a uma struct arranjo_reservas)
 *  Retorna: void
 */
void ordernar_reservas(arranjo_reservas *arranjo)
{
    for (int i = 0; i < arranjo->tamanho - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < arranjo->tamanho; j++)
        {
            if (arranjo->reservas[j].prioridade == arranjo->reservas[min].prioridade)
            {
                if (comparar_reservas_por_data(&(arranjo->reservas[j]), &(arranjo->reservas[min])) < 0)
                {
                    min = j;
                }
            }

            if (arranjo->reservas[j].prioridade < arranjo->reservas[min].prioridade)
                min = j;
        }
        Reserva temp = arranjo->reservas[i];
        arranjo->reservas[i] = arranjo->reservas[min];
        arranjo->reservas[min] = temp;
    }
}

/**
 *  Compara duas reservas com base na data de check-in
 * 
 *  Recebe: Reserva* (ponteiro/referência a uma struct Reserva)
 *          Reserva* (ponteiro/referência a uma struct Reserva)
 *  Retorna: int     (int < 0 => r1 é menor que r2,
 *                    int == 0 -> r1 é igual a r2,
 *                    int > 0 => r1 é maior que r2)
 */
int comparar_reservas_por_data(Reserva *r1, Reserva *r2)
{
    if (r1->dataCheckIn.ano < r2->dataCheckIn.ano)
    {
        return -1;
    }
    if (r1->dataCheckIn.ano > r2->dataCheckIn.ano)
    {
        return 1;
    }

    if (r1->dataCheckIn.mes < r2->dataCheckIn.mes)
    {
        return -1;
    }
    if (r1->dataCheckIn.mes > r2->dataCheckIn.mes)
    {
        return 1;
    }

    if (r1->dataCheckIn.dia < r2->dataCheckIn.dia)
    {
        return -1;
    }
    if (r1->dataCheckIn.dia > r2->dataCheckIn.dia)
    {
        return 1;
    }
    
    return 0; // são iguais
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
    DataDeCheckIn data,
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

    ar->reservas[i].dataCheckIn = data;
    ar->reservas[i].prioridade = prioridade;
}

/**
 *  Busca uma reserva por id usando a pesquisa binária
 * 
 *  Recebe: arranjo_reservas*   (ponteiro/referência a uma struct de arranjo de reservas)
 *          int                 (índice do começo do arranjo [sempre 0 ao envocar o algoritmo])
 *          int                 (índice do fim do arranjo [tamanho do arranjo])
 *          int                 (id da reserva que se quer achar)
 *  Retorna: Reserva*           (ponteiro para a reserva encontrada) ou
 *           NULL               (se não foi encontrada reserva com o ID)
 */
Reserva *buscar_por_id(arranjo_reservas *arr, int comeco, int fim, int id)
{
    if (fim >= comeco)
    {
        int meio = comeco + (fim - comeco) / 2;

        if (arr->reservas[meio].id == id)  // se o ID do meio é o que você procura...
            return &(arr->reservas[meio]); // achou!
        else if (arr->reservas[meio].id > id) // senão, se o ID do meio é maior...
            return buscar_por_id(arr, comeco, meio - 1, id); // busca na metade esquerda
        
        return buscar_por_id(arr, meio + 1, fim, id); // senão, busca na metade direita
    }

    return NULL; // não há reserva com esse id
}

/**
 *  Remove uma reserva do arranjo dinâmico
 * 
 *  Recebe: arranjo_reservas*   (ponteiro/referência à estrutura arranjo_reservas)
 *          int                 (id da reserva que se quer remover)
 *  Retorna: bool               (true se deu certo, false se não há esse elemento)
 */
bool remover_por_id(arranjo_reservas *arr, int id)
{
    // Se está na última posição
    if (arr->reservas[arr->tamanho - 1].id == id)
    {
        arr->tamanho--; // simplesmente decresce o tamanho
        return true;
    }
    // Se está entre o primeiro e o penúltimo
    for (int i = 0; i < arr->tamanho; i++)
    {
        if (arr->reservas[i].id == id)
        {
            for (int j = i; j < arr->tamanho - 1; j++)
            {
                arr->reservas[j] = arr->reservas[j + 1]; // mudando o que resta para a esquerda
            }
            arr->tamanho--;
            return true;
        }
    }

    return false; // caso último: não há esse elemento
}