#pragma once
#include "Nodo.h"
#include "Lista.h"
#include <vector>
#define MAX 32000
template <class T>
class Monticulo
{
private:
	Nodo<T> vec[MAX];
	int ult;
public:
	Monticulo();
	~Monticulo();
	bool insertar(T dato);
	bool eliminar(T& menor);
	void ReordenarAbajo(int pos);
	void ReordenarArriba(int pos);
	T getRaiz();
	Lista<T>& HeapSort(Lista<T>& listaor);
	void mostrar();
};

template<class T>
inline Monticulo<T>::Monticulo()
{
	ult = 0;
}

template<class T>
inline Monticulo<T>::~Monticulo()
{
}

template<class T>
inline bool Monticulo<T>::insertar(T dato)
{
	bool resp;
	if(ult==0)
	{
		ult = 1;
		vec[ult].setDato(dato);
		vec[ult].setExiste(true);
		resp = true;
	}
	else {
		ult = ult + 1;
		vec[ult].setDato(dato);
		vec[ult].setExiste(true);
		ReordenarArriba(ult);
		resp = true;
	}
	return resp;
}

template<class T>
inline bool Monticulo<T>::eliminar(T& mayor)
{
	bool resp;
	if (ult == 0) {
		resp = false;
	}
	else {
		mayor = vec[1].getDato();
		vec[1].setDato(vec[ult].getDato());
		vec[ult].setExiste(false);
		ult = ult - 1;
		resp = true;
		ReordenarAbajo(1);
	}
	return resp;
}

template<class T>
inline void Monticulo<T>::ReordenarAbajo(int pos)
{
	if (vec[pos].getExiste()) {
		Nodo<T> der = vec[pos * 2 + 1];
		Nodo<T> izq = vec[pos * 2];
		if (izq.getExiste() && der.getExiste() == false) {
			if(izq.getDato() > vec[pos].getDato())
			{
				T aux = vec[pos].getDato();
				vec[pos].setDato(izq.getDato());
				vec[pos * 2].setDato(aux);
				ReordenarAbajo(pos * 2);
			}
		}
		else {
			if(der.getDato()> vec[pos].getDato() && der.getExiste())
			{
				T aux = vec[pos].getDato();
				vec[pos].setDato(der.getDato());
				vec[pos * 2 + 1].setDato(aux);
				ReordenarAbajo(pos * 2 + 1);
			}
		    if(izq.getDato()> vec[pos].getDato() && izq.getExiste())
			{
					T aux = vec[pos].getDato();
					vec[pos].setDato(izq.getDato());
					vec[pos * 2].setDato(aux);
					ReordenarAbajo(pos * 2);
			}
		}
	}
}


template<class T>
inline T Monticulo<T>::getRaiz()
{
	return vec[1].getDato();
}

template<class T>
inline Lista<T>& Monticulo<T>::HeapSort(Lista<T>& original)
{
	Lista<T> lista;
	int i;
	for( i=0; i<10000; i++)
	{
		insertar(original[i]);
	}
	T dato = getRaiz();
	i = 0;
	while (eliminar(dato)==true){
		lista.Insertar(dato,i);
		i++;
		dato = getRaiz();
	}
	return lista;
}

template<class T>
inline void Monticulo<T>::mostrar()
{
	for (int i = 1; i <= ult; i++) {
		if (vec[i].getExiste() == true) {
			cout << vec[i].getDato() << " ";
		}
	}
	cout << endl;
}



template<class T>
inline void Monticulo<T>::ReordenarArriba(int pos)
{
	int padre = pos / 2;
	if(vec[padre].getExiste())
	{
		if(vec[pos].getDato()> vec[padre].getDato())
		{
			T aux = vec[pos].getDato();
			vec[pos].setDato(vec[padre].getDato());
			vec[padre].setDato(aux);
			ReordenarArriba(padre);
		}
	}
}

