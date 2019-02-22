#include <stdio.h>
#include <stdlib.h>
#include <conio.c>
#include <windows.h>
#include <string.h>

#define ENTER  0x0D
#define ESC  0x1B //!27
#define LIMPAR system("cls")
#define PAUSAR system("pause")
#define LOGIN_TELA system("MODE con cols=120 lines=30")
#define DIMENSIONAR_TELA system("MODE con cols=120 lines=30")
#define BACKGROUND_BRANCO system("color f0")
#define INICIO system("c:/projVoo/include/inicio")
#define FF fflush(stdin)

//funções
void botaNum(int x);
void reserva(char *caminho);
void sess();
void dados(char *sess);
char * tiraQuebra(char *var);
void menu();
void efetuarReserva();
void buscarVoo(char *tipo);
void meuHistorico();
void escrever(char *texto, int cor, int background);
void posicionar(int left, int top);
void area_login();
void login();
int autenticar();
void logout();
int tempo(int);
void cadeira(int x, int y);
void reservado(int x);

//variaveis globais
int autenticado; //0=não; 1=sim 
char sessao[40];
char tempNumeroVoo[50];
char tOrigem[50];
char tDestino[50];

//structs
struct dados {
	int id;
	char adm[4];	//0=nao; 1=sim
	char login[30];
	char nome[30];
	char sobrenome[30];
	char idade[30];
	char endereco[100];
	char cidade[20];
	char estado[20];
};
struct dados user;
int main(){
	DIMENSIONAR_TELA;
	autenticar();
	sess();
	dados(sessao);
	menu();
	return 0;
}
void botaNum(int x){
	int px, py, i, posicY, posicX;
	if((x%4) != 0){
		px = x/4;
		px++;
		int resto = x%4;
		if(resto == 1){
			py = 1;
		}else if(resto == 2){
			py = 2;
		}else if(resto == 3){
			py = 3;
		}
		
	}else{
		px = x/4;
		py = 4;
	}
	switch(py){
			case 1:
				posicY = 5;
			break;
			case 2:
				posicY = 9;
			break;
			case 3:
				posicY = 16;
			break;
			case 4:
				posicY = 20;
			break;
	}
	posicX = px*10;
	posicionar(posicX, posicY);
	escrever("", 15, 3);
	printf("%i", x);
	posicX = 0;
	posicY = 0;
	posicionar(1,1);
}
void reservado(int x){
	int px, py, i, posicY, posicX;
	if((x%4) != 0){
		px = x/4;
		px++;
		int resto = x%4;
		if(resto == 1){
			py = 1;
		}else if(resto == 2){
			py = 2;
		}else if(resto == 3){
			py = 3;
		}
		
	}else{
		px = x/4;
		py = 4;
	}
	switch(py){
			case 1:
				posicY = 5;
			break;
			case 2:
				posicY = 9;
			break;
			case 3:
				posicY = 16;
			break;
			case 4:
				posicY = 20;
			break;
	}
	posicX = px*10;
	for(i=0;i<8;i++){
		posicionar(i+posicX ,posicY);
		escrever(" ", 15, 4);
	}
	for(i=0;i<8;i++){
		posicionar(i+posicX ,posicY+1);
		escrever(" ", 15, 4);
	}
	for(i=0;i<8;i++){
		posicionar(i+posicX ,posicY+2);
		escrever(" ", 15, 4);
	}
	posicX = 0;
	posicY = 0;
	posicionar(1,1);
}
void cadeira(int x, int y){
	
	int i;
	for(i=0;i<8;i++){
		posicionar(x+i, y);
		escrever(" ", 15, 3);
	}
	for(i=0;i<8;i++){
		posicionar(x+i, y+1);
		escrever(" ", 15, 3);
	}
	for(i=0;i<8;i++){
		posicionar(x+i, y+2);
		escrever(" ", 15, 3);
	}
}

