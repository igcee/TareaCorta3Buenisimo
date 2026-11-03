#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <cstdio>
#include <vector>

class Nodo
{
public:
	int valor;
	int posicion;
	Nodo* Hizq;
	Nodo* Hder;

	Nodo(int valor, int posicion = -1);
};

typedef Nodo* pnodo;

Nodo::Nodo(int val, int pos)
{
	valor = val;
	posicion = pos;
	Hizq = NULL;
	Hder = NULL;
}

class ABBusqueda {
private:
	pnodo raiz;

	// Metodos auxiliares privados
	pnodo InsertaBinario(pnodo raiz, int valor, int posicion);
	bool Buscarvalor(pnodo raiz, int valor);
	int BuscarPosicion(pnodo raiz, int valor);
	//void InordenR(pnodo raiz);
	void PreordenR(pnodo raiz);
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

	void InsertaNodo(int valor, int posicion = -1);
	bool Buscarvalor(int valor);
	int BuscarPosicion(int valor);   // devuelve el indice, o -1 si no existe
	void Vaciar();

	//void InordenR();
	void PreordenR();
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


void ABBusqueda::InsertaNodo(int valor, int posicion)
{
	if (raiz == NULL) {
		raiz = new Nodo(valor, posicion);
	}
	else {
		raiz = InsertaBinario(raiz, valor, posicion);
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

pnodo ABBusqueda::InsertaBinario(pnodo raiz, int valor, int posicion)
{
	if (raiz == nullptr)
	{
		return new Nodo(valor, posicion);
	}

	if (valor < raiz->valor)
	{
		raiz->Hizq = InsertaBinario(raiz->Hizq, valor, posicion);
	}
	else
		if (valor > raiz->valor)
		{
			raiz->Hder = InsertaBinario(raiz->Hder, valor, posicion);
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
						raiz->posicion = sucesor->posicion;
						raiz->Hder = EliminarNodo(raiz->Hder, sucesor->valor);
					}
		}

	return raiz;
}

int ABBusqueda::BuscarPosicion(int valor)
{
	return BuscarPosicion(raiz, valor);
}

int ABBusqueda::BuscarPosicion(pnodo raiz, int valor)
{
	if (raiz == nullptr) return -1;
	if (valor == raiz->valor) return raiz->posicion;
	if (valor < raiz->valor)
		return BuscarPosicion(raiz->Hizq, valor);
	else
		return BuscarPosicion(raiz->Hder, valor);
}

void ABBusqueda::PreordenR()
{
	if (raiz == nullptr)
	{
		cout << "Arbol vacio" << endl;
		return;
	}
	cout << "Arbol en preorden (cedula[indice]): ";
	PreordenR(raiz);
	cout << endl;
}

void ABBusqueda::PreordenR(pnodo raiz)
{
	if (raiz == nullptr) return;
	cout << raiz->valor << "[" << raiz->posicion << "] ";
	PreordenR(raiz->Hizq);
	PreordenR(raiz->Hder);
}

void ABBusqueda::Vaciar()
{
	destruirArbol(raiz);
	raiz = nullptr;
}

string LimpiaLinea(string lineasucia) {
	// esta funcion es para limpiar las lineas de Clientes.txt, y devuelve string de linea ya limpia
	// por ejemplo, recibe    "01;Francisco            clientes sin repetidos "
	// y devuelve             "01;Francisco"
	string linealimpia = "";
	bool banderafin = false;
	int i = 0;
	int largo = lineasucia.size();

	while (banderafin == false and i < largo) { // si no se pone la condicion de largo se jode cuando no encuentra fin
		if (lineasucia[i] == ' ' or lineasucia[i] == '\t') { // si espacio, tab (\t), para
			banderafin = true;
		}
		else {
			linealimpia = linealimpia + lineasucia[i];
			i++;
		}
	}
	return linealimpia;
}

int SacaCedula(string linealimpia) {
	// recibe la linea ya limpia, y saca la cedula
	// por ejemplo, recibe "01;Francisco"
	// y devuelve 01, como int no como string
	int i = 0;
	string cedu = "";
	while (linealimpia[i] != ';') {
		cedu = cedu + linealimpia[i];
		i++;
	}
	int cedubuena = stoi(cedu);
	return cedubuena;
	//return cedu; // lo cambie para q lo sacara como string, pq salia como 1, en lugar de 01. Igual no creo q de problemas (si es q siquiera se ocupaba q saliera como int en primer lugar)
}


void LeerArchivoClientes(const char* nombreArchivo, ABBusqueda& arbol) {

	ifstream archivo(nombreArchivo);
	if (archivo.is_open() == false) {
		cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
		return;
	}

	string filaencabezado;
	string lineasucia, linealimpia;
	int cedula;
	int pos = 0;

	//getline(archivo, filaencabezado); // ignorar encabezado (Clientes.txt no tiene encabezado)
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
		if (arbolillorepe.Buscarvalor(cedula) == false) { // si esa cedula ya estaba en el arbol, eso significa q esta repetida, x lo q no se mete
			arbolillorepe.InsertaNodo(cedula);
			cout << "Como la cedula " << cedula << " no esta repetida, se inserta en archivo nuevo" << endl;

			temp << linealimpia << endl; // esto es para meter esa linea en el archivo de clientes bueno, osea limpio Y sin repe
		}
		else {
			cout << "Cedula " << cedula << " repetida, no se inserta en archivo nuevo" << endl;
		}

	}
	archivo.close();
	temp.close();
	// borra el archivo de clientes original (el sucio y con repe) y renombra el de clientes bueno (limpio y sin repe) al mismo nombre de ese
	remove(nombreArchivo);
	rename("ClientesTemporal.txt", nombreArchivo);
}


// =====================================================================
//  FUNCIONES AUXILIARES PARA LINEAS DE Clientes.txt
// =====================================================================
string QuitaRetorno(string linea) {
	if (linea.size() > 0 && linea[linea.size() - 1] == '\r') {
		linea.erase(linea.size() - 1);
	}
	return linea;
}

// "01;Francisco" -> "01"   (cedula como texto, para no perder el 0)
string SacaCedulaTexto(string linea) {
	string cedu = "";
	int i = 0;
	while (i < (int)linea.size() && linea[i] != ';') {
		cedu = cedu + linea[i];
		i++;
	}
	return cedu;
}

// "01;Francisco" -> "Francisco"   (tambien sirve con "01;Francisco;1")
string SacaNombre(string linea) {
	string nombre = "";
	int i = 0;
	while (i < (int)linea.size() && linea[i] != ';') {
		i++;
	}
	i++;
	while (i < (int)linea.size() && linea[i] != ';') {
		nombre = nombre + linea[i];
		i++;
	}
	return nombre;
}

// borrado = tiene un segundo ';' seguido de 1. Ejemplo: "01;Francisco;1"
bool EstaBorrado(string linea) {
	int cantidadPuntoComa = 0;
	int ultimo = -1;
	for (int i = 0; i < (int)linea.size(); i++) {
		if (linea[i] == ';') {
			cantidadPuntoComa++;
			ultimo = i;
		}
	}
	if (cantidadPuntoComa < 2) return false;
	return linea.substr(ultimo + 1) == "1";
}

// =====================================================================
//  PARTE 2: INDEXAR Y SALVAR INDICES   (formato  indice;cedula)
// =====================================================================
void CreaIndice(const char* nombreClientes, const char* nombreIndices) {
	ifstream clientes(nombreClientes);
	if (clientes.is_open() == false) {
		cout << "No se pudo abrir el archivo " << nombreClientes << endl;
		return;
	}
	ofstream indices(nombreIndices);
	string linea;
	int pos = 0;

	while (getline(clientes, linea)) {
		linea = QuitaRetorno(linea);
		if (linea.size() == 0) continue;
		if (EstaBorrado(linea) == false) {
			indices << pos << ";" << SacaCedulaTexto(linea) << endl;
		}
		pos++;
	}
	clientes.close();
	indices.close();
}

// =====================================================================
//  PARTE 3: CONSTRUIR EL ARBOL A PARTIR DE Indices.txt
// =====================================================================
void ConstruirArbol(const char* nombreIndices, ABBusqueda& arbol) {
	ifstream indices(nombreIndices);
	if (indices.is_open() == false) {
		cout << "No se pudo abrir el archivo " << nombreIndices << endl;
		return;
	}
	arbol.Vaciar();

	string linea;
	while (getline(indices, linea)) {
		linea = QuitaRetorno(linea);
		if (linea.size() == 0) continue;
		int pos = stoi(SacaCedulaTexto(linea));   // antes del ';' = indice
		int cedula = stoi(SacaNombre(linea));     // despues del ';' = cedula
		arbol.InsertaNodo(cedula, pos);
	}
	indices.close();
}

// =====================================================================
//  PARTE 4: MEMORIA CACHE (20 clientes) Y BUSQUEDA
// =====================================================================
const int TAM_CACHE = 20;

class Cache {
public:
	int posicion[TAM_CACHE];
	string cedula[TAM_CACHE];
	string nombre[TAM_CACHE];
	int cantidad;

