#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char letras[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};

void printArray(int array[], int length)
{
	printf("[");
	for (int i = 0; i < length; i++)
	{
		if (i != length - 1)
		{
			printf(" %d,", array[i]);
		}
		else
		{
			printf(" %d", array[i]);
		}
	}
	printf("]\n");
}

void printArrayOnlySpaced(int array[], int length)
{
	for (int i = 0; i < length; i++)
	{
		if (i)
		{
			printf(" %d", array[i]);
		}
		else
		{
			printf("%d", array[i]);
		}
	}
	printf("\n");
}

//dado um caractere, retorna o número correspondente ao mesmo
int encodeChar(char messagePiece){
	if (messagePiece >= 65 && messagePiece <= 90){
		messagePiece += 32;
	}
	for(int i = 0; i < 27; i++){
		if(letras[i] == messagePiece){
			return i+2;
		}
	}
	return -1; //significa que a letra fornecida é inválida
}

//transforma uma string em uma sequência numérica
void encodeString(char* message, int result[], int length){
	//pedir length como parãmetro ajuda a lembrar que result deve ter tamanho length 
	for (int i = 0; i < length; i++){
		result[i] = encodeChar(message[i]);
	}
}

//dado um numero, retorna o caractere correspondente ao mesmo
char decodeChar(int messagePiece){
	if(messagePiece>=2 && messagePiece<=28){
		return letras[messagePiece-2];
	}
	return '*'; //significa que o número não existe na coleção
}

//transforma uma sequência numérica em uma string
void decodeString(int message[], char result[], int length){
	//pedir length como parãmetro ajuda a lembrar que result deve ter tamanho length
	for (int i = 0; i < length; i++){
		result[i] = decodeChar(message[i]);
	}
}

//valida a relaçao entre e e (p-1(q-1)
int calculaMDC(int x, int y){
    int resto = 1;    
    int contador = 0;

    while (resto > 0){       
        resto = x%y; 
        x = y;      
        y = resto;
           
        contador += 1;
    }    
    return x;
}

// verifica p e q
int ehPrimo(int numero){
    int contador = 2;

    if (numero == 0 || numero == 1){
        return 0;
    }

    while (contador <= (numero/2)+1){
        if ((numero%contador) == 0){
            return 0;
		}
		contador += 1;  
    }       
    return 1; 
}


void gerarChavePublica(){
	FILE *keyFile;
	int p, q, e, i, pq_validos, e_validos;
	int chave[2];	   //pra gravar a chave no txt
	int chave_lida[2]; //para ler a chave do txt

	printf("P e Q:\n");
	while (pq_validos != 1) //só da continuidade se os numeros forem primos
	{
		scanf("%d%d", &p, &q);
		if (ehPrimo(p) && ehPrimo(q))
		{
			printf("São válidos\n\n");
			pq_validos = 1;

			int z = (p - 1) * (q - 1); // e deve ser coprimo a isto
			int n = p * q;			   //primeira parte da chave
			chave[0] = n;

			printf("E:\n");
			while (e_validos != 1) // só da continuidade se for coprimo
			{
				scanf("%d", &e); //segunda parte da chave

				if ((calculaMDC(e, z)) == 1)
				{
					printf("É válido\n");
					e_validos = 1;

					chave[1] = e;

					keyFile = fopen("key.txt", "w");					  //cria o arquivo pra gravação
					int res = fwrite(&chave, sizeof(int), 2, keyFile); //grava os valores do vetor no txt
					fclose(keyFile);									  //fecha o arquivo
				}
				else
				{
					printf("Não é válido\n\n");
					e_validos = 0;
				}
			}

			keyFile = fopen("key.txt", "r");				//abre o arquivo pra leitura
			fread(&chave_lida, sizeof(int), 2, keyFile); //lê os valores do txt e escreve-os no segundo vetor
			printf("Sua chave pública: (%d,%d)\n\n", chave_lida[0], chave_lida[1]);
			fclose(keyFile); //fecha arquivo
		}
		else
		{
			printf("Não são válidos\n\n");
			pq_validos = 0;
		}
	}
}

