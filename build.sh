# se nao existir, cria
mkdir -p out data 2> /dev/null || mkdir out data 2> nul

# compila
echo "Compilando Jogo..."
gcc src/first.c awtils/awtils.c -Iawtils -o out/first && \
echo "Compilando Alimentador do jogo..."
gcc src/second.c awtils/awtils.c -Iawtils -o out/second
echo "Pronto, os executáveis estao na pasta out"