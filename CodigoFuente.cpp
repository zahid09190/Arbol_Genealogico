#include <iostream>
using namespace std;

struct Nodo {
    string nombre;
    Nodo* izquierda;
    Nodo* derecha;
};

// Crear nuevo nodo
Nodo* crearNodo(string nombre) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->izquierda = nuevo->derecha = NULL;
    return nuevo;
}

// Insertar nodo en ABB
Nodo* insertar(Nodo* raiz, string nombre) {
    if (raiz == NULL) return crearNodo(nombre);
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre);
    else
        raiz->derecha = insertar(raiz->derecha, nombre);
    return raiz;
}

// Recorrido inorden
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        cout << raiz->nombre << " ";
        inorden(raiz->derecha);
    }
}

// Buscar miembro
bool pertenece(Nodo* raiz, string nombre) {
    if (raiz == NULL) return false;
    if (raiz->nombre == nombre) return true;
    if (nombre < raiz->nombre)
        return pertenece(raiz->izquierda, nombre);
    else
        return pertenece(raiz->derecha, nombre);
}

int main() {
    Nodo* raiz = NULL;
    raiz = insertar(raiz, "Atahualpa");
    raiz = insertar(raiz, "Huayna Capac");
    raiz = insertar(raiz, "Tupac Yupanqui");

    cout << "Recorrido Inorden: ";
    inorden(raiz);
    cout << endl;

    string buscar = "Huayna Capac";
    if (pertenece(raiz, buscar))
        cout << buscar << " pertenece al árbol." << endl;
    else
        cout << buscar << " NO pertenece al árbol." << endl;

    return 0;
}
