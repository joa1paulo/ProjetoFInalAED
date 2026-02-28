#include "Lista.h"

int main(){
    Lista* lista = criarLista();
    int opcao;

    while(opcao != 6) {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarReceita(lista);
                break;
            case 2:
                // Função para remover receita (a ser implementada)
                break;
            case 3:
                // Função para listar receitas (a ser implementada)
                break;
            case 4:
                // Função para cadastrar ingrediente em uma receita (a ser implementada)
                break;
            case 5:
                // Função para listar ingredientes de uma receita (a ser implementada)
                break;  
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }


}