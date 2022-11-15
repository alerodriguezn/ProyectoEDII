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

Lugar* grafo;


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

void insertarLugar(string nombre){
    struct Lugar *nuevoLugar = new Lugar(nombre);
    nuevoLugar->sig = grafo;
    grafo = nuevoLugar;
}

void modificarLugar(string lugar, string nuevoLugar) {
    struct Lugar*temp = grafo;
    while (temp != NULL) {
        if (temp->nombreLugar == lugar) {
            temp->nombreLugar = nuevoLugar;
            cout << "\nEl lugar se ha modificado correctamente";
        }
        temp = temp->sig;
    }
}

void eliminarLugar(string lugar) {
    struct Lugar*temp = grafo;
    while (temp->sig != NULL) {
        if (temp->sig->nombreLugar == lugar) {
            temp->sig = temp->sig->sig;
            cout << "\nEl lugar se ha eliminado correctamente";
        }
        temp = temp->sig;
    }    
}

void imprimirLugares() {
    struct Lugar*temp = grafo;
    cout << endl;
    while (temp != NULL) {
        cout << temp->nombreLugar << endl;
        temp = temp->sig;
    }
}

struct Lugar *buscarLugar(string origen){
    struct Lugar *temp = grafo;
    while (temp != NULL)    {
        if (temp->nombreLugar == origen)
            return temp;

        temp = temp->sig;
    }
    cout << "\nNo se encontró el lugar";
    return NULL;
}

void insertarArco(string origen, int distancia, string destino){
    struct Lugar *lugarOrigen = buscarLugar(origen);
    struct Lugar *lugarDestino = buscarLugar(destino);

    if(lugarOrigen== NULL){
        cout<<"\nNo se encuentra el origen.";
        return;
    }
    if(lugarDestino == NULL){
        cout<<"\nNo se encuentra el destino.";
        return;
    }
    struct Arco *nuevoArco = new Arco(distancia, destino);

    nuevoArco->sig = lugarOrigen->sublistaArcos;
    lugarOrigen->sublistaArcos = nuevoArco;
}

void modificarArco(string origen, int nuevaDistancia, string destino) {
    struct Lugar*temp = grafo;
    while (temp != NULL) {
        if (temp->nombreLugar == origen) {
            struct Arco*tempA = temp->sublistaArcos;
            while (tempA != NULL) {
                if (tempA->destino == destino) {
                    tempA->distancia = nuevaDistancia;
                    cout << "\nLa distancia del arco ha sido modificada";
                }
                tempA = tempA->sig;
            }
        }
        temp = temp->sig;
    }
}

void imprimirArcos() {
    struct Lugar*temp = grafo;
    cout << endl;
    while (temp != NULL) {
        struct Arco*tempA = temp->sublistaArcos;
        while (tempA != NULL) {
            cout << temp->nombreLugar << " - ";
            cout << tempA->distancia << " - ";
            cout << tempA->destino << endl;
            tempA = tempA->sig;
        }
        temp = temp->sig;
    }
}


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

void cargarDatos() {
    insertarLugar("A");
    insertarLugar("B");
    insertarLugar("C");
    insertarLugar("D");
    insertarLugar("E");

    insertarArco("A", 12, "B");
    insertarArco("A", 44, "E");
    insertarArco("B", 20, "C");
    insertarArco("B", 47, "D");
    insertarArco("C", 17, "A");
    insertarArco("C", 19, "D");
    insertarArco("D", 34, "E");
    insertarArco("D", 38, "B");
    insertarArco("E", 55, "C");
    insertarArco("E", 7, "A");

    cout << "\nLos datos se cargaron correctamente";
}

int main() {
    cargarDatos();

    modificarLugar("D", "NuevoD");
    eliminarLugar("C");
    cout << "\n\nImprimiendo los lugares del grafo";
    imprimirLugares();

    modificarArco("NuevoD", 10000, "E");
    cout << "\n\nImprimiendo los arcos del grafo";
    imprimirArcos();

    cout << endl << endl;

    crearPersona("Alejandro", NULL);
    editarPersona("Alejandro", "Alejandro2", NULL);
    cout<<listaPersonas->nombre;
    return 0;
   
}
