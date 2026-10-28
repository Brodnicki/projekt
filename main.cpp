// =============================================================================
//  main.cpp — krok 1: jeden wykonawca, kolejka FIFO, zlecenia wpisane w kodzie
// =============================================================================
//  Kompilacja:  g++ -std=c++17 -Wall -Wextra *.cpp -o symulator
//  Uruchomienie: ./symulator
//
//  Wynik do sprawdzenia NA KARTCE (FIFO, jeden wykonawca):
//    #1: przychodzi 0,  trwa 10 -> start 0,  koniec 10, czeka 0
//    #2: przychodzi 5,  trwa 3  -> start 10, koniec 13, czeka 5
//    #3: przychodzi 6,  trwa 1  -> start 13, koniec 14, czeka 7
//    średnie oczekiwanie = (0 + 5 + 7) / 3 = 4 s
// =============================================================================
#include "Symulator.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

int main() {
    const std::vector<Zlecenie> zlecenia{
        {1, 0, 10},  // {id, nadejscie, realizacja}
        {2, 5, 3},
        {3, 6, 1},
    };
    const std::vector<Wykonawca> wykonawcy{Wykonawca("Ewa"), Wykonawca("Jan")};
    
    // TODO (krok 2): dodaj drugiego wykonawcę, np. Wykonawca("Jan"), i sprawdź wynik ręcznie.


    Symulator symulator(zlecenia, wykonawcy);
    const std::vector<Wynik> wyniki = symulator.uruchom();

    std::cout << "\n  ID  nadejscie  start  koniec  oczekiwanie\n";
    double suma = 0;
    for (const Wynik& w : wyniki) {
        std::cout << std::setw(4) << w.idZlecenia << std::setw(11) << w.nadejscie << std::setw(7) << w.start
                  << std::setw(8) << w.koniec << std::setw(13) << w.oczekiwanie() << '\n';
        suma += w.oczekiwanie();
    }
    if (!wyniki.empty()) {
        std::cout << "\nSrednie oczekiwanie: " << suma / static_cast<double>(wyniki.size()) << " s\n";
    }
    for (const Wykonawca& w : symulator.wykonawcy()) {
        const double wykorzystanie = 100.0 * w.czasPracy() / std::max(1, symulator.czasKonca());
        std::cout << w.nazwa() << ": obsluzone zlecenia: " << w.obsluzone() << ", wykorzystanie " << std::fixed
                  << std::setprecision(1) << wykorzystanie << "%\n";
    }
    return 0;
}
