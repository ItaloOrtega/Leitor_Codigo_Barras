#include <stdio.h>
#include <stdlib.h>
//Declaração das funções
int calc_valor(int valor[]);
void escreve(char linha[], int tam, FILE *const arquivo2);
void percorre( FILE *const fin );

int main(){//Main do programa

  FILE *arquivo1;//Criação do arquivo de leitura

  arquivo1 = fopen("barras.dat", "r");//Abre o arquivo barras.dat para leitura

  if(arquivo1 == NULL){//Dando algum erro com o arquivo

    printf("Nao foi possivel abrir o arquivo!!!\n");
    exit(0);
  }

  percorre(arquivo1);//Chama a função que percorre os dados do arquivo de código de barras
  
  fclose(arquivo1);//Fecha o arquivo
  
  printf("\nPrograma Encerrado...\n");

  return 0;
}

int calc_valor(int valor[]){//Função que calcula o valores do código de barras de acordo com os 4 valores do vetor
   int r = 0;//Valor do número

   switch (valor[0]){//Switch da primeira posição do vetor valor[]

     case 1://Se o primeiro valor é 1, logo pode ser 3,4,5,6,7 ou 8
       switch (valor[1]){//Switch da segunda posição do vetor

       case 1://Se o segundo valor é 1, logo ele só pode ser 4 ou 6
         if(valor[2] == 3){
           r = 4;
         }
         else{
           r = 6;
         }
         break;

       case 2://Se o segundo valor é 2, logo ele só pode ser 5 ou 8
         if(valor[2] == 3){
           r = 5;
         }
         else{
           r = 8;
         }
       break;

       case 3://Se o segundo valor é 3, só pode ser 7
         r = 7;
         break;

       case 4://Se o segundo valor é 4, só pode ser 3
         r = 3;
         break;
       }
     break;

     case 2://Se o primeiro valor é 2, logo ele só pode ser 1 ou 2
     if(valor[1] == 2)
       r = 1;
     else
       r = 2;
     break;

     case 3://Se o primeiro valor é 3, logo ele só pode ser 0 ou 9
     if(valor[1] == 2)
       r = 0;
     else
       r = 9;
     break;
   }

  return r;//Retorna o valor do número
}

void escreve(char linha[], int tam, FILE *const arquivo2){
   int total = 0, base, cont, nums = 0,vlrs[4];//total = qtd. de números do cod. de barras; base = base do cod. de barras; cont = qtd. da sequencia de 1s ou 0s para determinar o valor de um número do cod. de barras;
   char crt, f = '0', aux = '1';//crt = caracter atual; f = estado da função: 0 - procurando a base, 1 - calculando a base, 2 - base calculada;
   //aux = valor do caractere era antes da iteração
   
   for(int i = 0; i < tam; i++){
     if(total == 12){//Se encontrar os 12 números do cod. de barras o for é terminado
       break;
     }
     crt = linha[i];//crt recebe o valor do caractere atual da linha

     if(crt != aux && f == '2'){//Tendo já encontrado a base do cod. de barras e o caracter atual sendo diferente do anterior lido, ou seja, tenha mudado de 1 para 0 ou vice-versa
       vlrs[nums] = cont/base;//Significa que encontramos um valor dos quatro para calcular um número do cod. de barras
       //Ele é colocado no vetor vlrs para que quando o vetor fique completo, com os 4 valores, podermos calcular o número do cod. de barras
       nums++;//incrementa a qtd. de valores para calcular esse número do cod. de barras
       cont = 0;//Zera a contagem, já que o valor de c mudou
       if(nums == 4){//Quando encontramos todos os valores para calcular o valor do cod. de barras
         nums = calc_valor(vlrs);//Usamos a váriavel nums para receber o número do cod. de barras que será calculado pela função calc_valor por meio do vetor vlrs
         fprintf(arquivo2, "%d ",nums);//escreve o valor do código de barras no arquivo
         ++total;//Incrementa o total de números do cod. de barras calculados
         if(total == 6){//Quando foram calculados os 6 primeiros valores do cod. de barras existe um 1-1-1-1-1 no cod. de barras
           i = i + (5 * base);//Pulando o 1-1-1-1-1 para ir para o começo do primeiro valor do 7º valor do cod. de barras
           crt = linha[i];//crt recebe esse novo caractere
         }
         nums = 0;//Zera a quantidade de valores que o veto vlrs possui para calcular o próximo valor do cod. de barras
       }
       aux = crt;//Aux recebe o valor do novo valor atual, ou seja, se era 1 virou 0 e vice-versa
     }

     if(crt == '0' && f == '0'){//Estando procurando a base do cod. de barras e o crt = '0', logo achou o 1-1-1
       f = '1';//Muda o estado de f para calculando a base
       cont = 0;//zera a contagem
     }

     if(crt == '1' && f == '1'){//Estando calculando a base do cod. de barras e o crt = '1', logo o programa se encontra no espaço do 1-1-1
       f = '2';//Muda o estado de f para base calculada
       base = cont;//base é o valor de cont, que é a quantidade de valores percorridos iguais sequencialmente
       i = i + (base * 2);//pular o espaço e a barra remanecentes do 1-1-1, para que a função já va para o primeiro valor
       printf("\nBase do cod. de barras = %d\n",base);//Mostra a base do cod. de barras na tela
       cont = 0;//zera a contagem
     }
     ++cont;//Incrementa a contagem
   }
  fprintf(arquivo2, "\n");//escreve um /n para separação de códigos de barras diferentes no arquivo
}


