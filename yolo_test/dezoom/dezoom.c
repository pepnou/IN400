#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

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

Uint32 moy_zone(SDL_Surface *Surface,int x,int y,int largeur,int hauteur)
{
	Uint32 pixel,pixel_tmp;
	Uint8 r,g,b,a;
	int m_r=0,m_g=0,m_b=0,m_a=0;
	int i,j;
	
	if(Surface->w - x < largeur)largeur = Surface->w - x;
	if(Surface->h - y < hauteur)hauteur = Surface->h - y;
	
	for(i=0;i<largeur;i++)
	{
		for(j=0;j<largeur;j++)
		{
			pixel_tmp = obtenirPixel(Surface,x+i,y+j);
			SDL_GetRGBA(pixel_tmp,Surface->format,&r,&g,&b,&a);
			m_r += (int)r;
			m_g += (int)g;
			m_b += (int)b;
			m_a += (int)a;
		}
	}
	
	m_r /= (largeur*hauteur);
	m_g /= (largeur*hauteur);
	m_b /= (largeur*hauteur);
	m_a /= (largeur*hauteur);
	
	pixel = SDL_MapRGBA(Surface->format,(Uint8)m_r,(Uint8)m_g,(Uint8)m_b,(Uint8)m_a);
	
	return pixel;
}

SDL_Surface* dezoom_v1(SDL_Surface *Surface,int z_lvl)
{
	int Width = (Surface->w/z_lvl)+(Surface->w%z_lvl != 0);
	int Height = (Surface->h/z_lvl)+(Surface->h%z_lvl != 0);
	
	SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
	
	int i,j,largeur,hauteur;
	
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Height;j++)
		{
			definirPixel(_ret,i,j,moy_zone(Surface,i*z_lvl,j*z_lvl,z_lvl,z_lvl));
		}
	}
	
	return _ret;
}

void test_v1()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Surface* image = SDL_LoadBMP("plan-metro-paris-2017.bmp");
	SDL_Surface* image_z;
	SDL_Surface* ecran;
	
	SDL_Rect position;position.x=0;position.y=0;
	
	int i;
	
	for(i=1;i<10;i++)
	{
		image_z = dezoom_v1(image,i);
		ecran = SDL_SetVideoMode(image_z->w,image_z->h,32,SDL_HWSURFACE);
		
		SDL_BlitSurface(image_z,NULL,ecran,&position);
		
		SDL_Flip(ecran);
		
		pause();
	}
	
	SDL_FreeSurface(image);
	SDL_FreeSurface(ecran);
	SDL_Quit();
}

SDL_Surface* dezoom_v2(SDL_Surface *Surface,int z_lvl)
{
	int Width = (Surface->w/(z_lvl-1))+(Surface->w%(z_lvl-1) != 0);
	int Height = (Surface->h/(z_lvl-1))+(Surface->h%(z_lvl-1) != 0);
	
	SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
	
	int i,j,largeur,hauteur;
	
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Height;j++)
		{
			definirPixel(_ret,i,j,moy_zone(Surface,i*(z_lvl-1),j*(z_lvl-1),z_lvl,z_lvl));
		}
	}
	
	return _ret;
}

void test_v2()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Surface* image = SDL_LoadBMP("plan-metro-paris-2017.bmp");
	SDL_Surface* image_z;
	SDL_Surface* ecran;
	
	SDL_Rect position;position.x=0;position.y=0;
	
	int i;
	
	for(i=2;i<10;i++)
	{
		image_z = dezoom_v2(image,i);
		ecran = SDL_SetVideoMode(image_z->w,image_z->h,32,SDL_HWSURFACE);
		
		SDL_BlitSurface(image_z,NULL,ecran,&position);
		
		SDL_Flip(ecran);
		
		pause();
	}
	
	SDL_FreeSurface(image);
	SDL_FreeSurface(ecran);
	SDL_Quit();
}

SDL_Surface* dezoom_vf(SDL_Surface *Surface,int z_lvl,int recouvrement)
{
	int Width = (Surface->w/(z_lvl-recouvrement))+(Surface->w%(z_lvl-recouvrement) != 0);
	int Height = (Surface->h/(z_lvl-recouvrement))+(Surface->h%(z_lvl-recouvrement) != 0);
	
	SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
	
	int i,j,largeur,hauteur;
	
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Height;j++)
		{
			definirPixel(_ret,i,j,moy_zone(Surface,i*(z_lvl-recouvrement),j*(z_lvl-recouvrement),z_lvl,z_lvl));
		}
	}
	
	return _ret;
}

void test_vf(int recouvrement)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Surface* image = SDL_LoadBMP("plan-metro-paris-2017.bmp");
	SDL_Surface* image_z;
	SDL_Surface* ecran;
	
	SDL_Rect position;position.x=0;position.y=0;
	
	int i;
	
	for(i=recouvrement+1;i<10;i++)
	{
		image_z = dezoom_vf(image,i,recouvrement);
		ecran = SDL_SetVideoMode(image_z->w,image_z->h,32,SDL_HWSURFACE);
		
		SDL_BlitSurface(image_z,NULL,ecran,&position);
		
		SDL_Flip(ecran);
		
		pause();
	}
	
	SDL_FreeSurface(image);
	SDL_FreeSurface(ecran);
	SDL_Quit();
}

int main()
{
	//test_v1();
	//test_v2();
	test_vf(2);
	
	return 0;
}
