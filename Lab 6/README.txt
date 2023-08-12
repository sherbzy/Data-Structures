Lab 6: Ancient Algorithms
Goals
Learn some new (old) algorithms
Practice implementing algorithms from descriptions
Appreciate the wisdom of the ancients!
Overview
According to Wikipedia, an algorithm is "an unambiguous specification of how to solve a class of problems". While we think of algorithms in connection with modern computer programming, in fact algorithms have been around for millenia. (The word "algorithm" itself comes from the name of a Persian scholar, Al-Kwharizmi, who lived roughly 780-850 C.E. His book on calculations using the Indian numerals - what we now call Arabic numerals - was translated into Latin in the 12th century, influencing European and world mathematics for all time.)

One of the more famous of ancient algorithms, still in use today, is Euclid's greatest common divisor (GCD) algorithm. You've played with that algorithm, more or less, if you did the ContinuedFractions APT. There are many other algorithms, however, which are either still in use today, or have been enormously influential along the way to modern algorithms. Below, we will explore four of these algorithms: Egyptian multiplication, the Babylonian method for finding square roots, the Sieve of Eratosthenes, and Archimedes' method for approximating pi.

Your task for this lab is to pick two of the described algorithms and implement them on the modern computer using C++. Of the four algorithms, Archimedes' approximation of pi is the least accessible, so I recommend it if you feel especially ambitious.

Instructions
Read through the sections on the different algorithms below, and choose two to implement. What you are expected to do for a given algorithm is detailed in the corresponding section. Your resulting program codes should be submitted on Canvas (you can do two separate programs, or one program with a user interface allowing us to select the algorithm to run).





Egyptian multiplication
Variants of this approach for multiplying two integers have been discovered and rediscovered by many cultures. It was used in the building of the pyramids, yet it is still useful today in the digital logic circuits used to multiply binary numbers. It has a wonderful connection, in fact, to the binary numbering system, in that its essential mechanism is the decomposition of one multiplicand into a sum of powers of two (effectively its binary representation).

The basic method (on paper) goes as follows: create two columns; write one multiplicand (preferably the smaller) at the top of the left column, and the other multiplicand at the top of the right column. You can now fill in the left column by dividing by two repeatedly until you get to 1. On each division, you discard any remainder (i.e., when dividing an odd number), so you only have integers in that column. Meanwhile, the right column is filled by doubling its numbers until you have the same count of numbers in the right column.

To complete the multiplication, strike out any rows in your table for which the left-hand number is even. Add up the remaining numbers in the right column to get the answer. For example, if we want to multiply 238 x 13, our table would look like:

13	238
6	476
3	952
1	1904
Crossing out the rows with even numbers in the left column leaves us with the sum 238 + 952 + 1904 = 3094.

Why does this work? If you look at the left-hand column in binary, you may get an intuition:

1101	238
110	476
11	952
1	1904
Each time, the right-most digit of the left-hand column tells us whether or not we are going to keep the corresponding power of 2 times the right-hand multiplicand in our final sum! Note that the only operations we really performed involved multiplying or dividing by 2, which are easily accomplished in the computer by shifting bits left or right.

If you choose to implement this algorithm, then your program should prompt the user for two (positive) integers to multiply. Display a representation of the two columns you generate, and the final answer. E.g., your program output might look like the following:

Please enter two positive integers: 13 238

13  238
 6  476
 3  952
 1 1904

Answer: 3094
To get your numbers to line up nicely in right-aligned columns, use setw: http://www.cplusplus.com/reference/iomanip/setw/.

The Babylonian Method
Also known as "Hero's method" after the Greek mathematician whose description of it survived to the modern era, the Babylonian method is an iterative approximation method for finding square roots. Iterative approximation algorithms can be used when closed-form solutions are not readily available, and work by repeated refinement of a solution towards the true value. These algorithms have many applications in scientific computing.

