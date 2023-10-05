#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 27/08/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Cantidad de monedas
- c: Cambio
- v: Tamaño vector dado
- m: Tamaño del mapa
*/

// Estructura para especificar el orden del coin map - O(1)
struct Compare {
    bool operator() (const int& a, const int& b) const {
        return a > b; // Orden descendente
    }
};

// Imprime el vector - O(v)
void printVec(vector <int> input, string line = "Vector =")
{
    cout << "\n" << line << " [";
    for (int i=0; i<input.size(); i++) // Itera por el vector - O(v)
    {
        if (i >= input.size() - 1) // Si es el último elemento solo imprime el elemento
        {
            cout << input[i];
            continue;
        }
        cout << input[i] << ", "; // En cualquier otro caso imprime el elemento y una coma
    }
    std::cout << "]" << endl; // Termina el formato con un ']'
}

// Imprime el mapa - O(m)
void printMap(map <int, int, Compare> input, string line = "Map =")
{
    cout << endl << line << " {" << endl;

    int count = 0;
    for (const auto& pair : input) { // Recorre el mapa - O(m)
        count ++;

        if (count >= input.size())
        {
            std::cout << pair.first << ": " << pair.second << " }";
            continue;
        }
        std::cout << pair.first << ": " << pair.second << "," << std::endl;
    }
}

// Imprime un vector de mapas - O(vm)
void printVectorMap(vector <pair<map <int, int, Compare>, int>> input, string line = "Vector of maps =")
{
    cout << endl << line + "[" << endl;

    int count = 0;
    for (auto p:input) // Itera con una complejidad O(m) por cada elemento del vector - O(vm)
    {
        count++;
        cout << "Length: " << p.second; // Imprime la longitud asociada

        printMap(p.first); // Imprime el mapa correspondiente - O(m)

        if (!(count >= input.size())) cout << ",";
        cout << endl;
    }
    cout << "]" << endl;
}

// Solución con DP - O(cnlog(n))
pair <map <int, int, Compare>, int> dpCoinChange(map <int, int, Compare> input, int change, vector <pair<map <int, int, Compare>, int>> &dp)
{
    // Las operaciones son log(n)  para dp[i].first ya que estamos buscando un elemento en un árbol balanceado y 
    // la máxima profundidad de un árbol binario balanceado siempre va a ser log(n)

    if (dp[change].second != -1) return dp[change]; // Si la solución ya existe, regrésala - O(1)
    // Es O(1) debido a que el tiempo de búsqueda en vectores es constante

    pair <int, int> min = make_pair(-1, -1); // Este es el mínimo elemento (cambio, profundidad debajo)
    // Regresa el cambio y la profundidad (iteraciones hasta llegar a la solución) que hay debajo del mínimo elemento
    for (const auto& c_pair : input) { // Recorre todas las monedas - O(n * log(n)) = O(nlog(n))
        int n_change = change - c_pair.first; // Obtiene el cambio si añadiéramos una moneda

        if (n_change == 0) // Si da 0 el resultado es el mejor posible, lo regresamos - O(log(n))
        {
            dp[change].first[c_pair.first] = 1; // Buscamos el elemento y le asiganmos un valor - O(log(n))
            dp[change].second = 1; // Lo mismo aquí pero a un elemento que no es mapa - O(1)
            return dp[change]; // Esto también es constante
        }

        if (n_change > 0) // Si es mayor debemos hacer más iteraciones
        {
            pair <map <int, int, Compare>, int> n_sol = dpCoinChange(input, n_change, dp);
            // Aquí empezamos la recursión, por la memoización podríamos decir que en el peor de los casos
            // la recursividad se ejecutaria m veces y eventualmente se ejecutaría en tiempo constante
            // (por el costo de búsqueda del vector). Si la complejidad hasta ahora era de O(nlog(n)) y en el
            // peor de los casos ejecutamos el ciclo recursivo m veces podríamos decir que esta función
            // tiene una complejidad de O(cnlog(n) + n) debido a que se asigna un mapa tamaño n. La
            // complejidad final es de O(cnlog(n))

            if (n_sol.second == -1) continue; // Ver si ocurre que no se haya encontrado solución

            if (min.first == -1) // Si el mínimo no ha sido inicializado se inicializa - O(1)
            {
                min.first = n_change;
                min.second = n_sol.second;
            }
            else if (min.second > n_sol.second) // Si ya fue inicializado pero es menor al valor enocntrado, se actualiza - O(1)
            {
                min.first = n_change;
                min.second = n_sol.second;
            }
        }
    }

    if (min.first && min.second == -1) return dp[0]; // No se encuentra ningún buen candidato, se regresa el caso default (no válido) - O(log(n))

    dp[change] = dp[min.first]; // Se igualan versiones del dp - O(n)
    dp[change].first[change-min.first]++; // Cambia un elemento del mapa dentro de dp - O(log(n))
    dp[change].second++; // Se altera un elemento del vector - O(1)

    return dp[change]; // Se regresa el dp obtenido - O(1)
}

