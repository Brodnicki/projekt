#include "Symulator.h"

#include <algorithm>
#include <iostream>
#include <utility>

Symulator::Symulator(std::vector<Zlecenie> zlecenia, std::vector<Wykonawca> wykonawcy)
    : zlecenia_(std::move(zlecenia)), wykonawcy_(std::move(wykonawcy)), rekordWykonawcy_(wykonawcy_.size(), -1) {
    // Zlecenia muszą być ułożone chronologicznie (przy remisie — po id).
    std::sort(zlecenia_.begin(), zlecenia_.end(), [](const Zlecenie& a, const Zlecenie& b) {
        return a.nadejscie != b.nadejscie ? a.nadejscie < b.nadejscie : a.id < b.id;
    });
}

void Symulator::zaplanuj(int czas, TypZdarzenia typ, int indeks) {
    kalendarz_.push(Zdarzenie{czas, typ, indeks, licznikZdarzen_++});
}

std::vector<Wynik> Symulator::uruchom() {
    if (!zlecenia_.empty()) {
        // Planujemy tylko PIERWSZE nadejście — każde kolejne zaplanuje poprzednie.
        zaplanuj(zlecenia_.front().nadejscie, TypZdarzenia::Nadejscie, 0);
    }

    while (!kalendarz_.empty()) {
        // ----- Faza A: przesuń zegar -----
        teraz_ = kalendarz_.top().czas;

        // ----- Faza B: wszystkie zdarzenia z chwilą teraz_ -----
        while (!kalendarz_.empty() && kalendarz_.top().czas == teraz_) {
            const Zdarzenie z = kalendarz_.top();  // kopia, bo pop() usunie element
            kalendarz_.pop();
            if (z.typ == TypZdarzenia::Nadejscie) {
                obsluzNadejscie(z.indeks);
            } else {
                obsluzZakonczenie(z.indeks);
            }
        }

        // ----- Faza C: przydział -----
        przydzielZlecenia();
    }
    return wyniki_;
}

void Symulator::obsluzNadejscie(int indeksZlecenia) {
    const Zlecenie& z = zlecenia_[static_cast<std::size_t>(indeksZlecenia)];
    std::cout << "[t=" << teraz_ << "] nadeszlo zlecenie #" << z.id << '\n';
    kolejka_.push(z);

    // Samoplanujące się nadejścia: w kalendarzu jest zawsze tylko jedno przyszłe nadejście.
    const int nastepne = indeksZlecenia + 1;
    if (nastepne < static_cast<int>(zlecenia_.size())) {
        zaplanuj(zlecenia_[static_cast<std::size_t>(nastepne)].nadejscie, TypZdarzenia::Nadejscie, nastepne);
    }
}

void Symulator::obsluzZakonczenie(int indeksWykonawcy) {
    Wykonawca& w = wykonawcy_[static_cast<std::size_t>(indeksWykonawcy)];
    const Zlecenie z = w.zakoncz(teraz_);
    const int rekord = rekordWykonawcy_[static_cast<std::size_t>(indeksWykonawcy)];
    wyniki_[static_cast<std::size_t>(rekord)].koniec = teraz_;
    std::cout << "[t=" << teraz_ << "] " << w.nazwa() << " konczy zlecenie #" << z.id << '\n';
}

void Symulator::przydzielZlecenia() {
    // Dopóki ktoś czeka i ktoś jest wolny — łączymy ich w pary.
    for (std::size_t i = 0; i < wykonawcy_.size() && !kolejka_.empty(); ++i) {
        Wykonawca& w = wykonawcy_[i];
        if (!w.wolny()) {
            continue;
        }
        const Zlecenie z = kolejka_.front();  // FIFO: najstarsze zlecenie
        kolejka_.pop();
        w.rozpocznij(z, teraz_);

        Wynik wynik;
        wynik.idZlecenia = z.id;
        wynik.nadejscie = z.nadejscie;
        wynik.start = teraz_;
        wynik.wykonawca = static_cast<int>(i);
        rekordWykonawcy_[i] = static_cast<int>(wyniki_.size());
        wyniki_.push_back(wynik);

        // Wykonawca nic nie odlicza — po prostu wpisujemy do kalendarza, kiedy skończy.
        zaplanuj(teraz_ + z.realizacja, TypZdarzenia::Zakonczenie, static_cast<int>(i));
        std::cout << "[t=" << teraz_ << "] " << w.nazwa() << " zaczyna zlecenie #" << z.id << " (czekalo "
                  << wynik.oczekiwanie() << " s)\n";
    }
}
