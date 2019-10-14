#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting */
	if(argc!=3) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}

   /* declarations */
   int i, scrsz=atoi(argv[1]), nl=atoi(argv[2]), midvert=scrsz/2;
   int *vposarr=calloc(nl, sizeof(int));
   for(i=0;i<nl;++i) {
       vposarr[i] = midvert - (int)( ((float)nl + 0.5)/2 ) + i; 
       printf("%i\n", vposarr[i]); 
   }

    free(vposarr);
   return 0;
}
