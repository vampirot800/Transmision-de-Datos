// Evidencia 1 Analisis de Algoritmos Avanzados
// Ramiro Flores
// Joseph Shakalo
// Fabrizio 

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Función para leer un archivo y devolver su contenido como un string
string readFile(const string &filename) {
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Función para buscar un substring en un archivo y retornar su posición o false si no lo encuentra
bool findSubstring(const string &transmission, const string &mcode, size_t &position) {
    position = transmission.find(mcode);
    return position != string::npos;
}

// Función para verificar si una cadena es un palíndromo
bool isPalindrome(const string &s) {
    return equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}

// Función para encontrar el palíndromo más largo en una cadena
pair<size_t, size_t> longestPalindrome(const string &str) {
    size_t maxLength = 1, start = 0;
    size_t n = str.size();

    // Tabla para guardar si un substring es palíndromo
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // Todos los substrings de longitud 1 son palíndromos
    for (size_t i = 0; i < n; ++i)
        dp[i][i] = true;

    // Revisa substrings de longitud 2
    for (size_t i = 0; i < n - 1; ++i) {
        if (str[i] == str[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Revisa substrings de longitud mayor a 2
    for (size_t k = 3; k <= n; ++k) {
        for (size_t i = 0; i < n - k + 1; ++i) {
            size_t j = i + k - 1;

            if (dp[i + 1][j - 1] && str[i] == str[j]) {
                dp[i][j] = true;

                if (k > maxLength) {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }

    return {start + 1, start + maxLength};
}

// Función para encontrar el substring común más largo entre dos cadenas
pair<size_t, size_t> longestCommonSubstring(const string &str1, const string &str2) {
    size_t n1 = str1.size(), n2 = str2.size();
    vector<vector <int>> lcs(n1 + 1, vector<int>(n2 + 1, 0));
    size_t maxLength = 0, endIdx = 0;

    for (size_t i = 1; i <= n1; ++i) {
        for (size_t j = 1; j <= n2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                if (lcs[i][j] > maxLength) {
                    maxLength = lcs[i][j];
                    endIdx = i - 1;
                }
            }
        }
    }

    return {endIdx - maxLength + 2, endIdx + 1};
}

int main() {
    // Leer los archivos de transmisión y mcode
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    string mcode1 = readFile("mcode1.txt");
    string mcode2 = readFile("mcode2.txt");
    string mcode3 = readFile("mcode3.txt");

    // Parte 1: Analizar si transmission1 y transmission2 contienen los mcode1, mcode2, mcode3
    size_t position;
    
    // transmission1
    cout << (findSubstring(transmission1, mcode1, position) ? "true " + to_string(position + 1) : "false") << endl;
    cout << (findSubstring(transmission1, mcode2, position) ? "true " + to_string(position + 1) : "false") << endl;
    cout << (findSubstring(transmission1, mcode3, position) ? "true " + to_string(position + 1) : "false") << endl;
    
    // transmission2
    cout << (findSubstring(transmission2, mcode1, position) ? "true " + to_string(position + 1) : "false") << endl;
    cout << (findSubstring(transmission2, mcode2, position) ? "true " + to_string(position + 1) : "false") << endl;
    cout << (findSubstring(transmission2, mcode3, position) ? "true " + to_string(position + 1) : "false") << endl;

    // Parte 2: Buscar el código "espejeado" más largo en cada archivo de transmisión
    pair<size_t, size_t> palindrome1 = longestPalindrome(transmission1);
    pair<size_t, size_t> palindrome2 = longestPalindrome(transmission2);

    cout << palindrome1.first << " " << palindrome1.second << endl;
    cout << palindrome2.first << " " << palindrome2.second << endl;

    // Parte 3: Substring común más largo entre los dos archivos de transmisión
    pair<size_t, size_t> lcs = longestCommonSubstring(transmission1, transmission2);
    cout << lcs.first << " " << lcs.second << endl;

    return 0;
}
