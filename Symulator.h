#pragma once
// =============================================================================
//  Symulator.h — pętla zdarzeń dyskretnych
// =============================================================================
//  Co robi uruchom():
//    A: zegar = czas najwcześniejszego zdarzenia w kalendarzu
//    B: obsłuż WSZYSTKIE zdarzenia z tą chwilą
//         nadejście   -> zlecenie do kolejki, zaplanuj następne nadejście
//         zakończenie -> wykonawca znów wolny
//    C: dopóki jest wolny wykonawca i czekające zlecenie -> przydziel,
//       zaplanuj zakończenie obsługi
//  Powtarzaj, aż kalendarz będzie pusty.
//
//  Fazy B i C są rozdzielone celowo: przydział zapada dopiero wtedy, gdy znamy
//  wszystko, co wydarzyło się w danej sekundzie.
// =============================================================================

#include "Wykonawca.h"
#include "Zdarzenie.h"
#include "Zlecenie.h"

#include <queue>
#include <vector>

class Symulator {
public:
    Symulator(std::vector<Zlecenie> zlecenia, std::vector<Wykonawca> wykonawcy);

    // Przeprowadza symulację i zwraca historię obsługi każdego zlecenia.
    std::vector<Wynik> uruchom();

    const std::vector<Wykonawca>& wykonawcy() const { return wykonawcy_; }
    int czasKonca() const { return teraz_; }

private:
    void zaplanuj(int czas, TypZdarzenia typ, int indeks);
    void obsluzNadejscie(int indeksZlecenia);
    void obsluzZakonczenie(int indeksWykonawcy);
    void przydzielZlecenia();  // faza C

    std::vector<Zlecenie> zlecenia_;   // posortowane po czasie nadejścia
    std::vector<Wykonawca> wykonawcy_;

    // Kolejka oczekujących. TODO (krok 3): zamienić na interfejs strategii,
    // żeby obok FIFO dało się podłączyć np. std::priority_queue po priorytecie.
    std::queue<Zlecenie> kolejka_;

    // Kalendarz zdarzeń przyszłych: kopiec, na szczycie najwcześniejsze zdarzenie.
    std::priority_queue<Zdarzenie, std::vector<Zdarzenie>, PozniejszeZdarzenie> kalendarz_;

    std::vector<Wynik> wyniki_;
    std::vector<int> rekordWykonawcy_;  // który wpis w wyniki_ należy do bieżącej pracy wykonawcy
    int teraz_ = 0;
    int licznikZdarzen_ = 0;
};
