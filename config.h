/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "brave-browser-nightly"

/* appearance */
#include <X11/X.h>
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]                = { "monospace:size=10", "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true"  };
static char *colors[][3] = {
        /*               fg         bg         border   */
        [SchemeNorm] = { "#bbbbbb", "#222222", "#000000" },
        [SchemeSel]  = { "#eeeeee", "#005577", "#770000"  },
        [SchemeHid]  = { "#770000", "#222222", "#770000"  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
	{ "Tor Browser",     NULL,       NULL,       0,            1,           1,           -1 },
	{ "brave",     NULL,       NULL,       0,            1,           1,           -1 },
	// { "Nsxiv",     NULL,       NULL,       0,            1,           -1 },
	// { "Blueman-manager",     NULL,       NULL,       0,            1,           -1 },
	// { "Wpa_gui",     NULL,       NULL,       0,            1,           -1 },
	// { "mpv",     NULL,       NULL,       0,            1,           -1 },
	// { "stacer",     NULL,       NULL,       0,            1,           -1 },
	// { "pop-up",     NULL,       NULL,       0,            1,           -1 },
	// { "Gpick",     NULL,       NULL,       0,            1,           -1 },
	// { "pavucontrol",     NULL,       NULL,       0,            1,           -1 },
	// { "chatterino",     "chatterino",       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },
	// { "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	// { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	// { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	// { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	// { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	// { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	// { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	// { MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", selbgcolor, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "shiftview.c"

static const Key keys[] = {
    /* modifier                     key              function        argument */
    // STACKKEYS(MODKEY,                             focus)
    STACKKEYS(MODKEY|ShiftMask,                      push)
	{ MODKEY,                       XK_j,            focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_Tab,          focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,            focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Tab,          focusstackvis,  {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_j,            focusstackhid,  {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_k,            focusstackhid,  {.i = -1 } },
	// { MODKEY,                       XK_s,            show,           {0} },
	// { MODKEY|ShiftMask,             XK_s,            showall,        {0} },
	// { MODKEY,                       XK_h,            hide,           {0} },
    { MODKEY,                       XK_h,            setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_d,            spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,		        XK_d,	         spawn,		     SHCMD("keepmenu") },
    { MODKEY,                       XK_Return,       spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_Return,       togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_b,            togglebar,      {0} },
    { MODKEY,                       XK_q,            killclient,     {0} },
    { MODKEY,                       XK_f,            togglefullscr,  {0} },
    { MODKEY,                       XK_space,        setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,        togglefloating, {0} },
    { MODKEY,		                XK_m,	         spawn,		     SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; kill -10 $(pidof dwmblocks)") },
    { MODKEY,			            XK_minus,	     spawn,		     SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; kill -10 $(pidof dwmblocks)") },
    { MODKEY,			            XK_equal,	     spawn,		     SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; kill -10 $(pidof dwmblocks)") },
    { MODKEY,		                XK_comma,	     shiftview,      { .i = -1 } },
    { MODKEY,			            XK_period,	     shiftview,      { .i = 1 } },
    { MODKEY,			            XK_BackSpace,    spawn,	         SHCMD("dmenusys") },
    { MODKEY|ShiftMask,			    XK_BackSpace,    spawn,	         SHCMD("rebuild dwm") },
    { MODKEY,			            XK_grave,	     spawn,		     SHCMD("dunstctl close") },
    { MODKEY|ShiftMask,			    XK_b,	         spawn,		     SHCMD("dmenubluetooth") },
    { 0,			                XK_Print,	     spawn,		     SHCMD("dmenumaim") },
	{ MODKEY,			            XK_w,		     spawn,		     {.v = (const char*[]){ BROWSER, NULL } } },
    { MODKEY,			            XK_c,	         spawn,		     SHCMD("chromium") },
    { MODKEY|ShiftMask,			    XK_f,	         spawn,		     SHCMD("ferdium") },
    { MODKEY|ShiftMask,			    XK_s,	         spawn,		     SHCMD("signal-desktop") },
    { MODKEY,			            XK_n,	         spawn,		     SHCMD("obsidian") },
    { MODKEY,			            XK_p,			 spawn,		     {.v = (const char*[]){ "mpc", "toggle", NULL } } },
    { MODKEY|ShiftMask,			    XK_v,	         spawn,		     SHCMD("vscodium") },
	{ MODKEY|ShiftMask,			    XK_minus,		 spawn,		     {.v = (const char*[]){ "mpc", "volume", "-5", NULL } } },
	{ MODKEY|ShiftMask,		        XK_equal,		 spawn,		     {.v = (const char*[]){ "mpc", "volume", "+5", NULL } } },
	{ MODKEY,			            XK_bracketleft,	 spawn,		     {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ MODKEY,		                XK_bracketright, spawn,		     {.v = (const char*[]){ "mpc", "next", NULL } } },
    { MODKEY,			            XK_u,	         spawn,		     SHCMD("dmenubookmarks") },
    { MODKEY,			            XK_i,	         spawn,		     SHCMD("dmenunet") },
    { MODKEY|ShiftMask,		        XK_i,		     spawn,		     {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
    { MODKEY,			            XK_r,	         spawn,		     SHCMD("remaps dmenu") },
    { MODKEY,			            XK_Delete,	     spawn,		     SHCMD("dmenukill") },
    { MODKEY,			            XK_F1,	         spawn,		     SHCMD("dmenumount") },
    { MODKEY,			            XK_F2,	         spawn,		     SHCMD("dmenuumount") },
    { MODKEY,			            XK_F3,	         spawn,		     SHCMD("dmenudisplay") },
    // { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    // { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    // { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    // { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    // { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    // { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    // { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    // { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    // { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                            0)
    TAGKEYS(                        XK_2,                            1)
    TAGKEYS(                        XK_3,                            2)
    TAGKEYS(                        XK_4,                            3)
    TAGKEYS(                        XK_5,                            4)
    TAGKEYS(                        XK_6,                            5)
    TAGKEYS(                        XK_7,                            6)
    TAGKEYS(                        XK_8,                            7)
    TAGKEYS(                        XK_9,                            8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	// { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
};

