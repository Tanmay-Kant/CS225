/* Your code here! */

#include "dsets.h"


void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++){
        _elems.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if(_elems[elem]<0){
        return elem;
    }
    else{
        int root = find(_elems[elem]);
        _elems[elem] = root;
        return root;
    }
}

void DisjointSets::setunion(int a, int b){
    int r1 = find(a);
    int r2 = find(b);
    int temp = _elems[r1] + _elems[r2];
    if (_elems[r1] <= _elems[r2]){
        _elems[r2] = r1;
        _elems[r1] = temp;
    }
    else if(_elems[r1] > _elems[r2]){
        _elems[r1] = r2;
        _elems[r2] = temp;
    } 
}

int DisjointSets::size(int elem){
    int root = find(elem);
    return -_elems[root];
}	
