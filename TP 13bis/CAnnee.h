#pragma once
#include <vector>
#include <memory>
#include "CCellule.h"

class CAnnee
{
	int m_iAnnee = 0;
	std::vector<std::shared_ptr<CCellule>> m_vCels;

public:
	CAnnee() { m_vCels.resize(12); };

	int GetAnnee() const;
	void SetAnnee(const int Annee);

	std::vector<std::shared_ptr<CCellule>> GetCels() const;
	void SetCel(std::shared_ptr<CCellule> pCel,int mois);
};

