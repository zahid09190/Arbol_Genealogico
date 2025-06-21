#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    string nombre;
    string codigo;  // Código ancestral (ej: "1.2.1")
    Nodo* izquierda;
    Nodo* derecha;
};

// Generar código de ancestro
string generarCodigo(Nodo* padre, bool esHijoIzquierdo) {
    if (padre == NULL) return "1";
    return padre->codigo + (esHijoIzquierdo ? ".1" : ".2");
}

// Crear nuevo nodo
Nodo* crearNodo(string nombre, Nodo* padre = NULL, bool esHijoIzquierdo = true) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->codigo = generarCodigo(padre, esHijoIzquierdo);
    nuevo->izquierda = nuevo->derecha = NULL;
    return nuevo;
}

// Insertar en ABB
Nodo* insertar(Nodo* raiz, string nombre, Nodo* padre = NULL, bool esHijoIzquierdo = true) {
    if (raiz == NULL) return crearNodo(nombre, padre, esHijoIzquierdo);
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, raiz, true);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, raiz, false);
    return raiz;
}

// Mostrar un nodo
void mostrarNodo(Nodo* nodo) {
    if (nodo != NULL) {
        cout << "Nombre: " << nodo->nombre << " | Código Ancestral: " << nodo->codigo << endl;
    }
}

// Recorridos
void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        mostrarNodo(raiz);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        mostrarNodo(raiz);
        inorden(raiz->derecha);
    }
}
void postorden(Nodo* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        mostrarNodo(raiz);
    }
}

// Buscar por nombre exacto
Nodo* buscar(Nodo* raiz, string nombre) {
    if (raiz == NULL) return NULL;
    if (raiz->nombre == nombre) return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);
    else
        return buscar(raiz->derecha, nombre);
}

// Buscar por apellido - Preorden
void buscarPorApellido(Nodo* raiz, const string& apellido) {
    if (raiz != NULL) {
        size_t pos = raiz->nombre.find_last_of(' ');
        if (pos != string::npos && raiz->nombre.substr(pos + 1) == apellido)
            mostrarNodo(raiz);
        buscarPorApellido(raiz->izquierda, apellido);
        buscarPorApellido(raiz->derecha, apellido);
    }
}

// Buscar por apellido - Inorden
void buscarPorApellidoInorden(Nodo* raiz, const string& apellido) {
    if (raiz != NULL) {
        buscarPorApellidoInorden(raiz->izquierda, apellido);
        size_t pos = raiz->nombre.find_last_of(' ');
        if (pos != string::npos && raiz->nombre.substr(pos + 1) == apellido)
            mostrarNodo(raiz);
        buscarPorApellidoInorden(raiz->derecha, apellido);
    }
}

// Buscar por apellido - Postorden
void buscarPorApellidoPostorden(Nodo* raiz, const string& apellido) {
    if (raiz != NULL) {
        buscarPorApellidoPostorden(raiz->izquierda, apellido);
        buscarPorApellidoPostorden(raiz->derecha, apellido);
        size_t pos = raiz->nombre.find_last_of(' ');
        if (pos != string::npos && raiz->nombre.substr(pos + 1) == apellido)
            mostrarNodo(raiz);
    }
}

//Elimiar miembro del arbol
Nodo* eliminar(Nodo* raiz, string nombre) {
    if (raiz == NULL) return NULL;

    if (nombre < raiz->nombre)
        raiz->izquierda = eliminar(raiz->izquierda, nombre);
    else if (nombre > raiz->nombre)
        raiz->derecha = eliminar(raiz->derecha, nombre);
    else {
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz;
            return NULL;
        }
        if (raiz->izquierda == NULL) {
            Nodo* temp = raiz->derecha;
            delete raiz;
            return temp;
        }
        if (raiz->derecha == NULL) {
            Nodo* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }

        Nodo* sucesor = raiz->derecha;
        while (sucesor->izquierda != NULL)
            sucesor = sucesor->izquierda;
        
        // Copiar nombre y código del sucesor
        raiz->nombre = sucesor->nombre;
        raiz->codigo = sucesor->codigo;

        raiz->derecha = eliminar(raiz->derecha, sucesor->nombre);
    }
    return raiz;
}
// Mostrar ancestros desde código
void mostrarAncestros(Nodo* raiz, string codigo) {
    size_t pos = codigo.find_last_of('.');
    if (pos != string::npos) {
        string codigoPadre = codigo.substr(0, pos);
        cout << "Ancestros de " << codigo << ":" << endl;
        while (!codigoPadre.empty()) {
            cout << "- Generación " << codigoPadre << endl;
            pos = codigoPadre.find_last_of('.');
            if (pos == string::npos) break;
            codigoPadre = codigoPadre.substr(0, pos);
        }
        cout << "- Fundador (1)" << endl;
    } else {
        cout << "Es el fundador, no tiene ancestros." << endl;
    }
}

