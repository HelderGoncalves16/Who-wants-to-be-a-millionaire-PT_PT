#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

int x, i, n, questaoNumero, tentativa, recebeQuestao=0, totalGanho, contadorVidas;
int premios[15]={25,50,125,250,500,750,1500,2500,5000,10000,16000,32000,64000,125000,250000};
char nome[100], vida[3];

void login(void);
void reg(void);
void mostraPerguntas(int nivel);
void usarVida(char respostaCorreta, int recebeQuestao);
void mostrarQuestoesNovamente();
void erroFicheiro();
void questaoErrada();
void recebeResposta(int recebeQuestao, int nivel, char respostaCorreta);
	
struct utilizador{
	char name[30];
	char pass[30];
}w[99];

struct niveis{
	char pergunta[120];
	char opcA[70];
	char opcB[70];
	char opcC[70];
	char opcD[70];
	char resposta[5]; 	
}perguntas[15]; 		// Esta Struct Recebe os ficheiros que contem as perguntas
						// Cada ficheiro cont�m 15 perguntas
						
FILE*primeiroNivel;
FILE*segundoNivel;
FILE*terceiroNivel;
	
int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	//Reset
	totalGanho = 0;
	questaoNumero = 0;
	vida[0] = 'X';
	vida[1] = 'X';
	vida[2] = 'X';
	
	printf("\n\t\t\t\t\t\tBEM VINDO AO");
	printf("\n\t\t\t\t\tQUEM QUER SER MILION�RIO");
	printf("\n\n\t\t\t\t=============================================");
	printf("\n\t\t\t\t\tPressiona Enter para Continuar!! ");
	
	if(getch()==13) // Tecla Enter
  
		XY:
	
		system("cls");

		printf("\n\n\n\t\t\t1. JOGAR (APENAS UTILIZADORES REGISTADOS)");
		printf("\n\t\t\t2. REGISTAR NOVO UTILIZADOR");
		printf("\n\t\t\t3. MODO ADMINISTRADOR");
		printf("\n\t\t\t4. SAIR");
		printf("\n\t\t\tDIGITE A SUA OP��O: ");

		scanf("%d",&n);

		switch(n)

 		 {

    	case 1: 
    
        login();
        printf("\n\t\t\tBEM-VINDO � PRIMEIRA FASE DO QUEM QUER SER MILION�RIO");
    	printf("\n\t\t\tNESTA FASE SER�O 5 PERGUNTAS\n");
    	printf("\t\t\tCUJO VALORES PARA CADA PERGUNTA � DE: \n\t\t\t1 - 25 Euros\n\t\t\t2 - 50 Euros\n\t\t\t3 - 125 Euros\n\t\t\t4 - 250 Euros\n\t\t\t5 - 500 Euros\n");
		printf("\t\t\tPREPARADO %s ? VAMOS COME�AR?", nome);
		getch();
        primeiroPatamar();
        segundoPatamar();
        terceiroPatamar();
        break;

    case 2: 

        reg();
        break;
        
	case 3:
				
	//	admin();
		
		break;
	case 4:
		
		system("cls");
		printf("\n\n\t\t\t\t\tA SAIR DO JOGO! OBRIGADO!");
		exit(1);
		
    default: printf("\n\n\t\t\t\tPOR FAVOR DIGITE UMA OP��O CORRETA!");

        if(getch()==13)
        
        goto XY;

  }

  return 0;

}

