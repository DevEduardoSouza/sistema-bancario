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
        printf("\n\tBANCO ONE\n");
        printf("\t\n**********************************\n");

        printf("\n0 - Sair\n1 - Login\n2 - Cadastrar\n3 - adm\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
            case 1:
                controle = login(lista, login_conta());
                if(controle)
                    printf("\nErro, cpf ou senha invalido\n");
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

    printf("\nInforme sua SENHA\n");
    scanf("%29[^\n]", conta.senha);
    getchar();

    conta.saldo = 0;

    return conta;
}
Conta login_conta(){
    Conta conta;

    printf("\nInforme seu CPF\n");
    scanf("%29[^\n]", conta.cpf);
    getchar();

    printf("\nInforme sua SENHA\n");
    scanf("%29[^\n]", conta.senha);
    getchar();
    return conta;
}


int login(Lista *lista, Conta conta){
    No *aux = lista->inicio;
    int controle;

    if(!aux) return 1; // não há conta cadastrada
    else{
        // Vou percorrer minha lista em busca da conta
        while(aux && strcmp(aux->conta.cpf, conta.cpf) != 0)
              aux = aux->prox;
              
        if(aux){
            if(strcmp(aux->conta.senha, conta.senha) == 0){
                printf("\nLogin feito com sucesso\n");
                painel(aux, lista);
            }else
                return 1;
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

    if(!aux) controle = 0;
    else {
        // Vou verificar se na lista já existe um cpf 
        while(aux && strcmp(aux->conta.cpf , conta.cpf) != 0)
            aux = aux->prox;
        
        if(aux == NULL) controle = 0;
    }
    return controle;
}

void saldo(No *c){
    printf("\n********Sua conta*********\n");
    printf("\nNome: %s\n", c->conta.nome);
    printf("\nSaldo: R$ %.2f\n", c->conta.saldo);
    printf("\n*****************\n");
}

void painel(No *conta, Lista *lista){
    limpar_tela();
    
    No *novo = malloc(sizeof(No));
    int op;
   
    do{
        limpar_tela();
        printf("\t\n**********************************\n");
        printf("\n\tBANCO ONE  -> PAINEL\n");
        printf("\t\n**********************************\n");

        printf("\n0 - sair\n1 - Saldo\n2 - Transferir\n3 - Deposito\n4 - Saque\n5 - editar informacoes\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1: limpar_tela();
                saldo(conta);
                system("pause");
            break;

        case 2: novo = transferencia(lista, conta);
            break;

        case 3: deposito(conta);
            break;

        case 4: saque(conta);
            break;

        case 5: editar_infos(conta, lista);
            break;

        default:if(op!=0) printf("\nOpção inválida\n");
                else{
                        salvar_conta(lista);  
                    }
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
    float total;
    do
    {
        printf("\n0 - sair\n1 - Mostra todos os users\n2 - Quantidade de dinheiro no banco\n");
        scanf("%d", &op);
        getchar();
        
        switch (op)
        {
        case 1: imprimir_lista(lista);
            break;
        case 2: total = qtd_dinheiro(lista);
                printf("\n*********************\n");
                printf("\nTotal de Dinheiro no banco\nR$ %.2f", total);
                printf("\n*********************\n");
            break;
        case 3: data_hora();
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
    saldo(c);

    float deposito;
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
    saldo(c);
    float value;

    printf("\nInforme o valor a ser retirado\n");
    scanf("%f", &value);
    getchar();

    //Verificar se o saldo a ser retirado é maior que o que está na conta
    if(value > c->conta.saldo){
        printf("\nSaldo insuficiente\n");
    } else {
        c->conta.saldo = c->conta.saldo - value;
        printf("\nSaldo retirado com sucesso\n");
    }
}

No* transferencia(Lista *lista, No *c){
    float valor;
    char cpf[30], op;
    No *aux = lista->inicio;
    Conta conta;

    limpar_tela();
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
                printf("\nTransferencia feita com sucesso\n");
            }else if(op == 'n'){
                printf("\nOk, transferencia cancelada\n");
                painel(c, lista);
            }else{
                printf("\nOpcao invalida\n");
            }
        } else {
            printf("\nCPF nao exite em nosso sistema\n");
            painel(c, lista);
        }
        return aux;
    }
}

void editar_infos(No *c, Lista *lista){
    printf("\t\n**********************************\n");
    printf("\n\tBANCO ONE  -> EDITAR INFORMACOES\n");
    printf("\t\n**********************************\n");
    int op;
    char newName[30], opt;

    printf("\n0 - sair\n1 - Editar nome\n2 - Excluir sua conta\n");
    scanf("%d", &op);
    getchar();

    switch (op)
    {
    case 1: 
        printf("\nInforme um novo nome\n");
        scanf("%29[^\n]", newName);
        getchar();
        strcpy(c->conta.nome, newName);

        if(strcmp(c->conta.nome, newName) == 0){
            printf("\nAlteracao feita com sucesso\n");
        } else  {
            printf("\nErro ao alterar o nome\n");
        }
        break;

    case 2: 
        printf("Tem certeza dessa decisao?\ns - sim\nn - nao\n");
        scanf("%c", &opt);
        getchar();

        if(opt == 's' || opt == 'S'){
            if(remover_conta(c, lista)){ 
                printf("\nConta removida com sucesso");
                exit(1);
            }
            else
                printf("\nErro ao remover sua conta\n");
        }else if(opt == 'n' || opt == 'N'){
               printf("\nOk, voltando para o menu");
        }else{
            printf("\nOpcao invalida\n");
        }
        break;

    default: if(op!=0)printf("\nOpcao invalida\n");
        break;
    }
}
bool remover_conta(No *c, Lista *lista){
    No*aux , *remover = malloc(sizeof(No));

    aux = lista->inicio;
    if(aux){
        if(strcmp(aux->conta.cpf, c->conta.cpf) == 0){
            remover = lista->inicio;
            lista->inicio = remover->prox;
        }else {
            while (aux->prox && strcmp(aux->prox->conta.cpf, c->conta.cpf) != 0)
                aux = aux->prox;

            if(aux){
                remover = aux->prox;
                aux->prox = remover->prox;
            } else
                return false;
        }
        free(remover);
        salvar_conta(lista);

        return true;
    }
}

float qtd_dinheiro(Lista *lista){
    No *aux = lista->inicio;
    float total = 0;

    while(aux){
        total += aux->conta.saldo;
        aux = aux->prox;
    }

    return total;
}
void data_hora(){
    time_t tempo;
    tempo = time(NULL);
    
    struct tm tm = *localtime(&tempo);
    printf("\n%d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("\n%d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    system("pause");
}

void limpar_tela(){
    Sleep(1000);
    system("cls");
}