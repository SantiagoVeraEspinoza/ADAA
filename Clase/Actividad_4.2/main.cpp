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

// Sobrecarga del cout para pares - O(1)
template <class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

// Regresa una porción de un vector dado un rango - O(v)
template <typename T>
vector <T> selectVectorRange(vector <T> input, int start, int end) {
    vector <T> res;
    for (int i=start; i < end; i++) { // Itera de principio a fin - O(v)
        res.push_back(input[i]);
    }
    return res;
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
pair<float, pair<int, int>> bruteForce(vector <Point> input) {
    float min = FLT_MAX;

    int p1, p2;

    for (int i=0; i<input.size(); i++) { // Itera por los puntos - O(n) -> O(n^2)
        for (int j=0; j<input.size(); j++) { // Itera por los puntos - O(n)
            if (i == j) continue; // Se salta cuando se evalua un punto con él mismo

            float d = input[i].distanceTo(input[j]); // Obtiene la distancia
            if ( d <= min) {
                min = d; 
                p1 = std::min(i, j); // El más pequeño
                p2 = std::max(i, j); // El más grande
            }
        }
    }

    return make_pair(min, make_pair(p1, p2));
}

// Regresa todos los elementos de un vector de puntos dentro de un rango en el eje x - O(v)
vector <Point> pointsInAXRange(vector <Point> input, int left_limit, int right_limit) {
    vector <Point> res;
    for (auto e:input) { // Itera de principio a fin - O(v)
        if (left_limit <= e.getX() && e.getX() <= right_limit) res.push_back(e); // Si el elemento esta dentro del rango
    }
    return res;
}

// Los dos puntos más cercanos por técnica divide y vencerás - O(nlog(n))
float divideAndConquer(vector <Point> p_x, vector <Point> p_y) { // Recibe los vectores preordenados
    int n = p_x.size(); // Tamaño del arreglo en x

    // Caso límite
    if (n <= 3) return bruteForce(p_x).first; // Regresa el resultado de un bruteforce en los nodos - O(6) -> O(1)

    // Divide en x usando el centro
    int mid = n/2;
    vector <Point> lp_x = selectVectorRange(p_x, 0, mid); // Porción izquierda - O(n/2) -> O(n)
    vector <Point> rp_x = selectVectorRange(p_x, mid, n); // Porción derecha - O(n/2) -> O(n)
    float d_l = divideAndConquer(lp_x, p_y); // Recursión, obtener el mínimo de cada porción. Se hace recursión por la mitad de cada arreglo
    float d_r = divideAndConquer(rp_x, p_y); // Se hace recursión P(n/2), como se divide constantemente, serán log(n) veces un proceso O(n) - O(nlog(n))
    float d = std::min(d_l, d_r); // El mínimo de los dos mínimos

    vector <Point> S = pointsInAXRange(p_y, p_x[mid].getX() - d, p_x[mid].getX() + d); // Obtiene la franja del medio +/- d en el eje x - O(n)
    for (int i=0; i<S.size(); i++) {
        for (int j=1; j<=7; j++) { // Itera por los posibles siguientes 7 puntos - O(7) -> O(1)
            if (j >= S.size()) continue;
            d = std::min(S[i].distanceTo(S[i+j]), d);
        }
    }

    return d;
}

// Proceso principal - O(n + nlog(n) + n^2 + 3nlog(n)) -> O(n^2)
void process() {
    int n;

    cin >> n; // Número de puntos

    vector <Point> points; // Vector de puntos

    for (int i=0; i<n; i++) { // Recoge todos los puntos - O(n)
        int x, y;
        cin >> x >> y;

        Point p(x, y);
        points.push_back(p);
    }

    pair<float, pair <int, int>> brute_force = bruteForce(points); // Resuelve por fuerza bruta - O(n^2)

    cout << "Brute force: " << brute_force.first << endl;

    cout << "The closest points are: " << brute_force.second.first + 1 << " and " << brute_force.second.second + 1 << endl;

    vector <Point> p_x = mergeSort(points, true); // Vector de puntos ordenado por coordenada x ascendentemente - O(nlog(n))
    vector <Point> p_y = mergeSort(points, false); // Vector de puntos ordenado por coordenada y ascendentemente - O(nlog(n))

    cout << "Divide & Conquer: " << divideAndConquer(p_x, p_y) << endl; // Imprime el resultado por divide y vencerás - O(nlog(n))
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