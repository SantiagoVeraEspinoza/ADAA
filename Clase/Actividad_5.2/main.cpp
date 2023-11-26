// g++ main.cpp -o main.exe
// main.exe < in.txt
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
#define INF 9999999

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 27/11/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- n: Número de iteraciones
- p: Tamaño población
- t: Tamaño del cromosoma
- m: Número de mutaciones
*/

string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz"; // Abecedario

void initialPopulation(vector<string> &poblacion, string objetivo); // Crea la población inicial - O(pt)
vector<int> objectiveFunction(vector<string> &poblacion, string objetivo); // Función objetivo - O(pt)
void printPopulation(vector<string> &poblacion, vector<int> &fitness); // Imprime la población - O(p)
vector<string> crossover(vector<string> &poblacion, vector<int> &fitness); // Cruza la población - O(pt)
void mutation(vector<string> &hijos, int nMutacion); // Se mutan todos los hijos - O(pm)
void reinsertion(vector<string> &poblacion, vector<int> &fitness, vector<string> &hijos, vector<int> &fitnessHijos); // Se checa si los padres deben ser sustituidos por los hijos - O(p)
int findBest(vector<int> &fitness); // Encuentra el mejor cromosoma de la población - O(p)

// Función principal - O(n(2pt + pm + 2p) + 2pt + 2p) -> O(n(pt + pm + p) + pt + p) -> O(n(p(t + m + 1)) + p(t + 1)) -> O(n(p(t + m)) + pt) -> O(npt + npm + pt) -> O(pt(n + 1) + npm) -> O(npt + npm)
int main() {
  srand(time(NULL)); // Cambia la semilla de alatoriedad
  string objetivo = "Tec de Monterrey", best; // Crea el string para el objetivo y el resultado - O(1)
  int iteraciones = 10000, sizePop = 30, nMutacion = 3, globalBest = INF, idx; // Crea el número de iteraciones, el tamaño de la población - O(1)
  vector<string> poblacion(sizePop), hijos; // Crea un vector población del tamaño de la población - O(p)
  vector<int> fitness, fitnessHijos; // Vector para el fitness de cada cromosoma
  initialPopulation(poblacion, objetivo); // Crea la población inicial - O(pt)
  fitness = objectiveFunction(poblacion, objetivo); // Evalua el fitness de cada cromosoma de la población - O(pt)
  cout << "Poblacion inicial:" << endl;
  printPopulation(poblacion, fitness); // Imprime la población inicial - O(p)
  int iter = 0;
  while (iter < iteraciones && globalBest > 0) { // Mientras no se pase de las iterciones máximas - O(n)
  // while (globalBest > 0) {
    iter++;
    hijos = crossover(poblacion, fitness); // Se cruzan los padres para generar una nueva generación - O(pt)
    mutation(hijos, nMutacion); // Se mutan los hijos - O(pm)
    fitnessHijos = objectiveFunction(hijos, objetivo); // Se obtiene el fitness de cada hijo - O(pt)
    reinsertion(poblacion, fitness, hijos, fitnessHijos); // Se checa si los hijos deben sustituir a los padres - O(p)
    idx = findBest(fitness); // Se encuentra al mejor cromosoma - O(p)
    if (globalBest > fitness[idx]) { // El mejor postor de la población actual es mejor que el mejor postor global?
      globalBest = fitness[idx]; // Se sustituye el mejor postor global
      best = poblacion[idx];
      cout << iter << " " << best << " " << globalBest << endl; // Se imprime el progreso de la especie
    }
  }
  cout << "Poblacion final:" << endl; // Se imprime la población final, se haya encontrado al cromosoma perfecto o no
  printPopulation(poblacion, fitness); // Imprime la población final - O(p)
}

// Crea la población inicial - O(pt)
void initialPopulation(vector<string> &poblacion, string objetivo) {
  int n = poblacion.size(), m = objetivo.size(); // Obtiene el tamaño del objetivo y de la población - O(1)
  string individuo;
  for (int i=0; i<n; i++) { // Itera por el tamaño de la población - O(p) -> O(pt)
    individuo = "";
    for (int j=0; j<m; j++) { // Itera por cada carácter del cromosoma - O(t)
      individuo += ABC[rand() % ABC.size()]; // Asigna un caracter aleatorio del abecedario - O(1)
    }
    poblacion[i] = individuo; // Se cambia la población
  }
}

