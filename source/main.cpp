#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
  
// Generar Distribucion Uniforme de 20'000 Puntos
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(1,100);

    const int dim = stoi(argv[1]);      //Nro de dimensiones - Cmd arg
    int puntos[20000][dim];

    for (int d = 0; d < dim; d++) {
        for (int i = 0; i < 20000; i++) {
            puntos[i][d] = distribution(gen);
        }
    }

// Calcular y almacenar las distancias al primer punto
    float distancias[19999];
    float min = INFINITY, max = 0;

    for (int i = 1; i < 20000; i++) {
        int sum = 0;
        for (int d = 0; d < dim; d++) {
            sum += (puntos[i][d] - puntos[0][d]) * (puntos[i][d] - puntos[0][d]);
        }
        float dis = sqrt((double)sum);
        if (dis < min) min = dis;
        else if (dis > max) max = dis;
        distancias[i] = dis;
    }

    end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


// Transformar las distancias a un rango [0-1]
    int range_dis[11];
    float max_min = max - min;

    for (int i = 0; i < 19999; i++) {
        float dis = 10 * (distancias[i] - min) / max_min;
        ++range_dis[(int)dis];
    }

// Imprimir la tabla de distancias y el tiempo 
    for (int i = 0; i < 11; i++) {
        cout << range_dis[i] << endl;
    }
    cout << "DIM: " << dim << ", tiempo: " << duration << " milisegundos\n";
    return 0;
}
