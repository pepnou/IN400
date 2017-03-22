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

/*SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height)
{
    if(!Surface || !Width || !Height)
        return 0;
     
    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

	double _stretch_factor_x = (double)Width  / (double)Surface->w;
    double _stretch_factor_y = (double)Height / (double)Surface->h;
	
	int y,x,o_y,o_x;
	
    for(y = 0; y < Surface->h; y++)
        for(x = 0; x < Surface->w; x++)
            for(o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(o_x = 0; o_x < _stretch_factor_x; ++o_x)
					definirPixel(_ret,((Sint32)_stretch_factor_x * x) + o_x, ((Sint32)_stretch_factor_y * y) + o_y,obtenirPixel(Surface,x,y));
                    //DrawPixel(_ret, ((Sint32)_stretch_factor_x * x) + o_x, ((Sint32)_stretch_factor_y * y) + o_y, ReadPixel(Surface, x, y));
 
    return _ret;
}*/

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
	
	for(i=0;i<(Surface->w/z_lvl)+(Surface->w%z_lvl != 0);i++)
	{
		for(j=0;j<(Surface->h/z_lvl)+(Surface->h%z_lvl != 0);j++)
		{
			definirPixel(_ret,i,j,moy_zone(Surface,i*z_lvl,j*z_lvl,z_lvl,z_lvl));
		}
	}
	
	return _ret;
}

void test()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Surface* image = SDL_LoadBMP("plan_metro_paris_2017.bmp");
	SDL_Surface* image_z = dezoom_v1(image,3);
	SDL_Surface* ecran = SDL_SetVideoMode(image_z->w,image_z->h,32,SDL_HWSURFACE);
	
	SDL_Rect position;position.x=0;position.y=0;
	
	//SDL_BlitSurface(image,NULL,ecran,&position);
	SDL_BlitSurface(image_z,NULL,ecran,&position);
	
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
