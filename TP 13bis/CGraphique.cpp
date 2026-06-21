#include "CGraphique.h"
#include <iostream>

CGraphique CGraphique::Top5AnneePlusChaude() const
{
	//initialise les objets et variable
	CGraphique NewGraph;
	std::vector<std::shared_ptr<CAnnee>> top5_annee;
	std::vector<float> top5_temp;
	top5_annee.resize(5);
	top5_temp.resize(5);
	float temp;

	//parcour chaque année
	for (auto& pAnnee : m_vAnnees)
	{
		//calcule la moyenne annuelle
		if (pAnnee && pAnnee->GetCels().size()>0)
		{
			temp = 0;
			for (auto& pMois : pAnnee->GetCels())
				temp += pMois->GetTemp();
		}
		temp /= pAnnee->GetCels().size();

		//parcour le top5 pour savoir si l'année doit y être
		for (size_t i = 0; i<=4; i++)
		{
			if (4-i == 4 && top5_temp[4-i] < temp)
			{
				top5_temp[4 - i] = temp;
				top5_annee[4 - i] = pAnnee;
			}
			else if (top5_temp[i] < temp && i!=0)
			{
				top5_temp[4 - i + 1] = top5_temp[4 - i];
				top5_temp[4 - i] = temp;
				top5_annee[4 - i + 1] = top5_annee[4 - i];
				top5_annee[4 - i] = pAnnee;
			}
			else
				break;
		}
	}
	//Créer le graph de retour
	for (auto& pAnnee : top5_annee)
		NewGraph.SetAnnees(pAnnee);
	NewGraph.SetAnneeStart(NewGraph.GetAnnees()[0]);
	NewGraph.SetHauteur(GetHauteur());
	NewGraph.SetLargeur(GetLargeur());
	NewGraph.SetNbAnneeAff(5);
	return NewGraph;
}

CGraphique CGraphique::Top5AnneePlusFroide() const
{
	//initialise les objets et variable
	CGraphique NewGraph;
	std::vector<std::shared_ptr<CAnnee>> top5_annee;
	std::vector<float> top5_temp;
	top5_annee.resize(5);
	top5_temp.resize(5);

	//initialise les temperatures à 100000 pour être sûr que ça soit supérieur aux moyennes annuelles
	for (auto& pTemp : top5_temp)
		pTemp = 100000;
	float temp;

	//parcour chaque année
	for (auto& pAnnee : m_vAnnees)
	{
		//calcule la moyenne annuelle
		if (pAnnee && pAnnee->GetCels().size() > 0)
		{
			temp = 0;
			for (auto& pMois : pAnnee->GetCels())
				temp += pMois->GetTemp();
		}
		temp /= pAnnee->GetCels().size();

		//parcour le top5 pour savoir si l'année doit y être
		for (size_t i = 0; i <= 4; i++)
		{
			if (4 - i == 4 && top5_temp[4 - i] > temp)
			{
				top5_temp[4 - i] = temp;
				top5_annee[4 - i] = pAnnee;
			}
			else if (top5_temp[i] > temp && i != 0)
			{
				top5_temp[4 - i + 1] = top5_temp[4 - i];
				top5_temp[4 - i] = temp;
				top5_annee[4 - i + 1] = top5_annee[4 - i];
				top5_annee[4 - i] = pAnnee;
			}
			else
				break;
		}
	}
	//Créer le graph de retour
	for (auto& pAnnee : top5_annee)
		NewGraph.SetAnnees(pAnnee);
	NewGraph.SetAnneeStart(NewGraph.GetAnnees()[0]);
	NewGraph.SetHauteur(GetHauteur());
	NewGraph.SetLargeur(GetLargeur());
	NewGraph.SetNbAnneeAff(5);
	return NewGraph;
}

//Fonction qui fait la moyenne de temp de toute les Decenies et qui renvoie un nouveau CGraphique de toute les décennies 
CGraphique CGraphique::ConvertToDec() const
{
	CGraphique graph_dec;
	std::shared_ptr<CAnnee> pAnnee;

	std::vector<float> Temp_NewTemp;
	std::vector<int> Temp_NbMois;
	Temp_NewTemp.resize(12);
	Temp_NbMois.resize(12);

	int LastYear = m_vAnnees[0]->GetAnnee()/10;
	LastYear *= 10;

	//parcour chaque année
	for (auto& pAn : m_vAnnees)
	{
		//parcour chaque mois de l'année
		for (size_t i = 0; i < 12; i++)
		{
			//si on change de décennie
			if (LastYear+10 < pAn->GetAnnee() && LastYear != 0)
			{
				pAnnee = std::make_shared<CAnnee>();
				pAnnee->SetAnnee(LastYear);
				for (size_t j = 0; j < 12; j++)
				{
					std::shared_ptr<CCellule> Cel = std::make_shared<CCellule>(Temp_NewTemp[j] / Temp_NbMois[j]);
					pAnnee->SetCel(Cel, j);
				}
				graph_dec.SetAnnees(pAnnee);

				LastYear += 10;
			}
			if (pAn->GetCels()[i]->GetTemp() != 100000)
			{
				Temp_NewTemp[i] += pAn->GetCels()[i]->GetTemp();
				Temp_NbMois[i] += 1;
			}
		}
	}
	pAnnee = std::make_shared<CAnnee>();
	pAnnee->SetAnnee(LastYear);
	for (size_t j = 0; j < 12; j++)
	{
		std::shared_ptr<CCellule> Cel = std::make_shared<CCellule>(Temp_NewTemp[j] / Temp_NbMois[j]);
		pAnnee->SetCel(Cel, j);
	}
	graph_dec.SetAnnees(pAnnee);
	graph_dec.SetLargeur(GetLargeur());
	graph_dec.SetHauteur(GetHauteur());

	LastYear += 10;

	graph_dec.SetAnneeStart(m_vAnnees[0]);
	graph_dec.SetNbAnneeAff(graph_dec.GetAnnees().size());
	return graph_dec;
}


//Fonction qui va chercher toute les annees d'une decenie et les renvoyer dans un nouveau CGraphique
CGraphique CGraphique::ZoomDec(const std::shared_ptr<CAnnee> startYear)  
{
	CGraphique ret;
	std::shared_ptr<CAnnee> lastYear = this->GetAnnees().back();
	int i, maxI;

	if (startYear->GetAnnee() == 1896) //verification des decenies qui ne sont pas completes
	{
		i = 0;
		ret.CAnneeStart = this->GetAnnees()[0];
		maxI = 4;
		startYear->SetAnnee(1896);
	}
	else if (startYear->GetAnnee() == 2020)
	{
		i = 0;
		maxI = 3;
	}
	else
	{
		i = 0;
		maxI = 10;
	}

	for (i; i < maxI; i++) //insertion des Annees dans le nouveau graph 
	{
		ret.SetAnnees(this->GetAnnees()[this->GetAnnees().size() - (lastYear->GetAnnee() - startYear->GetAnnee()) + i - 1]);
	}
	ret.m_nHauteur = this->m_nHauteur; //parametrage du nouveau graph
	ret.m_nLargeur = this->m_nLargeur;
	ret.m_stNbAnneeAff = maxI;
	ret.CAnneeStart = startYear;
	return ret;
}