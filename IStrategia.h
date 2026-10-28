#pragma once
#include "Zlecenie.h"
class IStrategia {
public:
	virtual void dodaj(const Zlecenie& z) = 0;
	virtual bool pusta() const = 0;
	virtual Zlecenie pobierz() = 0;
	virtual ~IStrategia() = default;
};