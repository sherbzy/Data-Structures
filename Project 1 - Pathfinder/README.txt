Project 1: Pathfinder
Purpose
To review basic C++ syntax: loops, if/else statements, functions, classes, and file I/O
To practice with simple linear and 2-D structures (e.g., vectors and vectors of vectors)
To make a cool graphical application of pathfinding on graphs
Before You Begin
Read the sections in their entirety before you start programming!
Download the starter source code and data files for this project
The project files include a CMakeLists.txt, so you should be able to just open the downloaded directory from CLion
As soon as CLion creates the cmake-build-debug directory, you should move the data subdirectory into cmake-build-debug so they are where your program will look for them (or you can change the working directory in CLion).
Do a test build/run of the code - it should compile as is, but will do nothing other than produce a simple gray shaded image
Introduction
In this lab you will read a set of topographic (land elevation) data into a 2D array and write some methods to compute some paths through the mountains as well as visualize them.

Background
There are many contexts in which you want to know the most efficient way to travel over land. When traveling through mountains (let's say you're walking) perhaps you want to take the route that requires the least total sum of changes in elevation – call it the path of least resistance. Given some topographic data it should be possible to calculate a "lowest-elevation-change walk" from one side of a map to the other.

Pathfinding on Graphs
Maps of various kinds are often represented as graphs, a type of data structure we'll study later in the semester. Essentially, each location on the map is represented by a vertex of the graph, while the paths between locations are represented by an edge, usually weighted by some measure of cost to travel the edge, such as distance. A road map, showing cities and the distances of each segment of road, is an example of such a graph.

A key problem on graphs of this type is to find the shortest or minimum-weight path between vertices (locations) on the graph. A brute-force attempt to try every possible path will fail on graphs of any significant size, as the number of possible paths grows exponentially with the size of the graph. Many efficient algorithms exist to compute shortest paths, including Dijkstra's algorithm, the Bellman-Ford algorithm, and the Floyd-Warshall algorithm. You will study some of these, along with many other graph algorithms, in CSCI 406 (Algorithms).

The pathfinding problem is greatly simplified if your graph is a directed acyclic graph, or DAG. A DAG is essentially characterized by the fact that you can never return to a place previously visited by following one-way directed edges on the graph. We are going to work with a map which is a 2D grid, and treat it as a DAG by enforcing a simple rule: every move has to take you at least one step east.

Topographical Maps
We will be working with elevation data culled from various online sources (usually satellite data). Our maps will consist of discretized 2D grids of elevations, where each point in the grid represents some roughly square area of the Earth's surface. (The size of the cells varies depending on the resolution of the map.) Our goal is to "walk" from west to east on the given map, while accumulating the least total amount of elevation change. We are allowed to start on any of the west-most grid locations, and end on any of the reachable east-most grid locations. For a given starting point, in one move we can step into one of three nearby points: the one directly east, the one directly northeast, or the one directly southeast.

Consider the example elevation data below, with an optimal path (green) and a not-so-optimal path (red).

A small map (see image smallmap.png inside "Instructional Images" folder)

By adding the absolute value of the differences in elevation between each point on the walk, we see that the optimal path has a total cost of 6 (|100 - 101| + |101 - 99| + |99 - 98| + |98 - 96|), while the less optimal path has a total cost of 14.

Dynamic Programming
Dynamic programming is an optimization technique that you will learn more about in CSCI 406. (The word "programming" in the name actually has nothing to do with computer programming.) Like many algorithmic techniques, dynamic programming breaks large problems into smaller subproblems; the trick with dynamic programming is to reduce the complexity of the task when subproblems need to be reused many times by solving the subproblem exactly once, storing the answer for quick retrieval on subsequent uses.

For our problem, dynamic programming comes into play because each starting point on the map can yield many, many paths which end up going through the same points later on. If we use a brute-force approach, we will end up computing the remaining cost of paths from those later points over and over again. If we instead apply dynamic programming, we can compute the minimum cost at each point exactly once!

