#pragma once
#include "NodoCola.h"
#include <iostream>

using namespace std;

template <typename T>
class Cola
{
private:
    NodoCola<T> *rear;
    NodoCola<T> *front;
public:
    Cola(): front(NULL), rear(NULL){}

    



};