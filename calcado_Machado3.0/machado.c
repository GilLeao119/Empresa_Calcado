#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "machado.h"

/**
 * Esta função permite ao cliente referir o grau de satisfação com o pedido
 * @param ficheiro o argumento da função
 */
void grau(char *ficheiro){
    int grau;
    do {
        printf("\n------------------------------------------------"
                "------------");
        printf("\n1 - ★");
        printf("\n2 - ★★");
        printf("\n3 - ★★★");
        printf("\n4 - ★★★★");
        printf("\n5 - ★★★★★");
        printf("\n0 - Sair");
        printf("\n------------------------------------------------"
                "------------");

        printf("\nOpcão: ");
        scanf("%d", &grau);
    }while(grau < 0 || grau > 5);
    if(grau == 0){
    }else{
        FILE *fpp = fopen(ficheiro, "a");
        fclose(fpp);
        FILE *fp = fopen(ficheiro, "w");
        if (fp == NULL) {
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "grau de satisfaçao: %d ★\n", grau);
        fclose(fp);
    }
}
/**
 * Esta função permite ler os clientes disponiveis no ficheiro
 * @param clientes o primeiro argumento
 * @param ficheiro o segundo argumento
 * @return falso se falhar a carregar o ficheiro e true se carregar ficheiro
 */
int carregarClientes(Clientes *clientes, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        fread(&clientes->contador, sizeof (int), 1, fp);

        if (clientes->contador > 0) {
            clientes->clientes = (Cliente*) malloc(clientes->contador * sizeof (Cliente));
            fread(clientes->clientes, sizeof (Cliente), clientes->contador, fp);

            clientes->tamanho = clientes->contador;

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            clientes->clientes = (Cliente*) malloc(CLIENTES_TAM_INICIAL * sizeof (Cliente));
            clientes->contador = 0;
            clientes->tamanho = CLIENTES_TAM_INICIAL;
            fclose(fp);

            sucesso = 1;
        }
    }

    return sucesso;
}
/**
 * Esta função liberta o espaço que não está a ser ocupado
 * 
 * @param clientes o único argumento da função
 */
void libertarClientes(Clientes * clientes) {
    free(clientes->clientes);
}
/**
 * Esta função permite atualizar o contador dos clientes no ficheiro
 * 
 * @param contador o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarContadorFX(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}
/**
 * Esta função insere os clientes no ficheiro
 * 
 * @param clientes o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void inserirClienteFX(Clientes clientes, char *ficheiro) {
    atualizarContadorFX(clientes.contador, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&clientes.clientes[clientes.contador - 1], sizeof (Cliente), 1, fp);

    fclose(fp);
}
/**
 * Esta função permite atualizar os clientes no ficheiro
 * 
 * @param clientes o primeiro argumento da função
 * @param indice o segundo argumento da função
 * @param ficheiro o terceiro argumento da função
 */
void atualizarClienteFX(Clientes clientes, int indice, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(fp, sizeof (int), SEEK_SET);

    fseek(fp, sizeof (Cliente) * indice, SEEK_CUR);

    fwrite(&clientes.clientes[indice], sizeof (Cliente), 1, fp);
}
/**
 * Esta função permite remover os clientes do ficheiro
 * 
 * @param clientes o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void removerClienteFX(Clientes clientes, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&clientes.contador, sizeof (int), 1, fp);
    fwrite(clientes.clientes, sizeof (Cliente), clientes.contador, fp);
}
/**
 * Esta função permite realocar o espaço previamente alocado com um novo tamanho
 * 
 * @param clientes o único argumento da função
 */
void expandirClientes(Clientes *clientes) {
    Cliente *temp = (Cliente*) realloc(clientes->clientes, sizeof (Cliente) * (clientes->tamanho * 2));
    if (temp != NULL) {
        clientes->tamanho *= 2;
        clientes->clientes = temp;
    }
}
/**
 * Esta função permite inserir clientes e encontra-se dentro de outra 
 * função, "inserirClientes",
 * 
 * @param clientes o único argumento da função
 * @return adiciona mais um no contador para a memória dinâmica
 */
