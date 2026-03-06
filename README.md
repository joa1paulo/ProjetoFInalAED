# 🥗 Projeto: Receitas Culinárias Saudáveis

Este projeto, desenvolvido como o **Tema 4**, propõe uma solução robusta para o gerenciamento de receitas saudáveis utilizando a linguagem C. A espinha dorsal da aplicação baseia-se na manipulação dinâmica de memória, utilizando listas duplamente ligadas e listas encadeadas simples.

---

## 📋 Status do Projeto

| Funcionalidade | Status |
| :--- | :---: |
| Cadastrar receita | ✅ |
| Remover receita | ✅ |
| Listar receitas | ✅ |
| Cadastrar ingredientes | ✅ |
| Contar ingredientes por receita | ✅ |
| Listar receitas por tipo | ❌ |
| Calcular valor calórico | ❌ |
| Cruzamento de dados (Ingredientes repetidos, etc) | ✅ |

---

## 🏗️ Estrutura de Dados
Toda a lógica do projeto gira em torno da manipulação de duas listas principais:

* **`Lista (No)`**: Uma lista duplamente ligada definida em `lista.h`, que armazena o nome, preço e a cabeça da sublista de ingredientes de cada receita.
* **`Receita`**: Uma lista encadeada simples definida em `ingrediente.h`, que armazena os ingredientes de forma linear.

---

## ⚙️ Detalhamento das Funções

### 🏠 Gestão de Receitas
* **`CriarLista()`**: Aloca o ponteiro para a estrutura do nó principal após reservar a memória necessária.
* **`CadastrarReceita()`**: A função mais complexa do sistema. Solicita nome, preço e número de ingredientes, gerencia o buffer de strings e insere o novo nó no início da lista principal.
* **`RemoverReceita()`**: Localiza a receita via `strcmp`, chama obrigatoriamente a função de liberação de sublista e reajusta os ponteiros dos nós vizinhos.
* **`ListarReceitas()`**: Percorre a lista duplamente ligada exibindo os dados formatados de cada prato.

### 🧪 Manipulação de Ingredientes
* **`CadastrarIngredienteReceita()`**: Adiciona novos itens a pratos já existentes, garantindo a alocação dinâmica com `strdup`.
* **`ListarIngredientesReceita()`**: Realiza busca sequencial e imprime a lista simples de ingredientes até encontrar o valor nulo.
* **`LiberarIngredientes()`**: Garante que nenhum endereço de memória seja perdido, limpando os nós da sublista recursivamente ou via laço.

### 📊 Análise e Cruzamento de Dados
* **`MenorPreço()`**: Complexidade $O(n)$. Identifica a receita mais barata (implementada como alternativa ao valor calórico).
* **`RegistrarIngrediente()`**: Núcleo do sistema de frequência. Utiliza ponteiros duplos (`freq**`) para modificar diretamente a contagem de itens globais.
* **`IngredienteMaisUsado()`**: Varre a lista de frequência temporária para identificar o item com maior contador.
* **`IngredientesEmComum()`**: Identifica e filtra quais componentes são compartilhados por mais de uma receita (contador > 1).
* **`ListarReceitasPorIngrediente()`**: Busca cruzada que retorna quais pratos cadastrados utilizam um ingrediente específico.

---

## 📖 Como utilizar
Abaixo, um exemplo do fluxo de interação com o sistema através do menu interativo:

### 1. Cadastrando e Listando Receitas
```shell
Escolha uma opcao: 1
Digite o nome do prato: ovo
Digite o preço do prato: 20
digite o numero de ingredientes: 2
Digite o ingrediente 1: ovo
Digite o ingrediente 2: oleo

Escolha uma opcao: 3
Nome: macarrao
Preco: 50.00
Ingredientes:
 - macarrao
 - oleo
 - sal
---
Nome: ovo
Preco: 20.00
Ingredientes:
 - ovo
 - oleo

---

## 🧠 Reflexão e Aprendizados
O método de implementação de **"uma lista dentro da outra"** foi fundamental para o entendimento da lógica de cruzamento de dados e manipulação de memória dinâmica. O uso do **GitHub** como ferramenta de colaboração permitiu um desenvolvimento incremental e organizado, abrindo portas para algoritmos mais eficientes no futuro.

---
> **Nota:** Projeto desenvolvido para fins acadêmicos com foco em Estrutura de Dados.
