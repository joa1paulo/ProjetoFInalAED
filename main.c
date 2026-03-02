#include "lista.h"
#include <stdio.h>
#include <string.h>

int main(){
    Lista* lista = criarLista();
    int opcao = 0;
    char buffer[100];
    while(opcao != 10){
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        switch(opcao){
            case 1:
                cadastrarReceita(lista);
                break;
            case 2:  // Função para remover receita (a ser implementada)
                printf("Digite o nome da receita a remover: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                removerReceita(lista, buffer);
                break;
            case 3: // Função para listar receitas (a ser implementada)
                listarReceitas(lista);
                break;
            case 4:// Função para cadastrar ingrediente em uma receita (a ser implementada)
                printf("Digite o nome da receita: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                cadastrarIngredienteReceita(lista, buffer);
                break;
            case 5:// Função para listar ingredientes de uma receita (a ser implementada)
                printf("Digite o nome da receita: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                listarIngredientesReceita(lista, buffer);
                break;
            case 6:
                printf("Digite o ingrediente: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                listarReceitasPorIngrediente(lista, buffer);
                break;
            case 7:
                MenorPreco(lista);
                break;
            case 8:
                IngredienteMaisUsado(lista);
                break;
            case 9:
                IngredientesEmComum(lista);
                break;
            case 10:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
    return 0;
}
