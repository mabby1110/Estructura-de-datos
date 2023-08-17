**Nombre:** Bernardo A. Márquez González  
**Materia:** Estructura de datos, [[C]]
**Profesor:** Zaira Zuviría

---
<br><br><br><br><br>
![[UAG logo.svg]]<br><br><br><br><br><br><br><br>
Fecha de entrega: 2023-08-04

---
# Reflexion
  
Los métodos de ordenamiento son como la manera en que organizamos nuestras cosas en casa para encontrarlas fácilmente. Imagina tu habitación: cuando colocas tus libros en estantes o tu ropa en cajones, todo se vuelve más ordenado y puedes acceder a lo que necesitas sin problemas. De la misma forma, en la programación y la computación, usamos métodos de ordenamiento para organizar listas de información, como números o nombres, para que podamos buscar y trabajar con esos datos de manera eficiente. Cada método de ordenamiento es como una herramienta diferente para poner en orden las cosas, y elegimos la que mejor se adapte a la situación, al igual que eliges si guardar tus zapatos en un estante o en un cajón en función de lo que sea más práctico.

# Shell
```c
#include <stdio.h>

void shellSort(int arr[], int n, int gap) {
    if (gap > 0) {
        int i, j, temp;
        for (i = gap; i < n; i++) {
            temp = arr[i];
            j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j = j - gap;
            }
            arr[j] = temp;
        }
        // Reducir el tamaño de la brecha y aplicar recursivamente
        shellSort(arr, n, gap / 2);
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int gap = n / 2;

    printf("Arreglo original:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    shellSort(arr, n, gap);

    printf("Arreglo ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

```

# quick sort
```c
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Arreglo original:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quickSort(arr, 0, n - 1);

    printf("Arreglo ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

```

# Intercalación de archivos

```c
#include <stdio.h>
#include <stdlib.h>

#define TAM_BLOQUE 5 // Tamaño del bloque para ordenar

void mergeFiles(FILE *f1, FILE *f2, FILE *output) {
    int num1, num2;
    int endOfFile1 = 0, endOfFile2 = 0;

    // Leer el primer número de cada archivo
    endOfFile1 = fscanf(f1, "%d", &num1);
    endOfFile2 = fscanf(f2, "%d", &num2);

    while (endOfFile1 != EOF && endOfFile2 != EOF) {
        // Comparar los números y escribir el menor en el archivo de salida
        if (num1 < num2) {
            fprintf(output, "%d ", num1);
            endOfFile1 = fscanf(f1, "%d", &num1);
        } else {
            fprintf(output, "%d ", num2);
            endOfFile2 = fscanf(f2, "%d", &num2);
        }
    }

    // Agregar los elementos restantes del archivo 1 (si hay)
    while (endOfFile1 != EOF) {
        fprintf(output, "%d ", num1);
        endOfFile1 = fscanf(f1, "%d", &num1);
    }

    // Agregar los elementos restantes del archivo 2 (si hay)
    while (endOfFile2 != EOF) {
        fprintf(output, "%d ", num2);
        endOfFile2 = fscanf(f2, "%d", &num2);
    }
}

void sortFile(FILE *input) {
    int numArray[TAM_BLOQUE];
    int i, j, temp, num;
    FILE *tempFile1, *tempFile2, *output;

    tempFile1 = fopen("tempFile1.txt", "w+");
    tempFile2 = fopen("tempFile2.txt", "w+");
    output = fopen("output.txt", "w+");

    do {
        // Leer un bloque de números del archivo original
        for (i = 0; i < TAM_BLOQUE; i++) {
            if (fscanf(input, "%d", &num) != EOF) {
                numArray[i] = num;
            } else {
                numArray[i] = -1; // Marcar el final del bloque
            }
        }

        // Ordenar el bloque en memoria RAM usando bubble sort
        for (i = 0; i < TAM_BLOQUE - 1; i++) {
            for (j = 0; j < TAM_BLOQUE - i - 1; j++) {
                if (numArray[j] > numArray[j + 1]) {
                    temp = numArray[j];
                    numArray[j] = numArray[j + 1];
                    numArray[j + 1] = temp;
                }
            }
        }

        // Escribir el bloque ordenado en un archivo temporal
        for (i = 0; i < TAM_BLOQUE; i++) {
            if (numArray[i] != -1) {
                fprintf(tempFile1, "%d ", numArray[i]);
            }
        }
    } while (numArray[TAM_BLOQUE - 1] != -1);

    fclose(input);
    fclose(tempFile1);
    fclose(tempFile2);

    // Realizar intercalación de los bloques ordenados
    int flag = 1;
    while (flag) {
        tempFile1 = fopen("tempFile1.txt", "r");
        tempFile2 = fopen("tempFile2.txt", "r");
        output = fopen("output.txt", "w");

        if (tempFile1 != NULL && tempFile2 != NULL) {
            mergeFiles(tempFile1, tempFile2, output);
            fclose(tempFile1);
            fclose(tempFile2);
            fclose(output);
        } else {
            flag = 0;
        }

        // Intercambiar los nombres de los archivos temporales
        FILE *temp = tempFile1;
        tempFile1 = tempFile2;
        tempFile2 = temp;
    }
}

int main() {
    FILE *input;

    input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }

    sortFile(input);

    printf("Ordenamiento por intercalación completado.\n");

    return 0;
}

```

# Mezcla directa
```c
#include <stdio.h>
#include <stdlib.h>

#define TAM_BLOQUE 1 // Tamaño del bloque para ordenar

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void sortFile(FILE *input) {
    int numArray[TAM_BLOQUE];
    int i, num;

    do {
        // Leer un bloque de números del archivo original
        for (i = 0; i < TAM_BLOQUE; i++) {
            if (fscanf(input, "%d", &num) != EOF) {
                numArray[i] = num;
            } else {
                numArray[i] = -1; // Marcar el final del bloque
            }
        }

        // Ordenar el bloque en memoria RAM usando merge sort
        mergeSort(numArray, 0, TAM_BLOQUE - 1);

        // Escribir el bloque ordenado en el archivo de salida
        for (i = 0; i < TAM_BLOQUE; i++) {
            if (numArray[i] != -1) {
                fprintf(input, "%d ", numArray[i]);
            }
        }
    } while (numArray[TAM_BLOQUE - 1] != -1);
}

int main() {
    FILE *input;
    input = fopen("input.txt", "r+");
    if (input == NULL) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }
    sortFile(input);
    printf("Mezcla directa completada.\n");
    return 0;
}

```

![[Pasted image 20230804083514.png]]
![[Pasted image 20230804083532.png]]
![[Pasted image 20230804083641.png]]
