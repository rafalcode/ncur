/* Takes one files lines, and converts them into a linked list */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define GENBUF 32

#include "f2ll.h"

linkty *newlink(char *linstr, uint lsz, uint idx) /* takes a string and integer and creates the first link in an ll from them */
{
    linkty *newp;
    newp = malloc(sizeof(linkty));

    newp->lsz = lsz;
    newp->lstr=calloc(newp->lsz, sizeof(char)); /* it will include \0 symbol */
    strcpy(newp->lstr, linstr);
    newp->idx = idx;
    newp->next = NULL;
    return newp;
}

linkty *addfront(linkty *listp, linkty *newp) /* add newp to front of listp */
{
    newp->next = listp;
    return newp;
}

linkty *addend(linkty *listp, linkty *newp) /* add newp to end of listp */
{
    linkty *p;

    /* first of all, take care of situ if l_list is totally empty */
    if (listp  == NULL)
        return newp;
    /* cycle through all elements which at least point to something */
    for (p=listp ; p->next != NULL; p = p->next) ;
    /* the forloop has brought us to the end of the ll, so ... */
    p->next = newp;
    return listp;
}

linkty *searchll(linkty *listp , char *linstr)
{
    for ( ; listp != NULL; listp = listp->next)
        if (strcmp(linstr, listp->lstr) == 0)
            return listp;
    return NULL;
}

linkty *searchidx(linkty *listp , uint id) /* return the link with a certain index */
{
    for ( ; listp != NULL; listp = listp->next)
        if (listp->idx == id)
            return listp;
    return NULL;
}

uint findmxval(linkty *listp , char *vstr)
{
    char *elnames[2]={"lsz", "whatevervalue"};
    uint i, casenum, mxv = 0;

    for(i=0;i<2;++i) 
        if((strcmp(elnames[i], vstr)) ==0) {
            casenum =i;
            break;
        }

    switch(casenum) {
        case 0:
            for ( ; listp != NULL; listp = listp->next)
                if (listp->lsz > mxv)
                    mxv = listp->lsz;
            break;

        default:
            printf("No such struct value\n"); 
            break;
    }
    return mxv;
}

void applypf (linkty *listp, void (*fn)(linkty *, void*) , void *arg)
{
    /* this func cycles through the loop */
    for ( ; listp != NULL; listp = listp->next)
        (*fn)(listp, arg); /* call the function */
}

void printlk(linkty *p, void *farg)
{
    char *fmt;
    fmt = (char *)farg;
    printf(fmt, p->idx, p->lstr, p->lsz);
}

void freeall(linkty *listp)
{
    linkty *next ;
    for ( ; listp != NULL; listp = next) {
        next = listp->next;
        free(listp->lstr);
        free(listp) ;
    }
}

linkty *dellink(linkty *listp, char *linstr)
{
    /* two ptrs defined, one is the looping index (p) and prev is its previous value in the loop,
     * the idea being that prev will connect to value of p->next, and so jump over (or delete) p */
    linkty *p, *prev; 
    prev = NULL;
    for(p = listp; p != NULL; p = p->next) {
        if(strcmp(linstr, p->lstr) == 0) { // ==0 => they're equal
            if(!prev) // == NULL, case where name is the first element.
                listp = p->next;
            else
                prev->next = p->next; // this is the jump over or deletion of currnet value of p
            free(p->lstr);
            free(p);
            return listp;
        }
        prev = p; // p will get pushed on in next loop, so itś time for its current value to be recorded into prev.
    }
    printf("dellink: %s not in list", linstr) ;
    return NULL;        /* can't get here */
}

linkty *flines2ll(char *fname, uint *numels) /* will render a file's lines into a linked list, will also record numels */
{
    FILE *fp=fopen(fname,"r");

    size_t gbuf = GENBUF;
    char *lines=calloc(gbuf, sizeof(char));

    char c;
    linkty *our_ll=NULL, *tmp_ll=NULL;

    uint lsz=0, k =0, l=0;
    while((c=fgetc(fp)) != EOF) {
        if(c!= '\n') {
            if(k==gbuf-1) {
                gbuf += GENBUF;
                lines=realloc(lines, sizeof(char)*gbuf);
            }
            lines[k++] = c;

        } else if (c == '\n') {
            if(k==0)
                continue; 

            lines[k]='\0';
            lsz=k+1;

            tmp_ll = newlink(lines, lsz, l);
            our_ll=addend(our_ll, tmp_ll);

            l++;
            k=0;
            lsz=0;
            gbuf=GENBUF;
            lines=realloc(lines, sizeof(char)*gbuf);
        }
    }

    fclose(fp);
    free(lines);
    return our_ll;
}

int main(int argc, char *argv[])
{
	if(argc!=2) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}

    uint nels=0;
    linkty *myll=flines2ll(argv[1], &nels);

    applypf(myll, printlk, "line number %u, sez %s of size %u\n");

//     linkty *relev=seachidx(myll, 0) not nec
    uint nt, ns;

    freeall(myll);

    return 0;
}
