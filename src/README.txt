#Dependências

- API GraphViewer, fornecida nas aulas, para visualização de grafos.

#Input files

Os ficheiros com informações relativas ao contexto do problema encontram-se na pasta 'maps/Porto_maps' com os respetivos mapas do Porto.
São utilizados no programa os seguintes ficheiros 'porto_full_nodes_xy.txt' e 'porto_full_edges.txt'.
Para questões de teste, incluímos também mapas de grelhas (pasta 'maps/GridGraphs').

#Instruções de compilação
1. Para compilar o projeto é necessária uma instalação CLion.
2. Criação de um projeto novo com pasta 'src/' como raiz e compilar.

#Instruções de utilização
- Correr o programa
- Na consola aparecerá os passos que o programa está a executar. Inicialmente, carrega o mapa e desenha-o.
- Depois, todo o controlo do programa será a partir de um Menu.

- Numa primeira fase, poderá adicionar encomendas ("Insert Baskets"; vértice das entregas colocados a verde)
e começar a distribuição ("Start").

- Após selecionada a opção "Start", será realizado um pré-processamento do grafo, eliminando todos os vértices inacessíveis e
encomendas impossíveis de entregar. O mapa será redesenhado e vértice da empresa colocado a amarelo.
- Fica ao critério do utilizador selecionar o tipo de distribuição, se opta por a primeira iteração do problema onde apenas um
veículo de capacidade ilimitada faz a entrega ou se vários veículos com capacidade limitada (segunda iteração).

- Para a segunda iteração, é possível adicionar veículos e começar a distribuição.

- Após a distribuição, o trajeto dos veículos será mostrada na janela com a mudança de cor das arestas (Mensagem "About to color" e "Done").

- É preciso fechar a janela da visualização do grafo para podermos terminar o programa.