void reg()

  {
  	
  	system("cls");

    FILE *fp;

    char c; 
	int z=0;

    fp=fopen("Utilizadores.txt","r+");

    printf("\n\n\t\t\t\t\tZONA DE REGISTO");

    printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

    for(i=0;i<100;i++)

    {
    	do {
    		
      		printf("\n\n\t\t\t\tDIGITE O SEU USERNAME: ");

      		scanf("%s",nome);
      
      		if(strlen(nome)<4 || strlen(nome)>12){
      		printf("\n\t\tO seu Username deve conter mais de 4 caracteres e menos de 12");
	  		}

}while(strlen(nome)<4 || strlen(nome)>12);

        while(!feof(fp))

        {

          fread(&w[i],sizeof(w[i]),1,fp);

          if(strcmp(nome,w[i].name)==0) //Verifica se o username j� existe no ficheiro

            {

            printf("\n\n\t\t\tO USERNAME INSERIDO JA EXISTE");


            reg();

            }

          else

          {

            strcpy(w[i].name,nome);

            break;

          }

        }

      printf("\n\n\t\t\t\tDIGITE A SUA PASSWORD: ");

      while((c=getch())!=13)

        {

          w[i].pass[z++]=c;

          printf("%c",'*');

        }

      fwrite(&w[i],sizeof(w[i]),1,fp); //Escreve o Username e Password para o Ficheiro

      fclose(fp);

      printf("\n\n\tPressionar Enter para confirmar o Username e Password inseridos!");

      if((c=getch())==13)

        {


        printf("\n\n\t\tRegisto Efetuado com Sucesso!");

        printf("\n\n\t\tEFETUAR LOGIN NA SUA CONTA?\n\n\t\t  ");

        printf(">1. SIM\n\n\t\t  >2. N�O\n\n\t\t\t\t");

        scanf("%d",&n);

        switch(n)

          {

              case 1: 

                    login();
                    break;

              case 2: 

                    printf("\n\n\n\t\t\t\t\tOBRIGADO POR SE REGISTAR!");
                    break;

          }

        }
        
        break;

      }

    getch();

  }

  void login()

    {
    	
    	system("cls");

      FILE *fp;

      char c,pass[30]; int z=0;

      int checku,checkp;

      fp=fopen("Utilizadores.txt","r+");

      printf("\n\n\t\t\t\tEFETUA O LOGIN ANTES DE JOGAR!");

      printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^");

      for(i=0;i<1000;i++)

      {

        printf("\n\n\t\t\t\tUSERNAME: ");

        scanf("%s",nome);

        printf("\n\n\t\t\t\tPASSWORD: ");

        while((c=getch())!=13)

        {

          pass[z++]=c;

          printf("%c",'*');

        }

        pass[z]='\0';

      while(!feof(fp))

        {

        fread(&w[i],sizeof(w[i]),1,fp);

          checku=strcmp(nome,w[i].name);

          checkp=strcmp(pass,w[i].pass);

          if(checku==0&&checkp==0)

          {

			system("cls");
            printf("\n\n\n\t\t\tLOGIN EFETUADO COM SUCESSO!!\n");
            fclose(fp);
			
            break;
          }

        else if(checku==0&&checkp!=0)

          {

            printf("\n\n\n\t\t\tPassword Errada!! Not %s??",nome);

            printf("\n\n\t\t\t\t  (Pressiona 'Y' para tentar novamente)");

            if(getch()=='y'||getch()=='Y')

              login();

          }

        else if(checku!=0)

          {

            printf("\n\n\n\t\t\tUtilizador n�o registado!\n \t\t\tPressiona Enter para Efetuar Registo!");
            printf("\n\t\t\tOutra Tecla para Voltar ao Menu Principal!");

            if(getch()==13) {
            	reg();
			} else {
				main();
			} 
          } 
        }

        break;

      }
      getch();

    }
    
    int primeiroPatamar(){ //Carregar as perguntas do Ficheiro primeiroNivel	
			if((primeiroNivel = fopen("primeiroNivel.txt","r"))==NULL){
				erroFicheiro();
			} else {
				while(!feof(primeiroNivel)){
					for(x=0; x<15; x++){
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
	
	int segundoPatamar(){ 
			if((segundoNivel = fopen("segundoNivel.txt","r"))==NULL){
				erroFicheiro();
			} else {
				while(!feof(segundoNivel)){
					for(x=0; x<15; x++){
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
	
		int terceiroPatamar(){ 
			if((terceiroNivel = fopen("teceiroNivel.txt","r"))==NULL){
				erroFicheiro();
			} else {
				while(!feof(segundoNivel)){
					for(x=0; x<15; x++){
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
	
	
	void mostraPerguntas(int nivel){
		
		char opc;
		int contadorQuestao; // Numero Total de Quest�es por n�vel
		int questaoMostra[5]={-1,-1,-1,-1,-1};
		int qu=0; //Para enviar questoes para o questaoMostra;
		
		srand(time(NULL));
		
		for(contadorQuestao=0; contadorQuestao<5; contadorQuestao++){
			
			questaoNumero++;
			
			do{
				
				recebeQuestao=(rand()%15); //Gera um numero at� Random at� 15
			
			}while(recebeQuestao == questaoMostra[0] || recebeQuestao == questaoMostra[1] || recebeQuestao == questaoMostra[2] || recebeQuestao == questaoMostra[3] || recebeQuestao == questaoMostra[4]);
			
			questaoMostra[qu]=recebeQuestao;
			
			if(questaoNumero!=1){ //Este codigo nao pode aparecer logo na primeira Quest�o (Possiblidade de Desistir)
				
				printf("\n\t\t\tPretende Continuar %s ?", nome);
				printf("\n\t\t\tA - Continuar\n\t\t\tB - Desistir e sair com %d ", totalGanho);
				
				do {
					
					opc = toupper(getch()); //Fun��o que converte uma letra miniscula em letra maiuscula
				
				} while(opc != 'A' && opc != 'B');
			}
			
			if(opc == 'B'){
				
				system("cls");
				printf("\n\t\t\tOBbrigado por jogar AO QUEM QUER SER MILION�RIO? %s", nome);
				
				//TODO 
				//Enviar nome e totalGanho para Ficheiro com Scores
				
				exit(1);
				break;
				
			} else {
				
				system("cls");
				
				if(questaoNumero!=1){
					printf("\n\t\t\tOK %s ! Vamos ent�o avan�ar para a pr�xima quest�o! \n", nome);
				}
				
				//-------------- QUEST�ES --------------------
				printf("\t\t\tQuest�o %d", questaoNumero);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].pergunta);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcA);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcB);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcC);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcD);
				
				depoisPerguntas:
				printf("\n\t\t\t%s, o que vo�� pretende fazer? ", nome);
				printf("\n\t\t\tA - Responder");
				if(questaoNumero != 15){ 
					printf("\n\t\t\tB - Usar Ajuda");
				}
				
				if(contadorVidas != 3){
					printf("\n\t\t\tVidas restantes: %d", 3-contadorVidas);
				} else {
					printf("\n\t\t\tN�o existem mais vidas!");
				}
				
				if(questaoNumero != 1){
							if(questaoNumero != 15){
									printf("\n\t\t\tC - Sair com metade dos ganhos atuais.");
								} else {
									printf("\n\t\t\tC - Sair com metade dos ganhos atuais.");
									}
				do {
						opc = toupper(getchar());
						}while(opc != 'A' && opc != 'B' && opc != 'C');
						goto adiante;
					} else if(questaoNumero == 15){
						do {
							opc = toupper(getchar());
						}while(opc != 'A'&& opc != 'C');
					} else 
						do {
							opc = toupper(getchar());
						} while(opc != 'A' && opc != 'B');
						
						adiante:
							mostrarQuestoesNovamente();
							if(vida[0]== 'A' && vida[1] == 'B' && vida[2] == 'C' && opc == 'B'){
								printf("\n\t\t\tVoce j� usou todas as vidas!");
								goto depoisPerguntas;
							}
							
							switch(opc){
								case 'A': 
									break;
								case 'B': 
									usarVida(*perguntas[recebeQuestao].resposta , recebeQuestao);
									break;
								case 'C':
									system("cls");
									printf("\n\t\t\tVoce decidiu desistir e ficar com metade dos ganhos atuais!");
									switch(*perguntas[recebeQuestao].resposta){
										case 'A':
											printf("\n\t\t\tA respota correta era a op��o A: %s", perguntas[recebeQuestao].opcA);
											break;
										case 'B':
											printf("\n\t\t\tA respota correta era a op��o B: %s", perguntas[recebeQuestao].opcB);
											break;
										case 'C':
											printf("\n\t\t\tA respota correta era a op��o C: %s", perguntas[recebeQuestao].opcC);
											break;
										case 'D':
											printf("\n\t\t\tA respota correta era a op��o D: %s", perguntas[recebeQuestao].opcD);
											break;
									}
									
									printf("\n\n\t\t\tGANHOU %d", totalGanho = totalGanho/2);
									printf("\n\t\t\tOBRIGADO POR JOGAR!");
									
									
									//TODO
									// ENVIAR PARA O SCORE			
									
									exit(1);						
							}
							
							recebeResposta(recebeQuestao, nivel, *perguntas[recebeQuestao].resposta);
							qu++;
					}
				}
				
			}
		
	void recebeResposta(int recebeQuestao, int nivel, char respostaCorreta){
		
		char resposta;
		int opc;
		
			antesResposta:
			printf("\n\t\t\tOK! Qual � a sua resposta %s ?", nome);
			do{
				resposta = toupper(getch());
			}while(resposta != 'A' && resposta != 'B' && resposta != 'C' && resposta != 'D');
			
			if(nivel == 2 || nivel == 3){
				printf("n\t\t\tA sua resposta � a %c . Prentende bloquear?");
				printf("\n\t\t\tA - Sim");
				printf("\n\t\t\tB - N�o");
				do{
					
					opc = toupper(getch());
					
				}while(opc != 'A' && opc != 'B');
				
				if(opc == 'B'){
					mostrarQuestoesNovamente();
					goto antesResposta;
				}
				
				if(opc == 'A'){
					if(resposta == respostaCorreta){
						system("cls");
						printf("\n\t\t\tA sua resposta est�.... CORRETA!!!");
						totalGanho = premios[questaoNumero-1];
					} else {
						questaoErrada();
					}
				}
			}
			if(resposta == respostaCorreta){
				system("cls");
				printf("\n\t\t\tRESPOSTA CORRETA! %s !", nome);
				totalGanho = premios[questaoNumero-1];
			} else {
				questaoErrada();
			}
	}
	
	void questaoErrada(){
		system("cls");
		printf("Upsssss, a resposta est� errada!");
		
		switch(*perguntas[recebeQuestao].resposta){
		case 'A':
			printf("\n\t\t\tA respota correta era a op��o A: %s", perguntas[recebeQuestao].opcA);
			break;
		case 'B':
			printf("\n\t\t\tA respota correta era a op��o B: %s", perguntas[recebeQuestao].opcB);
			break;
		case 'C':
			printf("\n\t\t\tA respota correta era a op��o C: %s", perguntas[recebeQuestao].opcC);
			break;
		case 'D':
			printf("\n\t\t\tA respota correta era a op��o D: %s", perguntas[recebeQuestao].opcD);
			break;
		}
		
	}
	
	void usarVida(char respostaCorreta, int recebeQuestao){ //Mostra as op��es de ajuda
		char opcVida;
		printf("Escolh");
	}
	
	void mostrarQuestoesNovamente(){
				system("cls");
		
				printf("\t\t\tQuest�o %d", questaoNumero);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].pergunta);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcA);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcB);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcC);
				printf("\n\t\t\t%s", perguntas[recebeQuestao].opcD);
	}
	void erroFicheiro(){
		system("cls");
		printf("\n\n\t\tErro ao Abrir o Ficheiro!");
		exit(1);
	}
    
    

