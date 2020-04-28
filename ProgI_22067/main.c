#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<locale.h>

static int i=0;

struct utilizador

{

char name[30],pass[30];

}w[99];

int n;

void login(void);

void reg(void);


	int main(){
	
	setlocale(LC_ALL, "Portuguese");

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

    char c,checker[30]; int z=0;

    fp=fopen("Utilizadores.txt","ab+");

    printf("\n\n\t\t\t\ZONA DE REGISTO");

    printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^");

    for(i=0;i<100;i++)

    {

      printf("\n\n\t\t\t\tDIGITE O SEU USERNAME: ");

      scanf("%s",checker);

        while(!feof(fp))

        {

          fread(&w[i],sizeof(w[i]),1,fp);

          if(strcmp(checker,w[i].name)==0) //Verifica se o username já existe no ficheiro

            {

            printf("\n\n\t\t\tO USERNAME INSERIDO JA EXISTE");


            reg();

            }

          else

          {

            strcpy(w[i].name,checker);

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

        printf("\n\n\t\tTry login your account??\n\n\t\t  ");

        printf("> PRESS 1 FOR YES\n\n\t\t  > PRESS 2 FOR NO\n\n\t\t\t\t");

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

      char c,name[30],pass[30]; int z=0;

      int checku,checkp;

      fp=fopen("Utilizadores.txt","rb");

      printf("\n\n\t\t\t\tEFETUA O LOGIN ANTES DE JOGAR!");

      printf("\n\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^");

      for(i=0;i<1000;i++)

      {

        printf("\n\n\t\t\t\tUSERNAME: ");

        scanf("%s",name);

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

          checku=strcmp(name,w[i].name);

          checkp=strcmp(pass,w[i].pass);

          if(checku==0&&checkp==0)

          {

            
			system("cls");
            printf("\n\n\n\t\t\tLOGIN EFETUADO COM SUCESSO!!");
            printf("\n\n\n\t\t\t\tWELCOME, HAVE A NICE DAY");

            break;

          }

        else if(checku==0&&checkp!=0)

          {

            printf("\n\n\n\t\t\tPassword Errada!! Not %s??",name);

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
			} 
          } 
        }

        break;

      }

      getch();

    }
    
    