The way we do this is to work the problem backwards in the sense that we will compute the cost of the end portions of paths before calculating the paths that lead to them. The algorithm can be illustrated by looking again at our example elevation data above:

Elevation data (see image elevationdata1.png inside "Instructional Images" folder)

To start, note that when we are on the east-most squares, our journey is done, so by definition there is no more cost to accumulate. Thus, we make a record noting that the total cost to travel east from one of the east-most cells is zero. We make this record in a second table:

Elevation and 1-step cost data (see image elevationdata2.png inside "Instructional Images" folder)

Now, consider each cell in the second-from-the-right column. We can move from each of those cells into the cell directly east, the cell directly northeast (if such cell exists), or the cell directly southeast (if such cell exists). Wherever we move to, we will still have the cost in that cell to pay to complete our journey. So for instance, in the top cell of the second-from-the-right column, we can go:

directly east for a cost of |63 - 66| + 0 = 3
southeast for a cost of |63 - 70| + 0 = 7
The better cost is 3, so we fill in a 3 for that cell:

Elevation and 2-step cost data (see image elevationdata3.png inside "Instructional Images" folder)

Similarly, for the next cell down, we can go:

east, for cost |75 - 70| + 0 = 5
southeast, for cost |75 - 93| + 0 = 18
northeast, for cost |75 - 66| + 0 = 9
Elevation and 2-step cost data (see image elevationdata4.png inside "Instructional Images" folder)

We can fill in the rest of the column:

Elevation and 2-step cost data (see image elevationdata5.png inside "Instructional Images" folder)

However, this only tells us the minimum cost to travel one step - we didn't actually record how to obtain the minimum cost! So we need to make yet another record of the optimal direction of travel from each cell, each time we calculate the optimal cost. Here's what that looks like with our data so far:

Elevation and 2-step cost data with directions (see image elevationdata6.png inside "Instructional Images" folder)

Here we indicate travel with arrows, but as arrows are difficult to draw in code, you might consider another table of char values, where 'e' means east, 'n' means northeast, and 's' means southeast.

Here's the final solution - we can see that our best path is, in fact, the path with total cost 6 we showed above:

Elevation and cost data complete (see image elevationdata7.png inside "Instructional Images" folder)

File Format
The files we are working with are very simple. Take a look, for instance, at data/colorado.dat. There are two lines at the top of each file, of the form

    ncols  844
    nrows  480
giving the number of columns and rows of data. The rest of the file is just integers separated by whitespace:

   2564   2559   2504   2496   2485   2499   2537   2483   2475   2480   2518   2532   2480 ...
The data are in what is called row-major order; the first number is the row 0 and column 0; the second number is row 0 and column 1, etc. That is, you fill in your grid one row at a time.

Instructions
The minimum requirements for the assignment are that you write code to produce something like the map shown in the picture below (using the colorado.dat data). To do that you need to complete the following 6 steps (more detail below):

Read the data into a 2D data structure
Find the min and max elevations in the data
Draw the map using grayscale intensities to represent relative elevations
Compute a costs table and accompanying directions table describing the costs and lowest-elevation-change paths going to the eastern edge of the map starting from every point in the map
Draw the optimal paths starting from each of the western-most points on the map, in the color of your choice (blue in the example below)
Find and draw the best of the optimal paths in another color of your choice (yellow below)
A solution to the problem (see optimalsolution.png inside "Instructional Images" folder)

Implementation Details
Take a look at the provided starter code. You can (and probably should) ignore picture.* and lodepng.* - this is the same code (provided by our textbook author) that we used in lab 2 to create PNG images. Also, main.cpp just provides the simplest of user interfaces, and leaves most of the work to the pathfinder class. Your job is to fill in the details of the pathfinder class by editing pathfinder.h and pathfinder.cpp.

This is a big task! We've provided TODO comments in the code suggesting what to do in each method, and you have the algorithm description above. Below are some more implementation hints you should consider:

Step 1: Reading in the data
You've already practiced the necessary file I/O in lab 1 for getting the data out of the file. The data files here are pretty simple - other than a couple of strings at the top, everything in the file is just an integer value.

