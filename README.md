# Decibelímetro

## Descrição
Projeto utilizando arduino para medir volume do som no ambiente e avisar caso exceda um certo limite.

## Materiais usados
  - Arduino
  - Decibelímetro
  - Buzzer

## Algoritmo
As leituras do sensor do decibelímetro oscilam em torno de um valor, variando em amplitude de acordo com a intensidade do som.

Para obter o valor médio são armazenadas diversas leituras anteriores e a média é calculada em cima deles. Para acelerar o cálculo da média é utilizado um vetor com os valores das últimas leituras. O valor novo é somado e o valor a ser sobreescrito no vetor é subtraído da conta.

São calculadas as diferenças entre o valor médio e o valor lido no sensor. É feita uma média dessas diferenças seguindo o mesmo esquema para evitar que um pico sozinho consiga ativar o aviso sonoro.