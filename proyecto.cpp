#include <iostream>     // Permite utilizar cout y cin para mostrar y recibir datos
#include <cstdlib>      // Permite utilizar rand() y srand() para generar numeros aleatorios
#include <ctime>        // Permite utilizar time() para cambiar los numeros aleatorios
#include <chrono>       // Permite medir el tiempo que tarda cada metodo

using namespace std;

// Se establece un limite maximo de 10000 numeros para el arreglo
const int MAX = 10000;

// Estas variables almacenan el tiempo que tarda cada metodo de ordenamiento
double tiempoBubble = 0;
double tiempoInsertion = 0;
double tiempoSelection = 0;
double tiempoMerge = 0;
double tiempoQuick = 0;
double tiempoCounting = 0;


// ==================================================
// BUBBLE SORT
// ==================================================

// Esta funcion ordena los numeros comparando elementos que estan juntos
void bubbleSort(int arreglo[], int cantidad)
{
    // Este ciclo controla la cantidad de recorridos que se hacen
    for (int i = 0; i < cantidad - 1; i++)
    {
        // Se comparan los elementos que estan uno al lado del otro
        for (int j = 0; j < cantidad - i - 1; j++)
        {
            // Si el elemento de la izquierda es mayor, se deben intercambiar
            if (arreglo[j] > arreglo[j + 1])
            {
                // Se utiliza una variable temporal para realizar el intercambio
                int temporal = arreglo[j];

                arreglo[j] = arreglo[j + 1];

                arreglo[j + 1] = temporal;
            }
        }
    }
}


// ==================================================
// INSERTION SORT
// ==================================================

// Esta funcion ordena los elementos colocando cada numero en su posicion
void insertionSort(int arreglo[], int cantidad)
{
    // Se empieza desde la segunda posicion porque la primera ya se considera ordenada
    for (int i = 1; i < cantidad; i++)
    {
        // Se guarda el elemento que se va a colocar en su posicion
        int actual = arreglo[i];

        // Se comienza a comparar con el elemento anterior
        int j = i - 1;

        // Se mueven los elementos mayores una posicion hacia la derecha
        while (j >= 0 && arreglo[j] > actual)
        {
            arreglo[j + 1] = arreglo[j];

            j--;
        }

        // Se coloca el elemento en la posicion que le corresponde
        arreglo[j + 1] = actual;
    }
}


// ==================================================
// SELECTION SORT
// ==================================================

// Esta funcion busca el elemento menor y lo coloca en la posicion correspondiente
void selectionSort(int arreglo[], int cantidad)
{
    // Recorre el arreglo buscando el menor elemento
    for (int i = 0; i < cantidad - 1; i++)
    {
        // Se toma la posicion actual como la del menor elemento
        int posicionMenor = i;

        // Se compara con los elementos que faltan por ordenar
        for (int j = i + 1; j < cantidad; j++)
        {
            // Si se encuentra un numero menor, se guarda su posicion
            if (arreglo[j] < arreglo[posicionMenor])
            {
                posicionMenor = j;
            }
        }

        // Se intercambia el elemento actual con el menor encontrado
        int temporal = arreglo[i];

        arreglo[i] = arreglo[posicionMenor];

        arreglo[posicionMenor] = temporal;
    }
}


// ==================================================
// MERGE SORT
// ==================================================

