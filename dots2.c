/*
 * Author: Thomas E. Dickey <dickey@clark.net> 1999
 *
 * $Id: dots.c,v 1.17 2008/02/09 18:08:50 tom Exp $
 *
 * A simple demo of the terminfo interface.
 * Not so simple... some of the low -level functions are used (.e. tputs)
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

int main(int argc, char *argv[])
{
    CATCHALL2(onsig); /*  macro held in dotspriv.h v "2" for  */

    setupterm((char *) 0, 1, (int *) 0); /*odd, yes, but this is the way see man 3ncurses terminfo */
    FILE *debugf;
    debugf=fopen("dotdbg.txt", "rw");
    fprintf(debugf, "mxcol =%i\n", max_colors);
    fclose(debugf);

  cleanup();
    ExitProgram(EXIT_SUCCESS);
}

/*  QUESTIONS: arising from this program:
 *  wtf does napms do? That's not easy to find out. It's not covered in the HOWTO
 *  Also it's tricky to check th sources ... can't work out the shenanigans they are up to
 Here's the tputs defn: tputs(const char *str, int affcnt, int (*putc)(int));
 affcnt mne must be affect context or, the number of lines affected
 the *str must be terminof string a specil one ofr terminfo */
