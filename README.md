# Criptografia em C: Cifra de César + Sequência Numérica

**Disciplina:** Algoritmo e Pensamento Computacional
**Professor:** Francisco de Assis Cavallari
**Atividade:** Atividade Avaliativa 02
**Integrantes:** _(preencher com os nomes do quarteto)_

---

## Sobre o projeto

Programa em linguagem C que une **criptografia simples** e **matemática aplicada (progressões e séries)**. A palavra secreta passa por **duas camadas** de criptografia e o resultado é gravado em arquivo.

O trabalho é fundamentado na **Taxonomia de Bloom** (lembrar, compreender, aplicar, analisar, avaliar e criar), conforme descrito no enunciado.

## Como funciona

O usuário informa:

1. Uma **palavra secreta** (até 15 letras, sem acentos nem caracteres especiais);
2. Um valor de **SHIFT** (ex.: 3 desloca `A` para `D`);
3. A **sequência numérica** usada na segunda camada (neste projeto: **Fibonacci**).

O programa então aplica:

| Camada | Técnica | Descrição |
|--------|---------|-----------|
| **Camada 1** | Cifra de César | Desloca cada letra em um SHIFT **fixo** |
| **Camada 2** | Deslocamento dinâmico | Desloca cada letra pelo termo correspondente da sequência |

O deslocamento total de cada letra é:

```
deslocamento total = SHIFT + sequência[i]
```

### Detalhes da implementação

- Usa a **tabela ASCII**: a letra é convertida para a posição `0–25` subtraindo a base (`'a'` ou `'A'`), recebe o deslocamento e volta para a faixa do alfabeto com `% 26`.
- Maiúsculas e minúsculas são preservadas.
- O SHIFT é normalizado para `0–25`, o que permite valores maiores que 26 e também negativos.
- Os termos de Fibonacci são calculados com `% 26` a cada passo, evitando estouro de `int`.
- A palavra é validada antes da criptografia: entre 1 e 15 letras, apenas caracteres alfabéticos.

## Sequência utilizada: Fibonacci

```
F(n) = F(n-1) + F(n-2), com F(1) = 1 e F(2) = 1
1, 1, 2, 3, 5, 8, 13, 21, ...
```

## Como compilar e executar

Requisito: compilador C (GCC).

```bash
gcc main.c -o criptografia
./criptografia
```

No Windows, execute `criptografia.exe`.

## Exemplo de execução

**Entrada**

```
Palavra: coracao
SHIFT: 3
Sequência: Fibonacci
```

**Cálculo interno**

| Letra | Posição | SHIFT | Fibonacci | Total | Resultado |
|:-----:|:-------:|:-----:|:---------:|:-----:|:---------:|
| c | 2  | 3 | 1  | 4  | **g** |
| o | 14 | 3 | 1  | 4  | **s** |
| r | 17 | 3 | 2  | 5  | **w** |
| a | 0  | 3 | 3  | 6  | **g** |
| c | 2  | 3 | 5  | 8  | **k** |
| a | 0  | 3 | 8  | 11 | **l** |
| o | 14 | 3 | 13 | 16 | **e** (30 mod 26 = 4) |

**Saída**

```
Palavra criptografada: gswgkle
```

**Arquivo gerado (`resultado_criptografia.txt`)**

```
Palavra codificada: gswgkle | SHIFT: 3 | Tipo: Fibonacci | Letras: 7
```

### Observação sobre o exemplo do enunciado

O exemplo do enunciado apresenta `fqvdjqb` como saída para `coracao`, SHIFT 3 e Fibonacci. Porém, aplicando a fórmula que o próprio enunciado descreve (`SHIFT + sequência[i]`), o resultado correto é **`gswgkle`**, conferido letra a letra na tabela acima. O programa segue a fórmula do enunciado, por isso a saída difere do exemplo.

## Estrutura do repositório

```
.
├── main.c                        # código-fonte
├── resultado_criptografia.txt    # gerado a cada execução
└── README.md
```

## Taxonomia de Bloom aplicada ao projeto

| Nível | Atividade no projeto |
|-------|----------------------|
| **Lembrar** | Revisar o alfabeto, os valores ASCII e as progressões numéricas |
| **Compreender** | Entender o efeito de diferentes SHIFTs e como funciona a cifra |
| **Aplicar** | Implementar a criptografia em C (César + sequência) |
| **Analisar** | Comparar resultados com PA, PG e Fibonacci |
| **Avaliar** | Julgar a segurança e os padrões da cifra |
| **Criar** | Gerar novas combinações e padrões de sequência |

## Limitações

- Apenas letras de `A–Z` e `a–z` são aceitas (sem acentos).
- É uma cifra didática: não deve ser usada para proteger informações reais.
- A sequência é fixa (Fibonacci). Para trocar por PA, PG ou primos, basta alterar o trecho que avança os termos na camada 2.