// Esta funcion une las dos partes del arreglo despues de ordenarlas
void mezclar(int arreglo[], int inicio, int medio, int fin)
{
    // Arreglo temporal donde se guardan los elementos ordenados
    int temporal[MAX];

    // i comienza en la primera parte del arreglo
    int i = inicio;

    // j comienza en la segunda parte del arreglo
    int j = medio + 1;

    // k indica la posicion donde se va guardando el resultado
    int k = inicio;

    // Se comparan los elementos de las dos partes
    while (i <= medio && j <= fin)
    {
        // Se guarda primero el elemento menor
        if (arreglo[i] <= arreglo[j])
        {
            temporal[k] = arreglo[i];

            i++;
        }
        else
        {
            temporal[k] = arreglo[j];

            j++;
        }

        k++;
    }

    // Si quedan elementos en la primera parte, se agregan
    while (i <= medio)
    {
        temporal[k] = arreglo[i];

        i++;
        k++;
    }

    // Si quedan elementos en la segunda parte, se agregan
    while (j <= fin)
    {
        temporal[k] = arreglo[j];

        j++;
        k++;
    }

    // Se pasan los elementos ordenados nuevamente al arreglo original
    for (i = inicio; i <= fin; i++)
    {
        arreglo[i] = temporal[i];
    }
}


// Esta funcion divide el arreglo en partes mas pequeñas
void mergeSort(int arreglo[], int inicio, int fin)
{
    // Se verifica que todavia existan elementos para dividir
    if (inicio < fin)
    {
        // Se calcula la posicion del medio del arreglo
        int medio = (inicio + fin) / 2;

        // Se ordena la primera mitad
        mergeSort(arreglo, inicio, medio);

        // Se ordena la segunda mitad
        mergeSort(arreglo, medio + 1, fin);

        // Se unen las dos partes que ya fueron ordenadas
        mezclar(arreglo, inicio, medio, fin);
    }
}


// ==================================================
// QUICK SORT
// ==================================================

// Esta funcion divide el arreglo utilizando un elemento llamado pivote
int particion(int arreglo[], int inicio, int fin)
{
    // Se toma el ultimo elemento como pivote
    int pivote = arreglo[fin];

    // Esta variable indica donde colocar los elementos menores
    int i = inicio - 1;

    // Se recorren los elementos hasta antes del pivote
    for (int j = inicio; j < fin; j++)
    {
        // Si el elemento es menor que el pivote, se mueve hacia la izquierda
        if (arreglo[j] < pivote)
        {
            i++;

            // Se intercambia el elemento encontrado
            int temporal = arreglo[i];

            arreglo[i] = arreglo[j];

            arreglo[j] = temporal;
        }
    }

    // Se coloca el pivote entre los elementos menores y mayores
    int temporal = arreglo[i + 1];

    arreglo[i + 1] = arreglo[fin];

    arreglo[fin] = temporal;

    // Se devuelve la posicion final del pivote
    return i + 1;
}


// Esta funcion aplica Quick Sort a las partes del arreglo
void quickSort(int arreglo[], int inicio, int fin)
{
    // Se verifica que haya mas de un elemento para ordenar
    if (inicio < fin)
    {
        // Se obtiene la posicion del pivote
        int posicion = particion(arreglo, inicio, fin);

        // Se ordena la parte izquierda del pivote
        quickSort(arreglo, inicio, posicion - 1);

        // Se ordena la parte derecha del pivote
        quickSort(arreglo, posicion + 1, fin);
    }
}


// ==================================================
// COUNTING SORT
// ==================================================

// Esta funcion ordena contando cuantas veces aparece cada numero
void countingSort(int arreglo[], int cantidad)
{
    // Como los numeros van de 0 a 999, se utiliza un arreglo de 1000 posiciones
    int conteo[1000] = {0};

    // Se cuenta cuantas veces aparece cada numero
    for (int i = 0; i < cantidad; i++)
    {
        conteo[arreglo[i]]++;
    }

    // Indica la posicion donde se volveran a colocar los numeros
    int posicion = 0;

    // Se recorren todos los posibles numeros desde 0 hasta 999
    for (int numero = 0; numero < 1000; numero++)
    {
        // Se coloca cada numero la cantidad de veces que fue contado
        while (conteo[numero] > 0)
        {
            arreglo[posicion] = numero;

            posicion++;

            conteo[numero]--;
        }
    }
}


// ==================================================
// COPIAR ARREGLO
// ==================================================

