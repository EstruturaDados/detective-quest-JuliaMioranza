# Detective Quest — Mapa da Mansão (árvore binária)

Projeto simples, direto ao ponto, simulando a exploração de uma mansão usando árvore binária. O jogador começa no **Hall de entrada** e decide seguir para **esquerda (e)**, **direita (d)** ou **sair (s)**. A exploração termina quando chega a um cômodo sem saídas.

## Como funciona

- Cada nó da árvore é um cômodo com `nome`, `esquerda` e `direita`.
- A árvore é montada automaticamente na `main()` com `criarSala()` 
- `explorarSalas()` mostra o cômodo atual, imprime o caminho percorrido e pergunta o próximo passo.
- Se o cômodo não tiver filhos, acabou a aventura naquele ponto. Simples assim.


               [Hall de entrada]
                /              \
       [Biblioteca]          [Corredor Leste]
        /        \             /            \
[Escritorio]  [Jardim]  [Cozinha]        [Sala de Jantar]
                              \
                           [Despensa]
```

## Funções

- `criarSala(const char* nome)` — aloca e retorna um nó com o nome informado.
- `explorarSalas(Sala* raiz)` — loop de navegação: aceita `e`, `d` ou `s`, imprimindo cada sala visitada.
- `liberarArvore(Sala* raiz)` — libera geral (pensando na memória)
- `main(void)` — monta o mapa e chama a exploração.

## Entrada válida

- `e` / `E` → segue para a esquerda, se existir.
- `d` / `D` → segue para a direita, se existir.
- `s` / `S` → encerra a exploração.

