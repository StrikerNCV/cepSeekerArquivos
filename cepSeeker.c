#include <stdio.h>
#include <string.h>

typedef struct _Adress Adress;

struct _Adress
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int buscaBinaria(FILE *f, char *cepSeek,long inicio,long fim,int cont){

	Adress a;
	long mid;
	rewind(f);
	if(inicio <= fim){

		int qt;

		cont++;

		mid = (inicio+fim)/2;

		fseek(f,(mid*sizeof(Adress)),SEEK_SET);

		qt = fread(&a, sizeof(Adress), 1, f);

		if(strncmp(cepSeek,a.cep,8) == 0){
			printf("\nLogradouro: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.72s\nSigla: %.2s\nCEP: %.8s\n\n",a.logradouro,a.bairro,a.cidade,a.uf,a.sigla,a.cep);
			return cont;
		}
		else{
			if(strncmp(cepSeek,a.cep,8) > 0){
				buscaBinaria(f,cepSeek,mid+1,fim,cont);
			}
			else if(strncmp(cepSeek,a.cep,8) < 0){
				buscaBinaria(f,cepSeek,inicio,mid-1,cont);
			}

		}

	}
	else{
		
		printf("Nao foi possivel encontrar o CEP\n");
		return cont;

	}

}

int main(int argc, char**argv){
	
	FILE *f;
	char cepSeek[8];
	long first, posic, last, mid;

	if(argc != 2){
		printf("Qual cep voce deseja encontrar?:\n");
		int x= 0;
		while(x < 8){
			cepSeek[x++] = getchar();
		}
	}
	else{

		strncpy(cepSeek,argv[1],8);

	}

	f = fopen("cep_ordenado.dat","r");


	fseek(f,0,SEEK_END);
	posic = ftell(f);
	
	printf("Tamanho do Registro: %ld\n", sizeof(Adress));
	printf("Tamanho do Arquivo: %ldBytes\n", posic);
	printf("Tamanho do Arquivo em Registros: %ld\n", posic/sizeof(Adress));
	
	first = 0;
	last = (posic/sizeof(Adress))-1;

	
	printf("\n -- Busca Binaria --\n\n");
	printf("Numero de ciclos: %d\n",buscaBinaria(f, cepSeek,first, last, 0));

	return 0;
}
