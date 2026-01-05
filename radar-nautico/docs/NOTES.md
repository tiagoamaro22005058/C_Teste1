# NOTES.md — Decisões de Implementação

Este documento define decisões técnicas e interpretações do enunciado do
Projeto Final de Linguagens de Programação I (Radar Náutico), com o objetivo de
eliminar ambiguidades e garantir comportamento consistente do programa.

---

## 1. Sistema de Coordenadas do Radar

- O radar tem dimensões `L x A` (largura x altura).
- A origem `(0,0)` corresponde ao canto superior esquerdo.
- O eixo X cresce para a direita.
- O eixo Y cresce para baixo.

Uma entidade está **fora do radar** se:
- `x < 0`
- `x >= L`
- `y < 0`
- `y >= A`

Entidades fora do radar são removidas da lista do frame atual.

---

## 2. Movimento das Embarcações

Cada embarcação possui:
- posição inicial `(x, y)`
- ângulo (múltiplos de 45º)
- velocidade (inteiro positivo)

O deslocamento por frame é calculado como:

| Ângulo | dx | dy |
|------:|---:|---:|
|   0°  | +v |  0 |
|  45°  | +v | -v |
|  90°  |  0 | -v |
| 135°  | -v | -v |
| 180°  | -v |  0 |
| 225°  | -v | +v |
| 270°  |  0 | +v |
| 315°  | +v | +v |

Onde `v` é a velocidade.

---

## 3. Simulação de Frames

- A simulação avança frame a frame.
- Em cada frame:
  1. Atualizam-se as posições de todas as embarcações
  2. Removem-se embarcações fora do radar
  3. Detetam-se colisões
  4. Guarda-se o estado do frame no histórico

---

## 4. Colisões

- Ocorre colisão quando **duas ou mais embarcações ocupam a mesma posição (x,y)
  no mesmo frame**.
- Todas as embarcações envolvidas numa colisão são removidas do frame.
- A colisão só é avaliada **após todas as posições do frame estarem atualizadas**.

---

## 5. Estruturas de Dados

### 5.1 Lista de Entidades (EntidadeIED)
- Lista ligada simples
- Contém as embarcações de um frame
- Cada nó representa uma embarcação
- Inserção mantém a ordem de leitura do ficheiro ou de inserção manual

### 5.2 Histórico de Frames (BaseDados)
- Lista ligada de frames
- Cada frame contém a sua própria lista de EntidadeIED
- Usado para:
  - voltar atrás (opção 4)
  - análise histórica

---

## 6. Histórico e Opção 4 (Reverter Frames)

- O histórico guarda **cópias independentes** dos frames
- Não são usados apontadores partilhados entre frames
- Ao voltar atrás:
  - os frames futuros são libertados com `free()`
  - o frame selecionado passa a ser o atual

---

## 7. Frames = 0

- Se o número de frames for `0`:
  - o programa **não avança automaticamente**
  - entra diretamente no menu interativo
  - nenhuma simulação é feita até ação do utilizador

---

## 8. Input e Output

- O ficheiro de input (`antes.txt`) é lido apenas uma vez no início.
- O ficheiro de output é sobrescrito no arranque do programa.
- Cada frame é escrito sequencialmente no ficheiro de saída.

A formatação do output segue **estritamente** o modelo do enunciado.

---

## 9. Tipos Especiais de Embarcação

Considerando que o último dígito do número de aluno é **8**, os tipos especiais
implementados são:

- Tipo 1 — ProfPaiMau
- Tipo 2 — Cruzador
- Tipo 3 — Submarino
- Tipo 12 — Porta-Aviões

O comportamento específico de cada tipo é implementado de acordo com o
enunciado e documentado no respetivo módulo (`sim.c` ou `collision.c`).

---

## 10. Gestão de Memória

- Não existem variáveis globais ou estáticas.
- Toda a memória dinâmica é alocada com `malloc()` / `calloc()`.
- Toda a memória alocada é libertada com `free()`:
  - ao remover embarcações
  - ao apagar frames do histórico
  - ao terminar o programa
- O código deve estar livre de memory leaks (testável com Valgrind).

---

## 11. Compilação

O projeto compila obrigatoriamente com:
-Wall -Wextra -g -Wvla -Wpedantic -Wdeclaration-after-statement -lm

Qualquer warning é considerado erro a corrigir.

## 12. Objetivo deste Documento
Este ficheiro serve para:
- alinhar comportamento entre membros do grupo
- evitar interpretações erradas do enunciado
- permitir que ferramentas automáticas (ex.: Codex) modifiquem o código
  sem introduzir comportamento inválido
