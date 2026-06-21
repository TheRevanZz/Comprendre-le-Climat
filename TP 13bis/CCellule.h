#pragma once
class CCellule
{
	float m_fTemp;

public:
	CCellule(float temp) { m_fTemp = temp; };

	float GetTemp() const { return m_fTemp; };
	void SetTemp(float Temp) { m_fTemp = Temp; };
};