int inserirCliente(Clientes *clientes) {
    int conta;    
    if(clientes->contador > 0){
        conta = clientes->clientes[(clientes->contador)-1].cod_cli;
    }else{
        conta = -1;
    }
    
    clientes->clientes[clientes->contador].cod_cli = ++conta;

    int nif = obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NIF);
    
    for (int i = 0; i < clientes->contador; i++) {
        if (clientes->clientes[i].nif == nif) {
            puts(ERRO_CLIENTE_EXISTE);
            return clientes->contador;
        }
    }
    clientes->clientes[clientes->contador].nif = nif;
    
    lerString(clientes->clientes[clientes->contador].nome, MAX_NOME_CLIENTE, MSG_OBTER_NOME);

    lerString(clientes->clientes[clientes->contador].pais, MAX_NOME_CLIENTE, MSG_OBTER_PAIS);

    clientes->clientes[clientes->contador].ativa = 1;
    
    return clientes->contador++;
}
/**
 * Esta função tem outras funções que estão dentro de if e de else que permite 
 * entrar dentro das outras funções caso seja válido
 * 
 * @param clientes o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void inserirClientes(Clientes *clientes, char *ficheiro) {
    if (clientes->contador == clientes->tamanho) {
        expandirClientes(clientes);
    }
    
        if (inserirCliente(clientes) == -1) {
            puts(ERRO_CLIENTE_EXISTE);
        } else {
            inserirClienteFX(*clientes, ficheiro);
        }
}
/**
 * Esta função permite escrever o cliente pedido
 * @param cliente o único argumento da função
 */
void imprimirCliente(Cliente cliente) {
    if(cliente.ativa == 1){
        printf("\n%d %s %d %s", cliente.cod_cli, cliente.nome, cliente.nif, cliente.pais);
    }
}
/**
 * Esta função permite confirmar se o cliente existe
 * 
 * @param clientes o primeiro argumento da função
 * @param cod_cli o segundo argumento da função
 * @return se o cliente existir retorna i, caso nao exista retorna -1
 */
int procurarCliente(Clientes clientes, int cod_cli) {
    int i;
    for (i = 0; i < clientes.contador; i++) {
        if (clientes.clientes[i].cod_cli == cod_cli) {
            return i;
        }
    }
    return -1;
}
/**
 * Esta função permite ao admnistrador procurar os clientes com conta já criada,
 * com a função "procurarCliente" e depois com uma função ja especificada 
 * para os imprimir "imprimirCliente"
 * 
 * @param clientes o único argumento da função
 */
void procurarClientes(Clientes clientes) {
    int cod_cli = procurarCliente(clientes, obterInt(VAL_MIN, clientes.contador - 1, MSG_OBTER_NUM_CLIENTE));

    if (cod_cli != -1) {
        imprimirCliente(clientes.clientes[cod_cli]);
    } else {
        puts(ERRO_CLIENTE_NAO_EXISTE);
    }
}
/**
 * Esta função permite procurar os clientes que deram login se ja existem, 
 * ou seja, se já tem aquele nif atribuido
 * 
 * @param clientes o primeiro argumento da função
 * @param nif o segundo argumento da função
 * @return  -1 caso nao exista o cliente e i caso exista 
 */
int procurarClienteLog(Clientes clientes, int nif) {
    int i;
    for (i = 0; i < clientes.contador; i++) {
        if (clientes.clientes[i].nif == nif) {
            return i;
        }
    }
    return -1;
}
/**
 * Obtemos o NIF a partir da função "procurarClienteLog" e darmos return
 * @param clientes o único argumento da função
 * @return nif se existir um cliente com este nif e -1 se nao existir
 */
int procurarClientesLog(Clientes clientes) {
    int nif = procurarClienteLog(clientes, obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NIF));

    if (nif != -1) {
        return nif;
    } else {
        return -1;
    }
}
/**
 * Esta função permite atualizar os dados dos clientes caso pretendam
 * 
 * @param cliente o único argumento da função
 */
