#include "biblioteca.h"

//VERTICES

void inicia_V(listaVertices *Lista)
{
	Lista->Prox = NULL;
}

int vazia_V(listaVertices *Lista)
{
	if(Lista->Prox == NULL)
		return 1;
	else
		return 0;
}

void insere_V(listaVertices *Lista,float x,float y,float z,int posicao)
{
	listaVertices *novo=(listaVertices*) malloc(sizeof(listaVertices));
	if(!novo){
		printf("Sem memoria\n");
		exit(1);
	}
	novo->posicao = posicao;
	novo->x = x;
	novo->y = y;
	novo->z = z;
	novo->Prox = NULL;
	if(vazia_V(Lista))
		Lista->Prox = novo;
	else{
		listaVertices *tmp = Lista->Prox;
		while(tmp->Prox !=NULL)
			tmp = tmp->Prox;
		tmp->Prox = novo;
	}
}

void imprime_V(listaVertices *V)
{
	listaVertices *tmp;
	tmp = V->Prox;
	while(tmp != NULL)
	{
		printf("VERTICE: %d : x:%5.2f y:%5.2f z:%5.2f\n",tmp->posicao,tmp->x,tmp->y,tmp->z);
		tmp = tmp->Prox;
	}
	printf("\n");
}

//FACES

void inicia_F(listaFaces *Lista)
{
	Lista->Prox = NULL;
}

int vazia_F(listaFaces *Lista)
{
	if (Lista->Prox == NULL)
		return 1;
	else
		return 0;
}

void insere_F(listaFaces *Lista,float w,float x,float y,float z)
{
	listaFaces *novo=(listaFaces*) malloc(sizeof(listaFaces));
	if(!novo){
		printf("Sem memoria\n");
		exit(1);
	}
	novo->w = w;
	novo->x = x;
	novo->y = y;
	if (z!= -1) novo->z = z;
	novo->Prox = NULL;
	if(vazia_F(Lista))
		Lista->Prox = novo;
	else{
		listaFaces *tmp = Lista->Prox;
		while(tmp->Prox !=NULL)
			tmp = tmp->Prox;
		tmp->Prox = novo;
	}
}

void imprime_F(listaFaces *F)
{
	listaFaces *tmp;
	tmp = F->Prox;
	while(tmp != NULL)
	{
		printf("FACE: a:%f b:%f c:%f d:%f\n",tmp->w,tmp->x,tmp->y,tmp->z);
		tmp = tmp->Prox;
	}
	printf("\n");
}

void ler(FILE *file, listaVertices *listaV, listaFaces *listaF)
{
	float x,y,z;
	float a,b,c,d,pos=0;
	char entrada[1000], nada;
    do
    {
		fgets(entrada,1000,file);
		if (entrada[0]=='v')
		{
			pos++;
			sscanf(entrada,"%c %f %f %f",&nada,&x,&y,&z);
			insere_V(listaV, x, y, z,pos);
		}
		if (entrada[0]=='f')
		{
			sscanf(entrada,"%c %f %f %f %f",&nada,&a,&b,&c,&d);
			insere_F(listaF, a, b, c, d);
		}
		d = -1;
	}while (!feof(file));
	//imprime_V(listaV);
	//imprime_F(listaF);
}

void ler_big(FILE *file, listaVertices *listaV, listaFaces *listaF)
{
	float x,y,z;
	float face1,face2,face3,a,b,c,d,e,f,g,h,i,pos=0;
	do
	{
		char lineHeader[128];
		int res = fscanf(file, "%s",lineHeader);
		if (res==EOF)
			break;
		if (strcmp(lineHeader, "v") == 0)
		{
			pos++;
			fscanf(file, "%f %f %f\n", &x,&y,&z);
			insere_V(listaV, x, y, z,pos);
		}
		else if (strcmp(lineHeader,"vt")==0) //nao sei oque eh vt e se precisa disso
		{
			fscanf(file, "%f %f\n",&x,&y);
		}
		else if (strcmp(lineHeader,"vn")==0) //le as normais, mas n sei se precisa
		{
			fscanf(file,"%f %f %f\n",&x,&y,&z);
		}else if(strcmp(lineHeader,"f")==0)
		{
			fscanf(file, "%f/%f/%f %f/%f/%f %f/%f/%f\n", &face1,&a,&b,&face2,&c,&d,&face3,&e,&f);
			d=-1;
			insere_F(listaF, face1, face2, face3, d);
		}
	}while(!feof(file));
	//imprime_V(listaV);
	//imprime_F(listaF);
}

void ler_big_coelho(FILE *file, listaVertices *listaV, listaFaces *listaF)
{
	float x,y,z;
	float face1,face2,face3,a,b,c,d,e,f,g,h,i,pos=0;
	do
	{
		char lineHeader[128];
		int res = fscanf(file, "%s",lineHeader);
		if (res==EOF)
			break;
		if (strcmp(lineHeader, "v") == 0)
		{
			pos++;
			fscanf(file, "%f %f %f\n", &x,&y,&z);
			insere_V(listaV, x, y, z,pos);
		}
		else if (strcmp(lineHeader,"vt")==0) //nao sei oque eh vt e se precisa disso
		{
			fscanf(file, "%f %f\n",&x,&y);
		}
		else if (strcmp(lineHeader,"vn")==0) //le as normais, mas n sei se precisa
		{
			fscanf(file,"%f %f %f\n",&x,&y,&z);
		}else if(strcmp(lineHeader,"f")==0)
		{
			fscanf(file, "%f/%f %f/%f %f/%f\n", &face1,&a,&face2,&c,&face3,&e);
			d=-1;
			insere_F(listaF, face1, face2, face3, d);
		}
	}while(!feof(file));
	//imprime_V(listaV);
	//imprime_F(listaF);
}

listaVertices* busca_vertice(listaVertices *lista, float posicao)
{
	listaVertices *tmp;
	tmp=lista->Prox;
	while(tmp->posicao != posicao)
	{
		tmp=tmp->Prox;
	}
	return tmp;
}