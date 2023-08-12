Project 4: Animal (20 Questions)
Purpose
Practice implementing and working with binary trees
Practice with recursion

(Optional) animal.cpp: Provides a rudimentary UI for the project.
Introduction
In this project, you will implement the game 20 questions. Here are the rules of the game:

One person selects a specific "thing"
The other person tries to guess that "thing" by asking yes/no questions.
In our version of the game, we will assume the "thing" is always some type of animal (e.g. "Zebra"), but it can easily be extended to cover other types of "things".

In this assignment, you will try to guess the user's selected secret using a binary decision tree. Every node represents a question, and the user's yes or no answer determines which child to transition to.

Below is a game tree for a simple game of "animal" 20 questions:

20 questions treeFigure 1: Example Game Tree (see treeFigure1.png)

The decision tree's setup is as follows:

A yes answer always goes left (blue arrows), while a no always goes to the right (red arrows).
The leaves of the tree are the terminal guesses. They should represent a guess of a specific type of animal.
The internal nodes are more general, and are designed to separate large categories of animals in order to narrow down the potential list.
All internal nodes have two children: one for yes, and one for no. This type of tree is called a full binary tree.
In this assignment, you will implement a learning version of 20 questions. Not only does the it play the game, but it learns when it loses. Additionally, you'll be able to save your learned tree to disk, so you can pick up where you left off.

Outline
There are four principal parts to this assignment.

Part 1: Reading the Game Tree
The first thing your program needs to do is read in an existing game tree. The following file format will be used in this project:

Each node is stored on a separate line, in a pre-order format.
This means the order is root, left subtree, right subtree.
Note the recursive format!
Internal nodes ("questions") begin with #Q , while leaves ("answers") begin with #A .
Below is the example tree file corresponding to Figure 1 above:

#Q Is it a mammal?
#Q Does it have stripes?
#A Is it a zebra?
#A Is it a lion?
#Q Is it a bird?
#Q Does it fly?
#A Is it an eagle?
#A Is it a penguin?
#A Is it a gila monster?
While you can technically leave the tree in this pre-order format, the rest of the project will be significantly easier if you work with the binary tree implementation we discussed in class.

You do NOT have to verify the file given is a proper file, just assume it is.

Part 2: Playing the Game
You will create a UI and the logic required to play the game of 20 questions. Here's the rundown:

After the user indicates they wish to start the game, display the first question, and prompt with a yes/no input
The first question is the one stored in the root of the tree
If the user answers yes, your program should ask the question stored in the left child node
If the user answers no, your program should ask the question stored in the right child node
You will need to maintain a pointer to the current node, and move it appropriately.

When the question is a leaf, a yes should result in a self-congratulatory "I win" message.
Otherwise, the game should indicate that it is out of questions and has lost the game. At this point the game should also prompt for an extension of the game tree (see part 3 below).
Here's a run through of a successful game:

Welcome to 20 questions!
1) Play the game
2) Save the game file
3) Quit
Please make your selection: 1
Is it a mammal? (y/n): n
Is it a bird? (y/n): y
Does it fly? (y/n): n
Is it a penguin? (y/n): y
YAY! I guessed your animal!
Part 3: Extending the Game Tree
When the game fails to guess the user's animal, the game should "learn" from this mistake (if the user chooses to let it.)

Prompt the user if they want to expand the game tree
If no, simply return to the main menu.
If yes:
Print out what questions you asked, along with the user's answers
Prompt the user to enter two new questions
The first question is the one which would have caused the game to win. E.g. "Is it a platypus?"
The second question distinguishes the new animal from the old animal. E.g. "Does it lay eggs?"
After expanding the game tree, return to the main menu.
Here's an example run through:

Welcome to 20 questions!
  1) Play the game
  2) Save the game file
  3) Quit
Please make your selection: 1
Is it a mammal? (y/n): y
Does it have stripes? (y/n): n
Is it a lion? (y/n): n
BOO! I don't know!

