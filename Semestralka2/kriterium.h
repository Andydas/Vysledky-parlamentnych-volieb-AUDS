 #pragma once
template<typename O, typename T>
class Kriterium
{
public:
	virtual T ohodnot(O objekt) = 0;
protected:
	Kriterium() {}
};

