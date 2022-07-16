

#include <iostream>
#include <cstdio>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ficha {
	char nome[200]; 		
	char end[50]; 
	char endi[50]; 		
	int cpf; 	
	float sal[20];		
	int status;			
	int qtd, qtdf;			
	float valor;		
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cont_ficha (const char* arquivo) {	
	FILE *fp;
	if ((fp = fopen (arquivo, "rb")) == NULL) {
		return 0;
	} else {
		fseek (fp, 0, SEEK_END);
		int pos = ftell(fp);
		fclose(fp);
		return (pos / sizeof (ficha));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ler_arquivo(ficha* produto, FILE* fp) {	
	fread(produto, sizeof(ficha), 1, fp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrar_apartamentos (ficha* produto) {	
	cout << endl << "EDERECO DO IMOVEL: " << (*produto).end << endl;
	cout <<         "VALOR DO ALUGUEL : " << (*produto).valor << endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrar_cliente (ficha* CLIENTESSSS) {	
	cout << endl << "NOME DO CLIENTE: " << (*CLIENTESSSS).endi << endl;
	cout <<         "CPF : " << (*CLIENTESSSS).cpf << endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int mostrar_apts_disponiveis (ficha* produto) {  
	FILE *fp;
	int cont = 0;
	if ((fp = fopen("arquivo.dat", "r+b")) == NULL) {
		cout << "Erro ao abrir arquivo! ";
		exit (0);
	} else {
		if ((cont_ficha("arquivo.dat")) == 0) {
			cout << "Voce ainda nao possui nenhum apartamento cadastrado! " << endl << endl;
			system ("pause");
			return 0;
		}
		ler_arquivo(produto, fp);
		cout << "Segue lista de apartamentos disponiveis: " << endl;
		while (!feof (fp)) {
			if (((*produto).status) == 0) {
				mostrar_apartamentos(produto);
				cont++;
			}
			ler_arquivo(produto, fp);
		}
		if (cont == 0) {
			cout << "Nao ha apartamentos disponiveis " << endl << endl;
		}
	}
	fclose (fp);
	system ("pause");

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cadastrarAP(FILE* fp) {		
	ficha produto;
	char x, status = 'S', _status = 'N';

	do {
		if ((fp = fopen ("arquivo.txt", "ab")) == NULL) {
			cout << "Erro ao abrir arquivo para gravacao!";
			exit(0);
		}
		system("cls");
		cout << "Cadastrando o "<< cont_ficha("arquivo.txt") + 1 << "Apartamento:" << endl << endl;


		cout << "NUMERO DE PROPRIETARIOS: ";
		cin >> produto.qtd;
		fflush(stdin);

		fflush(stdin);
		cout << "ENDERECO DO APARTAMENTO: ";
		gets(produto.end);
		strupr(produto.end);
		fflush(stdin);

		cout << "VALOR DO ALUGUEL P/MES R$:  ";
		cin >> produto.valor;
		fflush(stdin);

		if (produto.qtd > 0) {
			produto.status = 0;
		} else {
			produto.status = 1;
		}

		fwrite (&produto, sizeof (ficha), 1, fp);

		do {
			cout << endl << "Cadastrar novo apartamento? [S/N]" << endl;
			cin >> x;
			strupr(&x);
		} while ((x != 'N') && (x != 'S'));
		fclose(fp);
	} while (x != 'N');

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cadastrarCL(FILE* fp) {		
	ficha CLIENTESSSS;
	char x, status = 'S', _status = 'N';

	do {
		if ((fp = fopen ("arquivo.txt", "ab")) == NULL) {
			cout << "Erro ao abrir arquivo para gravacao!";
			exit(0);
		}
		system("cls");
		cout << "Cadastrando o "<< cont_ficha("arquivo.dat") + 1 << "Cliente:" << endl << endl;


		cout << "NUMERO DO CPF: ";
     	cin >> CLIENTESSSS.cpf;
		fflush(stdin);

		fflush(stdin);
		cout << "NOME E SOBRENOME: ";
		gets(CLIENTESSSS.nome);
		strupr(CLIENTESSSS.nome);
		fflush(stdin);

		cout << "SALARIO P/MES R$ ";
		cin >> CLIENTESSSS.sal[20];
		fflush(stdin);

		if (CLIENTESSSS.qtdf > 0) {
			CLIENTESSSS.status = 0;
		} else {
			CLIENTESSSS.status = 1;
		}

		fwrite (&CLIENTESSSS, sizeof (ficha), 1, fp);

		do {
			cout << endl << "Cadastrar novo Cliente? [S/N]" << endl;
			cin >> x;
			strupr(&x);
		} while ((x != 'N') && (x != 'S'));
		fclose(fp);
	} while (x != 'N');

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pesquisar(FILE* fp) {		
	ficha produto;
	ficha CLIENTESSSS;
	char _end[50],_nome[20];
	int op, j = 1;
	do {
		if ((fp = fopen ("arquivo.txt", "rb")) == NULL) {
			cout << "Erro na abertura do arquivo para leitura! ";
			exit (0);
		}
		system ("cls");
		if ((cont_ficha("arquivo.txt")) == 0) {
			cout << "E necessario pelo menos um apartamento ou cliente cadastrado para utilizar essa opcao! " << endl << endl;
			system ("pause");
			return 0;
		}
		cout << "Pesquisar por: " << endl << endl;
		cout << "\t[1] - endereco do apartamento" << endl;
		cout << "\t[2] - Nome do cliente" << endl;
		cout << "\t[0] - Voltar para o menu principal" << endl;
		cin >> op;

		switch(op) {
			case 0:
				break;
			case 1:
				system ("cls");
				fflush(stdin);
				cout << "Entre com o endereco: ";
				gets(_end);
				strupr(_end);
				ler_arquivo(&produto, fp);
				ler_arquivo(&CLIENTESSSS, fp);
		
				do {
					if ((strcmp(produto.end, _end)) == 0) {
						mostrar_apartamentos (&produto);
						j = 0;
					
					}
					ler_arquivo(&produto, fp);
				} while (!feof(fp));
				if (j == 1) {
					cout << "Nao encontrado! " << endl;
				} else {
					j = 1;
				}
				system("pause");
				break;
					case 2:
				system ("cls");
				fflush(stdin);
				cout << "Entre com o nome e sobrenome: ";
				gets(_nome);
				strupr(_nome);
				ler_arquivo(&CLIENTESSSS, fp);
				do {
					if ((strcmp(CLIENTESSSS.nome, _nome)) == 0) {
						mostrar_cliente (&CLIENTESSSS);
						j = 0;
					
					}
					ler_arquivo(&CLIENTESSSS, fp);
				} while (!feof(fp));
				if (j == 1) {
					cout << "cliente nao encontrado! " << endl;
				} else {
					j = 1;
				}
				system("pause");
				break;
			default:
				system ("cls");
				cout << "Opcao invalida! ";
				break;
		}
		fclose (fp);
	} while (op != 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void limpa_arquivo () {
	FILE *fp = fopen("arquivo.txt", "wb");
	cout << "Arquivo limpo com sucesso! " << endl;
	system("pause");
	fclose(fp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int mostrar_todos(ficha* produto) {
	FILE *fp;
	if ((fp = fopen ("arquivo.txt", "r+b")) == NULL) {
		cout << "Erro ao abrir arquivo para leitura!";
		exit (0);
		system ("pause");
		return 0;
	} else {
		if ((cont_ficha("arquivo.txt")) == 0) {
			cout << "Voce ainda nao possui nenhum apartamento cadastrado! " << endl << endl;
			system ("pause");
			return 0;
		}
		ler_arquivo(produto, fp);
		cout << "Segue lista de todos os apartamentos cadastrados: " << endl;
		while (!feof(fp)) {
			mostrar_apartamentos(produto);
			ler_arquivo(produto, fp);
		}
			ler_arquivo(produto, fp);
		cout << "Segue lista de todos os clientes cadastrados: " << endl;
		while (!feof(fp)) {
			mostrar_cliente(produto);
			ler_arquivo(produto, fp);
		}
	}
	fclose (fp);
	system ("pause");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int mostrar_todo(ficha* CLIENTESSSS) {
	FILE *fp;
	if ((fp = fopen ("arquivo.txt", "r+b")) == NULL) {
		cout << "Erro ao abrir arquivo para leitura!";
		exit (0);
		system ("pause");
		return 0;
	} else {
		if ((cont_ficha("arquivo.txt")) == 0) {
			cout << "Voce ainda nao possui nenhum cliente cadastrado! " << endl << endl;
			system ("pause");
			return 0;
	
		}
			ler_arquivo(CLIENTESSSS, fp);
		cout << "Segue lista de todos os clientes cadastrados: " << endl;
		while (!feof(fp)) {
			mostrar_cliente(CLIENTESSSS);
			ler_arquivo(CLIENTESSSS, fp);
		}
	}
	fclose (fp);
	system ("pause");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main () {
	setlocale(LC_ALL, "Portuguese");
	FILE* fp;
	ficha produto;
	int op;
	char op1;

	do {
	

cout << "                                   ..........ProStar Alugel..........";
    
cout << "\n";
cout << "\n";

cout << "                                   .......INTERFACE DA EMPRESA......." ;

cout << "\n";
cout << "\n";
cout << "\n";
cout << "\n";

cout << "                               ____________________________________________ \n";
cout << "                              |                                            | \n";
cout << "                              | 1 - Para adicionar apartamento.............| \n";
cout << "                              |                                            | \n";
cout << "                              | 2 - Para pesquisar.........................| \n";
cout << "                              |                                            | \n";
cout << "                              | 3 - Para Adicionar um cliente .............| \n";
cout << "                              |                                            | \n";
cout << "                              | 4 - Para mostrar todos.....................| \n";
cout << "                              |                                            | \n";
cout << "                              |99 - Para limpar o arquivo..................| \n";
cout << "                              |                                            | \n";
cout << "                              |                                            | \n";
cout << "                              |                                            | \n";
cout << "                              |                                            | \n";
cout << "                              |                                            | \n";
cout << "                              | 0 - Para Finalizar O Programa..............| \n";
cout << "                              |                                            | \n";
cout << "                              |............................................| \n";

cout << "                                   Digite o numero que deseja utilizar : ";

		cin >> op;

		switch (op) {
			case 0:
				cout << endl << endl <<"Finalizando...";
				break;
			case 1:
				cadastrarAP(fopen("arquivo.txt", "ab"));
				break;
			case 2:
				system ("cls");
				pesquisar(fopen("arquivo.txt", "rb"));
				break;
			case 3:
				system("cls");
				cadastrarCL(fopen("arquivo.txt", "ab"));
				break;
			case 4:
				system ("cls");
				mostrar_todos(&produto);
					system("cls");
				mostrar_todo(&produto); 
				break;
			case 99:
				system("cls");
				fflush(stdin);
				cout << "Tem certeza que deseja limpar TODOS OS DADOS cadastrados? [S/N]" << endl;
				cin >> op1;
				strupr(&op1);
				if (op1 == 'S') {
					limpa_arquivo();
				}
				break;
			default:
				cout << endl << "Opcao invalida! " << endl;
				system ("pause");
				break;
		}
	} while (op != 0);

	return 0;
}

