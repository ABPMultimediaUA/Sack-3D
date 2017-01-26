/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          List.h

Author:        Estudio Rorschach
Created:       08/01/2017 Miguel Cordoba
Modified:      24/01/2017 Miguel Cordoba

Overview:
Clase que contiene el codigo de funcionamiento para las listas.


/******************************************************************************
                               List
*******************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "node.h"

using namespace std;

template <class T>

class List
{
    public:
        List();
        ~List();

        void add_head(T);
        void add_end(T);
        void add_sort(T);
        void concat(List);
        void del_all();
        void del_by_data(T);
        void del_by_position(int);
        void fill_by_user(int);
        void fill_random(int);
        void intersection(List);
        void invert();
        void load_file(string);
        void print();
        void save_file(string);
        void search(T);
        void sort();

    private:
        Node<T> *m_head;
        int m_num_nodes;
};

#endif // LIST_H
