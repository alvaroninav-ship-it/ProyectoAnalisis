#pragma once
#include "Nodo.h"
#define MAXIMO 10000

template <class T>
class Lista
{
private:
	Nodo<T> vec[MAXIMO];
public:
	Lista();
	~Lista();
	void Insertar(T dato, int pos);
	void Mostrar();
	int operator[](int x);
	void RetornarCambio(int num);
};

template<class T>
inline Lista<T>::Lista()
{
}

template<class T>
inline Lista<T>::~Lista()
{
}

template<class T>
inline void Lista<T>::Insertar(T dato, int pos)
{
	vec[pos].setDato(dato);
	vec[pos].setExiste(true);
}

template<class T>
inline void Lista<T>::Mostrar()
{
	int e = 0;
	while (vec[e].getExiste()) {
		cout << vec[e].getDato() << " ";
		e++;
	}
	cout << endl;
}

template<class T>
inline int Lista<T>::operator[](int x)
{
	return vec[x].getDato();
}

template<class T>
inline void Lista<T>::RetornarCambio(int num)
{
	int i=0;
	while (vec[i].getExiste()) {
		while (num % vec[i].getDato() == 0) {
			vec[i].Increment();
		}
		i++;
	}
	while (vec[i].getExiste()) {
		cout << vec[i].getDato() << "x" << vec[i].getFrecuencia()<<" , ";
		i++;
	}
}

