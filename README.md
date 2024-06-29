# Trabalho-2
Estudante: Mariana Gonzaga Ramires  
Professor: Edson Takashi Matsubara  
Ciência da Computacação  
UFMS  
2024.1  

Considerando a base dados do trabalho anterior do IBGE de cidades (https://github.com/kelvins/municipios-brasileiros/blob/main/json/municipios.json), com esta estrutura adaptada você conseguirá fazer buscas por intervalos. Por exemplo retornar todas as cidades que possuem DDD entre 15 e 20. Retornar todas as cidades que possuem latitude entre -31 e -34 e longitude entre - 50 e -54, ou mesmo fazer combinações entre latitude, longitude e DDD. 

## Tarefa 1: Adaptação da AVL
Descrição: (1.1) Adapte o código de AVL dado em sala para que os nodes possuam ponteiro para o pai. (1.2) cada nó da árvore deve ter uma lista encadeada que armazena os registros com chaves iguais (um nó pode ter dois ou mais registros). (1.3) Implemente a função de sucessor de um nó que consiga olhar para os ancestrais (veja o código de sucessor no livro do Cormem), esta funcionalidade irá permitir fazer o range query. 

## Tarefa 2: Construção das AVLs
Descrição:  Construa uma AVL para cada um dos seguintes campos como chave da busca:  "nome", "latitude","longitude","codigo_uf" e "ddd". Deste modo você terá que instanciar cinco AVLs,  uma para cada campo. O registro armazenado deve conter a chave de busca + o código_ibge.  

Observe que na AVL  adaptada as chaves replicadas são armazenadas um mesmo nó. Por exemplo todas as cidades com DDD 67 serão amazenadas em um mesmo nó.

## Tarefa 3: Combinação de  range queries.
Descrição:  Considere as seguintes três queries: (1) cidades com latitude > 50,  (2) 20 < longitude < 30 e (3) DDD == 67. Cada query irá retornar um conjunto de códigos ibge. A combinação consiste em fazer a intersecção desses conjuntos. 

## Tarefa 4: Interface
Faça uma interface para que seja possível fazer range queries e combinação de range queries com qualquer um dos cinco campos definidos na tarefa 2. A busca deve retornar todos do campos das cidades fornecidas na base de dados. Para a busca das cidades pelo código IBGE você deve utilizar uma tabela hash.  



