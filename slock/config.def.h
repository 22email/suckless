/* user and group to drop privileges to */
static const char *user  = "kevin";
static const char *group = "wheel";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#7aa89f",   /* during input */
	[FAILED] = "#c34043",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
