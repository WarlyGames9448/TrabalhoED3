# Sistema de Matchmaking

## Descrição do Projeto
Este projeto implementa um sistema básico de *matchmaking* em C++. Ele gerencia uma fila de espera de jogadores, permitindo a inserção, remoção e organização estruturada com base nas pontuações (scores) e no tempo de entrada na fila (timestamps).

O sistema conta com algoritmos clássicos de ordenação (**Insertion Sort** e **Merge Sort**) e possui uma lógica especializada para agrupar jogadores com habilidades semelhantes (baseado em uma tolerância `delta` de score), simulando o comportamento de servidores de jogos multiplayer.

## Organização dos Arquivos
O projeto está dividido nos seguintes arquivos principais:

* **`Player.hpp` / `Player.cpp`**: Contêm a definição e a implementação da classe `Player`, que representa um jogador individual com atributos como ID, Nome, Score e Timestamp.
* **`Matchmaking.hpp` / `Matchmaking.cpp`**: Contêm a lógica principal do sistema. Gerenciam um array dinâmico de jogadores, as funções de ordenação e o algoritmo de formação de grupos (`formGroup`).
* **`main.cpp`**: Ponto de entrada do programa. Contém a suíte de testes automatizados que demonstra as capacidades e o funcionamento correto de todas as funções do sistema de *matchmaking*.

## Instruções de Compilação
Para compilar o projeto, você precisará de um compilador C++.

Abra o terminal na pasta raiz do projeto e execute o seguinte comando:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
