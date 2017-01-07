#ifndef APP_H
#define APP_H

#include "SDL2/SDL.h"
struct Config;

struct Application {
	int wndWidth;
	int wndHeight;
	unsigned int wndFlags;
	int resX;
	int resY;

	char *title;

	SDL_Window *window;
	SDL_Renderer *renderer;

};

typedef struct Application Application;

Application *app_Init(struct Config *cfg);
void app_Free(Application *app);

int app_Run(Application *app, int debug);

void app_BlitScreen(Application *app);
#endif /* APP_H */
