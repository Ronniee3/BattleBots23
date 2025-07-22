#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <limits>
#include <map>
using namespace std;

struct Robot {
    string nombre;
    int vida;
    int daño;
    int defensa;
    int velocidad;
};
vector<string> historialBusquedas;

    
string aMinusculasYTrim(string texto) {
    while (!texto.empty() && isspace(texto.front())) texto.erase(texto.begin());
    while (!texto.empty() && isspace(texto.back())) texto.pop_back();
    for (char& c : texto) c = tolower(c);
    return texto;
}

void buscarCampeonatoPorNombre() {
    ifstream archivo("CAMPEONATOS.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de campeonatos.\n";
        return;
    }

    string nombreBuscado, añoBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingresa el nombre del campeonato: ";
    getline(cin, nombreBuscado);

    cout << "Ingresa el año (puedes dejar vacío si no lo sabes): ";
    getline(cin, añoBuscado);

    historialBusquedas.push_back("Búsqueda de campeonato: " + nombreBuscado + " (" + añoBuscado + ")");

    nombreBuscado = aMinusculasYTrim(nombreBuscado);
    añoBuscado = aMinusculasYTrim(añoBuscado);

    bool encontrado = false;
    string linea;


    while (getline(archivo, linea)) {
    string nombre = aMinusculasYTrim(linea);
    if (nombre.empty()) continue;
    vector<string> datos;

    string lineaDatos;
    while (getline(archivo, lineaDatos) && lineaDatos != "*") {
        datos.push_back(lineaDatos);
    }

        string sitio = "", dia = "", año = "", categoria = "", rondas = "", ganador = "";

        for (string campo : datos) {
            size_t pos = campo.find(":");
            if (pos == string::npos) continue;

            string clave = aMinusculasYTrim(campo.substr(0, pos));
            string valor = aMinusculasYTrim(campo.substr(pos + 1));

            if (clave == "sitio") sitio = valor;
            else if (clave == "día" || clave == "dia") dia = valor;
            else if (clave == "año" || clave == "ano") año = valor;
            else if (clave == "categorías" || clave == "categorias") categoria = valor;
            else if (clave == "n° de rondas" || clave == "n de rondas") rondas = valor;
            else if (clave == "ganador/es") ganador = valor;
        }

        string nombreNormalizado = aMinusculasYTrim(nombre);


        if (nombreNormalizado.find(nombreBuscado) != string::npos &&
            (añoBuscado.empty() || año.find(añoBuscado) != string::npos)) {
            
            cout << "\nCampeonato encontrado:\n";
            cout << "Nombre: " << nombre << endl;
            cout << "Sitio: " << sitio << endl;
            cout << "Día: " << dia << endl;
            cout << "Año: " << año << endl;
            cout << "Categorías: " << categoria << endl;
            cout << "N° de rondas: " << rondas << endl;
            cout << "Ganador/es: " << ganador << endl;

            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ningún campeonato con esos datos.\n";
    }

    archivo.close();
}





int calcularDaño(Robot atacante, Robot defensor) {
    int base = atacante.daño - defensor.defensa / 2;
    if (base < 0) base = 0;
    return base + rand() % 4;
}

Robot combatir(Robot r1, Robot r2) {
    Robot* atacante;
    Robot* defensor;

    if (r1.velocidad >= r2.velocidad) {
        atacante = &r1;
        defensor = &r2;
    } else {
        atacante = &r2;
        defensor = &r1;
    }

    while (r1.vida > 0 && r2.vida > 0) {
        int daño = calcularDaño(*atacante, *defensor);
        defensor->vida -= daño;
        if (defensor->vida < 0) defensor->vida = 0;

        cout << atacante->nombre << " ataca a " << defensor->nombre << " causando " << daño << " de daño.\n";
        cout << "Vida de " << defensor->nombre << ": " << defensor->vida << "\n\n";

        Robot* temp = atacante;
        atacante = defensor;
        defensor = temp;
    }

    return (r1.vida > 0) ? r1 : r2;
}

void iniciarBatalla() {
    srand(time(0));

    Robot lista[3];
    lista[0] = {"Tombstone", 30, 12, 5, 10};
    lista[1] = {"Bite Force", 30, 10, 8, 8};
    lista[2] = {"End game", 30, 14, 3, 12};

    cout << "\nBatalla de prueba: Elige tu robot:\n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << lista[i].nombre << "\n";
    }

    int eleccion;
    cout << "Tu elección: ";
    cin >> eleccion;

    while (eleccion < 1 || eleccion > 3) {
        cout << "Número inválido. Intenta otra vez: ";
        cin >> eleccion;
    }

    Robot elegido = lista[eleccion - 1];

    int rivalIndex;
    do {
        rivalIndex = rand() % 3;
    } while (rivalIndex == (eleccion - 1));

    Robot enemigo = lista[rivalIndex];

    cout << "\nTu robot: " << elegido.nombre << "\n";
    cout << "Enfrenta a: " << enemigo.nombre << "\n";

    Robot ganador = combatir(elegido, enemigo);

    if (ganador.nombre == elegido.nombre) {
        cout << "¡Y el ganador es "<< ganador.nombre << "!\n";
    } else {
        cout << "!Y el ganador es " << ganador.nombre << "!\n" << "Perdiste... ¡Buena suerte para la proxima! :)\n";
    }
}
void mostrarHistorial() {
    cout << "\nHistorial de búsquedas:\n";
    if (historialBusquedas.empty()) {
        cout << "Su historial esta vacio, amigo :(\n";
    } else {
        for (int i = 0; i < historialBusquedas.size(); ++i) {
            cout << i+1 << ". " << historialBusquedas[i] << endl;
        }
    }
}
     
void curiosidadess(){
     map<string, string> curiosidades;

    ifstream archivo("CURIOSIDADES.txt");
    if (!archivo.is_open()) {
        cout << "¡Uyyy! No se pudo cargar el archivo...";
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string clave, texto;
        getline(ss, clave, ';');
        getline(ss, texto);

        curiosidades[clave] = texto;
    }

    archivo.close();

    srand(static_cast<unsigned int>(time(0)));

    int eleccionnum = 1 + (rand() % 9);
    string claveBuscada = to_string(eleccionnum);

    auto it = curiosidades.find(claveBuscada);
    if (it != curiosidades.end()) {
        cout << "Curiosidad #" << claveBuscada << ": " << it->second << endl;
    } 
}



 void mostrarMenuPrincipal(){
     int opcion;
     do { 
        cout << "====== Menu ========" << endl;
         cout << "1. Buscar campeonato\n";
          cout << "2. Ver historial\n";
          cout << "3. Simular batalla\n";
          cout << "4. Curiosidades\n";
         cout << "0. Salir\n";
         cout << endl;
         cout << "Selecciona una opción: ";
         cin >> opcion;
         
         switch(opcion) {
            case 1: buscarCampeonatoPorNombre(); break;
            case 2: mostrarHistorial(); break;
            case 3: iniciarBatalla(); break;
            case 4: curiosidadess(); break;
            default: cout << "Opción no válida.\n";
        }
     } while (opcion != 0);
 }
 
 
int main()
{
    cout << "\t ¡Bienvenid@! \t" << endl << "Este programa te ayudará a buscar un campeonato de BattleBots!" << endl;
    cout << endl;
    mostrarMenuPrincipal();

    return 0;
}
