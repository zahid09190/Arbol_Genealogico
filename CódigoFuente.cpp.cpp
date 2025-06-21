
#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    string nombre;
    string codigo;  // Código ancestral (ej: "1.2.1")
    Nodo* izquierda;
    Nodo* derecha;
};

// Función para extraer el apellido (sin usar vector)
string extraerApellido(const string& nombreCompleto) {
    size_t pos = nombreCompleto.find_last_of(' ');
    if (pos != string::npos) {
        return nombreCompleto.substr(pos + 1);
    }
    return ""; // Si no tiene apellido
}

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
        cout << "Nombre: " << nodo->nombre << " | Apellido: " << extraerApellido(nodo->nombre) 
             << " | Código: " << nodo->codigo << endl;
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
void buscarPorApellidoPreorden(Nodo* raiz, const string& apellido, int& contador) {
    if (raiz != NULL) {
        if (extraerApellido(raiz->nombre) == apellido) {
            mostrarNodo(raiz);
            contador++;
        }
        buscarPorApellidoPreorden(raiz->izquierda, apellido, contador);
        buscarPorApellidoPreorden(raiz->derecha, apellido, contador);
    }
}

// Buscar por apellido - Inorden
void buscarPorApellidoInorden(Nodo* raiz, const string& apellido, int& contador) {
    if (raiz != NULL) {
        buscarPorApellidoInorden(raiz->izquierda, apellido, contador);
        if (extraerApellido(raiz->nombre) == apellido) {
            mostrarNodo(raiz);
            contador++;
        }
        buscarPorApellidoInorden(raiz->derecha, apellido, contador);
    }
}

// Buscar por apellido - Postorden
void buscarPorApellidoPostorden(Nodo* raiz, const string& apellido, int& contador) {
    if (raiz != NULL) {
        buscarPorApellidoPostorden(raiz->izquierda, apellido, contador);
        buscarPorApellidoPostorden(raiz->derecha, apellido, contador);
        if (extraerApellido(raiz->nombre) == apellido) {
            mostrarNodo(raiz);
            contador++;
        }
    }
}

// Eliminar miembro del árbol
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

int main() {
    Nodo* raiz = NULL;
    int opcion;
    string nombre;

    cout << "Árbol Genealógico con Búsqueda por Apellidos\n";

    do {
        cout << "\n--- Menú ---\n";
        cout << "1. Agregar miembro\n";
        cout << "2. Mostrar recorrido preorden\n";
        cout << "3. Mostrar recorrido inorden\n";
        cout << "4. Mostrar recorrido postorden\n";
        cout << "5. Buscar miembro por nombre completo\n";
        cout << "6. Buscar miembros por apellido (preorden)\n";
        cout << "7. Buscar miembros por apellido (inorden)\n";
        cout << "8. Buscar miembros por apellido (postorden)\n";
        cout << "9. Eliminar miembro\n";
        cout << "10. Mostrar ancestros de un miembro (por código)\n";
        cout << "11. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                cout << "Ingrese nombre completo (nombre y apellido): ";
                getline(cin, nombre);
                
                if (raiz == NULL) {
                    raiz = insertar(raiz, nombre);
                    cout << "Miembro agregado como fundador.\n";
                } else {
                    string padreNombre;
                    cout << "Ingrese nombre completo del padre: ";
                    getline(cin, padreNombre);
                    
                    Nodo* padre = buscar(raiz, padreNombre);
                    if (padre != NULL) {
                        char lado;
                        cout << "¿Es hijo izquierdo (I) o derecho (D)? ";
                        cin >> lado;
                        cin.ignore();
                        if (toupper(lado) == 'I') {
                            if (padre->izquierda == NULL) {
                                padre->izquierda = insertar(padre->izquierda, nombre, padre, true);
                                cout << "Miembro agregado como hijo izquierdo.\n";
                            } else {
                                cout << "El padre ya tiene un hijo izquierdo.\n";
                            }
                        } else {
                            if (padre->derecha == NULL) {
                                padre->derecha = insertar(padre->derecha, nombre, padre, false);
                                cout << "Miembro agregado como hijo derecho.\n";
                            } else {
                                cout << "El padre ya tiene un hijo derecho.\n";
                            }
                        }
                    } else {
                        cout << "Padre no encontrado. No se agregó el miembro.\n";
                    }
                }
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
                cout << "Ingrese nombre completo a buscar: ";
                getline(cin, nombre);
                Nodo* encontrado = buscar(raiz, nombre);
                if (encontrado != NULL) {
                    mostrarNodo(encontrado);
                } else {
                    cout << nombre << " NO pertenece al árbol.\n";
                }
                break;
            }
            case 6: {
                cout << "Ingrese apellido a buscar (preorden): ";
                string apellido;
                getline(cin, apellido);
                int contador = 0;
                cout << "Resultados de búsqueda:\n";
                buscarPorApellidoPreorden(raiz, apellido, contador);
                if (contador == 0) {
                    cout << "No se encontraron miembros con el apellido '" << apellido << "'\n";
                } else {
                    cout << "Total encontrados: " << contador << endl;
                }
                break;
            }
            case 7: {
                cout << "Ingrese apellido a buscar (inorden): ";
                string apellido;
                getline(cin, apellido);
                int contador = 0;
                cout << "Resultados de búsqueda:\n";
                buscarPorApellidoInorden(raiz, apellido, contador);
                if (contador == 0) {
                    cout << "No se encontraron miembros con el apellido '" << apellido << "'\n";
                } else {
                    cout << "Total encontrados: " << contador << endl;
                }
                break;
            }
            case 8: {
                cout << "Ingrese apellido a buscar (postorden): ";
                string apellido;
                getline(cin, apellido);
                int contador = 0;
                cout << "Resultados de búsqueda:\n";
                buscarPorApellidoPostorden(raiz, apellido, contador);
                if (contador == 0) {
                    cout << "No se encontraron miembros con el apellido '" << apellido << "'\n";
                } else {
                    cout << "Total encontrados: " << contador << endl;
                }
                break;
            }
            case 9: {
                cout << "Ingrese nombre completo del miembro a eliminar: ";
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

