/*
 * Author: Thomas E. Dickey <dickey@clark.net> 1999
 *
 * $Id: dots.c,v 1.17 2008/02/09 18:08:50 tom Exp $
 *
 * A simple demo of the terminfo interface.
 *
 * rf: got rid of the GCC_UNUSED macro-marker ... in the h file it's says it is nothing!
 */
#define USE_TINFO
#include <dotspriv.h>
#include <time.h>
#define valid(s) ((s != 0) && s != (char *)-1)

#define CATCHALL2(handler) { \
		int nsig; \
		for (nsig = SIGHUP; nsig < SIGTERM; ++nsig) \
		    if (nsig != SIGKILL) \
			signal(nsig, handler); \
	    }

/*  three global variables: the first oneis particularly important */
static bool interrupted = FALSE;
static long total_chars = 0;
static time_t started;

static int outc(TPUTS_ARG c)
{
    if (interrupted) {
        char tmp = c;
        write(STDOUT_FILENO, &tmp, 1);
    } else
        putc(c, stdout);

    return 0;
}

static bool outs(char *s)
{
    if (valid(s)) {
        tputs(s, 1, outc);
        return TRUE;
    }
    return FALSE;
}

static void cleanup(void)
{
    outs(exit_attribute_mode);
    if (!outs(orig_colors))
        outs(orig_pair);
    outs(clear_screen);
    outs(cursor_normal);

    printf("\n\n%ld total chars, rate %.2f/sec\n", total_chars, ((double) (total_chars) / (time((time_t *) 0) - started)));
}

static void onsig(int n)
{
    interrupted = TRUE;
}

static float ranf(void)
{
    long r = (rand() & 077777);
    return ((float) r / 32768.);
}

int main(int argc, char *argv[])
{
    int x, y, z, p;
    float r, c;

    CATCHALL2(onsig); /*  macro held in dotspriv.h v "2" for  */

    srand((unsigned) time(0));
    setupterm((char *) 0, 1, (int *) 0);
    outs(clear_screen);
    outs(cursor_invisible);
    if (max_colors > 1) {
        if (!valid(set_a_foreground)
                || !valid(set_a_background)
                || (!valid(orig_colors) && !valid(orig_pair)))
            max_colors = -1;
    }

    r = (float) (lines - 2);
    c = (float) (columns - 2);
    started = time((time_t *) 0);
/* attempts to work out where max_colors is coming from
 * printf("max colors= %i\n", max_colors);
 * NOpe, can't find it even tried vu gdb too, it was undefined. */

     while (!interrupted) {
         x = (int) (c * ranf()) + 1;
         y = (int) (r * ranf()) + 1;
         p = (ranf() > 0.9) ? '*' : ' ';
 
         tputs(tparm3(cursor_address, y, x), 1, outc);
         if (max_colors > 0) {
             z = (int) (ranf() * max_colors);
             if (ranf() > 0.01) {
                 /*  tputs last arg is ptr to the outc func defined above: the way the char is put on the screen */
                 tputs(tparm2(set_a_foreground, z), 1, outc);
             } else { /* in in a few cases will this occur: deals with an extremity */
                 tputs(tparm2(set_a_background, z), 1, outc);
                 napms(1);
             }
         } else if (valid(exit_attribute_mode) && valid(enter_reverse_mode)) {
             /* now max_colors is 0 or -1: deal by reversing mode  */
             if (ranf() <= 0.01) {
                 outs((ranf() > 0.6) ? enter_reverse_mode : exit_attribute_mode);
                 napms(1);
             }
         }
         outc(p);
         fflush(stdout);
         ++total_chars; /* overall counter */
     }
    cleanup();
    ExitProgram(EXIT_SUCCESS);
}

/*  QUESTIONS: arising from this program:
 *  wtf does napms do? That's not easy to find out. It's not covered in the HOWTO
 *  Also it's tricky to check th sources ... can't work out the shenanigans they are up to */
