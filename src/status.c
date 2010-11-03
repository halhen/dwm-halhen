/* Functions to keep the dwm status bar updated within dwm itself.
   status_complete is called when it is time to update the status bar.
   
   To configure: edit status_complete to your liking. 

   Compile with -DASTEST to enable testing. main() is then included
   and will create an executable that prints a couple of 
   dummy status lines, which is useful for testing.*/

#include <string.h>
#include <time.h>

static int
strlcat(char *dest, const char *src, int maxlength)
{
	strncat(dest, src, maxlength - strlen(dest));
	return strlen(dest);
}

static void
status_appendtime(char *stext, const char* format, const char *separator, int maxlen) {
	time_t now;
	struct tm *tminfo;
	char timestr[100];

	now = time(NULL);
	tminfo = localtime(&now);

	if (strftime(timestr, sizeof(timestr), format, tminfo)) {
		if (stext[0] != '\0')
			strlcat(stext, separator, maxlen);
		strlcat(stext, timestr, maxlen);
	}
}

/* Edit status_complete to configure what your status line should look like.
   stext contains what dwm traditionally puts on the status line, i.e. the X
   root window name. You should modify stext, which will in the end be printed
   on the status bar. If you for example append text to stext, it will show
   after the traditional status bar. */
static void
status_complete(char *stext, int maxlen)
{
    const char* separator = " | ";
    status_appendtime(stext, "%T", separator, maxlen);
}

#ifdef ASTEST

#include <stdio.h>

int main()
{
    char line[100];

    /* With regular status text */
    strcpy(line, "status text");
    status_complete(line, sizeof(line) - 1);
    printf("%s\n", line);

    /* With no status text */
    strcpy(line, "");
    status_complete(line, sizeof(line) - 1);
    printf("%s\n", line);

    /* With limited length, i.e. truncated */
    strcpy(line, "");
    status_complete(line, 6);
    printf("%s\n", line);

    return 0;
}
#endif
