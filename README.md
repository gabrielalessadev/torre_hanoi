# Projeto Torre de Hanoí em C

    Torre de Hanoí 

     Movimentos: 0

        |                     |                     |
      (=1=)                   |                     |
     (==2==)                  |                     |
    (===3===)                 |                     |
        A                     B                     C

## Funcionalidades

- **Interface Grafica no Terminal:** O jogo e exibido de forma visual, com os discos desenhados em tamanhos de acordo com sua numeração para clareza.
- **Controles Intuitivos:** Os movimentos são feitos com letras (ex: `AB`, `BC`), e o jogo oferece a opção de reiniciar (`R`) ou sair da partida (`S`) a qualquer momento.
- **Sugestao de Jogada:** Em cada turno o jogo calcula e exibe o próximo movimento para resolver a Torre de Hanói no menor número de movimentos possíveis.
- **Regra de Vitoria Flexivel:** O jogador pode completar o desafio movendo a torre final tanto para o pino B quanto para o pino C.
- **Historico de Partidas:** O jogo salva automaticamente as partidas vitoriosas em um arquivo (`historico_partidas.txt`), registrando o nome do jogador, número de discos, movimentos e a data/hora.
- **Visualizacao e Busca:** O menu principal permite visualizar o histórico completo ou buscar por partidas de um jogador especifico ou por data estipulada.

## Como Compilar e Executar

1.  Clone ou baixe o repositório.
2.  Abra um terminal e navegue ate a pasta raiz do projeto.
3.  Execute o seguinte comando para compilar:

    ```sh
    gcc -o hanoi_game main.c hanoi.c pilha.c historico.c -Wall -Wextra
    ```

4.  Após a compilação, um executavel chamado `hanoi_game` (`hanoi_game.exe` no Windows) será criado e para jogar, execute-o:

    ```sh
    ./hanoi_game
    ```

## Como Jogar

- **Menu Principal:** Use os números para navegar entre `Novo Jogo`, `Ver Historico`, `Buscar no Historico` e `Sair`.
- **Durante a Partida:**
    - Para mover um disco, digite a letra do pino de **origem** seguida da letra do pino de **destino**, sem espaço (ex: `AC` para mover de A para C).
    - Digite `R` e pressione Enter para **reiniciar** a partida atual.
    - Digite `S` e pressione Enter para **sair** da partida e voltar ao menu principal.

## Estrutura do Projeto

- `main.c`: Contem a logica principal do programa, o menu e os loops de jogo.
- `hanoi.c` / `hanoi.h`: Define a logica do jogo, as regras de movimento, a exibicao do tabuleiro e o calculo da jogada.
- `pilha.c` / `pilha.h`: Implementa a estrutura de dados de pilha, usada para representar os pinos da torre.
- `historico.c` / `historico.h`: Gerencia o historico de partidas, incluindo salvar, carregar e buscar em arquivo.

## Projeto ministrado pelo Professor João Robson na matéria de estrutura de dados 

Autor: Gabriel Alessandro Lima Silva