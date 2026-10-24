#pragma once
// =============================================================================
//  Wykonawca.h — pracownik obsługujący zlecenia
// =============================================================================
//  Pracownik NIE "pracuje" w pętli. To tylko kilka zmiennych:
//    • bieżące zlecenie (puste = wolny, zawiera coś = zajęty),
//    • licznik czasu pracy i obsłużonych zleceń.
//  Kiedy praca się skończy, wie symulator — zapisuje to w kalendarzu zdarzeń.
// =============================================================================

#include "Zlecenie.h"

#include <optional>
#include <string>

class Wykonawca {
public:
    explicit Wykonawca(std::string nazwa);

    const std::string& nazwa() const { return nazwa_; }
    bool wolny() const { return !biezace_.has_value(); }

    // WOLNY -> ZAJĘTY
    void rozpocznij(const Zlecenie& z, int teraz);
    // ZAJĘTY -> WOLNY; zwraca ukończone zlecenie
    Zlecenie zakoncz(int teraz);

    int czasPracy() const { return czasPracy_; }
    int obsluzone() const { return obsluzone_; }

    // TODO (krok 3): tempo pracy i specjalizacje

private:
    std::string nazwa_;
    std::optional<Zlecenie> biezace_;  // std::optional = "zlecenie albo nic"
    int startBiezacego_ = 0;
    int czasPracy_ = 0;
    int obsluzone_ = 0;
};
