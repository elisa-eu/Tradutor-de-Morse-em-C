🌳 Tradutor de Código Morse (Árvore Binária em C)

Este projeto é um tradutor de Texto para Código Morse (e vice-versa), desenvolvido inteiramente na linguagem C. Esse foi um projeto que eu fiz para a matéria de Estrutura de Dados Avançados na faculdade.

Utilizei árvores binárias para fazê-lo.

Para otimizar a tradução de Morse para texto, o programa constrói uma árvore binária onde:

Cada nó da árvore representa um caractere (letra ou número).

Um caminho para a esquerda (esq) representa um Ponto (.).

Um caminho para a direita (dir) representa um Traço (-).

Dessa forma, ao receber um código morse como .- (letra A), o algoritmo simplesmente desce um nível para a esquerda e um nível para a direita na árvore, encontrando o caractere de forma extremamente eficiente (O(h), onde h é o tamanho do código).

Conceitos Aplicados:

Estruturas de Dados Avançadas: Árvores Binárias (struct node, ponteiros de ligação).

Gerenciamento de Memória: Uso massivo de alocação dinâmica (malloc) e liberação de memória (free) para evitar memory leaks.

Manipulação de Strings: Uso de bibliotecas padrão C (string.h) para concatenação e cópia segura de buffers.

Algoritmos de Travessia: Implementação de busca recursiva e impressão Pré-Ordem (ImprimirPreOrdem).

🛠️ Exemplo de Uso

O menu interativo via terminal permite duas opções:

Português -> Morse:

Entrada: OLA MUNDO

Saída: --- .-.. .- / -- ..- -. -.. --- 

Morse -> Português:

Entrada: --- .-.. .- / -- ..- -. -.. ---

Saída: OLA MUNDO