#include "bibliotecas.h"
//gcc main.c lista.c -o main.exe

void menu(){
    int op, controle = 0;
    Conta conta;
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    criar_lista(lista);

    ler_contas(lista);

    do
    {
        limpar_tela();
        printf("\t\n**********************************\n");
        printf("\t\t\nBANCO ONE\n");
        printf("\t\n**********************************\n");

        printf("\n0 - Sair\n1 - Login\n2 - Cadastrar\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
            case 1:
                controle = login(lista, cadatrar_cliente());
                if(controle == 1){
                    printf("\nCPF invalido\n");
                } else{
                    printf("\nSenha invalida\n");
                    controle = 1;
                }
            break;

            case 2: 
                conta = cadatrar_cliente();
                controle = verificar_cpf(conta, lista);
                
                if(controle)
                    printf("\n***ERRO CPF ja existe***\n");
                else{
                    printf("\nConta criada com sucesso\n");
                    inserir_lista(lista, conta);
                    salvar_conta(lista); 
                }
            break;
            case 3: adm(lista);
             break;

            default: if(op!=0) printf("\nOpção Inválida\n");
                    //  else salvar_conta(conta, lista);
            break;
        }
    } while (op != 0);
}
Conta cadatrar_cliente(){
    Conta conta;

    printf("\nInforme seu NOME\n");
    scanf("%29[^\n]", conta.nome);
    getchar();

    printf("\nInforme seu CPF\n");
    scanf("%29[^\n]", conta.cpf);
    getchar();

    //posso verificar aqui já

    printf("\nInforme sua SENHA\n");
    scanf("%29[^\n]", conta.senha);
    getchar();

    conta.saldo = rand() % 50000;

    //Tenho que verificar se já existe esse cpf nom meu arquivo
    
    return conta;
}
int login(Lista *lista, Conta conta){
    No *aux = lista->inicio;
    int controle;

    if(!aux) return 1; // não há conta cadastrada
    else{
        while(aux && strcmp(aux->conta.cpf, conta.cpf) != 0)
            aux = aux->prox;
      
        if(aux){
            if(strcmp(aux->conta.senha, conta.senha) == 0){
                printf("\nLogin feito com sucesso\n");
                painel(aux, lista);
            }
            else return 0; // cpf valido senha não valida
        }else
            return 1; 
    }
}
void imprimir_cliente(Conta conta){
    printf("\n-------------------\n");
    printf("Nome: %s\n", conta.nome);
    printf("CPF: %s\n", conta.cpf);
    printf("Senha: %s\n", conta.senha);
    printf("Saldo: R$ %.2f\n", conta.saldo);
    printf("\n-------------------\n");
}
int verificar_cpf(Conta conta, Lista *lista){
    No *aux= lista->inicio;
    int controle = 1;
    if(!aux){
        controle = 0;
    } else {
        while(aux && strcmp(aux->conta.cpf , conta.cpf) != 0)
            aux = aux->prox;
        
        if(aux == NULL)  controle = 0;
    }
    return controle;
}
void saldo(No *c){
    limpar_tela();
    printf("\n*****************\n");
    printf("\nNome: %s\n", c->conta.nome);
    printf("\nSaldo: R$ %.2f\n", c->conta.saldo);
    printf("\n*****************\n");
}
void painel(No *conta, Lista *lista){
    limpar_tela();
    printf("\t\n**********************************\n");
    printf("\t\t\nBANCO ONE  -> PAINEL\n");
    printf("\t\n**********************************\n");

    int op;

    do{
        printf("\n0 - sair\n1 - Saldo\n2 - Transferir\n3 - Deposito\n4 - Saque\n5 - historico de transfercia\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1: saldo(conta);
            break;
        case 2: transferencia(lista, conta);
            break;
        case 3: deposito(conta);
            break;
        case 4: saque(conta);
            break;
        case 5: 
            break;
        default: if(op!=0) printf("\nOpção inválida\n");
            else salvar_conta(lista); 
            break;
        }

    }while(op!=0);
    
}
void criar_lista(Lista *lista){
    lista->inicio = NULL;
}
bool inserir_lista(Lista *lista, Conta conta){
    No *novo = (No*) malloc(sizeof(No)), *aux;
    if(!novo){
        printf("\nErro ao alocar um no\n");
        return false;
    } else {
        novo->prox = NULL;
        novo->conta = conta;

        if(lista->inicio == NULL)
            lista->inicio = novo;
        else {
          aux = lista->inicio;
            while (aux->prox)
                aux = aux->prox;
            aux->prox = novo;
        }
        return true;
    }
}
void salvar_conta(Lista *lista){
    FILE *file = fopen("contas.bin","wb");
    No *aux = lista->inicio;

    if(!aux) printf("\nLISTA VAZIA\n");
    if(file){

        while(aux){
            fwrite(&aux->conta, sizeof(Conta),1, file);
            aux = aux->prox;
        }
    }     
    fclose(file);
}
void ler_contas(Lista *lista){
    FILE *file = fopen("contas.bin","rb");
    No *aux = malloc(sizeof(No));
    if(file){
        while(fread(&aux->conta, sizeof(Conta),1, file)){
               inserir_lista(lista, aux->conta);
        }
    }
    fclose(file);
}
void adm(Lista *lista){
    printf("\t\n**********************************\n");
    printf("\t\t\nAREA ADM\n");
    printf("\t\n**********************************\n");

    int op;
    do
    {
        printf("\n0 - sair\n1 - Mostra todos os users\n");
        scanf("%d", &op);
        getchar();
        
        switch (op)
        {
        case 1: imprimir_lista(lista);
            break;
        case 2:
            break;
        case 3:
            break;
        
        default: if(op!=0) printf("\nOpcao Invalida");
            break;
        }
    } while (op!=0);
}
void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;
    if(!aux){
        printf("\nSem usuarios\n");
        return;
    } else {
        while(aux){
            imprimir_cliente(aux->conta);
            aux = aux->prox;
        }
    }
}
void deposito(No *c){
    limpar_tela();
    printf("\t\n**********************************\n");
    printf("\t\t\nBANCO ONE -> DEPOSITO\n");
    printf("\t\n**********************************\n");

    int deposito;
    printf("Informe o valor a ser depositado: ");
    scanf("%f", &deposito);
    getchar();

    c->conta.saldo = c->conta.saldo + deposito;
    printf("\nSaldo depositado com sucesso\n");
}

