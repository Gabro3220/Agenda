#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct elemento {
    CLIENTE dados;
    struct elemento *prox;
};

typedef struct elemento ELEM;



void lerArquivo(Lista *li) {
    FILE *arquivo = fopen("listadecontatos.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }else{
        printf("Dados salvos carregados com sucesso\n");
    };

    CLIENTE cliente;
    while (fread(&cliente, sizeof(CLIENTE), 1, arquivo)) {
        insereOrdenado(li, cliente);
    }

    fclose(arquivo);
}

Lista* criaLista() {
    Lista *li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}


void abortaPrograma() {
    printf("Erro, lista nao foi alocada corretamente\n");
    printf("Programa sera encerrado...\n\n\n");
    exit(1);
}

void liberaLista(Lista *li) {
    ELEM *atual = *li;
    while (atual != NULL) {
        ELEM *x = atual;
        atual = atual->prox;
        free(x);
    }
    free(li);
}


int listaVazia(Lista *li) {
    if (li == NULL) {
        abortaPrograma();
    }
    if (*li == NULL) {
        return 1;
    }
    return 0;
}

int insereOrdenado(Lista *li, CLIENTE cl) {
    if (li == NULL) {
        abortaPrograma();
    }
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if (no == NULL) {
        return 0;
    }
    no->dados = cl;
    if (listaVazia(li)) {
        no->prox = (*li);
        *li = no;
        return cl.codigo;
    } else {
        ELEM *ant, *atual = *li;
        while (atual != NULL && atual->dados.codigo < cl.codigo) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) {
            no->prox = (*li);
            *li = no;
        } else {
            no->prox = ant->prox;
            ant->prox = no;
        }
        return cl.codigo;
    }


}

void insereNovoContato(Lista *li) {
    CLIENTE novoCliente;
    printf("Digite o codigo: ");
    scanf("%d", &novoCliente.codigo);

     if(consultaCodigo(li, novoCliente.codigo)!= NULL){

        printf("Erro: Este codigo ja esta associado a um contato\n ");

        return;

    }
    getchar();
    printf("Digite o nome: ");
    fgets(novoCliente.nome, 50, stdin);
    printf("Digite a empresa: ");
    fgets(novoCliente.empresa, 50, stdin);
    printf("Digite o departamento: ");
    fgets(novoCliente.departamento, 80, stdin);
    printf("Digite o telefone: ");
    scanf("%s", novoCliente.telefone);
    printf("Digite o celular: ");
    scanf("%s", novoCliente.celular);
    printf("Digite o email: ");
    scanf("%s", novoCliente.email);
    printf("\n\n");
    printf(" Contato inserido com sucesso!");
    insereOrdenado(li, novoCliente);
}


void relatorioGeral(Lista *li) {
    printf("\tRelatorio Geral:\n\n");
    ELEM *atual = *li;
    while (atual != NULL) {
        printf("\tCodigo: %d\n\n Nome: %s Empresa: %s Departamento: %s Telefone: %s\n Celular: %s\n Email: %s\n",
               atual->dados.codigo,
               atual->dados.nome,
               atual->dados.empresa,
               atual->dados.departamento,
               atual->dados.telefone,
               atual->dados.celular,
               atual->dados.email);
               atual = atual->prox;
               printf("\n\n");
    }
}




ELEM* consultaCodigo(Lista *li, int codigo){
    if(li == NULL){
        abortaPrograma();
    }
    ELEM *atual = *li;
    while(atual != NULL && atual->dados.codigo != codigo){
        atual = atual->prox;
    }
    return atual;
}

void relatorioCodigo(Lista *li) {
    int cod;
    printf("\nDigite o codigo: ");
    scanf("%d", &cod);

    ELEM *resultado = consultaCodigo(li, cod);
    if (resultado != NULL) {
        printf("\n\tCodigo: %d\n\n Nome: %s Empresa: %s Departamento: %s Telefone: %s\n Celular: %s\n Email: %s\n",
                resultado->dados.codigo,
                resultado->dados.nome,
                resultado->dados.empresa,
                resultado->dados.departamento,
                resultado->dados.telefone,
                resultado->dados.celular,
                resultado->dados.email);
                printf("\n\n");
    } else {
        printf("\nContato nao encontrado!\n");
        printf("\n\n");
    }
}