//função da Questão 7 da lista prática
int coeficientesInverso (int quocientes[], int contador, int mod){
	int matriz_st[100];
	int st[2];
	int c_inicial = contador;
	int t = 0;
	int s = 1;
	int i = 0;

	if (contador == 0)
	{			   //contador é par
		st[0] = t; //esse é meu s
		st[1] = s; //esse é meu t
	}
	else if (contador == 1)
	{										  //contador é ímpar
		st[0] = s + t;						  //esse é meu s
		st[1] = (quocientes[0] * s + t) * -1; //esse é meu t
	}
	else
	{
		contador -= 1;
		while (contador >= 0)
		{
			matriz_st[i] = quocientes[contador] * s + t;
			t = s;
			s = matriz_st[i];

			contador -= 1;
			i += 1;
		}
		if (c_inicial % 2 == 0)
		{								   // se contador for par, o s tem que ser negativo
			st[0] = matriz_st[i - 2] * -1; //esse é meu s
			st[1] = matriz_st[i - 1];	   //esse é meu t
		}
		else
		{								   // se o contador é impar, o t tem que ser negativo
			st[0] = matriz_st[i - 2];	   //esse é meu s
			st[1] = matriz_st[i - 1] * -1; //esse é meu t
		}
	}

	s = st[0];
	if (s < 0)
	{
		while (s < 0 && s < mod)
		{ //0 incluso ou nao?
			s = s + mod;
		}
	}
	return s;
}

//função da Questão 7 da lista prática
int calculaInversoMod(int x, int y){
	int resto = 1;
	int contador = 0;
	int quocientes[100];
	int mod = y;

	while (resto > 0)
	{
		resto = x % y;

		if (resto == 0) //pq nao queremos incluir o valor do quociente quando o resto é 0
		{
			x = y; // garante o valor do mdc
			break;
		}
		else
		{
			quocientes[contador] = x / y;
			x = y;
			y = resto;
			contador += 1;
		}
	}

	return coeficientesInverso(quocientes, contador, mod);
}

//dados n e M, verifica se n é uma potência de M
//esta função foi pensada para expoModRapida mas como vou fazer expoModRapida ser mais geral... não será utilizada... 
int aPotenciaDeB(int a, int b){
	if(a == b){
		return 1;
	}
	else
	{
		if (a%b == 0){
			return aPotenciaDeB(a/b, b);
		} else {
			return 0;
		}
	}
}

//exponenciação modular rápida de potências de 2, é componente de expoModRapida
long expoModRapidaPot2(long M, long e, long n){ 
	//C = M**e mod n
	long c;

	//printf("\nM:%ld e:%ld n:%ld\n", M, e, n);
	if (e != 2){
		long res = expoModRapidaPot2(M, (e/2), n);
		c = (res * res) % n;
	} else {
		c = (M * M) % n;
	}

	
	return c;
}

//base**expoente
long potenciaInt(long base, long expoente){
	if (expoente == 0){
		return 1;
	}

	if (base == 1){
		return 1;
	}

	long result = base;
	for (long i = 0; i < expoente-1; i++){
		result *= base;
	}

	return result;
}

int expoentesBinariosDeInteiro(int n, int res[]){
	int counter = 0;

	for (int i = 0; i < 32; i++){
		if(n){ //n != 0
			if(n%2){ //bit i = 1
				res[counter] = potenciaInt(2,i);
				counter++;
			}
			n = n/2;
		}
		else{
			break;
		}
	}

	return counter; //retorna quantidade de expoentes
}

int expoModRapida(int M, int e, int n)
{
	//C = M**e mod n
	//printf("Iniciou expoModRapida(%d,%d,%d)\n", M, e, n);
	long long c = 1;

	int lenExpBinE, expBinE[32]; //expoentes binários de e
	lenExpBinE = expoentesBinariosDeInteiro(e, expBinE);


	for (int i = 0; i < lenExpBinE; i++){
		if(expBinE[i] == 1){
			c *= M;
		} else {
			long res = expoModRapidaPot2(M, expBinE[i], n);
			//printf("-> expoModRapidaPot2(%d,%d,%d) = %ld\n", M, expBinE[i], n, res);
			c *= res;
			//printf("    -> %lld\n", c);
		}
	}
	c = c % n;

	//printf("resultado: %lld\n\n",c);

	int resposta = c;
	return resposta;
}

