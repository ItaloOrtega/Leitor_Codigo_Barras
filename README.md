# Leitor_Codigo_Barras
Projeto em C para a leitura de códigos de barras a partir de um FILE
Definições do Projeto:

1 Definicão

A leitura de código de barras  ́e um processo algor ́ıtmico em que se determina a
largura de barras e espa ̧cos para determinar d ́ıgitos decimais.
Considerando que um arquivo cont ́em um conjunto de c ́odigos de barras,
escreva um programa que leia tais c ́odigos e escreva em um segundo arquivo a
tradu ̧c ̃ao das barras em valores num ́ericos.
O texto “How UPC Bar Codes Work”, dispon ́ıvel em
https://electronics.howstuffworks.com/gadgets/high-tech-gadgets/upc.htm
descreve como c ́odigos de barras s ̃ao reconhecidos (ver principalmente a partir
de “Can I decode the bars”).
Aqui usaremos uma vers ̃ao simplificada desse processo, considerando que os
dados armazenados s ̃ao apenas valores 0 e 1, sendo que um valor 0 est ́a contido
em uma barra e o valor 1 est ́a contido em um espa ̧co.
O arquivo cont ́em um n ́umero desconhecido de linhas, sendo que cada c ́odigo
de barra ocupa de duas a cinco linhas, existindo sempre pelo menos duas linhas
preenchidas com espa ̧cos (valores 1) entre dois c ́odigos de barra.
Como indicado no documento citado acima, a primeira barra representa a
largura base das barras e espa ̧cos. Assim, se essa barra tiver largura de dois
valores 0, ent ̃ao podemos ter barras com largura de dois, quatro, seis ou oito
0 consecutivos. O mesmo vale para os espa ̧cos, com dois, quatro, seis ou oito
valores 1. Esse tamanho base pode ser de um a quatro caracteres (pixels),
variando de um c ́odigo para outro.

2 O que deve ser feito

Escreva um programa que leia o arquivo de entrada, denominado “barras.dat”
e escreva os d ́ıgitos correspondentes a cada c ́odigo em um segundo arquivo,
denominado “codigos.dat”. No arquivo de sa ́ıda deve existir uma linha para
cada c ́odigo de barra, sendo que os d ́ıgitos devem estar separados por um espa ̧co
em branco.

3 Condições de teste

Seu programa deve executar considerando que o arquivo de entrada cont ́em um
conjunto de linhas compostas por zeros e uns, sem separa ̧c ̃ao entre eles dentro
de uma linha. O exemplo a seguir mostra o come ̧co de cada linha do arquivo de
entrada.
11111111111111111111111111111111111111...
11101010010001110100110011010100001001...
11101010010001110100110011010100001001...
11101010010001110100110011010100001001...
11111111111111111111111111111111111111...
11111111111111111111111111111111111111...
11111111111111111111111111111111111111...
11100110011000000110000111111000011001...
11100110011000000110000111111000011001...
11111111111111111111111111111111111111...
Sendo que o primeiro c ́odigo gera 8916..., enquanto o segundo c ́odigo gera
70..., ou seja, no arquivo de sa ́ıda ter ́ıamos:
8 9 1 6 ... ...
7 0 ... ...
