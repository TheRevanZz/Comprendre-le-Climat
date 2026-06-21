#include "CBouton.h"

void CBouton::Afficher() const
{
	ILibGraph2* libgraph = GetLibGraph2();

	//Dessine le rectangle
	libgraph->setSolidBrush(m_ARGB);
	libgraph->drawRectangle(CRectangle(m_cpCoord, m_csSize));
	libgraph->setSolidBrush(MakeARGB(255,0, 0, 0));
	//Dessine le texte du bouton
	libgraph->setFont("calibri", m_fFontSize, LibGraph2::font_styles::FontStyleBold);
	libgraph->drawString(CString(m_sTxt), m_cpCoord);
}

//Test si le pointeur de la souris est sur le bouton
bool CBouton::Hover(const LibGraph2::CPoint& ptP1) const
{
	return ((ptP1.m_fX > m_cpCoord.m_fX && ptP1.m_fX < m_cpCoord.m_fX + m_csSize.m_fWidth) && (ptP1.m_fY > m_cpCoord.m_fY && ptP1.m_fY < m_cpCoord.m_fY + m_csSize.m_fHeight));
}

//créer un bouton pour chaque décennie
std::vector<std::shared_ptr<CBouton>> ListeBoutons(const CGraphique& graph)
{
	std::vector<std::shared_ptr<CBouton>> lst;
	int coord = 100;
	for (auto& pAnnee : graph.GetAnnees())
	{
		float y = static_cast<float>(graph.GetHauteur()) / graph.GetAnnees().size();
		CPoint(150, 100);
		std::shared_ptr<CBouton> bouton = std::make_shared<CBouton>(CPoint(150, coord), CSize(graph.GetLargeur(), y), std::to_string(pAnnee->GetAnnee()), 0.0f, (255, 16, 108, 159));
		lst.push_back(bouton);
		coord += y;
	}
	return lst;
}