// Analisis de Algoritmos Avanzados
// Evidencia 1:  Actividad Integradora 1
// Ramiro Flores
// Joseph Shakalo
// Fabrizio Barrios
// 31/10/2024

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Función para leer un archivo y devolver su contenido como un string
string readFile(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error al abrir el archivo: " << filename << endl;
    return "";
  }
  string content((istreambuf_iterator<char>(file)),
                 istreambuf_iterator<char>());
  file.close();
  return content;
}

// Función para buscar un substring en un archivo y retornar su posición 
bool findSubstring(const string &transmission, const string &mcode,
                   size_t &position) {
  position = transmission.find(mcode);
  return position != string::npos;
}

// Función para remover espacios de una cadena
string removeSpaces(const string &str) {
  string result;
  copy_if(str.begin(), str.end(), back_inserter(result),
          [](char c) { return !isspace(c); });
  return result;
}

// Función modificada para encontrar el palíndromo más largo
pair<size_t, size_t> longestPalindrome(const string &original_str) {
  string str = removeSpaces(original_str);
  vector<size_t> position_map;
  for (size_t i = 0; i < original_str.length(); i++) {
    if (!isspace(original_str[i])) {
      position_map.push_back(i);
    }
  }

  size_t maxLength = 1, start = 0;
  size_t n = str.size();

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

  // Convertir las posiciones de la cadena sin espacios
  size_t original_start = position_map[start];
  size_t original_end = position_map[start + maxLength - 1];

  return {original_start + 1, original_end + 1};
}

// Función para encontrar el substring común más largo entre dos cadenas
pair<size_t, size_t> longestCommonSubstring(const string &str1,
                                            const string &str2) {
  size_t n1 = str1.size(), n2 = str2.size();
  vector<vector<int>> lcs(n1 + 1, vector<int>(n2 + 1, 0));
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

  // Verificar si los archivos fueron leídos correctamente
  if (transmission1.empty() || transmission2.empty() || mcode1.empty() ||
      mcode2.empty() || mcode3.empty()) {
    cerr << "Uno o más archivos de entrada no pudieron ser leídos. Saliendo "
            "del programa."
         << endl;
    return 1;
  }

  // Parte 1: Analizar si transmission1 y transmission2 contienen los mcode1, mcode2, mcode3
  size_t position;

  // transmission1
  if (findSubstring(transmission1, mcode1, position)) {
    cout << "mcode1 encontrado en transmission1 en la posición: " << position + 1
         << endl;
  } else {
    cout << "mcode1 no se encontró en transmission1" << endl;
  }

  if (findSubstring(transmission1, mcode2, position)) {
    cout << "mcode2 encontrado en transmission1 en la posición: " << position + 1
         << endl;
  } else {
    cout << "mcode2 no se encontró en transmission1" << endl;
  }

  if (findSubstring(transmission1, mcode3, position)) {
    cout << "mcode3 encontrado en transmission1 en la posición: " << position + 1
         << endl;
  } else {
    cout << "mcode3 no se encontró en transmission1" << endl;
  }

  // transmission2
  if (findSubstring(transmission2, mcode1, position)) {
    cout << "mcode1 encontrado en transmission2 en la posición: " << position + 1
         << endl;
  } else {
    cout << "mcode1 no se encontró en transmission2" << endl;
  }

  if (findSubstring(transmission2, mcode2, position)) {
    cout << "mcode2 encontrado en transmission2 en la posición: " << position + 1
         << endl;
  } else {
    cout << "mcode2 no se encontró en transmission2" << endl;
  }

  if (findSubstring(transmission2, mcode3, position)) {
    cout << "mcode3 encontrado en transmission2 en la posición: " << position + 1
         << endl;
  } else {
    cout << "mcode3 no se encontró en transmission2" << endl;
  }
  cout << endl;

  // Parte 2: Buscar el código "espejeado" más largo en cada archivo de transmisión
  pair<size_t, size_t> palindrome1 = longestPalindrome(transmission1);
  pair<size_t, size_t> palindrome2 = longestPalindrome(transmission2);

  cout << "El palíndromo más largo en transmission1 está entre las posiciones: "
       << palindrome1.first << " y " << palindrome1.second << endl;

  cout << "El palíndromo más largo en transmission2 está entre las posiciones: "
       << palindrome2.first << " y " << palindrome2.second << endl;
  cout << endl;

  // Parte 3: Substring común más largo entre los dos archivos de transmisión
  pair<size_t, size_t> lcs =
      longestCommonSubstring(transmission1, transmission2);
  cout << "El substring común más largo entre transmission1 y transmission2: "
          "está entre las posiciones "
       << lcs.first << " y " << lcs.second << " en transmission1" << endl;

  return 0;
}