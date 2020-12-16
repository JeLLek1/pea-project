#include "ANeighborhood.h"

// mapowanie typ�w s�siedztwa i ich opis�w
const std::map<NeigborhoodTypes, std::string> ANeighborhood::typeNames = {
	{NeigborhoodTypes::EXCHANGE, "Przez zamiane"},
	{NeigborhoodTypes::INSERT, "Przez wstawienie"},
};

ANeighborhood::~ANeighborhood()
{
}
