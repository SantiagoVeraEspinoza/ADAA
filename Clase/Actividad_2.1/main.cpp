#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "sha256.h"

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

- n: Cantidad de palabras
- m: Cantidad de caracteres (palabra más larga)
*/

 // Djb2 hash fucntion - O(m)
unsigned long djb2(unsigned char *str) {
  unsigned long hash = 5381; // Asigna un numero primo alto
  int c;
  while (c = *str++) { // Itera por la palabra hasta encontrar un caracter nulo - O(m)
    hash = ((hash << 7) + hash) + c; // hash * 33 + c - Desplaza el hash 7 bits, se le suma lo que tenía y se le suma el valor del apuntador
    // Con 7 como desplazador de bit se reduce notoriamente la cantidad de colisiones
	}

  return hash;
}

// Método main - O((n^2)m)
int main() {
  int collisions = 0; // Guarda las colisiones con el método djb2 modificado y sha256
  int sha_collisions = 0;

  unsigned long n; // Variable de las keys de ambos métodos
  string n_sha;

  fstream newfile; // Stream para leer txt
  string word; // Palabra leída
  vector<string> words; // Arreglo de palabras

  map<unsigned long, string> mapDJB2; // Mapa de keys djb2 y sha256
  map<string, string> mapSHA256;

	newfile.open("words.txt", ios::in); // Abre el archivo txt
	if (newfile.is_open()) {
    while (getline(newfile, word)) { // Lee cada línea del archivo - O(n)
			words.push_back(word); // Lo agrega al vector - O(1)
		}
		newfile.close();
	}

  vector <string> collisions_output; // Vector para guardar la info de la colisión
  for (int i=0; i<words.size(); i++){ // Se itera por todas las palabras - O(n) = O((n^2)m)

    n = djb2((unsigned char *)words[i].c_str()); // Key por djb2 - O(m)
    n_sha = SHA256::cifrar(words[i]); // Key por sha256 - O(m)

    if (mapDJB2.find(n) != mapDJB2.end()){ // Colisión en djb2 - O(n)
      // Guarda un string sobre la colisión con: Índice de la palabra - Palabra - Hash Value de la palabra - Palabra que tenía el mismo Hash Value
      collisions_output.push_back(to_string(i) + " " + words[i] + " " + to_string(n) + " " + mapDJB2[n]); // String con datos de la colisión - O(n)
      collisions++;
    }
    if (mapSHA256.find(n_sha) != mapSHA256.end()){ // Colisión en sha256
      sha_collisions++;
    }

    mapDJB2[n] = words[i]; // Asigna un valor en el avl de ambos
    mapSHA256[n_sha] = words[i];
  }

  // Imprime resultados - O(1)
  cout << "Total palabras = " << words.size() << endl;
  cout << "\nColisiones de DJB2 = " << collisions << endl;
  for (auto e:collisions_output)
  {
    cout << e << endl;
  }
  cout << "\nColisiones de SHA256 = " << sha_collisions << endl;
}
