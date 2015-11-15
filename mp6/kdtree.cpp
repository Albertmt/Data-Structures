/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const{
    /**
     * @todo Implement this function!
     */
	if(first[curDim] == second[curDim])
		return first < second;
	return first[curDim] < second[curDim];
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
	
	if(distSquared(target, potential) == distSquared(target, currentBest))
		return potential < currentBest;
	return distSquared(target, potential) < distSquared(target, currentBest);
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
	points = newPoints;
	build(0, points.size() - 1, 0);
}

template<int Dim>
void KDTree<Dim>::build(int start, int end, int dim){
	int mean = (start + end) / 2;
	quickSelect(start, end, mean, dim);
	if(start < mean - 1)
		build(start, mean - 1, (dim + 1) % Dim);
	if(end > mean + 1)
        	build(mean + 1, end, (dim + 1) % Dim);
	
}

template<int Dim>
void KDTree<Dim>::quickSelect(int start, int end, int place, int dim){
	if(start >= end)
		return;
	int mean = (start + end) / 2;
	mean = partition(start, end, mean, dim);
	if(place == mean)
		return;
	if(place < mean)
		quickSelect(start, mean - 1, place, dim);
	else
		quickSelect(mean + 1, end, place, dim);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const	{
    /**
     * @todo Implement this function!
     */
	Point<Dim> currBest;
	bool isFirst = true;
	fNNhelper(/*start*/ 0, /*end*/ points.size() - 1,
		 /*dim*/ 0, query, currBest, /*minDis*/ 0, isFirst);

	return currBest;
}

template<int Dim>
void KDTree<Dim>::fNNhelper(int start, int end, int dim, const Point<Dim> & query, 
				Point<Dim> & currBest, int minDis, bool & isFirst) const{
	
	//handling a leaf
	if(start >= end){
		if(isFirst){
			isFirst = false;
			currBest = points[end];
		}
		else{
			if(shouldReplace(query, currBest, points[start]))
				currBest = points[start];
		}
        	return;
	}

	//handling an internal node
	int mean = (start + end)/2;

	if(smallerDimVal(query, points[mean], dim)){
		fNNhelper(start, mean - 1, (dim + 1) % Dim, query, currBest, minDis, isFirst);
		if(shouldReplace(query, currBest, points[mean]))
			currBest = points[mean];
		minDis = distSquared(currBest, query);
		if((query[dim] - points[mean][dim]) * (query[dim] - points[mean][dim]) <= minDis)
			fNNhelper(mean + 1, end, (dim + 1) % Dim, query, currBest, minDis, isFirst);
	}
	else{
        	fNNhelper(mean + 1, end, (dim + 1) % Dim, query, currBest, minDis, isFirst);
		if(shouldReplace(query, currBest, points[mean]))
			currBest = points[mean];
		minDis = distSquared(currBest, query);
		if((query[dim] - points[mean][dim]) * (query[dim] - points[mean][dim]) <= minDis)
			fNNhelper(start, mean - 1, (dim + 1) % Dim, query, currBest, minDis, isFirst);   
	}
}
