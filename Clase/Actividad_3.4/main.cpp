#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 11/10/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de nodos
- m: Número de aristas

- v: Elementos en un vector
- e: Vecinos de un nodo
- c: Número de colores
*/

// Sobrecarga del cout para vectores - O(v)
template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    os << "[ ";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end()-1; ii++) // Itera por el vector - O(v)
    {
        os << *ii << ", ";
    }
    cout << v[v.size()-1];
    os << " ]";
    return os;
}

// Valida si un color se puede utilizar en un nodo - O(e)
bool canUseColor(vector <vector <int>> adj_list, int curr, int color, vector <int> colors) {
    for (auto n:adj_list[curr]) { // Itera por todos los vecinos del nodo - O(e)
        if (color == colors[n]) return false; // Algun vecino tiene el color a decidir
    }

    return true;
}

// Problema de desición del grafo - O(nc^n)
bool graphDecision(vector <vector <int>> adj_list, vector <int> colors, int n_colors, int curr) {
    if (curr == adj_list.size()) return true; // Si equivale al número de colores - O(1)
    for (int i=0; i<n_colors; i++) { // Por todos los colores - O(c)
        if (canUseColor(adj_list, curr, i, colors)) { // Identifica si se puede utilizar el color (para simplificar será n, asumiendo que se puede ir desde un vector hacia cualquier otro) - O(n)
            colors[curr] = i;
            if (graphDecision(adj_list, colors, n_colors, curr + 1)) return true; // Recursivo con uno arriba - O(nc^n)
            colors[curr] = -1;
        }
    }

    return false;
}

// Problema de optimización del grafo - O(n^2)
int GraphOptimization(vector <vector <int>> adj_list) {
    vector <int> colors(adj_list.size(), -1); // Inicializa el vector de colores - O(n)
    colors[0] = 1;

    int crom_num = 0;
    for (int i=1; i<adj_list.size(); i++) { // Itera por todos los elementos - O(n) -> O(n^2)
        vector <bool> assigned(adj_list.size(), false); // Crea un vector para los colores que ya han sido asignados - O(n)

        for (auto c:adj_list[i]) { // Itera por la lista - O(n)
            if (colors[c] != -1) assigned[colors[c]] = true; // Si ya ha sido asignado ese color se marca
        }

        int min_num;
        for (min_num = 1; min_num<=adj_list.size(); min_num++) { // Itera por el máximo posible número de colores de menor a mayor - O(n)
            if (assigned[min_num] == false) break; // Si un color no ha sido asignado, ese es el menor
        }

        if (min_num > crom_num) crom_num = min_num; // Actualiza el número cromático si este el mínimo es mayor a este
        colors[i] = min_num;
    }

    for (int i=0; i< adj_list.size(); i++) { // Imprime el resultado en cada nodo - O(n)
        cout << "Node " << i + 1 << " <-> Assigned Color: " << colors[i] << endl;
    }
    cout << "Max colors: " << crom_num << endl; // Número cromático
}

// Proceso principal - O(n^n)
void process()
{
    int n;

    cin >> n;

    vector <vector <int>> adj_list(n); // Crea una lista de adyacencia de tamaño n - O(n)
    
    for (int i = 0; i < n; i++) // Itera por la matríz de adyacencia dada - O(n) -> O(n^2)
    {
        for (int j = 0; j < n; j++) { // Itera por una fila de la matríz - O(n)
            int curr;
            cin >> curr;
            if (i == j) continue;
            if (curr == 1) adj_list[i].push_back(j); // Añade un nodo a la lista de adyacencia - O(1)
        }
    }

    // Optimización de Grafo

    cout << endl << "Graph Optimization Problem:" << endl;

    GraphOptimization(adj_list); // Ejecuta la optimización - O(n^2)

    // Desición con Grafo

    vector <int> colors(n, -1); // Inicializa el vector de colores - O(n)

    cout << endl << "Graph Decision Problem:" << endl;
    for (int i=0; i<n; i++) { // Itera por todos los posibles números de colores - O(n^n)
        cout << "The graph can be colored with " << i+1 << " color";
        if (i > 0) cout << "s";
        cout << "? "; 
        if (graphDecision(adj_list, colors, i+1, 0)) cout << "True" << endl; // Evalue el número de colores - O(nc^n) -> O(nn^n) -> O(n^n)
        else cout << "False" << endl;
    }

    // Permutaciones de Grafo

    cout << endl << "Graph Permutation Problem:" << endl;
}

#ifdef _WIN32
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    process();
}

#else

int main() 
{
    process();
}

#endif