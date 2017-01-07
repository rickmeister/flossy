#ifndef CFG_H
#define CFG_H

#include <stdlib.h>
#include <stdio.h>

/*
 * This will later be used to import settings from either a script or a
 * json file
 */

struct Config {
	int width;
	int height;

	int res_x;
	int res_y;

	int fullscreen;
	char *title;

	/* Some cross-platform stuff. Finish later */
	char delim;
	char path[1024];
	char osname[64];
};

typedef struct Config Config;

#endif /* CFG_H */

