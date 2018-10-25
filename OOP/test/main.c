#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,level,tot;
    scanf("%d",&level);
    tot=1;
    for(i=level;i>1;i--)
    {
        tot=tot+i;
        //printf("%d %d \n",i,tot);
    }
    printf("%d\n",tot);
    return 0;
}
