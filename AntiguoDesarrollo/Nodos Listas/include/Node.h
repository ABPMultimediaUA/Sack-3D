/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Node.h

Author:        Estudio Rorschach
Created:       08/01/2017 Miguel Cordoba
Modified:      24/01/2017 Miguel Cordoba

Overview:
Clase que contiene el codigo de funcionamiento para los nodos par las listas.

/******************************************************************************
                               Node
*******************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <class T>

class Node
{
    public:
        Node();
        Node(T);
        ~Node();

        Node *next;
        T data;

        void delete_all();
        void print();
};

#endif // NODE_H
