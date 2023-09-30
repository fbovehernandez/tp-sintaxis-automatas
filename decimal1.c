// Bibliotecas utilizadas
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Definicion de estructuras (Pilas)
typedef struct nodo {
   int info;
   struct nodo* siguiente;
} nodo;

typedef nodo* ptrNodo;
typedef nodo* Pila;

// Definicion de funciones utilizadas
int esPalabraDecimal(char *);
int esPalabraOctal(char *);
int esPalabraHexa(char *);
int columnaDecimal(int);
int columna2(int);
int columna3(int);
int columna4(int);
int estaEntreCaracteres(int, char, char);
void pushConvertidos(Pila *, char *);
void push(Pila *, int);
int pop(Pila *);
int esPalabraValida(char *);
float realizarOperacion(Pila *, Pila *, Pila *);
int esOperadorPrioritario(int);
float operar(float,float, int);
void desapilarYApilarEnAux(Pila*, Pila*);
void Punto1();
void Punto2();
void Punto3(Pila*,Pila*);
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

int main() {

    Pila pila = NULL;
    Pila pila2 = NULL;

    int opcion;
    do {
        printf("------------------------MENU------------------------\n");
        printf("--------Selecciona una opcion(numero)--------\n");
        printf("1- Desarrollo del punto 1 \n");
        printf("2- Desarrollo del punto 2\n");
        printf("3- Desarrollo del punto 3\n");
        printf("0- Salir\n");
        printf("Ingrese un valor correspondiente\n");
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
                Punto3(&pila,&pila2);
                break;
            default:
                printf("--------opcion invalida, por favor ingrese una opcion valida!--------\n");
                break;
        }
    } while (opcion != 0);
    return 0;
}

// Explicacion del uso de strtok : 

// Lo primero es entender que necesito definir 2 vectores de caracteres, uno para la palabra y otro para el caracter separador, ademas, es necesario un puntero auxiliar donde pueda guardar las diferentes partes de la palabra. Cuando encuentre el primer "caracter espurio/separador" va a quedarse con lo que habia detras de este (en el primer caso, se quedara con la palabra desde su comienzo hasta el caracter). Por ejemplo, si yo tengo la cadena "Quiero$separar$esto" comienza desde el primer elemento y guarda hasta el caracter. Como hacemos para seguir guardando el resto de los caracteres? Bueno, llamamos a la misma funcion pero en vez de pasarle el vector de caracteres como la primera vez (junto con el char vector del separador), voy a pasarle NULL, y asi la funcion sabe que yo quiero que busque desde el ultimo caracter que freno la palabra. Podriamos asignarlo a diferentes char *vectorAux pero en este caso nos convenia pisarlo y volver a ejecutar el while con la proxima palabra. Cada vez que ejecutamos el while preguntamos si la palabra es distinta del NULL, por ende va  a saber cuando detenerse.

// https://www.youtube.com/watch?v=nrO_pXGZc3Y 
// https://parzibyte.me/blog/2018/11/13separar-cadena-delimitadores-c-strtok/
// En este video se muestra de manera muy buena como funciona esta funcion. Podriamos haber implementado tambien una pila, ir separando las palabras y despues sacar eso y usarlo, pero esta funcion nos facilita mucho mas la separacion de las mismas. 


