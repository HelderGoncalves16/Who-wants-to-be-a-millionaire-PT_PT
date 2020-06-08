#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <conio.h>

#include <dos.h>

#include <windows.h>

#include <time.h>

#include <locale.h>

// Variaveis globais

int premios[15] = {
  25,
  50,
  125,
  250,
  500,
  750,
  1500,
  2500,
  5000,
  10000,
  16000,
  32000,
  64000,
  125000,
  250000
};
int x, i, n, questaoNumero, tentativa, recebeQuestao = 0, totalGanho, contadorVidas = 0;
char nome[100], vida[3];
int pontuacaoOrdenada[300];
char converterScore[10][300];
char converterTentativa[100];

//FUNCOE DECLARADAS ERRO DE CONFLICTING TYPES

void login(void);
void reg(void);
void admin(void);
void mostraPerguntas(int nivel);
void usarVida(char respostaCorreta, int recebeQuestao);
void erroFicheiro(void);
void questaoErrada(void);
void recebeResposta(int recebeQuestao, int nivel, char respostaCorreta);
void enviarParaPontuacao(char * nome, int score);
void mostrarScores(void);
void escreveScore(void);
void imprimeOrdenacao(void);
void ordenaPontuacao2(int * aNumber, int size);
void lerScore(void);
char gerarRespostaErrada(char correta);
void ligarAmigo(char correta);
void ligarAmigoInteligente(char correta);
void ligarAmigoIncerto(char correta);
void mostrar5050(char correta, int recebeQuestao);
void perguntarAudiencia(char correta);
void mostrarQuestoesNovamente();
void jogar();
void listarJogadores();
void ordenarArray(int * aNumber, int size);

// -------------------------------------------------------------

struct utilizador {
  int tentativas;
  char name[30];
  char pass[30];
  char pontuacao[7];
}
w[99], top[10];

struct niveis {
  char pergunta[120];
  char opcA[70];
  char opcB[70];
  char opcC[70];
  char opcD[70];
  char resposta[5];
}
perguntas[15];

// Esta Struct Recebe os ficheiros que contem as perguntas
// Cada ficheiro contém 15 perguntas

// DECLARAR FICHEIROS

FILE * fp;
FILE * primeiroNivel;
FILE * segundoNivel;
FILE * terceiroNivel;
FILE * pontuacoes;
FILE * pontuacoes2;

int main() {

  setlocale(LC_ALL, "Portuguese");

  //Reset
  totalGanho = 0;
  questaoNumero = 0;
  vida[0] = 'X';
  vida[1] = 'X';
  vida[2] = 'X';
  contadorVidas = 0;

  system("cls");
  printf("\n\t\t\t\t\t\tBEM VINDO AO");
  printf("\n\t\t\t\t\tQUEM QUER SER MILIONÁRIO");
  printf("\n\n\t\t\t\t=============================================");
  printf("\n\t\t\t\t\tPressiona Enter para Continuar!! ");

  if (getch() == 13) // Tecla Enter

    XY:

    system("cls");

  printf("\n\n\n\t\t\t1. JOGAR (APENAS UTILIZADORES REGISTADOS)");
  printf("\n\t\t\t2. REGISTAR NOVO UTILIZADOR");
  printf("\n\t\t\t3. MODO ADMINISTRADOR");
  printf("\n\t\t\t4. SAIR");
  printf("\n\t\t\tDIGITE A SUA OPÇÃO: ");

  scanf("%d", & n);

  switch (n) {

  case 1:

    login();
    jogar();
    break;

  case 2:

    reg();
    break;

  case 3:

    admin();
    break;

  case 4:

    system("cls");
    printf("\n\n\t\t\t\t\tA SAIR DO JOGO! OBRIGADO!");
    exit(1);

  default:
    printf("\n\n\t\t\t\tPOR FAVOR DIGITE UMA OPÇÃO CORRETA!");

    if (getch() == 13)

      goto XY;

  }

  goto XY;
  return 0;

}
void jogar() {
  system("cls");
  printf("\n\t\t\tBEM-VINDO À PRIMEIRA FASE DO QUEM QUER SER MILIONÁRIO");
  printf("\n\t\t\tNESTA FASE SERÃO 5 PERGUNTAS\n");
  printf("\t\t\tCUJO VALORES PARA CADA PERGUNTA É DE: \n\n\t\t\t1 - 25 Euros\n\t\t\t2 - 50 Euros\n\t\t\t3 - 125 Euros\n\t\t\t4 - 250 Euros\n\t\t\t5 - 500 Euros\n");
  printf("\n\t\t\tPREPARADO %s ? VAMOS COMEÇAR? ", nome);
  getch();
  primeiroPatamar();
  segundoPatamar();
  terceiroPatamar();
  printf("PARABENS ACABOU DE SE TORNAR MILIIONÁRIO!!");

}
void admin() {

  char opc;
  char passwordAdmin[15];
  system("cls");
  printf("\n\t\t\tDIGITE A PASSWORD DE ACESSO AO MENU DE ADMIN: ");
  scanf("%s", & passwordAdmin);
  if (strcmp(passwordAdmin, "helder22067") == 0) {

    system("cls");
    printf("\n\t\t\tA - MOSTRAR SCORES");
    printf("\n\t\t\tB - LISTAR JOGADORES");
    printf("\n\t\t\tC - SAIR");
    printf("\n\t\t\tOPÇÃO: ");

    do {
      opc = toupper(getch());
    } while (opc != 'A' && opc != 'B' && opc != 'C');

    switch (opc) {
    case 'A':
      mostrarScores();
      break;
    case 'B':
      listarJogadores();
      break;
    case 'C':
      main();
      break;
    }

  } else {
    printf("\n\t\t\tPASSWORD ERRADA - A VOLTAR PARA O MENU INICIAL...");
    sleep(2);
    main();
  }

}