A decision you need to make is where to store the data. A good choice here is a vector<vector<int>>, which makes a good, simple, and efficient 2D grid. Your structure (whatever you decide) should be stored as a member variable of the pathfinder class, so you will have access to it from all the different methods.

There are a couple of options you have if you go the vector<vector<int>> route. If you simply declare the vector<vector<int>> as a member variable, it will initially be of size zero (that is, 0 x 0). You can do one of two things with this:

You can replace the initial vector with a vector<vector<int>> sized exactly to the dimensions of the map. For instance, the code below sets up a vector<vector<int>> with r rows and c columns:

 vector<vector<int>> foo;                       // initially zero size
 foo = vector<vector<int>>(r, vector<int>(c));  // now foo is r x c
The second line here is using the vector constructors in a way you may not have seen before - essentially we are constructing an anonymous vector<vector<int>> object and assigning it to foo (in place of the initial vector). You can now set or get the ith row and jth column of your data using the [] operator: foo[i][j].

The second option is to build the vector<vector<int>> up, one row and column at a time. This is a bit tricky to get right, but essentially you need to create each row, one at a time, as an empty vector<int>, using push_back() to fill in the row. Then you can push_back() the row vector into your overall (initially empty) vector<vector<int>>. Once all of your data is in the structure, you can again access the data using the [] operator: foo[i][j].

Recommended: test as you go! Use a small file (like the example data above - in your data directory as example.dat) and run your code on it, then use cout statements to make sure the data you have matches what is in your file.

Step 2: Finding min and max elevations
Not much to say about this, except that you should again use cout to make sure your values make sense. All elevations in the files are expressed in meters above/below sea-level.

Step 3: Draw the map
The only trick here is deciding the gray level for a given elevation. This should be done proportionally, relative to the max/min elevations. You have a total of 256 possible levels of gray (0 - 255), but you may have a much smaller or bigger spread of elevations. Your highest elevations should use gray value 255, your lowest value 0. Use math.

Once you have the gray value for a given pixel, use the set() method of the Picture object (there is already a declaration for a Picture variable named _image in pathfinder.h) to draw the pixel. Note that set() takes in RGB values - for gray, set all three to the gray level you want:

    int gray = <your math here>
    _image.set(x, y, gray, gray, gray);
Once you have the _draw_map() method of pathfinder working, you should see a grayscale map like the one above (minus the blue and yellow lines) when you build and execute your program.

Note: Your program will run much faster if you do one small thing: before you start drawing, draw a pixel at the lower right corner of the image - this will force the image library to pre-allocate all the memory it needs at once, instead of in bits and pieces:

    _image.set(_width - 1, _height - 1, 0, 0, 0);
Step 4: Compute costs and directions for optimal paths
Steps 4 - 6 should all be done by the _draw_paths() method of pathfinder (unless you modify the code, which you are welcome to do). It is strongly recommended that you add additional helper methods to break up the work in _draw_paths(), but the choice is up to you.

Here you get to apply the dynamic programming algorithm described above to determine optimal paths from the western edge of the map to the eastern edge. You will likely want two additional vector<vector<>> data structures to keep track of your costs and directions tables.

