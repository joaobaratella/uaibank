   #include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[100];
    int idade, id;
    double saldo;
} usuarios;

usuarios* info = NULL;
int idmax = 0, users = 0;

int outraacao(int opcao) {
    printf("\n  Deseja realizar outra a��o?\n");
    printf(" (1)-Voltar ao Menu.\n");
    printf(" (2)-Sair.\n");
    printf(" Op��o: ");
    scanf("%i", &opcao);
    system("cls");
    getchar();
    if (opcao == 1) {
        return 1;
    } else {
        printf("\n Saindo...\n");
        exit(1);
    }
}

void carregarsave(FILE *arq) {
    usuarios user;
    while (fscanf(arq, "%99s %d %lf %d\n", user.nome, &user.idade, &user.saldo, &user.id) == 4) {
        users++;
        info = (usuarios*)realloc(info, users * sizeof(usuarios));
        info[users - 1] = user;
        if (user.id > idmax) {
            idmax = user.id;
        }
    }
    fclose(arq);
}

void usuarioarray() {
    FILE *arq = fopen("arqq.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    for (int i = 0; i < users; i++) {
        fprintf(arq, "%s %d %.2lf %d\n", info[i].nome, info[i].idade, info[i].saldo, info[i].id);
    }

    fclose(arq);
}

void newuser() {
    usuarios user;

    printf("\n   --Criar um novo usuario--\n");
    printf("   Insira o nome do usuario: ");
    fgets(user.nome, sizeof(user.nome), stdin);
    size_t len = strlen(user.nome);
    if (len > 0 && user.nome[len - 1] == '\n') {
        user.nome[len - 1] = '\0';
    }
    else if(len>99){
        printf("\n Quantidade de caracteres excedidas, digite menos que 100 caracteres.\n\n ");
        return;
    }

    printf("   Idade do usu�rio: ");
    scanf("%i", &user.idade);
    getchar();
    if(user.idade<=0){
        printf("\n Idade inv�lida, tente novamente... \n\n");
        return;
    }

    printf("   Saldo atual do usu�rio: ");
    scanf("%lf", &user.saldo);
    getchar();
     if(user.saldo<0){
        printf("\n Saldo inv�lido, tente novamente... \n\n");
        return;
     }
    users++;
    idmax++;
    user.id = idmax;

    printf("  Usu�rio inserido com id %i!\n", user.id);
    info = (usuarios*)realloc(info, users * sizeof(usuarios));
    info[users - 1] = user;
}

void variosusers() {
    int qtde;
    printf("\n    --Criar v�rios usu�rios--\n");
    printf("  Digite a quantidade de us�rios que deseja inserir: ");
    scanf("%i", &qtde);
    getchar(); // Consumir o '\n' deixado pelo scanf

    if (qtde <= 0) {
        printf("  A quantidade de usu�rios deve ser maior que 0.\n");
        return;
    }

    for (int i = 0; i < qtde; i++) {
        usuarios user;
        printf("\n  Usu�rio %i\n", i + 1);

        printf("  Insira o nome do usu�rio: ");
        fgets(user.nome, sizeof(user.nome), stdin);
        size_t len = strlen(user.nome);
        if (len > 0 && user.nome[len - 1] == '\n') {
            user.nome[len - 1] = '\0';
        }
        else if(len>99){
        printf("\n Quantidade de caracteres excedidas, digite menos que 100 caracteres.\n\n ");
        return;
    }

        printf("  Idade do usu�rio: ");
        scanf("%i", &user.idade);
        getchar();
         if(user.idade<=0){
        printf("\n Idade inv�lida, tente novamente... \n\n");
        return;
    }
        printf("  Saldo atual do usu�rio: ");
        scanf("%lf", &user.saldo);
        getchar();
        if(user.saldo<0){
        printf("\n Saldo inv�lido, tente novamente... \n\n");
        return;
     }

        users++;
        idmax++;
        user.id = idmax;
        info = (usuarios*)realloc(info, users * sizeof(usuarios));
        info[users - 1] = user;

        printf("  Usu�rio inserido com id %i!\n", user.id);
    }
}




