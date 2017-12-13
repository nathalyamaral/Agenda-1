

#include <iostream> //biblioteca padrão
#include "funcoes.h" //biblioteca com as funções da agenda
#include <string> //biblioteca para manipulação de strings
#include <fstream>//para entrada/saida manipulação de arquivos
#include <cstdlib>//para complar linux

using namespace std;


/*------------------------------------|
* função menu, void                   |
*                                     |
* função que monta as opçoes          |
*------------------------------------*/

void menu(){


    desenha(1);//essa função só desenha uma linha na tela
    cout <<" >>>>>>>> AGENDA  <<<<<<<<\n\n" << endl;
    desenha(1);

        desenha(0);
    cout <<"\n\tEscolha a opcao:" << endl;
    cout <<"1 - Insere contato." << endl;
    cout <<"2 - remove contato." << endl;
    cout <<"3 - Mostra Contatos" << endl;
    cout <<"4 - Sair do programa." << endl;
    desenha(0);
}


int main()
{

    //ponteiros para o inicio e final da lista
    TLista * Inicio = NULL, * Fim = NULL, add;


    //carrega os dados direto do arquivo pro nó
    abrirArquivo(&Inicio, &Fim);

    int opc;//variavel para as opcões

    do{//Loop principal que fica voltando para o menu
        menu(); //chamada para a escolha das opçoes da agenda

        //valida a opção
        do {

            cin >> opc;

            }while(opc < 1 || opc > 4);

            //case para as escolhas
            switch( opc ) {

                case 1:// insere contato

                /*testa se o nome tem mais de 30 caracteres
                 se tiver, manda escrever novamente ou se possui ; na string*/

		cin.get();//se ano tivesse esta linha no linux pula para a proxima instrução
		do{
		cin.sync();
                    cout <<"Informe o nome: " << endl;



                    getline(cin,add.nome); //pega o nome
                    cout <<"\nAperte ENTER:" << endl;
                    cin.get();

                }while ( ( int(add.nome.length()) > 30) || add.nome.find(';')!= string::npos);

                //CONVERTE a string para minuscula
                for( int i = 0; i < int(add.nome.length()); i ++)
                    add.nome[i] = tolower(add.nome[i]);


                  /*testa se o data tem mais de 10 caracteres
                 se tiver, manda escrever novamente ou se possui ; na string*/
                do{
                    cout <<"Informe o ano de nascimento (dd/mm/aaa): " << endl;
                    cin.sync();
                    getline(cin,add.data);//pega a data
                }while( int(add.data.length()) > 10 || add.data.find(';')!= string::npos);

                //chama a funcao que insere ordenado
                insereOrdenado(add.nome,add.data, &Inicio, &Fim );

                cout <<"\n\tAdicionado!" << endl;
                cout <<"\nAperte ENTER:" << endl;
                cin.get();

                break;

                //deleta contato de maior prioridade
                case 2:

                TLista *delCont;

                delCont = Inicio;
                if(Inicio == Fim) { Inicio = Fim = NULL; }

                else { Inicio = delCont->prox; }

                delete delCont; //deleta delCont

                cout <<"Contato de maior prioridade deletado! " << endl;

                cout <<"\nAperte ENTER:" << endl;
                cin.get();
                cin.get();

                break;

                //mostra contato - lista
                case 3:

                desenha(1);
                cout <<">>> LISTA <<< "<< endl;
                mostra (Inicio, 0);  //parametro 0, só imprime na tela (veja o codigo em "funcoes.h"
                desenha(1);

                cout <<"\nAperte ENTER:" << endl;
                cin.get();
                cin.get();
                break;

                case 4:

                desenha(0);
                cout << "\nFim do programa!" << endl;
                break;

                default: cout <<"opcao errada\n" << endl; break;

                } //fim do case

                }while(opc != 4); //fim do loop principal

                cin.get();

                mostra (Inicio, 1); //parametro 1, grava os dados no arquivo

                libera(Inicio); //libera toda a memoria alocada que a lista usou

    return 0;
}
