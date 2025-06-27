#include <iostream>
#include <string>
using namespace std;

// Estructura del nodo del árbol genealógico
struct Nodo {
    string nombre;
    string codigo;  // Código ancestral (ej: "1.2.1")
    Nodo* izquierda;
    Nodo* derecha;
};

// Función para generar el código ancestral
string generarCodigo(Nodo* padre, bool esHijoIzquierdo) {
    if (padre == NULL) return "1";  // Fundador
    return padre->codigo + (esHijoIzquierdo ? ".1" : ".2");
}

// Crear nuevo nodo con nombre y código
Nodo* crearNodo(string nombre, Nodo* padre = NULL, bool esHijoIzquierdo = true) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->codigo = generarCodigo(padre, esHijoIzquierdo);
    nuevo->izquierda = nuevo->derecha = NULL;
    return nuevo;
}

// Insertar un nodo en el ABB
Nodo* insertar(Nodo* raiz, string nombre, Nodo* padre = NULL, bool esHijoIzquierdo = true) {
    if (raiz == NULL) return crearNodo(nombre, padre, esHijoIzquierdo);
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, raiz, true);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, raiz, false);
    return raiz;
}

// Mostrar la información de un nodo
void mostrarNodo(Nodo* nodo) {
    if (nodo != NULL)
        cout << "Nombre: " << nodo->nombre << " | Código Ancestral: " << nodo->codigo << endl;
}

// Recorridos
void preorden(Nodo* raiz) {
    if (raiz) {
        mostrarNodo(raiz);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void inorden(Nodo* raiz) {
    if (raiz) {
        inorden(raiz->izquierda);
        mostrarNodo(raiz);
        inorden(raiz->derecha);
    }
}

void postorden(Nodo* raiz) {
    if (raiz) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        mostrarNodo(raiz);
    }
}

// Buscar por nombre exacto
Nodo* buscar(Nodo* raiz, string nombre) {
    if (!raiz) return NULL;
    if (raiz->nombre == nombre) return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);
    else
        return buscar(raiz->derecha, nombre);
}

// Buscar por apellido en preorden
void buscarPorApellido(Nodo* raiz, const string& apellido) {
    if (raiz) {
        size_t pos = raiz->nombre.find_last_of(' ');
        if (pos != string::npos && raiz->nombre.substr(pos + 1) == apellido)
            mostrarNodo(raiz);
        buscarPorApellido(raiz->izquierda, apellido);
        buscarPorApellido(raiz->derecha, apellido);
    }
}

// Buscar por apellido en inorden
void buscarPorApellidoInorden(Nodo* raiz, const string& apellido) {
    if (raiz) {
        buscarPorApellidoInorden(raiz->izquierda, apellido);
        size_t pos = raiz->nombre.find_last_of(' ');
        if (pos != string::npos && raiz->nombre.substr(pos + 1) == apellido)
            mostrarNodo(raiz);
        buscarPorApellidoInorden(raiz->derecha, apellido);
    }
}

// Buscar por apellido en postorden
void buscarPorApellidoPostorden(Nodo* raiz, const string& apellido) {
    if (raiz) {
        buscarPorApellidoPostorden(raiz->izquierda, apellido);
        buscarPorApellidoPostorden(raiz->derecha, apellido);
        size_t pos = raiz->nombre.find_last_of(' ');
        if (pos != string::npos && raiz->nombre.substr(pos + 1) == apellido)
            mostrarNodo(raiz);
    }
}

// Eliminar un nodo del árbol
Nodo* eliminar(Nodo* raiz, string nombre) {
    if (!raiz) return NULL;

    if (nombre < raiz->nombre)
        raiz->izquierda = eliminar(raiz->izquierda, nombre);
    else if (nombre > raiz->nombre)
        raiz->derecha = eliminar(raiz->derecha, nombre);
    else {
        // Caso sin hijos
        if (!raiz->izquierda && !raiz->derecha) {
            delete raiz;
            return NULL;
        }
        // Un solo hijo
        if (!raiz->izquierda) {
            Nodo* temp = raiz->derecha;
            delete raiz;
            return temp;
        }
        if (!raiz->derecha) {
            Nodo* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        // Dos hijos
        Nodo* sucesor = raiz->derecha;
        while (sucesor->izquierda)
            sucesor = sucesor->izquierda;

        raiz->nombre = sucesor->nombre;
        raiz->codigo = sucesor->codigo;
        raiz->derecha = eliminar(raiz->derecha, sucesor->nombre);
    }
    return raiz;
}

// Mostrar ancestros a partir del código ancestral
void mostrarAncestros(Nodo* raiz, string codigo) {
    size_t pos = codigo.find_last_of('.');
    if (pos != string::npos) {
        string codigoPadre = codigo.substr(0, pos);
        cout << "Ancestros de " << codigo << ":\n";
        while (!codigoPadre.empty()) {
            cout << "- Generación " << codigoPadre << endl;
            pos = codigoPadre.find_last_of('.');
            if (pos == string::npos) break;
            codigoPadre = codigoPadre.substr(0, pos);
        }
        cout << "- Fundador (1)\n";
    } else {
        cout << "Es el fundador, no tiene ancestros.\n";
    }
}

// Mostrar árbol visualmente (rotado)
void mostrarArbolVisual(Nodo* raiz, int espacio = 0, bool esHijoIzquierdo = false) {
    if (!raiz) return;
    espacio += 5;
    mostrarArbolVisual(raiz->izquierda, espacio, true);
    cout << endl;
    for (int i = 5; i < espacio; i++) cout << " ";
    cout << "+-- " << raiz->nombre << " (" << raiz->codigo << ")" << endl;
    mostrarArbolVisual(raiz->derecha, espacio, false);
}

// Liberar memoria del árbol
void liberar(Nodo* raiz) {
    if (raiz) {
        liberar(raiz->izquierda);
        liberar(raiz->derecha);
        delete raiz;
    }
}

// Menú principal
int main() {
    Nodo* raiz = NULL;
    int opcion;
    string nombre;

    // Inicialización de miembros
    raiz = insertar(raiz, "Manco Capac");
    insertar(raiz, "Sinchi Roca");
    insertar(raiz, "Lloque Yupanqui");
    insertar(raiz, "Mayta Capac");
    insertar(raiz, "Capac Yupanqui");
    insertar(raiz, "Inca Roca");
    insertar(raiz, "Yahuar Huacac");

    cout << "Arbol Genealogico Inca con Codigos Ancestrales\n";

    do {
        cout << "\n--- Menu ---\n";
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
        cout << "11. Mostrar Arbol Visual\n";
        cout << "12. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
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
                    if (padre) {
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
            case 2: preorden(raiz); break;
            case 3: inorden(raiz); break;
            case 4: postorden(raiz); break;
            case 5: {
                cout << "Ingrese nombre a buscar: ";
                getline(cin, nombre);
                Nodo* nodo = buscar(raiz, nombre);
                if (nodo) mostrarNodo(nodo);
                else cout << nombre << " NO se encuentra en el árbol.\n";
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
                cout << nombre << " ha sido eliminado (si existía).\n";
                break;
            }
            case 10: {
                cout << "Ingrese codigo ancestral (ej: 1.2.1): ";
                string codigo;
                getline(cin, codigo);
                mostrarAncestros(raiz, codigo);
                break;
            }
            case 11:
                cout << "\nVisualización del Arbol Genealógico:\n";
                mostrarArbolVisual(raiz);
                break;
            case 12:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 12);

    liberar(raiz);
    return 0;
}

