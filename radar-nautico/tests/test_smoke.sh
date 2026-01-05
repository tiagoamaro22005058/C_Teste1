#!/usr/bin/env bash
set -euo pipefail

# Exemplo: correr 0 frames e sair logo, garantindo que escreve output
./radar antes.txt 20x80 0 out.txt <<EOF
0
EOF

test -s out.txt
echo "OK: output gerado"
