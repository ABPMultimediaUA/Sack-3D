/*******************************************************************************
/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Node.cpp

Author:        Estudio Rorschach
Created:       08/01/2017 Miguel Cordoba
Modified:      24/01/2017 Miguel Cordoba

Overview:
Clase que contiene el codigo de funcionamiento para los nodos par las listas.

/******************************************************************************
                               Node
*******************************************************************************/

#include "node.h"

// Constructor por defecto
template<typename T>

Node<T>::Node()
{
    data = NULL;
    next = NULL;
}

// Constructor por parámetro
template<typename T>
Node<T>::Node(T data_)
{
    data = data_;
    next = NULL;
}

// Eliminar todos los Nodos
template<typename T>
void Node<T>::delete_all()
{
    if (next)
        next->delete_all();
    delete this;
}

// Imprimir un Nodo
template<typename T>
void Node<T>::print()
{
    //cout << "Node-> " << "Dato: " << dato << " Direcion: " << this << " Siguiente: " << next << endl;
    cout << data << "-> ";
}

template<typename T>
Node<T>::~Node() {}
