#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

#define COULEUR 255,0,0,255

void pause()
{
	SDL_Event event;
	int continuer = 1;
	while(continuer)
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_MOUSEBUTTONUP)
		{
			continuer = 0;
		}
	}
}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
	
    switch(nbOctetsParPixel)
    {
        case 1:
            *p = pixel;
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0; 
    }
}

void draw_rectangle(SDL_Surface** Surface,int x, int y,int cote)
{
	Uint32 pixel;
	pixel = SDL_MapRGBA((*Surface)->format,COULEUR);
	
	int i,j;
	for(i=x-(cote/2);i<=x+(cote/2);i++)
	{
		for(j=y-(cote/2);j<=y+(cote/2);j++)
		{
			definirPixel(*Surface,i,j,pixel);
		}
	}
}

int distance(int x1, int x2)
{
	if(x1-x2 >= 0) return x1-x2;
	else return x2-x1;
}

void draw_line(SDL_Surface** Surface,int x1, int y1, int x2, int y2, int epaisseur)
{
	Uint32 pixel;
	pixel = SDL_MapRGBA((*Surface)->format,COULEUR);
	
	draw_rectangle(Surface,x1,y1,epaisseur);
	
	while((x1 != x2)&&(y1 != y2))
	{
		if(distance(x1,x2)>distance(y1,y2))
		{
			if(x1 > x2)
				x1--;
			else
				x1++;
		}
		else
		{
			if(y1 > y2)
				y1--;
			else
				y1++;
		}
		draw_rectangle(Surface,x1,y1,epaisseur);
	}
}

void test()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Surface* ecran = SDL_SetVideoMode(600,600,32,SDL_HWSURFACE);
	SDL_Surface* image = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 600, 32, 0, 0, 0, 0);
	SDL_Rect position,position_copie;position.x=0;position.y=0;
	
	//draw_line(&image,100,100,500,500,10);
	//draw_rectangle(&image,300,300,100);
	
	SDL_BlitSurface(image,NULL,ecran,&position);
	SDL_Flip(ecran);
	
	pause();
	
	SDL_FreeSurface(image);
	SDL_FreeSurface(ecran);
	
	SDL_Quit();
}

int main()
{
	test();
	
	return 0;
}
