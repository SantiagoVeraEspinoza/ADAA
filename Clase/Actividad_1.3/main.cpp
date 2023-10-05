#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 03/09/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Cantidad de columnas
- m: Cantidad de filas
*/

class node // Clase nodo, base para la resolución del problema
{
    private: // Contiene un apuntador a su padre (nullptr en caso de no tener), el contenido (o coordenadas) y sus hijos
        node *father;
        pair <int, int> content;
        vector <node*> childs;

    public:
        node() // Contructor por defecto
        {
            this->father = nullptr;
            this->content = make_pair(0, 0);
        }

        node(pair <int, int> content) // Constructor pasando coordenadas
        {
            this->father = nullptr;
            this->content = content;
        }

        node(pair <int, int> content, node* father) // Constructoor completo (coordenadas y padre)
        {
            this->father = father;
            this->content = content;
        }

        void setFather(node *father) // Actualiza el padre
        {
            this->father = father;
        }

        node* getFather() // Obtiene el padre
        {
            return this->father;
        }

        pair <int, int> getContent() // Obtiene las coordenadas
        {
            return this->content;
        }

        void addChild(pair <int, int> content) // Añade un hijo (no utilizado) - O(1)
        {
            this->childs.push_back(new node(content, this));
        }
};

// Suma dos pares de enteros - O(1)
pair <int, int> sumPairs(pair <int, int> p1, pair <int, int> p2)
{
    return make_pair(p1.first + p2.first, p1.second + p2.second);
}

// Imprime un par de enteros - O(1)
void printPair(pair <int, int> input)
{
    cout << "(" << input.first << ", " << input.second << ")";
}

// Imprime una matriz nm - O(nm)
void printMat(vector <vector <int>> input)
{
    for (int y = 0; y < input[0].size(); y++) // Itera a través de la matríz - O(nm)
    {
        for (int x = 0; x < input.size(); x++)
        {
            cout << input[x][y] << " ";
        }
        cout << endl;
    }
}

// Backtracking para encontrar la solución - O(nm)
vector <vector <int>> backtrackingSol(vector <vector <int>> input, vector <vector <int>> sol, pair <int, int> c_crd)
{
    vector <pair <int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // Genera un vector de pares con posibles movimientos
    int lenght = input.size();
    int height = input[0].size();

    sol[c_crd.first][c_crd.second] = 1; // Establece la casilla actual como marcada - O(1)

    if (c_crd.first >= lenght - 1 && c_crd.second >= height - 1) return sol; // Si llega a destino regresa la solución

    for (auto i_crd:dirs) // Itera por las posibles direcciones - O(4) = O(1)
    {
        pair <int, int> n_crd = sumPairs(i_crd, c_crd); // Genera una coordenada con la nueva posición

        if (n_crd.first < 0 || n_crd.first >= lenght) continue; // Se pasa de los límites, regresa

        if (n_crd.second < 0 || n_crd.second >= height) continue; // Se pasa de los límites, regresa

        if (input[n_crd.first][n_crd.second] == 0) continue; // No es un camino permitido, regresa

        if (sol[n_crd.first][n_crd.second] == 1) continue; // Encuentra una casilla previamente marcada, regresa

        vector <vector <int>> this_sol = backtrackingSol(input, sol, n_crd); // Obtiene la recursión de la siguiente posición - O(nm)
        // Este proceso regresa un vector, en el peor de los casos iterará por todas las casillas,
        // por lo que el proceso es O(nm). Después se guardará, por lo que sería O(nm + nm) = O(2nm) = O(nm)
        // Nunca se iterará por una casilla previamente recorrida. El mapa recorrido se hereda.

        if (this_sol[lenght - 1][height - 1] == 1) return this_sol; // Si la casilla destino del método previo esta marcada regresa la solución - O(1)
    }

    sol[c_crd.first][c_crd.second] = 0; // Si ninguna dirección causa recursión estamos atorados, por lo que desmarcamos y regresamos solución como está.
    // Eventualmente regresara al root si no hay solución. Es decir, si no hay solución segreará una matríz de ceros.

    return sol;
}

