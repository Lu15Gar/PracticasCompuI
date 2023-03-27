#include <iostream>
#include <array>

// Añadir std para fácil llamado de funciones
using namespace std;

//// Declaración de funciones
//Definimos un template (un tipo de dato) para nuestra matriz
template <typename matriz>
void LlenarMatriz(matriz & miMatriz);

template <typename matriz>
void ImprimirMatriz(matriz & miMatriz);

template <typename matriz>
void GaussJordan(matriz & miMatriz);

template <typename matriz>
void ImprimirSolucion(matriz & miMatriz);


int main()
{
    // Definimos el número de variables de nuestro sistema
    const int variables = 3;
    // El número de columnas será el número de variables más su solición para cada ecuación
    const int columnas = variables + 1;

    // Inicializamos la matriz que vamos a ocupar
    array <array<float, columnas>, variables> miMatriz = { 0 };

    // Pedimos al usuario que llene la matriz
    LlenarMatriz(miMatriz);

    // Aplicamos el método de Gauss-Jordan sobre nuestra matriz
    GaussJordan(miMatriz);

    // Imprimimos la solución de la matriz
    ImprimirSolucion(miMatriz);

    //ImprimirMatriz(miMatriz);

    return 0; // Indicamos que salimos del programa con éxito
}

/*
Llena 'miMatriz' con valores ingresados por el usuario para cada elemento.
No regresa ningún valor.
*/
template <typename matriz>
void LlenarMatriz(matriz & miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        for (int j = 0; j <= variables; j++) {
            cout << "Valor elemento [" << i << "][" << j << "]: ";
            cin >> miMatriz[i][j];
        }
    }
}

/*
Imprime cada elemento de 'miMatriz' emulando una matriz con corchetes cuadrados.
No regresa ningún valor.
*/
template <typename matriz>
void ImprimirMatriz(matriz & miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++)
            cout << miMatriz[i][j] << '\t';
        cout << "]\n";
    }
}

/*
Imprime en pantalla la solución para cada variable del sistema de ecuaciones correspondiente a los valores en 'miMatriz'.
No regresa ningún valor.
*/
template <typename matriz>
void ImprimirSolucion(matriz & miMatriz)
{
    int variables = miMatriz.size();
    cout << endl <<  "Soluciones:" << "\n";
    for (int i = 0; i < variables; i++) {
        cout << "\n"  << "x" << (i - 1) + 1 << " = " << miMatriz[i][variables] << endl;
    }
}

/*
Implementa el algoritmo de Gauss-Jordan sobre 'miMatriz', finalizando en ella la solución del algoritmo.
No regresa ningún valor.
*/
template <typename matriz>
void GaussJordan(matriz & miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        // Buscar el valor máximo en la columna actual
        float maxVal = abs(miMatriz[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < variables; k++) {
            if (abs(miMatriz[k][i]) > maxVal) {
                maxVal = abs(miMatriz[k][i]);
                maxRow = k;
            }
        }

        // Intercambiar filas máximas, si es necesario
        if (maxRow != i) {
            for (int k = i; k < variables + 1; k++) {
                swap(miMatriz[maxRow][k], miMatriz[i][k]);
            }
        }

        // Hacer todos los elementos debajo de esta fila 0 en la columna actual
        for (int k = i + 1; k < variables; k++) {
            float factor = -miMatriz[k][i] / miMatriz[i][i];
            for (int j = i; j < variables + 1; j++) {
                miMatriz[k][j] += factor * miMatriz[i][j];
            }
        }
    }

    // Resolver ecuaciones en la matriz
    for (int i = variables - 1; i >= 0; i--) {
        miMatriz[i][variables] /= miMatriz[i][i];
        miMatriz[i][i] = 1;

        // Hacer todos los elementos de las filas anteriores 0 en la columna actual
        for (int k = i - 1; k >= 0; k--) {
            float factor = -miMatriz[k][i];
            miMatriz[k][i] += factor * miMatriz[i][i];
            miMatriz[k][variables] += factor * miMatriz[i][variables];
        }
    }
}


