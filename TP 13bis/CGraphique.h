#pragma once
#include "CAnnee.h"

class CGraphique
{
	std::vector<std::shared_ptr<CAnnee>> m_vAnnees;
	int m_nHauteur;
	int m_nLargeur;
	size_t m_stNbAnneeAff;
	std::shared_ptr<CAnnee> CAnneeStart;

public:
	std::vector<std::shared_ptr<CAnnee>> GetAnnees() const { return m_vAnnees; };
	void SetAnnees(std::shared_ptr<CAnnee> annee) { m_vAnnees.push_back(annee); };

	int GetHauteur() const { return m_nHauteur; };
	void SetHauteur(int Hauteur) { m_nHauteur = Hauteur; };

	int GetLargeur() const { return m_nLargeur; };
	void SetLargeur(int largeur) { m_nLargeur = largeur; };

	size_t GetNbAnneeAff() const { return m_stNbAnneeAff; };
	void SetNbAnneeAff(size_t nb) { m_stNbAnneeAff = nb; };

	std::shared_ptr<CAnnee> GetAnneeStart() const { return CAnneeStart; };
	void SetAnneeStart(std::shared_ptr<CAnnee> pAnnee) { CAnneeStart = pAnnee; ; }

	CGraphique Top5AnneePlusChaude() const;
	CGraphique Top5AnneePlusFroide() const;

	CGraphique ConvertToDec() const;

	CGraphique ZoomDec(const std::shared_ptr<CAnnee> startYear);
};


