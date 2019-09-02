# ParodyTextMarkovChain
Fun summer project that reads in a text file and creates a Markov Chain structure for generating random text.

## 1. What is a Markov Chain?

A Markov Chain used for text generation is a graph like data structure where each node represents a word, while each directed edge between nodes represents the probability that the adjacent node's word is generated next.

More information here: https://en.wikipedia.org/wiki/Markov_chain

## 2. Markov Chain implementation.
The graph is built in several steps. First, the text file book.txt is scanned through once, and creates a binary search tree of all the unique words it encounters. On the second pass, it then tallies the occurances of words following other words, slowly building the graph with the probabilities on the edges.
Since the graph being generated from text would be very sparse, it made more sense to use an adjacency list rather than an adjacency matrix to prevent too much memory from being used.

The adjacency list comprised of a 2d array, with the row being the node, while the column contains a simple struct which contains the connected node, plus the probability of transitioning to that node.
Since a map (binary search tree) is used to keep track of each word's location in the matrix, the lookup is O(log(n)) instead of O(n) when trying to find the next node to transition to.

## 3. Use
To use this markov chain, simply clone or download the files to a folder. In this folder, include a file named `books.txt` for the program to learn from. Personally, I've found good results with longer books, and many books are available for free as a txt file on https://www.gutenberg.org/

Here is some example generated text from War and Peace (Leo Tolstoy):

>He imagined otherwise. To each action without wars. How can live." put it be studied side or how many forces, did six this way!" said to the planets, so long before a long been pleased her-that that mode of awe at laws." Nicholas never imagine that mode of small quantity, can exist, nor hearing this strange that a little girl. "Till now proceeding from the count paid his momentary undefinable essence of personality to induce her confinement is as exists is it?" they saw Denisov from destroying, even strengthens the planets, so history of personality to soil produce any conception of


Compile the files with `g++ -w *.cpp`

Run with `./a.out`