// Liberar memoria
void liberar(Nodo* raiz) {
    if (raiz != NULL) {
        liberar(raiz->izquierda);
        liberar(raiz->derecha);
        delete raiz;
    }
}

// MAIN
int main() {
    Nodo* raiz = NULL;
    int opcion;
    string nombre;

    // Miembros iniciales
    raiz = insertar(raiz, "Manco Cápac");
    insertar(raiz, "Sinchi Roca");
    insertar(raiz, "Lloque Yupanqui");
    insertar(raiz, "Mayta Cápac");
    insertar(raiz, "Cápac Yupanqui");
    insertar(raiz, "Inca Roca");
    insertar(raiz, "Yáhuar Huácac");

    cout << "Árbol Genealógico Inca con Códigos Ancestrales\n";

    do {
        cout << "\n--- Menú ---\n";
        cout << "1. Agregar miembro\n";
        cout << "2. Mostrar recorrido preorden\n";
        cout << "3. Mostrar recorrido inorden\n";
        cout << "4. Mostrar recorrido postorden\n";
        cout << "5. Buscar miembro por nombre\n";
        cout << "6. Buscar miembros por apellido (preorden)\n";
        cout << "7. Buscar miembros por apellido (inorden)\n";
        cout << "8. Buscar miembros por apellido (postorden)\n";
        cout << "9. Eliminar miembro\n";
        cout << "10. Mostrar ancestros de un miembro\n";
        cout << "11. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                cout << "Ingrese nombre del nuevo miembro: ";
                getline(cin, nombre);
                string padreNombre;
                cout << "Ingrese nombre del padre (deje vacío si es el fundador): ";
                getline(cin, padreNombre);
                
                if (padreNombre.empty()) {
                    raiz = insertar(raiz, nombre);
                } else {
                    Nodo* padre = buscar(raiz, padreNombre);
                    if (padre != NULL) {
                        char lado;
                        cout << "¿Es hijo izquierdo (I) o derecho (D)? ";
                        cin >> lado;
                        cin.ignore();
                        if (toupper(lado) == 'I') {
                            padre->izquierda = insertar(padre->izquierda, nombre, padre, true);
                        } else {
                            padre->derecha = insertar(padre->derecha, nombre, padre, false);
                        }
                    } else {
                        cout << "Padre no encontrado.\n";
                    }
                }
                cout << "Miembro agregado.\n";
                break;
            }
            case 2:
                cout << "Recorrido preorden:\n";
                preorden(raiz);
                break;
            case 3:
                cout << "Recorrido inorden:\n";
                inorden(raiz);
                break;
            case 4:
                cout << "Recorrido postorden:\n";
                postorden(raiz);
                break;
            case 5: {
                cout << "Ingrese nombre a buscar: ";
                getline(cin, nombre);
                Nodo* encontrado = buscar(raiz, nombre);
                if (encontrado != NULL)
                    mostrarNodo(encontrado);
                else
                    cout << nombre << " NO pertenece al árbol.\n";
                break;
            }
            case 6: {
                cout << "Apellido a buscar (preorden): ";
                string apellido;
                getline(cin, apellido);
                buscarPorApellido(raiz, apellido);
                break;
            }
            case 7: {
                cout << "Apellido a buscar (inorden): ";
                string apellido;
                getline(cin, apellido);
                buscarPorApellidoInorden(raiz, apellido);
                break;
            }
            case 8: {
                cout << "Apellido a buscar (postorden): ";
                string apellido;
                getline(cin, apellido);
                buscarPorApellidoPostorden(raiz, apellido);
                break;
            }
            case 9: {
			    cout << "Ingrese nombre del miembro a eliminar: ";
			    getline(cin, nombre);
			    raiz = eliminar(raiz, nombre);
			    cout << nombre << " ha sido eliminado (si existía en el árbol).\n";
			    break;
			}
            case 10: {
                cout << "Ingrese código ancestral (ej: 1.2.1): ";
                string codigo;
                getline(cin, codigo);
                mostrarAncestros(raiz, codigo);
                break;
            }
            case 11:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 11);

    liberar(raiz);
    return 0;
}

