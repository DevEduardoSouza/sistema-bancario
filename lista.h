// Usar uma pilha para salvar os historicos de tranferecia

typedef struct Histo
{
    char cpf_send[30], cpf_rcv[30], nome[30];
    float valor_send, valor_rcv;

}Histo;

typedef struct No2
{
    Histo h;
    struct No2 *prox;
}No2;

typedef struct Pilha{
    No2 *topo;
}Pilha;

// fim

typedef struct Conta
{
    char nome[30];
    char cpf[30];
    char senha[30];
    float saldo, lastTr;
}Conta;

typedef struct No
{
   Conta conta;
   struct No *prox;
}No;

typedef struct{
    No *inicio;
}Lista;




// ---------- Funções Principais---------
void menu();
Conta cadatrar_cliente();
Conta login_conta();
int verificar_cpf(Conta, Lista*);
void painel(No*, Lista*);
bool inserir_lista(Lista*,Conta);
void salvar_conta(Lista*);
void criar_lista(Lista*);
void ler_contas(Lista*);
int login(Lista*,Conta);
void imprimir_cliente(Conta);
void limpar_tela();
void saldo(No*);
No* transferencia(Lista*, No*);
void deposito(No*);
void saque(No *c);
void editar_infos(No *c, Lista *lista);
bool remover_conta(No *c, Lista *lista);
float qtd_dinheiro(Lista *lista);
void data_hora();

//----------- Funções Adm ----------
void adm(Lista*);
void imprimir_lista(Lista*);

// ------------- Funções Pilha----------------



