#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main() {
    printf("\t\tBem Vindo!\n\n");

    Lista *li = criaLista();
    if (li == NULL) {
        abortaPrograma();
    }
    lerArquivo(li);

    int opcao;
    do {
      printf("\n");
        printf("========================================\n");
        printf("|                MENU                  |\n");
        printf("========================================\n");
        printf("| 1. Inserir novo contato              |\n");
        printf("| 2. Gerar relatorio total             |\n");
        printf("| 3. Gerar relatorio por codigo        |\n");
        printf("| 4. Gerar relatorio por nome          |\n");
        printf("| 5. Editar contato                    |\n");
        printf("| 6. Remover contato                   |\n");
        printf("| 7. Sair                              |\n");
        printf("========================================\n");
        printf("O que deseja fazer?");
        scanf("%d", &opcao);
        printf("\n\n");
        switch (opcao) {
            case 1:
                insereNovoContato(li);

                break;

            case 2:
                relatorioGeral(li);
                break;

            case 3:
                relatorioCodigo(li);
                break;

            case 4:
                relatorioNome(li);
                break;

            case 5:
                editaContato(li);
                break;
            case 6:
                removeContato(li);
                break;

            case 7:
                gravaArquivo(li);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
