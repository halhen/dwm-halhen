/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[] = "-*-terminus-*-*-*-*-12-*-*-*-*-*-iso8859-1";
static const char normbordercolor[] = "#222222";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#f2f2f2";
static const char selbordercolor[]  = "#afc81c";
static const char selbgcolor[]      = "#222222";
static const char selfgcolor[]      = "#fdb436";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 2;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	{ "Skype",    NULL,       NULL,      1 << 8,       True,  1  },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

/* Added source files */
#include "fibonacci.c"
#include "shiftview.c"
#include "status.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
    { "(@)",      spiral },  /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};


/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]           = {"dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]            = {"urxvt", "-e", "zsh", "-c", "tmux; zsh -i", NULL };
static const char *togglescreenscmd[]   = {"xtogglescreens", NULL};
static const char *raisevolcmd[]        = {"amixer", "-q", "set", "Master", "5%+", NULL};
static const char *lowervolcmd[]        = {"amixer", "-q", "set", "Master", "5%-", NULL};
static const char *mutevolcmd[]         = {"amixer", "-q", "set", "Master", "toggle", NULL};
static const char *mediatoggle[]        = {"mocp", "--play", NULL};
static const char *mediastop[]          = {"mocp", "--stop", NULL};
static const char *medianext[]          = {"mocp", "--next", NULL};
static const char *mediaprev[]          = {"mocp", "--previous", NULL};
static const char *monbrightnessup[]    = {"sudo", "/usr/local/sbin/backlight", "up", NULL};
static const char *monbrightnessdown[]  = {"sudo", "/usr/local/sbin/backlight", "down", NULL};
static const char *togglemouse[]        = {"xmouse", NULL};
static const char *browser[]            = {"firefox", NULL};
static const char *lockscreen[]         = {"slock", NULL};
static const char *wallpaper[]          = {"wallpaper", NULL};
static const char *menucmd[]            = {"mygtkmenu", "/home/henrik/.menu", NULL};

static Key keys[] = {
	/* modifier                     key                      function        argument */
    { 0,                            XF86XK_Display,          spawn,          {.v = togglescreenscmd } },
    { 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = raisevolcmd } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = lowervolcmd } },
	{ 0,                            XF86XK_AudioMute,        spawn,          {.v = mutevolcmd } },
    { 0,                            XF86XK_AudioPlay,        spawn,          {.v = mediatoggle } },
    { 0,                            XF86XK_AudioStop,        spawn,          {.v = mediastop } },
    { 0,                            XF86XK_AudioNext,        spawn,          {.v = medianext } },
    { 0,                            XF86XK_AudioPrev,        spawn,          {.v = mediaprev } },
    { 0,                            XF86XK_MonBrightnessUp,  spawn,          {.v = monbrightnessup } },
    { 0,                            XF86XK_MonBrightnessDown,spawn,          {.v = monbrightnessdown } },
    { ALTKEY|ControlMask,           XK_Left,                 shiftview,      {.i = -1 } },
    { ALTKEY|ControlMask,           XK_Right,                shiftview,      {.i = 1 } },
	{ MODKEY,                       XK_a,                    spawn,          {.v = togglemouse} },
	{ MODKEY,                       XK_p,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,                    spawn,          {.v = browser } },
	{ MODKEY,                       XK_l,                    spawn,          {.v = lockscreen } },
	{ MODKEY,                       XK_w,                    spawn,          {.v = wallpaper } },
	{ MODKEY|ShiftMask,             XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,                    togglebar,      {0} },
	{ MODKEY,                       XK_Down,                 focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,                   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Left,                 focusstack,     {.i = -1} },
	{ MODKEY,                       XK_Right,                focusstack,     {.i = +1} },
	{ MODKEY,                       XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_minus,                setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_plus,                 setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,               zoom,           {0} },
	{ ALTKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY,                       XK_q,                    killclient,     {0} },
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ MODKEY|ALTKEY|ShiftMask,      XK_q,                    quit,           {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,               tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                    0)
	TAGKEYS(                        XK_2,                    1)
	TAGKEYS(                        XK_3,                    2)
	TAGKEYS(                        XK_4,                    3)
	TAGKEYS(                        XK_5,                    4)
	TAGKEYS(                        XK_6,                    5)
	TAGKEYS(                        XK_7,                    6)
	TAGKEYS(                        XK_8,                    7)
	TAGKEYS(                        XK_9,                    8)
};

/* button definitions */
/* click can be a tag number (starting at 0),
 * ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkRootWin,           0,              Button3,        spawn,          {.v = menucmd } },
};
