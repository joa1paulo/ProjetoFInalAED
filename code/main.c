#include "receita.h"
#include <stdio.h>

int main(){
    Lista* lista = criarLista();
    int opcao = 0;
    
    while(opcao != 10){
        exibirMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        // Limpar o buffer de entrada após scanf
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        
        switch(opcao){
            case 1:
                cadastrarReceita(lista);
                break;
            case 2:
                removerReceita(lista);
                break;
            case 3:
                listarReceitas(lista);
                break;
            case 4:
                cadastrarIngredienteReceita(lista);
                break;
            case 5:
                listarIngredientesReceita(lista);
                break;
            case 6:
                listarReceitasPorIngrediente(lista);
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
    
    liberarLista(lista);
    return 0;
}
