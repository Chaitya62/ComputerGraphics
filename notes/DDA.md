# Digital Differential Analyzer


Derived using `y = mx + c`

### Points to note


1. m = dx/ dy

2. if m < 1 or (dx > dy) :
	X(k+1) = (Xk) + 1
	Y(k+1) = (Yk) + m

3. if m > 1 or (dy > dx)):
	Y(k+1) = (Yk) + 1
	X(k+1) = (Xk) + 1/m

4. if m == 1 or (dx == dy):
	Y(k+1) = (Yk) + 1
	X(k+1) = (Xk) + 1



### Algorithm
	
1. Read points x1,y1 and x2,y2
2. Calculate dx = (x2-x1) and dy = (y2-y1)
3. Calculate no. of steps 
	steps = dx if dx > dy
	steps = dy if dy > dx
	steps = dx or dy if dx == dy
4. Calculate x-increament (xi) and y-increament (yi)
	xi = (dx/ steps ) 
	yi = (dy/ steps )
	*Notice how the above step will take care of different values of m i.e m < 1 or m>1 or m==1*
5.  Initiailize x = x1 and y = y1

6.  putpixel(x, y)

7. for i 1 to steps
	 x = x + xi
	 y = y + yi
	putpixel(x, y)
8. End


You can find the Code [here](../code/DDA.cpp)


### Disadvantages of DDA

1. We have to use round function for each point. Therefore the number of computations are increased 

