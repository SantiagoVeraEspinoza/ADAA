#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 05/10/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de artículos
- w: Peso máximo

- l: Articulos en la mitad izquierda
- r: Articulos en la mitad derecha
*/

// Sobrecarga del cout para vectores
template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    os << "[ ";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end()-1; ii++)
    {
        os << *ii << ", ";
    }
    cout << v[v.size()-1];
    os << " ]";
    return os;
}

// Clase article para guardar y acceder a los artículos
class article {
    private: // Peso y valor
        int weight;
        float value;

    public:
        article(){ // Constructor por defecto
            this->weight = 0;
            this->value = 0.0;
        }

        article(int weight, float value) { // Constructor con argumentos
            this->weight = weight;
            this->value = value;
        }

        int getWeight() {
            return this->weight;
        }

        float getValue() {
            return this->value;
        }

        void setWeight(int weight) {
            this->weight = weight;
        }

        void setValue(float value) {
            this->value = value;
        }

        friend ostream& operator<<(ostream& os, const article& input) { // Sobrecarga al cout
            os << "(" << input.weight << ", " << input.value << ")";
            return os;
        }
};

// Greedy - O(n)
vector <pair <int, article>> greedy(vector <article> input, int max_weight, float curr_val = 0.0, vector <pair <int, article>> res = {{-1, article()}}, int curr = 0) {
    if (curr >= input.size()) return res; // Si es mayor a n, regresa el resultado - O(1)

    int n_weight = max_weight - input[curr].getWeight(); // Obtiene el nuevo peso máximo - O(1)
    // El elemento no se añade al saco
    if (n_weight < 0) return greedy(input, max_weight, curr_val, res, curr + 1); // Si el nuevo peso máximo es negativo, se salta el elemento - O(n)

    // El elemento se añade al saco
    int n_value = curr_val + input[curr].getValue(); // Obtiene el nuevo valor acumulado - O(1)
    res.push_back(make_pair(curr, article(input[curr].getWeight(), input[curr].getValue()))); // Añade el elemento al resultado - O(1)
    return greedy(input, n_weight, n_value, res, curr + 1); // Hace recursión con los nuevos valores - O(n)

    // En cualquiera de los casos el curr aumenta y como este esta limitado por n, la recursión es O(n)
}

// DP - O(nw)
float dpKS(vector <article> input, int max_weight, vector <vector <float>> dp, int curr = 0) { // dp[n][w]
    if (dp[curr][max_weight] != -1) return dp[curr][max_weight];
    if (curr >= input.size() || max_weight <= 0) return dp[curr][max_weight] = 0;

    cout << curr << " " << max_weight << endl;

    int n_weight = max_weight - input[curr].getWeight(); // Obtiene el nuevo peso máximo - O(1)
    if (n_weight <= 0) return dp[curr][max_weight] = dpKS(input, max_weight, dp, curr + 1);

    float has = dpKS(input, n_weight, dp, curr + 1) + input[curr].getValue(); // Obtiene el nuevo valor acumulado - O(1)
    float has_not = dpKS(input, max_weight, dp, curr + 1); // Obtiene el nuevo valor acumulado - O(1)

    if (has > has_not) return dp[curr][max_weight] = has;

    return dp[curr][max_weight] = has_not;
}