void reserva(char *caminho){
	escrever(" ", 3,15);
	LIMPAR;
	int tecla = 0;
	int posicaoX, posicaoY, inicioX, inicioY, numeroPol;
	posicaoX = 1;
	posicaoY = 1;
	char DirName[] = "c:/projVoo/lib/libVooN";
	strcat(DirName, caminho);
	posicionar(5, 2);
	escrever(" ", 0, 15);
	printf("Seja Bem vindo(a) %s", tiraQuebra(user.nome));
	posicionar(2,6);
	escrever("Janela", 8,15);
	posicionar(2,21);
	escrever("Janela", 8,15);
	posicionar(30,14);
	escrever("Corredor", 8,15);
	posicionar(60,14);
	escrever("Corredor", 8,15);
	
	int i;
	int lh = 0;
	while(lh<18){
		for(i=0;i<40;i++){
			posicionar(80+i,lh+5);
			escrever(" ", 3, 8);
		}
		lh++;
	}
	lh = 0;
	while(lh<18){
		for(i=0;i<9;i++){
			posicionar(80+i,lh+5);
			escrever(" ", 3, 15);
		}
		lh++;
	}
	posicionar(80, 7);
	escrever("\n\t\t\t\t\t\t\t\t\t\t\t  Atencao!!! \n\n\n\t\t\t\t\t\t\t\t\t\t\t  As cadeiras em vermelho \n\t\t\t\t\t\t\t\t\t\t\t  estao reservadas, portanto \n\t\t\t\t\t\t\t\t\t\t\t  se voce selecionar uma delas\n\t\t\t\t\t\t\t\t\t\t\t  seu embarque nao sera\n\t\t\t\t\t\t\t\t\t\t\t  realizado.", 15, 8);
	escrever("", 5,8);
	posicionar(80, 18);
	printf("\t\t  Numero deste voo: %s", tempNumeroVoo);
	for(i=1;i<=8;i++){
		cadeira(i*10,5);
	}
	for(i=1;i<=8;i++){
		cadeira(i*10,9);
	}
	for(i=1;i<=8;i++){
		cadeira(i*10,16);
	}
	for(i=1;i<=8;i++){
		cadeira(i*10,20);
	}
	posicionar(1,18);
	int numerar = 1;
	while(numerar <=32){
		botaNum(numerar);
		numerar++;
	}
	int cont = 0;
	int ocupado[32];
	FILE *fp;
	if(fopen(DirName, "r") == NULL){
		fopen(DirName, "w");
	}
	fp = fopen(DirName, "r");
	char dados[10];
	char *resultado;
	while(!feof(fp)){
		resultado = fgets(dados, 10, fp);
		if(resultado != NULL){
			char tempRess[10];
			strcpy(tempRess, tiraQuebra(resultado));
			if(tempRess != NULL){
				int num = atoi(tempRess);
				reservado(num);
				ocupado[cont] = num;
			}
		}
		cont++;
	}
	fclose(fp);
	for(i=0;i<78;i++){
		posicionar(i+10,24);
		escrever(" ", 15, 7);
	}
	posicionar(10, 25);
	escrever("", 5,15);
	printf("Digite o numero da poltrona: ");
	fflush(stdin);
	scanf("%i", &numeroPol);
	if((numeroPol > 0) && (numeroPol < 33)){
		escrever("", 3, 15);
		LIMPAR;
		printf(" Detalhes da reserva:\n\n\n Nome: %s %s\n Embarque: %s\n Desembarque: %s\n Numero do voo: %s", user.nome, tiraQuebra(user.sobrenome), tiraQuebra(tOrigem), tiraQuebra(tDestino), tempNumeroVoo);
		posicionar(2, 10);
		escrever("Pressione ENTER para confirmar ou qualquer outra tecla para cancelar.", 4, 15);
		if(kbhit){
			char tltl = getch();
			if(tltl == ENTER){
				FILE *fp;
				char caminho[] = "c:/projVoo/lib/libVooN";
				strcat(caminho, tempNumeroVoo);
				fp = fopen(caminho,"a");
				fprintf(fp, "%i\n", numeroPol);
				fclose(fp);
				FILE *fpp;
				char caminhoo[] = "c:/projVoo/lib/lib";
				strcat(caminhoo, tempNumeroVoo);
				fpp = fopen(caminhoo,"a");
				fprintf(fpp, "linhaAut\n%s %s\n10\n%i\n%s\n", user.nome, tiraQuebra(user.sobrenome), numeroPol, tiraQuebra(user.login));
				fclose(fpp);
				escrever("", 3,15);
				LIMPAR;
				posicionar(40,10);
				printf("Reserva efetuada com Sucesso!!!");
				getch();
				menu();
			}else{
				escrever("", 15,4);
				LIMPAR;
				posicionar(40,10);
				printf("Reserva cancelada!!!");
				getch();
				menu();
			}
		}
	}else {
		escrever("", 15,4);
		LIMPAR;
		posicionar(40,10);
		printf("Poltrona Inexistente");
		getch();
		menu();
	}
}
void efetuarReserva(){
	int tecla = 0;
	int posicaoX, posicaoY, inicioX, inicioY, tempOrigem, tempDestino;
	posicaoX = 1;
	posicaoY = 1;
	while(tecla == 0){
		escrever(" ", 3, 15);
		LIMPAR;
		posicionar(5, 2);
		escrever(" ", 0, 15);
		printf("Seja Bem vindo(a) %s", tiraQuebra(user.nome));
		posicionar(25,25);
		escrever("PROJETADO E CODADO POR TAUAN © tauan@alunos.utfpr.edu.br", 7, 15);
		posicionar(70,2);
		escrever("Pressione (Q) para voltar ao menu inicial.", 12,15);
		int i;
		for(i=5;i<115;i++){
				posicionar(i, 4);
				escrever(" ", 15, 3);
		}
		for(i=5;i<115;i++){
				posicionar(i, 5);
				escrever(" ", 15, 3);
		}
		for(i=5;i<115;i++){
				posicionar(i, 6);
				escrever(" ", 15, 3);
		}
		posicionar(10,5);
		escrever("Selecione a origem do voo.", 15, 3);
		FILE *arq;
		char dados[50];
		char *resultado;
		arq = fopen("c:/projVoo/lib/libAeroportos", "rt");
		int c = 1;
		int d=8;
		escrever("", 3, 15);
		while(!feof(arq)) {
			resultado = fgets(dados, 50, arq);
			if((c % 2) == 0){
				posicionar(12, d);
				printf("%s", resultado);
				d++;
			}
			c++;
		}	
		for(i=0;i<10;i++){
			posicionar(9,i+8);
			escrever("(",3,15);
			posicionar(11,i+8);
			escrever(")",3,15);
		}
			
		if(posicaoY == 1){
			posicionar(10, 8);
			escrever("+", 5, 15);
		}else if(posicaoY == 2){
			posicionar(10, 9);
			escrever("+", 5, 15);
		}else if(posicaoY == 3){
			posicionar(10, 10);
			escrever("+", 5, 15);
		}else if(posicaoY == 4){
			posicionar(10, 11);
			escrever("+", 5, 15);
		}else if(posicaoY == 5){
			posicionar(10, 12);
			escrever("+", 5, 15);
		}else if(posicaoY == 6){
			posicionar(10, 13);
			escrever("+", 5, 15);
		}else if(posicaoY == 7){
			posicionar(10, 14);
			escrever("+", 5, 15);
		}else if(posicaoY == 8){
			posicionar(10, 15);
			escrever("+", 5, 15);
		}else if(posicaoY == 9){
			posicionar(10, 16);
			escrever("+", 5, 15);
		}else if(posicaoY == 10){
			posicionar(10, 17);
			escrever("+", 5, 15);
		}
			
		posicionar(80,18);
		if(kbhit){
			char ch = getch();
			if(ch == ENTER){
				tecla++;
				tempOrigem = posicaoY;
			}else if((ch == 'w')||(ch == 'W')){
				if(posicaoY > 1){
					posicaoY--;
				}
			}else if((ch == 's')||(ch == 'S')){
				if(posicaoY < 10){
					posicaoY++;
				}
			}else if((ch == 'q')||(ch == 'Q')){
				tecla =1;
				LIMPAR;
				menu();
			}
		}
	}
	posicaoX = 1;
	posicaoY = 1;
	tecla = 0;
	while(tecla == 0){
		escrever(" ", 3, 15);
		LIMPAR;
		posicionar(5, 2);
		escrever(" ", 0, 15);
		printf("Seja Bem vindo(a) %s", tiraQuebra(user.nome));
		posicionar(25,25);
		escrever("PROJETADO E CODADO POR TAUAN © tauan@alunos.utfpr.edu.br", 7, 15);
		posicionar(70,2);
		escrever("Pressione (Q) para voltar ao menu inicial.", 12,15);
		int i;
		for(i=5;i<115;i++){
				posicionar(i, 4);
				escrever(" ", 15, 3);
		}
		for(i=5;i<115;i++){
				posicionar(i, 5);
				escrever(" ", 15, 3);
		}
		for(i=5;i<115;i++){
				posicionar(i, 6);
				escrever(" ", 15, 3);
		}
		// int j = 0;
		// while(j<13){
		// 	for(i=5;i<115;i++){
		// 		posicionar(i, j+7);
		// 		escrever(" ", 15, 7);
		// 		
	 //  	  	  }	
		// 		 j++;	
		// }
		posicionar(10,5);
		escrever("Selecione o destino do voo.", 15, 3);
		FILE *arq;
		char dados[50];
		char *resultado;
		arq = fopen("c:/projVoo/lib/libAeroportos", "rt");
		int c = 1;
		int d=8;
		escrever("", 3, 15);
		while(!feof(arq)) {
			resultado = fgets(dados, 50, arq);
			if((c % 2) == 0){
				posicionar(12, d);
				printf("%s", resultado);
				d++;
			}
			c++;
		}	
		for(i=0;i<10;i++){
			posicionar(9,i+8);
			escrever("(",3,15);
			posicionar(11,i+8);
			escrever(")",3,15);
		}
		if(posicaoY == 1){
			posicionar(10, 8);
			escrever("+", 5, 15);
		}else if(posicaoY == 2){
			posicionar(10, 9);
			escrever("+", 5, 15);
		}else if(posicaoY == 3){
			posicionar(10, 10);
			escrever("+", 5, 15);
		}else if(posicaoY == 4){
			posicionar(10, 11);
			escrever("+", 5, 15);
		}else if(posicaoY == 5){
			posicionar(10, 12);
			escrever("+", 5, 15);
		}else if(posicaoY == 6){
			posicionar(10, 13);
			escrever("+", 5, 15);
		}else if(posicaoY == 7){
			posicionar(10, 14);
			escrever("+", 5, 15);
		}else if(posicaoY == 8){
			posicionar(10, 15);
			escrever("+", 5, 15);
		}else if(posicaoY == 9){
			posicionar(10, 16);
			escrever("+", 5, 15);
		}else if(posicaoY == 10){
			posicionar(10, 17);
			escrever("+", 5, 15);
		}
		posicionar(80,18);
		if(kbhit){
			char ch = getch();
			if(ch == ENTER){
				tecla=9;
				tempDestino = posicaoY;
			}else if((ch == 'w')||(ch == 'W')){
				if(posicaoY > 1){
					posicaoY--;
				}
			}else if((ch == 's')||(ch == 'S')){
				if(posicaoY < 10){
					posicaoY++;
				}
			}else if((ch == 'q')||(ch == 'Q')){
				tecla =1;
				LIMPAR;
				menu();
			}
		}
	}
	/*
		fazer buscas de voos disponiveis e sugestões
	*/
	if(tecla == 9){
			LIMPAR;
		//tempDestino tempOrigem
		FILE *fp;
		fp = fopen("c:/projVoo/lib/libAeroportos", "r");
		char origem[100];
		char destino[100];
		char dd[100];
		char *ress;
		int k = 1;
		while(k <= tempOrigem*2){
			   	ress = fgets(dd, 100, fp);
			   	k++;
		}
		strcpy(origem, ress);
		strcpy(tOrigem, origem);
		fclose(fp);
		
		FILE *fpp;
		fpp = fopen("c:/projVoo/lib/libAeroportos", "r");
		k = 1;
		while(k <= tempDestino*2){
			   	ress = fgets(dd, 100, fpp);
			   	k++;
		}
		strcpy(destino, ress);
		strcpy(tDestino,destino);
		fclose(fp);
		LIMPAR;
		FILE *arq;
		arq = fopen("c:/projVoo/lib/libVoos", "r");
		char dados[100];
		char *resultado;
		int resultVoo = 0;
		while(!feof(arq)){
			resultado = fgets(dados, 100, arq);
			if(resultado != NULL){
				if(strcmp(tiraQuebra(resultado), "linhaBranca") == 0){
					resultado = fgets(dados, 100, arq);
					if(strcmp(resultado, origem) == 0){
						resultado = fgets(dados, 100, arq);
						if(strcmp(tiraQuebra(resultado), "linhaO") == 0){
							resultado = fgets(dados, 100, arq);
							if(strcmp(resultado, destino) == 0){
								resultado = fgets(dados, 100, arq);
								if(strcmp(resultado, "linhaD\n") == 0){
									resultado = fgets(dados, 100, arq);
									strcpy(tempNumeroVoo, tiraQuebra(resultado));
									resultVoo++;
								}
								
							}
						}
					}
				}
			}
			
		}
		
		fclose(arq);
		if(resultVoo < 1){
			int i;
			for(i=0;i<80;i++){
				posicionar(i+15, 5);
				escrever(" ", 15, 12);
			}
			for(i=0;i<80;i++){
				posicionar(i+15, 6);
				escrever(" ", 15, 12);
			}
			for(i=0;i<80;i++){
				posicionar(i+15, 7);
				escrever(" ", 15, 12);
			}
			posicionar(25,6);
			printf("Lamentamos, mas nenhum voo esta disponivel para essa rota!!");
			tecla = 1;
			while(tecla == 1){
				if(kbhit){
					char tecla = getch();
					if(tecla == ENTER){
						menu();
					}
				}
			}
		}else {
			reserva(tempNumeroVoo);
		}
	}
}
void buscarVoo(char *tipo){
	if(tipo == "origem"){
		int tecla = 0;
		int posicaoX, posicaoY, inicioX, inicioY;
		posicaoX = 1;
		posicaoY = 1;
		while(tecla == 0){
			escrever(" ", 3, 15);
			LIMPAR;
			posicionar(5, 2);
			escrever(" ", 0, 15);
			printf("Seja Bem vindo(a) %s", tiraQuebra(user.nome));
			posicionar(25,25);
			escrever("PROJETADO E CODADO POR TAUAN © tauan@alunos.utfpr.edu.br", 7, 15);
			posicionar(70,2);
			escrever("Pressione (Q) para voltar ao menu inicial.", 12,15);
			int i;
			for(i=5;i<115;i++){
					posicionar(i, 4);
					escrever(" ", 15, 3);
			}
			for(i=5;i<115;i++){
					posicionar(i, 5);
					escrever(" ", 15, 3);
			}
			for(i=5;i<115;i++){
					posicionar(i, 6);
					escrever(" ", 15, 3);
			}
			posicionar(10,5);
			escrever("Pesquisa por origem.", 15, 3);
			FILE *arq;
			char dados[50];
			char *resultado;
			arq = fopen("c:/projVoo/lib/libAeroportos", "rt");
			int c = 1;
			int d=8;
			escrever("", 3, 15);
			while(!feof(arq)) {
				resultado = fgets(dados, 50, arq);
				if((c % 2) == 0){
					posicionar(12, d);
					printf("%s", resultado);
					d++;
				}
				c++;
			}	
			for(i=0;i<10;i++){
				posicionar(9,i+8);
				escrever("(",3,15);
				posicionar(11,i+8);
				escrever(")",3,15);
			}
			if(posicaoY == 1){
				posicionar(10, 8);
				escrever("+", 5, 15);
			}else if(posicaoY == 2){
				posicionar(10, 9);
				escrever("+", 5, 15);
			}else if(posicaoY == 3){
				posicionar(10, 10);
				escrever("+", 5, 15);
			}else if(posicaoY == 4){
				posicionar(10, 11);
				escrever("+", 5, 15);
			}else if(posicaoY == 5){
				posicionar(10, 12);
				escrever("+", 5, 15);
			}else if(posicaoY == 6){
				posicionar(10, 13);
				escrever("+", 5, 15);
			}else if(posicaoY == 7){
				posicionar(10, 14);
				escrever("+", 5, 15);
			}else if(posicaoY == 8){
				posicionar(10, 15);
				escrever("+", 5, 15);
			}else if(posicaoY == 9){
				posicionar(10, 16);
				escrever("+", 5, 15);
			}else if(posicaoY == 10){
				posicionar(10, 17);
				escrever("+", 5, 15);
			}
			posicionar(80,18);
			if(kbhit){
				char ch = getch();
				if(ch == ENTER){
					tecla=9;
				}else if((ch == 'w')||(ch == 'W')){
					if(posicaoY > 1){
						posicaoY--;
					}
				}else if((ch == 's')||(ch == 'S')){
					if(posicaoY < 10){
						posicaoY++;
					}
				}else if((ch == 'q')||(ch == 'Q')){
					tecla =1;
					LIMPAR;
					menu();
				}
			}
		}
		LIMPAR;
		FILE *fph;
		fph = fopen("c:/projVoo/lib/libAeroportos", "r");
		char origem[100];
		char dd[100];
		char *ress;
		int k = 1;
		while(k <= posicaoY*2){
			   	ress = fgets(dd, 100, fph);
			   	k++;
		}
		strcpy(origem, ress);
		fclose(fph);
	
		//parte 2
		escrever("", 3,15);
		LIMPAR;
		escrever(" Voos correspondentes a busca:\n\n", 5,15);
		
		escrever("", 3,15);
		FILE *fp;
		fp = fopen("c:/projVoo/lib/libVoos", "r");
		char dados[100];
		char *resultado;
		while(!feof(fp)){
			resultado = fgets(dados, 100, fp);
			if(resultado != NULL){
				if(strcmp(resultado, "linhaBranca\n") == 0){
					resultado = fgets(dados, 100, fp);
					if(strcmp(origem, resultado) == 0){
						printf(" Origem: %s", resultado);
						resultado = fgets(dados, 100, fp);
						resultado = fgets(dados, 100, fp);
						printf(" Destino: %s", resultado);
						resultado = fgets(dados, 100, fp);
						resultado = fgets(dados, 100, fp);
						printf(" Numero do voo: %s", resultado);
						resultado = fgets(dados, 100, fp);
						resultado = fgets(dados, 100, fp);
						printf(" Numero de acentos no voo: %s", resultado);
						
						printf("\n\n\n");
					}
				}
			}
		}
		fclose(fp);
		posicionar(2,20);
		escrever("Precione qualquer tecla para retornar ao menu.", 4,15);
		getch();
		menu();
	}else if(tipo == "destino"){
		int tecla = 0;
		int posicaoX, posicaoY, inicioX, inicioY;
		posicaoX = 1;
		posicaoY = 1;
		while(tecla == 0){
			escrever(" ", 3, 15);
			LIMPAR;
			posicionar(5, 2);
			escrever(" ", 0, 15);
			printf("Seja Bem vindo(a) %s", tiraQuebra(user.nome));
			posicionar(25,25);
			escrever("PROJETADO E CODADO POR TAUAN © tauan@alunos.utfpr.edu.br", 7, 15);
			posicionar(70,2);
			escrever("Pressione (Q) para voltar ao menu inicial.", 12,15);
			int i;
			for(i=5;i<115;i++){
					posicionar(i, 4);
					escrever(" ", 15, 3);
			}
			for(i=5;i<115;i++){
					posicionar(i, 5);
					escrever(" ", 15, 3);
			}
			for(i=5;i<115;i++){
					posicionar(i, 6);
					escrever(" ", 15, 3);
			}
			posicionar(10,5);
			escrever("Pesquisa por origem.", 15, 3);
			FILE *arq;
			char dados[50];
			char *resultado;
			arq = fopen("c:/projVoo/lib/libAeroportos", "rt");
			int c = 1;
			int d=8;
			escrever("", 3, 15);
			while(!feof(arq)) {
				resultado = fgets(dados, 50, arq);
				if((c % 2) == 0){
					posicionar(12, d);
					printf("%s", resultado);
					d++;
				}
				c++;
			}	
			for(i=0;i<10;i++){
				posicionar(9,i+8);
				escrever("(",3,15);
				posicionar(11,i+8);
				escrever(")",3,15);
			}
			if(posicaoY == 1){
				posicionar(10, 8);
				escrever("+", 5, 15);
			}else if(posicaoY == 2){
				posicionar(10, 9);
				escrever("+", 5, 15);
			}else if(posicaoY == 3){
				posicionar(10, 10);
				escrever("+", 5, 15);
			}else if(posicaoY == 4){
				posicionar(10, 11);
				escrever("+", 5, 15);
			}else if(posicaoY == 5){
				posicionar(10, 12);
				escrever("+", 5, 15);
			}else if(posicaoY == 6){
				posicionar(10, 13);
				escrever("+", 5, 15);
			}else if(posicaoY == 7){
				posicionar(10, 14);
				escrever("+", 5, 15);
			}else if(posicaoY == 8){
				posicionar(10, 15);
				escrever("+", 5, 15);
			}else if(posicaoY == 9){
				posicionar(10, 16);
				escrever("+", 5, 15);
			}else if(posicaoY == 10){
				posicionar(10, 17);
				escrever("+", 5, 15);
			}
			posicionar(80,18);
			if(kbhit){
				char ch = getch();
				if(ch == ENTER){
					tecla=9;
				}else if((ch == 'w')||(ch == 'W')){
					if(posicaoY > 1){
						posicaoY--;
					}
				}else if((ch == 's')||(ch == 'S')){
					if(posicaoY < 10){
						posicaoY++;
					}
				}else if((ch == 'q')||(ch == 'Q')){
					tecla =1;
					LIMPAR;
					menu();
				}
			}
		}
		LIMPAR;
		FILE *fph;
		fph = fopen("c:/projVoo/lib/libAeroportos", "r");
		char destino[100];
		char dd[100];
		char *ress;
		int k = 1;
		while(k <= posicaoY*2){
			   	ress = fgets(dd, 100, fph);
			   	k++;
		}
		strcpy(destino, ress);
		fclose(fph);
		escrever("", 3,15);
		LIMPAR;
		escrever(" Voos correspondentes a busca:\n\n", 5,15);
		char tempBuscaDestino[50];
		escrever("", 3,15);
		FILE *fp;
		fp = fopen("c:/projVoo/lib/libVoos", "r");
		char dados[100];
		char *resultado;
		while(!feof(fp)){
			resultado = fgets(dados, 100, fp);
			if(resultado != NULL){
				if(strcmp(resultado, "linhaBranca\n") == 0){
					resultado = fgets(dados, 100, fp);
					strcpy(tempBuscaDestino, resultado);
					resultado = fgets(dados, 100, fp);
					resultado = fgets(dados, 100, fp);
					if(strcmp(destino, resultado) == 0){
						printf(" Destino: %s", resultado);
						printf(" Origem: %s", tempBuscaDestino);
						resultado = fgets(dados, 100, fp);
						resultado = fgets(dados, 100, fp);
						printf(" Numero do voo: %s", resultado);
						resultado = fgets(dados, 100, fp);
						resultado = fgets(dados, 100, fp);
						printf(" Numero de acentos no voo: %s", resultado);
						
						printf("\n\n\n");
					}
				}
			}
		}
		fclose(fp);
		posicionar(2,20);
		escrever("Precione qualquer tecla para retornar ao menu.", 4,15);
		getch();
		menu();
	}else if(tipo == "numero"){
		char numero[50];
		escrever("", 3,15);
		LIMPAR;
		int i;
		for(i=0; i<30;i++){
			posicionar(i+15,5);
			escrever(" ", 15,3);
		}
		posicionar(5,5);
		escrever("Digite o numero do voo:", 3,15);
		escrever("", 15,3);
		posicionar(29,5);
		fflush(stdin);
		scanf("%s", &numero);
		strcat(numero, "\n");
		escrever("", 3,15);
		LIMPAR;
		escrever(" Voos correspondentes a busca:\n\n", 5,15);
		char tempBuscaOrigem[50];
		char tempBuscaDestino[50];
		escrever("", 3,15);
		FILE *fp;
		fp = fopen("c:/projVoo/lib/libVoos", "r");
		char dados[100];
		char *resultado;
		while(!feof(fp)){
			resultado = fgets(dados, 100, fp);
			if(resultado != NULL){
				if(strcmp(resultado, "linhaBranca\n") == 0){
					resultado = fgets(dados, 100, fp);
					strcpy(tempBuscaOrigem, resultado);
					resultado = fgets(dados, 100, fp);
					resultado = fgets(dados, 100, fp);
					strcpy(tempBuscaDestino, resultado);
					resultado = fgets(dados, 100, fp);
					resultado = fgets(dados, 100, fp);
					if(strcmp(numero, resultado) == 0){
						printf(" Origem: %s", tempBuscaOrigem);
						printf(" Destino: %s", tempBuscaDestino);
						printf(" Numero do voo: %s", resultado);
						resultado = fgets(dados, 100, fp);
						resultado = fgets(dados, 100, fp);
						printf(" Numero de acentos no voo: %s", resultado);
						
						printf("\n\n\n");
					}
				}
			}
		}
		fclose(fp);
		posicionar(2,20);
		escrever("Precione qualquer tecla para retornar ao menu.", 4,15);
		getch();
		menu();
	}
}
void meuHistorico(){
	menu();
}

