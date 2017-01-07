#ifndef SPRITE_H
#define SPRITE_H
#include "SDL2/SDL.h"
#include "chipmunk/chipmunk.h"

struct Application;

struct Sprite {
	int width;
	int height;

	float x;
	float y;
	float angle;
	float rotation;
	float speed;

	cpBody *body;
	cpShape *shape;

	SDL_Texture *t;
	SDL_Rect *r;
};

typedef struct Sprite Sprite;

Sprite *sprite_Create(SDL_Renderer *r, SDL_Surface *s);

void sprite_Destroy(Sprite *sprite);

void sprite_SetPosition(Sprite *sprite, float x, float y);
void sprite_Update(Sprite *sprite);
#endif /* SPRITE_H */
