// Evidencia 1 Analisis de Algoritmos Avanzados
// Ramiro Flores
// Joseph Shakalo
// Fabrizio Barrios
// 31/10/2024

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Función para leer el contenido de un archivo y devolverlo como una cadena de texto
string readFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return "";
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

// Función para buscar un substring dentro de una cadena
// Retorna true y la posición si se encuentra, o false si no se encuentra
bool findSubstring(const string &transmission, const string &mcode, size_t &position) {
    position = transmission.find(mcode);
    return position != string::npos;
}

// Función para encontrar el palíndromo más largo en una cadena
// Retorna la posición inicial y final del palíndromo más largo
pair<size_t, size_t> longestPalindrome(const string &str) {
    size_t maxLength = 1, start = 0;
    vector<vector<bool>> dp(str.size(), vector<bool>(str.size(), false));

    for (size_t i = 0; i < str.size(); ++i) 
        dp[i][i] = true;

    for (size_t i = 0; i < str.size() - 1; ++i) {
        if (str[i] == str[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    for (size_t k = 3; k <= str.size(); ++k) {
        for (size_t i = 0; i < str.size() - k + 1; ++i) {
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
// Retorna la posición inicial y final del substring común más largo en la primera cadena
pair<size_t, size_t> longestCommonSubstring(const string &str1, const string &str2) {
    size_t maxLength = 0, endIdx = 0;
    vector<vector<int>> lcs(str1.size() + 1, vector<int>(str2.size() + 1, 0));

    for (size_t i = 1; i <= str1.size(); ++i) {
        for (size_t j = 1; j <= str2.size(); ++j) {
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

    // Leer el contenido de los archivos de transmisión y de código malicioso
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    string mcode1 = readFile("mcode1.txt");
    string mcode2 = readFile("mcode2.txt");
    string mcode3 = readFile("mcode3.txt");

    size_t position;

    // Parte 1: Verificar si transmission1 y transmission2 contienen mcode1, mcode2, mcode3

    // Para transmission1
    if (findSubstring(transmission1, mcode1, position)) {
        cout << "mcode1 encontrado en transmission1 desde la posición: " << position + 1 << endl;
    } else {
        cout << "mcode1 no se encontró en transmission1" << endl;
    }

    if (findSubstring(transmission1, mcode2, position)) {
        cout << "mcode2 encontrado en transmission1 desde la posición: " << position + 1 << endl;
    } else {
        cout << "mcode2 no se encontró en transmission1" << endl;
    }

    if (findSubstring(transmission1, mcode3, position)) {
        cout << "mcode3 encontrado en transmission1 desde la posición: " << position + 1 << endl;
    } else {
        cout << "mcode3 no se encontró en transmission1" << endl;
    }

    // Para transmission2
    if (findSubstring(transmission2, mcode1, position)) {
        cout << "mcode1 encontrado en transmission2 desde la posición: " << position + 1 << endl;
    } else {
        cout << "mcode1 no se encontró en transmission2" << endl;
    }

    if (findSubstring(transmission2, mcode2, position)) {
        cout << "mcode2 encontrado en transmission2 desde la posición: " << position + 1 << endl;
    } else {
        cout << "mcode2 no se encontró en transmission2" << endl;
    }

    if (findSubstring(transmission2, mcode3, position)) {
        cout << "mcode3 encontrado en transmission2 desde la posición: " << position + 1 << endl;
    } else {
        cout << "mcode3 no se encontró en transmission2" << endl;
    }
        cout << endl;

    // Parte 2: Buscar el palíndromo más largo en cada archivo de transmisión
    auto palindrome1 = longestPalindrome(transmission1);
    auto palindrome2 = longestPalindrome(transmission2);

    cout << "El palíndromo más largo en transmission1 está entre las posiciones: " << palindrome1.first << " y " << palindrome1.second << endl;
    cout << "El palíndromo más largo en transmission2 está entre las posiciones: " << palindrome2.first << " y " << palindrome2.second << endl;
    cout << endl;

    // Parte 3: Buscar el substring común más largo entre los dos archivos de transmisión
    auto lcs = longestCommonSubstring(transmission1, transmission2);
    cout << "El substring común más largo entre transmission1 y transmission2 está entre las posiciones: " << lcs.first << " y " << lcs.second << " en transmission1" << endl;
    cout << endl;

    return 0;
}
