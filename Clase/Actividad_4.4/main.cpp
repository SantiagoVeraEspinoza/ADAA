#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 13/11/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de elementos

- v: Elementos en un vector
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

// Sobrecarga del cout para pares - O(1)
template <class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

// Enfoque iterativo para buscar un elemento - O(n)
pair <int, int> iterativeRandBinarySerach(vector <int> input, int target) {
    int l = 0;
    int r = input.size() - 1;

    int p; // Puntero aleatorizado
    int it = 0; // Contador de iteraciones

    // En el peor de los casos se probarán todos los elementos del arrreglo
    while (l <= r && input[p] != target) { // Mientras exista espacio entre los límites y no se haya encontrado el target - O(n)
        it++; // Incrementa el contador
        p = l + rand() % (r - l + 1); // Elige un numero aleatorio en el rango

        if (target < input[p]) { r = p - 1; continue; } // Es mayor, se recorre la derecha
        if (target > input[p]) { l = p + 1; continue; } // Es menor, se recorre a la izquierda

        break;
    }

    if (input[p] != target) return {-1, it}; // Si no encuentra el elemento

    return {p, it};
}

// Enfoque recursivo para buscar un elemento - O(n)
pair <int, int> recursiveRandBinarySearch(vector <int> input, int target, int l=0, int r=-10) {
    if (r == -10) r = input.size() - 1; // Establece el puntero derecho si se pasa el valor por defecto

    pair <int, int> res = {-1, 0}; // Valor dado un error

    if (l > r) return res; // Caso límite donde no hay solución, limita la complejidad

    int p = l + rand() % (r - l + 1); // Elige un numero aleatorio en el rango

    if (target == input[p]) { // Se encuentra el objetivo
        res = make_pair(p, 0);
    }
    else if (target < input[p]) { // El objetivo es menor
        res = recursiveRandBinarySearch(input, target, l, p - 1); // Recursión, se puede ejecutar un máximo de n veces antes de llegar al caso límite - O(n)
    }
    else if (target > input[p]) { // El objetivo es mayor
        res = recursiveRandBinarySearch(input, target, p + 1, r); // Recursión, se puede ejecutar un máximo de n veces antes de llegar al caso límite - O(n) 
    }

    return make_pair(res.first, res.second + 1);
}

// Método principal - O(3n) -> O(n)
void process()
{
    srand(time(NULL));

    int n, f;

    cin >> n;

    vector<int> input;
    
    for (int i=0; i<n; i++) { // Lee todos los elementos - O(n)
        int e;
        cin >> e;
        input.push_back(e);
    }

    cin >> f;

    pair <int, int> res_it = iterativeRandBinarySerach(input, f); // Se obtiene el resultado por iteración - O(n)
    pair <int, int> res_re = recursiveRandBinarySearch(input, f); // Se obtiene el resultado por recursión - O(n)

    if (res_it.first != -1 && res_re.first != -1) { // Encontró el elemento
        cout << "Version iterativa: Se evaluaron " << res_it.second << " iteraciones, el elemento " << f 
             << " está en la posicion " << res_it.first << "." << endl;

        cout << "Version recursiva: Se evaluaron " << res_re.second << " iteraciones, el elemento " << f 
             << " está en la posicion " << res_re.first << "." << endl;

        return;
    }

    // No encontró el elemento
    cout << "Version iterativa: Se evaluaron " << res_it.second << " iteraciones, no se encontró el elemento " << f << endl;

    cout << "Version recursiva: Se evaluaron " << res_re.second << " iteraciones, no se encontró el elemento " << f << endl;
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