node *makelist();
node *addnode(node *list,char type,int index);
node *searchfig(node *list,int index);
node *deletefig(node *list,int index);
void deletelist(node *list);
void circle(node *list,double x,double y,double r,char *cb,char *cp);
void rectangle(node *list,double x,double y,double w,double h,char *cb,char *cp);
void texto(node *list,double x,double y,char *t,char *cb,char *cp);
void linha(node *list,double x1,double x2,double y1,double y2,char *c);