void buscarid() {
    int idcheck;
    printf("\n    --Buscar usu�rio por id--\n");
    printf("\n   Digite o id: ");
    scanf("%i", &idcheck);
    getchar(); // Consumir o '\n' deixado pelo scanf

    if (idcheck <= 0 || idcheck > idmax) {
        printf("  Id inexistente!\n");
        return;
    }

    for (int i = 0; i < users; i++) {
        if (idcheck == info[i].id) {
            printf("\n  O usu�rio %s tem %.2lf de saldo.\n", info[i].nome, info[i].saldo);
            return;
        }
    }

    printf("  Id n�o encontrado!\n");
}





void tranfer() {
    int idorigem, iddestino;
    double quantia;

    printf("\n   --Fazer transfer�ncia--\n");
    printf(" Digite o id do usu�rio de origem: ");
    scanf("%d", &idorigem);
    getchar();

    if (idorigem <= 0 || idorigem > idmax) {
        printf("\n Id inv�lido.\n");
        return;
    }

    int idxOrigem = -1;
    for (int i = 0; i < users; i++) {
        if (info[i].id == idorigem) {
            idxOrigem = i;
            break;
        }
    }

    if (idxOrigem == -1) {
        printf("\n Usu�rio de origem n�o encontrado.\n");
        return;
    }

    printf("\n Digite o id do usu�rio de destino: ");
    scanf("%d", &iddestino);
    getchar();

    if (iddestino <= 0 || iddestino > idmax) {
        printf("\n Id inv�lido.\n");
        return;
    }

    int idxDestino = -1;
    for (int i = 0; i < users; i++) {
        if (info[i].id == iddestino) {
            idxDestino = i;
            break;
        }
    }

    if (idxDestino == -1) {
        printf("\n Usu�rio de destino n�o encontrado.\n");
        return;
    }

    printf("\n Digite a quantia da transfer�ncia: ");
    scanf("%lf", &quantia);
    getchar();

    if (quantia <= 0 || quantia > info[idxOrigem].saldo) {
        printf("\n N�o foi poss�vel realizar a transfer�ncia.\n");
        return;
    }

    info[idxOrigem].saldo -= quantia;
    info[idxDestino].saldo += quantia;
    printf("\n Transfer�ncia realizada com sucesso!\n");
}



void deleteid(){
       usuarios user;
       int rpst, certo;

       fflush(stdin);
       printf("\n   --Excluir usu�rio por id--");
       printf("\n Digite o id que deseja excluir: ");
       scanf("%d", &rpst);
       fflush(stdin);
       if(rpst>=1){
        for(int i=0; i < users; i++){
        if(info[i].id == rpst){
            certo = i;
            for(int j=certo; j<users; j++){
                info[j] = info[j+1];
                break;
            }
        }
       }

       }
       else{
        printf("\n\n  Nunhum usu�rio encontrado, digite um id maior que 0.\n\n");
        return;
       }
       users--;
       info = (usuarios*)realloc(info, users * sizeof(usuarios));
       printf("\n Usu�rio exclu�do!\n\n");
}

void principal() {
    printf(" Digite a opcao que deseja realizar:\n");
    printf(" (1)-Cadastrar um novo usuario.\n");
    printf(" (2)-Cadastrar varios novos usuarios.\n");
    printf(" (3)-Buscar usuario por id.\n");
    printf(" (4)-Fazer tranferencia.\n");
    printf(" (5)-Excluir usuario por id.\n");
    printf(" (6)-Sair.\n\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    FILE *arq = fopen("arqq.txt", "r+");
    if (arq == NULL) {
        printf("Erro ao carregar o arquivo.\n");
        return 1;
    }
    carregarsave(arq);

    printf("     ::::::UaiBank::::::\n    --Seja Bem-Vindo(a)--\n\n");
    principal();
    int opcao;

    while (1) {
        printf(" Op��o: ");
        scanf("%i", &opcao);
        getchar(); // Consumir o '\n' deixado pelo scanf
         system("cls");
        switch (opcao) {
            case 1:
                newuser();
                usuarioarray();
                break;
            case 2:
                variosusers();
                usuarioarray();
                break;
            case 3:
                buscarid();
                usuarioarray();
                break;
            case 4:
                tranfer();
                usuarioarray();
                break;
            case 5:
                deleteid();
                usuarioarray();
                break;
            case 6:
                printf("\n Saindo...\n\n");
                exit(1);

                break;
            default:
                printf("\n  Op��o inv�lida.\n\n");
                break;
        }

        if (outraacao(opcao) != 1) {
            break;
        }

        printf("     ::::::UaiBank::::::\n    --Seja Bem-Vindo(a)--\n\n");
        principal();
    }

    free(info);
    return 0;
}
