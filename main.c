#include <stdio.h>
#include <math.h>
//valida a relaçao entre e e (p-1(q-1)
int calcula_mdc(int x, int y){
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
int eh_primo(int numero){
    int contador = 2;

    if (numero == 0 || numero == 1)
    {
        return 0;
    }

    while (contador < numero)
    {
        if ((numero%contador) == 0)
        {
            return 0;
        }
        contador += 1;  
    }       
    return 1; 
}

void menu(){
    FILE *chaves;
    int opcao, p, q, e, i, pq_validos, e_validos;
    int chave[2]; //pra gravar a chave no txt
    int chave_lida[2]; //para ler a chave do txt


    printf("Opção 1: Gerar chave pública \nOpção 2: Encriptar \nOpção 3: Desencriptar \n");
    scanf("%d", &opcao);
    
    if(opcao == 1) //chave publica
    {
        printf("Digite p e q: \n");
        while (pq_validos != 1) //só da continuidade se os numeros forem primos
        {
            scanf("%d%d", &p, &q);
            if(eh_primo(p) == 1 && eh_primo(q)== 1) 
            {
                printf("Numeros válidos\n");
                pq_validos = 1;

                int z = (p-1) * (q-1); // e deve ser coprimo a isto
                int n = p * q; //primeira parte da chave                        
                chave[0] = n;

                printf("Digite e: \n");
                while (e_validos != 1) // só da continuidade se for coprimo
                {
                    scanf("%d", &e); //segunda parte da chave               
                   
                    if((calcula_mdc(e, z)) == 1)
                    {
                        printf("Válido\n");
                        e_validos = 1;   
                        
                        chave[1] = e;

                        chaves = fopen ("key.txt", "w"); //cria o arquivo pra gravação  
                        int res = fwrite(&chave, sizeof(int), 2, chaves); //grava os valores do vetor no txt
                        fclose(chaves); //fecha o arquivo
                    }
                    else
                    {
                        printf("Invalido\n");
                        e_validos = 0;
                    }
                }
                
                chaves = fopen ("key.txt", "r"); //abre o arquivo pra leitura
                fread(&chave_lida, sizeof(int), 2, chaves); //grava os valores do txt no segundo vetor
                printf("Sua chave pública: (%d,%d)\n\n", chave_lida[0], chave_lida[1]); 
                fclose(chaves); //fecha arquivo
            }
            else
            {
                printf("Nao sao primos\n");
                pq_validos = 0;
            }
        }  
    }
    else if(opcao == 2) //encriptar
    {
        //taigo, lute
    }
    else if(opcao == 3) //desencriptar
    {
        //taigo, lute duas vezes
    }

    menu();
}
void main(){
    menu();
}