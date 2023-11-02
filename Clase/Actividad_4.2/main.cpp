#include <iostream>
#include <math.h>
#include <cfloat>
#include <algorithm>
#include <vector>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 02/11/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de puntos

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

// Clase punto
class Point {
    private: // Coordenadas
        float x;
        float y;

    public:
        // Constructores
        Point() { 
            this->x = 0;
            this->y = 0;
        }

        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }

        // Getters y Setters
        float getX() {
            return this->x;
        }

        float getY() {
            return this->y;
        }

        void setX(float x) {
            this->x = x;
        }

        void setY(float y) {
            this->y = y;
        }

        // Methods
        float distanceTo(Point target) { // Distancia entre dos puntos - O(1)
            float dx = this->x - target.getX();
            float dy = this->y - target.getY();
            return pow(((dx * dx) + (dy * dy)), 0.5);
        }

        // Sobrecargas
        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            os << "(" << p.x << ", " << p.y << ")";
            return os;
        }

        // Funciones de comparación - O(1)
        static bool compareByX(const Point& p1, const Point& p2) { // Compara coordenadas x
            return p1.x < p2.x;
        }

        static bool compareByY(const Point& p1, const Point& p2) { // Compara coordenadas y
            return p1.y < p2.y;
        }
};

// Merge - O(n)
std::vector<Point> merge(const std::vector<Point>& left, const std::vector<Point>& right, bool byX = true) {
    std::vector<Point> result; // Resultado
    size_t leftIndex = 0;
    size_t rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size()) { // Itera por los elementos - O(n)
        if (byX) { // Caso si ordena por x
            if (Point::compareByX(left[leftIndex], right[rightIndex])) { // Es menor el de la izquierda?
                result.push_back(left[leftIndex]); // Se agrega
                leftIndex++; // Incrementa el apuntador izquierdo
            } else {
                result.push_back(right[rightIndex]); // Sino, se agrega el derecho y aumenta su apuntador
                rightIndex++;
            }
        }
        else { // Caso si ordena por y
            if (Point::compareByY(left[leftIndex], right[rightIndex])) { // Es menor el de la izquierda?
                result.push_back(left[leftIndex]); // Se agrega
                leftIndex++; // Incrementa el apuntador izquierdo
            } else {
                result.push_back(right[rightIndex]); // Sino, se agrega el derecho y aumenta su apuntador
                rightIndex++;
            }
        }
    }

    result.insert(result.end(), left.begin() + leftIndex, left.end()); // Inserta lo que quedó de la primera mitad - O(n/2) -> O(n)
    result.insert(result.end(), right.begin() + rightIndex, right.end()); // Inserta lo que quedó de la segunda mitad - O(n/2) -> O(n)

    return result;
}

// Merge sort - O(nlog(n))
std::vector<Point> mergeSort(const std::vector<Point>& points, bool byX=true) {
    if (points.size() <= 1) { // Caso base - O(1)
        return points;
    }

    size_t middle = points.size() / 2;
    std::vector<Point> left(points.begin(), points.begin() + middle); // Lista hasta el punto medio - O(n/2) -> O(n)
    std::vector<Point> right(points.begin() + middle, points.end()); // Lista por la derecha

    left = mergeSort(left, byX); // Ordena recursivamente - O(log(n))
    right = mergeSort(right, byX);

    return merge(left, right, byX); // Junta ambas partes - O(n)
}

// Los dos puntos más cercanos por fuerza bruta - O(n^2)
float bruteForce(vector <Point> input) {
    float min = FLT_MAX;

    for (int i=0; i<input.size(); i++) { // Itera por los puntos - O(n) -> O(n^2)
        for (int j=0; j<input.size(); j++) { // Itera por los puntos - O(n)
            if (i == j) continue; // Se salta cuando el se evalua un punto con él mismo
            min = std::min(min, input[i].distanceTo(input[j]));
        }
    }

    return min;
}

// Proceso principal - O(n + nlog(n) + n^2) -> O(n^2)
void process()
{
    int n;

    cin >> n; // Número de puntos

    vector <Point> points; // Vector de puntos

    for (int i=0; i<n; i++) { // Recoge todos los puntos - O(n)
        int x, y;
        cin >> x >> y;

        Point p(x, y);
        points.push_back(p);
    }

    cout << "Brute force: " << bruteForce(points) << endl; // Resuelve por fuerza bruta - O(n^2)

    vector <Point> p_x = mergeSort(points, true); // Vector de puntos ordenado por coordenada x ascendentemente - O(nlog(n))
    vector <Point> p_y = mergeSort(points, false); // Vector de puntos ordenado por coordenada y ascendentemente - O(nlog(n))

    cout << p_x << endl << p_y << endl;
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