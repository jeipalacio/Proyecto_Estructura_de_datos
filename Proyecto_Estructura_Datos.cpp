#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 10;
struct Nodo { string nombre; int padre; };

struct Grafo {
    int n = 0;
    string nombres[MAXN];
    int mat[MAXN][MAXN];
    Grafo() {
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j)
                mat[i][j] = 0;
    }
    int agregarNodo(const string &nombre) {
        for (int i = 0; i < n; ++i) if (nombres[i] == nombre) return i;
        if (n >= MAXN) return -1;
        nombres[n] = nombre;
        return n++;
    }
    void conectar(int a, int b) {
        if (a < 0 || b < 0 || a >= n || b >= n) return;
        mat[a][b] = mat[b][a] = 1;
    }
    void imprimirMatriz() const {
        cout << "Matriz de Adyacencia:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) cout << mat[i][j] << " ";
            cout << "\n";
        }
    }
};

void warshall(int M[MAXN][MAXN], int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M[i][j] = (M[i][j] != 0) ? 1 : 0;
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (M[i][k] && M[k][j]) M[i][j] = 1;
}

void imprimirMatrizCaminos(int M[MAXN][MAXN], int n) {
    cout << "\nMatriz de Caminos (alcanzabilidad):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << M[i][j] << " ";
        cout << "\n";
    }
}

void dfs_generador(int u, const Grafo &g, bool vis[MAXN], int parent[MAXN]) {
    vis[u] = true;
    for (int v = 0; v < g.n; ++v) {
        if (g.mat[u][v] && !vis[v]) {
            parent[v] = u;
            dfs_generador(v, g, vis, parent);
        }
    }
}

void imprimirArbolDFS(int parent[MAXN], int n, const string names[MAXN]) {
    cout << "\nArbol (parent index):\n";
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        if (parent[i] == -1) cout << "root";
        else cout << parent[i] << " (" << names[parent[i]] << ")";
        cout << " -> " << names[i] << "\n";
    }
}

void imprimirAislados(const Grafo &g) {
    cout << "\nNodos aislados:\n";
    bool any = false;
    for (int i = 0; i < g.n; ++i) {
        bool iso = true;
        for (int j = 0; j < g.n; ++j) if (g.mat[i][j]) { iso = false; break; }
        if (iso) { cout << i << " -> " << g.nombres[i] << "\n"; any = true; }
    }
    if (!any) cout << "Ninguno\n";
}

int main() {
    Grafo g;
    vector<Nodo> arbol;
    arbol.push_back({"Universidad", -1});
    arbol.push_back({"Ingenieria", 0});
    arbol.push_back({"Edificio A", 1});

    int A = g.agregarNodo("EdificioA");
    int B = g.agregarNodo("EdificioB");
    int C = g.agregarNodo("EdificioC");
    int D = g.agregarNodo("EdificioD");
    int E = g.agregarNodo("EdificioE");

    g.conectar(A, B);
    g.conectar(A, E);
    g.conectar(B, C);
    g.conectar(C, D);
    g.conectar(D, E);

    g.imprimirMatriz();

    int reach[MAXN][MAXN];
   
    for (int i = 0; i < g.n; ++i)
        for (int j = 0; j < g.n; ++j)
            reach[i][j] = g.mat[i][j];
    warshall(reach, g.n);
    imprimirMatrizCaminos(reach, g.n);

    bool vis[MAXN] = {0};
    int parent[MAXN];
    for (int i = 0; i < MAXN; ++i) parent[i] = -1;
    int start = 0;
    parent[start] = -1;
    dfs_generador(start, g, vis, parent);
    imprimirArbolDFS(parent, g.n, g.nombres);

    imprimirAislados(g);
    return 0;
}
