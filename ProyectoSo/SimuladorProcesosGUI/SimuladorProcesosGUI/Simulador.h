#pragma once
#pragma once
#include <vector>

struct Proceso {
    int id;
    int llegada;
    int rafaga;
    int inicio;
    int fin;
};

class Simulador {
public:
    static void FCFS(std::vector<Proceso>& procesos);
    static void SJF(std::vector<Proceso>& procesos);
    static void RoundRobin(std::vector<Proceso>& procesos, int quantum);
};

