typedef struct{
    double r,x,y;
    char cb[20], cp[20]; /* estrutura que representa um círculo*/
}circ;

typedef struct{
    double h,w,x,y;
    char cb[20], cp[20]; /* estrutura que representa um retângulo*/
}rect;

typedef struct{
    double x,y;
    char cb[20], cp[20], txt[40]; /* estrutura que representa um texto*/
}text;

typedef struct{
    double x1,y1,x2,y2;
    char cor[20]; /* estrutura que representa uma linha reta*/
}line;

typedef union{
    circ c;
    rect r;
    text t;
    line l; /* estrutura union que pode representar qualquer uma das figuras mencionadas acima*/
}fig;

typedef struct node {
    fig *figure;
    int i;
    char figtype;
    struct node *next; /* estrutura que representa o nó em uma alocação dinâmica, juntamente com os dados de uma figura, seu índice e uma letra que determina o tipo da figura*/
}node;