	Cache();
	void Vaciar();
	int BuscarPosicion(int pos);
	void Cargar(const char* nombreClientes, int posicionInicial);
	void Mostrar();
};

Cache::Cache() {
	cantidad = 0;
}

void Cache::Vaciar() {
	cantidad = 0;
}

int Cache::BuscarPosicion(int pos) {
	for (int i = 0; i < cantidad; i++) {
		if (posicion[i] == pos) return i;
	}
	return -1;
}

// reemplaza la cache: el buscado (queda de primero) + 19 siguientes no borrados, circular
void Cache::Cargar(const char* nombreClientes, int posicionInicial) {
	ifstream clientes(nombreClientes);
	if (clientes.is_open() == false) {
		cout << "No se pudo abrir el archivo " << nombreClientes << endl;
		return;
	}
	vector<string> lineas;
	string linea;
	while (getline(clientes, linea)) {
		linea = QuitaRetorno(linea);
		if (linea.size() == 0) continue;
		lineas.push_back(linea);
	}
	clientes.close();

	int total = lineas.size();
	cantidad = 0;
	int i = posicionInicial;
	int visitados = 0;

	while (cantidad < TAM_CACHE && visitados < total) {
		if (EstaBorrado(lineas[i]) == false) {
			posicion[cantidad] = i;
			cedula[cantidad] = SacaCedulaTexto(lineas[i]);
			nombre[cantidad] = SacaNombre(lineas[i]);
			cantidad++;
		}
		i = (i + 1) % total;
		visitados++;
	}
}

void Cache::Mostrar() {
	cout << "----------- CACHE (" << cantidad << "/" << TAM_CACHE << ") -----------" << endl;
	if (cantidad == 0) {
		cout << "Cache vacia" << endl;
		cout << "-----------------------------------" << endl;
		return;
	}
	cout << "Indice\tCedula\tNombre" << endl;
	for (int i = 0; i < cantidad; i++) {
		cout << posicion[i] << "\t" << cedula[i] << "\t" << nombre[i] << endl;
	}
	for (int i = cantidad; i < TAM_CACHE; i++) {
		cout << "Espacio libre" << endl;
	}
	cout << "-----------------------------------" << endl;
}

// arbol -> indice -> cache -> (si no esta) recarga la cache desde el archivo
void BuscarCliente(ABBusqueda& arbol, Cache& cache, int cedula) {
	int pos = arbol.BuscarPosicion(cedula);
	if (pos == -1) {
		cout << "La cedula " << cedula << " no existe (o fue eliminada)." << endl;
		return;
	}
	int espacio = cache.BuscarPosicion(pos);
	if (espacio != -1) {
		cout << "Encontrado en CACHE (no se leyo el archivo)." << endl;
	}
	else {
		cout << "No estaba en cache: se reemplazan los 20 registros." << endl;
		cache.Cargar("Clientes.txt", pos);
		espacio = cache.BuscarPosicion(pos);
	}
	cout << "Cliente -> Indice: " << cache.posicion[espacio] << " | Cedula: " << cache.cedula[espacio]
		<< " | Nombre: " << cache.nombre[espacio] << endl;
}




int main() {

	ABBusqueda arbolillo;
	LeerArchivoClientes("Clientes.txt", arbolillo);

	Cache cache;
	CreaIndice("Clientes.txt", "Indices.txt");
	ConstruirArbol("Indices.txt", arbolillo);

	int opcion = -1;
	while (opcion != 0) {
		cout << endl << "1. Ver arbol (preorden)" << endl;
		cout << "2. Ver cache" << endl;
		cout << "3. Buscar cliente" << endl;
		cout << "0. Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;

		if (opcion == 1) {
			arbolillo.PreordenR();
		}
		else if (opcion == 2) {
			cache.Mostrar();
		}
		else if (opcion == 3) {
			int cedula;
			cout << "Cedula a buscar: ";
			cin >> cedula;
			BuscarCliente(arbolillo, cache, cedula);
			arbolillo.PreordenR();
			cache.Mostrar();
		}
	}



	return 0;
}

