  Hello!
  This is my first bigger project in C++.
It shows my style of writting a code in most programming languages similar to C. (like Java)
I descripted a problem that this program is showing/solving below.
                                                        Have a nice time reading the code, 
                                                                                   Agooon.

// Here is my explanation of the program, and the problem that needs solving.
/*
	dostL - amount of suppliers | fabL - amount of fabrics
	magL - amount of warehouses | sklL - amount of shops
	xd - matrix of amount of raw materials transporting from supplier X to fabric Y
	xf - matrix of amount of products that are created and transported from fabric X to warehouse Y
	xm - matrix of amount of products that are stored and transported from warehouse X to shop Y
	
	cd - cost of buying and transportingvraw materials from supplier X to fabric Y
	cf - cost of creating and transporting products from fabric X to warehouse Y
	cm - cost of storing and transporting products from warehouse X to shop Y
*/

/*
		An objective of this program is to solve the problem with 4 main variables:
	Suppliers, fabrics, warehouses and shops.
	And we have 3 matrix: xd/xf/xm, which combined are going to be our solution.
	
		Our goal is to balance the values in each of the matrixes to get the best solution, 
	which is measured by function dGetQuality(std::vector pdSolution) in the class of CProblem.


		So now, whats the conditions, that our optimizers and dGetQuality() need to have "in mind"?
	1) The length of the solution should be: (4 + (dostL*fabL) + (fabL*magL) + (magL*sklL))
			(+4 becous of basic values that are put in front: dostL|fabL|magL|sklL)
	2) For each value in xd/xf/xm matrixes there is a min/max limit, which is placed in matrixes xdminmax/xfminmax/xmminmax.
	3) There are arrays of processing capacity for each supplier/fabric/warehouse/shops.
	4) Suppliers/fabrics/warehouses have maintenance costs, so sometimes is better to shutdown one, then use it a little.
	5) Shops have a value price of final product, the income is just: amountOfSoldproducts*price. Each shop can have different price.
	5) There is a cost of transporting/creating/storing the raw materials/products, the cost of it is placed in matrixes cd/cf/cm.
	6) Ofcourse each fabric can't produce more than it gets raw minerals from suppliers and 
		warehouse can't transport to shop more than it gets products from fabrics.
	

	This program contains 2 main optimizers: CRandomSearch and CDiffEvol, and 2 simple ones: CMeanSolver and CTrivMethod.
	CRandomSearch - just gets a random value between minimum and maximum for each. 
		If the solution is better then actual solution, actual solution gets replaced by new one, 
		till the end of time.
	
	CDiffEvol - have 3 main variables: amountOfPopulation, crossProb, diffWeight. Each of these have
		big impact on algorythm efficiency. At the start population is an array of random solutions,
		and each solution is modified by each loop of the algorithm by being mixed with other solutions
		and if new solution is better then old one, there is a replacement. (more explonation in the code of algorithm)
		
		
*/
