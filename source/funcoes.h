/*                     FUNCOES
* Trabalho de Estrutura de Dados II (lista de prioridades)
* Academico: Jhonathan Paulo Banczek
* Professor: Ademir Martinez Sanches
* Data: 26/08/2010
* @email: banczek256@hotmail.com ou jpbanczek@gmail.com
*  >>>>>>>>>>>>>>>>>>DOMINIO LIVRE<<<<<<<<<<<<<<
*/
#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED
#include <fstream> //manipulação de arquivos
#include <cstdlib> //pro linux


#define INICIO 1
#define FIM    2
#define MEIO   3

using namespace std;

//Struct com o nó na lista
//------------------------------------------------------------------------
typedef struct NoProx
{
   string nome;//nome do contato
   string data;//data de nacimento do contato

   struct NoProx *prox;
}TLista;

//------------------------------------------------------------------------

/*------------------------------------|
* função desenha, void                |
* parametros: 1 ou 0                  |
* função que desenha linhas da janela |
*------------------------------------*/


void desenha(int i)
{
    if( i == 0)
        cout<<"\nÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ"<<endl;

        else if ( i == 1)
            cout <<"ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ\n" << endl;
}

//------------------------------------------------------------------------

/*-------------------------|
* função insereNo, void    |
* recebe o nome e a data   |
*-------------------------*/

//chave = nome
void insereNo( string nome_insere, string data_insere, TLista * EndIns, int Posicao, TLista ** Inicio, TLista ** Fim )
{
    TLista * NovoNo;       //ponteiro para o novo no
    NovoNo = new( TLista );//aloca memoria para o novo no
    NovoNo->nome = nome_insere; // nome do contato
    NovoNo->data = data_insere; // data do contato

    if( *Inicio == NULL ){ //se Lista vazia insere no Inicio
       *Inicio = *Fim = NovoNo;
       NovoNo->prox=NULL;
    }

    else{ //senao o NO sera inserido na posicao INICIO ou FIM ou MEIO
       switch( Posicao ){
          case INICIO:
               NovoNo->prox = *Inicio;
               *Inicio = NovoNo;
               break;

          case FIM:
               NovoNo->prox = NULL;
               ( *Fim )->prox = NovoNo;
               *Fim = NovoNo;
               break;

          default://inseere no MEIO
             NovoNo->prox = EndIns->prox;
             EndIns->prox = NovoNo;
             if(EndIns == *Inicio)
                *Fim = NovoNo;
       }
    }
} //fim da função insereNo


//------------------------------------------------------------------------
/*------------------------------|
* função insereOdenado, void  |
* recebe o nome e a data        |
*--------------------------- -*/

void insereOrdenado( string nome, string data, TLista** Inicio, TLista** Fim )
{
   if( (*Inicio)==NULL){ //lista vazia
      insereNo( nome, data, NULL, INICIO, Inicio, Fim );
   }else{ //lista nao esta vazia
     TLista  * aux, //pontero para o atual
             * aux2;//pontero para o anterior
     //procura a posicao certa para inserir a nova chave
     for( aux = aux2 = *Inicio;            //inicializacao
         aux != NULL && aux->nome < nome;//teste
         aux2 = aux, aux = aux->prox );    //incremento

      if( aux == aux2 )      //caso inicio
         insereNo(nome, data, *Inicio, INICIO, Inicio, Fim);
      else if( aux2 == *Fim )//caso fim
               insereNo(nome, data, NULL, FIM, Inicio, Fim);
           else              //caso meio
               insereNo(nome, data, aux2, MEIO, Inicio, Fim);
    }
}//fim da função insereOrdenado
//------------------------------------------------------------------------

/*-------------------------------------------------|
* funcao abrirArquivo, void                        |
* abre os dados do arquivo "agenda.csv  "          |
*-------------------------------------------------*/

void abrirArquivo (TLista** Inicio, TLista** Fim) {

    string bufferArquivo; // variavel q recebe a linha(getline) do arquivo

    fstream aux("agenda.csv");//canl de entrada

    if(aux == NULL){//senao existir, cria um novo.
        aux.open("agenda.csv",ios::out);
        aux.close();

        }

    ifstream arq;//canal de entrada

    arq.open("agenda.csv",ios::in);//Leitura

    //testa o arquivo
    if(arq.fail()) {
        cout <<"Erro na abertura do arquivo!!" << endl;
        arq.close();
        exit(1);
         }

         else {
             //string que receberão nome e data
             string nome, data;

            //enquanto nao for fim do arquivo
             while (!arq.eof()){

                 getline(arq, bufferArquivo);//pega a primeira linha do arquivo

                 //grava o nome da variavel da posição 0 até achar ';'
                nome = bufferArquivo.substr(0, bufferArquivo.find_first_of(';'));

                 //grava a data de nascimento partindo do ';' até final da string "bufferArquivo"
                data = bufferArquivo.substr(bufferArquivo.find_first_of(';')+1 );

                if(nome != ""){//se nome for diferente de campo vazio insere
                //chama a função que insere ordenado.
                insereOrdenado( nome, data, Inicio, Fim);
                }
                //e repete até fim do arquivo.

                }
         }

        //fecha o arquivo
         arq.close();

} //fim da função abrirArquivo


//------------------------------------------------------------------------

/*-------------------------------------------------|
* funcao libera, void                              |
* libera toda a memoria alocada que a lista usou   |
*-------------------------------------------------*/

void libera( TLista * Inicio )
{
   TLista * aux;
   while( Inicio ){
     aux = Inicio->prox;
     delete Inicio;
     Inicio = aux;
   }
}//fim da função libera

//------------------------------------------------------------------------

/*---------------------------------------------------|
* função mostra, void                                |
*                                                    |
* função que mostra os contatos armazenados          |
* parametro: 0 = só mostra o que tem na lista        |
* parametro: 1 = salva a lista no arquivo            |
*---------------------------------------------------*/
void mostra( TLista * Inicio, int opc ) {

    TLista *NoAux;

    NoAux = Inicio;

    // 0 - mostra
    if ( opc == 0 ){
            desenha(1);
            cout<<"Lista de contatos: \n\n";

        while( NoAux ){
            cout<<"\nNome: " << NoAux->nome <<" | Data de nascimento: ";
            cout<<NoAux->data<< endl;
            NoAux = NoAux->prox;
            }
            }
            //2 - grava
            else if (opc == 1){

                ofstream fgrava;

                fgrava.open("agenda.csv",ios::trunc);//deleta todo arquivo

                fgrava.close();

                fgrava.open ("agenda.csv",ios::app);

                //testa o arquivo
                if(fgrava.fail()) {
                    cout <<"Erro na abertura do arquivo" << endl;
                    fgrava.close();
                    exit(1);
                    }

                while( NoAux ){
                    fgrava<<NoAux->nome <<";" << NoAux->data<<endl;
                    NoAux = NoAux->prox;
                    }

                    fgrava.close();//fecha o arquivo
                    }
}//fim da função mostra


#endif // FUNCOES_H_INCLUDED
