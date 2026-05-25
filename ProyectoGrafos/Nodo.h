#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class Nodo
{
private:
	T dato;
	bool existe;
	int frecuencia;
	
public:
	Nodo();
	~Nodo();
	T getDato();
	bool getExiste();
	void setDato(T dato);
	void setExiste(bool existe);
	int getFrecuencia();
	void Increment();
};

template<class T>
inline Nodo<T>::Nodo()
{
	existe = false;
	frecuencia = 0;
}

template<class T>
inline Nodo<T>::~Nodo()
{
}

template<class T>
inline T Nodo<T>::getDato()
{
	return dato;
}

template<class T>
inline bool Nodo<T>::getExiste()
{
	return existe;
}

template<class T>
inline void Nodo<T>::setDato(T dato)
{
	this->dato = dato;
}

template<class T>
inline void Nodo<T>::setExiste(bool existe)
{
	this->existe = existe;
}

template<class T>
inline int Nodo<T>::getFrecuencia()
{
	return frecuencia;
}

template<class T>
inline void Nodo<T>::Increment()
{
	frecuencia++;
}
