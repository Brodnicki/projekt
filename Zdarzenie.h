#pragma once
// =============================================================================
//  Zdarzenie.h — wpis w kalendarzu zdarzeń przyszłych
// =============================================================================
//  Symulacja to tylko zdarzenia: "zlecenie nadeszło" i "wykonawca skończył".
//  Między nimi nic się nie zmienia, więc zegar przeskakuje od zdarzenia
//  do zdarzenia zamiast tykać co sekundę.
// =============================================================================

enum class TypZdarzenia { Nadejscie, Zakonczenie };

struct Zdarzenie {
    int czas = 0;
    TypZdarzenia typ = TypZdarzenia::Nadejscie;
    int indeks = 0;   // Nadejscie: indeks zlecenia; Zakonczenie: indeks wykonawcy
    int numer = 0;    // kolejność planowania — rozstrzyga remisy czasowe
};

// Komparator dla std::priority_queue.
// UWAGA: priority_queue trzyma na szczycie element "NAJWIĘKSZY", a my chcemy
// NAJWCZEŚNIEJSZY. Dlatego zwracamy true, gdy a jest PÓŹNIEJSZE od b.
struct PozniejszeZdarzenie {
    bool operator()(const Zdarzenie& a, const Zdarzenie& b) const {
        if (a.czas != b.czas) {
            return a.czas > b.czas;
        }
        return a.numer > b.numer;  // przy tym samym czasie: kto wcześniej zaplanowany
    }
};
