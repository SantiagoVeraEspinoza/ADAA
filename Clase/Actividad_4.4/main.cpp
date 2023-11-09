#include <iostream>
#include <vector>

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

void process()
{
    int n, f;

    cin >> n;

    vector<int> input;
    
    for (int i=0; i<n; i++) {
        int e;
        cin >> e;
        input.push_back(e);
    }

    cin >> f;

    cout << input;
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