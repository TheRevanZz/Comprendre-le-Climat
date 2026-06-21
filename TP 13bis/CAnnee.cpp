#include "CAnnee.h"

int CAnnee::GetAnnee() const {
	return this->m_iAnnee;
}

void CAnnee::SetAnnee(const int Annee) {
	m_iAnnee = Annee;
}

std::vector<std::shared_ptr<CCellule>> CAnnee::GetCels() const {
	return this->m_vCels;
}

void CAnnee::SetCel(std::shared_ptr<CCellule> pCel, int mois)
{
	m_vCels[mois] = pCel;
}