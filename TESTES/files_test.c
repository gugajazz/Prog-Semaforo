/* #include<stdio.h>
struct address
{
 int tab[2][2];
};

int main()
{
    FILE *p;
    struct address x;
    int tab[2][2]= {{1,2},{3,4}};
    p=fopen("address","wb");

    fwrite(&x,sizeof(x),1,p);

    fclose(p);
    printf("1 file created");
    return 0;
}  */


#include<stdio.h>
struct address
{
 int tab[2][2];
};

int main()
{
 FILE *p;
 struct address x;
 p=fopen("address","rb");
 printf("Rcords of file:\n");
 while(1)
 {
  fread(&x,sizeof(x),1,p);
  if(feof(p)!=0)
    break;
  printf("%d",x.tab[1][2]);
 }
 fclose(p);
 return 0;
}