// Solución greedy - O(n^clog(n))
map <int, int, Compare> greedyCoinChange(pair <map <int, int, Compare>, int> &sol, vector <int> input, int change)
{
    bool found_sol = false; // Una bandera que guarda si alguna de las monedas da una solución válida

    for (int i=0; i<input.size(); i++) // Itera por cada elemento del input - O(n)
    {
        int n_change = change - input[i]; // Obtienes el cambio con cada moneda

        if (n_change < 0) continue; // Si es solución inválida la salta
        if (n_change == 0) // Si es igual a cero regresa la solución
        {
            sol.first[input[i]] += 1; // Aumenta en uno la solución en el espacio de la moneda usada - O(log(n))
            sol.second = 1; // Settea el tamaño como 1 - O(1)
            return sol.first;
        }
        if (n_change > 0) // Si es mayor hace recursión en el elemento
        {
            found_sol = true;
            int last_n_sol_state = sol.second; // Obtinene el elemento actual de la recursión - O(log(n))

            greedyCoinChange(sol, input, n_change); // Hace la recursión pasando la solución como referencia
            // En el peor de los casos se hará una recursión de tamaño n^c con procesos O(log(n))

            if (sol.second != last_n_sol_state) // Si el elemento modificado por la recursión inmediatamente abajo fue modificado
            {
                sol.first[input[i]] += 1; // Se cuenta la solución como verdadera y se aumenta el elemento actual de la solución - O(log(n))
                sol.second += 1; // Aumenta el tamaño en 1 - O(1)
                return sol.first;
            }
        }
    }

    return sol.first; // No encontro solución, regresa la funcion como la recibió
}

// Este es el proceso principal que utilizaremos - O(3n + nc + cnlog(n) + n^clog(n)) = O(n^clog(n))
void process()
{
    int n, p, q;

    cout << "Inserta número: "; // Pide n
    cin >> n;
    cout << endl;

    map <int, int, Compare> coins; // Árbol AVL con todas la coins
    
    for (int i = 0; i < n; i++) // Busca todos los numero del vector - O(n)
    {
        cout << "Elemento " << i << ": ";
        int coin;
        cin >> coin;
        coins.emplace(coin, 0); // Guarda la key y la cantidad de cada moneda, lo bueno es que el emplace automaticamente ordena las monedas - O(1)
    }

    vector <int> vec_coins; // Vector para el método greedy

    for (const auto& pair : coins) { // Añade todos los elementos del mapa a un vector - O(n)
        vec_coins.push_back(pair.first);
    }

    cout << endl << "Ingresa el precio del producto: "; // Obtiene la cantidad de dinero que cuesta el producto y lo que se da de dinero
    cin >> p;
    cout << endl << "Ingresa la cantidad de dinero ofercida: ";
    cin >> q;

    int change = q - p; // Se obtiene el cambio

    if (change <= 0) return; // Si te falta dinero sale de la función

    vector <pair <map <int, int, Compare>, int> > dp; // Hace un vector de árboles y enteros

    for (int i=0; i<change+1; i++) // Itera c veces con un proceso de complejidad O(n) cada iteración - O(c*n) = O(nc)
    {
        dp.push_back(make_pair(coins, -1)); // Se anexa una copia de tamaño n y un entero a cada elemento c - O(n)
    }

    cout << endl;

    printMap(dpCoinChange(coins, change, dp).first, "La solución con dp es ="); // Ejecuta el método dp - O(cnlog(n))
    cout << endl;

    pair <map <int, int, Compare>, int> map_pair = make_pair(coins, -1); // Hago un par mapa con su tamaño - O(n)
    printMap(greedyCoinChange(map_pair, vec_coins, change), "La solución con greedy es ="); // Ejecuta el método greedy - O(n^clog(n))
    // El costo de imprimir tambien es O(n) pero al hacerlo después de obtener el mapa en ambos casos, se elimina este valor de la complejidad final

    // Ambos métodos regresan un mapa setteado en 0 si no existe ninguna solución
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