void consultaNome(Lista *li, char *nome) {

    ELEM *atual = *li;
    int encontrado = 0;
    while (atual != NULL) {
        if(strncasecmp(atual->dados.nome, nome, strlen(nome)- 1) == 0) {
            printf("\n\tCodigo: %d\n\n Nome: %s Empresa: %s Departamento: %s Telefone: %s\n Celular: %s\n Email: %s\n",
                   atual->dados.codigo,
                   atual->dados.nome,
                   atual->dados.empresa,
                   atual->dados.departamento,
                   atual->dados.telefone,
                   atual->dados.celular,
                   atual->dados.email);
                   encontrado = 1;
        }
        atual = atual->prox;
    }

    if (!encontrado){
            printf("\nNenhum contato encontrado");
    }


}

void relatorioNome(Lista *li) {
    char nome[50];
    printf("Digite o nome: ");
    getchar();
    fgets(nome, 50, stdin);
    printf("\nResultados da busca por nome '%s':\n", nome);
    if (strlen(nome) < 2 ) {
        printf("opcao invalida");
        return;

    }
    consultaNome(li, nome);
    printf("\n\n");
}

void editaContato(Lista *li) {
    int cod;
    printf("Digite o codigo: ");
    scanf("%d", &cod);

    ELEM *resultado = consultaCodigo(li, cod);
    if (resultado != NULL) {
        printf("\n\tCodigo: %d\n\n Nome: %s Empresa: %s Departamento: %s Telefone: %s\n Celular: %s\n Email: %s\n",
                resultado->dados.codigo,
                resultado->dados.nome,
                resultado->dados.empresa,
                resultado->dados.departamento,
                resultado->dados.telefone,
                resultado->dados.celular,
                resultado->dados.email);


         printf("\n\tDeseja alterar as informacoes desse contato? (s/n): ");
         char opcao;
         scanf(" %c", &opcao);
         if (opcao == 's' || opcao == 'S') {
                printf("\nDigite o novo nome: ");
                getchar();
                fgets(resultado->dados.nome, 50, stdin);
                printf("Digite a nova empresa: ");
                fgets(resultado->dados.empresa, 50, stdin);
                printf("Digite o novo departamento: ");
                fgets(resultado->dados.departamento, 80, stdin);
                printf("Digite o novo telefone: ");
                scanf("%s", resultado->dados.telefone);
                printf("Digite o novo celular: ");
                scanf("%s", resultado->dados.celular);
                printf("Digite o novo email: ");
                scanf("%s", resultado->dados.email);

                printf("\nContato editado com sucesso!\n");
         }


    } else {
        printf("\n Contato nao encontrado!\n");
        printf("\n\n");
    }
}

void removerCodigo(Lista *li, int codigo) {
    if (*li == NULL) return;

    if ((*li)->dados.codigo == codigo) {
        ELEM *x = *li;
        *li= (*li)->prox;
        free(x);
        return;
    }

    ELEM *atual = *li;
    while (atual->prox != NULL && atual->prox->dados.codigo != codigo) {
        atual = atual->prox;
    }

    if (atual->prox != NULL) {
        ELEM *x = atual->prox;
        atual->prox = x->prox;
        free(x);
    }
}

void removeContato(Lista *li) {
    int codigo;
    printf("Digite o codigo do contato a ser removido: ");
    scanf("%d", &codigo);

    ELEM *resultado = consultaCodigo(li, codigo);
    if (resultado != NULL) {
        printf("\n\tCodigo: %d\n\n Nome: %s Empresa: %s Departamento: %s Telefone: %s\n Celular: %s\n Email: %s\n",
               resultado->dados.codigo,
               resultado->dados.nome,
               resultado->dados.empresa,
               resultado->dados.departamento,
               resultado->dados.telefone,
               resultado->dados.celular,
               resultado->dados.email);

        printf("\nDeseja remover este contato? (s/n): ");
        char opcao;
        scanf(" %c", &opcao);
        if (opcao == 's' || opcao == 'S') {
            removerCodigo(li, codigo);
            printf("\nContato removido com sucesso!\n");
            printf("\n\n");
        }
    } else {
        printf("\nContato nao encontrado!\n");
        printf("\n\n");
    }
}

void gravaArquivo(Lista *li) {
    FILE *arquivo = fopen("listadecontatos.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    ELEM *atual = *li;
    while (atual != NULL) {
        fwrite(&atual->dados, sizeof(CLIENTE), 1, arquivo);
        atual = atual->prox;
    }
    printf("Dados salvos com sucesso\n");
    fclose(arquivo);
}