void menu(){
	int tecla = 0;
	int posicaoX, posicaoY, inicioX, inicioY;
	posicaoX = 1;
	posicaoY = 1;
	while(tecla == 0){
		escrever(" ", 3, 15);
		LIMPAR;
		
		if(strcmp(tiraQuebra(user.adm), "1") == 0){	
			getch();
			logout();
		}else{
			posicionar(5, 2);
			escrever(" ", 0, 15);
			printf("Seja Bem vindo(a) %s", tiraQuebra(user.nome));
			posicionar(80,2);
			escrever("Pressione (Q) para sair.", 12,15);
			int i;
			for(i=5;i<115;i++){
				posicionar(i, 4);
				escrever(" ", 15, 8);
			}
			for(i=5;i<115;i++){
				posicionar(i, 5);
				escrever(" ", 15, 8);
			}
			for(i=5;i<115;i++){
				posicionar(i, 6);
				escrever(" ", 15, 8);
			}
			int j = 8; 
			for(i=60;i<115;i++){
				posicionar(i,8);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,9);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,10);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,11);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,12);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,13);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,14);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,15);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,16);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,17);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,18);
				escrever(" ", 15, 8);
			}
			for(i=60;i<115;i++){
				posicionar(i,19);
				escrever(" ", 15, 8);
			}
			escrever("", 7, 8);
			posicionar(65, 9);
			printf("MEUS DADOS: ");
			escrever(" ", 15, 8);
			posicionar(65, 11);
			printf("Nome: %s", user.nome);
			posicionar(65, 12);
			printf("Sobrenome: %s", user.sobrenome);
			posicionar(65, 13);
			printf("Idade: %s", user.idade);
			posicionar(65, 14);
			printf("Endereco: %s", user.endereco);
			posicionar(65, 15);
			printf("Cidade: %s", user.cidade);
			posicionar(65, 16);
			printf("Estado: %s", user.estado);		
			posicionar(10,5);
			escrever("Efetuar reserva", 15, 8);
			posicionar(35,5);
			escrever("Buscar Voo", 15, 8);
			posicionar(54,5);
			escrever("Meu historico", 15, 8);
			/*
			orientações de navegacao
			*/
			
			posicionar(10, 10);
			escrever("Utilize as teclas abaixo para navegar!!!", 3,15);
			posicionar(20, 12);
			printf("(w) cima");
			posicionar(10, 14);
			printf("(a) esquerda      (d) direita");
			posicionar(20, 16);
			printf("(s) baixo");
			posicionar(60, 18);
			
			posicionar(25,25);
			escrever("PROJETADO E CODADO POR TAUAN © tauan@alunos.utfpr.edu.br", 7, 15);
			if(posicaoX == 1){
				int u;
				for(u=5;u<30;u++){
					posicionar(u, 4);
					escrever(" ",2, 3);
				}
				for(u=5;u<30;u++){
					posicionar(u, 5);
					escrever(" ",2, 3);
				}for(u=5;u<30;u++){
					posicionar(u, 6);
					escrever(" ",2, 3);
				}
				posicionar(10, 5);
				escrever("Efetuar reserva",15,3);
				
			}else if(posicaoX == 2){
				int u;
				for(u=30;u<50;u++){
					posicionar(u, 4);
					escrever(" ",2, 3);
				}
				for(u=30;u<50;u++){
					posicionar(u, 5);
					escrever(" ",2, 3);
				}
				for(u=30;u<50;u++){
					posicionar(u, 6);
					escrever(" ",2, 3);
				}
				posicionar(35, 5);
				escrever("Buscar Voo",15,3);
				posicionar(30,7);
				escrever("                             ", 15,7);
				posicionar(30,8); 
				escrever("  Buscar por origem do voo   ", 8,7);
				posicionar(30,9);
				escrever("  Buscar por destino do voo  ", 8,7);
				posicionar(30,10);
				escrever("  Buscar por numero de voo   ", 8,7);
				posicionar(30,11);
				escrever("                             ", 0,7);
				if(posicaoY==1){
					posicionar(30,8); 
					escrever("  Buscar por origem do voo   ", 3,7);
				}else if(posicaoY==2){
					posicionar(30,9);
					escrever("  Buscar por destino do voo  ", 3,7);
				}else if(posicaoY==3){
					posicionar(30,10);
					escrever("  Buscar por numero de voo   ", 3,7);
				}
			}else if(posicaoX == 3){
				int u;
				for(u=50;u<70;u++){
					posicionar(u, 4);
					escrever(" ",2, 3);
				}
				for(u=50;u<70;u++){
					posicionar(u, 5);
					escrever(" ",2, 3);
				}
				for(u=50;u<70;u++){
					posicionar(u, 6);
					escrever(" ",2, 3);
				}
				posicionar(54, 5);
				escrever("Meu historico",15,3);
			}
			posicionar(80,18);
			if(kbhit){
				char ch = getch();
				if(ch == ENTER){
					tecla = 1;
					switch(posicaoX)
					{
						case 1:
							efetuarReserva();
						break;
						case 2:
							if(posicaoY == 1){
								buscarVoo("origem");
							}else if(posicaoY == 2){
								buscarVoo("destino");
							}else if(posicaoY == 3){
								buscarVoo("numero");
							}
						break;
						case 3:
							meuHistorico();
						break;
					}
				}else if((ch == 'q') || (ch == 'Q')){
					logout();
				}else if((ch == 'w') || (ch == 'W')){
					if((posicaoY > 1) && (posicaoX == 2)){
						posicaoY--;
					}
				}else if((ch == 'a') || (ch == 'A')){
					if(posicaoX > 1){
						posicaoX--;
						posicaoY = 1;
					}
				}else if((ch == 'd') || (ch == 'D')){
					if(posicaoX < 3){
						posicaoX++;
						posicaoY = 1;
					}
				}else if((ch == 's') || (ch == 'S')){
					if((posicaoY < 3) && (posicaoX == 2)){
						posicaoY++;
					}
				}
			}
			
		}
	}
	
}

