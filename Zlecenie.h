#pragma once
// =============================================================================
//  Zlecenie.h — jedno zgłoszenie (zlecenie magazynowe)
// =============================================================================
//  Zlecenie to tylko "kartka z danymi". Nigdy się nie zmienia w trakcie
//  symulacji — to, KIEDY je obsłużono i KTO, zapisujemy osobno (Wynik).
//
//  Czas liczymy w sekundach jako liczby całkowite (czas dyskretny).
// =============================================================================

struct Zlecenie {
    int id = 0;
    int nadejscie = 0;   // chwila pojawienia się w systemie [s]
    int realizacja = 0;  // ile trwa obsługa [s]
    // TODO (krok 3): priorytet, termin (deadline), wymagana specjalizacja
};

// Co się stało ze zleceniem — wypełnia symulator, czytają statystyki.
struct Wynik {
    int idZlecenia = 0;
    int nadejscie = 0;
    int start = 0;       // kiedy wykonawca zaczął pracę
    int koniec = 0;      // kiedy skończył
    int wykonawca = 0;   // indeks wykonawcy

    int oczekiwanie() const { return start - nadejscie; }
    int pobyt() const { return koniec - nadejscie; }
};
