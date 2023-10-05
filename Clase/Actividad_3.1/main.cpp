#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Datos:
- Nombre: Santiago Vera Espinoza
- Matrícula: A01641585
- Fecha: 25/09/2023
- Clase: Análisis y diseño de algoritmos avanzados - TC2038
- Grupo: 570
- Profesores: Frumencio Olivas Alvarez y Faviel Francisco González Galarza

Variables de complejidad:

- pi: Número de palabras a insertar
- pb: Número de palabras a buscar
- n: Cantidad de letras en palabra a buscar
- a: Longitud del alfabeto (Tiende a ser constante esta variable - Ex. 26 letras del alfabeto)
- l: Longitud de la palabra más larga en el Trie
- v: Longitud del vector
*/

// Imprime el vector - O(v)
template <typename T>
void printVec(vector <T> input, string line = "Vector =")
{
    cout << "\n" << line << " [";
    for (int i=0; i<input.size(); i++) // Itera por el vector - O(v)
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

// Objeto Trie
class Trie {
    private:
        vector <Trie *> next_chars; // Todos los posibles siguientes caracteres
        char curr_char;
        bool is_word; // Es este caracter una palabra válida?

    public:
        Trie(){
            this->curr_char = '\0';
            this->is_word = false;
        }

        Trie(char n_char){
            this->curr_char = n_char;
            this->is_word = false;
        }

        // Esta nodo representa una palabra? - O(1)
        bool isWord(){
            return this->is_word;
        }

        void setIsWord(bool is_word){
            this->is_word = is_word;
        }

        char getChar(){
            return this->curr_char;
        }

        void setChar(char n_char){
            this->curr_char = n_char;
        }

        vector <Trie *> getChilds(){
            return this->next_chars;
        }

        void addChild(Trie *child){
            this->next_chars.push_back(child);
        }

        // Inserta una palabra en el ADT - O(na)
        void insertWord(string word){
            Trie *curr_char = this; // Crea un puntero al Trie actual para recorrer todo el ADT
            for (auto c:word){ // Itera por todos los caracteres de la palabra a insertar - O(na) -> O(n)
                bool found_char = false; // Bandera para saber si encontro el caracter en sus hijos
                for (auto child_char:curr_char->getChilds()){ // Busca el caracter en sus hijos - O(a) -> O(1) [Tiende a ser constante]
                    if (child_char->getChar() == c){ // Si encuentra el siguiente caracter el puntero ahora apunta a él
                        curr_char = child_char;
                        found_char = true; // Encontro el caracter
                        break;
                    }
                }
                if (!found_char){ // Si no encuentra el caracter, lo crea
                    Trie *n_char = new Trie(c); // Puntero dinámico
                    curr_char->addChild(n_char);
                    curr_char = n_char;
                }
                //cout << c << " -> " << curr_char->getChilds().size() << endl;
            }
            curr_char->setIsWord(true); // Al terminar de iterar setea el último Trie como true en su valor para saber si es palabra
        }

        // Verifica si una palabra es válida con el Trie - O(na)
        bool fetchWord(string word){
            Trie *curr_char = this; // Crea un puntero al Trie actual para recorrer todo el ADT
            for (auto c:word){ // Itera por todos los caracteres de la palabra a insertar - O(na) -> O(n)
                bool found_char = false; // Bandera para saber si encontro el caracter en sus hijos
                for (auto child_char:curr_char->getChilds()){ // Busca el caracter en sus hijos - O(a) -> O(1) [Tiende a ser constante]
                    if (child_char->getChar() == c){ // Si encuentra el siguiente caracter el puntero ahora apunta a él
                        curr_char = child_char;
                        found_char = true; // Encontro el caracter
                        break;
                    }
                }
                if (!found_char) return false; // Si no lo encuentra regresa falso
            }
            if (curr_char->isWord()) return true; // Si llega al final y es una palabra regresa verdadero
            return false; // En cualquier otro caso es falso
        }

        // Imprime el ADT - O(la) -> O(l)
        void printTrie(){
            queue <Trie*> queue;
            queue.push(this);

            cout << this->getChar() << endl;

            while (!queue.empty()){ // Inicia la impresión por nivel en el BFS - O(la) -> O(1)
                Trie* curr_el = queue.front();
                for (auto child:curr_el->getChilds()){ // Obtiene todos los hijos - O(a) -> O(1)
                    queue.push(child);
                    cout << curr_el->getChar() << " -> " << child->getChar() << " ";
                }
                cout << endl;
                queue.pop();
            }
        }
};

// Proceso principal - O(n(pi + pb))
void process()
{
    int n;

    cout << "Inserta el número de palabras a insertar: ";
    cin >> n;
    cout << endl;

    Trie words; // Crea el Trie
    
    for (int i = 0; i < n; i++) // Inserta en el Trie todas las palabras a insertar - O(pi*n)
    {
        cout << "Elemento " << i << ": ";
        string input;
        cin >> input, words.insertWord(input); // Inserta la palabra - O(n)
    }

    int m;

    cout << endl << "Inserta el número de palabras a buscar: ";
    cin >> m;
    cout << endl;

    vector <bool> result; // Vector con los resultados de todas las búsquedas
    
    for (int i = 0; i < m; i++) // Busca en el Trie todas las palabras a buscar - O(pb*n)
    {
        cout << "Elemento " << i << ": ";
        string input;
        cin >> input;
        result.push_back(words.fetchWord(input)); // Busca la palabra y la agrega al vector resultado - O(n)
    }

    printVec(result); // Imprime el vector - O(pb)
     
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