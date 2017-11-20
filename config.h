/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = { 
	"Misc xbmicons:size=10",
	"Terminus:size=10",
	"simsun:size=10",
	"monospace:size=10"
};

#define NUMCOLORS 14
static const char colors[NUMCOLORS][3][9] = {
  // border foreground background
  { "#444444", "#bbbbbb", "#222222" }, // 1 = normal (grey on black)
  { "#005577", "#eeeeee", "#005577" }, // 2 = selected (white on black)
  { "#dc322f", "#1d1f21", "#f0c674" }, // 3 = urgent (black on yellow)
  { "#282a2e", "#282a2e", "#1d1f21" }, // 4 = darkgrey on black (for glyphs)
  { "#282a2e", "#1d1f21", "#282a2e" }, // 5 = black on darkgrey (for glyphs)
  { "#282a2e", "#cc6666", "#1d1f21" }, // 6 = red on black
  { "#282a2e", "#b5bd68", "#1d1f21" }, // 7 = green on black
  { "#282a2e", "#de935f", "#1d1f21" }, // 8 = orange on black
  { "#282a2e", "#f0c674", "#282a2e" }, // 9 = yellow on darkgrey
  { "#282a2e", "#81a2be", "#282a2e" }, // A = blue on darkgrey
  { "#282a2e", "#b294bb", "#282a2e" }, // B = magenta on darkgrey
  { "#282a2e", "#8abeb7", "#282a2e" }, // C = cyan on darkgrey
  { "#282a2e", "#282a2e", "#005577" },// darkgry on blue (for glyphs)
  { "#282a2e", "#005577", "#282a2e" }// blue on darkgrey (for glyphs)


};

static const char dmenufont[]       = "monospace:size=10";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "\uE000", "\uE001", "\uE002", 
                              "\uE003", "\uE008", "\uE004", 
                              "\uE005", "\uE006", "\uE007" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "jetbrains-android-studio", NULL, NULL,  0,       1,           -1 },
	{ "netease-cloud-music", NULL, NULL,  1 << 1,       1,           -1 },
	{ "Typora",   NULL,       NULL,       1 << 3,       1,           -1 }
	
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\uE019 \uE009 \uE019",      tile },    /* first entry is default */
	{ "\uE019 \uE00A \uE019",      NULL },    /* no layout function means floating behavior */
	{ "\uE019 \uE00B \uE019",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod4Mask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "xterm", NULL };
static const char *lockscr[]  = { "slock", NULL};

static const char *upvol[]   = { "amixer", "-D", "pulse", "sset", "Master", "5%+", NULL };
static const char *downvol[] = { "amixer", "-D", "pulse", "sset", "Master", "5%-", NULL };
static const char *mutevol[] = { "amixer", "-D", "pulse", "sset", "Master", "toggle", NULL };

#include "push.c"
#include "selfrestart.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod4Mask,                     XK_r,      spawn,          {.v = dmenucmd    } },
	{ Mod4Mask,                     XK_t,      spawn,          {.v = termcmd     } },
	{ Mod4Mask,                     XK_l,      spawn,          {.v = lockscr     } },
	{ Mod4Mask,                     XK_j,      pushup,         {0} },
	{ Mod4Mask,                     XK_k,      pushdown,       {0} },
	{ Mod4Mask|ShiftMask,           XK_r,      self_restart,   {0} },
	{ MODKEY,                       XK_F12,    spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_F11,    spawn,          {.v = downvol } },
	{ MODKEY,	       		XK_F9,     spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_grave,  view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
};

