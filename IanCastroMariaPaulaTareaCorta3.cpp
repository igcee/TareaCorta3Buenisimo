#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <cstdio>

class Nodo
{
public:
    int valor;
    //int posicion;
    Nodo* Hizq;
    Nodo* Hder;

    Nodo(int valor);
};

typedef Nodo* pnodo;

Nodo::Nodo(int val)
{
    valor = val;
    //posicion = pos;
    Hizq = NULL;
    Hder = NULL;
}

class ABBusqueda {
private:
    pnodo raiz;

    // Metodos auxiliares privados
    pnodo InsertaBinario(pnodo raiz, int valor);
    bool Buscarvalor(pnodo raiz, int valor);
    //void InordenR(pnodo raiz);
    //void PreordenR(pnodo raiz);
    //void PostordenR(pnodo raiz);
    void destruirArbol(pnodo raiz);
    pnodo EliminarNodo(pnodo raiz, int valor);
    pnodo encontrarMinimo(pnodo raiz);

    //void preordenI(pnodo raiz);
    //void inordenI(pnodo raiz);
    //void postordenI(pnodo raiz);

public:
    ABBusqueda();
    ~ABBusqueda();

    void InsertaNodo(int valor);
    bool Buscarvalor(int valor);

    //void InordenR();
    //void PreordenR();
   // void PostordenR();

    //void recorridoPorNiveles();

    //void preordenI();
    //void inordenI();
    //void postordenI();

    void EliminarNodo(int valor);
};

ABBusqueda::ABBusqueda() 
{
    raiz = nullptr;
}
ABBusqueda::~ABBusqueda() 
{
    destruirArbol(raiz);
}


void ABBusqueda::InsertaNodo(int valor) 
{
    if(raiz==NULL){
        raiz = new Nodo(valor);
    }else{
        raiz = InsertaBinario(raiz, valor);
    }
}

bool ABBusqueda::Buscarvalor(int valor) 
{
    return Buscarvalor(raiz, valor);
}


void ABBusqueda::EliminarNodo(int valor) 
{
    raiz = EliminarNodo(raiz, valor);
}

pnodo ABBusqueda::InsertaBinario(pnodo raiz, int valor) 
{
    if (raiz == nullptr) 
	{
        return new Nodo(valor);
    }

    if (valor < raiz->valor) 
	{
        raiz->Hizq = InsertaBinario(raiz->Hizq, valor);
    } 
	else 
	   if (valor > raiz->valor) 
	   {
        raiz->Hder = InsertaBinario(raiz->Hder, valor);
       }

    return raiz;
}

bool ABBusqueda::Buscarvalor(pnodo raiz, int valor) 
{
    if (raiz == nullptr) return false;
    if (valor == raiz->valor) return true;
    if (valor < raiz->valor)
        return Buscarvalor(raiz->Hizq, valor);
    else
        return Buscarvalor(raiz->Hder, valor);
}

void ABBusqueda::destruirArbol(pnodo raiz) 
{
    if (raiz == nullptr) return;
    destruirArbol(raiz->Hizq);
    destruirArbol(raiz->Hder);
    delete raiz;
}
pnodo ABBusqueda::encontrarMinimo(pnodo raiz) 
{
    while (raiz->Hizq != nullptr) 
	{
        raiz = raiz->Hizq;
    }
    return raiz;
}
pnodo ABBusqueda::EliminarNodo(pnodo raiz, int valor) 
{
    if (raiz == nullptr) {
        cout << "Valor no encontrado: " << valor << endl;
        return nullptr;
    }

    if (valor < raiz->valor) 
	{
        raiz->Hizq = EliminarNodo(raiz->Hizq, valor);
    } 
	else 
	   if (valor > raiz->valor) 
	   {
        raiz->Hder = EliminarNodo(raiz->Hder, valor);
       } 
	   else 
	   {
        // Nodo encontrado
        if (raiz->Hizq == nullptr && raiz->Hder == nullptr) 
		{
            delete raiz;
            return nullptr;
        } 
		else 
		   if (raiz->Hizq == nullptr) 
		   {
             pnodo temp = raiz->Hder;
             delete raiz;
             return temp;
           } 
		   else 
		      if (raiz->Hder == nullptr) 
			  {
                pnodo temp = raiz->Hizq;
                delete raiz;
                return temp;
              } 
			  else 
			  {
                pnodo sucesor = encontrarMinimo(raiz->Hder);
                raiz->valor = sucesor->valor;
                raiz->Hder = EliminarNodo(raiz->Hder, sucesor->valor);
              }
        }

    return raiz;
}