void saque(No *c){
    limpar_tela();
    printf("\t\n**********************************\n");
    printf("\t\t\nBANCO ONE -> SAQUE\n");
    printf("\t\n**********************************\n");
    float value;

    printf("\nInforme o valor a ser retirado\n");
    scanf("%f", &value);
    getchar();

    //Verifircar se o saldo a ser retirado é maior que o que está na conta
    if(value > c->conta.saldo){
        printf("\nSaldo insuficiente\n");
    } else {
        c->conta.saldo = c->conta.saldo - value;
        printf("\nSaldo retirado com sucesso\n");
    }
}

void transferencia(Lista *lista, No *c){
    float valor;
    char cpf[30], op;
    No *aux = lista->inicio;
    Conta conta;
    printf("\t\n**********************************\n");
    printf("\t\t\nBANCO ONE -> TRANSFERENCIA\n");
    printf("\t\n**********************************\n");

    saldo(c);
    printf("Informe o valor: ");
    scanf("%f", &valor);
    getchar();

    if(c->conta.saldo < valor){
        printf("\nSaldo insuficiente");
        painel(c, lista);
    }else{
        printf("\nInforme o cpf para quem voce vai enviar: ");
        scanf("%29[^\n]", conta.cpf);
        getchar();
        

        while(aux && strcmp(aux->conta.cpf , conta.cpf) != 0)
            aux = aux->prox;

        if(aux){
            printf("\n***Usuario encontrado***\n");
            printf("Nome: %s\n", aux->conta.nome);
            printf("Cpf : %s\n", aux->conta.cpf);
            printf("\nDeseja enviar R$ %.2f para %s?\n(s- sim) ou (n - nao)\n", valor, aux->conta.nome);
            scanf("%c", &op);
            getchar();

            if(op == 's'){
               c->conta.saldo = c->conta.saldo - valor;
               aux->conta.saldo =  aux->conta.saldo + valor;
                printf("\nTransferenci feita com sucesso\n");
            }else if(op == 'n'){
                printf("\nOk, trnaferencia cancelada\n");
                painel(c, lista);
            }else{
                printf("\nOpcao invalida\n");
            }
           

        } else {
            printf("\nCPF nao exite em nosso sistema\n");
            painel(c, lista);
        }
    }

}
void limpar_tela(){
    Sleep(1500);
    system("cls");
}