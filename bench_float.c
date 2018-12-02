//Autor: Guilherme Milan Santos
//Numero USP: 9012966
//Turma: BCC B

#include <stdio.h>
#include <stdlib.h>

//Le do console uma matriz com as dimensoes especificadas
double **le_matriz(int linhas, int colunas);

//Imprime elemento por elemento de uma matriz com as dimensoes especificadas
void imprime_matriz(double  **matriz, int linhas, int colunas);

//Aplica o escalonamento na matriz ate obter uma matriz triangular superior
double **triangula_matriz(double **matriz, int qtd_linhas, int qtd_colunas,
                         int *qtd_trocas_de_linha);

//Multiplica uma linha inteira da matriz (sem modificar a matriz)
//retorna uma copia da linha original, multiplicada pelo numero
double *multiplica_linha_por_numero(double *linha, int qtd_colunas, double numero);

//Soma uma linha da matriz com uma segunda linha especificada
//Nao altera a matriz, mas retorna uma copia da linha original ja com os valores somados
double *soma_duas_linhas(double *linha1, double *linha2, int qtd_colunas);

//Imprime uma linha da matriz (para fins de debug)
void imprime_linha(double *linha, int colunas);

//Pega uma das linhas temporarias geradas nas funcoes acima e coloca
//no lugar de uma das linhas da matriz
double **substitui_linha_na_matriz(double **matriz, int linha_substituida,
                                  double *linha_substituidora, int qtd_colunas);

//Troca duas linhas da matriz de posicao. usada no caso de achar um
//pivo 0 no escalonamento
double **troca_linhas_da_matriz(double **matriz, int linha1, int linha2);

//Multiplica os numeros da diagonal principal da matriz
//usado na matriz ja triangulada para obter o determinante
double multiplica_elementos_na_diagonal_principal(double **matriz, int ordem_matriz);

//Funcao que recebe a matriz escalonada e devolve o resultado do sistema
//linear representado por ela
double *calcula_resultado_sistema(double **matriz, int qtd_linhas, int qtd_colunas);

//Funcao que calcula o determinante da matriz, levando em consideracao o numero de trocas
//de linha que foram realizadas para obter a matriz triangulada
double calcula_determinante(double **matriz, int qtd_variaveis, int qtd_trocas_de_linha);

int main() {
    int qtd_variaveis;
    double  **matriz;
    int qtd_trocas_de_linha;
    double determinante;

    //No final do loop, pede para o usuario digitar 1 para continuar executando
    //ou 0 para parar, e coloca na variavel 'executando'. se 'executando' for zero, o programa
    //acaba
    int executando = 1;
    while(executando) {
        //Le o numero de componentes de cada vetor
        printf("digite a quantidade de componentes dos vetores: ");
        scanf("%d", &qtd_variaveis);
        printf("\n");

        //Le elemento por elemento da matriz, e imprime a matriz resultante no final
        matriz = le_matriz(qtd_variaveis, qtd_variaveis);
        printf("\nMatriz original: \n");
        imprime_matriz(matriz, qtd_variaveis, qtd_variaveis);
        printf("\n");

        //Escalona a matriz
        triangula_matriz(matriz, qtd_variaveis, qtd_variaveis, &qtd_trocas_de_linha);

        printf("\nMatriz escalonada: \n");
        imprime_matriz(matriz, qtd_variaveis, qtd_variaveis);

        //Calcula o determinante da matriz
        determinante = calcula_determinante(matriz, qtd_variaveis, qtd_trocas_de_linha);
        printf("\nDeterminante: %.5lf\n", determinante);

        //Com o determinante calculado, especifica se os vetores sao LI ou LD
        if(determinante == 0.0f) {
            printf("Os vetores sao linearmente dependentes\n");
        } else {
            //Se forem LI, calcula os escalares para fazer com que a combinacao linear
            //dos vetores resulte no vetor V=(1,2,3,...,n)
            printf("Os vetores sao linearmente independentes\n");
            double *resultado = calcula_resultado_sistema(matriz, qtd_variaveis, qtd_variaveis+1);
            int i;
            printf("Solucao: [");
            for(i=0; i < qtd_variaveis; i++) {
                printf("%.4lf ", resultado[i]);
            }
            printf("]\n");
        }
        //Permite que o usuario execute novamente ou encerre o programa
        printf("executar novamente? 0/1: ");
        scanf("%d", &executando);
    }
    return 0;
}

//Funcao que calcula o determinante da matriz, levando em consideracao o numero de trocas
//de linha que foram realizadas para obter a matriz triangulada
double calcula_determinante(double **matriz, int qtd_variaveis, int qtd_trocas_de_linha) {
    double determinante = 0;

    determinante = multiplica_elementos_na_diagonal_principal(matriz, qtd_variaveis);
    if(qtd_trocas_de_linha % 2 != 0) {
        determinante = determinante * (-1);
    }
    if(determinante == -0.0f) {
        determinante = 0.0f;
    }

    return determinante;
}

//Funcao que recebe a matriz escalonada e devolve o resultado do sistema
//linear representado por ela
double *calcula_resultado_sistema(double **matriz, int qtd_linhas, int qtd_colunas) {
    double *resultado = malloc(sizeof(double)*qtd_linhas);
    double soma;
    int i, j, k;
    for(i=qtd_linhas-1; i >= 0; i--) {
        resultado[i] = 1;
        soma = 0;
        //Descobre o valor das incognitas de baixo para cima,
        //substituindo nas linhas de cima o valor das incognitas
        //obtidas nas linhas de baixo
        for(j = qtd_linhas-1; j > i; j--) {
            soma += matriz[i][j]*resultado[j];
        }
        resultado[i] = (matriz[i][qtd_colunas-1]-soma)/matriz[i][i];
    }
    return resultado;
}

