#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <string.h>

struct Vertice
{
	int posicao;
	float x;
	float y;
	float z;
	struct Vertice *Prox;
};

typedef struct Vertice listaVertices;

struct Face
{
	float w;
	float x;
	float y;
	float z;
	struct Face *Prox;
};

typedef struct Face listaFaces;

void inicia_V(listaVertices *Lista);
int vazia_V(listaVertices *Lista);
void insere_V(listaVertices *Lista,float x,float y,float z,int posicao);
void imprime_V(listaVertices *V);
void inicia_F(listaFaces *Lista);
int vazia_F(listaFaces *Lista);
void insere_F(listaFaces *Lista,float w,float x,float y,float z);
void imprime_F(listaFaces *F);
void ler(FILE *file, listaVertices *listaV, listaFaces *listaF);
void ler_big(FILE *file, listaVertices *listaV, listaFaces *listaF);
void ler_big_coelho(FILE *file, listaVertices *listaV, listaFaces *listaF);
listaVertices* busca_vertice(listaVertices *lista, float posicao);