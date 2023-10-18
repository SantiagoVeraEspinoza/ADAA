#include <iostream>
#include <vector>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 19/10/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de casos

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
template <class T, class K>
std::ostream& operator << (std::ostream& os, const std::pair<T, K>& p) {
    os << "(" << p.first << ", " << p.second << ")"; // Regresa el valor de cada elemento en forma de coordenada - O(1)
    return os;
}

// Obtiene la dirección de tres puntos - O(1)
int getOrientation(pair <int, int> p1, pair <int, int> p2, pair <int, int> p3) {
    int val = (p2.second - p1.second) * (p3.first - p2.first) - (p3.second - p2.second) * (p2.first - p1.first); // Obtiene la expresión - O(1)

    if (val == 0) return 0;  // Colinear
    return (val > 0) ? -1 : 1;  // Torque negativo (horario) o positivo (antihorario)
}

// Verifica si dos segmentos intersectan - O(1)
bool segmentsIntersect(pair <pair <int, int>, pair <int, int>> seg1, pair <pair <int, int>, pair <int, int>> seg2) {
    // Caso especial - O(1)
    if (getOrientation(seg1.first, seg1.second, seg2.first) == 0 && 
        getOrientation(seg1.first, seg1.second, seg2.second) == 0 && 
        getOrientation(seg2.first, seg2.second, seg1.first) == 0 && 
        getOrientation(seg2.first, seg2.second, seg1.second) == 0) { // Si todas las uniones posibles con colineares - O(1)
        
        if (seg1.first.first < seg2.second.first && seg1.second.first > seg2.first.first) return true; // Checa intersección en el eje x
        if (seg1.first.second < seg2.second.second && seg1.second.second > seg2.first.second) return true; // Checa intersección en el eje y

        return false; // No encuentra intersección
    }

    // Caso general - O(1)
    if ((getOrientation(seg1.first, seg1.second, seg2.first) != getOrientation(seg1.first, seg1.second, seg2.second)) &&
        (getOrientation(seg2.first, seg2.second, seg1.first) != getOrientation(seg2.first, seg2.second, seg1.second))) return true;

    return false;
}

// Proceso principal - O(n)
void process() {
    int n;

    cin >> n;
    
    for (int i = 0; i < n; i++) { // Itera por todos los casos - O(n)
        pair <pair <int, int>, pair <int, int>> seg1; // Segmentos
        pair <pair <int, int>, pair <int, int>> seg2;

        int x, y; // Variables para guardar las coordenadas

        // Obtiene los dos puntos del segmento 1 - O(2) -> O(1)
        cin >> x >> y;
        seg1.first = make_pair(x, y);

        cin >> x >> y;
        seg1.second = make_pair(x, y);

        // Obtiene los dos puntos del segmento 2 - O(2) -> O(1)
        cin >> x >> y;
        seg2.first = make_pair(x, y);

        cin >> x >> y;
        seg2.second = make_pair(x, y);

        string res = segmentsIntersect(seg1, seg2) ? "True" : "False"; // Crea string con el valor correspondiente a 0 y 1 - O(1)

        cout << res << endl; // Verifica si los segmentos intersectan - O(1)
    }
}

#ifdef _WIN32
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    process();
}

#else

int main() {
    process();
}

#endif