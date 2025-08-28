#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct produto
{
    int codigo;
    int qnt_E;
    float Pv;
    char Nome[50];
} P;
typedef struct venda
{
    int codigo_V;
    P p_Ve;
    float Vt;
} V;



int verificaEx(P A[],int ent,int qnt)
{
    int aux_2=0;
    for(int i=0; i<qnt; i++)
    {
        if(A[i].codigo==ent)
        {
            aux_2=1;
            break;
        }
    }
    return aux_2;
}


void Cadastro(P A[], int *qnt_p)
{
    int aux;

    if (*qnt_p == 50)
    {
        printf("\n\n\n\t\t\t\t+-----------------------------------------------------+\n");
        printf("\t\t\t\t|                 Estoque lotado!                   |\n");
        printf("\t\t\t\t+-----------------------------------------------------+\n");
        fflush(stdin);
        getchar();
        system("cls");
        return;
    }

    system("cls");

    printf("\n\n\n");
    printf("\t\t+---------------------------------------------------------+\n");
    printf("\t\t|                  CADASTRO DE PRODUTO                    |\n");
    printf("\t\t+---------------------------------------------------------+\n");

    printf("\t\t| Código do Produto: ");
    scanf("%d", &aux);

    if (!verificaEx(A, aux, *qnt_p))
    {
        A[*qnt_p].codigo = aux;

        printf("\t\t| Nome do Produto: ");
        fflush(stdin);
        gets(A[*qnt_p].Nome);

        printf("\t\t| Quantidade em Estoque: ");
        scanf("%d", &A[*qnt_p].qnt_E);

        printf("\t\t| Preço de Venda: R$");
        scanf("%f", &A[*qnt_p].Pv);

        printf("\t\t+---------------------------------------------------------+\n");
        printf("\t\t| Produto cadastrado com sucesso!                         |\n");
        printf("\t\t+---------------------------------------------------------+\n");

        (*qnt_p)++;
    }
    else
    {
        printf("\t\t+---------------------------------------------------------+\n");
        printf("\t\t| Produto já existe no estoque!                           |\n");
        printf("\t\t+---------------------------------------------------------+\n");
    }

    printf("\n\t\tPressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
}

void Registro(P A[], V B[], int *qnt_p, int *qnt_v)
{
    int aux, aux_2, ven, i,tam,tam2;
    float val;
    tam = *qnt_p;
    tam2=*qnt_v;

    system("cls");
    printf("\n\n\t\t+-------------------------------------------------------------+\n");
    printf("\t\t|                     REGISTRO DE VENDA                      |\n");
    printf("\t\t+-------------------------------------------------------------+\n");

    printf("\n\t\t| Digite o código do produto para venda: ");
    scanf("%d", &aux);

    for (i = 0; i < tam; i++)
    {
        if (A[i].codigo == aux)
        {
            system("cls");
            printf("\n\n\t\t+-------------------------------------------------------------+\n");
            printf("\t\t| Produto encontrado: %s                                      \n", A[i].Nome);
            printf("\t\t+-------------------------------------------------------------+\n");

            printf("\n\t\t| Digite a quantidade de itens vendidos: ");
            scanf("%d", &ven);

            if (A[i].qnt_E >= ven)
            {
                val = ven * A[i].Pv;
                printf("\n\t\t| Valor da venda: R$%.2f", val);
                printf("\n\t\t| Confirma a venda? (1 - Sim, 0 - Não): ");
                scanf("%d", &aux_2);

                if (!aux_2)
                {
                    system("cls");
                    printf("\n\t\t| Venda cancelada! Pressione ENTER para continuar...");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    return;
                }


                A[i].qnt_E -= ven;

                B[tam2].codigo_V = tam2;
                B[tam2].p_Ve.codigo = A[i].codigo;
                strcpy(B[tam2].p_Ve.Nome, A[i].Nome);
                B[tam2].p_Ve.qnt_E = A[i].qnt_E;
                B[tam2].p_Ve.Pv = A[i].Pv;
                B[tam2].Vt = val;
                (*qnt_v)++;

                system("cls");
                printf("\n\t\t+-------------------------------------------------------------+\n");
                printf("\t\t| Produto vendido com sucesso!                                |\n");
                printf("\t\t+-------------------------------------------------------------+\n");
                printf("\n\t\t| Pressione ENTER para continuar...");
                fflush(stdin);
                getchar();
                system("cls");
                return;
            }
            else
            {
                system("cls");
                printf("\n\t\t+-------------------------------------------------------------+\n");
                printf("\t\t| Quantidade insuficiente em estoque para a venda!           |\n");
                printf("\t\t+-------------------------------------------------------------+\n");
                printf("\n\t\t| Pressione ENTER para tentar novamente...");
                fflush(stdin);
                getchar();
                system("cls");
                return;
            }
        }
    }

    system("cls");
    printf("\n\t\t+-------------------------------------------------------------+\n");
    printf("\t\t| Produto não encontrado no estoque!                          |\n");
    printf("\t\t+-------------------------------------------------------------+\n");
    printf("\n\t\t| Pressione ENTER para tentar novamente...");
    fflush(stdin);
    getchar();
    system("cls");
}

void L_Produtos_D(P A[],int *qnt_p)
{
    int i=0,tam;
    tam = *qnt_p;
    printf("\n\n\t\t+---------------------------------------------------------+\n");
    printf("\t\t|                 LISTA DE PRODUTOS DISPONÍVEIS            |\n");
    printf("\t\t+---------------------------------------------------------+\n");

    for(; i<tam; i++)
    {
        if(A[i].qnt_E>0)
        {
            printf("\n\t\t| Código: %d | Nome: %s | Quantidade: %d | Preço: R$%.2f |\n", A[i].codigo, A[i].Nome, A[i].qnt_E, A[i].Pv);;
        }
    }
    printf("\n\t\tPressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
}

void L_Vendas(V B[],int *qnt_v)
{
    int i=0,tam;
    tam = *qnt_v;
    printf("\n\n\t\t+---------------------------------------------------------+\n");
    printf("\t\t|                       LISTA DE VENDAS                    |\n");
    printf("\t\t+---------------------------------------------------------+\n");

    for(; i<tam; i++)
    {
        printf("\n\t\t |Código da Venda: %d \n\t\t |Código do Produto: %d \n\t\t |Nome: %s \n", B[i].codigo_V, B[i].p_Ve.codigo, B[i].p_Ve.Nome);
        printf("\t\t |Quantidade em Estoque (Atual): %d \n\t\t |Quantidade Vendida: %.0f  \n\t\t |Preço de Venda:R$%.2f        \n\t\t |Valor Total da Venda:R$%.2f \n", B[i].p_Ve.qnt_E,B[i].Vt/B[i].p_Ve.Pv, B[i].p_Ve.Pv, B[i].Vt);
        printf("\t\t---------------------------------------------------------\n");
    }
    printf("\n\t\tPressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
}

void L_Produtos_F(P A[],int *qnt_p)
{
    int i=0,tam;
    tam = *qnt_p;

    printf("\n\n\t\t+---------------------------------------------------------+\n");
    printf("\t\t|                 LISTA DE PRODUTOS EM FALTA               |\n");
    printf("\t\t+---------------------------------------------------------+\n");

    for(; i<tam; i++)
    {
        if(A[i].qnt_E==0)
        {
            printf("\n\t\t| Código: %d | Nome: %s | Quantidade: %d | Preço: R$%.2f |\n", A[i].codigo, A[i].Nome, A[i].qnt_E, A[i].Pv);

        }
    }

    printf("\n\t\tPressione ENTER para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
}

void relatorio(V B[], int *b)
{
    int aux, qnt_v = *b;

    while (1)
    {
        printf("\n\n\n\t\t\t+---------------------------------------------------------------------+\n");
        printf("\t\t\t|                         MENU  DE RELATÓRIOS                         |\n");
        printf("\t\t\t+---------------------------------------------------------------------+\n");
        printf("\t\t\t|   #1 -> Produto mais vendido                                        |\n");
        printf("\t\t\t|   #2 -> Total de vendas por produto                                 |\n");
        printf("\t\t\t|   #3 -> Valor total obtido                                          |\n");
        printf("\t\t\t|   #4 -> Sair                                                        |\n");
        printf("\t\t\t+---------------------------------------------------------------------+\n");

        do
        {
            printf("\n\t\t\tDigite o código do relatório: ");
            scanf("%d", &aux);
            if (aux < 1 || aux > 4)
                printf("\t\t\tCódigo inválido! Digite um número de 1 a 4.\n");
        }
        while (aux < 1 || aux > 4);

        system("cls");


        switch (aux)
        {
        case 1:
        {
            int maisVendidoQtd = 0;
            int codigoMaisVendido = 0;
            int qtdTotal;

            for (int i = 0; i < qnt_v; i++)
            {
                qtdTotal = 0;
                for (int j = 0; j < qnt_v; j++)
                {
                    if (B[i].p_Ve.codigo == B[j].p_Ve.codigo)
                    {
                        qtdTotal += (int)(B[j].Vt / B[j].p_Ve.Pv);
                    }
                }

                if (qtdTotal > maisVendidoQtd)
                {
                    maisVendidoQtd = qtdTotal;
                    codigoMaisVendido = B[i].p_Ve.codigo;
                }
            }

            printf("\n\t\t+---------------------------------------------------------------------+\n");
            printf("\t\t|                       PRODUTO MAIS VENDIDO                          |\n");
            printf("\t\t+---------------------------------------------------------------------+\n");
            printf("\t\t| Código do Produto: %-10d Quantidade Total Vendida: %-5d       \n", codigoMaisVendido, maisVendidoQtd);
            printf("\t\t| Códigos das Vendas:                                                 \n");

            for (int i = 0; i < qnt_v; i++)
            {
                if (B[i].p_Ve.codigo == codigoMaisVendido)
                {
                    printf("\t\t| -> Venda #%03d | Quantidade: %.0f\n", B[i].codigo_V, B[i].Vt / B[i].p_Ve.Pv);
                }
            }
            printf("\t\t+---------------------------------------------------------------------+\n");
            printf("\t\tPressione ENTER para continuar...            \n");
            fflush(stdin);
            getchar();
            system("cls");
            break;
        }

        case 2:
        {
            int ja_listado = 0;
            int total_vendido = 0;
            printf("\n\t\t+---------------------------------------------------------------------+\n");
            printf("\t\t|                    TOTAL DE VENDAS POR PRODUTO                      |\n");
            printf("\t\t+---------------------------------------------------------------------+\n");

            for (int i = 0; i < qnt_v; i++)
            {
                ja_listado = 0;

                for (int j = 0; j < i; j++)
                {
                    if (B[i].p_Ve.codigo == B[j].p_Ve.codigo)
                    {
                        ja_listado = 1;
                        break;
                    }
                }

                if (!ja_listado)
                {
                    printf("\t\t| Nome do Produto: %-30s Código: %-5d          \n", B[i].p_Ve.Nome, B[i].p_Ve.codigo);
                    total_vendido = 0;
                    for (int j = 0; j < qnt_v; j++)
                    {
                        if (B[j].p_Ve.codigo == B[i].p_Ve.codigo)
                        {
                            total_vendido += (int)(B[j].Vt / B[j].p_Ve.Pv);
                        }
                    }
                    printf("\t\t| Total Vendido: %-5d unidades                                   \n", total_vendido);

                    printf("\t\t| Vendas realizadas:                                             \n");

                    for (int k = 0; k < qnt_v; k++)
                    {
                        if (B[k].p_Ve.codigo == B[i].p_Ve.codigo)
                        {
                            printf("\t\t| -> Código da Venda: %-5d  Quantidade: %.0f                  \n",
                                   B[k].codigo_V, B[k].Vt / B[k].p_Ve.Pv);
                        }
                    }

                    printf("\t\t+---------------------------------------------------------------------+\n");
                }
            }

            printf("\t\tPressione ENTER para continuar...\n");
            fflush(stdin);
            getchar();
            system("cls");
            break;
        }


        case 3:
        {
            float total = 0;
            printf("\n\t\t+---------------------------------------------------------------------+\n");
            printf("\t\t|                    VALOR TOTAL OBTIDO COM VENDAS                    |\n");
            printf("\t\t+---------------------------------------------------------------------+\n");

            for (int i = 0; i < qnt_v; i++)
            {
                printf("\t\t| Venda #%03d | Produto Código: %d  Nome: %-20s \n",
                       B[i].codigo_V, B[i].p_Ve.codigo, B[i].p_Ve.Nome);
                printf("\t\t| Quantidade: %.0f | Preço Unitário: R$%.2f | Valor Venda: R$%.2f   \n",
                       B[i].Vt / B[i].p_Ve.Pv, B[i].p_Ve.Pv, B[i].Vt);
                printf("\t\t+---------------------------------------------------------------------+\n");

                total += B[i].Vt;
            }

            printf("\t\t| Valor Total Acumulado: R$%.2f                                      \n", total);
            printf("\t\t+---------------------------------------------------------------------+\n");
            printf("\t\tPressione ENTER para continuar...\n");
            fflush(stdin);
            getchar();
            system("cls");
            break;
        }
        case 4:
        {
            return;
        }
        }


    }
}



int main()
{
    int rod=1,aux,qnt_p=0,qnt_v=0;
    P prod[50];
    V vend[1000];
    setlocale(LC_ALL, "Portuguese");

    printf("\n\n\n\n\n\n\n\t\t\t\t+-------------------------------------------------------+\n");
    printf("\t\t\t\t|                                                       |\n");
    printf("\t\t\t\t|          BEM-VINDO AO SISTEMA DE ESTOQUE E VENDAS     |\n");
    printf("\t\t\t\t|                                                       |\n");
    printf("\t\t\t\t|                                                       |\n");
    printf("\t\t\t\t|                                                       |\n");
    printf("\t\t\t\t|          Pressione ENTER para continuar...            |\n");
    printf("\t\t\t\t|                                                       |\n");
    printf("\t\t\t\t+-------------------------------------------------------+\n");
    getchar();
    system("cls");

    while(rod==1)
    {
        printf("\n\n\n\n\n\n\n\t\t\t+---------------------------------------------------------------------+\n");
        printf("\t\t\t|                         MENU PRINCIPAL                              |\n");
        printf("\t\t\t+---------------------------------------------------------------------+\n");
        printf("\t\t\t|                                                                     |\n");
        printf("\t\t\t|   #1 -> Cadastrar um Produto                                        |\n");
        printf("\t\t\t|   #2 -> Registrar uma Venda                                         |\n");
        printf("\t\t\t|   #3 -> Listar Produtos Disponíveis                                 |\n");
        printf("\t\t\t|   #4 -> Listar Vendas                                               |\n");
        printf("\t\t\t|   #5 -> Listar Produtos em Falta                                    |\n");
        printf("\t\t\t|   #6 -> Gerar Relatórios                                            |\n");
        printf("\t\t\t|   #7 -> Sair                                                        |\n");
        printf("\t\t\t|                                                                     |\n");
        printf("\t\t\t+---------------------------------------------------------------------+\n");
        do
        {
            printf("\n\t\t\tDigite o código da função: ");
            scanf("%d", &aux);

            if (aux < 1 || aux > 7)
            {
                printf("\n\t\t\tCódigo inválido! Digite um número de 1 a 7:");
                scanf("%d", &aux);
            }
        }
        while (aux < 1 || aux > 7);

        switch (aux)
        {
        case 1:
            system("cls");
            Cadastro(prod,&qnt_p);
            break;

        case 2:
            system("cls");
            Registro(prod,vend,&qnt_p,&qnt_v);
            break;

        case 3:
            system("cls");
            L_Produtos_D(prod,&qnt_p);
            break;
        case 4:
            system("cls");
            L_Vendas(vend,&qnt_v);
            break;
        case 5:
            system("cls");
            L_Produtos_F(prod,&qnt_p);
            break;
        case 6:
            system("cls");
            relatorio(vend,&qnt_v);
            system("cls");
            break;
        case 7:
            return 0;
        }

    }
}
