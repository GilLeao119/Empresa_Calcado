#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Machado.h"
#include "input.h"

void menu_ini() {
    printf("\n------------------\n");
    printf("0 - Sair\n");
    printf("1 - Cliente\n");
    printf("2 - Administrador\n");
    printf("------------------\n");
}

void menu_cli() {
    printf("\n------------------\n");
    printf("0 - Voltar atrás\n");
    printf("1 - Login\n");
    printf("2 - Criar Conta\n");
    printf("------------------\n");
}

void menu_adm() {
    printf("\n--------------------------------\n");
    printf("0 - Voltar atrás.\n");
    printf("1 - C.R.U.D. de clientes.\n");
    printf("2 - C.R.U.D. de artigos.\n");
    printf("3 - C.R.U.D. das tabelas de custo.\n");
    printf("--------------------------------\n");
}

void menu_crud_cli() {
    printf("\n--------------------------------\n");
    printf("0 - Voltar atrás.\n");
    printf("1 - Criar clientes.\n");
    printf("2 - Listar clientes.\n");
    printf("3 - Editar clientes.\n");
    printf("4 - Eleminar clientes.\n");
    printf("--------------------------------\n");
}

void menu_crud_artigos() {
    printf("\n--------------------------------\n");
    printf("0 - Voltar atrás.\n");
    printf("1 - Criar artigos.\n");
    printf("2 - Listar artigos.\n");
    printf("3 - Editar artigos.\n");
    printf("4 - Eleminar artigos.\n");
    printf("--------------------------------\n");
}

void menu_crud_precos() {
    printf("\n--------------------------------\n");
    printf("0 - Voltar atrás.\n");
    printf("1 - Editar precos.\n");
    printf("--------------------------------\n");
}

void Menu_edit_especifico() {
    printf("\n--------------------------------\n");
    printf("0 - Voltar atrás.\n");
    printf("1 - editar mao de obra.\n");
    printf("2 - editar custo fixo.\n");
    printf("3 - editar lucro.\n");
    printf("4 - editar preço de numero.\n");
    printf("--------------------------------\n");
}

void msg_error() {
    printf("Digite novamente. Ocorreu um erro!\n");
}

void msg_adeus() {
    system("clear");
    printf("Obrigado e volte sempre.\nCalçado Machado - De manhã não abre, à tarde está fechado.");
}

int procurarCliente(Clientes clientes, int Cod_Cli) {
    int i;
    for (i = 0; i < clientes.contador; i++) {
        if (clientes.clientes[i].Cod_Cli == Cod_Cli) {
            return i;
        }
    }
    return -1;
}

int inserirCliente(Clientes *clientes) {
    int Cod_Cli = obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_CLI);
    int Nif = obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NIF);
    if (procurarCliente(*clientes, Cod_Cli) == -1) {
        clientes->clientes[clientes->contador].Cod_Cli = Cod_Cli;
        lerString(clientes->clientes[clientes->contador].Nome, MAX_NOME_CLI, MSG_OBTER_NOME);
        lerString(clientes->clientes[clientes->contador].Apelido, MAX_APELIDO_CLI, MSG_OBTER_APELIDO);
        clientes->clientes[clientes->contador].Nif = Nif;
        lerString(clientes->clientes[clientes->contador].Pais, MAX_PAIS_CLI, MSG_OBTER_PAIS);
        return clientes->contador++;
    }
    return -1;
}

void inserirClientes(Clientes *clientes) {
    if (clientes->contador < MAX_CLI) {
        if (inserirCliente(clientes) == -1) {
            puts(ERRO_CLI_EXISTE);
        }
    } else {
        puts(ERRO_LISTA_CHEIA);
    }
}

void atualizarAluno(Cliente *cliente) {
    lerString((*cliente).Nome, MAX_NOME_CLI, MSG_OBTER_NOME);
    lerString((*cliente).Apelido, MAX_NOME_CLI, MSG_OBTER_APELIDO);
    (*cliente).Nif = obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NIF);
    lerString((*cliente).Pais, MAX_PAIS_CLI, MSG_OBTER_PAIS);
}

void editarClientes(Clientes *clintes) {
    int numero = procurarCliente(*clintes, obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_CLI));
    if (numero != -1) {
        atualizarAluno(&(*clintes).clientes[numero]);
    } else {
        puts(ERRO_CLI_NAO_EXISTE);
    }
}

