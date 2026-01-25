#include <SDL2/SDL.h>

#define ROWS 10
#define COLS 10

typedef enum {
    NONE = 0, // 0
    SOLID = 1 << 0, // 0x01
    DAMAGE = 1 << 1 // 0x02
} TileFlag;

typedef enum {
    EMPTY = 0,
    WALL = (EMPTY) | (SOLID),
    THORN = (EMPTY) | (DAMAGE),
    LAVA = (EMPTY) | (SOLID | DAMAGE)
} Block;

int block_to_flags(Block block) {
    return (int) block;
}

int main() {
    int nx = 0, ny = 0;
    Block arr[ROWS][COLS];
    FILE *fp = fopen("tile.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file: ");
        return -1;
    }
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL Texture denemesi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, -1);

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    SDL_Surface *spriteSurface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(spriteSurface, NULL, SDL_MapRGB(spriteSurface->format, 139, 69, 19));
    int health = 100;

    SDL_Surface *lavaSurface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(lavaSurface, NULL, SDL_MapRGB(lavaSurface->format, 255, 117, 0));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture *sprite = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    SDL_Texture *lavaTexture = SDL_CreateTextureFromSurface(renderer, lavaSurface);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(spriteSurface);
    SDL_FreeSurface(lavaSurface);
    
    SDL_Rect srcRect = {0, 0, 32, 32};
    SDL_Rect dstRect = {0, 0, 32, 32};
    SDL_Rect spriteRect = {0, 0, 32, 32};
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    SDL_RenderPresent(renderer);

    int temp_block;
    for (int i = 0; i < COLS; i++) {
	for (int j = 0; j < ROWS; j++) {
	    fscanf(fp, "%d", &temp_block);
	    arr[i][j] = (Block) temp_block;
	    dstRect.x = j * 32;
	    dstRect.y = i * 32;
	    if (arr[i][j] == WALL)
		SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
	    else if (arr[i][j] == LAVA)
		SDL_RenderCopy(renderer, lavaTexture, &srcRect, &dstRect);
	}
    }

    SDL_Event event;
    int running = 1;
    int block_flags;
   
    while (running) {
	if (SDL_PollEvent(&event)) {
	    if (event.type == SDL_QUIT) {
		running = 0;
	    } else if (event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
		case SDLK_RIGHT: {
		    block_flags = block_to_flags(arr[ny][nx + 1]);
		    if (!(block_flags & SOLID)) {
			spriteRect.x += 32;
			nx++;
		    }
		    break;
		}
		case SDLK_LEFT: {
		    block_flags = block_to_flags(arr[ny][nx - 1]);
		    if (!(block_flags & SOLID)) {
			spriteRect.x -= 32;
			nx--;
		    }
		    break;
		}
		case SDLK_UP: {
		    block_flags = block_to_flags(arr[ny - 1][nx]);
		    if (!(block_flags & SOLID)) {
			spriteRect.y -= 32;
			ny--;
		    }
		    break;
		}
		case SDLK_DOWN: {
		    block_flags = block_to_flags(arr[ny + 1][nx]);
		    if (!(block_flags & SOLID)) {
			spriteRect.y += 32;
			ny++;
		    }
		    break;
		}
		}
		if (block_flags & DAMAGE) {
		    health -= 5;
		    printf("Health decreased by 5\n");
		}
		if (health <= 0) {
		    printf("Game over, your health is 0\n");
		    break;
		}
	    }
	}
	SDL_RenderClear(renderer);
    
	for (int i = 0; i < COLS; i++) {
	    for (int j = 0; j < ROWS; j++) {
		dstRect.x = j * 32;
		dstRect.y = i * 32;
		if (arr[i][j] == WALL)
		    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
		else if (arr[i][j] == LAVA)
		    SDL_RenderCopy(renderer, lavaTexture, &srcRect, &dstRect);
	    }
	}

	SDL_RenderCopy(renderer, sprite, NULL, &spriteRect);
	SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(sprite);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    fclose(fp);
    return 0;
}
