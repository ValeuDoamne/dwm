/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0; 	/* 1 means swallow foating windows by default */
static const unsigned int gappx	    = 18;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono:Regular:size=9:antialiasing=true", "Material Design Icons:Regular:pixelsize=18:antialias=true", "PowerlineSymbols:pixelsize=24","Siji:pixelsize=12", "fontawesome:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[]       = "hack:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_blue[]	    = "#2258EB";
static const char col_dark_blue[]   = "#0C225E";
static const char col_orchid[]	    = "#DA75D6";
static const char col_black[]       = "#000000";
static const char col_light_black[] = "#0a0a0a"; 
static const char col_red[]	    = "#ff0000";
static const char col_redish[]      = "#400000";
static const char col_white[]       = "#ffffff";
static const char col_yellow[]      = "#ffff00";




static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_black,  col_redish },
};


static const char *const autostart[] = {
	"xset", "r", "rate", "300", "50", NULL,
	"slstatus", NULL,
	"dbus-update-activation-environment", "--systemd", "DBUS_SESSION_BUS_ADDRES", "DISPLAY", "XAUTHORITY", NULL,
	"redshift", NULL,
	"feh", "--bg-scale", "/home/cred/.config/arch2.png", NULL,
	"/usr/lib/notify-osd/notify-osd", NULL,
	"xcompmgr", NULL,
	"xinput", "set-prop", "14",  "317", "1", NULL,
	"xss-lock", "slock", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };



static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{"Alacritty",NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,      NULL,     "Snake",        0,         0,          0,           1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󰙀",        tile },    /* first entry is default */
	{ "<><",      NULL },    /* no layout function means floating behavior */
	{ "[D]",      deck },
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "󰕴",        dwindle },
	{ "󰋁",        grid }, 
	{ "󱒅",        centeredmaster },
	{ "󰕬",        centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_bracketleft, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_bracketright,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_apostrophe,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_slash,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_period,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define XK_NO_MOD 0

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL};
static const char *termcmd[]  = { "st", NULL };

static const char *browser[] = { "chromium", NULL} ;
static const char *player_previous[] = { "playerctl", "previous", NULL };
static const char *player_next[] =     { "playerctl", "next", NULL};
static const char *player_play_pause[] = { "playerctl", "play-pause", NULL};
static const char *player_stop[]       = { "playerctl", "stop", NULL};


static const char *brightness_up[]     = {"light", "-A", "10", "-s", "sysfs/backlight/amdgpu_bl0", NULL};
static const char *brightness_down[]   = {"light", "-U", "10", "-s", "sysfs/backlight/amdgpu_bl0", NULL};

//static const char *lower_volume[] = {"pamixer", "-d", "10;", "kill" , "-44", "$(pidof", "dwmblocks)", NULL};
//static const char *raise_volume[] = {"pamixer", "-i", "10", NULL};
//static const char *mute_volume[] =  {"pamixer", "-t", NULL};


#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY, 	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,			XK_w, 	   spawn, 	   {.v = browser} },
	{ MODKEY,			XK_s,	   spawn,	   SHCMD("st -e lf")},

	{ MODKEY,			XK_grave,  spawn,	   SHCMD("dmenuunicode")},
	{ XK_NO_MOD, 			XF86XK_AudioPrev, spawn,       	{.v = player_previous} },
	{ XK_NO_MOD,			XF86XK_AudioNext, spawn,       	{.v = player_next} },
	{ XK_NO_MOD,			XF86XK_AudioPlay, spawn,       	{.v = player_play_pause} },
	{ XK_NO_MOD, 			XF86XK_AudioPause, spawn,      	{.v = player_play_pause} },
	{ XK_NO_MOD,			XF86XK_AudioStop, spawn,       	{.v = player_stop} },
	{ XK_NO_MOD,			XF86XK_AudioLowerVolume, spawn,	SHCMD("pamixer -d 10") },
	{ XK_NO_MOD,			XF86XK_AudioRaiseVolume, spawn,	SHCMD("pamixer -i 10") },
	{ XK_NO_MOD,			XF86XK_AudioMute, spawn,	SHCMD("pamixer -t ") },
	{ XK_NO_MOD,			XF86XK_MonBrightnessUp, spawn, 	{.v = brightness_up} },
	{ XK_NO_MOD,			XF86XK_MonBrightnessDown, spawn, {.v = brightness_down} },
	{ XK_NO_MOD,			XF86XK_TouchpadToggle, spawn,    SHCMD("perl -e \'{`xinput list-props \"ELAN1300:00 04F3:3057 Touchpad\"` =~ /^.*Device Enabled.+?(\\d)$/m and  {$1 ? `xinput --disable \"ELAN1300:00 04F3:3057 Touchpad\"` : `xinput --enable \"ELAN1300:00 04F3:3057 Touchpad\"`}} \'") },
	{ XK_NO_MOD,			XF86XK_ScreenSaver,       spawn,    SHCMD("xset dpms force off") },
	{ MODKEY,			XK_Print, spawn,     SHCMD("scrot '%F-%H-%M_$wx$h.png' -e 'mv $f /home/cred/Pictures/'") },
	
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY|Mod1Mask,              XK_equal,    incnmaster,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_minus,    incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,			XK_minus,  setgaps,	     {.i = -1 } },
	{ MODKEY,			XK_equal,  setgaps,	     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_equal,  setgaps,	     {.i = 0} },
	
	/*	
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
*/
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,			XK_g,	   setlayout,	   {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,		XK_g,	   setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,		XK_t,	   setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,		XK_r,	   setlayout, 	   {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,		XK_v,	   setlayout, 	   {.v = &layouts[8]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
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
	{ MODKEY,			XK_Escape, self_restart,  {0} },
	{ MODKEY|ShiftMask,             XK_Escape, quit,          {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
