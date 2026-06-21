#include "Dessin.h"

//dessine le graphique
void DessinerLigne(const CGraphique& graph)
{
	ILibGraph2* libgraph = GetLibGraph2();


	float startPosX = 150;
	float starPosY = 100;
	CPoint p(startPosX,starPosY);
	CSize size(static_cast<float>(graph.GetLargeur()) / 12 , static_cast<float>(graph.GetHauteur()) / graph.GetAnnees().size());
	ARGB color;
	std::vector<std::shared_ptr<CAnnee>> vpAnnees;
	std::shared_ptr<CAnnee> pAnnees = std::make_shared<CAnnee>();
	std::vector<std::shared_ptr<CCellule>> vpCels;
	std::shared_ptr<CCellule> pCels;
	vpAnnees = graph.GetAnnees();


	for (int j = 0; j < graph.GetNbAnneeAff(); j++) //desinne une case puis décalle de x pixel vers la droite
	{												//une fois decale 12 fois descent de y pixel vers le bas
		pAnnees = vpAnnees[j];
		vpCels = pAnnees->GetCels();
		p.m_fX = startPosX;
		for (int i = 0; i < vpCels.size() ; i++)
		{
			pCels = vpCels[i];
			CRectangle Rec(p, size);
			color = setColor(pCels);
			libgraph->setSolidBrush(color);
			libgraph->drawRectangle(Rec);
			p.m_fX += static_cast<float>(graph.GetLargeur()) / 12;
		}
		p.m_fY += static_cast<float>(graph.GetHauteur()) / graph.GetAnnees().size(); //le décalage de pixel est calculer en fonction du nombre d'element dans le graph
	}
}

//selectionne la couleur de la cellule
ARGB setColor(const std::shared_ptr<CCellule> cel)
{
	float temp = cel->GetTemp();
	ARGB ret;
	if (temp < -8.1)
	{
		ret = MakeARGB(255, 16, 108, 159);
	}
	else if(temp >= -8.1 && temp < -4.4)
	{
		ret = MakeARGB(255, 48, 153, 212);
	}
	else if (temp >= -4.4 && temp < -0.6)
	{
		ret = MakeARGB(255, 132, 211, 255);
	}
	else if (temp >= -0.6 && temp < 2.9)
	{
		ret = MakeARGB(255, 213, 240, 255);
	}
	else if (temp >= 2.9 && temp < 6.7)
	{
		ret = MakeARGB(255, 255, 210, 183);
	}
	else if (temp >= 6.7 && temp < 10.5)
	{
		ret = MakeARGB(255, 255, 164, 107);
	}
	else if (temp >= 10.5 && temp < 14.2)
	{
		ret = MakeARGB(255, 248, 109, 72);
	}
	else if (temp == 100000)
	{
		ret = MakeARGB(255, 0, 0, 0);
	}
	else if (temp >= 14.2)
	{
		ret = MakeARGB(255, 187, 39, 0);
	}
	
	return ret;
}

//Affiche la légende
void AfficherLegend(const CGraphique& graph)
{
	ILibGraph2* libgraph = GetLibGraph2();

	//Affiche les mois
	libgraph->setFont("calibri", 28.0f, LibGraph2::font_styles::FontStyleBold);
	libgraph->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));

	std::vector<std::string> sMois{ "Jan.", "Fev.", "Mar.", "Avr.", "Mai.", "Juin.", "Juil.", "Aout.", "Sept.", "Oct.", "Nov.", "Dec." };
	CPoint p(160, 5*126+100+27);
	for (int i = 0; i < sMois.size(); i++)
	{
		libgraph->drawString(sMois[i], p);
		p.m_fX += static_cast<float>(graph.GetLargeur()) / 12;
	}

	//Affiche les annees
	float font_size = 25.0f;
	libgraph->setFont("calibri", font_size, LibGraph2::font_styles::FontStyleBold);
	int esp = 100;
	for (auto& pAnnee : graph.GetAnnees())
	{
		int annee = pAnnee->GetAnnee();
		libgraph->drawString(LibGraph2::CString(std::to_string(annee)+"-"), LibGraph2::CPoint(50,esp));
		esp += static_cast<float>(graph.GetHauteur()) / graph.GetAnnees().size();
	}

	std::vector<ARGB> couleurs{ MakeARGB(255, 16, 108, 159),MakeARGB(255, 48, 153, 212), MakeARGB(255, 132, 211, 255) , MakeARGB(255, 213, 240, 255) , MakeARGB(255, 255, 210, 183) ,MakeARGB(255, 255, 164, 107),MakeARGB(255, 248, 109, 72),MakeARGB(255, 187, 39, 0) };
	std::vector<std::string> donnees{"< -8.2","-8.1 - -4.5","-4.4 - -0.7","-0.6 - 2.8","2.9 - 6.6","6.7 - 10.4","10.5 - 14.1","> 14.2"};
	int y = 625;
	CSize size(25, 25);
	for (size_t i=0;i<couleurs.size();++i)
	{
		libgraph->setSolidBrush(couleurs[i]);
		libgraph->drawRectangle(CRectangle(CPoint(1500,y), size));
		libgraph->setFont("calibri", 25.0f, LibGraph2::font_styles::FontStyleBold);
		libgraph->drawString(CString(donnees[i]), LibGraph2::CPoint(1535, y-7));
		y += 50;
	}
}