void percorre( FILE *const fin ){
   int tam;//Tamanho da linha atual
    char c, enc = '0';//c = caracter da posição; enc = variavel dita se a função está buscando uma linha de códigos de barras, já encontrou uma ou está buscando uma nova
    FILE *arquivo2;//Cria o ponteiro para o arquivo de escrita

    arquivo2 = fopen("codigos.dat", "w");//Abre o arquivo codigos.dat para escrever nele

    if(arquivo2 == NULL){//Dando algum erro com o arquivo
      printf("Nao foi possivel abrir o arquivo!!!\n");
      exit(0);
    }
    while(!feof(fin)){//While para percorrer o arquivo
      tam = 0;//zerar a varíavel do tamanho da linha a cada iteração do while
      for( ;; ){//for que percorre cada linha
        c = fgetc( fin );//c recebe o valor do digito atual

        if( c != EOF && c != '\n' ){//Se o c não é um valor de final de linha
          if (enc == '0' && c == '0')//Caso a c dif. de 1 e ainda não ter encontrado uma linha com dados do cod de barras
            enc = '1';//Muda o enc para 1, no qual ele já encontrou a linha desejada, a linha com os dados do cod de barras
          if (enc == '2' && c == '0'){//Se enc = 2, que é quando ele está em busca de uma linha de espaços e c = 0, ele pula de linha
            break;//Pois é uma linha que possuem dados que já foram escritos
          }
        }

        if( c == EOF || c == '\n' ){//Caso c for igual a um final de linha/arquivo
            if(tam > 0 && enc == '1'){//Tendo encontrado a linha de dados do cod. de barras e o tamanho sendo > 0
              printf("\nTamanho do cod. barras = %d\n",tam);//Printa o tamanho do cod. de barras
              ++tam;//Incrementa 1 em tam, para que tenha até o final da linha
              char linha[tam];//cria o vetor de char para receber a linha de dados
              enc = '2';//Muda o enc para encontrar uma linha de espaço, ou seja, que contem somente 1s
              fgets(linha, tam, fin);//Copia a próxima linha para o vetor linha. O cod. de barras sempre tem no mínimo duas linhas com dados, portanto a próxima linha tem os mesmos dados do que a que foi lida totalmente
              escreve(linha, tam, arquivo2);//Chama a função escreve para escrever os números do cod. de barras no arquivo codigos.dat
            }
            break;
        }
        ++tam;//Incremento do tamanho da linha
        //Tamanho > 32, pois o maximo de espaços antes do 1-1-1 do cod. de barras é 32, que é o caso de 4 espaços de base 8
        if(tam > 32 && enc == '0' && c == '1'){//Caso o tamanho já esteja valendo > 32 e o enc = '0', significa a linha atual não possui os dados do cod. de barras pois ela é uma linha de espaço, portanto paramos o for
          break;
        }

        if(tam > 32 && enc == '2' && c == '1'){//Caso semelhante ao anterior, mas nesse caso ele esta buscando essa linha de espaço, encontrando-a o enc é mudado para 0, para o estado de busca de linha de dados do cod. de barras
          enc = '0';
          break;
        }
      }
    }
    fclose(arquivo2);//Fecha o arquivo
}