void atualizarCliente(Cliente *cliente) {
    (*cliente).nif = obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NIF);
    lerString((*cliente).nome, MAX_NOME_CLIENTE, MSG_OBTER_NOME);
    lerString((*cliente).pais, MAX_NOME_CLIENTE, MSG_OBTER_PAIS);
}
/**
 * Esta função engloba várias funções que caso a função procurarCliente retorne
 * -1 o cliente irá ser atualizado no programa e no ficheiro, tal como as 
 * funções atualizarCliente e atualizarClienteFX fazem
 * @param clientes o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarClientes(Clientes *clientes, char *ficheiro) {
    int cod_cli = procurarCliente(*clientes, obterInt(VAL_MIN, 
            clientes->contador - 1, MSG_OBTER_NUM_CLIENTE));

    if (cod_cli != -1) {
        atualizarCliente(&(*clientes).clientes[cod_cli]);

        atualizarClienteFX(*clientes, cod_cli, ficheiro);
    } else {
        puts(ERRO_CLIENTE_NAO_EXISTE);
    }
}
/**
 * Esta função permite apagar os dados que o admnistrador pretenda
 * 
 * @param cliente o único argumento da função
 */
void apagarDadosCliente(Cliente *cliente) {
    if(cliente->ativa == 0){
        cliente->ativa = 1;
    }else{
        cliente->ativa = 0;
    }
}
/**
 * Esta função permite remover clientes, englobando outras funções
 * 
 * @param clientes o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void removerClientes(Clientes *clientes, char *ficheiro) {
    int i, cod_cli = procurarCliente(*clientes, obterInt(VAL_MIN, clientes->contador - 1, MSG_OBTER_NUM_CLIENTE));

    if (cod_cli != -1) {
        for (i = cod_cli; i < clientes->contador - 1; i++) {
            clientes->clientes[i] = clientes->clientes[i + 1];
        }

        apagarDadosCliente(&clientes->clientes[i]);
        clientes->contador--;

        removerClienteFX(*clientes, ficheiro);
    } else {
        puts(ERRO_CLIENTE_NAO_EXISTE);
    }
}
/**
 * Esta função permite listar os clientes já criados
 * 
 * @param clientes o único argumento da função
 */
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
/**
 * Esta função permite imprimir todos os dados do artigo
 * @param artigo 
 */
void imprimirArtigo(Artigo artigo) {
    printf("\n%d %s %d %d %d", artigo.cod_art, artigo.nome, artigo.tip_cal, artigo.min, artigo.max);
}

/**
 * Esta função permite carregar os artigos do ficheiro 
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 * @return falso se falhar a carregar o ficheiro e true se carregar ficheiro
 */
int carregarArtigos(Artigos *artigos, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        fread(&artigos->contador, sizeof (int), 1, fp);

        if (artigos->contador > 0) {
            artigos->artigos = (Artigo*) malloc(artigos->contador * sizeof (Artigo));
            fread(artigos->artigos, sizeof (Artigo), artigos->contador, fp);

            artigos->tamanho = artigos->contador;

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            artigos->artigos = (Artigo*) malloc(CLIENTES_TAM_INICIAL * sizeof (Artigo));
            artigos->contador = 0;
            artigos->tamanho = CLIENTES_TAM_INICIAL;
            fclose(fp);

            sucesso = 1;
        }
    }

    return sucesso;
}
/**
 * Esta função liberta o espaço que nao está a ser ocupado
 * @param artigos o único argumento da função
 */
void libertarArtigos(Artigos * artigos) {
    free(artigos->artigos);
}
/**
 * Esta função permite atualizar o contador dos artigos no ficheiro
 * @param contador o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarContadorFX_art(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}
/**
 * Esta função permite inserir novos artigos que o admnistrador pretenda
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void inserirArtigoFX(Artigos artigos, char *ficheiro) {
    atualizarContadorFX_art(artigos.contador, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&artigos.artigos[artigos.contador - 1], sizeof (Artigo), 1, fp);

    fclose(fp);
}
/**
 * Esta função permite atualizar os artigos nos ficheiros
 * @param artigos o primeiro argumento da função
 * @param indice o segundo argumento da função
 * @param ficheiro o terceiro argumento da função
 */
