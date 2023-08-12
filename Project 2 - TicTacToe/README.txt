Project 2: Tic-Tac-Toe
Purpose
To practice designing and implementing an algorithm
To practice evaluating algorithm efficiency
To practice with recursion or stacks or queues
Before You Begin
Read the sections below in their entirety.
Background
A standard Tic-Tac-Toe game is played between two players, 'X', and 'O', with the board shown below:

Tic tac toe board (see tictactoeboard.gif image)

Traditionally, here are the rules:

X goes first, and marks a position
Then, O chooses any empty position, and marks it.
X and O continue until either:
A player wins (by having 3 marks in a row)
The board is full, with no one winning
Finding the Number of Possible, Unique Boards
At first glance, it may seem easy to calculate the number of possible boards: after the first spot is taken by X, there are 8 locations for O to take; so there are 9 * 8 (72) different board configurations with 1 X and 1 O.

After a second move, there are 9 * 8 * 7 different board configurations, after the third, 9 * 8 * 7 * 6. After the 9th move, there are 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1 = 9!. Therefore, the total number of game boards (including the empty board) are:

1 + 9 + 9 * 8 + 9 * 8 * 7 + ... 9! = 986,410

However, there are a lot of duplicate boards. Consider the following moves, shown below, which result in the same board:

 X |   |       X | O |       X | O | X
---+---+---   ---+---+---   ---+---+---
   |   |         |   |         |   |   
---+---+---   ---+---+---   ---+---+---
   |   |         |   |         |   |   
   |   | X       | O | X     X | O | X
---+---+---   ---+---+---   ---+---+---
   |   |         |   |         |   |   
---+---+---   ---+---+---   ---+---+---
   |   |         |   |         |   |  
When all the duplicates are removed, there are 6,046 different boards left.

However, not all of these boards are possible. Since the game ends once a player wins, there are game boards that can not possibly exist. For instance, the board below can never exist, as the game would have stopped before both X and O could have won:

 X |   |      
---+---+---
 X | X | X     
---+---+---
 O | O | O
Your Program
You will write a program that generates every unique and valid tic-tac-toe board. There are fewer than 6,000 of these once you remove duplicates and unreachable boards! Additionally, you will keep track of the number of (unique & valid) boards where:

X wins
O wins
No one wins (a tie).
These should be output in this exact format:

total boards: nnn, wins for 'O': nnn, wins for 'X': nnn, ties: nnn
After that first line, the output from your program should be one line per board, where each line is a string representing the board using the following indexing scheme below:

 0 | 1 | 2    
---+---+---   
 3 | 4 | 5    
---+---+---  
 6 | 7 | 8   
For example, the string X O OX X represents the following board:

 X |   | O
---+---+---  
   | O | X    
---+---+---  
   | X |
Additionally, your program's output should be in sorted order.

...so if you're storing the strings representing the boards in a vector, you'll need to sort it before printing.
Keep in mind the following rules:

X goes first
The empty board is a valid board
The game stops when someone wins—no more moves are made.
Your program does not have to be fast, but it should run in less than a minute. With the right algorithm, it is possible to have it run in seconds.

The following is the first several boards (when printed in sorted order):


        X
       OX
       X
       XO
      O X
Write Up
In addition to submitting your code for this assignment, answer the following questions below in a single PDF file.

Explain your approach to solving this problem.
Justify why the output of your program is correct.
Consider the run time of your program; do you think your solution is efficient? Do you think it could be made more efficient?
Implementation Hints
What you are doing is effectively exploring the game tree of tic-tac-toe. One way of exploring the game tree, discussed in the lecture on recursion, is using backtracking. Take some time to think about what the recursive substructure of this problem is; how can you start with an empty board and generate all of the next moves, and where do you go from there?

We will very soon learn a little bit about graphs (and later, trees, which are a special type of graph), and talk more about some algorithms used on graphs, in the lecture on stacks and queues. If you are starting this project after the lecture on stacks and queues, then you might consider using breadth-first or depth-first search to explore the game tree. In this case, think about what you need to store in your stack or queue.

The requirements of the problem state that you must return unique boards, in sorted order. There are many ways to go about this, some of which you haven't learned yet (for example, we haven't yet learned about the set data structure, which is ideal for this problem). For now, I suggest you:

generate all of the boards, not worrying about duplicates
sort the boards
eliminate duplicates as a last step (hint, you might find a library function to help with this)
Grading
Item	Points
Code compiles and runs as submitted	5 points
Code style & quality	5 points
Eliminating duplicate boards	5 points
Eliminating boards unreachable due to a win	5 points
Correct # boards and wins	5 points
Correct output format and order	5 points
Writeup	25 points
README.txt	5 points
Total	60 points
Extra Credit	Up to 3 points
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
Your writeup, in .pdf format.
Extra Credit: Symmetry
Many boards are the same board because of symmetry. For example, the three boards below are the only truly unique boards for the first move.

 X |   |         | X |         |   |
---+---+---   ---+---+---   ---+---+---
   |   |         |   |         | X |   
---+---+---   ---+---+---   ---+---+---
   |   |         |   |         |   |   
All the other moves are symmetric* to one of these.

There are three rotational symmetries: rotating 90, 180, and 270 degrees.
 X | O |         | X | X       |   |         |   |     
---+---+---   ---+---+---   ---+---+---   ---+---+---  
 X |   |         |   | O       |   | X     O |   |     
---+---+---   ---+---+---   ---+---+---   ---+---+---  
   |   |         |   |         | O | X     X | X |    
There are four reflective symmetries: horizontal, vertical, left/right diagonal, and right/left diagonal.
 X | O |         |   |         | O | X     X | X |        |   |
---+---+---   ---+---+---   ---+---+---   ---+---+---  ---+---+---  
 X |   |       X |   |         |   | X     O |   |        |   | O
---+---+---   ---+---+---   ---+---+---   ---+---+---  ---+---+---  
   |   |       X | O |         |   |         |   |        | X | X

For extra credit, add an option for your program to not count symmetric boards as unique; i.e., prune all symmetries from your output. Make sure you provide a way for the grader to choose the regular solution or your extra credit solution!


Project README - 
	1. Author: Lauren Sherburne
	   Collaborators: Pierre Visconti, TA Jake LaLuna, TA Hannah Lee
	2. In my opinion, the biggest challenge that I faced while working on this project was coming up with a way to 
create the list of all possible tic tac toe boards. I knew from the start that recursion was one of the best options for
accomplishing this, but I needed help with the looping portion of the function. Another issue that was difficult to
overcome was sorting and eliminating duplicates within my data, however, I realized that I could use a set to accomplish
both of these challenges.
	3. Honestly, it was interesting to think about how many different tic tac toe boards there are possible. I enjoyed
how we used programming to calculate numbers and data that otherwise would be very difficult and time consuming to
consider. Also, I liked that we were able to use a set to simplify the process of sorting our data. However, I'm not sure
if it was just me, but I had a lot of trouble finding a starting point for this project. I would not have been able to come
up with the recursive function necessary for the solution without any help. If I had a better understanding of where to 
begin on this aspect of the project, perhaps I would not have needed to start my code over so many times.
	4. I spent approximately 9 or 10 hours on this project mostly because I had to ditch my code and start over several
times because I did not have the right idea for my recursive function.
