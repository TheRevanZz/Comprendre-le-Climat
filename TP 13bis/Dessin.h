#pragma once
#include "CGraphique.h"
#include "LibGraph2.h"
#include "CBouton.h"
using namespace LibGraph2;

void DessinerLigne(const CGraphique& graph);

ARGB setColor(const std::shared_ptr<CCellule> graph);

void AfficherLegend(const CGraphique& graph);

std::vector<std::shared_ptr<CBouton>> ListeBoutons(const CGraphique& graph);