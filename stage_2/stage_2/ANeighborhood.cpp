#include "ANeighborhood.h"

// mapowanie typów s¹siedztwa i ich opisów
const std::map<NeigborhoodTypes, std::string> ANeighborhood::typeNames = {
	{NeigborhoodTypes::EXCHANGE, "Przez zamiane"},
	{NeigborhoodTypes::INSERT, "Przez wstawienie"},
};

ANeighborhood::~ANeighborhood()
{
}
