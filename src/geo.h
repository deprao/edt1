void svgen(char *out,node *list); /* cria um arquivo .svg, substituindo algum de mesmo nome*/
void drawc(double r, double x, double y, char *corp, char *corb,FILE *g); /* desenha um círculo em um arquivo .svg*/
void drawr(double w,double h, double x, double y, char *corp, char *corb,FILE *g); /* desenha um retângulo em um arquivo .svg*/
void wtext(double x, double y, char *corp, char *corb, char *txto,FILE *g); /* escreve um texto em um arquivo .svg*/
void drawl(double x1,double x2,double y1,double y2,char *corl,FILE *g); /* desenha uma linha em um arquivo .svg*/
void drawarrayr(double w,double h, double x, double y, char *corb, FILE *g); /* desenha um retângulo de borda tracejada em um arquivo .svg*/