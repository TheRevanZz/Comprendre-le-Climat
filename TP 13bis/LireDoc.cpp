#include "LireDoc.h"
#include <fstream>
#include <iostream>
#include <sstream>

//Comprend toutes les fonction pour lire le CVS et inserer les donnees dans les objets

void LireDoc(CGraphique& graph)
{
	std::ifstream in("aigoual_Mensuel.csv");
	if (!in.is_open())
		std::cerr << "Problème d'ouverture du fichier \"aigoual_Mensuel.csv\".\n";
	else {

		std::string line;
		std::string annee;
		int last_annee=0;
		std::string mois;
		std::string temp;
		std::shared_ptr<CAnnee> pannee;

		std::getline(in, line);

		//initialise toutes les températures à 100000 (abscence de donnée)
		pannee = std::make_shared<CAnnee>();
		for (size_t i = 0; i < 12; i++)
			pannee->SetCel(std::make_shared<CCellule>(100000), i);

		//lit le document ligne par ligne
		while (!in.eof())
		{
			temp = "";
			annee = "";
			mois = "";

			//recup l'annee
			for (size_t i = 0; i < 4; i++)
				annee += line[i];
			//si on change d'annee
			if (last_annee != std::stoi(annee) && last_annee != 0)
			{
				pannee->SetAnnee(last_annee);
				graph.SetAnnees(pannee);
				pannee = std::make_shared<CAnnee>();
				for (size_t i = 0; i < 12; i++)
					pannee->SetCel(std::make_shared<CCellule>(100000), i);

			}
			//recup le mois
			for (size_t i = 4; i < 6; i++)
				mois += line[i];

			//recup la temp
			for (size_t i = 7; i < line.size() && (line[i] != ';'); i++)
				temp += line[i];

			//créer la cellule du mois
			std::shared_ptr<CCellule> cel = std::make_shared<CCellule>(std::stof(temp));
			pannee->SetCel(cel,std::stoi(mois)-1);
			last_annee = std::stoi(annee);
			std::getline(in, line);
		}
		//rajoute la dernière année
		pannee->SetAnnee(last_annee);
		graph.SetAnnees(pannee);
		pannee = std::make_shared<CAnnee>();
		for (size_t i = 0; i < 12; i++)
			pannee->SetCel(std::make_shared<CCellule>(100000), i);
	}

}