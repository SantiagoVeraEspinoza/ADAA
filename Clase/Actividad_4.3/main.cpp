#include <iostream>
#include <vector>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 09/11/2023
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

class Point {
    private: // Atributos
        float x, y;

    private: // Métodos privados
        // Función para combinar dos subarrays ordenados - O(v)
        vector<Point> merge(vector<Point> leftArr, vector<Point> rightArr) {
            vector<Point> result;
            int leftIndex = 0;
            int rightIndex = 0;

            while (leftIndex < leftArr.size() && rightIndex < rightArr.size()) { // Itera por cada elemento cada lista O(v)
                if (this->whereTheyTurn(leftArr[leftIndex], rightArr[rightIndex]) > 0) { // Giro antihorario
                    result.push_back(leftArr[leftIndex]);
                    leftIndex++;
                } 
                if (this->whereTheyTurn(leftArr[leftIndex], rightArr[rightIndex]) < 0) { // Giro horario
                    result.push_back(rightArr[rightIndex]);
                    rightIndex++;
                }
                else { // Colinealidad
                    // Pendiente entre ambos puntos
                    float dy = (leftArr[leftIndex].getY() - rightArr[rightIndex].getY()); // Diferencia en y
                    float dx = (leftArr[leftIndex].getX() - rightArr[rightIndex].getX()); // Diferencia en x

                    if (dx == 0) { // Si es colinear vertical
                        if (dy < 0) { // Orden de lejano a cercano
                            result.push_back(rightArr[rightIndex]);
                            rightIndex++;
                            continue;
                        }
                        result.push_back(leftArr[leftIndex]);
                        leftIndex++;
                        continue;
                    }

                    float slope = dy / dx; // Pendiente
                    
                    if (slope > 0) { // Pendiente positiva
                        if (dy < 0) { // Orden de cercano a lejano
                            result.push_back(leftArr[leftIndex]);
                            leftIndex++;
                            continue;
                        }
                        result.push_back(rightArr[rightIndex]);
                        rightIndex++;
                        continue;
                    }

                    // Pendiente negativa
                    if (dy < 0) { // Orden de lejano a cercano
                        result.push_back(rightArr[rightIndex]);
                        rightIndex++;
                        continue;
                    }
                    result.push_back(leftArr[leftIndex]);
                    leftIndex++;
                }
            }

            while (leftIndex < leftArr.size()) { // Integra restantes - O(v)
                result.push_back(leftArr[leftIndex]);
                leftIndex++;
            }

            while (rightIndex < rightArr.size()) { // Integra restantes - O(v)
                result.push_back(rightArr[rightIndex]);
                rightIndex++;
            }

            return result;
        }

    public:
        // Constructores
        Point() { this->x = this->y = 0; }
        Point(float x, float y) { this->x = x; this->y = y; }

        // Getters y setters
        float getX() { return this->x; }
        float getY() { return this->y; }

        void setX(float x) { this->x = x; }
        void setY(float y) { this->x = y; }
        void setCoordinates(float x, float y) { this->x = x; this->y = y; }

        // Métodos
        // Calcula el producto cruz del punto origen al punto objetivo, uando como pivote el punto actual - O(1)
        float crossProduct(Point source, Point target) { 
            // Producto cruz usando el punto actual como origen - O(1)
            float cross = (source.getX()-this->getX())*(target.getY()-this->getY()) - (target.getX()-this->getX())*(source.getY()-this->getY()); 

            return cross;
        }

        // Regresa un entero indicando la dirección de giro - O(1)
        int whereTheyTurn(Point source, Point target) {
            float cross = this->crossProduct(source, target); // Evalua el producto cruz bruto - O(1)

            if (cross < 0) return -1; // Horario
            if (cross > 0) return 1; // Antihorario
            return 0; // Colinear
        }

        // Merge Sort - O(nlog(n))
        vector<Point> mergeSort(vector<Point> arr) {
            if (arr.size() <= 1) return arr; // Caso límite

            int mid = arr.size() / 2;
            vector<Point> leftArr(arr.begin(), arr.begin() + mid); // Separa la mitad izquierda - O(n)
            vector<Point> rightArr(arr.begin() + mid, arr.end()); // Separa la mitad derecha - O(n)

            leftArr = mergeSort(leftArr); // Recursión a la izquierda - O(log(n)) -> O(nlog(n))
            rightArr = mergeSort(rightArr); // Recursión a la derecha - O(log(n)) -> O(nlog(n))

            return merge(leftArr, rightArr); // Combina arreglos ordenados - O(n)
        }

        // Sobrecarga de operadores
        // Sobrecarga stdout
        friend ostream& operator<<(std::ostream& os, const Point& obj) {
            os << "(" << obj.x << ", " << obj.y << ")";
            return os;
        }
};

void process()
{
    Point p1(3, 1);
    Point p2(0, 3);
    Point p3(0, 4);
    Point p4(-1, 1);
    Point p5(5, 4);
    Point p6(0, 3);
    Point p7(-2, 2);
    Point piv;

    // cout << piv.whereTheyTurn(p1, p1);

    vector <Point> test_sort = {p1, p2, p3, p4, p5, p6, p7};
    cout << piv.mergeSort(test_sort);
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