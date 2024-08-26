
typedef struct cliente {
    int codigo;
    char nome[50];
    char empresa[50];
    char departamento[80];
    char telefone[50];
    char celular[50];
    char email[50];
} CLIENTE;

typedef struct elemento* Lista;
typedef struct elemento ELEM;

Lista* criaLista();
void abortaPrograma();
void liberaLista(Lista* li);
int insereOrdenado(Lista *li, CLIENTE cl);
int listaVazia(Lista *li);
void insereNovoContato(Lista *li);
void lerArquivo(Lista *li);
void gravaArquivo(Lista *li);
void relatorioGeral(Lista *li);
ELEM*consultaCodigo(Lista *li, int codigo);
void relatorioCodigo(Lista *li);
void relatorioNome(Lista *li);
void consultaNome(Lista *li, char *nome);
void editaContato(Lista *li);
void removerCodigo(Lista *li, int codigo);
void removeContato(Lista *li);



