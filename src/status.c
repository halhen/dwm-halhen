/* Functions to keep the dwm status bar updated within dwm itself.
   status_complete is called when it is time to update the status bar.

   To configure: edit status_complete to your liking. Then configure
   status_nextupdatein to set how often the status bar should update.

   Compile with -DASTEST to enable testing. main() is then included
   and will create an executable that prints a couple of 
   dummy status lines, which is useful for testing.*/

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

    static int
strlcat(char *dest, const char *src, int maxlength)
{
    strncat(dest, src, maxlength - strlen(dest));
    return strlen(dest);
}

static int
readint(const char *filename) {
    int result = -1;
    FILE* fp = fopen(filename, "r");

    if (fp) {
        fscanf(fp, "%d", &result);
        fclose(fp);
    }
    return result;
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

static void
status_appendbattery(char *stext, const char *separator, int maxlen)
{
    char battxt[5];
    battxt[0] = '\0';

    FILE *fp = fopen("/sys/class/power_supply/BAT0/status", "r");
    if (fp) {
        int status = fgetc(fp);
        fclose(fp);

        switch (status) {
            case 'F': /* Full */
                strcpy(battxt, "100%");
                break;
            case 'C': /* Charging */
            case 'D': /* Discharging */
                {
                    int now = readint("/sys/class/power_supply/BAT0/energy_now");
                    int full = readint("/sys/class/power_supply/BAT0/energy_full");

                    if (now > 0 && full > 0)
                        sprintf(battxt, "%c%d%%", status == 'C' ? '+' : '-', (now-1)/((full)/100));
                }
                break;
        }
    }

    if (battxt[0] != '\0') {
        if (stext[0] != '\0')
            strlcat(stext, separator, maxlen);
        strlcat(stext, battxt, maxlen);
    }
}

static void
status_appendtemperature(char *stext, const char *separator, int maxlen)
{
    char tempstr[5];
    int temp = readint("/sys/class/thermal/thermal_zone0/temp");

    if (temp > 0) {
        if (stext[0] != '\0')
            strlcat(stext, separator, maxlen);
        sprintf(tempstr, "%dC", temp / 1000);
        strlcat(stext, tempstr, temp);
    }
}

static void
status_appendmailcount(char *stext, const char *separator, int maxlen)
{
    char mailstr[20];
    int numfiles = -2; /* Don't count .. and . */
    DIR *dir = opendir("/home/henrik/.mail/INBOX/new");

    if (dir) {
        while(readdir(dir))
            numfiles += 1;
        closedir(dir);

        if (numfiles > 0) 
            sprintf(mailstr, "%d new mail", numfiles);
        if (numfiles > 1)
            strcat(mailstr, "s");	

        if (numfiles > 0) {
            if (stext[0] != '\0')
                strlcat(stext, separator, maxlen);
            strlcat(stext, mailstr, maxlen);
        }
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
    status_appendmailcount(stext, separator, maxlen);
    status_appendtemperature(stext, separator, maxlen);
    status_appendbattery(stext, separator, maxlen);
    status_appendtime(stext, "%R", separator, maxlen);
}

/* When should the status bar be updated next? This is called after an update,
   to allow updates at e.g. top of the minute.*/
static int
status_nextupdatein()
{
	/* Update at the top of the minute */
	time_t now = time(NULL);
	struct tm *tminfo = localtime(&now);

	return 60 - tminfo->tm_sec;
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
