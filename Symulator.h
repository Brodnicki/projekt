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
//.h to plik nagłówkowy czyli miejsce raczej gdzie jest szablon klasy niż jego "mięsko"
#include "Wykonawca.h"
#include "Zdarzenie.h"
#include "Zlecenie.h"
#include "IStrategia.h"
#include <queue>
#include <memory>
#include <vector>
//Klasa Symulator
class Symulator {
    //Rzeczy dostępne dla innych klas
public:
    //Konstruktor, jego argumentem jest std::vector, jest to lista która może rosnąć, między <> jest to typ danych jaki się zwiększa
    //Zlecenie pochodzi z pliku nagłówkowego Zlecenie.h
    //Wykonawca jest klasą pochodzącą z pliku nagłówkowego Wykonawca.h
    Symulator(std::vector<Zlecenie> zlecenia, std::vector<Wykonawca> wykonawcy);

    // Przeprowadza symulację , nie przyjmując argumentów, zwraca Wynik który jest wektorem
    std::vector<Wynik> uruchom();
    //Przekazuje orginalną listę i zwraca wykonawcy_, const to obietnica że niczego się nie zmodyfikuje
    const std::vector<Wykonawca>& wykonawcy() const { return wykonawcy_; }
    //Zmienne kończącę się na _ oznacza dane w środku klasy
    int czasKonca() const { return teraz_; }
    //Rzeczy prywatne tylko dla klasy Symulator
private:
    //Funkcja nic nie zwraca, w nawiasach dane potrzebne do wykonania funckji
    void zaplanuj(int czas, TypZdarzenia typ, int indeks);
    //Wpisuje zlecenie do kolejki
    void obsluzNadejscie(int indeksZlecenia);
    //Wykonuje się jak zlecenie się skończy bierze za argument indeks wykonawcy
    void obsluzZakonczenie(int indeksWykonawcy);
    //Przydziela zlecenie
    void przydzielZlecenia();  // faza C

    std::vector<Zlecenie> zlecenia_;   // posortowane po czasie nadejścia
    std::vector<Wykonawca> wykonawcy_; //Wszyscy pracownicy

    // Kolejka oczekujących. TODO (krok 3): zamienić na interfejs strategii,
    // żeby obok FIFO dało się podłączyć np. std::priority_queue po priorytecie.

    std::unique_ptr<IStrategia> kolejka_;

    // Kalendarz zdarzeń przyszłych: kopiec, na szczycie najwcześniejsze zdarzenie.
    //Takie pudełko sprawdzające które zdarzenie jest wcześniejsze, bierze zdarzenie,
    //To w czym je trzymamy, oraz reguła porównawcza (późniejsze zdarzenie)
    std::priority_queue<Zdarzenie, std::vector<Zdarzenie>, PozniejszeZdarzenie> kalendarz_;

    std::vector<Wynik> wyniki_;
    std::vector<int> rekordWykonawcy_;  // który wpis w wyniki_ należy do bieżącej pracy wykonawcy
    int teraz_ = 0;
    int licznikZdarzen_ = 0;
};