void listarJogadores() {

  system("cls");

  fp = fopen("Utilizadores.txt", "r");
  if (fp == NULL) {
    erroFicheiro();
  }

  printf("\n\t\t\tUTILIZADORES LOGADOS NO SISTEMA");
  while (!feof(fp))

  {
    fread( & w[i], sizeof(w[i]), 1, fp);
    printf("\n\t\t\tNOME = %s", w[i].name);

  }
  getch();
  fclose(fp);
}

void reg()

{

  system("cls");
  char c;
  int z = 0;

  fp = fopen("Utilizadores.txt", "a");

  printf("\n\n\t\t\t\t\tZONA DE REGISTO");

  printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

  for (i = 0; i < 100; i++)

  {
    do {

      XY:

        printf("\n\n\t\t\t\tDIGITE O SEU USERNAME: ");

      scanf("%s", & nome);

      if (strlen(nome) < 4 || strlen(nome) > 12) {
        printf("\n\t\t\tO seu Username deve conter mais de 4 caracteres e menos de 12");
      }

    } while (strlen(nome) < 4 || strlen(nome) > 12);

    while (!feof(fp))

    {

      fread( & w[i], sizeof(w[i]), 1, fp);

      if (strcmp(nome, w[i].name) == 0) //Verifica se o username já existe no ficheiro

      {

        printf("\n\n\t\t\tO USERNAME INSERIDO JA EXISTE");
        goto XY;

      } else

      {

        strcpy(w[i].name, nome);

        break;

      }

    }

    printf("\n\n\t\t\t\tDIGITE A SUA PASSWORD: ");

    while ((c = getch()) != 13)

    {

      w[i].pass[z++] = c;

      printf("%c", '*');

    }

    fwrite( & w[i], sizeof(w[i]), 1, fp); //Escreve o Username e Password para o Ficheiro
    fprintf(fp, "\n");
    fclose(fp);

    printf("\n\n\t\t\tPressionar Enter para confirmar o Username e Password inseridos!");

    if ((c = getch()) == 13)

    {
      system("cls");
      printf("\n\t\t\tRegisto Efetuado com Sucesso!");
      printf("\n\t\t\tPREPARA-SE PARA INICIAR O JOGO!");
      sleep(2);
      jogar();

    }

    break;

  }

  jogar();
  getch();

}

void login()

