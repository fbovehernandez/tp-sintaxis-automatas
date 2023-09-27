#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodo {
   int info;
   struct nodo* siguiente;
} nodo;

typedef nodo* ptrNodo;
typedef nodo* Pila;

/*
int main() {
    int opcion;
    do {
        printf("------------------------MENU------------------------\n");
        printf("--------Selecciona una opcion(numero)--------\n");
        printf("1- Punto 1\n");
        printf("2- Punto 2\n");
        printf("3- Punto 3\n");
        printf("0- Salir\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 0:
                printf("--------Hasta Luego--------\n");
                printf("--------Fin del Programa--------\n");
                break;
            case 1:
                Punto1();
                break;
            case 2:
                Punto2();
                break;
            case 3:
                Punto3();
                break;
            default:
                printf("--------opcion invalida, por favor ingrese una opcion valida!--------\n");
                break;
        }
    } while (opcion != 0);
    return 0;
}
*/

int esPalabraDecimal(char *);
int esPalabraOctal(char *);
int esPalabraHexa(char *);
int columna(int);
int columna2(int);
int columna3(int);
int columna4(int);
int estaEntreCaracteres(int, char, char);
void pushConvertidos(Pila *, char *);
void push(Pila *, int);
int pop(Pila *);
int esPalabraValida(char *);
int realizarOperacion(Pila *, Pila *);
int esOperadorPrioritario(int);
int operar(int, int, int);

void push(Pila *pila, int info) {
    ptrNodo nuevo;
    nuevo =(ptrNodo)malloc(sizeof(nodo));
    nuevo->info = info;
    nuevo->siguiente = (*pila),
    *pila = nuevo;
}

int pop(Pila *pila) {
    int x = (*pila) -> info; // Rompe aca. 
    ptrNodo aux =(*pila);
    *pila = aux->siguiente;
    free(aux);
    return x;
}

int main () {
    int contadorDecimal = 0;
    int contadorOctal = 0;
    int contadorHexa = 0;
    char caracterSeparador[] = "$"; 

    Pila pila = NULL;
    Pila pila2 = NULL;

    char cadenaNumeros[50] = "203$062$0x8Y$071"; // 203$0x06$0982
    char palabra[10] = "10+5*3";
    
    if (esPalabraValida(palabra)) {
        pushConvertidos(&pila, palabra);
        realizarOperacion(&pila, &pila2);
        // printf("Resultado %d.\n", realizarOperacion(&pila, &pila2));
    } else {
        printf("Ingrese una palabra valida");
    }
   
    // while(pila != NULL) {
       //  printf("El valor es %d.\n" , pop(&pila));
   //  }

    // printf("Ingrese cadena separada por $");
    // scanf("%s", cadenaNumeros);
/*
    char *palabra = strtok(cadenaNumeros, caracterSeparador); // "$"

while(palabra != NULL) {
    printf("%s.\n", palabra);

    // if (! Verifica(palabra)) {
     //  printf("Tiene caracteres no validos \n");
    if (esPalabraDecimal(palabra)) {
        printf("Es palabra decimal \n");
        contadorDecimal ++;
        }  
        else if (esPalabraOctal(palabra)) {
                 printf("Es palabra Octal \n");
                 contadorOctal ++;
            } else if (esPalabraHexa(palabra)) {
                printf("Es palabra Hexa \n");
                contadorHexa ++;
        
            }   else {
                printf("No pertenece al lenguaje \n"); 
            } 
            
        palabra = strtok(NULL, caracterSeparador);
    }

    printf("cantidad Decimales es %d.\n" , contadorDecimal);
    */
}

int esPalabraDecimal(char *palabra) {
                // 0 1-9 + - R
    int tt[4][5]= {{3,2,1,1,3},  // 0-
                   {3,2,3,3,3},  // 1
                   {2,2,3,3,3},  // 2+
                   {3,3,3,3,3}   // 3
                  };

    int estado = 0;
    int i = 0;
    int c = palabra[i];

    while(c != '\0' && estado != 3) {
       estado = tt[estado][columna(c)]; 
       c= palabra[++i]; // itero la cadena
    }

    if (estado == 2) {
        return 1;
    } return 0;
}

int columna(int c) {
    if (estaEntreCaracteres(c,'1','9')) { // optamos por usar un estado mas y no verificar ya que la verificacion despues nos daba problemas con la forma en la que haciamos esta columna, pero de todas formas esta hecha porque la usamos para el punto 3
        return 1;
    } else {
        switch (c) {
            case '0':
                return 0;
            case '+':
                return 2;
            case '-':
                return 3;
            default :
                return 4; // otro, rechazo
        }
    } 
}

int esPalabraOctal(char * palabra) {
                // 0 1-7 
    int tt[4][3]= {{1,3,3},  // 0-
                   {2,2,3},  // 1
                   {2,2,3},  // 2+
                   {3,3,3}   // 3
                  };

    int estado = 0;
    int i = 0;
    int c = palabra[i];

    while(c != '\0' && estado != 3) {
       estado = tt[estado][columna2(c)]; 
       c= palabra[++i]; // itero la cadena
    }

    if (estado == 2) {
        return 1;
    } return 0;
}

