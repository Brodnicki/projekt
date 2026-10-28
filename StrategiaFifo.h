#pragma once
#include "IStrategia.h"
#include <queue>
//Fifo polega na tym że kto pierwszy przychodzi jest lepszy.
//Każda z strategii będzie dziedziczyć po interfejsie strategii
//Niech żyje podejście obiektowe dla wyższej oceny!!!
class StrategiaFifo : public IStrategia {
public:
	//Nowe zlecenie będzie na końcu kolejki
	void dodaj(const Zlecenie& z) override {
		kolejka_.push(z);
	}

	//Sprawdzanie czy ktoś czeka
	bool pusta() const override { return kolejka_.empty(); }
};