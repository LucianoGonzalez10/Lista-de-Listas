#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
    char materia[40];
    int idMateria;
} registroArchivo;

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
} notas;

typedef struct nodo
{
    notas dato;
    struct nodo * siguiente;
} nodo;

typedef struct
{
    char materia[40];
    int idMateria;
} materia;

typedef struct nodo2
{
    materia datito;
    struct nodo2 * siguiente;
    nodo * lista;
} nodo2;

nodo * iniclista();
nodo2 * iniclista2();
nodo * crearNodo(notas dato);
nodo2 * crearNodo2(materia datito);
nodo2 * cargarDatos(nodo2 * lista2, char nombreAr[]);
nodo2 * alta(nodo2 * lista2, notas datito, materia datazo);
nodo2 * buscarUltimo2(nodo2 * lista2);
nodo * buscarUltimo(nodo * lista);
nodo * agregarFinal(nodo * lista, nodo * nuevo);
nodo2 * agregarFinal2(nodo2 * lista2, nodo2 * nuevo);
nodo2 * buscarMateria(nodo2 * lista2, int dato);
void mostrarListas(nodo2 * lista2);
nodo * agregarPrincipio(nodo * lista, nodo * nuevo);
nodo2 * agregarPrincipio2(nodo2 * lista2, nodo2 * nuevo);

int main()
{
    char nombreAr[] = "Archivo alumnos";
    nodo2 * lista2 = iniclista2();
    lista2 = cargarDatos(lista2, nombreAr);
    mostrarListas(lista2);
    // mostrar(nombreAr);
    return 0;
}

nodo * iniclista()
{
    return NULL;
}

nodo2 * iniclista2()
{
    return NULL;
}

nodo * crearNodo(notas dato)
{
    nodo * aux = (nodo*) malloc(sizeof(nodo));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodo2 * crearNodo2(materia datito)
{
    nodo2 * aux = (nodo2*) malloc(sizeof(nodo2));
    aux->datito = datito;
    aux->siguiente = NULL;
    aux->lista = iniclista();
    return aux;
}

nodo2 * cargarDatos(nodo2 * lista2, char nombreAr[])
{
    registroArchivo dato;
    notas datito;
    materia datazo;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&dato, sizeof(registroArchivo),1, buffer ) > 0)
        {
            strcpy(datito.nombreApe, dato.nombreApe);
            datito.legajo = dato.legajo;
            datito.nota = dato.nota;
            datazo.idMateria = dato.idMateria;
            strcpy(datazo.materia, dato.materia);
            lista2 = alta(lista2, datito, datazo);
        }
        fclose(buffer);
    }
    return lista2;
}

nodo2 * alta(nodo2 * lista2, notas datito, materia datazo)
{
    nodo * aux = crearNodo(datito);
    nodo2 * buscado = buscarMateria(lista2, datazo.idMateria);
    if(buscado == NULL)
    {
        nodo2 * nuevo = crearNodo2(datazo);
        lista2 = agregarPrincipio2(lista2, nuevo);
        buscado=lista2;
   }
        buscado->lista = agregarFinal(buscado->lista, aux);

    return lista2;
}

nodo * buscarUltimo(nodo * lista)
{
    nodo * seg = lista;
    if(lista != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }

    return seg;
}

nodo2 * buscarUltimo2(nodo2 * lista2)
{
    nodo2 * seg = lista2;
    if(lista2 != NULL)
    {
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    }

    return seg;
}

nodo * agregarFinal(nodo * lista, nodo * nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nodo * ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevo;
    }
    return lista;
}

nodo2 * agregarFinal2(nodo2 * lista2, nodo2 * nuevo)
{
    if(lista2 == NULL)
    {
        lista2 = nuevo;
    }
    else
    {
        nodo2 * ultimo = buscarUltimo2(lista2);
        ultimo->siguiente = nuevo;
    }
    return lista2;
}

nodo2 * buscarMateria(nodo2 * lista2, int dato)
{
    nodo2 * seg = lista2;
    nodo2 * buscado = NULL;
    if(seg != NULL)
    {
        while(seg != NULL && buscado == NULL)
        {
            if(seg->datito.idMateria == dato)
            {
                buscado = seg;
            }
            seg = seg->siguiente;
        }
    }
    return buscado;
}


void mostrarListas(nodo2 * lista2)
{
    if(lista2 != NULL)
    {
        printf("MATERIA: %s \n \n", lista2->datito.materia);
        while(lista2->lista != NULL)
        {
            printf("Nombre: %s \n", lista2->lista->dato.nombreApe);
            printf("Nota: %d \n", lista2->lista->dato.nota);
            printf("Legajo: %d \n", lista2->lista->dato.legajo);
            printf("------------------------- \n");
            lista2->lista = lista2->lista->siguiente;
        }
        mostrarListas(lista2->siguiente);
    }
}

void mostrar(char nombreAr[])
{
    registroArchivo dato;
    FILE * buffer = fopen(nombreAr, "rb");
    if(buffer)
    {
        while(fread(&dato, sizeof(registroArchivo),1, buffer ) > 0)
        {
            printf("Materia: %s \n", dato.materia);
            printf("ID Materia: %d \n", dato.idMateria);
            printf("Nombre: %s \n", dato.nombreApe);
            printf("Nota: %d \n", dato.nota);
            printf("Legajo: %d \n", dato.legajo);
            printf("-----------------------------\n");
        }
        fclose(buffer);
    }
}

nodo2 * agregarPrincipio2(nodo2 * lista2, nodo2 * nuevo){
    if(lista2 == NULL){
        lista2 = nuevo;
    }
    else{
        nuevo->siguiente = lista2;
        lista2 = nuevo;
    }
    return lista2;
}

nodo * agregarPrincipio(nodo * lista, nodo * nuevo){
    if(lista == NULL){
        lista = nuevo;
    }
    else{
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}
