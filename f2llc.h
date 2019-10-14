/* header file for conversion of a text file into an ll */
#ifndef _F2LLB_H
#define _F2LLB_H

#define MXFSZ (1<<24)

typedef unsigned int uint;
typedef unsigned char boole;

typedef struct linkty
{
    char *lstr;
    uint wn; /* word nmber, number of words that the line has */
    uint lsz; /* size of the name string */
    uint idx; /*  associated general purpose value */
    struct linkty *next; /* next in the list, null if it's the last */
} linkty;


/* for making an aray of linked lists */
typedef struct linktv
{
    linkty *lk;
    uint v; /* how many in this linked list */
} linktv;

/* Function protoypes */
uint fszfind(FILE *fp);
linkty *newlink(char *linstr, uint lsz, uint idx, uint wds);
linkty *addfront(linkty *listp, linkty *newp);
linkty *addend(linkty *listp, linkty *newp);
linkty *searchll(linkty *listp , char *linstr);
void applypf (linkty *listp, void (*fn)(linkty *, void*), void *arg);
void printlk(linkty *p, void *farg);
void freeall(linkty *listp);
linkty *dellink(linkty *listp, char *linstr);
linkty *flines2ll(FILE *, uint *);
uint findmxval(linkty *listp , char *vstr);

#endif