char * tiraQuebra(char *var){
	int m = strlen(var);
	if(var[m - 1] == '\n'){
		var[--m] = 0;
	}
	return var;
}
// Sessao
void sess() {
	char dados[40];
	FILE *fp;
	fp = fopen("C:/ProjVoo/lib/libSession","r");
	fgets(dados, 40, fp);
	strcpy(sessao, dados);
	fclose(fp);
}

//DADOS
void dados(char *sess){
	FILE *arq;
	char dados[100];
	char *resultado;
	char comp[40];
	strcpy(comp, sess);
	arq = fopen("C:/ProjVoo/lib/libContent", "r");
	while(!feof(arq)) {
		resultado = fgets(dados, 100, arq);
		if(resultado != NULL) {
			int rel = strcmp(resultado, comp);
			if(rel == 0){
				resultado = fgets(dados, 100, arq);
				if(resultado != NULL){
					if(strcmp("linhaAut\n", resultado) == 0){
						resultado = fgets(dados, 100, arq);
						user.id = int(resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.adm, resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.login, resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.nome, resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.sobrenome, resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.idade, resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.endereco, resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.cidade, resultado);
						
						resultado = fgets(dados, 100, arq);
						strcpy(user.estado, resultado);
					}
				}
			}
		}
		
	}
	fclose(arq);
	
}
void login() {
	int a,b,g,c, z, mensagem;
	a = 0;
	b = 0;
	mensagem = 0;
	int  index = 0;	
	char login[50];
	char senha[50] = {0};
	while(a==0){
		area_login();
		if(mensagem!=0){
			switch(mensagem)
			{
			case 2:
				posicionar(38,15);
				escrever("          Dados de login incorretos          ", 15,4);
			break;
			case 1:
				 posicionar(38,15);
				escrever("          Dados de login incorretos          ", 15,4); 	
			break;
			}
		}
		posicionar(55,7);
		escrever("", 15 ,3);
		fflush(stdin);
		scanf("%s", &login);
		posicionar(55,9);
		fflush(stdin);
		while(1)
	    {
	        char ch = getch();
	
	        if(ch == ENTER)
	            break;
	        else
	            putchar('*');
	        senha[index] = ch; 
	        index++;
	    }
		posicionar(53,12);
		escrever("Autenticando dados", 3,7);
		for(c=41;c<80;c++){
			posicionar(c,13);
			escrever(" ",1, 3 );
			Sleep(150);
		}
	    index = 0;
	    FILE *arq;
		char dados[50];
		char *resultado;
		strcat(login, "\n");
		strcat(senha, "\n");
		int c;
		arq = fopen("C:/ProjVoo/lib/libAcess", "rt");
		c = 1;
		while(!feof(arq)) {
			resultado = fgets(dados, 50, arq);
			if((c % 2) != 0){
				if(strcmp(login, resultado) == 0) {
					resultado = fgets(dados, 50, arq);
					c++;
					if(strcmp(senha, resultado) == 0){
						FILE * lok;
						lok = fopen("C:/ProjVoo/lib/libAut","w");
						fprintf(lok, "1 #tauan %% linkValue 1690 TRUE\n2 #tauan %% linkValue 1691 TRUE\n3 #tauan %% linkValue 1692 TRUE");
						fclose(lok);
						FILE * lod;
						lod = fopen("C:/ProjVoo/lib/libSession","w");
						fprintf(lod, "%s", login);
						fclose(lod);
						a++;
						autenticado = 1;
					}else {
						mensagem = 1;
					}
				}else { mensagem = 2; }
			}
			c++;
		}
		for(z=0;z<50;z++){
			senha[z] = {0};
		}
		c = 1;
		b++;
		LIMPAR;
	}
}
void area_login() {
	int i;
	escrever(" ", 3, 7);
	LIMPAR;
	LOGIN_TELA;
	for(i=40;i<80;i++){
		posicionar(i,6);
		escrever(" ", 3,15);
	}
	for(i=40;i<80;i++){
		posicionar(i,7);
		escrever(" ", 3,15);
	}
	for(i=40;i<80;i++){
		posicionar(i,8);
		escrever(" ", 3,15);
	}
	for(i=40;i<80;i++){
		posicionar(i,9);
		escrever(" ", 3,15);
	}
	for(i=40;i<80;i++){
		posicionar(i,10);
		escrever(" ", 3,15);
	}
	posicionar(40,5);
	escrever("              EFETUE LOGIN              ",15,3);
	posicionar(42, 7);
	escrever("   Usuario: ", 3,15);
	posicionar(42, 9);
	escrever("   Senha:   ", 3,15);
	posicionar(54, 7);
	escrever("                      ",1, 3 );
	posicionar(54, 9); 
	escrever("                      ",1, 3 );
}
int autenticar(){
	int a;
	FILE *fp;
	if(fopen("c:/projVoo/lib/libAut", "r") == NULL){
		login();
	}
	fp = fopen("c:/projVoo/lib/libAut", "r");
	fflush(stdin);
	a = int(fgetc(fp));
	if(a == 49){
		autenticado = 1;

	} else {
		autenticado = 0;
		login();
	}
	return 1;
}
void escrever(char *texto, int cor, int background) {
	textcolor(cor);
	textbackground(background); 
    printf("%s", texto);
}
void posicionar(int left, int top) {
	gotoxy(left,top);
}
void logout() {
	FILE *arq;
	arq = fopen("c:/projVoo/lib/libAut", "w");
	fprintf(arq, " 1 #tauan %% linkValue 1690 TRUE\n 2 #tauan %% linkValue 1691 TRUE\n 3 #tauan %% linkValue 1692 TRUE");
	fclose(arq);
	exit(0);
}
int tempo(int valor){
	Sleep(valor);
	return 1;
}