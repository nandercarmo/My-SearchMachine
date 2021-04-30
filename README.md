#	🔍	My-SearchMachine

<div align="left">
    <img src="https://img.shields.io/badge/language-c-blue">
    <img src="https://img.shields.io/badge/compiler-gcc-brightgreen">
    <img src="https://img.shields.io/badge/build-makefile-green">
    <img src="https://img.shields.io/badge/license-MIT-blueviolet">
</div>

---

This library was developed during the discipline of **"Algorithms and Data Structures"** at **UFMG**.  It aims to implement some of the main concepts of search and hashing algorithms and to simulate a search engine that, given a database or articles is able to tell if a list of terms received are present in those articles and in what quantity.

The file **"search.txt"** must contain a phrase or as words to be searched in the database. The file **"files/stopword_file.txt"** contains a list of words that should be disregarded when searching.

<p align="center">
  <img src="resources/gif.gif">
</p>

---

##	📦	Install

To test this library, just make a clone of this repo and build using the commands below:

```bash
$ git clone https://github.com/NanderSantos/My-SearchMachine.git

$ cd search-machine

$ make
```

Or use this magical one-liner command to make it easiest:

```bash
$ git clone https://github.com/NanderSantos/My-SearchMachine.git && cd My-SearchMachine && make
```

---

##	🏃	Run 
To run the program just use the following command line below:

```bash
$ ./MySearch search.txt
```

To see the results of other searches, just change the input words in the ***"search.txt"*** file

---

##	🗑️	Clear

To clear the project just use the following command line below:

```bash
$ make clean
```