int columna2(int c) {
    if (estaEntreCaracteres(c,'1','7')) { 
        return 1;
    } else {
        switch (c) {
            case '0':
                return 0;
            default :
                return 2;
        }
    }  
}

int esPalabraHexa(char *palabra) {
                // 0 x X Digit OTRO
    int tt[5][5]= {{1,4,4,4,4},  // 0-
                   {4,2,2,4,4},  // 1
                   {3,4,4,3,4},  // 2
                   {3,4,4,3,4},  // 3+
                   {4,4,4,4,4}   // 4
                  };

    int estado = 0;
    int i = 0;
    int c = palabra[i];

    while(c != '\0' && estado != 4) {
       estado = tt[estado][columna3(c)]; 
       c= palabra[++i]; // itero la cadena
    }

    if (estado == 3) {
        return 1;
    } return 0;

}

int columna3(int c) {
    if (estaEntreCaracteres(c, 'a', 'f')  || estaEntreCaracteres(c,'A','F') || estaEntreCaracteres(c,'1','9')) {
        return 3; 
    } else {
        switch (c) {
            case '0':
                return 0;
            case 'x':
                return 1;
            case 'X':
                return 2; 
            default : 
                return 4;
        }
    } 
}

int estaEntreCaracteres(int caracter, char indice_inicial, char indice_Superior) {
    if (! (caracter >= indice_inicial && caracter <= indice_Superior)) return 0; 
    return 1;
}

//// Punto 2

int Valor (int c) {    
    return (c - '0'); 
} /* fin Valor */ 

int esOperador(char operador) {
    if (operador == '+' || operador == '-' || operador == '*' || operador == '/') return 1;
    return 0;
}

int esPalabraValida(char *palabra) {
                //  + - / * 0 1-9 
    int tt[4][6]= {{3,3,3,3,2,1},  // 0-
                   {0,0,0,0,1,1},  // 1+
                   {3,3,3,3,3,3},  // 2+
                   {3,3,3,3,3,3}   // 3
                  };

    int estado = 0;
    int i = 0;
    int c = palabra[i];

    while(c != '\0' && estado != 3) {
       estado = tt[estado][columna4(c)]; 
       c= palabra[++i]; // itero la cadena
    }

    if (estado == 2 || estado == 1) {
        return 1;
    } return 0;
}

// 
int columna4(int c) {
    if (estaEntreCaracteres(c,'1','9')) { // optamos por usar un estado mas y no verificar ya que la verificacion despues nos daba problemas con la forma en la que haciamos esta columna, pero de todas formas esta hecha porque la usamos para el punto 3
        return 5;
    } else {
        switch (c) {
            case '0':
                return 4;
            case '+':
                return 0;
            case '-':
                return 1;
            case '*':
                return 3;
            case '/':
                return 2;
        }
    } 
}
//

// 1+222*8/6 --- 
void pushConvertidos(Pila *pila, char * palabra) {
    int a = 0;
    char operador;
    for(int i=0; palabra[i] != '\0'; i++) {
        if (isdigit (palabra[i]) ) {
           a = 10 * a + Valor(palabra[i]);
        } else {
           push(pila,a);
           a = 0;
           operador = palabra[i];
           push(pila,operador); // se puede cargar palabra[i] directo, pero para ser mas expresivo
        }
    }
    push(pila,a);
} 

int realizarOperacion(Pila *pila, Pila *pila2) {
    int num1 = pop(pila);
    int operador = pop(pila);
    int resultado = 0;
    int num2;

    while(pila != NULL) { // 10+15
        printf ("hola");
        if (!esOperadorPrioritario(operador)) {  // * y / son prioritarios
            push(pila2, num1);
            push(pila2, operador);
        } else {
            num2 = pop(pila);
            resultado = operar(num2, num1, operador);
            push(pila, resultado);
        }
        
        num1 = pop(pila);
        if(pila != NULL) {
            operador = pop(pila);
        } else {
            push(pila2, num1);
        }
    }

    while (pila2 != NULL) { // NO ENTRA
        printf ("hola");
        num1 = pop(pila2);
        if(pila2 != NULL) {
            operador = pop(pila2);   
            num2 = pop(pila2);
            resultado = operar(num1,num2,operador); 
            push(pila2,resultado);
        } else {
            return num1;
        }
    }
}
 
int operar(int num2, int num1, int op) {
    int resultado = 0;

    if (op == 42) { // * es el 42 en ASCII
        resultado = num1 * num2;
    } else if(op == 47) { // / es el 47 en ASCII
        resultado = num1 / num2;
    } else if(op == 43) { // + es el 43 en ASCII
        resultado = num1 + num2;
    } else if(op == 45) { // - es el 45 en ASCII
        resultado = num1 - num2;
    }

    return resultado;
}

int esOperadorPrioritario(int operador){
    if (operador == 47 || operador == 42) return 1;
    return 0;
}


