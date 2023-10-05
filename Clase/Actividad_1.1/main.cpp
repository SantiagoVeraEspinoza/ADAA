#include <iostream>
#include <vector>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 20/08/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de elementos en el arreglo
- l: Número de elementos de la suma de dos sublistas
*/

// Imprime el vector - O(n)
void printVec(vector <int> input, string line = "Vector =")
{
    cout << "\n" << line << " [";
    for (int i=0; i<input.size(); i++) // Itera por el vector
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

// Se combinan dos listas ordenadas - O(n)
vector <int> orderSortedLists(vector <int> l1, vector <int> l2, bool ascending = true)
{
    vector <int> res; // Crea un vector para el resultado

    int p1 = 0;
    int p2 = 0;

    while (true) // Ciclo tecnicamente infinito, pero por el diseño se ejecutara un máximo de l veces
    {
        if (p1 >= l1.size() && p2 >= l2.size()) // Si ambos contadores llegaron al limite de sus vectores se regresa la respuesta (siempre acaba aquí)
        {
            return res;
        }
        if (p1 >= l1.size()) // Si un contador llego al límite de su vector
        {

            res.push_back(l2[p2]);
            p2++;
            continue;
        }
        if (p2 >= l2.size()) // Si un contador llego al límite de su vector
        {
            res.push_back(l1[p1]);
            p1++;
            continue;
        }
        if (l1[p1] < l2[p2]) // Si uno es menor que el otro se añade el menor
        {
            if (ascending == false){ // O el mayor si se trata de orden descendente
                res.push_back(l2[p2]);
                p2++;
                continue;
            }
            res.push_back(l1[p1]);
            p1++;
            continue;
        }
        if (l1[p1] > l2[p2]) // Si uno es menor que el otro se añade el menor
        {
            if (ascending == false){ // O el mayor si se trata de orden descendente
                res.push_back(l1[p1]);
                p1++;
                continue;
            }
            res.push_back(l2[p2]);
            p2++;
            continue;
        }
        if (l1[p1] == l2[p2]) // Si son iguales solo avanza
        { // En caso de que avance al límite de un vector se activará el if de arriba en siguientes iteraciones y la respuesta será correcta
            res.push_back(l1[p1]);
            p1++;
            continue;
        }
    }

    return res; // Regresa la respuesta el remoto caso de que no llegue el ciclo al fin (es algo redundante ya que los contadores siempre aumentan)
}

// El merge sort en sí, funciona con punteros - O(nlog(n))
// El vector se divide log(n) veces y cada una de esas veces ejecuta un proceso O(n), por lo que tenemos O(nlog(n))
// Si además del vector, le pasas un false, ordena de manera descendente
vector <int> mergeSort(vector <int> &input, bool ascending = true, int first = -1, int last = -1)
{
    if (first == -1) first = 0; // Para evitar que el usuario meta mucho argumentos, se crea una excepcion para el caso default, que es -1
    if (last == -1) last = input.size() - 1;

    int middle = ((last - first + 1) / 2) + first; // Se encuentra el punto medio de los dos puntos dados

    if (first == last) // Si se llega a un elemento unitario, se refresa este último
    {
        return {input[first]};
    }

    // En este punto se inicia la recursividad, como el tamaño de los elementos recursivos es siempre la mitad se habla de una complejidad O(log(n))
    vector <int> left = mergeSort(input, ascending, first, middle - 1); // Se guarda una variable con la información del vector ordenado de la izquierda
    vector <int> right = mergeSort(input, ascending, middle, last); // Se guarda una variable con la información del vector ordenado de la derecha

    return orderSortedLists(left, right, ascending); // Se ordenan las dos listas dadas, en el peor de los casos seran unidas del tamaño del vector total - O(n)
}

// Este es el proceso principal que utilizaremos - O(n + n + n + ) = O(nlog(n))
void process()
{
    int n;

    cout << "\nInserta número: "; // Pide la inserción de un número
    cin >> n;
    cout << endl;

    vector<int> vec(n); // Crea un vector de tamaño n - O(n)
    
    for (int i = 0; i < n; i++) // Pide todos los elementos - O(n)
    {
        cout << "Elemento " << i << ": ";
        cin >> vec[i]; // Pide un elemento y se lo asigna al vector en la posición 'i'
    }
    
    printVec(vec, "El vector es ="); // Imprime el vector con una frase personalizada - O(n)

    printVec(mergeSort(vec), "El vector ordenado es ="); // Imprime el vector ordenado - O(n + nlog(n)) = O(nlog(n))
    // Para este último, primero se realiza el método O(nlog(n)) y luego, con la información devuelta, se ejecuta un método O(n)

}

#ifdef _WIN32 // Proceso para Windows
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001); // Hace que la consola de windows trabaje en UNICODE (Acepta carácteres especiales)
    process(); // Proceso principal - O(nlog(n))
}

#else // Proceso para Linux y Mac

int main() 
{
    process(); // Proceso principal - O(nlog(n))
}

#endif