string LimpiaLinea(string lineasucia){
	// esta funcion es para limpiar las lineas de Clientes.txt, y devuelve string de linea ya limpia
	// por ejemplo, recibe    "01;Francisco            clientes sin repetidos "
	// y devuelve             "01;Francisco"
	string linealimpia = "";
	bool banderafin = false;
	int i = 0;
	int largo = lineasucia.size();

	while (banderafin == false and i<largo){ // si no se pone la condicion de largo se jode cuando no encuentra fin
		if (lineasucia[i] == ' ' or lineasucia[i] == '\t'){ // si espacio, tab (\t), para
			banderafin = true;
		}
		else{
			linealimpia = linealimpia + lineasucia[i];
			i++;
		}
	}
	return linealimpia;	
}

int SacaCedula(string linealimpia){
	// recibe la linea ya limpia, y saca la cedula
	// por ejemplo, recibe "01;Francisco"
	// y devuelve 01, como int no como string
	int i = 0;
	string cedu = "";
	while (linealimpia[i] != ';'){
		cedu = cedu + linealimpia[i];
		i++;
	}
	int cedubuena = stoi(cedu);
	return cedubuena;
	//return cedu; // lo cambie para q lo sacara como string, pq salia como 1, en lugar de 01. Igual no creo q de problemas (si es q siquiera se ocupaba q saliera como int en primer lugar)
}


void LeerArchivoClientes(const char* nombreArchivo, ABBusqueda& arbol){
	
	ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }
    
    string filaencabezado;
    string lineasucia, linealimpia;
    int cedula;
    int pos = 0;
    
    getline(archivo, filaencabezado); // ignorar encabezado
    ofstream temp("ClientesTemporal.txt");
    ABBusqueda arbolillorepe; // para revisar luego por cedulas repe
    //bool cedulafin = false;
    
    while (getline(archivo, lineasucia)) { // lineasucia tendria, por ejemplo, "01;Francisco            clientes sin repetidos "
    	cout << "Linea actual: " << lineasucia << endl;
    	linealimpia = LimpiaLinea(lineasucia); // linealimpia tendria, por ejemplo, "01;Francisco"
    	cout << "Linea actual despues de limpiar: " << linealimpia << endl;
		//cout << linealimpia << endl; //test
		cedula = SacaCedula(linealimpia);
		cout << "Cedula de la linea actual: " << cedula << endl;
			if (arbolillorepe.Buscarvalor(cedula) == false){ // si esa cedula ya estaba en el arbol, eso significa q esta repetida, x lo q no se mete
				arbolillorepe.InsertaNodo(cedula);
				cout << "Como la cedula " << cedula << " no esta repetida, se inserta en archivo nuevo" << endl;
				
				temp << linealimpia << endl; // esto es para meter esa linea en el archivo de clientes bueno, osea limpio Y sin repe
			}
			else{
				cout << "Cedula " << cedula << " repetida, no se inserta en archivo nuevo" << endl;
			}
			
	}
	archivo.close();
	temp.close();
	// borra el archivo de clientes original (el sucio y con repe) y renombra el de clientes bueno (limpio y sin repe) al mismo nombre de ese
	remove(nombreArchivo);
    rename("ClientesTemporal.txt", nombreArchivo);	
	}


/*
void CreaIndice(const char* nombreClientes, const char* nombreIndices){
	ifstream archivo(nombreClientes);
	if (archivo.is_open() == false){
		cout << "No se pudo abrir el archivo " << nombreClientes << endl;
		return;
	}
	
	ofstream indices(nombreIndices);
	string lineasucia, linealimpia;
	
}

*/



int main(){
	
	ABBusqueda arbolillo;
	LeerArchivoClientes("Clientes.txt", arbolillo);
	
	
	
	return 0;
}