// Esta funcion copia los numeros originales para que cada metodo trabaje con los mismos datos
void copiarArreglo(int original[], int copia[], int cantidad)
{
    // Se recorren todos los elementos del arreglo original
    for (int i = 0; i < cantidad; i++)
    {
        copia[i] = original[i];
    }
}


// ==================================================
// GENERAR NUMEROS
// ==================================================

// Esta funcion genera numeros aleatorios entre 0 y 999
void generarNumeros(int arreglo[], int cantidad)
{
    // Se repite hasta generar la cantidad solicitada por el usuario
    for (int i = 0; i < cantidad; i++)
    {
        // rand() genera un numero y % 1000 limita el resultado entre 0 y 999
        arreglo[i] = rand() % 1000;
    }
}


// ==================================================
// MOSTRAR ARREGLO
// ==================================================

// Esta funcion muestra en pantalla los numeros generados
void mostrarArreglo(int arreglo[], int cantidad)
{
    // Se recorren todos los numeros almacenados
    for (int i = 0; i < cantidad; i++)
    {
        cout << arreglo[i] << " ";

        // Cada 20 numeros se realiza un salto de linea para facilitar la lectura
        if ((i + 1) % 20 == 0)
        {
            cout << endl;
        }
    }

    cout << endl;
}


// ==================================================
// EJECUTAR BUBBLE SORT
// ==================================================

void ejecutarBubble(int original[], int cantidad)
{
    // Se crea una copia para no modificar los numeros originales
    int copia[MAX];

    copiarArreglo(original, copia, cantidad);

    // Se guarda el tiempo justo antes de ejecutar el metodo
    auto inicio = chrono::high_resolution_clock::now();

    bubbleSort(copia, cantidad);

    // Se guarda el tiempo despues de terminar el ordenamiento
    auto fin = chrono::high_resolution_clock::now();

    // Se calcula la diferencia entre el inicio y el final en milisegundos
    tiempoBubble =
        chrono::duration<double, milli>(fin - inicio).count();

    cout << "Bubble Sort terminado." << endl;
    cout << "Tiempo: " << tiempoBubble << " ms" << endl;
}


// ==================================================
// EJECUTAR INSERTION SORT
// ==================================================

void ejecutarInsertion(int original[], int cantidad)
{
    // Se crea una copia para que el arreglo original no sea modificado
    int copia[MAX];

    copiarArreglo(original, copia, cantidad);

    // Se guarda el tiempo antes de ordenar
    auto inicio = chrono::high_resolution_clock::now();

    insertionSort(copia, cantidad);

    // Se guarda el tiempo despues de ordenar
    auto fin = chrono::high_resolution_clock::now();

    // Se calcula el tiempo que tardo el algoritmo
    tiempoInsertion =
        chrono::duration<double, milli>(fin - inicio).count();

    cout << "Insertion Sort terminado." << endl;
    cout << "Tiempo: " << tiempoInsertion << " ms" << endl;
}


// ==================================================
// EJECUTAR SELECTION SORT
// ==================================================

void ejecutarSelection(int original[], int cantidad)
{
    // Se copia el arreglo original
    int copia[MAX];

    copiarArreglo(original, copia, cantidad);

    // Se inicia la medicion del tiempo
    auto inicio = chrono::high_resolution_clock::now();

    selectionSort(copia, cantidad);

    // Se termina la medicion del tiempo
    auto fin = chrono::high_resolution_clock::now();

    // Se calcula el tiempo de ejecucion
    tiempoSelection =
        chrono::duration<double, milli>(fin - inicio).count();

    cout << "Selection Sort terminado." << endl;
    cout << "Tiempo: " << tiempoSelection << " ms" << endl;
}


// ==================================================
// EJECUTAR MERGE SORT
// ==================================================

