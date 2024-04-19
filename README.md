ESPECIFICAÇÕES SISTEMA DE ARQUIVOS

Alunos: Isadora Coelho, Maria Eduarda e Gabriel Lenser
Docente: Marcio Seiji Oyamada
Disciplina: Sistemas operacionais 

1. ESPECIFICAÇÃO

Método de alocação
Alocação contígua
Gerenciamento de espaços livres
Mapa de bits

tabela 01: combinações escolhidas

	O sistema de arquivos a ser desenvolvido pela equipe usa a alocação contígua sendo que a memória do disco é segmentada em setores de 512 bytes, que são a menor unidade alocável possível, quanto ao gerenciamento de espaços livres a estratégia escolhida foi o bitmap.
Como mostra a figura abaixo, o disco será dividido em quatro principais áreas, a primeira delas, o boot record, o qual ocupa sempre o primeiro setor do disco. Nele é possível encontrar informações pertinentes à organização do sistema. Em seguida, temos o diretório raiz, que será o único pois adotamos o diretório de apenas um nível, que armazena informações de todos os arquivos presentes no sistema e após ele a área de dados, que contém os dados dos arquivos. Por fim, temos um mapa de bits, que registra se os setores do disco estão ocupados ou não.

imagem 01: ilustração do disco dividida por setores




2. ÁREAS DO DISCO

BOOT RECORD:
Offset
Size (bytes)
Info
0
2
Bytes por setor 
default 512
2
2
Setores reservados 
default 1
4
2
Número de entradas de diretório raiz
default 128
6
8
Tamanho do diretório raiz em bytes
14
8
Início do bitmap em setores 
22
8
Tamanho do bitmap em bytes

tabela 02: Boot record

DIRETÓRIO RAIZ:
Offset
Length (bytes)
Info
0
12
10 caracteres para nome e 3 para extensão.
12
8
Primeiro setor
20
4
Tamanho do arquivo em bytes
24
8 
Número de setores

tabela 03: root dir

Para sabermos se tem uma entrada disponível para alocação de arquivo, o primeiro bytes estará zerados.



DADOS

	Os dados são armazenados em setores, obrigatoriamente um setor é ocupado por apenas um arquivo, mesmo que sua utilização ocupe apenas alguns bytes.

BITMAP:
Características do Bitmap: 
Cada byte no bitmap corresponde a um setor do disco.
O bitmap será inicializado com os primeiros 9 setores ocupados, sendo referentes ao boot record e ao diretório raíz.
O bitmap será atualizado a cada mudança realizada em um arquivo.
O tamanho do bitmap será equivalente ao número de setores no disco.
Em cada posição no bitmap, 0 indicará livre e 1 ocupado.
Início do bitmap = setores reservados + tamanho rootdir + área de dados

3. OPERAÇÕES DE USO

3.1 Formatador

Para criar uma partição do disco, o usuário informará o número de setores desejados, e a partir disso é necessário realizar os seguintes cálculos, considerando que o boot record sempre ocupará 1 setor:

Tamanho do diretório raiz em bytes = 128 * 32, onde:  
128 = número máximo de entradas do diretório raiz
32 = tamanho de cada entrada

Tamanho do bitmap em bytes = n 
Tamanho do bitmap em setores = ceil(n/512), onde:
n = números de setores formatado pelo usuário
Por conta do arredondamento para cima, caso o bitmap contenha mais bytes que setores, todos eles serão postos como ocupados para evitar acessos fantasmas.

Início do bitmap em bytes = tamanho do boot record +tamanho diretório raíz + 
 tamanho área de dados 

Número de setores por arquivo = tamanho do arquivo / tamanho do setor

Número de setores na área de dados = total de setores - boot record - rootdir - 
bitmap

3.2 Cópia de um arquivo do disco rígido para o sistema de arquivos
	
	A primeira parte para realizar essa operação será solicitar ao usuário que arquivo ele deseja copiar para o sistema de arquivos. O arquivo obrigatoriamente deverá estar no mesmo diretório que a imagem e código fonte. Em seguida será necessário:
Calcular quantos setores o arquivo ocupa e, verificar se existe espaço para alocá-lo contiguamente;
Ocupar uma entrada no diretório raíz com o nome do arquivo a ser copiado e seus dados;
Ir até o primeiro setor e enquanto lê o arquivo do disco rígido, descarregar as suas informações no sistema de arquivos até elas atingirem o seu tamanho.

3.3 Cópia de um arquivo do sistemas de arquivos para o disco rígido

	A primeira parte para realizar essa operação será solicitar ao usuário que arquivo ele deseja copiar para o disco rígido. O arquivo será criado no mesmo diretório que a imagem e código fonte. Em seguida será necessário:
Encontrar o arquivo no diretório raíz e navegar até seu primeiro setor;
Criar o arquivo no disco rígido;
Ler as informações presentes nos setores e ir descarregando no disco até que o tamanho seja alcançado.

3.4 Listagem dos arquivos
	
	Para realizar a listagem dos arquivos presentes no sistema de arquivos será necessário realizar os seguintes passos:
Ir até o ínicio do diretório raiz;
Verificar se os dois primeiros bytes indicam que o arquivo foi excluído;
Caso esteja apagado, apenas ignorar e seguir para próxima entrada;
Imprimir na tela o nome dos arquivos que são entradas válidas até que uma delas esteja vazia, indicando que elas acabaram.


3.5 Remoção de arquivos

	Para remover um arquivo, será solicitado ao usuário o nome do arquivo que ele deseja apagar, em seguida serão realizadas as seguintes operações:
Identificar a entrada no diretório raíz referente ao arquivo a ser apagado;
Mudar os primeiros dois bytes para “E5”, indicando que a entrada foi excluída;
Identificar quais setores pertencem ao arquivo, e mudá-los no bitmap para livres.

