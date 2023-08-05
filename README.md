# Data_Structures_TA
Designed this project as a Teacher Assistant for the Data Structures course.([Professor Hossein Esfandiari](https://scholar.google.com/citations?user=Rt8ppJsAAAAJ&hl=en))

# Project Details
In this project, students are given a number of restaurants along with their names and their distance (relative to the user) as input.  
In the next step, students will receive a number of queries, each query containing a string (S) and an integer (K).
Students should be able to use the data structure they learned in this course to search for restaurants that start with the prefix S among K restaurants close to the user with appropriate complexity and suggest the full name of those restaurants to the user.

# Approach
They need a min-heap for sorting all the restaurants that the user gave us as input. Then when we call the queries, in addition to removing them from the heap and putting the n-called restaurant to a trie-tree, They also need to put them into a stack to protect the order of the algorithm They used.
