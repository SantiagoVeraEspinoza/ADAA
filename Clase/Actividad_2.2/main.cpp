#include <iostream>
#include <map>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 10/09/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Cantidad de letras en palabra
- c: Cantidad de letras en cadena más corta
*/

// Compara la cadena que va a entrar y la cadena que se encuentra en la cabeza del priority queue - O(c)
struct Compare {
    bool operator() (const string& a, const string& b) const { // Función para comparar dos strings
        return a < b; // Ordena descendentemente - O(c)
    }
};

// Proceso principal - O(n^2)
void process()
{
    string input;

    cout << "Inserta una cadena de caracteres: ";
    cin >> input;
    cout << endl;

    map<string, int, Compare> suffix_array; // Árbol AVL de suffixes

    for (int i=0; i< input.size(); i++){ // Itera por todos los caracteres de la cadena - O(n) -> O(n^2)
        string sub_str = input.substr(i, input.size() - i); // Obtiene la subcadena a utilizar según el índice - O(n)

        suffix_array.emplace(sub_str, i); // Se coloca el substring en el árbol avl (este se ordena en automático) - O(n)
        // Es un proceso O(n) ya que si bien, el añadir un elemento es de complejidad O(1), comparar dos strings que en el
        // peor de los casos sera n-1 vs n hace que la compración sea O(n).
    }
    
    cout << "Suffix array:" << endl;
    for (auto e:suffix_array) // Se itera por la lista de cadenas de texto - O(n)
    {
        cout << e.first << endl;
    }

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