void encriptar()
{
	//ler e codificar a string
	char mensagem[5000];
	printf("Mensagem: ");
	fgets(mensagem, sizeof(mensagem), stdin);
	fgets(mensagem, sizeof(mensagem), stdin);
	/*
		A linha duplicada previne que o resultado
		de fgets seja o \n que scanf deixou no 
		stream quando foi executado no menu...

		bugs estranhos de C, como sempre
	*/

	int tamanho = strlen(mensagem) - 1; //pq fgets adiciona como ultimo caractere
	int codificada[tamanho];

	encodeString(mensagem, codificada, tamanho);

	//encriptar a string codificada em numeros 
	FILE *keyFile;
	int key[2];

	keyFile = fopen("key.txt", "r");
	fread(&key, sizeof(int), 2, keyFile);
	printf("Chave pública contida no arquivo -> n: %d, e: %d\n", key[0], key[1]);
	fclose(keyFile);

	int n = key[0];
	int e = key[1];

	int encriptada[tamanho];

	int C;
	for (int i = 0; i < tamanho; i++){
		int M = codificada[i];
		C = expoModRapida(M, e, n);
		encriptada[i] = C;
	}

	printArray(codificada, tamanho);
	printArray(encriptada, tamanho);

	//write encypted string to message.txt
	FILE *msgFile;
	msgFile = fopen("message.txt", "w");
	fwrite(&encriptada, sizeof(int), tamanho, msgFile); //change encoded to encrypted 
	fclose(msgFile);
}

void decriptar(){
	//ler a mensagem encriptada e codificada
	FILE *msgFile;
	int encriptada[5000];
	int tamanho;

	msgFile = fopen("message.txt", "r");
	tamanho = fread(&encriptada, sizeof(int), 5000, msgFile);
	fclose(msgFile);

	//decriptar a mensagem codificada
	int codificada[5000];
	int p, q, e;
	printf("P, Q e E:\n");
	scanf("%d %d %d", &p, &q, &e);

	int pq = (p * q);
	int p1q1 = (p - 1) * (q - 1);

	int d = calculaInversoMod(e, p1q1);
	printf("Inverso: %d\n", d);

	int M;
	for (int i = 0; i < tamanho; i++)
	{
		M = expoModRapida(encriptada[i], d, pq);
		codificada[i] = M;
	}

	printArray(encriptada, tamanho);
	printArray(codificada, tamanho);

	//decodificar a mensagem
	char mensagem[tamanho + 1];
	mensagem[tamanho] = '\0';

	decodeString(codificada, mensagem, tamanho);
	printf("Mensagem: %s\n", mensagem);
}

void menu(){
	int op;
	int shouldContinue = 1;

	while (shouldContinue)
	{
		printf("\n--------------MENU--------------\n");
		printf("Opção 0: Sair\nOpção 1: Gerar chave pública\nOpção 2: Encriptar\nOpção 3: Decriptar\n");
		printf("---------------------------------\n");
		printf("Opção: ");
		scanf("%i", &op);

		switch (op)
		{
		case 0:
			printf("\nExecução finalizada.\n");
			shouldContinue = 0;
			break;

		case 1:
			printf("\n-------GERAR-CHAVE-PÚBLICA-------\n");
			gerarChavePublica();
			printf("\n");
			break;

		case 2:
			printf("\n-------ENCRIPTAR-MENSAGEM--------\n");
			encriptar();
			printf("\n");
			break;

		case 3:
			printf("\n-------DECRIPTAR-MENSAGEM--------\n");
			decriptar();
			printf("\n");
			break;

		default:
			printf("%d não é uma opção válida.\n\n", op);
			break;
		}
	}
}

int main(){
	/*TESTE - expoModRapidaPot2(int M, int e, int n) sendo M**e mod n
	long M, e, n;
	scanf("%ld %ld %ld", &M, &e, &n);
	printf("%ld\n", expoModRapidaPot2(M, e, n));
	//FUNÇÃO VALIDADA*/

	/*TESTE - expoentesBinariosDeInteiro(int n, int res[]) sendo M**e mod n
	int n, res[32] = {0};
	scanf("%d", &n);
	int i = expoentesBinariosDeInteiro(n, res);
	printArray(res, i);
	//FUNÇÃO VALIDADA*/

	/*TESTE - potenciaInt(int base, int expoente) sendo b**e
	int n;
	scanf("%d", &n);
	printf("%d\n", potenciaInt(2, n));
	//FUNÇÃO VALIDADA*/

	/*TESTE - expoModRapida(int M, int e, int n) sendo M**e mod n
	int M, e, n;
	scanf("%d %d %d", &M, &e, &n);
	printf("%d\n", expoModRapida(M, e, n));
	//FUNÇÃO VALIDADA*/

	menu();
}