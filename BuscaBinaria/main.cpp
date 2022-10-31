#include <iostream>
#include <cstring>

using namespace std;

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Dedicado ao Espaço no final da linha e a quebra de linha
};

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Erro ao utilizar %s\n", argv[0]);
		fprintf(stderr,"USO: %s [CEP PARA BUSCA]\n",argv[0]);
		return 1;
	}

	FILE *f;
	Endereco e;
	int total, cmp, tamarq, tamreg, inicio, meio, fim;

	f = fopen("cep.dat","r");
	fseek(f,0,SEEK_END);
	tamarq = ftell(f);
	tamreg = sizeof(Endereco);
	inicio = 0;
	fim = (tamarq/tamreg) - 1;
	total = 0;

	while(inicio <= fim)
	{
		meio = (inicio+fim)/2;
		fseek(f,meio*tamreg,SEEK_SET);
		fread(&e,tamreg,1,f);
		/* onde &e e o endereco da variavel da struct endereco, sizeof e o tamanho da struct,
		1 e a quantidade de enderecos que esta sendo inserida e f eo ponteiro pro arquivo. */
		total++;
		cmp = strncmp(argv[1],e.cep,8);
		if(cmp == 0)
		{
			cout <<("CEP encontrado! =)\n\n");
			cout <<("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			cout <<("Total lidos: %d\n", total);
			fclose(f);
			return 0;
		}
		else if(cmp > 0)
			inicio = meio + 1;
		else
			fim = meio - 1;
	}

	cout <<("CEP não encontrado! =(\n");
	fclose(f);
	return 1;
}
