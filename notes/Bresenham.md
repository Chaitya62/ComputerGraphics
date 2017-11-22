# Bresenham's Algorithm

Also drived using `y= mx+c` like DDA but does not make use round function 

	
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

5. We use p(decision paramter) to decide the next value of x or y


6. for m < 1: p0 = 2dy - dx and pi+1 = pi + (2dy - 2dx((yi+1) - y(i)))

### For m < 1

#### Algorithm

1. Read two points 
2. Calculte dx, dy
	dx = x2-x1
	dy = y2-y1
3. Calculate intial decision paramter 
	pi = 2dy - dx 	
4. Initialize x = x1, y = y1
5. for i in 1 to dx
6. if pi >= 0:
	xi+1 = xi + 1
	yi+1 = yi + 1
7. if pi < 0:
	xi+1 = xi + 1
	yi+1 = yi 
8. putpixel(x, y)
9. pi = pi + (2dy - dx(yi+1 - yi)) 






