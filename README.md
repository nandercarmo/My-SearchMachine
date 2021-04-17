# My-SearchMachine

This library was developed during the discipline of "Algorithms and Data Structures" at UFMG.  It aims to implement some of the main concepts of search and hashing algorithms and to simulate a search engine that, given a database or articles is able to tell if a list of terms received are present in those articles and in what quantity.

The file "search.txt" must contain a phrase or as words to be searched in the database. The file "files/stopword_file.txt" contains a list of words that should be disregarded when searching.

<p align="center">
  <img src="resources/gif.gif">
</p>

## Install

To test this library, just make a clone of this repo using the command below:

> git clone https://github.com/NanderSantos/My-SearchMachine.git

> cd search-machine

Finally run this command and everything will be done:

> make

Or use this magical one-liner command to make it easiest:

> git clone https://github.com/NanderSantos/My-SearchMachine.git && cd My-SearchMachine && make

## Run

To run the program just use the following command line below:

> ./MySearch search.txt

To see the results of other searches, just change the input words in the search.txt file

## Clear

To clear the project just use the following command line below:

> make clean
