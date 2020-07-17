node *makelist(); /* inicializa a lista dinâmica*/
node *addnode(node *list,char type,int index); /* adiciona um nó à lista*/
node *searchfig(node *list,int index); /* busca um elemento pertencente à lista, de acordo com seu índice*/
node *deletefig(node *list,int index); /* retira um elemento de índice index da lista, liberando a memória antes alocada para esse elemento*/
void deletelist(node *list); /* desaloca a memória da lista inteira*/
void circle(node *list,double x,double y,double r,char *cb,char *cp); /* adiciona um círculo a um nó da lista sem figura*/
void rectangle(node *list,double x,double y,double w,double h,char *cb,char *cp); /* adiciona um retângulo a um nó da lista sem figura*/
void texto(node *list,double x,double y,char *t,char *cb,char *cp); /* adiciona um texto a um nó da lista sem figura*/
void linha(node *list,double x1,double x2,double y1,double y2,char *c); /* adiciona uma linha a um nó da lista sem figura*/