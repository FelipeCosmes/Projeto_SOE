# Detector de Fadiga

## Projeto Final da Disciplina FGA0103 - Sistemas Operacionais Embarcados

- Professor: Diogo Caetano Garcia

## Objetivo do Trabalho Final

Esse projeto tem por finalidade aplicar os conhecimentos de sistemas embarcados obtidos no decorrer do semestre. 

- Conhecer os fundamentos básicos de sistemas embarcados;
- Compreender o processo de desenvolvimento de software para um sistema embarcado;
- Conhecer as técnicas de desenvolvimento de aplicações e drivers para sistemas embarcados.

## Explicação do Projeto

Sono e cansaço estão entre os principais motivos pelos quais acontecem acidentes nas estradas brasileiras. A probabilidade de uma sinistralidade acontecer é maior se o condutor dorme menos do que o período recomendado. Basta um momento de cansaço ou distração para que o pior aconteça. Cerca de 60% dos acidentes são causados por sono ou fadiga, o que mostra a seriedade do assunto. É por isso que, cada vez mais, as empresas e profissionais fazem uso do sensor de fadiga. Sendo assim, o sensor de fadiga é um importante instrumento que atua para identificar os comportamentos de risco e alertar o condutor em tempo real. Os alertas na cabine auxiliam os condutores a manterem o foco na estrada, reduzindo riscos e os conscientizando sobre a importância de uma condução segura.

O dispositivo serve, antes de tudo, para proteção. Afinal, ao acompanhar o estado do condutor e emitir alerta quando necessário, preza pela integridade física dos motoristas. A proteção também é válida para o veículo e demais bens patrimoniais do condutor. Evitando, assim, gastos desnecessários. Além disso, no ramo de transportes, os dados obtidos pelo sensor podem ajudar as empresas a detectar os perfis dos motoristas e, assim, indicá-los a rotas onde esses profissionais sentem mais fadiga, distração ou sono. Assim, age-se preditivamente para evitar acidentes e problemas associados.

O projeto desenvolvido visa avaliar o intervalo entre o nível do olho do condutor e a partir disso avaliar se o condutor está com fadiga ou não, caso seja identificada a fadiga, o alarme seria ativado e despertaria o motorista. Além disso, é possível ir além da detecção da fadiga, é possível detectar quando o usuário está mexendo no celular, está bebendo e fumando.

## Teste de Utilização

<p align="center">
  <img src="https://github.com/FelipeCosmes/Projeto_SOE/blob/main/imagens/detection.png" alt="Teste" width="400"/>
</p>

Note que há o desenho dos olhos do usuário. Além disso, há o cálculo do EAR (Eye Aspect Ratio), essa informação que é responsável por determinar se o usuário está com os olhos fechados ou não.

## Como Rodar o Código C++

* Vá até a pasta do código c++

> `cd Projeto_SOE/código-fonte/Codigo_cpp`

* Para compilar o código, basta executar o aquivo bash start.sh

> `./start.sh`

* Após compilar, basta executar o programa criado

> `./build/projeto_SOE`

## Como Rodar o Código Python

* Vá até a pasta do código em python

> `cd Projeto_SOE/código-fonte/Codigo_python`

* Para compilar o código, basta executar o seguinte comando

> `python3 detector_fadiga.py`