void ejecutarMerge(int original[], int cantidad)
{
    // Se crea una copia para utilizar los mismos datos originales
    int copia[MAX];

    copiarArreglo(original, copia, cantidad);

    // Se inicia la medicion del tiempo
    auto inicio = chrono::high_resolution_clock::now();

    mergeSort(copia, 0, cantidad - 1);

    // Se termina la medicion del tiempo
    auto fin = chrono::high_resolution_clock::now();

    // Se obtiene el tiempo que tardo Merge Sort
    tiempoMerge =
        chrono::duration<double, milli>(fin - inicio).count();

    cout << "Merge Sort terminado." << endl;
    cout << "Tiempo: " << tiempoMerge << " ms" << endl;
}


// ==================================================
// EJECUTAR QUICK SORT
// ==================================================

void ejecutarQuick(int original[], int cantidad)
{
    // Se crea una copia del arreglo original
    int copia[MAX];

    copiarArreglo(original, copia, cantidad);

    // Se inicia la medicion del tiempo
    auto inicio = chrono::high_resolution_clock::now();

    quickSort(copia, 0, cantidad - 1);

    // Se termina la medicion del tiempo
    auto fin = chrono::high_resolution_clock::now();

    // Se obtiene el tiempo de ejecucion
    tiempoQuick =
        chrono::duration<double, milli>(fin - inicio).count();

    cout << "Quick Sort terminado." << endl;
    cout << "Tiempo: " << tiempoQuick << " ms" << endl;
}


// ==================================================
// EJECUTAR COUNTING SORT
// ==================================================

void ejecutarCounting(int original[], int cantidad)
{
    // Se crea una copia del arreglo para mantener los datos originales
    int copia[MAX];

    copiarArreglo(original, copia, cantidad);

    // Se inicia la medicion del tiempo
    auto inicio = chrono::high_resolution_clock::now();

    countingSort(copia, cantidad);

    // Se termina la medicion del tiempo
    auto fin = chrono::high_resolution_clock::now();

    // Se calcula el tiempo que tardo Counting Sort
    tiempoCounting =
        chrono::duration<double, milli>(fin - inicio).count();

    cout << "Counting Sort terminado." << endl;
    cout << "Tiempo: " << tiempoCounting << " ms" << endl;
}


// ==================================================
// EJECUTAR TODOS LOS METODOS
// ==================================================

void ejecutarTodos(int original[], int cantidad)
{
    cout << endl;
    cout << "Ejecutando todos los metodos..." << endl;
    cout << endl;

    // Se ejecutan todos los metodos utilizando el mismo arreglo original
    ejecutarBubble(original, cantidad);
    ejecutarInsertion(original, cantidad);
    ejecutarSelection(original, cantidad);
    ejecutarMerge(original, cantidad);
    ejecutarQuick(original, cantidad);
    ejecutarCounting(original, cantidad);
}


// ==================================================
// SUBMENU DE ORDENAMIENTO
// ==================================================

void submenuOrdenamiento(int original[], int cantidad)
{
    int opcion;

    // El submenu se repite hasta que el usuario seleccione regresar
    do
    {
        cout << endl;
        cout << "===== METODOS DE ORDENAMIENTO =====" << endl;
        cout << "1. Bubble Sort" << endl;
        cout << "2. Insertion Sort" << endl;
        cout << "3. Selection Sort" << endl;
        cout << "4. Merge Sort" << endl;
        cout << "5. Quick Sort" << endl;
        cout << "6. Counting Sort" << endl;
        cout << "7. Todos los metodos" << endl;
        cout << "8. Regresar" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        // Dependiendo de la opcion se ejecuta un metodo diferente
        switch (opcion)
        {
            case 1:
                ejecutarBubble(original, cantidad);
                break;

            case 2:
                ejecutarInsertion(original, cantidad);
                break;

            case 3:
                ejecutarSelection(original, cantidad);
                break;

            case 4:
                ejecutarMerge(original, cantidad);
                break;

            case 5:
                ejecutarQuick(original, cantidad);
                break;

            case 6:
                ejecutarCounting(original, cantidad);
                break;

            case 7:
                ejecutarTodos(original, cantidad);
                break;

            case 8:
                cout << "Regresando..." << endl;
                break;

            default:
                cout << "Opcion no valida." << endl;
        }

    } while (opcion != 8);
}


