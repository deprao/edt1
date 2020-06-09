typedef struct{
    double r,x,y;
    char cb[20], cp[20];
}circ;

typedef struct{
    double h,w,x,y;
    char cb[20], cp[20];
}rect;

typedef struct{
    double x,y;
    char cb[20], cp[20], txt[40];
}text;

typedef struct{
    double x1,y1,x2,y2;
    char *cor;
}line;

typedef union{
    circ c;
    rect r;
    text t;
    line l;
}fig;

typedef struct node {
    fig *figure;
    int i;
    char figtype;
    struct node *next;
}node;
