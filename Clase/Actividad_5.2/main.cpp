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

- n: Número de elementos

- v: Elementos en un vector
*/

string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";

void initialPopulation(vector<string> &poblacion, string objetivo);
vector<int> objectiveFunction(vector<string> &poblacion, string objetivo);
void printPopulation(vector<string> &poblacion, vector<int> &fitness);
vector<string> crossover(vector<string> &poblacion, vector<int> &fitness);
void mutation(vector<string> &hijos, int nMutacion);
void reinsertion(vector<string> &poblacion, vector<int> &fitness, vector<string> &hijos, vector<int> &fitnessHijos);
int findBest(vector<int> &fitness);

int main() {
  srand(time(NULL));
  string objetivo = "Tec de Monterrey", best;
  int iteraciones = 10000, sizePop = 30, nMutacion = 3, globalBest = INF, idx;
  vector<string> poblacion(sizePop), hijos;
  vector<int> fitness, fitnessHijos;
  initialPopulation(poblacion, objetivo);
  fitness = objectiveFunction(poblacion, objetivo);
  cout << "Poblacion inicial:" << endl;
  printPopulation(poblacion, fitness);
  int iter = 0;
  while (iter < iteraciones && globalBest > 0) {
  // while (globalBest > 0) {
    iter++;
    hijos = crossover(poblacion, fitness);
    mutation(hijos, nMutacion);
    fitnessHijos = objectiveFunction(hijos, objetivo);
    reinsertion(poblacion, fitness, hijos, fitnessHijos);
    idx = findBest(fitness);
    if (globalBest > fitness[idx]) {
      globalBest = fitness[idx];
      best = poblacion[idx];
      cout << iter << " " << best << " " << globalBest << endl;
    }
  }
  cout << "Poblacion final:" << endl;
  printPopulation(poblacion, fitness);
}

void initialPopulation(vector<string> &poblacion, string objetivo) {
  int n = poblacion.size(), m = objetivo.size();
  string individuo;
  for (int i=0; i<n; i++) {
    individuo = "";
    for (int j=0; j<m; j++) {
      individuo += ABC[rand() % ABC.size()];
    }
    poblacion[i] = individuo;
  }
}

vector<int> objectiveFunction(vector<string> &poblacion, string objetivo) {
  // Agrega tu codigo aqui para que el algoritmo funcione
  // la salida es un vector de enteros llamado fitness
  // cada individuo de la poblacion debe tener su propio valor de fitness
  vector <int> fitness;

  for (auto cromosoma:poblacion) {
    int t_fitness = objetivo.size();
    for (int i=0; i<objetivo.size(); i++) {
      if (cromosoma[i] == objetivo[i]) t_fitness--;
    }
    fitness.push_back(t_fitness);
  }

  return fitness;
}

void printPopulation(vector<string> &poblacion, vector<int> &fitness) {
  int n = poblacion.size();
  for (int i=0; i<n; i++) {
    cout << poblacion[i] << " " << fitness[i] << endl;
  }
  cout << endl;
}

vector<string> crossover(vector<string> &poblacion, vector<int> &fitness) {
  int n = poblacion.size(), m = poblacion[0].size();
  vector<string> hijos(n);
  string padre1, padre2;
  int a,b,c,d,p;
  for (int i=0; i<n; i+=2) {
    a = rand() % n;
    b = rand() % n;
    c = rand() % n;
    d = rand() % n;
    padre1 = fitness[a] < fitness[b] ? poblacion[a] : poblacion[b];
    padre2 = fitness[c] < fitness[d] ? poblacion[c] : poblacion[d];
    p = rand() % m;
    hijos[i] = padre1.substr(0, p) + padre2.substr(p);
    hijos[i+1] = padre2.substr(0, p) + padre1.substr(p);
  }
  return hijos;
}

void mutation(vector<string> &hijos, int nMutacion) {
  int n = hijos.size(), m = hijos[0].size(), p;
  for (int i=0; i<n; i++) {
    for (int j=0; j<nMutacion; j++) {
      p = rand() % m;
      hijos[i][p] = ABC[rand() % ABC.size()];
    }
  }
}

void reinsertion(vector<string> &poblacion, vector<int> &fitness, vector<string> &hijos, vector<int> &fitnessHijos) {
  int n = poblacion.size();
  for (int i=0; i<n; i++) {
    if (fitness[i] > fitnessHijos[i]) {
      poblacion[i] = hijos[i];
      fitness[i] = fitnessHijos[i];
    }
  }
}

int findBest(vector<int> &fitness) {
  int n = fitness.size(), mejor = INF, idx=-1;
  for (int i=0; i<n; i++) {
    if (mejor > fitness[i]) {
      mejor = fitness[i];
      idx = i;
    }
  }
  return idx;
}