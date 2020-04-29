#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<locale.h>

int x, i, n, questaoNumero, tentativa, recebeQuestao=0, totalGanho;
int premios[15]={25,50,125,250,500,750,1500,2500,5000,10000,16000,32000,64000,125000,250000};
char nome[100], vidas[3];

void login(void);
void reg(void);
void mostraPerguntas(int nivel);
	
struct utilizador{
	char name[30];
	char pass[30];
	int tentativas;
	char score[7];
}w[99];

struct niveis{
	char pergunta[120];
	char opcA[70];
	char opcB[70];
	char opcC[70];
	char opcD[70];
	char resposta[5]; 	
}perguntas[15]; 		// Esta Struct Recebe os ficheiros que contem as perguntas
						// Cada ficheiro contém 15 perguntas
	
int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	//Reset
	totalGanho = 0;
	questaoNumero = 0;
	vidas[0] = 'X';
	vidas[1] = 'X';
	vidas[2] = 'X';
	
	printf("\n\t\t\t\t\t\tBEM VINDO AO");
	printf("\n\t\t\t\t\tQUEM QUER SER MILIONÁRIO");
	printf("\n\n\t\t\t\t=============================================");
	printf("\n\t\t\t\t\tPressiona Enter para Continuar!! ");
	
	if(getch()==13) // Tecla Enter
  
		XY:
	
		system("cls");

		printf("\n\n\n\t\t\t1. JOGAR (APENAS UTILIZADORES REGISTADOS)");
		printf("\n\t\t\t2. REGISTAR NOVO UTILIZADOR");
		printf("\n\t\t\t3. MODO ADMINISTRADOR");
		printf("\n\t\t\t4. SAIR");
		printf("\n\t\t\tDIGITE A SUA OPÇÃO: ");

		scanf("%d",&n);

		switch(n)

 		 {

    	case 1: 
    
        login();
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
		
    default: printf("\n\n\t\t\t\tPOR FAVOR DIGITE UMA OPÇÃO CORRETA!");

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

    fp=fopen("Utilizadores.txt","ab+");

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

          if(strcmp(nome,w[i].name)==0) //Verifica se o username já existe no ficheiro

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

        printf(">1. SIM\n\n\t\t  >2. NÃO\n\n\t\t\t\t");

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

      fp=fopen("Utilizadores.txt","rb");

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
			
			primeiroPatamar();
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

            printf("\n\n\n\t\t\tUtilizador não registado!\n \t\t\tPressiona Enter para Efetuar Registo!");
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
    
    int primeiroPatamar(){
    	
    	FILE *primeiroNivel;
    	
    	printf("\n\t\t\tBEM-VINDO À PRIMEIRA FASE DO QUEM QUER SER MILIONÁRIO");
    	printf("\n\t\t\tNESTA FASE SERÃO 5 PERGUNTAS\n");
    	printf("\t\t\tCUJO VALORES PARA CADA PERGUNTA É DE: \n\t\t\t1 - 25 Euros\n\t\t\t2 - 50 Euros\n\t\t\t3 - 125 Euros\n\t\t\t4 - 250 Euros\n\t\t\t5 - 500 Euros\n");
		printf("\t\t\tPREPARADO %s ? VAMOS COMEÇAR?", nome);
		
		if(getch()==13){
			
			if((primeiroNivel = fopen("primeiroNivel.txt","r"))==NULL){
				erroFicheiro();
			} else {
				while(!feof(primeiroNivel)){
					for(x=0; x<30; x++){
						fgets(perguntas[x].pergunta, 120, primeiroNivel);
						fgets(perguntas[x].opcA, 70, primeiroNivel);
						fgets(perguntas[x].opcB, 70, primeiroNivel);
						fgets(perguntas[x].opcC, 70, primeiroNivel);
						fgets(perguntas[x].opcD, 70, primeiroNivel);
						fgets(perguntas[x].resposta, 70, primeiroNivel);
					}
				}
			}
		}
		
		mostraPerguntas(1); //Mostrar as Perguntas Armazenadas
		fclose(primeiroNivel);
	}
	
	int segundoPatamar(){
		return 0;
	}
	
	void mostraPerguntas(int nivel){
		
		char opc;
		int contadorQuestao; // Numero Total de Questões por nível
		int questaoMostra[5]={-1,-1,-1,-1,-1};
		int qu=0; //Para enviar questoes para o questaoMostra;
		
		
		system("cls");
		srand(time(NULL));
		
		for(contadorQuestao=0; contadorQuestao<5; contadorQuestao++){
			
			questaoNumero++;
			
			do{
				
				recebeQuestao=(rand()%15); //Gera um numero até Random até 15
			
			}while(recebeQuestao == questaoMostra[0] || recebeQuestao == questaoMostra[1] || recebeQuestao == questaoMostra[2] || recebeQuestao == questaoMostra[3] || recebeQuestao == questaoMostra[4]);
			
			questaoMostra[qu]=recebeQuestao;
			
			if(questaoNumero!=1){ //Este codigo nao pode aparecer logo na primeira Questão (Possiblidade de Desistir)
				
				printf("\n\t\t\tPretende Continuar %s ?", nome);
				printf("\n\t\t\tA - Continuar\n\t\t\tB - Desistir e sair com %d", totalGanho);
				
				do {
					
					opc = toupper(getch()); //Função que converte uma letra miniscula em letra maiuscula
				
				} while(opc !="A" && opc != 'B');
			}
			
			if(opc='B'){
				
				system("cls");
				printf("\n\t\t\tOBbrigado por jogar AO QUEM QUER SER MILIONÁRIO? %s", nome);
				
				//TODO 
				//Enviar nome e totalGanho para Ficheiro com Scores
				
				exit(1);
				break;
				
			} else {
				
				system("cls");
				
				if(questaoNumero!=1){
					printf("\n\t\t\tOK %s ! Vamos então avançar para a próxima questão!\n", nome);
				}
				
				//-------------- QUESTÕES --------------------
				printf("\t\t\tQuestão %d\n", questaoNumero);
				printf("%s", perguntas[recebeQuestao].pergunta);
				printf("%s", perguntas[recebeQuestao].opcA);
				printf("%s", perguntas[recebeQuestao].opcB);
				printf("%s", perguntas[recebeQuestao].opcC);
				printf("%s", perguntas[recebeQuestao].opcD);
			}
		}
	}
	
	void erroFicheiro(){
		system("cls");
		printf("\n\n\t\tErro ao Abrir o Ficheiro!");
		exit(1);
	}
    
    