// Solución por ramificación y poda - O()
vector <vector <int>> branchAndBoundSol(vector <vector <int>> input, vector <vector <int>> sol, pair <int, int> c_crd)
{
    vector <pair <int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // Crea todas las direcciones - O(1)
    int lenght = input.size();
    int height = input[0].size();

    bool break_bfs = false; // Bandera para salir del BFS

    vector <vector <int>> visited = sol; // Se crea una copia de sol para los nodos visitados en el bfs - O(nm)

    queue <node*> queue; // Se crea una fila de nodos para guardar tanto la coordenada como el puntero al padre de la respuesta
    queue.push(new node({c_crd.first, c_crd.second})); // Primer push al nodo - O(1)
    visited[queue.front()->getContent().first][queue.front()->getContent().second] = 1; // Primer elemento seteado en 1

    node *curr_node = queue.front(); // S crea una variable que guardara el último nodo encontrado

    while (!break_bfs && !queue.empty()) // Inicia el BFS, en el peor de los casos recorrera todos los espacios - O(nm)
    { // Se ejecuta el BFS mientras la fila tenga elementos

        queue.push(new node({-1, -1})); // Se inserta un separador de nivel del BFS

        while (!break_bfs && queue.front()->getContent() != make_pair(-1, -1)) // Si la cabeza de la fila existe, se consiguen sus hijos - O(1)
        {
            for (auto i_crd:dirs) // Se itera por la distintas direcciones - O(1)
            {
                pair <int, int> n_crd = sumPairs(i_crd, queue.front()->getContent()); // Se suman la dirección y la cabeza de la fila

                if (n_crd.first < 0 || n_crd.first >= lenght) continue; // Se pasa de los límites, regresa

                if (n_crd.second < 0 || n_crd.second >= height) continue; // Se pasa de los límites, regresa

                if (input[n_crd.first][n_crd.second] == 0) continue; // No es un camino permitido, regresa
                
                if (visited[n_crd.first][n_crd.second] == 1) continue; // Encuentra una casilla previamente marcada, regresa

                node *n_node = new node(n_crd, queue.front()); // Si se pasan los filtros, se crea un nuevo nodo

                if (n_crd.first >= lenght - 1 && n_crd.second >= height - 1) // Si se encuentra la solución, se activa la bandera y se sale del BFS
                {
                    curr_node = n_node;
                    break_bfs = true;
                    break;
                }

                queue.push(n_node); // Inserta el nodo en en la fila en caso contrario

                visited[n_crd.first][n_crd.second] = 1; // Marca el nodo como visitado
            }

            if (break_bfs) continue; // Ayuda al proceso de evaciuación de BFS
            
            curr_node = queue.front(); // Actualiza el nodo final
            queue.pop(); // Borra el último elemento para ir al siguiente elemento del nivel del BFS
        }
        if (break_bfs) continue; // Ayuda al proceso de evaciuación de BFS

        queue.pop(); // Borra el separador de niveles en la fila
    }

    while (curr_node) // Hace "Bactracking" por todos los nodos del último ADT nodo - O(nm)
    {
        sol[curr_node->getContent().first][curr_node->getContent().second] = 1; // Deja un rastro con unos del final al principio
        curr_node = curr_node->getFather(); // Se itera el apuntador hacia el padre
    }

    return sol; // Regresa la solución obtenida
}

// Proceso principal - O(nm)
void process()
{
    int m, n;

    cout << "Inserta el número de filas: ";
    cin >> m;
    cout << endl;

    cout << "Inserta el número de columnas: ";
    cin >> n;
    cout << endl;

    vector <vector <int>> mat(n, vector<int>(m, -1)); // Crea la matríz de entrada - O(nm)
    vector <vector <int>> sol(n, vector<int>(m, 0)); // Crea la matríz de solución - O(nm)
    
    cout << "Inserta los elementos:" << endl;

    for (int y = 0; y < m; y++) // Itera a través de la matríz para recibir un input - O(nm)
    {
        for (int x = 0; x < n; x++)
        {
            cin >> mat[x][y];
        }
    }

    vector <vector <int>> res = backtrackingSol(mat, sol, {0, 0}); // Solución por backtracking - O(nm)

    cout << endl << "Solución por backtracking:" << endl;
    printMat(res);

    res = branchAndBoundSol(mat, sol, {0, 0}); // Solución por backtracking - O(nm)

    cout << endl << "Solución por branch and bound:" << endl;
    printMat(res);
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