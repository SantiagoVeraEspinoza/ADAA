#define INF 99999

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 02/10/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de nodos
- v: Número de vértices

- m: Longitud de una matríz
- l: Longitud vector
*/


// Imprime una matrix - O(m^2)
template <typename T>
void printMatrix(vector <vector <T>> input)
{
    for (int i=0; i<input.size(); i++) // Itera por la longitud - O(m)
    {
        for (auto e:input[i]) // Itera por cada columna - O(m)
        {
            cout << e << " ";
        }
        cout << endl;
    }
}

// Imprime una matríz de adyacencia - O(nv)
void printAdj(vector<vector <pair <int, int>>> input)
{
    for (int i = 0; i < input.size(); i++) // Itera por cada vértice - O(n) = O(nv)
    {
        cout << i + 1 << " -> ";

        int cont = 0;
        for (auto pair:input[i]) // Itera por cada arista del vértice - O(v)
        {
            cout << pair.first + 1 << ": " << pair.second;
            if (cont < input[i].size() - 1) cout << ", ";
            cont++;
        }
        cout << endl;
    }
}

// Imprime un vector - O(l)
template <typename T>
void printVec(vector <T> input, string msg="Vector = ")
{
    cout << msg << "[ ";
    for (int i=0; i < input.size()-1; i++) cout << input[i] << ", "; // Itera por cada elemento de la lista - O(l)
    cout << input[input.size()-1] << " ]" << endl;
}

// Ordenar priority queue con segundo elemento - O(1)
struct CompareBySecond {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const { // Regresa un boleano con una comparación
        return lhs.second > rhs.second;  // '>' para orden descendente, '<' para orden ascendente
    }
};

// Dijkstra Algorithm - O((n + v)log(n + v))
vector <int> dijkstra(int start, vector<vector <pair <int, int>>> input)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareBySecond> pq; // Priority queue
    vector <bool> visited (input.size(), false); // Vector de vértices visitados - O(n)
    vector <int> res(input.size(), -1); // Vector con la respuesta para un vértice - O(n)

    pq.push(make_pair(start, 0)); // Introduce el primer elemento O(1)

    while (!pq.empty()) // Mientras el priority queue tenga elementos O(n + v) -> O((n + v)log(n + v))
    {
        pair <int, int> curr = pq.top(); // Obtiene el primer elemento de la pq - O(1)
        pq.pop(); // Popea el elemento - O(log(n + v))

        if (visited[curr.first]) continue; // Si ya fue visitado ignora el elemento
        visited[curr.first] = true;

        res[curr.first] = curr.second; // Guuarda el elemento en la respuesta - O(1)

        for (auto pair:input[curr.first]) // Itera por las aristas del vértice - O(v)
        {
            if (visited[pair.first]) continue; // Si fue visitado lo ignora - O(1)

            pq.push(make_pair(pair.first, pair.second + curr.second)); // Ingresa un nuevo elemento al pq - O(log(n + v))
        }
    }

    return res;
}

// Floyd Warshall Algorithm - O(2n + v + n^2 + n^3) -> O(n^3 + v) -> O(n^3)
vector <vector <int>> floydWarshall(vector<vector <pair <int, int>>> input)
{
    vector <vector <int>> res (input.size(), vector <int> (input.size(), INF)); // Crea una matríz respuesta nxn de numeros infinitos - O(n^2)

    for (int i=0; i<input.size(); i++) res[i][i] = 0; // Todos los elementos de la diagonal se establecen en 0 - O(n)

    for (int i=0; i<input.size(); i++) // Todos los elementos de la lista de ayacencia son ingresados a la respeusta - O(n) -> O(n + v)
    {
        for (auto pair:input[i]) // Por todos los elementos del vértice - O(v)
        {
            res[i][pair.first] = pair.second;
        }
    }

    for (int k=0; k<input.size(); k++) // Por todos los vértices - O(n) -> O(n^2) -> O(n^3)
    {
        for (int i=0; i<input.size(); i++) // Por todos los vértices - O(n) -> O(n^2)
        {
            for (int j=0; j<input.size(); j++)  // Por todos los vértices - O(n)
            {
                if (res[i][j] > res[i][k] + res[k][j]) res[i][j] = res[i][k] + res[k][j];
            }
        }
    }

    return res;
}

// Proceso principal - O()
void process()
{
    int n;

    cout << "Inserta número: "; // Inserta el número de vértices
    cin >> n;
    cout << endl;

    // Lista de adjacencia con pares (id, peso) - O(n)
    vector<vector <pair <int, int>>> adj(n);

    cout << "Inserta la matríz de adyacencia: " << endl;
    
    // Leer la matriz - O(n^2)
    for (int i = 0; i < n; i++) // Itera por la lista de adjacencia en vertical - O(n)
    {
        for (int j = 0; j < n; j++) // Itera por la lista en horizontal - O(n)
        {
            int in;
            cin >> in;

            if (i != j && in != -1) adj[i].push_back(make_pair(j, in));
        }
    }

    cout << endl << "Dijkstra:" << endl;

    for (int i=0; i<n; i++){ // Aplica Dijkstra en cada vértice - O(n) -> O(n(n + v)log(n + v)) - > O((n^2 + nv)log(n + v))
        vector <int> res = dijkstra(i, adj); // Aplica Dijkstra - O((n + v)log(n + v))

        for (int j=0; j<n; j++)
        {
            if (i==j) continue;

            cout << "node " << i+1 << " to node " << j+1 << ": " << res[j] << endl;
        }
    }

    cout << endl << "Floyd Warshall:" << endl;

    vector <vector <int>> floyd = floydWarshall(adj); // Aplica Floyd Warshall - O(n^3)

    printMatrix(floyd);
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