// ==================================================
// MOSTRAR RESULTADOS
// ==================================================

// Esta funcion muestra los tiempos obtenidos por cada metodo
void mostrarResultados()
{
    cout << endl;
    cout << "===== RESULTADOS =====" << endl;

    cout << "Bubble Sort: "
         << tiempoBubble << " ms" << endl;

    cout << "Insertion Sort: "
         << tiempoInsertion << " ms" << endl;

    cout << "Selection Sort: "
         << tiempoSelection << " ms" << endl;

    cout << "Merge Sort: "
         << tiempoMerge << " ms" << endl;

    cout << "Quick Sort: "
         << tiempoQuick << " ms" << endl;

    cout << "Counting Sort: "
         << tiempoCounting << " ms" << endl;
}


// ==================================================
// PROGRAMA PRINCIPAL
// ==================================================

int main()
{
    // Se crea el arreglo donde se almacenaran los numeros aleatorios
    int numeros[MAX];

    // Al principio no se ha generado ninguna cantidad de numeros
    int cantidad = 0;

    int opcion;

    // Permite que los numeros aleatorios sean diferentes en cada ejecucion
    srand(time(NULL));

    // El menu se repite hasta que el usuario seleccione la opcion 6
    do
    {
        cout << endl;
        cout << "===== MENU PRINCIPAL =====" << endl;
        cout << "1. Generar numeros aleatorios" << endl;
        cout << "2. Mostrar numeros generados" << endl;
        cout << "3. Ordenar con un metodo" << endl;
        cout << "4. Comparar todos los metodos" << endl;
        cout << "5. Mostrar resultados" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        // Se utiliza switch para ejecutar la opcion seleccionada
        switch (opcion)
        {
            case 1:

                cout << "Ingrese la cantidad de numeros: ";
                cin >> cantidad;

                // Se verifica que la cantidad este dentro del limite permitido
                if (cantidad > 0 && cantidad <= MAX)
                {
                    // Se generan los numeros aleatorios
                    generarNumeros(numeros, cantidad);

                    cout << "Numeros generados correctamente."
                         << endl;
                }
                else
                {
                    // Si la cantidad no es valida, se muestra un mensaje
                    cout << "Cantidad no valida." << endl;

                    // Se vuelve a colocar cantidad en cero
                    cantidad = 0;
                }

                break;


            case 2:

                // Se verifica que primero se hayan generado numeros
                if (cantidad > 0)
                {
                    mostrarArreglo(numeros, cantidad);
                }
                else
                {
                    cout << "Primero debe generar los numeros."
                         << endl;
                }

                break;


            case 3:

                // Se verifica que existan numeros antes de ordenarlos
                if (cantidad > 0)
                {
                    submenuOrdenamiento(numeros, cantidad);
                }
                else
                {
                    cout << "Primero debe generar los numeros."
                         << endl;
                }

                break;


            case 4:

                // Se ejecutan los seis metodos para poder comparar sus tiempos
                if (cantidad > 0)
                {
                    ejecutarTodos(numeros, cantidad);
                }
                else
                {
                    cout << "Primero debe generar los numeros."
                         << endl;
                }

                break;


            case 5:

                // Muestra los tiempos registrados de los diferentes metodos
                mostrarResultados();

                break;


            case 6:

                cout << "Programa finalizado." << endl;

                break;


            default:

                // Se muestra este mensaje cuando se ingresa una opcion diferente
                cout << "Opcion no valida." << endl;
        }

    } while (opcion != 6);

    return 0;
}