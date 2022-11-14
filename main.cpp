#include <iostream>
#include <string>

using namespace std;


struct Lugar{
    string nombreLugar;
    struct Lugar* sig; 
    struct Arco* sublistaArcos; 
    bool visitado;
    Lugar(string nombre){
        nombreLugar = nombre;
        sig = NULL;
        sublistaArcos = NULL;
        visitado = false;
    }
}*listaLugares;


struct Arco{
    int distancia;
    string destino;
    struct Arco* sig;
    Arco(int dist,string dest){
        distancia = dist;
        destino = dest;
        sig = NULL;
    }
};


struct Persona{
    string nombre;
    struct Lugar*ubicacionActual;
    struct Persona*sig;
    Persona(string nomb,Lugar*ubicacion){
        nombre= nomb;
        ubicacionActual = ubicacion;
        sig = NULL;
    }

}*listaPersonas;


void crearPersona(string nombre,Lugar*ubicacion){
    Persona*nuevaPersona = new Persona(nombre,ubicacion);
    nuevaPersona->sig = listaPersonas;
    listaPersonas = nuevaPersona;
}

Persona*buscarPersona(string nombre){
    if(listaPersonas == NULL){
        return NULL;
    }
    Persona*personaTemp = listaPersonas;
    while(personaTemp != NULL){
        if(personaTemp->nombre == nombre){
            return personaTemp;
        }
    }
    return NULL;
}


void editarPersona(string nombre,string nombreN,Lugar*ubicacion){
    Persona*p = buscarPersona(nombre);
    if(p == NULL){
        cout<<"\nNo se encontró a la persona"<<endl;
    }
    else{
        p->nombre = nombreN;
        p->ubicacionActual = ubicacion;
    }
}


void eliminarPersona(string nombre){
    Persona*p = buscarPersona(nombre);
    if (p == NULL){
        cout<<"\nNo se encontró a la persona";
    }
    else{
        if (listaPersonas->nombre == nombre){
            listaPersonas = listaPersonas->sig;
        }
        else{
            Persona*temp = listaPersonas;
            Persona*ant = NULL;
            while((temp!=NULL)&&(temp->nombre!=nombre)){
                ant = temp;
                temp = temp->sig;
            }
            if(temp ==NULL){
                cout<<"\nNo se encontró a la persona";

            }else{
                ant->sig = temp->sig;
            }
        }
    }
}

int main() {
    crearPersona("Alejandro",NULL);
    editarPersona("Alejandro","Alejandro2",NULL);
    cout<<listaPersonas->nombre;
    return 0;
   
}