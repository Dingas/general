% Enter the names of your group members below.
% If you only have 2 group members, leave the last space blank
%
%%%%%
%%%%% NAME: Kelvin Gu
%%%%% NAME: Brandon Aboukhater
%%%%% NAME: Derek Eliopoulos
%
% Add the required rules in the corresponding sections. 
% If you put the rules in the wrong sections, you will lose marks.
%
% You may add additional comments as you choose but DO NOT MODIFY the comment lines below
%

%%%%% SECTION: cost
% Put your atomic statements for the cost in this section
cost(laptop, 600). cost(monitor, 300). cost(keyboard, 100).

%%%%% SECTION: numPurchased
% Put your atomic statements for the numPurchased predicate in this section
numPurchased(laptop, 2). numPurchased(monitor, 1). numPurchased(keyboard, 3).

%%%%% SECTION: shippingCost
% Put your atomic statements for the shippingCost predicate in this section
shippingCost(laptop, 35). shippingCost(monitor, 35). shippingCost(keyboard, 10).

%%%% SECTION: taxRate
% Put your atomic statements for the taxRate predicate in this section
taxRate(0.13).

%%%%% SECTION: freeRegularShippingMin
% Put your atomic statements for the freeRegularShippingMin predicate in this section
freeRegularShippingMin(1000).

%%%%% SECTION: freeExpressShippingMin
% Put your atomic statements for the freeExpressShippingMin predicate in this section
freeExpressShippingMin(2000).

%%%%% SECTION: subtotal
% Put your rules for the subtotal predicate in this section
subtotal(Sub) :- cost(laptop, LaptopCost), cost(monitor, MonitorCost), cost(keyboard, KeyboardCost), numPurchased(laptop, LaptopNum), numPurchased(monitor, MonitorNum), numPurchased(keyboard, KeyboardNum), Sub is LaptopCost * LaptopNum + MonitorCost * MonitorNum + KeyboardCost * KeyboardNum.

%%%%% SECTION: calculateBaseShipping
% Put your rules for the calculateBaseShipping predicate in this section
calculateBaseShipping(ShippingCost) :- shippingCost(laptop, LaptopCost), shippingCost(monitor, MonitorCost), shippingCost(keyboard, KeyboardCost), numPurchased(laptop, LaptopNum), numPurchased(monitor, MonitorNum), numPurchased(keyboard, KeyboardNum), ShippingCost is LaptopCost * LaptopNum + MonitorCost * MonitorNum + KeyboardCost * KeyboardNum.

%%%%% SECTION: calculateShipping
% Put your rules for the calculateShipping predicate in this section
calculateShipping(regular, ShippingCost) :- subtotal(Sub), freeRegularShippingMin(FreeShippingMin), Sub >= FreeShippingMin, ShippingCost is 0.
calculateShipping(regular, ShippingCost) :- subtotal(Sub), freeRegularShippingMin(FreeShippingMin), Sub < FreeShippingMin, calculateBaseShipping(ShippingCost).
calculateShipping(express, ShippingCost) :- subtotal(Sub), freeExpressShippingMin(FreeShippingMin), Sub >= FreeShippingMin, ShippingCost is 0.
calculateShipping(express, ShippingCost) :- subtotal(Sub), freeExpressShippingMin(FreeShippingMin), Sub < FreeShippingMin, calculateBaseShipping(Base), ShippingCost is Base * 1.5.

%%%%% SECTION: totalCost
% Put your rules for the totalCost predicate in this section
totalCost(ShippingType, Cost) :- subtotal(Sub), calculateShipping(ShippingType, ShippingCost), taxRate(Rate), Cost is (Sub + ShippingCost) * (1 + Rate).

