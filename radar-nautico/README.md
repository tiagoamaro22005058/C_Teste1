# Radar Náutico (LP1)

## Build
make

Compila com:
-Wall -Wextra -g -Wvla -Wpedantic -Wdeclaration-after-statement -lm

## Run
./radar antes.txt 20x80 1000 depois.txt

## Regras (obrigatórias)
- Sem variáveis globais ou estáticas
- Estruturas e listas ligadas: BaseDados (frames) e EntidadeIED (entidades)
- malloc/free obrigatórios, sem memory leaks
- Remover barcos afundados ou fora do radar da lista do frame

## Tipos especiais implementados (meu nº: ... último dígito 8)
Tipos: 1 (ProfPaiMau), 2 (Cruzador), 3 (Submarino), 12 (PortaAvioes)

## Testes
make test