//Aplica o escalonamento na matriz ate obter uma matriz triangular superior
double **triangula_matriz(double **matriz, int qtd_linhas, int qtd_colunas,
                         int *qtd_trocas_de_linha) {
    int i, j, k;
    (*qtd_trocas_de_linha) = 0;
    double pivo;
    double fator;
    double *linha_temporaria = malloc(sizeof(double)*qtd_colunas+1);

    //Varre a matriz pelos elementos abaixo da diagonal principal
    for(j=0; j < qtd_colunas-1; j++) {
        for(i=j+1; i < qtd_colunas; i++) {
            //Se o elemento varrido ja for zero, pula
            if(matriz[i][j] == 0) {
                continue;
            }
            //Escolhe o pivo
            pivo = matriz[j][j];
            //Se o pivo for zero, procura uma linha em que o elemento correspondente
            //nao eh zero e faz a troca de linha. tambem recorda a quantidade de trocas
            //de linha para trocar o resultado do determinante no final, se o numero
            //de trocas de linha tiver sido impar
            if(pivo == 0) {
                k = j+1;
                while(matriz[k][j] == 0 && k < qtd_linhas) {
                    k++;
                }
                troca_linhas_da_matriz(matriz, j, k);
                (*qtd_trocas_de_linha)++;
                pivo = matriz[j][j];
            }
            //Calcula o fator pelo qual a linha do pivo deve ser multiplicada,
            //faz a multiplicacao, e soma na linha cujo elemento deve ser zerado
            fator = -matriz[i][j] / pivo;
            linha_temporaria = multiplica_linha_por_numero(matriz[j], qtd_colunas+1, fator);
            linha_temporaria = soma_duas_linhas(linha_temporaria, matriz[i], qtd_colunas+1);
            substitui_linha_na_matriz(matriz, i, linha_temporaria, qtd_colunas+1);
        }
    }
    return matriz;
}

//Troca duas linhas da matriz de posicao. usada no caso de achar um
//pivo 0 no escalonamento
double **troca_linhas_da_matriz(double **matriz, int linha1, int linha2) {
    double *aux = matriz[linha1];
    matriz[linha1] = matriz[linha2];
    matriz[linha2] = aux;
    return matriz;
}

//Multiplica os numeros da diagonal principal da matriz
//usado na matriz ja triangulada para obter o determinante
double multiplica_elementos_na_diagonal_principal(double **matriz, int ordem_matriz) {
    double resultado = 1;
    int i;
    for(i=0; i < ordem_matriz; i++) {
        resultado *= matriz[i][i];
    }
    return resultado;
}

//Pega uma das linhas temporarias geradas nas funcoes de soma e multiplicacao de linha
//e coloca no lugar de uma das linhas da matriz
double **substitui_linha_na_matriz(double **matriz, int linha_substituida,
                                  double *linha_substituidora, int qtd_colunas) {
    int i, j;
    for(i=0; i < qtd_colunas; i++) {
        matriz[linha_substituida][i] = linha_substituidora[i];
    }
    return matriz;
}

//Soma uma linha da matriz com uma segunda linha especificada
//Nao altera a matriz, mas retorna uma copia da linha original ja com os valores somado
double *soma_duas_linhas(double *linha1, double *linha2, int qtd_colunas) {
    double *resultado = malloc(sizeof(double)*qtd_colunas);
    int i;
    for(i=0; i < qtd_colunas; i++) {
        resultado[i] = linha1[i] + linha2[i];
    }
    return resultado;
}

//Multiplica uma linha inteira da matriz (sem modificar a matriz)
//retorna uma copia da linha original, multiplicada pelo numero
double *multiplica_linha_por_numero(double *linha, int qtd_colunas, double numero) {
    int i;
    double *resultado = malloc(sizeof(double)*qtd_colunas);
    for(i=0; i < qtd_colunas; i++) {
        resultado[i] = linha[i]*numero;
    }
    return resultado;
}

//Le do console uma matriz com as dimensoes especificadas
double **le_matriz(int linhas, int colunas) {
    int i, j;
    double **matriz = malloc(sizeof(double*)*linhas);
    int coordenada_v = 1;

    for(i=0; i < linhas; i++) {
        matriz[i] = malloc(sizeof(double)*(colunas+1));
        for(j=0; j < colunas; j++) {
            printf("[%d][%d]: ", i, j);
            scanf("%lf", &matriz[i][j]);
        }
        matriz[i][colunas] = coordenada_v;
        coordenada_v++;
    }
    return matriz;
}

//Imprime uma linha da matriz (para fins de debug)
void imprime_linha(double *linha, int colunas) {
    int i;
    for(i=0; i < colunas; i++) {
        printf("%.2lf\t", linha[i]);
    }
    printf("\n");
}

//Imprime elemento por elemento de uma matriz com as dimensoes especificadas
void imprime_matriz(double **matriz, int linhas, int colunas) {
    int i, j;
    for(i=0; i < linhas; i++) {
        for(j=0; j < colunas; j++) {
            printf("%.5lf ", matriz[i][j]);
        }
        printf("\n");
    }
}
