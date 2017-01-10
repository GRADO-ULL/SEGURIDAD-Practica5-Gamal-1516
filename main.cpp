#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stack>          // std::stack
#include <vector>

int a = 0;
int b = 0;
int p = 0;

#include "funciones.cpp"

using namespace std;

//Variables globales

void mostrar_cifrado(Punto mensaje_original, int aA, Punto clave_publica, Punto original)
{
    Punto a;
    Punto b;
    
    a = mensaje_original + multiplicar_xfactor(clave_publica,aA);
    b = multiplicar_xfactor(original, aA);
    
    cout << "Mensaje cifrado: {";
    imprimir_punto(a);
    cout << " , ";
    imprimir_punto(b);
    cout << "}" << endl;
}

int main()
{
    //Constante p. Zp
    //Constante dB. Clave privada para hallar clave publica
    int dB = 0;
    int aA = 0;
    //Punto inicial P
    Punto P;
    Punto mensaje_original;
    //Vector de puntos de la curva eliptica
    vector<Punto> puntos_curva;
    
    //Constante para la curva eliptica
    
    cout << "Informacion privada:" << endl;
    cout << "Curva eliptica:" << endl;
    cout << "Constante a:";
    cin >> a;
    cout << "Constante b:";
    cin >> b;
    cout << "Numero primo:";
    cin >> p;
    cout << "Dato dB para hallar la clave publica:";
    cin >> dB;
    cout << endl;
    
    cout << "Introduzca datos punto P:" << endl;
    cout << "Coordenada x:";
    cin >> P.coordenada_x;
    cout << "Coordenada y:";
    cin >> P.coordenada_y;
    cout << endl;
    
    cout << "Introduzca datos punto M:" << endl;
    cout << "Coordenada x:";
    cin >> mensaje_original.coordenada_x;
    cout << "Coordenada y:";
    cin >> mensaje_original.coordenada_y;
    cout << "Constante aleatoria para el cifrado del mensaje original:";
    cin >> aA;
    cout << endl;
    
    cout << "-------------------------------------------"<<endl;
    
    cout << "Informacion introducida:" << endl;
    cout << "P:\t" << p << endl;
    cout << "Constante a:\t" << a << endl;
    cout << "Constante b:\t" << b << endl;
    cout << "Punto inicial P: ";
    imprimir_punto(P);
    cout << endl;
    cout << "Constante dB: " << dB << endl;
    cout << "Mensaje original:";
    imprimir_punto(mensaje_original);
    cout << endl;
    cout << "Constante aA: " << aA << endl;
    
    cout << "-------------------------------------------" << endl;
    
    generar_puntos_curva(puntos_curva,a,b,p);

    cout << "-------------------------------------------" << endl;
    Punto clave_publica = hallar_clave_publica(P, dB);
    cout << "Generando clave publica => dB * P => " << dB << " * " << "(" << P.coordenada_x << "," << P.coordenada_y << ") = ";
    imprimir_punto(clave_publica);
    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Generando cifrado:" << endl;
    mostrar_cifrado(mensaje_original,aA, clave_publica, P);
    cout << endl;
    
    return 0;
}