#pragma once
#include "LibGraph2.h"
#include "CGraphique.h"
using namespace LibGraph2;

class CBouton
{
	CPoint m_cpCoord;
	CSize m_csSize;
	std::string m_sTxt;
	float m_fFontSize;
	ARGB m_ARGB;

public:
	CBouton(CPoint pts, CSize size, std::string string, float font_size, ARGB argb) { m_cpCoord = pts; m_csSize = size; m_sTxt = string; m_fFontSize = font_size; m_ARGB = argb; };

	void Afficher() const;
	bool Hover(const LibGraph2::CPoint& ptP1) const;

	std::string GetTxt() const { return m_sTxt; };
};