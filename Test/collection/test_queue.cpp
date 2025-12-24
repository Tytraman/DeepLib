#include "DeepLib/lib.hpp"
#include "DeepLib/collection/queue.hpp" // Adapte le chemin si nécessaire

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::queue<int> q = deep::queue<int>(context.get());

    // --- TEST 1 : État initial ---

    if (!q.is_empty())
    {
        return 10; // La file doit être vide à la création
    }

    if (q.count() != 0)
    {
        return 11; // Le compteur doit être à 0
    }

    // --- TEST 2 : Ajout d'éléments (Enqueue) ---

    if (!q.add(10))
    {
        return 20;
    }

    if (q.is_empty())
    {
        return 21;
    }

    if (q.count() != 1)
    {
        return 22;
    }

    if (q.get_front() != 10)
    {
        return 23;
    }

    if (q.get_back() != 10)
    {
        return 24;
    }

    q.add(20);
    q.add(30);

    if (q.count() != 3)
    {
        return 25;
    }

    // --- TEST 3 : Inspection (Front / Back) ---
    // La file contient : [10, 20, 30]
    // Front (Tête) doit être 10 (le premier entré)
    // Back (Queue) doit être 30 (le dernier entré)

    if (q.get_front() != 10)
    {
        return 30;
    }

    if (q.get_back() != 30)
    {
        return 31;
    }

    // --- TEST 4 : Retrait d'éléments (Dequeue/Pop) ---

    if (!q.pop())
    {
        return 40;
    }

    // État attendu : [20, 30]
    if (q.count() != 2)
    {
        return 41;
    }

    if (q.get_front() != 20)
    {
        return 42;
    }

    // Deuxième Pop : doit retirer 20
    q.pop();

    // État attendu : [30]
    if (q.count() != 1)
    {
        return 43;
    }

    if (q.get_front() != 30)
    {
        return 44;
    }

    if (q.get_back() != 30)
    {
        return 45;
    }

    // Troisième Pop : doit retirer 30
    q.pop();

    // État attendu : [] (Vide)
    if (!q.is_empty())
    {
        return 46;
    }

    if (q.count() != 0)
    {
        return 47;
    }

    // --- TEST 5 : Pop sur file vide ---

    if (q.pop())
    {
        return 50;
    }

    return 0;
}