Would you like to expand the game tree (y/n)? y

I asked the following:
Is it a mammal? YES
Does it have stripes? NO
Is it a lion? NO

Enter a new animal in the form of a question,
e.g., 'Is it a whale?':
Is it a platypus?
Now enter a question for which the answer is 'yes' for your new
animal, and which does not contradict your previous answers:
Does it lay eggs?
When the new questions are entered, the game needs to modify the game tree.

The question asked in part 2b) replaces the old leaf
Using the example above, "Is it a lion?" gets replaced with "Does it lay eggs?"
The old leaf, and the question asked in 2a) both are added as new nodes
"Is it a lion?" and "Is it a platypus?" are the two new nodes, using the example above.
Once the tree is updated, show the main menu.

Part 4: Writing the Game Tree
This is simply the reverse of reading in the game tree. To write out the game tree, simply do a pre-order traversal of the binary tree, and print out the tree in the proper format.

Remember to follow the file format guidelines given Part 1 — your program must produce a file that follows the conventions given in this project.

Put another way, your program must be able to read in and parse game files which it writes.
Implementation Hints
You can implement this project however, you want, but here are some hints:

Storing the Game Tree
Keep a pointer to your root node in main. Pass the pointer to all other functions.
Every node in the tree needs two pieces of information: The question it represents, and whether or not it's a leaf. You can keep track of this in a couple ways:
Create a class or struct to explicitly mark whether it's a leaf or not
Implicitly know that it's a leaf from the fact that all leaves have two nullptr children.
Reading the Game Tree
Use recursion.

Have two functions:

node* read_game_tree();

node* read_preorder(ifstream& fin);
Use read_game_tree() to setup the recursive call by opening an ifstream to the game tree file. Then pass the open ifstream to your read_preorder() function.

Inside of read_preorder(), you'll want to use getline() to pull the entire line and parse it into the tree->data. Then, check if the line started with #Q , if so, then make a recursive call to obtain tree->left and tree->right. If not, then this is the base case of your recursion — return (be sure to terminate your tree by setting the child nodes to nullptr!).

Make sure to close your input stream once read_preorder() is finished!

Writing the Game Tree
Just like reading the tree, make a recursive function that takes an ofstream and a node pointer. Write the file using a pre-order traversal, following the proper format.

Close the stream after writing!

Playing the Game
Use a node pointer to keep track of the current question. When not on a leaf node, you'll set this pointer to the left child when the user answers yes, and to the right child when the user answers no.

Do NOT print out #Q  and #A  when asking the questions! These either need to be removed from the question when reading the tree (and then re-added when writing), or simply not shown to the user through some other method.
Use a queue to record a history of the questions asked and the user's answers. You'll need this when prompting the user for a question to expand the game tree with.

You can just record the history of the user's answers, then reconstruct the path from the root pointer based on those answers.
Extra Credit Ideas
If you're interested receiving some extra credit on this project, try some of these optional extensions!

1: Print the tree file in the DOT format
DOT is a specific file format that can be used to easily visualize complex graphs (or in our case, trees). While the full spec for DOT is quite complicated, it's fairly straightforward to write a basic .gv file by following the follow steps:

The first line of the file should always be digraph G { (digraph is short for "directed graph", i.e. all edges have arrows)
Nodes should be listed one per line, in the format of "parent" -> {"left child" "right child"};
The last line of the file should always be }
Below is the example tree file corresponding to original game tree:

digraph G {
	"Is it a mammal?" -> {"Does it have stripes?" "Is it a bird?"};
	"Does it have stripes?" -> {"Is it a zebra?" "Is it a lion?"};
	"Is it a bird?" -> {"Does it fly?" "Is it a gila monster?"};
	"Does it fly?" -> {"Is it an eagle?" "Is it a penguin?"};
}
The reason you should this format is that it makes visualizing the game tree quite easy: you can go to this website, paste in the tree file, and it will draw the game tree for you! The figure below shows the output for the example file.