{

  system("cls");

  FILE * fp;

  char c, pass[30];
  int z = 0;

  int checku, checkp;

  fp = fopen("Utilizadores.txt", "r+");

  system("cls");
  printf("\n\n\t\t\t\tEFETUA O LOGIN ANTES DE JOGAR!");

  printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^");
  printf("\n\t\t\t\tUSERNAME: ");

  scanf("%s", nome);

  printf("\n\t\t\t\tPASSWORD: ");

  while ((c = getch()) != 13)

  {

    pass[z++] = c;

    printf("%c", '*');

  }

  pass[z] = '\0';

  while (!feof(fp))

  {

    fread( & w[i], sizeof(w[i]), 1, fp);

    checku = strcmp(nome, w[i].name);

    checkp = strcmp(pass, w[i].pass);

    if (checku == 0 && checkp == 0)

    {

      system("cls");
      printf("\n\t\t\tLOGIN EFETUADO COM SUCESSO!!\n");
      fclose(fp);
      jogar();
      break;
    } else if (checku != 0) {

      system("cls");
      printf("\n\n\t\t\tUTILIZADOR NÃO REGISTADO!\n\n\t\t\tPRESSIONA ENTER PARA EFETUAR REGISTO!");
      printf("\n\t\t\tOUTRA TECLA PARA VOLTAR MENU INICIAL!");

      if (getch() == 13) {
        reg();
      } else {
        main();
      }
    }

  }
  getch();

}

int primeiroPatamar() { //Carregar as perguntas do Ficheiro primeiroNivel	
  if ((primeiroNivel = fopen("primeiroNivel.TXT", "r")) == NULL) {
    erroFicheiro();
  } else {
    while (!feof(primeiroNivel)) {
      for (x = 0; x < 15; x++) {
        fgets(perguntas[x].pergunta, 120, primeiroNivel);
        fgets(perguntas[x].opcA, 70, primeiroNivel);
        fgets(perguntas[x].opcB, 70, primeiroNivel);
        fgets(perguntas[x].opcC, 70, primeiroNivel);
        fgets(perguntas[x].opcD, 70, primeiroNivel);
        fgets(perguntas[x].resposta, 70, primeiroNivel);
      }
    }
  }
  mostraPerguntas(1); //Mostrar as Perguntas Armazenadas
  fclose(primeiroNivel);
}

int segundoPatamar() {
  if ((segundoNivel = fopen("segundoNivel.txt", "r")) == NULL) {
    erroFicheiro();
  } else {
    while (!feof(segundoNivel)) {
      for (x = 0; x < 15; x++) {
        fgets(perguntas[x].pergunta, 120, segundoNivel);
        fgets(perguntas[x].opcA, 70, segundoNivel);
        fgets(perguntas[x].opcB, 70, segundoNivel);
        fgets(perguntas[x].opcC, 70, segundoNivel);
        fgets(perguntas[x].opcD, 70, segundoNivel);
        fgets(perguntas[x].resposta, 70, segundoNivel);
      }
    }
  }
  mostraPerguntas(2); //Mostrar as Perguntas Armazenadas
  fclose(segundoNivel);
}

int terceiroPatamar() {
  if ((terceiroNivel = fopen("teceiroNivel.TXT", "r")) == NULL) {
    erroFicheiro();
  } else {
    while (!feof(terceiroNivel)) {
      for (x = 0; x < 15; x++) {
        fgets(perguntas[x].pergunta, 120, terceiroNivel);
        fgets(perguntas[x].opcA, 70, terceiroNivel);
        fgets(perguntas[x].opcB, 70, terceiroNivel);
        fgets(perguntas[x].opcC, 70, terceiroNivel);
        fgets(perguntas[x].opcD, 70, terceiroNivel);
        fgets(perguntas[x].resposta, 70, terceiroNivel);
      }
    }
  }
  mostraPerguntas(3); //Mostrar as Perguntas Armazenadas
  fclose(terceiroNivel);
}

