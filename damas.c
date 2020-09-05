//********************************************
// damas.c
// 
// programita que simula un juego de damas simple entre 
// dos jugadores con un valor continuo de expertise P
// que va desde 0 (jugador aleatorio) hasta 1 (jugador cauteloso)
// Rogelio Díaz-Méndez,
// Habana Vieja, junio de 2010.
//*********************************************


#include <stdio.h>
#include <stdlib.h>
#include <math.h> 



#define l 8 // tamanho lineal del tablero

#define N l*l/2 //numero de casillas transitables



/********************************************************************/
/*****THIS IS COMPLETELY DEVOTED TO THE RANDOM NUMEBR GENERATOR******/
#define FNORM   (2.3283064365e-10)
#define RANDOM  ((ira[ip++] = ira[ip1++] + ira[ip2++]) ^ ira[ip3++])
#define FRANDOM (FNORM * RANDOM)
#define pm1 ((FRANDOM > 0.5) ? 1 : -1)         

unsigned myrand, ira[256];
unsigned char ip, ip1, ip2, ip3;

unsigned rand4init(void)
{
  unsigned long long y;

  y = (myrand*16807LL);
  myrand = (y&0x7fffffff) + (y>>31);
  if (myrand&0x80000000)
    myrand = (myrand&0x7fffffff) + 1;
  return myrand;
}                    

void Init_Random(void)
{
  int i;

  ip = 128;
  ip1 = ip - 24;
  ip2 = ip - 55;
  ip3 = ip - 61;

  for (i=ip3; i<ip; i++)
    ira[i] = rand4init();
}                    