Example tree file, drawn with graphvizFigure 2: Animal Tree, drawn with GraphViz (see treeFigure2.png)

If you choose to do this option, make sure to implement this in a separate function than the write in part 4. By writing in this format, your read_preorder() function will no longer be able to parse the tree, so the original write_preorder() should still be there.

2. Make a larger / new game tree.
The game tree we provide for you is quite small, in fact there's only a max of 3 internal nodes! You could extend this in neat ways, such as:

Creating an entirely new game tree, one centered around a different type of "thing" (e.g. Marvel movies, genres of books, types of rocks, etc.)
Expanding the current game tree significantly by adding new / different types of animals.
The world is your oyster here, so be as creative as you want!

Grading
Item	Points
Program compiles and executes	5 points
README.txt	5 points
Code quality and style	5 points
Parts 1 and 2 (Reading & playing the game)	20 points
Part 3 (Expanding the game tree)	20 points
Part 4 (Saving)	10 points
Total	65 Points
Extra Credit: Innovations of your own design	Up to 3 points
README.txt
Include YOUR NAME and the names of all people who helped/collaborated as per the syllabus.
Describe the challenges you encountered and how you surmounted them.
What did you like/dislike about the assignment?
How long did you spend working on this assignment?
A description of any novel features you added for extra credit (if any)
Submission Instructions
Submit a zip file on Canvas containing:

README.txt
All .h and .cpp files.
Full Run Through
Below is an example highlighting the full functionality of the project.

Welcome to 20 questions!
  1) Play the game
  2) Save the game file
  3) Quit
Please make your selection: 1
Is it a mammal? [y/n]: n
Is it a bird? [y/n]: n
Is it a gila monster? [y/n]: n
BOO! I don't know!

Would you like to expand the game tree? [y/n]: y
I asked the following:
Is it a mammal? n
Is it a bird? n
Is it a gila monster? n
Enter a new animal in the form of question (e.g. is it a platypus?): Is it a shark?
Now enter a question for which the answer is 'yes' for your new animal, and which does not contradict your previous answers: Does it swim?

Welcome to 20 questions!
  1) Play the game
  2) Save the game file
  3) Quit
Please make your selection: 1
Is it a mammal? [y/n]: n
Is it a bird? [y/n]: n
Does it swim? [y/n]: y
Is it a shark? [y/n]: y
YAY! I guessed your animal!

Welcome to 20 questions!
  1) Play the game
  2) Save the game file
  3) Quit
Please make your selection: 2
Game file saved in 'animal.txt'

Welcome to 20 questions!
  1) Play the game
  2) Save the game file
  3) Quit
Please make your selection: 3



Project README - 
	1. Lauren Sherburne (no collaborators)
	2. Challenges: Unfortunately, when I was writing the function used to read in the data for the binary tree, I made
a minor mistake that caused a lot of trouble because while I was debugging, I was under the impression that I had a major
logic issue. I spent a lot of time reworking the function to create the binary several times before realizing that I failed
to initialize the new node. This was an easy fix once I realized. Another challenge that I had to overcome was how to add
new questions and answers to my binary tree. I overcame this by using a whiteboard to help visualize the logic. The rest of
the project was not too difficult to write.
My only big problems occurred when I made little writing errors in the code, but none were too drastic.
	3. Like: I thoroughly enjoyed creating this game because now I have a basic format that I can alter in slight ways
to personalize it. Additionally, the functions and content required in this project really helped my understanding of 
binary trees and how to work with them.
	   Dislike: To be completely honest, I cannot think of anything that I dislike about this project because it was
very enjoyable to code and I believe that I learned a lot in the process and was able to reinforce the content from
lecture.
	4. Time Estimate: 16 hours
	5. Extra Credit: print the tree file in DOT format