// Merge - O(l + r)
void merge(std::vector<article>& arr, int l, int m, int r, string unmatcher="Profit") {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Crea vectores temporales
    vector<article> left(n1);
    vector<article> right(n2);

    // Inicializa la info en los vectores
    for (int i = 0; i < n1; i++) left[i] = arr[l + i]; // O(l)
    for (int j = 0; j < n2; j++) right[j] = arr[m + 1 + j]; // O(r)

    // Combina los subvectores
    int i = 0; // Índice incial del primer subvector
    int j = 0; // Índice incial del segundo subvector
    int k = l; // Índice incial del subvector combinado

    if (unmatcher == "Weight") { // Ordena por peso
        while (i < n1 && j < n2) { // Itera hasta el mientras j sea menor al subvector más pequeño - O(min(l, r))
        if (left[i].getWeight() <= right[j].getWeight()) { // Inserta el izquierdo
            arr[k] = left[i];
            i++;
        } else { // Inserta el derecho
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    }
    else if (unmatcher == "ProfitWeight") { // Ordena por valor entre peso
        while (i < n1 && j < n2) { // Itera hasta el mientras j sea menor al subvector más pequeño - O(min(l, r))
        if (left[i].getValue()/left[i].getWeight() > right[j].getValue()/right[j].getWeight()) { // Inserta el izquierdo
            arr[k] = left[i];
            i++;
        } else { // Inserta el derecho
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    }
    else { // Ordena por valor
        while (i < n1 && j < n2) { // Itera hasta el mientras j sea menor al subvector más pequeño - O(min(l, r))
        if (left[i].getValue() >= right[j].getValue()) { // Inserta el izquierdo
            arr[k] = left[i];
            i++;
        } else { // Inserta el derecho
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    }

    // Si quedan elementos en la izquierda los insertas - O(r-l)
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Si quedan elementos en la derecha los insertas - O(l-r)
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Merge Sort - O(nlog(n))
void mergeSort(std::vector<article>& arr, int left, int right, string unmatcher = "Profit") {
    if (left < right) {
        // Obtiene la mitad entre los punteros - O(1)
        int middle = left + (right - left) / 2;

        // Ordena la primera y la segunda mitad - O(nlog(n))
        mergeSort(arr, left, middle, unmatcher); // O()
        mergeSort(arr, middle + 1, right, unmatcher);

        // Combina dos mitades ordenadas - O(l + r) -> O(n)
        merge(arr, left, middle, right, unmatcher);
    }
}

void process() {
    int n, w;

    cout << "Inserta el número de artículos: ";
    cin >> n;
    cout << endl;

    cout << "Inserta el peso máximo: ";
    cin >> w;
    cout << endl;

    vector <article> articles;
    
    for (int i = 0; i < n; i++) // Obtiene todos los artículos - o(n)
    {
        cout << "Elemento " << i << ": ";
        int w;
        float v;
        cin >> w >> v;

        articles.push_back(article(w, v));
    }

    vector <float> results_greedy(4, -1); // Inicializa un vector con todos los resultados de cada greedy - O(1)

    vector <pair <int, article>> res = greedy(articles, w); // Resuleve por greedy - O(n)

    float acum_weight = 0.0; // Peso y valor acumulado
    float acum_sum = 0;

    cout << endl << "Greedy Take First Item:" << endl;
    for (int i=1; i<res.size(); i++) { // Itera por la solución - O(n)
        acum_weight += res[i].second.getWeight();
        acum_sum += res[i].second.getValue();
        cout << "i=" << res[i].first << " : w=" << res[i].second.getWeight() << " : p=" << res[i].second.getValue() << endl;
    }
    results_greedy[0] = acum_sum;
    cout << "Total Items in the Knapsack = " << res.size()-1 << endl;
    cout << "Total Weight = " << acum_weight << "/" << w << endl;
    cout << "Total Profit = " << acum_sum << endl;

    mergeSort(articles, 0, articles.size() - 1, "Weight"); // Ordena los artículos por peso - O(nlog(n))

    res = greedy(articles, w); // Resuleve por greedy - O(n)

    acum_weight = 0.0; // Peso y valor acumulado
    acum_sum = 0;

    cout << endl << "Greedy Min Weight:" << endl;
    for (int i=1; i<res.size(); i++) { // Itera por la solución - O(n)
        acum_weight += res[i].second.getWeight();
        acum_sum += res[i].second.getValue();
        cout << "i=" << res[i].first << " : w=" << res[i].second.getWeight() << " : p=" << res[i].second.getValue() << endl;
    }
    results_greedy[1] = acum_sum;
    cout << "Total Items in the Knapsack = " << res.size()-1 << endl;
    cout << "Total Weight = " << acum_weight << "/" << w << endl;
    cout << "Total Profit = " << acum_sum << endl;

    mergeSort(articles, 0, articles.size() - 1, "Profit"); // Ordena los artículos por valor - O(nlog(n))

    res = greedy(articles, w); // Resuleve por greedy - O(n)

    acum_weight = 0.0; // Peso y valor acumulado
    acum_sum = 0;

    cout << endl << "Greedy Max Profit:" << endl;
    for (int i=1; i<res.size(); i++) { // Itera por la solución - O(n)
        acum_weight += res[i].second.getWeight();
        acum_sum += res[i].second.getValue();
        cout << "i=" << res[i].first << " : w=" << res[i].second.getWeight() << " : p=" << res[i].second.getValue() << endl;
    }
    results_greedy[2] = acum_sum;
    cout << "Total Items in the Knapsack = " << res.size()-1 << endl;
    cout << "Total Weight = " << acum_weight << "/" << w << endl;
    cout << "Total Profit = " << acum_sum << endl;

    mergeSort(articles, 0, articles.size() - 1, "ProfitWeight"); // Ordena los artículos por valor entre peso - O(nlog(n))

    res = greedy(articles, w); // Resuleve por greedy - O(n)

    acum_weight = 0.0; // Peso y valor acumulado
    acum_sum = 0;

    cout << endl << "Greedy Max Profit/Weight:" << endl;
    for (int i=1; i<res.size(); i++) { // Itera por la solución - O(n)
        acum_weight += res[i].second.getWeight();
        acum_sum += res[i].second.getValue();
        cout << "i=" << res[i].first << " : w=" << res[i].second.getWeight() << " : p=" << res[i].second.getValue() << endl;
    }
    results_greedy[3] = acum_sum;
    cout << "Total Items in the Knapsack = " << res.size()-1 << endl;
    cout << "Total Weight = " << acum_weight << "/" << w << endl;
    cout << "Total Profit = " << acum_sum << endl;

    vector <vector <float>> dp(articles.size()+1, vector <float>(w+1, -1)); // Crea una matriz para el dp - O(nw)

    float dp_res = dpKS(articles, w, dp);

    float closest_res = -1;
    int closest_res_id;
    for (int i=0; i<results_greedy.size(); i++) {
        float dist = fabs(results_greedy[i] - dp_res);

        if (closest_res == -1 || dist < closest_res) {
            closest_res = dist;
            closest_res_id = i;
        }
    }

    cout << endl << "Best Strategy was ";
    switch(closest_res_id) {
        case 0:
            cout << "Greedy Take First Item";
            break;
        case 1:
            cout << "Greedy Min Weight";
            break;
        case 2:
            cout << "Greedy Max Profit";
            break;
        case 3:
            cout << "Greedy Max Profit/Weight";
            break;
        default:
            break;
    }
    cout << " with " << results_greedy[closest_res_id] << " of profit" << endl;
    cout << "With Dynamic Programming the profit is = " << dp_res;
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