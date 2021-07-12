#pragma once

template <typename O>
class Comparator
{
public:
	Comparator(bool vzostupne) : vzostupne_(vzostupne) {}
	virtual ~Comparator() {}
	int operator()(O a, O b);
protected:
	virtual int compare(O a, O b) = 0;
private:
	bool vzostupne_;
};

template<typename O>
inline int Comparator<O>::operator()(O a, O b)
{
	return vzostupne_ ? compare(a, b) : compare(b, a); //alebo namiesto compare(b,a) skus compare(a,b)*-1
}