void mostraPerguntas(int nivel) {

  char opc;
  int contadorQuestao; // Numero Total de Questões por nível
  int questaoMostra[5] = {
    -1,
    -1,
    -1,
    -1,
    -1
  };
  int qu = 0; //Para enviar questoes para o questaoMostra;

  system("cls");
  srand(time(NULL));
  for (contadorQuestao = 0; contadorQuestao < 5; contadorQuestao++) {

    questaoNumero++; // Para o numero da questao nao ser 0

    do {

      recebeQuestao = (rand() % 15); //Gera um numero Random até 15

    } while (recebeQuestao == questaoMostra[0] || recebeQuestao == questaoMostra[1] || recebeQuestao == questaoMostra[2] || recebeQuestao == questaoMostra[3] || recebeQuestao == questaoMostra[4]);

    questaoMostra[qu] = recebeQuestao;

    if (questaoNumero != 1) { //Este codigo nao pode aparecer logo na primeira Questão (Possiblidade de Desistir)

      printf("\n\t\t\tPRETENDE CONTINUAR? %s ?", nome);
      printf("\n\t\t\tA - CONTINUAR\n\t\t\tB - DESISTIR COM %d ", totalGanho);

      do {

        opc = toupper(getch()); //Função que converte uma letra miniscula em letra maiuscula

      } while (opc != 'A' && opc != 'B');
    }

    if (opc == 'B') {
      system("cls");
      printf("\n\t\t\tGANHOU: %d", totalGanho);
      printf("\n\t\t\tOBRIGADO POR JOGAR AO QUEM QUER SER MILIONÁRIO? %s", nome);
      enviarParaPontuacao(nome, totalGanho);
      exit(1);
      break;

    } else {

      system("cls");

      if (questaoNumero != 1) {
        printf("\n\t\t\tOK %s ! VAMOS ENTÃO SEGUIR PARA A PRÓXIMA QUESTÃO!\n", nome);
      }

      //-------------- QUESTÕES --------------------
      printf("\n\t\t\tQuestão %d\n", questaoNumero);
      printf("\t\t\t%s", perguntas[recebeQuestao].pergunta);
      printf("\t\t\t%s", perguntas[recebeQuestao].opcA);
      printf("\t\t\t%s", perguntas[recebeQuestao].opcB);
      printf("\t\t\t%s", perguntas[recebeQuestao].opcC);
      printf("\t\t\t%s", perguntas[recebeQuestao].opcD);

      depoisPerguntas:
        printf("\n\t\t\t%s, O QUE VOCE PRETENDE FAZER?", nome);
      printf("\n\t\t\tA - RESPONDER.");
      if (questaoNumero != 15) {
        printf("\n\t\t\tB - USAR AJUDA.");
      }

      if (contadorVidas != 3) {
        printf("\n\t\t\tVIDAS RESTANTES: %d ", 3 - contadorVidas);
      } else {
        printf("\n\t\t\tNÃO EXISTEM MAIS VIDAS!\n");
      }

      if (questaoNumero != 1) {
        if (questaoNumero == 15) {
          printf("\n\t\t\tC - SAIR COM METADE DOS GANHOS ATUAIS. ");
        } else {
          printf("\n\t\t\tC - SAIR COM METADE DOS GANHOS ATUAIS. ");
        }
        do {
          opc = toupper(getch());
        } while (opc != 'A' && opc != 'B' && opc != 'C');
        goto adiante;
      } else if (questaoNumero == 15) {
        do {
          opc = toupper(getch());
        } while (opc != 'A' && opc != 'C');
      } else
        do {
          opc = toupper(getch());
        } while (opc != 'A' && opc != 'B');

      adiante:
        mostrarQuestoesNovamente();
      if (vida[0] == 'A' && vida[1] == 'B' && vida[2] == 'C' && opc == 'B') {
        printf("\n\t\t\tVOCE JA USOU TODAS AS VIDAS!");
        goto depoisPerguntas;
      }

      switch (opc) {
      case 'A':
        break;
      case 'B':
        usarVida( * perguntas[recebeQuestao].resposta, recebeQuestao);
        break;
      case 'C':
        system("cls");
        printf("\n\t\t\tVoce decidiu desistir e ficar com metade dos ganhos atuais!");
        switch ( * perguntas[recebeQuestao].resposta) {
        case 'A':
          printf("\n\t\t\tA respota correta era a opção A: %s", perguntas[recebeQuestao].opcA);
          break;
        case 'B':
          printf("\n\t\t\tA respota correta era a opção B: %s", perguntas[recebeQuestao].opcB);
          break;
        case 'C':
          printf("\n\t\t\tA respota correta era a opção C: %s", perguntas[recebeQuestao].opcC);
          break;
        case 'D':
          printf("\n\t\t\tA respota correta era a opção D: %s", perguntas[recebeQuestao].opcD);
          break;
        }

        printf("\n\n\t\t\tGANHOU %d", totalGanho = totalGanho / 2);
        printf("\n\t\t\tOBRIGADO POR JOGAR %s", nome);

        enviarParaPontuacao(nome, totalGanho);
        exit(1);
      }

      recebeResposta(recebeQuestao, nivel, * perguntas[recebeQuestao].resposta);
      qu++;
    }
  }

}

