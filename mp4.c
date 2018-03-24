#include "biblioteca.h"

//atribuicao da tela
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

int main()
{
	//le objeto
	FILE *obj;listaVertices *v;
	//para ver outro objeto é só colocar o nome do objeto e ter ele na pasta
	obj = fopen("cube.obj", "rt");
	
	listaVertices *VERTICES = (listaVertices*) malloc(sizeof(listaVertices));
	listaFaces *FACES = (listaFaces*)malloc(sizeof(listaFaces));
	inicia_F(FACES);
	inicia_V(VERTICES);
	//funcoes para ler objts
	//ler_big(obj,VERTICES,FACES);
	//ler_big_coelho(obj,VERTICES,FACES);	
	ler(obj,VERTICES,FACES);


	listaFaces *tmp;
	float face1,face2,face3,face4;
	float Cx=40,Cy=20,Cz=55; //posicao da camera
	float Vx,Vy,Vz,PX,PY,screen_x,screen_y;
	float x1,x2,y1,y2,x3,y3,x4,y4;
	SDL_Init(SDL_INIT_VIDEO); //inicializa o SDL e o sistema de video
	SDL_Surface *screen; //a janela principal
	SDL_Event event; //para os eventos
	SDL_Rect dest = {0,0,0,0}; //destino da imagem nno screen

	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32 ,SDL_HWSURFACE | SDL_DOUBLEBUF); //Cria a janela

	int done = 0; //variavel para controle do loop
	while(done == 0)//loop principal
	{
		while(SDL_PollEvent(&event))  //le a fila de eventos e poe o evento mais antigo em event
		{
			//verifica se o evento mais antigo é do tipo SDL_QUIT
			if (event.type == SDL_QUIT) //se o usuario clicou para fechar a janela
			{
				done = 1;//encerra o loop
			}
				SDL_FillRect(screen,NULL,0x000000);
				tmp = FACES->Prox;
				while(tmp != NULL)
				{
					face1=tmp->w;
					v = busca_vertice(VERTICES,face1); //vai retornar os vertices que estavam na linha face1
					Vx = v->x;
					Vy = v->y;
					Vz = v->z;
					x1 = Cx + Cz*((Vx - Cx)/(Vz + Cz));
					y1 = Cy + Cz*((Vy - Cy)/(Vz + Cz));	
					x1 = x1 + SCREEN_WIDTH/2;
					y1 = y1 + SCREEN_HEIGHT/2;

						
					face2=tmp->x;
					v = busca_vertice(VERTICES,face2); //vai retornar os vertices que estavam na linha face2
					Vx = v->x;
					Vy = v->y;
					Vz = v->z;
					x2 = Cx + Cz*((Vx - Cx)/(Vz + Cz));
					y2 = Cy + Cz*((Vy - Cy)/(Vz + Cz));	
					x2 = x2 + SCREEN_WIDTH/2;
					y2 = y2 + SCREEN_HEIGHT/2;

					lineRGBA(screen,
			               x1, y1,
			               x2, y2,
			               255, 0, 0, 255);

					face3=tmp->y; 
					v = busca_vertice(VERTICES,face3); //vai retornar os vertices que estavam na linha face3
					Vx = v->x;
					Vy = v->y;
					Vz = v->z;
					x3 = Cx + Cz*((Vx - Cx)/(Vz + Cz));
					y3 = Cy + Cz*((Vy - Cy)/(Vz + Cz));
					x3 = x3 + SCREEN_WIDTH/2;
					y3 = y3 + SCREEN_HEIGHT/2;
	

					lineRGBA(screen,
			               x2, y2,
			               x3, y3,
			               255, 0, 0, 255);

					face4=tmp->z;
					if(face4==0)
					{
						lineRGBA(screen,
			               x3, y3,
			               x1, y1,
			               255, 0, 0, 255);
					}
					else
					{
						v = busca_vertice(VERTICES,face4); //vai retornar os vertices que estavam na linha face4
						Vx = v->x;
						Vy = v->y;
						Vz = v->z;
						x4 = Cx + Cz*((Vx - Cx)/(Vz + Cz));
						y4 = Cy + Cz*((Vy - Cy)/(Vz + Cz));	
						x4 = x4 + SCREEN_WIDTH/2;
						y4 = y4 + SCREEN_HEIGHT/2;


						lineRGBA(screen,
			               x3, y3,
			               x4, y4,
			               255, 0, 0, 255);

			            lineRGBA(screen,
			               x4, y4,
			               x1, y1,
			               255, 0, 0, 255);
					}		
					tmp = tmp->Prox;
				}    		

			//verifica se o evento mais antigo eh do tipo SDL_KEYDOWN
			if(event.type == SDL_KEYDOWN)
			{
				//verifica qual tecla foi apertada
				switch(event.key.keysym.sym) //vai mover a camera
				{
					case SDLK_UP:
						Cy=Cy+20;
						break;
					case SDLK_DOWN:
						Cy=Cy-20;
						break;
					case SDLK_RIGHT:
						Cx=Cx+20;
						break;
					case SDLK_LEFT:
						Cx=Cx-20;
						break;
					case SDLK_PAGEUP:
						Cz=Cz+20;
						break;
					case SDLK_PAGEDOWN:
						Cz=Cz-20;
						break;		
					default:
						break;		
				}
			}			
		}
		SDL_Flip(screen);
	}

	SDL_Quit(); //fecha o SDL
	return 0;
}