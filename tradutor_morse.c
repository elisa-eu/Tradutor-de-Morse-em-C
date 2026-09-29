#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node* link;
struct node {
    char codigo[8];
    char chave;
    link esq;
    link dir;
};

link raiz = NULL;

link criarNo(){
    link novo = (link)(malloc(sizeof(struct node)));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->chave = '\0';
    novo->codigo[0] = '\0';

    return novo;
}

void inserir(link raiz, char letra, char *codigo_morse){
    link atual = raiz;
    for(int i = 0; codigo_morse[i] != '\0'; i++){
        if(codigo_morse[i] == '.'){
            if(atual->esq == NULL){
                atual->esq = criarNo();
            }
            atual = atual->esq;
        } 
        else if(codigo_morse[i] == '-'){
            if(atual->dir == NULL){
                atual->dir = criarNo();
            }
            atual = atual->dir;
        }
    }
    
    atual->chave = letra;
    strcpy(atual->codigo, codigo_morse);  //copia a string do código para dentro do nó
}

void ConstruirArvore(link raiz, char *vetor_codigos[]){
    for(int i = 0; i < 10; i++){ //numeros
        char numero = '0' + i; 
        inserir(raiz, numero, vetor_codigos[i]);
    }
    for(int i = 0; i < 26; i++){ //letras
        char letra = 'A' + i; 
        inserir(raiz, letra, vetor_codigos[i + 10]);
    }
}

void ImprimirPreOrdem(link raiz, char vetor[], int idx){ 
    if(raiz == NULL){
        return;
    }
        
    if(raiz->chave != '\0'){
        printf("%s -> %c\n", vetor, raiz->chave);
    }
          
    vetor[idx] = '.';
    vetor[idx + 1] = '\0';

    ImprimirPreOrdem(raiz->esq, vetor, idx + 1);

    vetor[idx] = '-';
    vetor[idx + 1] = '\0';

    ImprimirPreOrdem(raiz->dir, vetor, idx + 1);
}

link buscar(link raiz, char chave){
    if(raiz == NULL){
        return NULL;
    }

    if(raiz->chave == chave){
        return raiz;
    }


    link achou_esq = buscar(raiz->esq, chave);
    if(achou_esq != NULL){
        return achou_esq;
    }

    return buscar(raiz->dir, chave);
}


char* Traduzir(link raiz, char *mensagem){
    int tamanho_max = (strlen(mensagem) * 6) + 1;
    char *traduzida = (char*) malloc(tamanho_max * sizeof(char));
    
    traduzida[0] = '\0'; 

    for(int i = 0; mensagem[i] != '\0'; i++){
        if(mensagem[i] == ' '){
            strcat(traduzida, "/ ");
        } 
        else{
            char letra = toupper(mensagem[i]);
            link no = buscar(raiz, letra);
            
            if(no != NULL){
                strcat(traduzida, no->codigo);
                strcat(traduzida, " ");
            }
        }
    }
    
    return traduzida; // usar o free() na hora de chamar a função
}

char* MorseToPortugues(link raiz, char *mensagem_morse){
    int tamanho_max = strlen(mensagem_morse);
    char *traduzida_morse = (char*) malloc(tamanho_max * sizeof(char));
    
    traduzida_morse[0] = '\0';
    link atual = raiz;

    int n = 0;
    
    for(int i = 0; i < strlen(mensagem_morse) + 1; i++){ //--- .. / ..
        if(mensagem_morse[i] == '.'){
            atual = atual->esq;
        }
        else if(mensagem_morse[i] == '-'){
            atual = atual->dir;
        }
        else if(mensagem_morse[i] == ' ' || mensagem_morse[i] == '\0'){
            if(atual != raiz){
                traduzida_morse[n] = atual->chave;
                atual = raiz;
                n++;
            }
        }
        else if(mensagem_morse[i] == '/'){
            traduzida_morse[n] = ' ';
            n++;
        }
    }
    
    traduzida_morse[n] = '\0';
    return traduzida_morse; // usar o free() na hora de chamar a função
}


int main(){
    char *codigo_morse[36] = { // dicionario
        "-----", ".----", "..---", "...--", "....-", 
        ".....", "-....", "--...", "---..", "----.",
        
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    char vetor[20] = "";

    link raiz = criarNo();
    ConstruirArvore(raiz, codigo_morse);
    ImprimirPreOrdem(raiz, vetor, 0);

    printf("\n1- PORTUGUES -> MORSE\n2- MORSE -> PORTUGUES\n");
    printf("Sua escolha:");
    int escolha;
    scanf("%d", &escolha);
    while(getchar() != '\n');

    if(escolha == 1){
        char mensagem[10000];
        printf("Digite a mensagem em PORTUGUES: ");
        fgets(mensagem, sizeof(mensagem), stdin);
        mensagem[strcspn(mensagem, "\n")] = '\0';
        char *resultado = Traduzir(raiz, mensagem);
    
        printf("Mensagem: %s\n", mensagem);
        printf("Morse: %s\n", resultado);

        free(resultado);
    }
    
    else if(escolha == 2){
        char mensagem[10000];
        printf("Digite o codigo MORSE: ");
        fgets(mensagem, sizeof(mensagem), stdin);
        mensagem[strcspn(mensagem, "\n")] = '\0';
        char *resultado = MorseToPortugues(raiz, mensagem);
    
        printf("Morse: %s\n", mensagem);
        printf("Mensagem: %s\n", resultado);

        free(resultado);
    }
    
    else{
        printf("Escolha inválida!");
    }
    
    return 0;
}