void recebeResposta(int recebeQuestao, int nivel, char respostaCorreta) {

  char resposta;
  int opc;

  antesResposta:
    printf("\n\t\t\tOK! QUAL É A SUA RESPOSTA FINAL %s ?", nome);
  do {
    resposta = toupper(getch());
  } while (resposta != 'A' && resposta != 'B' && resposta != 'C' && resposta != 'D');

  if (nivel == 2 || nivel == 3) {
    printf("\n\t\t\tA SUA RESPOSTA É A %c . PRETENDE BLOQUEAR?", resposta);
    printf("\n\t\t\tA - SIM");
    printf("\n\t\t\tB - NÃO");
    do {
      opc = toupper(getch());
    } while (opc != 'A' && opc != 'B');

    if (opc == 'B') {
      mostrarQuestoesNovamente();
      goto antesResposta;
    }

    if (opc == 'A') {
      if (resposta == respostaCorreta) {
        system("cls");
        printf("\n\t\t\tA sua resposta está.... CORRETA!!!");
        totalGanho = premios[questaoNumero - 1];
      } else {
        questaoErrada();
      }
    }
  }
  if (resposta == respostaCorreta) {
    system("cls");
    printf("\n\t\t\tA sua resposta está.... CORRETA!!!");
    totalGanho = premios[questaoNumero - 1];
  } else {
    questaoErrada();
  }
}

void questaoErrada() {
  system("cls");
  printf("\n\t\t\tUPSSSSSSS, A RESPOSTA ESTÁ ERRADA!");

  switch ( * perguntas[recebeQuestao].resposta) {
  case 'A':
    printf("\n\n\t\t\tA respota correta era a opção A: %s", perguntas[recebeQuestao].opcA);
    break;
  case 'B':
    printf("\n\n\t\t\tA respota correta era a opção B: %s", perguntas[recebeQuestao].opcB);
    break;
  case 'C':
    printf("\n\n\t\t\tA respota correta era a opção C: %s", perguntas[recebeQuestao].opcC);
    break;
  case 'D':
    printf("\n\n\t\t\tA respota correta era a opção D: %s", perguntas[recebeQuestao].opcD);
    break;
  }
  totalGanho = totalGanho / 4;
  printf("\n\t\t\t%s , GANHOU: %d", nome, totalGanho);
  printf("\n\t\t\tOBRIGADO POR JOGAR");
  enviarParaPontuacao(nome, totalGanho);
  exit(1);
}

void usarVida(char respostaCorreta, int recebeQuestao) { //Mostra as opções de ajuda

  char vidaUsada;
  printf("\n\t\t\tESCOLHA A VIDA A USAR");
  if (vida[0] != 'A') {
    printf("\n\t\t\tA - LIGAR A UM AMIGO");
  }
  if (vida[1] != 'B') {
    printf("\n\t\t\tB - PERGUNTAR AUDIENCIA");
  }
  if (vida[2] != 'C') {
    printf("\n\t\t\tC - 50/50");
  }

  do {
    vidaUsada = toupper(getch());
  } while ((vidaUsada != 'A' && vidaUsada != 'B' && vidaUsada != 'C') || vidaUsada == vida[0] || vidaUsada == vida[1] || vidaUsada == vida[2]);

  switch (vidaUsada) {
  case 'A':
    ligarAmigo(respostaCorreta);
    vida[0] = 'A'; //Atribui o valor A a esta posição assim da proxima vez caso tenha A nao mostra esta opção
    contadorVidas++;
    break;
  case 'B':
    perguntarAudiencia(respostaCorreta);
    vida[1] = 'B';
    contadorVidas++;
    break;
  case 'C':
    mostrar5050(respostaCorreta, recebeQuestao);
    vida[2] = 'C';
    contadorVidas++;
    break;
  }
}