The Babylonian method is very simple. Given a number n and a guess at its square root x, we make the observation that if x is an overestimate of the square root of n, then n / x will be an underestimate of the square root. In contrast, if x is an underestimate of the square root of n then n / x will be an overestimate (convince yourself of this with a bit of algebra). From this, it is reasonable to expect that the average of x and n / x is a better estimate of the square root than we started with.

The Babylonian method proceeds, then, by updating x to be the average of x and n / x, repeating until the change in values is very small, or until a fixed number of iterations have occurred. The value x will converge on the true square root.

For this algorithm, your program should prompt the user for a number to take the square root of (you should allow floating point or integer values) and an initial guess, and apply the Babylonian method, printing out each estimate of the square root until the change in estimates is less than 1e-8. (If you want to see more decimal places in your approximation, use the setprecision manipulator http://www.cplusplus.com/reference/iomanip/setprecision/. For example:

Enter a number: 7234
What is your guess? 1000
503.617
258.9905451
143.4610333
96.94293788
85.78207742
85.05602362
85.05292476
85.0529247
85.0529247
The Sieve of Eratosthenes
The Sieve of Eratosthenes is an ancient method for finding prime numbers. Prime numbers are crucial in many algorithms, particularly in cryptography, so methods for finding them are quite important; sieve methods descended from the Sieve of Eratosthenes are still used.

To apply the sieve, one must first specify a maximum number; the sieve will find all primes less than or equal to the specified number. On paper, the sieve is applied as follows:

Write down all numbers between 2 and the specified maximum
2 is the first prime. All numbers that are multiples of 2 are not prime by definition, so cross out every other number, starting with the second number after 2. Note that no math is being done - this is purely mechanical in that you cross out every other number rather than computing multiples of 2!
The next number that isn't crossed out (3) is the next prime - we know this, because if it were not prime, it would have been crossed out as a multiple of some previous prime. So proceed again by crossing out each 3rd number following 3 (be sure to not cross out 3).
Continue this procedure - pick the next number not crossed out, say n, and cross out every nth number until you reach the rightmost number.
The numbers which remain are the prime numbers from 2 to the specified maximum.
An illustration is shown below for finding all the prime numbers up to 120 (original source)

Sieve of Eratosthenes

This algorithm runs extremely fast if implemented correctly - but it is easy to make inefficient choices! The trick is to use a vector that is as large as the maximum number, and have the indices represent the number (you don't need to actually store the numbers). Each index of the vector only needs to contain an indicator of whether or not the number is still a prime candidate - so a vector of bool works fine.

Next, and this is important, do no divisions or modulo operations! Doing these is unnecessary and will kill your performance. Instead, for a given prime n, you only need to look at every nth index after n itself - change the value at the index to indicate that the number is not prime.

For reference, on my laptop, my implementation can find all primes up to 10,000,000 in just over 1 second.

For this algorithm, prompt the user for a maximum number, and print out a sequence of all the prime numbers less than the specified number, e.g.

Input a maximum number: 30

2 3 5 7 11 13 17 19 23 29
Archimedes' Approximation of Pi
Archimedes' method is easily explained, but working out the mathematics is a bit more complicated. It is another example of an iterative approximation algorithm.

The very short explanation of Archimedes' approach is that he starts by inscribing a regular hexagon inside a circle (touching the circle at all the vertices) and another regular hexagon outside the circle (so the circle is tangent to all of the sides of the hexagon); the area of the circle must then be between the areas of the two hexagons. (Try drawing this yourself and you should see what I mean.) Now, double the number of sides of each polygon to twelve - and do it again - and again... each time, the polygons get closer and closer to the actual circle.

Technically this approach will work with any polygons, but hexagons have some useful properties as a starting point, and Archimedes' ingenuity is really in how he works out the length of the sides and the apothems of the polygons after doubling the number of sides (an apothem is a line from the center of a regular polygon at right angles to any of its sides).

A nice video that helps illustrate the mathematics can be found here. Note that in this video, only the polygon inside the circle is used, and we only compute the perimeter of the polygon, which makes the math much easier even though the method is less accurate. However, with the power of a computer, it is possible to make a polygon with a very large number of sides indeed, thus approximating the circle even better than Archimedes' could using his method by hand. If you implement this algorithm, you should probably use this approach (all the important math occurs by about 6:30).

Note, a proper implementation of Archimedes' method should not use any trigonometric functions! You can do all of the math using nothing more complex than sqrt - hey, you could even use your solution to the Babylonian method, above!

Here's the math of the simplified approach:

Start with a regular hexagon inscribed inside a circle of radius 1.
Usefully, in a regular hexagon, the distance from the center to a vertex is the same as the length of a side - which means, if the hexagon is inscribed in a circle of radius 1, the length of any side of the hexagon is also 1.
Since, by definition, the circumference of the circle is 
2
 
 
2πr, and our approximation is the regular hexagon with a perimeter of 
6
∗
1
=
6
6∗1=6, our first approximation to 
 
π must be 
6
/
2
 
=
3
6/2r=3.
Compute the apothem
The apothem makes a right angle with a side by bisecting it, and we know the side has length 1, therefore we have a right triangle with a short side = 1/2, and a hypotenuse of 1. Hexagon inside a circle
By Pythagoras, then, our apothem is 
1
2
−
(
1
2
)
2
√
​1
​2
​​ −(
​2
​
​1
​​ )
​2
​​ 
​
​​ .
More generally, as we increase the number of sides, the apothem will be equal to 
1
2
−
(
 
 
 
 
 
 
 
 
 
ℎ
2
)
2
√
​1
​2
​​ −(
​2
​
​sidelength
​​ )
​2
​​ 
​
​​ , or just 
1
−
(
 
 
 
 
 
 
 
 
 
ℎ
)
2
/
4
√
​1−(sidelength)
​2
​​ /4
​
​​ .
Double the number of sides and compute the new side length
Note the red triangle on the diagram, which is also a right triangle: Archimedes' method in action
It turns out, we have all the information we need to calculate the sides of this new triangle - and the hypotenuse of the new triangle is the length of a side when we double the number of sides in our polygon.
The little short length is just the radius minus the apothem (and the radius is 1).
The longer, non-hypotenuse side is half of the old side length.
So the hypotenuse, the length of a new polygon side is just 
(
1
−
 
 
 
 
ℎ
 
 
)
2
+
(
 
 
 
 
 
 
 
 
 
ℎ
2
)
2
√
​(1−apothem)
​2
​​ +(
​2
​
​sidelength
​​ )
​2
​​ 
​
​​ .
Compute perimeter and estimate 
 
π
Finally, we can compute the perimeter of the new polygon - the new side length times the new number of sides.
Our new approximation of 
 
π is just the perimeter divided by the diameter.
Repeat steps 2 - 4 until some desired degree of accuracy.

If you choose this algorithm, then simply print out your successive approximations to pi until the change in values is very small (~1e-12); it is also interesting to print out the number of sides your polygon has at each step. You'll need to use the setprecision manipulator http://www.cplusplus.com/reference/iomanip/setprecision/ to see all your pi digits!

Here's the first few lines of output of my implementation:

Num sides: 6 -> pi: 3
Num sides: 12 -> pi: 3.10582854123025
Num sides: 24 -> pi: 3.13262861328124
Num sides: 48 -> pi: 3.13935020304687

Extra Credit Opportunity
If you're interested in earning some extra credit, implement more than two of the ancient algorithms! Each additional algorithm will be worth a point of extra credit.

Project README - 
Name: Lauren Sherburne (no collaborators)
Comments: I really enjoyed this lab! Working with the algorithms was very interesting and engaging and it was fun to 
	  see how to implement mathematical algorithms with code.