void atualizarArtigoFX(Artigos artigos, int indice, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(fp, sizeof (int), SEEK_SET);

    fseek(fp, sizeof (Artigo) * indice, SEEK_CUR);

    fwrite(&artigos.artigos[indice], sizeof (Artigo), 1, fp);
}
/**
 * Esta função permite remover os artigos no ficheiro
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void removerArtigoFX(Artigos artigos, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&artigos.contador, sizeof (int), 1, fp);
    fwrite(artigos.artigos, sizeof (Artigo), artigos.contador, fp);
}
/**
 * Esta função que carrega os valores padrões, devido a erros na leitura do excel
 * @param artigos o único argumento da função
 */
void carrega_val(Artigos *artigos){
    
    for(int i = 0; i < 3; i++){
        artigos->artigos[artigos->contador].cod_art = i;
        if(i == 0){
            strcpy(artigos->artigos[artigos->contador].nome, "sapatos");
            artigos->artigos[artigos->contador].mao_obra = 5;
            artigos->artigos[artigos->contador].custo_fix = 3;
            artigos->artigos[artigos->contador].lucro = 0.3;
        }if(i == 1){
            strcpy(artigos->artigos[artigos->contador].nome, "sandalias");
            artigos->artigos[artigos->contador].mao_obra = 4;
            artigos->artigos[artigos->contador].custo_fix = 3;
            artigos->artigos[artigos->contador].lucro = 0.2;
        }if(i == 2){
            strcpy(artigos->artigos[artigos->contador].nome, "botas");
            artigos->artigos[artigos->contador].mao_obra = 6;
            artigos->artigos[artigos->contador].custo_fix = 3;
            artigos->artigos[artigos->contador].lucro = 0.4;
        }
        artigos->artigos[artigos->contador].max = 48;
        artigos->artigos[artigos->contador].min = 34;
        artigos->artigos[artigos->contador].tip_cal = i;
        for(int k = 0; k < 15; k++){
            if(i == 0){
                artigos->artigos[artigos->contador].tamanhos[k] = 0.65 + (0.05 * k);
            }else if(i == 1){
                artigos->artigos[artigos->contador].tamanhos[k] = 0.8 + (0.025 * k);
            }else{
                artigos->artigos[artigos->contador].tamanhos[k] = 0.7 + (0.05 * k);
            }

        }
    artigos->contador++;
    }
}
/**
 * Esta função permite inserir novos artigos
 * @param artigos o primeiro argumento da função
 * @return mais 1 no contador para a memória dinâmica
 */
int inserirArtigo(Artigos *artigos) {
    int conta;    
    if(artigos->contador > 0){
        conta = artigos->artigos[(artigos->contador)-1].cod_art;
    }else{
        conta = -1;
    }
    artigos->artigos[artigos->contador].cod_art = ++conta;
    
    lerString(artigos->artigos[artigos->contador].nome, MAX_NOME_ARTIGO, "");
    lerString(artigos->artigos[artigos->contador].nome, MAX_NOME_ARTIGO, MSG_OBTER_NOME_ARTIGO);
    
    do {
        printf("1 - sapato");
        printf("\n2 - sandalia");
        printf("\n3 - botas");
        printf("\nopçao: ");
        scanf("%d",&(artigos->artigos[artigos->contador].tip_cal));
    } while((artigos->artigos[artigos->contador].tip_cal) < 1 || (artigos->artigos[artigos->contador].tip_cal) > 3);

    artigos->artigos[artigos->contador].min = obterInt(MIN_MIN, MAX_MIN, MSG_OBTER_MIN);
    artigos->artigos[artigos->contador].max = obterInt(artigos->artigos[artigos->contador].min, MAX_MAX, MSG_OBTER_MAX);

    artigos->artigos[artigos->contador].mao_obra = obterInt(0, MAX_NIF, MSG_OBTER_MAO_OBRA);
    artigos->artigos[artigos->contador].custo_fix = obterInt(0, MAX_NIF, MSG_OBTER_CUSTO_FIXO);
    artigos->artigos[artigos->contador].lucro = obterFloat(0, MAX_NIF, MSG_OBTER_LUCRO);

    int quantidade = artigos->artigos[artigos->contador].max - artigos->artigos[artigos->contador].min + 1;
    int tamanho = artigos->artigos[artigos->contador].min;
    float custo;

    for(int j = 0; j < quantidade; j++){
        printf("insira o custo adicional do tamanho numero %d: ",tamanho);
        tamanho++;
        scanf("%f",&custo);
        artigos->artigos[artigos->contador].tamanhos[j] = custo;
    }

    return artigos->contador++;
}
/**
 * Esta função permite atualizar os artigos
 * @param artigo o primeiro argumento da função
 */