// DESARROLLO DEL PRIMER PUNTO 
void Punto1() {
    // Inicializacion
    char *cadenaNumeros;
    char caracterSeparador[] = "$";
    int contadorDecimal = 0; 
    int contadorOctal = 0; 
    int contadorHexa = 0; 
    
    printf("Ingrese cadena separada por $\n");
    scanf("%s", cadenaNumeros);
    char *palabra = strtok(cadenaNumeros, caracterSeparador); // "$"

while(palabra != NULL) {
    printf("%s.\n", palabra); // chequeo para saber que palabra imprime. 
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
    printf("cantidad de caracteres decimales es %d.\n" , contadorDecimal);
    printf("cantidad de caracteres octales %d.\n" , contadorOctal);
    printf("cantidad de caracteres hexadecimales es %d.\n" , contadorHexa);
}

// DESARROLLO DEL SEGUNDO PUNTO
void Punto2() {
    char caracter;
    printf("Ingrese un caracter numerico (1-9)\n");
    scanf(" %c", &caracter);
    printf("El valor numerico del caracter es: %d.\n ", Valor(caracter));
}

// DESARROLLO DEL TERCER PUNTO
void Punto3(Pila* pila, Pila* pila2) {
    Pila pilaAux = NULL;
    Pila pilaAux2 = NULL;

    char palabra[50]; // Inicializamos un vector con un tope, porque no encontramos la forma exacta de poder hacerlo sin tener un tamaño maximo. 
    printf("Ingrese una cadena de digitos y operaciones\n");
    scanf("%s", palabra);

    if (esPalabraValida(palabra)) { // chequea que la palabra este dentro los parametros establecidos.
        pushConvertidos(pila, palabra); // primeros pusheamos todos los caracteres y los pusheamos en la lista transformandolos a numeros. 
        desapilarYApilarEnAux(pila, &pilaAux); // para que resuelva a izq, y respetar la precedencia matematica, sino teniamos problemas con la division. 
        printf("Resultado %lf.\n", realizarOperacion(pila2, &pilaAux, &pilaAux2));
    } else {
        printf("Ingrese una palabra valida");
    }
}

int esPalabraDecimal(char *palabra) {
                // 0 1-9 - + OTRO
    int tt[5][5]= {{1,2,3,3,4},  // 0-
                   {4,4,4,4,4},  // 1+
                   {2,2,4,4,4},  // 2+
                   {4,2,4,4,4},  // 3
                   {4,4,4,4,4}   // 4
                  };

    int estado = 0;
    int i = 0;
    int c = palabra[i];

    while(c != '\0' && estado != 4) {
       estado = tt[estado][columnaDecimal(c)]; 
       c= palabra[++i]; // itero la cadena
    }

    if (estado == 2 || estado == 1) {
        return 1;
    } return 0;
}

int columnaDecimal(int c) {
    if (estaEntreCaracteres(c,'1','9')) { 
        return 1;
    } else {
        switch (c) {
            case '0':
                return 0;
            case '+':
                return 3;
            case '-':
                return 2;
            default :
                return 4; // otro, rechazo
        }
    }
}

int esPalabraOctal(char * palabra) {
                // 0 1-7 OTRO
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
    if (!(caracter >= indice_inicial && caracter <= indice_Superior)) return 0; 
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

// Esta funcion esta hecha para respetar la resolucion de las operaciones matematicas de izquierda a derecha
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
       c= palabra[++i]; 
    }

    if (estado == 2 || estado == 1) { // ambos son estados de aceptacion
        return 1;
    } return 0;
}

int columna4(int c) {
    if (estaEntreCaracteres(c,'1','9')) { 
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

// Aclaracion: la idea de hacerlo float es para no tener problemas en casos de division.
// La idea de esta funcion es simplemente pushear los valores de la cadena transformalos en sus respectivos numeros, los operadores los transforma en un entero tambien, su codigo ASCII (dato de color).

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

float realizarOperacion(Pila *pila2, Pila *pilaAux, Pila *pilaAux2) {
    float num1;
    int operador;
    float resultado = 0;
    float num2;

    num1 = pop(pilaAux);
    while(*pilaAux != NULL) {
        operador = pop(pilaAux); // Si es prioritario se opera y se almacena en la pila auxiliar, sino, se almacena sin operarse en la otra pila, haciendo que en la otra queden el +/- con la misma prioridad. 
        if (!esOperadorPrioritario(operador)) {  // * y / son prioritarios
            push(pila2, num1); 
            push(pila2, operador);
        } else { 
            num2 = pop(pilaAux);
            resultado = operar(num1, num2, operador);
            push(pilaAux, resultado);
        }
        num1 = pop(pilaAux);
    }

    push(pila2,num1);

    desapilarYApilarEnAux(pila2, pilaAux2);

    num1 = pop(pilaAux2);
    while (*pilaAux2 != NULL){
        operador = pop(pilaAux2);
        num2 = pop(pilaAux2);
        resultado = operar(num1,num2,operador); 
        push(pilaAux2,resultado);
        num1 = pop(pilaAux2);
    }
    return num1;
}
 
float operar(float num1, float num2, int op) {
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