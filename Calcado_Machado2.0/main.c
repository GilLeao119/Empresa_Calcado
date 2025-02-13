/**
 * 
 * @file main.c
 * @author Gil Leão, Rui Ferreira, Pedro Nunes
 * @date 24 novembro 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Machado.h"
#include "input.h"

int main() {
    int Menu = 0, Menu_Adm = 0, Menu_Cli = 0, Menu_Crud_cli = 0, Menu_Precos = 0, Menu_Artigos = 0, Menu_Edit = 0, Menu_edita_especifico;
    Clientes clientes = {.contador = 0};
    Artigos artigos = {.contador = 0};
    do{
        switch( Menu ){
            default: 
                do{
                    menu_ini();
                    scanf("%d",&Menu);
                    system("clear");
                    if(Menu < 0 || Menu > 2){
                        msg_error();
                    }
                }while(Menu < 0 || Menu > 2);
                break;
                
            case 1://cliente
                
                do{
                    switch(Menu_Cli){
                        default:
                            do{
                                menu_cli();
                                scanf("%d",&Menu_Cli);
                                system("clear");
                                if(Menu_Cli < 0 || Menu_Cli > 2){
                                    msg_error();
                                }
                            }while(Menu_Cli < 0 || Menu_Cli > 2);
                            break;
                        case 1: //login
                            if(procurarClientes(clientes) == 1){
                                //codigo apos login
                            }
                            Menu_Cli = -1;
                            system("clear");
                            break;
                        case 2: //criar conta
                            inserirClientes(&clientes);
                            Menu_Cli = -1;
                            system("clear");
                            break;
                    }
                }while(Menu_Cli != 0);
                
                Menu = -1;
                system("clear");
                break;
                
            case 2://Adm
                
                do{
                    switch(Menu_Adm){
                        default:
                            do{
                                menu_adm();
                                scanf("%d",&Menu_Adm);
                                system("clear");
                                if(Menu_Adm < 0 || Menu_Adm > 3){
                                    msg_error();
                                }
                            }while(Menu_Adm < 0 || Menu_Adm > 3);
                            break;
                        case 1: //Crud clientes
                            do{
                                switch(Menu_Crud_cli){
                                    default:
                                        do{
                                            menu_crud_cli();
                                            scanf("%d",&Menu_Crud_cli);
                                            if(Menu_Crud_cli < 0 || Menu_Crud_cli > 4){
                                                msg_error();
                                            }
                                        }while(Menu_Crud_cli < 0 || Menu_Crud_cli > 4);
                                        break;
                                    case 1:
                                        inserirClientes(&clientes);
                                        Menu_Crud_cli = -1;
                                        system("clear");
                                        break;
                                    case 2:
                                        system("clear");
                                        listarClientes(clientes);
                                        Menu_Crud_cli = -1;
                                        break;
                                    case 3:
                                        editarClientes(&clientes);
                                        Menu_Crud_cli = -1;
                                        system("clear");
                                        break;
                                    case 4:
                                        eliminarClientes(&clientes);
                                        Menu_Crud_cli = -1;
                                        system("clear");
                                        break;
                                }
                            }while(Menu_Crud_cli != 0);
                            Menu_Adm = -1;
                            system("clear");
                            break;
                        case 2: //Crud artigos
                            do{
                                switch(Menu_Artigos){
                                    default:
                                        do{
                                            menu_crud_artigos();
                                            scanf("%d",&Menu_Artigos);
                                            if(Menu_Artigos < 0 || Menu_Artigos > 4){
                                                msg_error();
                                            }
                                        }while(Menu_Artigos < 0 || Menu_Artigos > 4);
                                        break;
                                    case 1:
                                        inserirArtigos(&artigos);
                                        Menu_Artigos = -1;
                                        system("clear");
                                        break;
                                    case 2:
                                        system("clear");
                                        listarArtigos(artigos);
                                        Menu_Artigos = -1;
                                        break;
                                    case 3:
                                        editarArtigos(&artigos);
                                        Menu_Artigos = -1;
                                        system("clear");
                                        break;
                                    case 4:
                                        eliminarArtigos(&artigos);
                                        Menu_Artigos = -1;
                                        system("clear");
                                        break;
                                }
                            }while(Menu_Artigos != 0);
                            Menu_Adm = -1;
                            system("clear");
                            break;
                        case 3: //crud preços
                            do{
                                menu_crud_precos();
                                scanf("%d",&Menu_Precos);
                                if(Menu_Precos == 1){
                                    do{
                                        switch(Menu_edita_especifico){
                                            default:
                                                do{
                                                Menu_edit_especifico();
                                                scanf("%d",&Menu_edita_especifico);
                                                if(Menu_edita_especifico < 0 || Menu_edita_especifico > 4){
                                                    msg_error();
                                                }
                                                }while(Menu_edita_especifico < 0 || Menu_edita_especifico > 4);
                                                system("clear");
                                                break;
                                            case 1:
                                                system("clear");
                                                int sim = menu_edit_precos(artigos);
                                                if(sim != -1){
                                                    if(sim != 0){
                                                        alteraPrecoMaoObra(&artigos, --sim);
                                                    }    
                                                }
                                                Menu_edita_especifico = -1;
                                                break;
                                            case 2:
                                                system("clear");
                                                sim = menu_edit_precos(artigos);
                                                if(sim != -1){
                                                    if(sim != 0){
                                                        alteraPrecoFixo(&artigos, --sim);
                                                    }    
                                                }
                                                Menu_edita_especifico = -1;
                                                system("clear");
                                                break;
                                            case 3:
                                                system("clear");
                                                sim = menu_edit_precos(artigos);
                                                if(sim != -1){
                                                    if(sim != 0){
                                                        alteraPrecoLucro(&artigos, --sim);
                                                    }    
                                                }
                                                Menu_edita_especifico = -1;
                                                system("clear");
                                                break;
                                            case 4:
                                                system("clear");
                                                
                                                sim = menu_edit_precos(artigos);
                                                if(sim != -1 && sim != 0){
                                                    int nao = menu_edit_tamanhos(artigos, --sim);
                                                    if(nao != 0){
                                                        alteraPrecoTamanho(&artigos, sim--, --nao);
                                                    }
                                                }
                                                
                                                Menu_edita_especifico = -1;
                                                system("clear");
                                                break;
                                        }
                                    }while(Menu_edita_especifico != 0);
                                    system("clear");
                                    Menu_Precos = -1;
                                    system("clear");
                                }else if(Menu_Precos == 0){
                                    Menu_Adm = -1;
                                    system("clear");
                                }else{
                                    msg_error();
                                    Menu_Precos = -1;
                                }
                            }while(Menu_Precos != 0);
                            break;
                    }
                }while(Menu_Adm != 0);
                
                Menu = -1;
                system("clear");
                break;
                
        }
    }while(Menu != 0);
    msg_adeus();
    return (0);
}