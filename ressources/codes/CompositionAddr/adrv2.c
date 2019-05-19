#include "../../env_config/env_config.c"
#include <stdio.h>
#include <stdlib.h>

struct adrv_t
 {  unsigned long pagenum;
    unsigned long offset; 
 };

int main (int argc, char*argv[])
{
  bootEnvVars(&argc, &argv);
  printf("argc=   %d\n", argc);
  printf("argv1:::: %s\n", argv[1]);
  if(argc!=3)
  { printf("Deux parametres sont recquis: adresse virtuelle (en decimal)  et taille d'une page (en decimal) \n");
    return 1;
  }
  struct adrv_t* adv = (struct adrv_t*) malloc(sizeof(struct adrv_t));

  unsigned long adrvDecimal=strtoul(argv[1], NULL, 0);
  unsigned long pagesizeDecimal =strtoul(argv[2], NULL, 0);
  
  adv->pagenum = adrvDecimal / pagesizeDecimal;
  adv->offset = adrvDecimal % pagesizeDecimal;
  printf("adrv(decimal)=%lu, adrv(hex)=%lX, pagenum(decimal)=%lu, offset(decimal)=%lu \n",adrvDecimal,adrvDecimal,adv->pagenum, adv->offset);
 return 0;
}

