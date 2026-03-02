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
        while((c = getchar()) != '\n' && c != EOF);// limpar o buffer de entrada após scanf
        switch(opcao){
            case 1:
                cadastrarReceita(lista);
                break;
            case 2:  // Função para remover receita 
                printf("Digite o nome da receita a remover: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                removerReceita(lista, buffer);
                break;
            case 3: // Função para listar receitas 
                listarReceitas(lista);
                break;
            case 4:// Função para cadastrar ingrediente em uma receita 
                printf("Digite o nome da receita: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                cadastrarIngredienteReceita(lista, buffer);
                break;
            case 5:// Função para listar ingredientes de uma receita 
                printf("Digite o nome da receita: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                listarIngredientesReceita(lista, buffer);
                break;
            case 6:// Função para listar receitas por ingrediente 
                printf("Digite o ingrediente: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                listarReceitasPorIngrediente(lista, buffer);
                break;
            case 7:// Função para encontrar o prato com menor preço
                MenorPreco(lista);
                break;
            case 8:// Função para encontrar o ingrediente mais usado
                IngredienteMaisUsado(lista);
                break;
            case 9:// Função para encontrar ingredientes em comum entre receitas
                IngredientesEmComum(lista);
                break;
            case 10:// saída do loop
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
    return 0;
}