void ligarAmigo(char correta) {

  mostrarQuestoesNovamente();

  int tipoAmigo;
  tipoAmigo = (rand() % 2) + 1;

  switch (tipoAmigo) {
  case 1:
    ligarAmigoInteligente(correta);
    break;
  case 2:
    ligarAmigoIncerto(correta);
    break;
  }
}
void ligarAmigoInteligente(char correta) {
  mostrarQuestoesNovamente();
  srand(time(NULL));
  int probabilidade;
  probabilidade = (rand() % 10) + 1;

  if (probabilidade == 10) {
    //10 % De Probabilidade de errar
    printf("\n\t\t\tAMIGO: Eu penso que a resposta correta seja a %c", gerarRespostaErrada(correta));
  } else {
    // 90 % de a resposta recebida ser certa
    printf("\n\t\t\tAMIGO: Eu penso que a resposta certa seja a %c", correta);
  }
}

void ligarAmigoIncerto(char correta) {
  mostrarQuestoesNovamente();
  srand(time(NULL));
  int probabilidade;
  probabilidade = (rand() % 10) + 1;

  if (probabilidade <= 5) { // 50 % de falhar ou acertar
    printf("\n\t\t\tAMIGO: Eu penso que a resposta correta seja a %c", gerarRespostaErrada(correta));
  } else {
    printf("\n\t\t\tAMIGO: Eu penso que a resposta certa seja a %c", correta);
  }
}

void perguntarAudiencia(char correta) {
  mostrarQuestoesNovamente();
  srand(time(NULL));
  int probabilidade;
  probabilidade = (rand() % 100) + 1;
  int a, b, c, d;

  int audiencia[3];

  do {
    audiencia[0] = (rand() % 100) + 1;
    audiencia[1] = (rand() % 100) + 1;
    audiencia[2] = (rand() % 100) + 1;
    audiencia[3] = (rand() % 100) + 1;
  } while (audiencia[0] + audiencia[1] + audiencia[2] + audiencia[3] != 100);

  if (probabilidade <= 60) {
    ordenarArray(audiencia, 4);
    switch (correta) {
    case 'A':
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - A", audiencia[0]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - B", audiencia[a = geraNumeroRandom1()]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - C", audiencia[geraNumeroRandom2(a)]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - D", audiencia[geraNumeroRandom3(a, geraNumeroRandom2(a, audiencia))]);
      break;
    case 'B':
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - A", audiencia[a = geraNumeroRandom1()]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - B", audiencia[0]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - C", audiencia[audiencia[geraNumeroRandom2(a)]]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - D", audiencia[geraNumeroRandom3(a, geraNumeroRandom2(a, audiencia))]);
      break;
    case 'C':
      a = geraNumeroRandom1();
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - A", audiencia[a]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - B", audiencia[geraNumeroRandom2(a)]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - C", audiencia[0]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - D", audiencia[geraNumeroRandom3(a, geraNumeroRandom2(a, audiencia))]);
      break;
    case 'D':
      a = geraNumeroRandom1();
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - A", audiencia[a]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - B", audiencia[geraNumeroRandom2(a)]);;
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - C", audiencia[geraNumeroRandom3(a, geraNumeroRandom2(a, audiencia))]);
      printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - D", audiencia[0]);
      break;
    }
  } else {
    printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - A", audiencia[0]);
    printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - B", audiencia[1]);
    printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - C", audiencia[2]);
    printf("\n\t\t\t%d % DA AUDIENCIA PENSA QUE A RESPOSTA CORRETA SEJA - D", audiencia[3]);
  }
}

//FUNCOES PARA GERAR NUMEROS RANDOM

int geraNumeroRandom1() {
  int random;
  srand(time(NULL));
  do {
    random = (rand() % 4);
  } while (random == 0);
  return random;
}

int geraNumeroRandom2(int a) {
  int random;
  srand(time(NULL));
  do {
    random = (rand() % 4);
  } while (random == a || random == 0);
  return random;
}

int geraNumeroRandom3(int a, int b) {
  int random;
  srand(time(NULL));
  do {
    random = (rand() % 4);
  } while (random == a || random == 0 || random == b);

  return random;
}