void apagarDadosCliente(Cliente *cliente) {
    cliente->Cod_Cli = 0;
    strcpy(cliente->Nome, "");
    strcpy(cliente->Apelido, "");
    cliente->Nif = 0;
    strcpy(cliente->Pais, "");
}

void eliminarClientes(Clientes *clientes) {
    int i, numero = procurarCliente(*clientes, obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_CLI));
    if (numero != -1) {
        for (i = numero; i < clientes->contador - 1; i++) {
            clientes->clientes[i] = clientes->clientes[i + 1];
        }
        apagarDadosCliente(&clientes->clientes[i]);
        clientes->contador--;
    } else {
        puts(ERRO_CLI_NAO_EXISTE);
    }
}

int procurarClientes(Clientes clientes) {
    int numero = procurarCliente(clientes, obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_CLI));
    if (numero != -1) {
        return 1;
    } else {
        puts(ERRO_CLI_NAO_EXISTE);
        return 0;
    }
}

void imprimirCliente(Cliente cliente) {
    printf("\n%d %s %s %d %s", cliente.Cod_Cli, cliente.Nome, cliente.Apelido, cliente.Nif, cliente.Pais);
}

void listarClientes(Clientes clientes) {
    if (clientes.contador > 0) {
        int i;
        for (i = 0; i < clientes.contador; i++) {
            imprimirCliente(clientes.clientes[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}




int procurarArtigo(Artigos artigos, int Cod_Art) {
    int i;
    for (i = 0; i < artigos.contador; i++) {
        if (artigos.artigos[i].Cod_Art == Cod_Art) {
            return i;
        }
    }
    return -1;
}

int inserirArtigo(Artigos *artigos) {
    int Cod_Art = obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_ART);
    if (procurarArtigo(*artigos, Cod_Art) == -1) {
        artigos->artigos[artigos->contador].Cod_Art = Cod_Art;
        lerString(artigos->artigos[artigos->contador].Nome, MAX_NOME_CLI, MSG_OBTER_NOME_CAL);
        lerString(artigos->artigos[artigos->contador].Tip_Cal, MAX_APELIDO_CLI, MSG_OBTER_TIP_CAL);
        artigos->artigos[artigos->contador].Min = obterInt(MIN_Min, MAX_Min, MSG_OBTER_MIN);
        artigos->artigos[artigos->contador].Max = obterInt(artigos->artigos[artigos->contador].Min, MAX_Max, MSG_OBTER_MAX);
        artigos->artigos[artigos->contador].Mao_obra = obterInt(MIN_OBRA, MAX_OBRA, MSG_OBTER_MAO_OBRA);
        artigos->artigos[artigos->contador].Custo_fix = obterInt(MIN_FIX, MAX_FIX, MSG_OBTER_CUSTO_FIX);
        artigos->artigos[artigos->contador].lucro = obterFloat(MIN_LUCRO, MAX_LUCRO, MSG_OBTER_LUCRO);
        int quantidade = artigos->artigos[artigos->contador].Max - artigos->artigos[artigos->contador].Min + 1;
        int tamanho = artigos->artigos[artigos->contador].Min;
        float custo;
        for(int j = 0; j < quantidade; j++){
            printf("insira o custo adicional do tamanho numero %d: ",tamanho);
            tamanho++;
            scanf("%f",&custo);
            artigos->artigos[artigos->contador].tamanhos[j] = custo;
        }
        return artigos->contador++;
    }
    return -1;
}

void inserirArtigos(Artigos *artigos) {
    if (artigos->contador < MAX_ART) {
        if (inserirArtigo(artigos) == -1) {
            puts(ERRO_ART_EXISTE);
        }
    } else {
        puts(ERRO_LISTA_CHEIA_ART);
    }
}

void atualizarArtigo(Artigo *artigo) {
    lerString((*artigo).Nome, MAX_NOME_CLI, MSG_OBTER_NOME_CAL);
    lerString((*artigo).Tip_Cal, MAX_NOME_CLI, MSG_OBTER_TIP_CAL);
    (*artigo).Max = obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_MAX);
    (*artigo).Min = obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_MIN);
}

void editarArtigos(Artigos *artigos) {
    int numero = procurarArtigo(*artigos, obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_ART));
    if (numero != -1) {
        atualizarArtigo(&(*artigos).artigos[numero]);
    } else {
        puts(ERRO_ART_NAO_EXISTE);
    }
}

