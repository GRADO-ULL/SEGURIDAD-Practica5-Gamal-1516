
using namespace std;

typedef struct 
{
    int coordenada_x;
    int coordenada_y;
}Punto;


double exponenciacion_rapida(double base, double exponente, double modulo)
{
    double x = 1;
    double y = fmod(base,modulo);
    while(exponente > 0 && y > 1)
    {
      if(fmod(exponente,2) != 0)
      {
        //Impar
        x = fmod((x*y),modulo);
        exponente = exponente-1;
      }
      else
      {
        //Par
        y = fmod((y*y),modulo);
        exponente = exponente / 2;
      }
    }
    return x;
}


int algoritmo_euclides(int a, int b)
{
    int inverso = 0;
    bool inverso_control;
    vector<int> x;
    vector<int> z;
    int condicion = a; 
    int contador = 0;
    
    x.resize(x.size()+2);
    z.resize(z.size()+1);
    
    z[-1] = 0;
    z[0] = 1;
    
    x[0] = a;
    x[1] = b;
    
    while(condicion != 0)
    {
        //Divido x[contador] / x[contador+1]
            //Cociente
            if(x[contador] < x[contador+1])
            {
                int temp = x[contador];
                x[contador] = x[contador+1];
                x[contador+1] = temp;
            }
            int cociente = x[contador] / x[contador+1];
            //cout << "Divido " << x[contador] << "/" << x[contador+1] << "=" << cociente << endl;
            cociente = -cociente;
            //cout << "Cambio signo de cociente:" << cociente << endl;
            //Resto división
            condicion = x[contador] % x[contador+1];
        
        //Inserto en z[contador] el resultado anterior
        z.resize(z.size()+1);
        z[contador+1] = (cociente*z[contador]) + z[contador-1];

        //Inserto en x[contador+2] resto de la primera división
        x.resize(x.size()+1);
        x[contador+2] = condicion;

        //Actualizo contador
        contador++;
    }
    //cout << "Contador:" << contador << endl;
    //cout << "Imprimiendo x[contador]=>" << x[contador] << endl;
    
    if(condicion == 0 && x[contador] == 1)
    {
        //cout << "Inverso: " << z[contador-1] << endl;
        inverso = z[contador-1];
    }
    
    if(inverso < 0)
    {
        //cout << "Inverso negativo" << endl;
        while(inverso < 0)
        {
            inverso = inverso+b;
        }
        //cout << "Inverso actualizado:" << inverso << endl;
    }
    
    return inverso;
}

//Métodos de impresión
void imprimir_punto(Punto P)
{
    cout << "(" << P.coordenada_x << "," << P.coordenada_y << ")";    
}

void imprimir(vector<Punto> puntos)
{
    cout << "Puntos de la curva:" << endl;
    for(int i=0;i<puntos.size();i++)
    {
        cout << "(" << puntos[i].coordenada_x << "," << puntos[i].coordenada_y << ")";
        if(i < puntos.size()-1)
            cout << ",";
    }
    cout << endl;
}

//Sobrecarga de operadores == y + para los puntos
bool operator==(Punto punto0, Punto punto1)
{
    bool iguales = false;
    
    if(punto0.coordenada_x == punto1.coordenada_x)
    {
        if(punto0.coordenada_y == punto1.coordenada_y)
        {
            // cout << "punto0.coordenada_x:" << punto0.coordenada_x << endl;
            // cout << "punto0.coordenada_y:" << punto0.coordenada_y << endl;
            // cout << "punto1.coordenada_x:" << punto1.coordenada_x << endl;
            // cout << "punto1.coordenada_y:" << punto1.coordenada_y << endl;

            iguales = true;   
        }
    }
    
    return iguales;
}



void hallar_modulo(int &num, int modulo)
{
    while(num < 0)
        num = num + modulo;
    num = num % modulo;
}

