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
float realizarOperacion(Pila *, Pila *);
int esOperadorPrioritario(int);
float operar(float,float, int);
void desapilarYApilarEnAux(Pila*, Pila*);
void Punto1();
void Punto2();
void Punto3(Pila*,Pila*,Pila*);
int Valor(int);


void push(Pila *pila, int info) {
    ptrNodo nuevo;
    nuevo =(ptrNodo)malloc(sizeof(nodo));
    nuevo->info = info;
    nuevo->siguiente = (*pila),
    *pila = nuevo;
}

int pop(Pila* pila) {
    int x = (*pila) -> info;
    ptrNodo aux = (*pila);
    *pila = aux->siguiente;
    free(aux);
    return x;
}

// Main
int main() {

    Pila pila = NULL;
    Pila pila2 = NULL;
    Pila pilaAux = NULL;

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
                Punto3(&pila,&pilaAux,&pila2);
                break;
            default:
                printf("--------opcion invalida, por favor ingrese una opcion valida!--------\n");
                break;
        }
    } while (opcion != 0);
    return 0;
}

// DESARROLLO DEL PRIMER PUNTO
void Punto1() {
    char *cadenaNumeros;
    char caracterSeparador[] = "$";
    int contadorDecimal = 0; 
    int contadorOctal = 0; 
    int contadorHexa = 0; 
    
    printf("Ingrese cadena separada por $\n");
    scanf("%s", cadenaNumeros);
    char *palabra = strtok(cadenaNumeros, caracterSeparador); // "$"

while(palabra != NULL) {
    printf("%s.\n", palabra);

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
}

// DESARROLLO DEL SEGUNDO PUNTO
void Punto2() {
    char caracter;
    printf("Ingrese un caracter numerico\n");
    scanf(" %c", &caracter);
    printf("El valor numerico del caracter es: %d.\n ", Valor(caracter));
}

// DESARROLLO DEL TERCER PUNTO
void Punto3(Pila* pila, Pila* pilaAux, Pila* pila2) {
    char* palabra;
    
    printf("Ingrese una cadena de digitos y operaciones\n");
    scanf("%s", palabra);
    if (esPalabraValida(palabra)) {
        pushConvertidos(&pila, palabra);
        desapilarYApilarEnAux(&pila, &pilaAux); // para que resuelva a izq, y respetar la precedencia matematica. 
        printf("Resultado %lf.\n", realizarOperacion(&pilaAux, &pila2));
    } else {
        printf("Ingrese una palabra valida");
    }
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
}

//// Punto 3

int esOperador(char operador) {
    if (operador == '+' || operador == '-' || operador == '*' || operador == '/') return 1;
    return 0;
}

void desapilarYApilarEnAux(Pila* pila, Pila* pilaAux) {
    while(*pila != NULL){
        push(pilaAux , pop(pila));
    }
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
    float a = 0;
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

float realizarOperacion(Pila *pilaAux, Pila *pila2) {
    float num1;
    int operador;
    float resultado = 0;
    float num2;

    num1 = pop(pilaAux);
    while(*pilaAux != NULL) {
        printf("hola");
        operador = pop(pilaAux);
        if (!esOperadorPrioritario(operador)) {  // * y / son prioritarios
            push(pila2, num1);
            push(pila2, operador);
        } else {
            num2 = pop(pilaAux);
            resultado = operar(num2, num1, operador);
            push(pilaAux, resultado);
        }
        
        num1 = pop(pilaAux);
    }

    push(pila2,num1);

    num1 = pop(pila2);
    while (*pila2 != NULL){
        operador = pop(pila2);
        num2 = pop(pila2);
        resultado = operar(num1,num2,operador); 
        push(pila2,resultado);
        // ..

        num1 = pop(pila2);
    }

    return num1;
}
 
float operar(float num2, float num1, int op) {
    float resultado = 0;

    if (op == 42){ // * es el 42 en ASCII
        resultado = num1 * num2;
    }else if(op == 47) { // / es el 47 en ASCII
        resultado = num1 / num2;
    }else if(op == 43) { // + es el 43 en ASCII
        resultado = num1 + num2;
    }else if(op == 45) { // - es el 45 en ASCII
        resultado = num1 - num2;
    }

    return resultado;
}

int esOperadorPrioritario(int operador){
    if (operador == 47 || operador == 42) return 1;
    return 0;
}