void apagarDadosArtigo(Artigo *artigo) {
    artigo->Cod_Art = 0;
    strcpy(artigo->Nome, "");
    strcpy(artigo->Tip_Cal, "");
    artigo->Max = 0;
    artigo->Min = 0;
}

void eliminarArtigos(Artigos *artigos) {
    int i, numero = procurarArtigo(*artigos, obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_ART));
    if (numero != -1) {
        for (i = numero; i < artigos->contador - 1; i++) {
            artigos->artigos[i] = artigos->artigos[i + 1];
        }
        apagarDadosArtigo(&artigos->artigos[i]);
        artigos->contador--;
    } else {
        puts(ERRO_ART_NAO_EXISTE);
    }
}

int procurarArtigos(Artigos artigos) {
    int numero = procurarArtigo(artigos, obterInt(MIN_COD_CLI, MAX_COD_CLI, MSG_OBTER_COD_ART));
    if (numero != -1) {
        return 1;
    } else {
        puts(ERRO_ART_NAO_EXISTE);
        return 0;
    }
}

void imprimirArtigo(Artigo artigo) {
    printf("\n%d, %s, %s, %d, %d;", artigo.Cod_Art, artigo.Nome, artigo.Tip_Cal, artigo.Max, artigo.Min);
}

void listarArtigos(Artigos artigos) {
    if (artigos.contador > 0) {
        int i;
        for (i = 0; i < artigos.contador; i++) {
            imprimirArtigo(artigos.artigos[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA_ART);
    }
}





void imprimirArtigoPreco(Artigo artigo,int num) {
    printf("\n%d - %d %s %s %d %d %f",++num ,artigo.Cod_Art, artigo.Nome, artigo.Tip_Cal, artigo.Mao_obra, artigo.Custo_fix, artigo.lucro);
}

int menu_edit_precos(Artigos artigos) {
    if (artigos.contador > 0) {
        int i, Menu_Edit = 0;
        printf("\n0 - voltar atras");
        do{
            for (i = 0; i < artigos.contador; i++) {
                imprimirArtigoPreco(artigos.artigos[i], i);
            }
            printf("\n");
            scanf("%d",&Menu_Edit);
            system("clear");
            if(Menu_Edit < 0 || Menu_Edit > ++(artigos.contador)){
                msg_error();
            }
        }while(Menu_Edit < 0 || Menu_Edit > ++(artigos.contador));
        return Menu_Edit;
    } else {
        puts(ERRO_LISTA_VAZIA_ART);
        return -1;
    }
}

void imprimirArtigoTamanho(Artigo artigo,int num) {
    
}

int menu_edit_tamanhos(Artigos artigos, int sim){
    int tamanhos = artigos.artigos[sim].Max - artigos.artigos[sim].Min;
        int i, Menu_Tamanhos = 0;
        printf("\n0 - voltar atras");
        do{
            int i = 0;
            while(i <= tamanhos){
                int tamanho = artigos.artigos->Min + i;
                printf("\n%d - %d %f",i + 1, tamanho , artigos.artigos->tamanhos[i]);
                i++;
            }
            printf("\n");
            scanf("%d",&Menu_Tamanhos);
            system("clear");
            if(Menu_Tamanhos < 0 || Menu_Tamanhos > tamanhos + 1){
                msg_error();
            }
        }while(Menu_Tamanhos < 0 || Menu_Tamanhos > tamanhos + 1);
        return Menu_Tamanhos;
}

void alteraPrecoMaoObra(Artigos *artigos,int sim){
    artigos->artigos[sim].Mao_obra = obterInt(MIN_OBRA, MAX_OBRA, MSG_OBTER_MAO_OBRA);
}

void alteraPrecoFixo(Artigos *artigos,int sim){
    artigos->artigos[sim].Custo_fix = obterInt(MIN_FIX, MAX_FIX, MSG_OBTER_CUSTO_FIX);
}

void alteraPrecoLucro(Artigos *artigos,int sim){
    artigos->artigos[sim].lucro = obterFloat(MIN_LUCRO, MAX_LUCRO, MSG_OBTER_LUCRO);
}

void alteraPrecoTamanho(Artigos *artigos, int sim, int nao){
    artigos->artigos[sim].tamanhos[nao] = obterFloat(0, 10, MSG_OBTER_TAMANHO);
}