void atualizarArtigo(Artigo *artigo) {
    lerString((*artigo).nome, MAX_NOME_ARTIGO, MSG_OBTER_NOME);
    do {
        printf("1 - sapato");
        printf("\n2 - sandalia");
        printf("\n3 - botas");
        printf("\nopçao: ");
        scanf("%d", &((*artigo).tip_cal));
    } while((*artigo).tip_cal < 1 || (*artigo).tip_cal > 3);
}
/**
 * Esta função permite expandir o tamanho caso nao haja mais espaço para 
 * novos artigos
 * 
 * @param artigos o primeiro argumento da função
 */
void expandirArtigos(Artigos *artigos) {
    Artigo *temp = (Artigo*) realloc(artigos->artigos, sizeof (Artigo) * (artigos->tamanho * 2));
    if (temp != NULL) {
        artigos->tamanho *= 2;
        artigos->artigos = temp;
    }
}
/**
 * Esta função permite inserir novos artigos usando as outras funções, 
 * dependendo se entre nos if`s ou não
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void inserirArtigos(Artigos *artigos, char *ficheiro) {
    if (artigos->contador == artigos->tamanho) {
        expandirArtigos(artigos);
    }
    
        if (inserirArtigo(artigos) == -1) {
            puts(ERRO_CLIENTE_EXISTE);
        } else {
            inserirArtigoFX(*artigos, ficheiro);
        }
}
/**
 * Esta função confirma se os artigos existem
 * @param artigos o primeiro argumento da função
 * @param cod_art o segundo argumento da função
 * @return i para a função "procurarArtigos" saber se teve sucesso na procura 
 * e -1 caso não tenha
 */
int procurarArtigo(Artigos artigos, int cod_art) {
    int i;
    for (i = 0; i < artigos.contador; i++) {
        if (artigos.artigos[i].cod_art == cod_art) {
            return i;
        }
    }
    return -1;
}
/**
 * Esta função verifica se há o artigo pretendido e caso haja imprime o artigo
 * @param artigos o primeiro argumento da função
 */
