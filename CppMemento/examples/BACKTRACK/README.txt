https://www.geeksforgeeks.org/backtracking-algorithms/

// search the first solution
init
while(true)
    path = genNextPath
    if(!path.isValid())
	break
    if(isGoal(path))
	return path

// search all solutions
init
pathList = empty
path = genNextPath
while(path.isValid)
    if( isGoal(path))
	pathList.add(path)
    path = genNextPath
return pathList
