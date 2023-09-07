/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdint>



using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0){
      return false;
    }
    else if(curDim >= Dim){
      return false;
    }
    if(first[curDim]==second[curDim])  
      	return first<second;
    return (first[curDim] < second[curDim]); 
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double distance = 0, potentialDistance = 0;
    for(int i=0; i<Dim;i++){  
       	distance += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
       	potentialDistance += ((target[i]-potential[i])*(target[i]-potential[i]));
    }
    if(distance==potentialDistance) return potential < currentBest;
    return potentialDistance<distance;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.empty()){
       root = NULL;
       size = 0;
     }
     else {
       vector<Point<Dim>> points = newPoints;
       size = 0;
       buildTree(points, 0, points.size() - 1, 0, root);
     }
}

template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>>& newPoints, int left, int right, int dimension, KDTreeNode*& subroot)
{
  if(left > right){
    return;
  }
  size_t median = (left + right) / 2;

  Point<Dim> temp = quickAlg(newPoints, left, right, median, dimension);
  subroot = new KDTreeNode(temp);
  size++;
  if(subroot == NULL){
    wellThen();
  }
  buildTree(newPoints, left, median - 1, (dimension + 1) % Dim, subroot->left);
  buildTree(newPoints, median + 1, right, (dimension + 1) % Dim, subroot->right);
}

template <int Dim>
int KDTree<Dim>::split(vector<Point<Dim>>& list, int left, int right, size_t middle, int dimension){
  Point<Dim> pivotValue = list[middle];
  Point<Dim> temp = list[middle];
  list[middle] = list[right];
  list[right] = temp;
  size_t storeIndex = left;
  int i = left;
  while(i < right){
    if(smallerDimVal(list[i], pivotValue, dimension)){
      Point<Dim> temp2 = list[storeIndex];
      list[storeIndex] = list[i];
      list[i] = temp2;

      storeIndex++;
    }
    i++;
  }
  Point<Dim> temp3 = list[right];
  list[right] = list[storeIndex];
  list[storeIndex] = temp3;
  return storeIndex;
}


template <int Dim>
Point<Dim> KDTree<Dim>::quickAlg(vector<Point<Dim>>& list, int left, int right, size_t k, int dimension){
  if(left == right){ 
    return list[left]; 
  }
  size_t middle = (left + right) / 2;
  middle = split(list, left, right, middle, dimension);
  if (k == middle){
    return list[k];
  }
  if (list.size() < k) {
		return list[k];
	}
  else if(k < middle){
    return quickAlg(list, left, middle - 1, k, dimension);
  }
  else{
    return quickAlg(list, middle + 1, right, k, dimension);
  }
  
  //heap did not work
  /*std::priority_queue<int, vector<int>> pq(list.begin(), list.begin() + k);
 
    for (int i = k; i < list.size(); i++)
    {
      auto x = reinterpret_cast<std::uintptr_t>(list[i]);
        if (x < pq.top())
        {
            pq.pop();
            pq.push(list[i]);
        }
    }
 
    return pq.top();*/
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(this->root, other.root);
	size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != NULL) clear(root);
  	copy(this->root, rhs.root);
  	size = rhs.size;
  	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _delete(root);

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> currentBest = root->point;
    Point<Dim> temp = query;  //To prevent error
    findNearHelper(root, currentBest, temp, 0);
    return currentBest;
}

template <int Dim>
void KDTree<Dim>::findNearHelper(KDTreeNode* current, Point<Dim> &currentBest, Point<Dim> &query, int dimension) const{

    if(current == NULL){
      return;
    }
    KDTreeNode* next;
    KDTreeNode* alt;
    if(smallerDimVal(current->point, query, dimension)){
      next = current->right;
      alt = current->left;
    }
    else {
      next = current->left;
      alt = current->right;
    }
    findNearHelper(next, currentBest, query, (dimension + 1) % Dim);


    if(shouldReplace(query, currentBest, current->point)){
      currentBest = current->point;
    }


    double radius = 0.0;
    int i = 0;
    while(i < Dim){
      radius += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
      i++;
    }
    double distance =  (current->point[dimension] - query[dimension]) * (current->point[dimension] - query[dimension]);
    if(radius >= distance){
      findNearHelper(alt, currentBest, query, (dimension + 1) % Dim);
    }
}

template <int Dim>
void KDTree<Dim>::_copy(KDTreeNode*& current, KDTreeNode*& other){
  if(other == NULL){
    return;
  }
  current = new KDTreeNode(other->point);
  _copy(current->left, other->left);
  _copy(current->right, other->right);
}

template <int Dim>
void KDTree<Dim>::_delete(KDTreeNode*& subroot){
  if(subroot == NULL){
    return;
  }
  _delete(subroot->left);
  _delete(subroot->right);
  delete subroot;
}

template <int Dim>
void KDTree<Dim>::wellThen(){
  cout << "yo subroot null dawg this aint finna work lol, or this error was called for another reason but either way wtf you doin\n" << endl;
}