void procurarArtigos(Artigos artigos) {
    int cod_art = procurarArtigo(artigos, obterInt(VAL_MIN, artigos.contador - 1, MSG_OBTER_NUM_ART));

    if (cod_art != -1) {
        imprimirArtigo(artigos.artigos[cod_art]);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}
/**
 * Esta função permite verificar se existe o artigo e caso haja atualiza o que 
 * o admnistrador pretender
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarArtigos(Artigos *artigos, char *ficheiro) {
    int cod_art = procurarArtigo(*artigos, obterInt(VAL_MIN,
            artigos->contador - 1, MSG_OBTER_NUM_ART));

    if (cod_art != -1) {
        atualizarArtigo(&(*artigos).artigos[cod_art]);

        atualizarArtigoFX(*artigos, cod_art, ficheiro);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}
/**
 * Esta função permite apagar artigos
 * @param artigo o primeiro argumento da função
 */
void apagarArtigo(Artigo *artigo){
    artigo->cod_art = 0;
    artigo->custo_fix = 0;
    artigo->lucro = 0;
    artigo->mao_obra = 0;
    //artigo->nome = '';
    int tam = artigo->max - artigo->min;
    for(int i = 0; i < tam; i++){
        artigo->tamanhos[i] = 0;
    }
    artigo->max = 0;
    artigo->min = 0;
    artigo->tip_cal = 0;
}
/**
 * Esta função caso haja os artigos selecionados irá remover os artigos, 
 * tal como pretendido
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 * @param encomendas o terceiro argumento da função
 */
void removerArtigos(Artigos *artigos, char *ficheiro, Encomendas *encomendas) {
    int i, cod_art = procurarArtigo(*artigos, obterInt(VAL_MIN, artigos->contador - 1, MSG_OBTER_NUM_ART));

    if (cod_art != -1) {
        for (i = cod_art; i < artigos->contador - 1; i++) {
            artigos->artigos[i] = artigos->artigos[i + 1];
        }
        
        int apagar;
        
        for(int i = 0; i < encomendas->contador; i++){
            if(artigos->artigos[i].cod_art == encomendas->encomendas[i].enc_art){
                apagar = 1;
            }
        }
        apagar = -1;
        
        
        if(apagar == 1){
            apagarArtigo(&artigos->artigos[i]);
            artigos->contador--;
            removerArtigoFX(*artigos, ficheiro);
        }else{
            printf("\nArtigo em uso numa encomenda.");
        }

    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}
/**
 * Esta função permite listar os artigos
 * @param artigos o único argumento da função
 */
void listarArtigos(Artigos artigos) {
    if (artigos.contador > 0) {
        int i;
        for (i = 0; i < artigos.contador; i++) {
            imprimirArtigo(artigos.artigos[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}
/**
 * Esta função permite atualizar o preço da mão de obra dos artigos
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarMao_obra(Artigos *artigos, char *ficheiro) {
    int cod_art = procurarArtigo(*artigos, obterInt(VAL_MIN, artigos->contador - 1, MSG_OBTER_NUM_ART));

    if (cod_art != -1) {
        artigos->artigos[cod_art].mao_obra = obterInt(0, MAX_NIF, MSG_OBTER_MAO_OBRA);

        atualizarArtigoFX(*artigos, cod_art, ficheiro);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}
/**
 * Esta função permite atualizar o custo fixo dos artigos
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarCusto_fixo(Artigos *artigos, char *ficheiro) {
    int cod_art = procurarArtigo(*artigos, obterInt(VAL_MIN, artigos->contador - 1, MSG_OBTER_NUM_ART));

    if (cod_art != -1) {
        artigos->artigos[cod_art].custo_fix = obterInt(0, MAX_NIF, MSG_OBTER_CUSTO_FIXO);

        atualizarArtigoFX(*artigos, cod_art, ficheiro);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}
/**
 * Esta função permite atualizar o lucro dos artigos
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarLucro(Artigos *artigos, char *ficheiro){
    int cod_art = procurarArtigo(*artigos, obterInt(VAL_MIN, artigos->contador - 1, MSG_OBTER_NUM_ART));

    if (cod_art != -1) {
        artigos->artigos[cod_art].lucro = obterFloat(0, MAX_NIF, MSG_OBTER_LUCRO);

        atualizarArtigoFX(*artigos, cod_art, ficheiro);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}
/**
 * Esta função imprime os preços dos artigos
 * @param artigo
 */
void imprimirArtigo_preco(Artigo artigo) {
    printf("\n%d %s %d %d %f", artigo.cod_art, artigo.nome, artigo.mao_obra, artigo.custo_fix, artigo.lucro);
    
    int quantidade = artigo.max - artigo.min + 1;
    int tamanho = artigo.min;
    float custo;

    for(int j = 0; j < quantidade; j++){
        printf("\n%d - %f", tamanho, artigo.tamanhos[j]);
        tamanho++;
    }
}
/**
 * Esta função imprime os preços de todos os artigos existentes
 * @param artigos o único argumento da função
 */
void listarArtigos_precos(Artigos artigos){
    if (artigos.contador > 0) {
        int i;
        for (i = 0; i < artigos.contador; i++) {
            imprimirArtigo_preco(artigos.artigos[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}
/**
 * Esta função permite alterar os tamanhos
 * @param artigos o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 * @param opcao o terceiro argumento da função
 */
void alteraTamanho(Artigos *artigos, char *ficheiro, int opcao){
    int opcao1;
    do {
    int quantidade = artigos->artigos[opcao].max - artigos->artigos[opcao].min + 1;
    int tamanho = artigos->artigos[opcao].min;
    int tamanhoMax = artigos->artigos[opcao].max;
    printf("\n------------------------------------------------------------");
    for(int j = 1; j <= quantidade; j++){
        printf("\n%d - %d.",j ,tamanho);
        tamanho++;
    }
    printf("\n0 - sair.");
    printf("\n------------------------------------------------------------");
    scanf("%d",&opcao1);
    if(opcao1 < 0 || opcao1 > tamanhoMax){
        printf("Opçao invalida.");
    }else{
        if(opcao1 != 0){
            opcao1--;
            artigos->artigos[opcao].tamanhos[opcao1] = obterFloat(0, MAX_NIF, MSG_OBTER_TAMANHO);
        }
    }
    } while(opcao1 != 0);
}
/**
 * Esta função permite imprimir os dados das encomendas
 * @param encomenda o único argumento da função
 */
void imprimirEncomenda(Encomenda encomenda) {
    printf("\n%d %d %d %d", encomenda.cod_enc, encomenda.nif_cli, encomenda.enc, encomenda.enc_art);
}
/**
 * Esta função carrega as encomendas para os ficheiros
 * @param encomendas o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 * @return falso se falhar a carregar o ficheiro e true se carregar ficheiro
 */
int carregarEncomendas(Encomendas *encomendas, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        fread(&encomendas->contador, sizeof (int), 1, fp);

        if (encomendas->contador > 0) {
            encomendas->encomendas = (Encomenda*) malloc(encomendas->contador * sizeof (Encomenda));
            fread(encomendas->encomendas, sizeof (Encomenda), encomendas->contador, fp);

            encomendas->tamanho = encomendas->contador;

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            encomendas->encomendas = (Encomenda*) malloc(CLIENTES_TAM_INICIAL * sizeof (Encomenda));
            encomendas->contador = 0;
            encomendas->tamanho = CLIENTES_TAM_INICIAL;
            fclose(fp);

            sucesso = 1;
        }
    }

    return sucesso;
}
/**
 * Esta função liberta o espaço que não está a ser ocupado pelas encomendas
 * @param encomendas o único argumento da função
 */
void libertarEncomendas(Encomendas *encomendas) {
    free(encomendas->encomendas);
}
/**
 * Esta função atualiza o contador nos ficheiros
 * @param contador o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void atualizarContadorFX_enc(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}
/**
 * Esta função insere as encomendas no ficheiro
 * @param encomendas o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void inserirEncomendaFX(Encomendas encomendas, char *ficheiro) {
    atualizarContadorFX_enc(encomendas.contador, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&encomendas.encomendas[encomendas.contador - 1], sizeof (Encomenda), 1, fp);
    fclose(fp);
}
/**
 * Esta função insere encomenda nos ficheiro para mostrar ao cliente
 * @param encomendas o primeiro argumento da função
 * @param artigos o segundo argumento da função
 * @param ficheiro o terceiro argumento da função
 */
void inserirEncomendaTXT(Encomendas encomendas, Artigos artigos, char *ficheiro) {

    FILE *fpp = fopen(ficheiro, "a");
    fclose(fpp);
    FILE *fp = fopen(ficheiro, "w");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < encomendas.contador;i++){
        char tipo[11];
        switch(artigos.artigos[i].tip_cal){
            case 1:
                strcpy( tipo, "sapatos");
                break;
            case 2:
                strcpy( tipo, "sandalias");
                break;
            case 3:
                strcpy( tipo, "botas");
                break;
        }
        fprintf(fp, "\nid: %d \nnif: %d \ncodigo encomenda: %d \ntipo de calçado: %s \ntamanho: %d "
                "\nmao de obra: %d\ncusto fixo: %d\nlucro: %f\npercentagem do tamanho: %f\n", encomendas.encomendas[i].cod_enc,
                encomendas.encomendas[i].nif_cli, encomendas.encomendas[i].enc,
                tipo,
                encomendas.encomendas[i].enc_art + artigos.artigos[encomendas.encomendas[i].enc].min,
                artigos.artigos[encomendas.encomendas[i].enc].mao_obra,
                artigos.artigos[encomendas.encomendas[i].enc].custo_fix,
                artigos.artigos[encomendas.encomendas[i].enc].lucro,
                artigos.artigos[encomendas.encomendas[i].enc].tamanhos[encomendas.encomendas[i].enc_art]);
        fprintf(fp, "conta: %f\n",((artigos.artigos[encomendas.encomendas[i].enc].mao_obra * 2)+ artigos.artigos[encomendas.encomendas[i].enc].custo_fix)+(((artigos.artigos[encomendas.encomendas[i].enc].mao_obra * 2)+ artigos.artigos[encomendas.encomendas[i].enc].custo_fix) * artigos.artigos[encomendas.encomendas[i].enc].lucro) + (((artigos.artigos[encomendas.encomendas[i].enc].mao_obra * 2)+ artigos.artigos[encomendas.encomendas[i].enc].custo_fix) * artigos.artigos[encomendas.encomendas[i].enc].tamanhos[encomendas.encomendas[i].enc_art]));
    }

    fclose(fp);
}
/**
 * Esta função permite inserir encomendas no programa
 * @param encomendas o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 * @param clientes o terceiro argumento da função
 * @param artigos o quarto argumento da função
 * @return mais um no contador para a memória dinâmica
 */
int inserirEncomenda(Encomendas *encomendas, char *ficheiro, Clientes *clientes, Artigos *artigos) {
    int conta;    
    if(encomendas->contador > 0){
        conta = encomendas->encomendas[(encomendas->contador)-1].cod_enc;
    }else{
        conta = -1;
    }
    encomendas->encomendas[encomendas->contador].cod_enc = ++conta;
    int cod,tam;
    do {
        printf("\nInsira o codigo do artigo(0-%d): ",artigos->contador - 1);
        scanf("%d",&cod);
    }while(cod > artigos->contador - 1 || cod < 0);
    do {
    printf("\nInsira o tamanho do artigo(0-%d)(tamanhos entre %d - %d): ",artigos->artigos[cod].max - artigos->artigos[cod].min, artigos->artigos[cod].min,artigos->artigos[cod].max);
    scanf("%d",&tam);
    }while(tam > artigos->artigos[cod].max - artigos->artigos[cod].min || tam < 0);
    
    encomendas->encomendas[encomendas->contador].enc = cod;
    encomendas->encomendas[encomendas->contador].enc_art = tam;
    encomendas->encomendas[encomendas->contador].contador++;

    return encomendas->contador++;
}
/**
 * Esta função é para expandir o espaço caso não haja espaço suficiente
 * @param encomendas o único argumento da função
 */
void expandirEncomendas(Encomendas *encomendas) {
    Encomenda *temp = (Encomenda*) realloc(encomendas->encomendas, sizeof (Encomenda) * (encomendas->tamanho * 2));
    if (temp != NULL) {
        encomendas->tamanho *= 2;
        encomendas->encomendas = temp;
    }
}
/**
 * Esta função permite inserir encomendas no artigo e no ficheiro
 * @param encomendas o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 * @param clientes o terceiro argumento da função
 * @param artigos o quarto argumento da função
 * @param verificar o quinto argumento da função
 * @param vis o sexto argumento da função
 */
void inserirEncomendas(Encomendas *encomendas, char *ficheiro, Clientes *clientes, Artigos *artigos, int verificar, char *vis) {
    if (encomendas->contador == encomendas->tamanho) {
        expandirEncomendas(encomendas);
    }
    encomendas->encomendas[encomendas->contador].nif_cli = clientes->clientes[verificar].nif;
        if (inserirEncomenda(encomendas, ficheiro, clientes, artigos) == -1) {
            puts(ERRO_CLIENTE_EXISTE);
        } else {
            inserirEncomendaFX(*encomendas, ficheiro);
            inserirEncomendaTXT(*encomendas, *artigos, vis);
        }
}
/**
 * Esta função lista todas as encomendas criadas
 * @param encomendas o primeiro argumento da função
 * @param ficheiro o segundo argumento da função
 */
void listarEncomendas(Encomendas encomendas, char *ficheiro) {
    if (encomendas.contador > 0) {
        int i;
        for (i = 0; i < encomendas.contador; i++) {
            imprimirEncomenda(encomendas.encomendas[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}