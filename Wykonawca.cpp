#include "Wykonawca.h"

#include <stdexcept>
#include <utility>

Wykonawca::Wykonawca(std::string nazwa) : nazwa_(std::move(nazwa)) {}

void Wykonawca::rozpocznij(const Zlecenie& z, int teraz) {
    if (!wolny()) {
        // Programowanie defensywne: taki błąd oznacza pomyłkę w symulatorze.
        throw std::logic_error(nazwa_ + " jest już zajęty");
    }
    biezace_ = z;
    startBiezacego_ = teraz;
}

Zlecenie Wykonawca::zakoncz(int teraz) {
    if (wolny()) {
        throw std::logic_error(nazwa_ + " nie ma czego kończyć");
    }
    Zlecenie z = *biezace_;
    biezace_.reset();  // znów wolny
    czasPracy_ += teraz - startBiezacego_;
    ++obsluzone_;
    return z;
}
