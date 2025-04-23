#include "Simulador.h"
#include <algorithm>

void Simulador::FCFS(std::vector<Proceso>& procesos) {
    std::sort(procesos.begin(), procesos.end(), [](Proceso a, Proceso b) {
        return a.llegada < b.llegada;
        });

    int tiempo = 0;
    for (auto& p : procesos) {
        if (tiempo < p.llegada)
            tiempo = p.llegada;

        p.inicio = tiempo;
        tiempo += p.rafaga;
        p.fin = tiempo;
    }
}

void Simulador::SJF(std::vector<Proceso>& procesos) {
    std::vector<Proceso> lista = procesos;
    procesos.clear();

    int tiempo = 0;
    while (!lista.empty()) {
        std::vector<Proceso> disponibles;
        for (auto& p : lista) {
            if (p.llegada <= tiempo)
                disponibles.push_back(p);
        }

        if (disponibles.empty()) {
            tiempo++;
            continue;
        }

        auto menor = std::min_element(disponibles.begin(), disponibles.end(), [](Proceso a, Proceso b) {
            return a.rafaga < b.rafaga;
            });

        Proceso siguiente = *menor;
        siguiente.inicio = tiempo;
        tiempo += siguiente.rafaga;
        siguiente.fin = tiempo;

        procesos.push_back(siguiente);

        lista.erase(std::remove_if(lista.begin(), lista.end(), [&](Proceso p) {
            return p.id == siguiente.id;
            }), lista.end());
    }
}

void Simulador::RoundRobin(std::vector<Proceso>& procesos, int quantum) {
    std::vector<Proceso> cola = procesos;
    std::vector<int> tiempo_restante(cola.size());

    for (size_t i = 0; i < cola.size(); ++i)
        tiempo_restante[i] = cola[i].rafaga;

    int tiempo = 0;
    std::vector<bool> iniciado(cola.size(), false);
    std::vector<Proceso> resultado;

    bool terminado = false;
    while (!terminado) {
        terminado = true;
        for (size_t i = 0; i < cola.size(); ++i) {
            if (tiempo_restante[i] > 0 && cola[i].llegada <= tiempo) {
                terminado = false;

                if (!iniciado[i]) {
                    cola[i].inicio = tiempo;
                    iniciado[i] = true;
                }

                int tiempo_ejec = std::min(quantum, tiempo_restante[i]);
                tiempo += tiempo_ejec;
                tiempo_restante[i] -= tiempo_ejec;

                if (tiempo_restante[i] == 0)
                    cola[i].fin = tiempo;
            }
        }

        // Si ningún proceso se ejecutó este ciclo, avanza el tiempo
        if (terminado) {
            for (size_t i = 0; i < cola.size(); ++i) {
                if (cola[i].llegada > tiempo) {
                    tiempo = cola[i].llegada;
                    terminado = false;
                    break;
                }
            }
        }
    }

    procesos = cola;
}