// Se obtiene el fitness de cada cromosoma - O(pt)
vector<int> objectiveFunction(vector<string> &poblacion, string objetivo) {
  // Agrega tu codigo aqui para que el algoritmo funcione
  // la salida es un vector de enteros llamado fitness
  // cada individuo de la poblacion debe tener su propio valor de fitness
  vector <int> fitness;

  for (auto cromosoma:poblacion) { // Se itera por la población - O(p) -> O(pt)
    int t_fitness = objetivo.size();
    for (int i=0; i<objetivo.size(); i++) { // Se itera por el tamaño del cromosoma - O(t)
      if (cromosoma[i] == objetivo[i]) t_fitness--;
    }
    fitness.push_back(t_fitness);
  }

  return fitness;
}

// Imprime la población - O(p)
void printPopulation(vector<string> &poblacion, vector<int> &fitness) {
  int n = poblacion.size();
  for (int i=0; i<n; i++) { // Itera por la población - O(p)
    cout << poblacion[i] << " " << fitness[i] << endl;
  }
  cout << endl;
}

// Se genera una nueva generación cruzando a la población - O(pt + p) -> O(pt)
vector<string> crossover(vector<string> &poblacion, vector<int> &fitness) {
  int n = poblacion.size(), m = poblacion[0].size(); // Tamaño de la población y de un cromosoma - O(1)
  vector<string> hijos(n); // Crea un vector para la siguiente generación del mismo tamaño que la anterior - O(p)
  string padre1, padre2;
  int a,b,c,d,p;
  for (int i=0; i<n; i+=2) { // Itera por todas las parejas de la población - O(p/2) -> O(p) -> O(pt)
    a = rand() % n; // Obtiene cuatro cromosomas aleatorios de la población - O(1)
    b = rand() % n;
    c = rand() % n;
    d = rand() % n;
    padre1 = fitness[a] < fitness[b] ? poblacion[a] : poblacion[b]; // Obtiene al padre con mejores genes de los dos primeros - O(1)
    padre2 = fitness[c] < fitness[d] ? poblacion[c] : poblacion[d]; // Obtiene al padre con mejores genes de los dos segundos
    p = rand() % m; // Elige un índice aleatorio del tamaño de los cormosomas - O(1)
    hijos[i] = padre1.substr(0, p) + padre2.substr(p); // Se combina la primer mitad del primer padre con la segunda mitad del segundo - O(t)
    hijos[i+1] = padre2.substr(0, p) + padre1.substr(p); // Se hace lo mismo pero al revés para el segundo hijo - O(t)
  }
  return hijos;
}

// Se mutan los hijos - O(pm)
void mutation(vector<string> &hijos, int nMutacion) {
  int n = hijos.size(), m = hijos[0].size(), p; // Número de hijos y tamaño de los cromosomas - O(1)
  for (int i=0; i<n; i++) { // Se itera por los hijos - O(p) -> O(pm)
    // Los hijos siempre son del mismo tamaño de la población
    for (int j=0; j<nMutacion; j++) { // Se itera por el número de mutaciones - O(m)
      p = rand() % m; // Se elige un número aleatorio del cromosoma - O(1)
      hijos[i][p] = ABC[rand() % ABC.size()]; // Se cambia aleatoriamente un gen del cromosoma - O(1)
    }
  }
}

// Se checa si los hijos deben sustituir al padre - O(p)
void reinsertion(vector<string> &poblacion, vector<int> &fitness, vector<string> &hijos, vector<int> &fitnessHijos) {
  int n = poblacion.size(); // Tamaño de la población
  for (int i=0; i<n; i++) { // Se itera por la población - O(p)
    if (fitness[i] > fitnessHijos[i]) { // El hijo es mejor al padre?
      poblacion[i] = hijos[i]; // Se sustiture el padre por el hijo
      fitness[i] = fitnessHijos[i];
    }
  }
}

// Se encuentra al mejor cromosoma - O(p)
int findBest(vector<int> &fitness) {
  int n = fitness.size(), mejor = INF, idx=-1; // Tamaño de la población, mejor postor actual, índice del mejor postor - O(1)
  for (int i=0; i<n; i++) { // Se itera por la población - O(p)
    if (mejor > fitness[i]) { // Es mejor el postor actual que el mejor postor global?
      mejor = fitness[i]; // Se sustituye el mejor postor
      idx = i;
    }
  }
  return idx;
}