float gauss_ran(void)
{
  static int iset=0;
  static float gset;
  float fac, rsq, v1, v2;
  
  if (iset == 0) {
    do {
      v1 = 2.0 * FRANDOM - 1.0;
      v2 = 2.0 * FRANDOM - 1.0;
      rsq = v1 * v1 + v2 * v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    fac = sqrt(-2.0 * log(rsq) / rsq);
    gset = v1 * fac;
    iset = 1;
    return v2 * fac;
  } else {
    iset = 0;
    return gset;
  }
}

/***********HERE WE FINISH THE RANDOM NUMBER GENERATOR********/
/*************************************************************/





//*** Variables

int tab[N], vec[N][l];
int iN[N], jZ[4];
int nexp;
double P1, P2;
char *dir;
unsigned myrand_back;
int salida;




//*** Functions

void init_vec();
void init_fichas();
void print_tablero(int);
int jugada(int);
int comida(int*,int*,int);
void come(int,int);
void mueve(int,int);
int aleat(int,int);
int defensa(int);
int amenaza(int,int);
int eval_comida(int,int,int);
int eval_move(int,int);
int aleat_iN(int);
int aleat_jZ(int);
void make_files();
void print_tiempo(int);
void print_ventaja(int);
double set_ventaja();



//****************************************
int main(int argc, char *argv[])
{
  int i, j, t, f;
  double pct;
  
  if(argc!=7) {
    printf("usage: %s <P1(blancas)> <P2(negras)> <nexp> <directorio> <pct(fotos)> <seed>\n", argv[0]);
    exit(1);
  }          
  
  P1=(double)atof(argv[1]); // expertize del jugador 1
  P2=(double)atof(argv[2]); // expertize del jugador 2
  nexp=(int)atoi(argv[3]); // cantidad de partidas
  dir=(char *)argv[4]; // directorio de resultados
  pct=(double)atof(argv[5]);// porciento de fotos de juegos a tirar
  myrand=(unsigned)atoi(argv[6]); // semilla del generador de aleatorios
  
  myrand_back=myrand;
  Init_Random();

  init_vec();

  make_files();


  for (i=0;i<nexp;i++)
    {
      
      init_fichas();
      if (i<nexp*pct) print_tablero(i);
      
      salida=pm1;
      
      t=0;
      do
	{
	  f=jugada(t);
	  t++;
	  if (i<nexp*pct) print_tablero(i);
	  print_ventaja(1);
	}
      while(f);
      print_tiempo(t);
      print_ventaja(0);
    }



  return 0;
}
//****************************************



//***** dice si puede comer dado un sitio, un sentido y una ficha
int eval_comida(int i, int j, int ficha)
{
  int c=0;
  
  if (vec[i][j]>0&&vec[i][j+4]>0)
    if ((tab[vec[i][j]]==-ficha)&&(tab[vec[i][j+4]]==0))
	c=1;
  
  return c;
} 


//***** dice si puede mover un sitio dado en una direccion dada
int eval_move(int i, int j)
{
  int c=0;
  
  if (vec[i][j]>0)
    if (tab[vec[i][j]]==0)
      c=1;
  
  return c;
} 


//***** dice si se puede comer y donde
int comida(int *n1, int *n2, int ficha)
{
  int i, j, c=0;

  for (i=0;i<N;i++)
    if (tab[i]==ficha)
      for (j=0;j<4;j++)
	  if (eval_comida(i,j,ficha)==1)
	    {
	      *n1=i;
	      *n2=j;
	      j=4;
	      i=N;
	      c=1;
	    }
  return c;
}



//**** come en una posicion dada
void come(int n1, int n2)
{
  
  tab[vec[n1][n2+4]]=tab[n1];
  tab[vec[n1][n2]]=0;
  tab[n1]=0;

}




//**** mueve a un vecino dado
void mueve(int n1, int n2)
{
  
  tab[vec[n1][n2]]=tab[n1];
  tab[n1]=0;

}


//**** busca un valor aleatorio no repetido entre 0 y N-1
int aleat_iN(int request)
{
  int i, val=-1;

  if (request==0)
    for (i=0;i<N;i++) iN[i]=-1;
  else
    do
      {
	val=floor(FRANDOM*N);
	for (i=0;i<N;i++) 
	  if (val==iN[i]) val=-1;
      } while (val==-1);

  for (i=N-1;i>0;i--) iN[i]=iN[i-1];
  iN[0]=val;

  return val;
}


//**** busca un valor aleatorio no repetido entre 0 y 4
int aleat_jZ(int request)
{
  int i, val=-1;

  if (request==0)
    for (i=0;i<4;i++) jZ[i]=-1;
  else
    do
      {
	val=floor(FRANDOM*4);
	for (i=0;i<4;i++) 
	  if (val==jZ[i]) val=-1;
      } while (val==-1);

  for (i=4-1;i>0;i--) jZ[i]=jZ[i-1];
  jZ[0]=val;

  return val;
}






//**** hace una movida completamente aleatoria sm=0 o sin comprometer ficha sm=1
int aleat(int ficha, int sm)
{
  int i, j, c=0;
  int nsit, nvec;


  aleat_iN(0);
  for (i=0;i<N;i++)
    {
      nsit=aleat_iN(1);      
      if (tab[nsit]==ficha)
	{
	  aleat_jZ(0);
	  for (j=0;j<4;j++)
	    {
	      nvec=aleat_jZ(1);
	      if (eval_move(nsit,nvec)==1)
		if (sm==0)
		  {
		    mueve(nsit,nvec);
		    c=1;
		    j=4;
		    i=N;
		  }
		else if (amenaza(nsit,nvec)!=1)
		  {
		    mueve(nsit,nvec);
		    c=1;
		    j=4;
		    i=N;
		  }
	    }
	}
    }
  
  return c;
}





//**** evalua  si una ficha esta amenazada (al moverse a la direccion ve)
int amenaza(int n1, int ve)
{
  int i, am=0;

  if (ve==-1) // amenaza a la ficha donde esta
    {
      if (vec[n1][0]>0&&vec[n1][2]>0) 
	if (tab[vec[n1][0]]+tab[vec[n1][2]]==-tab[n1]) am=1;
      
      if (vec[n1][1]>0&&vec[n1][3]>0) 
	if (tab[vec[n1][1]]+tab[vec[n1][3]]==-tab[n1]) am=1;
    }
  else // amenaza a la ficha en la posicion ve: ALGORITMO RECURSIVO.
    {
      mueve(n1,ve);
      am=amenaza(vec[n1][ve],-1);
      mueve(vec[n1][ve],ve+2-(div(ve,2).quot*4)); //buscando el vecino conjugado
    }

  return am;
}





//**** hace jugada de defensa si puede
int defensa(int ficha)
{
  int nsit, nvec, i, j, c=0;
  
  
  aleat_iN(0);
  for (i=0;i<N;i++)
    {
      nsit=aleat_iN(1);      
      if (tab[nsit]==ficha)
	if (amenaza(nsit,-1))
	  {
	    aleat_jZ(0);
	    for (j=0;j<4;j++)
	      {
		nvec=aleat_jZ(1);
		if (eval_move(nsit,nvec)==1)
		  if (amenaza(nsit,nvec)!=1)
		    {
		      mueve(nsit,nvec);
		      c=1;
		      j=4;
		      i=N;
		    }
	      }
	  }
    }
  
  
  if (c==0) c=aleat(ficha,1); // aleatorio defensivo (no regalar)

  return c;
}





//***** algoritmo principal de la jugada
int jugada(int t)
{
  int f=1, ficha;
  int n1,n2;

  ficha=pow(-1,t+(1-salida)/2);

  if (comida(&n1,&n2,ficha)) come(n1,n2);
  else
    //if (!comida(&n1,&n2,-ficha)) f=aleat(ficha,0); //aleatorio estricto
    //else
    if (FRANDOM<(ficha>0?P1:P2)) f=defensa(ficha); //juega defensivamente
    else f=aleat(ficha,0); //juega estrictamente aleatorio
  
  return (f);
}




//**** imprime en el fichero de juego
void print_tablero(int ii)
{
  FILE *opfph;
  char phfile[40];
  int i;


  sprintf(phfile,"%s/tableros/juego%i.dat",dir,ii+1);  
  opfph = fopen(phfile, "a");

  for (i=0;i<N;i++) fprintf(opfph,"%i\t",tab[i]);

  fprintf(opfph, "\n");    
  fclose(opfph);  
  
}



//**** imprime en el fichero de tiempos
void print_tiempo(int t)
{
  FILE *opfph;
  char phfile[40];
  int i;


  sprintf(phfile,"%s/tiempos.dat",dir);  
  opfph = fopen(phfile, "a");
  fprintf(opfph,"%i\n",t);
  fclose(opfph);  
  
}


//**** imprime en el fichero de ventajas
void print_ventaja(int mode)
{
  FILE *opfph;
  char phfile[40];
  int i;

  sprintf(phfile,"%s/ventajas.dat",dir);  

  if (mode==0)
    {
      opfph = fopen(phfile, "a");
      fprintf(opfph,"\n");
      fclose(opfph);  
    }
  else
    {
      opfph = fopen(phfile, "a");
      fprintf(opfph,"%2.3f\t",set_ventaja());
      fclose(opfph);  
    }

}


//**** devuelve la ventaja actual
double set_ventaja()
{
  int i;
  double ven=0.0;

  for (i=0;i<N;i++) ven+=1.0*tab[i];

  return (1.0*ven);
}


//**** pone al tablero en la posicion inicial
void init_fichas()
{
  int i;

  
  for (i=0;i<N;i++) tab[i]=0;
  for (i=0;i<12;i++) tab[i]=1;
  for (i=N-12;i<N;i++) tab[i]=-1;

}



//**** inicializa la lista de vecinos y pone tab a cero 
void init_vec()
{
  int x,y,k,xx,yy;

  for (x=0;x<N;x++)
    for (y=0;y<8;y++)
      vec[x][y]=-1;

  k=0;

  for (y=0;y<l;y++)
    for (x=0;x<l;x++)
      if (div(x+y,2).rem==0)
	{
	  //primeros vecinos en sentido horario
	  xx=x+1;
	  yy=y-1;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][0]=yy*l+xx;
	  xx=x+1;
	  yy=y+1;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][1]=yy*l+xx;
	  xx=x-1;
	  yy=y+1;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][2]=yy*l+xx;
	  xx=x-1;
	  yy=y-1;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][3]=yy*l+xx;

	  //segundos vecinos en sentido horario
	  xx=x+2;
	  yy=y-2;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][4]=yy*l+xx;
	  xx=x+2;
	  yy=y+2;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][5]=yy*l+xx;
	  xx=x-2;
	  yy=y+2;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][6]=yy*l+xx;
	  xx=x-2;
	  yy=y-2;
	  if (xx>=0&&xx<l&&yy>=0&&yy<l) vec[k][7]=yy*l+xx;


	  tab[k]=y*l+x; //guarda los numeros de casillas transitables

	  k++;
	}
  
  for (k=0;k<N;k++)
    for (x=0;x<N;x++)
      for (y=0;y<8;y++)
	if (vec[x][y]==tab[k]) vec[x][y]=k;

  for (k=0;k<N;k++) tab[k]=0;

}





//************************************
void make_files()
{
    FILE *opf;
    char order[99], rfile[99];

 
    sprintf(order,"mkdir %s",dir);
    system(order); 
    sprintf(order,"mkdir %s/tableros",dir);
    system(order); 




    sprintf(rfile,"%s/README.dat",dir);        
    opf = fopen(rfile, "w");

    fprintf(opf,"*********************************************************\n");
    fprintf(opf,"\n");
    fprintf(opf,"parametros explicitos\n");
    fprintf(opf,"\n");
    fprintf(opf,"   p1(blancas) = %f\n", P1);
    fprintf(opf,"    p2(negras) = %f\n", P2);
    fprintf(opf,"          nexp = %i\n", nexp);
    fprintf(opf,"          seed = %u\n", myrand_back);
    fprintf(opf,"\n");
    fprintf(opf,"\n");
    fprintf(opf,"\n");
    fprintf(opf,"\n");
    fclose(opf);
}