Punto operator+(Punto punto0, Punto punto1)
{
    Punto auxiliar;
    
    int lambda = 0;
    int auxiliar_num = 0;
    int auxiliar_denom = 0;
    
    if(punto0 == punto1)
    {
        
        auxiliar_num = 3*pow(punto0.coordenada_x,2)+a;

        hallar_modulo(auxiliar_num, p);
        
        auxiliar_denom = 2 * punto0.coordenada_y;

        hallar_modulo(auxiliar_denom, p);

        auxiliar_denom = algoritmo_euclides(auxiliar_denom,p);
    }
    else
    {

        auxiliar_num = punto1.coordenada_y - punto0.coordenada_y;
        
        hallar_modulo(auxiliar_num, p);

        auxiliar_denom = punto1.coordenada_x - punto0.coordenada_x;
        
        hallar_modulo(auxiliar_denom,p);
        
        auxiliar_denom = algoritmo_euclides(auxiliar_denom, p);
    }
    
    lambda = auxiliar_num * auxiliar_denom;

    hallar_modulo(lambda,p);
    
    auxiliar.coordenada_x = pow(lambda,2) - punto0.coordenada_x -punto1.coordenada_x;
    
    hallar_modulo(auxiliar.coordenada_x, p);

    auxiliar.coordenada_y = lambda*(punto0.coordenada_x-auxiliar.coordenada_x) - punto0.coordenada_y;
    
    hallar_modulo(auxiliar.coordenada_y,p);

    return auxiliar;
}


void generar_puntos_curva(vector<Punto> &puntos, int a, int b, int p)
{
    //y^2 = x^3+ax+b
    vector<int> resultados_x;
    vector<int> resultados_y;

    int i=0;
    int j=0;
    int contador = 0;
   
    while(i<p)
    {
        resultados_x.resize(resultados_x.size()+1);
        resultados_y.resize(resultados_y.size()+1);
        
        
        int auxiliar_x = pow(i,3)+ a*i + b;
        int auxiliar_y = pow(i,2);

        auxiliar_x = auxiliar_x % p;
        auxiliar_y = auxiliar_y % p;
        
        resultados_x[i] = auxiliar_x;
        resultados_y[i] = auxiliar_y;
        i++;
    }
    
    for(i=0;i<p;i++)
    {
        while(j<p)
        {
            if(resultados_x[i] == resultados_y[j])
            {
                Punto aux;
                aux.coordenada_x = i;
                aux.coordenada_y = j;
                
                puntos.resize(puntos.size()+1);
                puntos[contador] = aux;
                
                contador++;
            }
            j++;
        }
        j = 0;
    }
    imprimir(puntos);        
}



Punto calcularp(vector<int> potencias, Punto P)
{
    int i = potencias.size()-2;

    stack<Punto> suma_puntos;

    Punto primer_punto = P+P;

    suma_puntos.push(P+P);

    for(i;i>=0;i--)
    {
        // cout << "accedo" << endl;
        Punto auxiliar;
        Punto resultado;
        auxiliar = suma_puntos.top();
        suma_puntos.pop();
        resultado = auxiliar + auxiliar;
        suma_puntos.push(resultado);
    }
    
    Punto final = suma_puntos.top();
    suma_puntos.pop();
    return final;
}


void imprimir_pila(stack<Punto> p)
{
    //cout << "Pila:";
    while(!p.empty())
    {
        imprimir_punto(p.top());
        p.pop();
        cout << ",";
    }
    //cout << endl;
}



Punto multiplicar_xfactor(Punto P, int factor)
{
    
    int cociente = factor;
    stack<Punto> suma_puntos;
    
    int iteracion = 0;
    //Factorizando
    while(cociente > 0)
    {
        vector<int> potencias_2;
        Punto resultado;
        
        int resto = cociente % 2;

        if(resto == 1)
        {
            if(iteracion > 0)
            {
                int contador_auxiliar = 0;
                while(contador_auxiliar < iteracion)
                {
                    potencias_2.resize(potencias_2.size()+1);
                    potencias_2[contador_auxiliar] = 2;
                    contador_auxiliar++;
                }
                resultado = calcularp(potencias_2,P);
            }
            else
            {
                resultado = P;
            }

            suma_puntos.push(resultado);
        }
        
        
        cociente = cociente / 2;
        iteracion++;

    }
    
    //sumar_puntos
    while(suma_puntos.size() > 1)
    {
        Punto sumando1 = suma_puntos.top();
        suma_puntos.pop();

        Punto sumando2 = suma_puntos.top();

        suma_puntos.pop();
        
        Punto aux = sumando1 + sumando2;

        suma_puntos.push(aux);
    }
    
    Punto final = suma_puntos.top();
    suma_puntos.pop();
    return final;
}

Punto hallar_clave_publica(Punto P, int dB)
{
    return multiplicar_xfactor(P,dB);    
}
