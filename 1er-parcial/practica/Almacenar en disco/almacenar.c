/******************************************************************************
Almacenar en Disco: open, write/read, close 
v 1.0
*******************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
struct ejemplo{
  char x[10];
  int y;
  float z;
};

void Almacenar (struct ejemplo Datos[3]);
void Leer (struct ejemplo Datos[3]);
int main()
{
    struct ejemplo Datos[3]={{"pato",12,3.4}, {"gato",7,1.2},{"perro",4,1.1}};
    Leer( Datos);
    //Almacenar ( Datos );
    printf("Info -- %s %i \n", Datos[0].x,Datos[0].y);
    printf("Info -- %s %i \n", Datos[1].x,Datos[1].y);
    printf("Info -- %s %i \n", Datos[2].x,Datos[2].y);
    system("ls -l");
    return 0;
}

void Leer (struct ejemplo Datos[3])
{
    int archivo;
    archivo=open("ganadores.zrz",O_RDONLY );
    if (archivo == -1)
    {
        printf("no se pudo");
    }
    else{
        read (archivo, Datos, sizeof(struct ejemplo)*3);
       // fprintf(archivo,"%s %i puntos\n", Datos[0].x,Datos[0].y)
        close(archivo);
        
    }
}

void Almacenar (struct ejemplo Datos[3])
{
    int archivo;
    archivo=open("ganadores.zrz",O_WRONLY | O_CREAT);
    if (archivo == -1)
    {
        printf("no se pudo");
    }
    else{
        write (archivo, Datos, sizeof(struct ejemplo)*3 );
       // fprintf(archivo,"%s %i puntos\n", Datos[0].x,Datos[0].y)
        close(archivo);
        
    }
}