Start by setting the rightmost column of your costs table to zero. (The rightmost column of your directions table doesn't matter.) Then start from the next-to-the-last column and apply the dynamic programming algorithm cell-by-cell:

Assume you will go east, and calculate the cost to go east as the absolute value of the elevation difference going east, plus the optimal cost stored in the cell to the "east".
If you can go north-east (remember that will be in the negative y-direction), calculate the cost as the absolute value of the elevation difference going northeast, plus the optimal cost stored in the cell to the northeast. If this is better than going east, update your cost and direction for this cell.
If you can go south-east, calculate that cost and update your cost and direction if better.
When you are done, you should (again) test your result by printing out or examining some of the values in your tables to see that they make sense. Use a small map!

Step 5: Draw optimal paths
Once you've created your costs and directions tables, use the directions table to draw every optimal path that starts at the western edge. Use blue or the color of your choice - blue has a red value of 0, a green value of 0 and a blue value of 255.

The trick here is to loop over x, incrementing each step, but update y on each step based on the direction stored in your directions table.

Step 6: Draw best optimal path
Find the best of the optimal paths by simply looking at the left-most column in your costs table to find the lowest cost starting point. Then repeat the work in step 5 to draw just this one path in a different color of your choice (yellow is r = 255, g = 255, b = 0).

Extra Credit
This is somewhat open ended. Basically, do something cool that goes beyond the basic requirements of the project. Some ideas:

Compare against a different algorithm. The algorithm we used is optimal and hard to beat, but it may not be immediately intuitive. A greedy algorithm is another option, and lets you compute just one path at a time; in the greedy approach, you simply make the best move available in the moment, without any kind of global knowledge. For instance, from a given start position, you might move to the (eastward) position that has the least immediate elevation change. Is this approach optimal? If not, how much worse is it?
Another approach you could try is a Monte-Carlo method. There are many approaches that fall under this umbrella. One relatively simple approach is to simply try lots and lots of paths, choosing moves randomly - this is expensive, and far from optimal (although with enough tries, you'll eventually find the right path!) A more sophisticated approach would be to do a number of tries, following a mostly greedy strategy - in this approach, on every move you would generate a random number. If the random number falls below your specified probability threshold, you would try a random choice; otherwise, you would use the greedy choice. This means you are trying for some kind of optimality, but allowing for exploration of all options.
Implement east-west, north-south, and south-north pathfinding (with some kind of menu option in main() to let us select the direction of travel).
Do a drawing of the mountain in colors other than a monochromatic scale. This would give you more than 256 shades of color to work with. For example, what if you shaded the lower elevations green (for lush valleys) and the highest elevations some sort of rock color brown/tan? To do this arithmetically you need to look up how to 'interpolate' colors.

Grading
Item	Points
Program compiles and executes	5 points
README.txt	5 points
Code quality and style	5 points
Display the topographical map	25 points
Compute and display optimal paths	25 points
Compute and display best optimal path	10 points
Total	75 Points
Extra Credit:	Up to 5 points (grader's discretion)
README.txt
Include YOUR NAME and the names of all people who helped/collaborated as per the syllabus.
Describe the challenges you encountered and how you surmounted them.
What did you like/dislike about the assignment?
How long did you spend working on this assignment?
A description of any features you added for extra credit (if any)

Submission Instructions
Submit a zip file on Canvas containing:

README.txt
Your .h and .cpp files.
Addendum: Styling
For styling, we are mostly looking for consistency and clarity. Some things to be aware of:

Have good naming of variables
Be consistent with how you use braces
Do not leave //TODO comments
Commenting not required, but if you have comments ensure that they are professional
Consistent indenting
Credits
This project is based on the Mountain Paths assignment by Baker Franke of Code.org and University of Chicago Laboratory Schools.


Project README - 
	1. Name: Lauren Sherburne, I worked alone with the exception of using TA and professor input at certain points on
this project.
	2. Challenges: One of the biggest challenges that I faced while working on this project was attempting to visualize
the cost and direction tables. I had a lot of trouble understanding the relationship between the tables that I was supposed
to create and the data given. Also, it was very difficult to understand that while North on the picture was up and South
was down as per usual on a map, East and West were switched. Initially when I went to write the code to create the cost and
direction tables, I had my directions mixed up and my values were incorrect because of my confusion about the instructions.
This caused many problems down the road when I attempted to draw the pathways on the map.
	3. Like: I really enjoyed the fact that we began with starter code because it gave me good practice reading someone
else's code and understanding the goal and how it works. Also, the outcome of our project was really interesting and
rewarding when I finally finished.
	   Dislike: For a first project of the course, this was very difficult. Last semester, I spent maybe half the time
on each project than the amount that I spent on this project and I did not need to rely on office hours and getting a lot
of help to actually finish the assignment.
	4. Time working on assignment: I probably spent 12 hours working on this project simply because it was difficult to
understand the instructions and I had trouble visualizing how to work with and manage the data.
