/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 12;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono NF:size=10" };
static const char dmenufont[]       = "JetBrainsMono NF:size=10";
static const char col_gray1[]       = "#191724";
static const char col_gray2[]       = "#191724";
static const char col_gray3[]       = "#6e6a86";
static const char col_gray4[]       = "#191724";
static const char main_col[]        = "#c4a7e7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, main_col,  main_col},
	[SchemeTitle]  = { col_gray3, col_gray1,  col_gray1}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

#include<X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", main_col, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[] = {"firefox", NULL};

static const char *vol_up[] = {"/home/kevin/.config/suckless/dwm/scripts/volumecontrol.sh", "i", NULL};
static const char *vol_down[] = {"/home/kevin/.config/suckless/dwm/scripts/volumecontrol.sh", "d", NULL};
static const char *mute[] = {"/home/kevin/.config/suckless/dwm/scripts/volumecontrol.sh", "m", NULL};

static const char *bright_up[] = {"/home/kevin/.config/suckless/dwm/scripts/brightness.sh", "i", NULL};
static const char *bright_down[] = {"/home/kevin/.config/suckless/dwm/scripts/brightness.sh", "d", NULL};

static const char *lock[] = {"slock", NULL};

static const char *screenshot_select[] = {"flameshot", "gui", NULL};
static const char *screenshot_full[] = {"flameshot", "full", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ControlMask,           XK_f,      spawn,          {.v = browsercmd } },
  { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
  {0, XF86XK_AudioRaiseVolume,               spawn,          {.v = vol_up} },
  {0, XF86XK_AudioLowerVolume,               spawn,          {.v = vol_down} },
  {0, XF86XK_AudioMute,                      spawn,          {.v = mute} },
  {0, XF86XK_MonBrightnessUp,                spawn,          {.v = bright_up} },
  {0, XF86XK_MonBrightnessDown,              spawn,          {.v = bright_down} },
  { ControlMask,                  XK_Escape, togglebar,      {0} },
  { MODKEY,                       XK_l,      focusright,     {0} },					// focus right
	{ MODKEY|ControlMask,		        XK_minus,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_equal, cyclelayout,    {.i = +1 } },
  { MODKEY|ControlMask,           XK_l,      spawn,          {.v = lock}},
	{ MODKEY,                       XK_h,      focusleft,      {0} },					// focus left
  { MODKEY|ShiftMask, XK_s, spawn, {.v = screenshot_select }},
  { MODKEY|Mod1Mask, XK_s, spawn, {.v = screenshot_full}},
	{ MODKEY,                       XK_j,      focusdown,      {0} },					// focus down
	{ MODKEY,                       XK_k,      focusup,        {0} },					// focus up
  { MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|Mod1Mask,              XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,              XK_k,      setcfact,       {.f = +0.25} },
	{ MODKEY|Mod1Mask,              XK_j,      setcfact,       {.f = -0.25} },
	{ MODKEY|Mod1Mask,              XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // (Tiled)
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, // Monocle
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[13]} }, // Flote
	{ MODKEY,                       XK_z,      setlayout,      {0} },
	{ MODKEY,                       XK_s,      togglefloating, {0} },
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
	{ MODKEY,                       XK_Delete,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