void mostrar5050(char correta, int recebeQuestao) {
  system("cls");
  printf("\n\t\t\tQuestão %d", questaoNumero);
  printf("\n\t\t\t%s", perguntas[recebeQuestao].pergunta);

  char respostaCorreta;

  switch (correta) {
  case 'A':
    respostaCorreta = 1;
    break;
  case 'B':
    respostaCorreta = 2;
    break;
  case 'C':
    respostaCorreta = 3;
    break;
  case 'D':
    respostaCorreta = 4;
    break;
  }

  if (respostaCorreta == 1) {
    printf("\t\t\t%s", perguntas[recebeQuestao].opcA);
    printf("\t\t\t%s", perguntas[recebeQuestao].opcB);
  }
  if (respostaCorreta == 2) {
    printf("\t\t\t%s", perguntas[recebeQuestao].opcB);
    printf("\t\t\t%s", perguntas[recebeQuestao].opcC);
  }
  if (respostaCorreta == 3) {
    printf("\t\t\t%s", perguntas[recebeQuestao].opcC);
    printf("\t\t\t%s", perguntas[recebeQuestao].opcD);
  }
  if (respostaCorreta == 4) {
    printf("\t\t\t%s", perguntas[recebeQuestao].opcB);
    printf("\t\t\t%s", perguntas[recebeQuestao].opcD);
  }

}

void mostrarScores() {
  system("cls");
  int i = 0, j, x, y;
  int pontuacao[300];
  char opc;
  char str[10];

  if ((pontuacoes = fopen("pontuacoes.txt", "r")) == NULL) {
    erroFicheiro();
  }

  //Int para char para nao dar error de cast
  sprintf(str, "%d", w[i].tentativas);

  while (!feof(pontuacoes)) {
    fgets(str, 300, pontuacoes);
    fgets(w[i].name, 100, pontuacoes);
    fgets(w[i].pontuacao, 100, pontuacoes);
    i++;
  }

  for (j = 0; j < 300; j++) {
    pontuacao[j] = atoi(w[j].pontuacao); //converte uma string em inteiro
  }

  printf("\n\t\t\tMELHORES SCORES\n");
  for (i = 0; i < 10; i++) {
    if (strlen(w[i].name) > 1) {
      printf("\n\t\t\tNOME: %s\nSCORE: %d\n", w[i].name, pontuacao[i]);
    }
  }
  printf("\n\t\t\tA -  MENU PRINCIPAL\n\t\t\tB - SAIR");
  do {
    opc = (toupper(getch()));
  } while (opc != 'A' && opc != 'B');

  switch (opc) {
  case 'A':
    main();
    break;
  case 'B':
    system("cls");
    printf("\n\t\t\tOBRIGADO POR JOGAR %s !", nome);
    exit(1);
    break;
  }

}
void enviarParaPontuacao(char * nome, int score) {

  char opc;
  char converterPontuacao[100];
  tentativa++;

  sprintf(converterPontuacao, "%d", score);
  sprintf(converterTentativa, "%d", tentativa);

  if ((pontuacoes = fopen("pontuacoes.txt", "a")) == NULL) {
    erroFicheiro();
  }

  fprintf(pontuacoes, "Tentativa: %s", converterTentativa);
  fprintf(pontuacoes, "\n");
  fprintf(pontuacoes, "Nome: %s", nome);
  fprintf(pontuacoes, "\n");
  fprintf(pontuacoes, "Premio: %s", converterPontuacao);
  fclose(pontuacoes);

  imprimeOrdenacao();

  if (totalGanho != 1000000) {
    printf("\n\t\t\tPRESSIONA NO TECLADO PARA CONTINUAR!");
    getch();
    system("cls");
    printf("\n\t\t\tDESEJA JOGAR DE NOVO?\n\t\t\tA - SIM\n\t\t\tB - NÃO");
    do {
      opc = toupper(getch());
    } while (opc != 'A' && opc != 'B');
    if (opc == 'A') {
      system("cls");
      imprimeOrdenacao();
      main();
    } else {
      imprimeOrdenacao();
      exit(1);
    }
  }
}

