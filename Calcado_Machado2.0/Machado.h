#ifndef MACHADO_H
#define MACHADO_H

#define ERRO_CLI_NAO_EXISTE "O cliente não existe na lista."
#define ERRO_LISTA_VAZIA "A lista de clientes está vazia."
#define ERRO_LISTA_CHEIA "A lista de clientes está cheia."
#define ERRO_CLI_EXISTE "O número de aluno já se encontra atribuído."

#define ERRO_ART_NAO_EXISTE "O artigo não existe na lista."
#define ERRO_LISTA_VAZIA_ART "A lista de artigos está vazia."
#define ERRO_LISTA_CHEIA_ART "A lista de artigos está cheia."
#define ERRO_ART_EXISTE "O número do artigo já se encontra atribuído."

#define MAX_CLI 50
#define MAX_ART 50
#define MIN_COD_CLI 0
#define MAX_COD_CLI 100
#define MAX_NIF 999999999 
#define MIN_NIF 100000000
#define MIN_Min 34
#define MAX_Min 48
#define MAX_Max 55
#define MIN_LUCRO 0.0
#define MIN_OBRA 0
#define MIN_FIX 0
#define MAX_FIX 15
#define MAX_OBRA 15
#define MAX_LUCRO 100
#define MSG_OBTER_MAO_OBRA "Insira o preço da mao de obra: "
#define MSG_OBTER_CUSTO_FIX "Insira o preço do custo fixo: "
#define MSG_OBTER_LUCRO "Insira o lucro: "
#define MSG_OBTER_COD_CLI "Insira um codigo de cliente: "
#define MSG_OBTER_PAIS "Insira a nacionalidade do cliente: "
#define MSG_OBTER_NIF "Insira o seu nif: "
#define MAX_PAIS_CLI 15
#define MAX_NOME_CLI 31
#define MAX_APELIDO_CLI 31
#define MSG_OBTER_APELIDO "Insira o apelido do cliente: "
#define MSG_OBTER_NOME "Insira o nome do cliente: "

#define MSG_OBTER_COD_ART "Insira o codigo do artigo: "
#define MSG_OBTER_TIP_CAL "Insira o tipo de calçado: "
#define MSG_OBTER_NOME_CAL "Insira o nome do calçado: "
#define MSG_OBTER_MIN "Insira o menor tamanho: "
#define MSG_OBTER_MAX "Insira o maior tamanho: "
#define MSG_OBTER_TAMANHO "Insira a nova percentagem: "

#define MIN_NUM_CLIENTE 0
#define MAX_NUM_CLIENTE 100
#define MSG_OBTER_COD_CLIENTE "qual o seu codigo de cliente?"
#define MAX_NOME_CLIENTE 10
#define ERRO_CLI_EXISTE "O número de cliente já se encontra atribuído."

void menu_ini();
void menu_cli();
void menu_adm();
void menu_crud_cli();
void menu_crud_artigos();
void menu_crud_precos();
void Menu_edit_especifico();
void msg_error();
void msg_adeus();

typedef struct {
    int Cod_Cli;
    char Nome[10];
    char Apelido[10];
    int Nif;
    char Pais[15];
} Cliente;

typedef struct {
    int contador;
    Cliente clientes[100];
} Clientes;

typedef struct {
    int Cod_Art;
    char Nome[15];
    char Tip_Cal[10];
    int Min;
    int Max;
    int Mao_obra;
    int Custo_fix;
    float lucro;
    float tamanhos[12];
} Artigo;

typedef struct {
    int contador;
    Artigo artigos[100];
} Artigos;

void inserirClientes(Clientes *clientes);
int procurarClientes(Clientes clientes);
void listarClientes(Clientes clientes);
void editarClientes(Clientes *clientes);
void eliminarClientes(Clientes *clientes);

void inserirArtigos(Artigos *artigos);
int procurarArtigos(Artigos artigos);
void listarArtigos(Artigos artigos);
void editarArtigos(Artigos *artigos);
void eliminarArtigos(Artigos *artigos);

int menu_edit_precos(Artigos artigos);
int menu_edit_tamanhos(Artigos artigos, int sim);
void alteraPrecoMaoObra(Artigos *artigos,int sim);
void alteraPrecoFixo(Artigos *artigos,int sim);
void alteraPrecoLucro(Artigos *artigos,int sim);
void alteraPrecoTamanho(Artigos *artigos, int sim, int nao);

#endif /* MACHADO_H */