void lerScore() {
  int i = 0, j;
  char str[10];

  if ((pontuacoes2 = fopen("pontuacoes.txt", "r")) == NULL) {
    erroFicheiro();
  }

  sprintf(str, "TENTATIVAS: %d", w[i].tentativas);

  while (!feof(pontuacoes2)) {
    fgets(str, 300, pontuacoes2);
    fgets(w[i].name, 100, pontuacoes2);
    fgets(w[i].pontuacao, 100, pontuacoes2);
    i++;

  }
  for (j = 0; j < 300; j++) {
    pontuacaoOrdenada[j] = atoi(w[j].pontuacao);
  }

  ordenaPontuacao2(pontuacaoOrdenada, 300);
  fclose(pontuacoes2);

}

void ordenaPontuacao2(int * aNumber, int size) {
  int i, j, temp;
  char temp1[100];
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size; j++) {
      if (aNumber[i] < aNumber[j]) {
        strcpy(temp1, w[i].name);
        strcpy(w[i].name, w[j].name);
        strcpy(w[j].name, temp1);
        temp = aNumber[i];
        aNumber[i] = aNumber[j];
        aNumber[j] = temp;
      }
    }
  }
}

void ordenarArray(int * aNumber, int size) {
  int i, j, temp;
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size; j++) {
      if (aNumber[i] < aNumber[j]) {
        temp = aNumber[i];
        aNumber[i] = aNumber[j];
        aNumber[j] = temp;
      }
    }
  }
}

void imprimeOrdenacao() {
  lerScore();

  int i = 0, j, k, l = 0;
  itoa(pontuacaoOrdenada[0], converterScore[0], 10);
  itoa(pontuacaoOrdenada[1], converterScore[1], 10);
  itoa(pontuacaoOrdenada[2], converterScore[2], 10);
  itoa(pontuacaoOrdenada[3], converterScore[3], 10);
  itoa(pontuacaoOrdenada[4], converterScore[4], 10);
  itoa(pontuacaoOrdenada[5], converterScore[5], 10);
  itoa(pontuacaoOrdenada[6], converterScore[6], 10);
  itoa(pontuacaoOrdenada[7], converterScore[7], 10);
  itoa(pontuacaoOrdenada[8], converterScore[8], 10);
  itoa(pontuacaoOrdenada[9], converterScore[9], 10);
  escreveScore();
}

void escreveScore() {
  int i;
  if ((pontuacoes2 = fopen("pontuacoes.txt", "w+")) == NULL) {
    erroFicheiro();
  } else {
    for (i = 0; i < tentativa && i < 10; i++) {
      fprintf(pontuacoes2, "%d", i + 1);
      fprintf(pontuacoes2, "\n");
      fprintf(pontuacoes2, "%s", w[i].name);
      fprintf(pontuacoes2, "%s", converterScore[i]);
      fprintf(pontuacoes2, "\n\n");
    }
  }

  fclose(pontuacoes2);
}

void mostrarQuestoesNovamente() {
  system("cls");

  printf("\t\t\tQuestão %d\n", questaoNumero);
  printf("\t\t\t%s", perguntas[recebeQuestao].pergunta);
  printf("\t\t\t%s", perguntas[recebeQuestao].opcA);
  printf("\t\t\t%s", perguntas[recebeQuestao].opcB);
  printf("\t\t\t%s", perguntas[recebeQuestao].opcC);
  printf("\t\t\t%s", perguntas[recebeQuestao].opcD);
}

//Função para gerar uma resposta errada
char gerarRespostaErrada(char correta) {
  srand(time(NULL));
  int respostaCorreta;
  char respostaErrada;
  int qualErrada;
  switch (correta) {
  case 'A':
    respostaCorreta = 1;
    break;
  case 'B':
    respostaCorreta = 2;
    break;
  case 'C':
    respostaCorreta = 3;
    break;
  case 'D':
    respostaCorreta = 4;
    break;
  }

  do {
    qualErrada = (rand() % 4) + 1;
  } while (qualErrada == respostaCorreta); //Recebe a resposta errada obrigatoriamente diferente da certa

  switch (qualErrada) {
  case 1:
    respostaErrada = 'A';
    break;
  case 2:
    respostaErrada = 'B';
    break;
  case 3:
    respostaErrada = 'C';
    break;
  case 4:
    respostaErrada = 'D';
    break;
  }

  return respostaErrada;
}

void erroFicheiro() {
  system("cls");
  printf("\n\n\t\tErro ao Abrir o Ficheiro!");
  exit(1);
}
