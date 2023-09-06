/*
 * Name: Elle Hanckel
 * Date Submitted: 05/02/2023
 * Assignment Name: Word Ladder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<string> V; //words from wordlist05.txt
//gathered from Lab 10
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
// GENERIC -- these shouldn't need to be changed...
unordered_map<string, bool> visited;         // have we queued up this string for visitation?
unordered_map<string, string> pred;          // predecessor string we came from
unordered_map<string, int> dist;             // distance (# of hops) from source node
unordered_map<string, vector<string>> nbrs;  // vector of neighboring string
unordered_set<string> wordSet;               //set of the words 

void build_graph();
void search(string word);

//Implement breadth-first search, refer to Lab 10
// GENERIC (breadth-first search, outward from source_node)
void search(string word)
{
  //visiting nodes in order that they are discovered first
  //to_visit is first single item in queue 
  //distance is 0 and mark node has true as visited before moving on so node doesnt show up again later in queue 
  queue<string> to_visit;
  to_visit.push(word);
  visited[word] = true;
  dist[word] = 0;

  //while queue is not empty, set curnode to first item in queue, go through processing all nbrs of node being visited as long as they aren't visited
  //update pred to be curnode and update distance with +1
  //then mark as true for it as visited when adding to queuem so it only goes into queue once, put back into queue 
  while (!to_visit.empty()) {
    string curnode = to_visit.front();
    to_visit.pop();
    for (string n : nbrs[curnode])
      if (!visited[n]) {
	    pred[n] = curnode;
	    dist[n] = 1 + dist[curnode];
	    visited[n] = true;
	    to_visit.push(n);
      }
  }
}

void build_graph() {

  //openingf file, and looping through it and pushing words into V and wordset
  ifstream myFile("wordlist05.txt");
  string word;
  while (getline(myFile, word)) {
    V.push_back(word);
    wordSet.insert(word);
  }

  //looping through words in V
  for (auto word : V) {
    //looping through each letter in word
    for (int index = 0; index < word.length(); index++) {
      for (char letter = 'a'; letter <= 'z'; letter++) {
        //if the letter is the same then continue
        if (letter == word.at(index)) {
          continue;
        //if letter is not the same at word[index]
        } else {
          //create temp string, change the letter and if it is in wordSet, push back temp into nbrs at word index
          string temp = word;
          temp.at(index) = letter;
          if (wordSet.find(temp) != wordSet.end()) {
            nbrs[word].push_back(temp);
          }
        }
      }
    }
  }

}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
  //calling functions
  build_graph();
  search(s);

  //no solution case
  if (pred.find(t) == pred.end()) {
    steps = 0;
    p.clear();
    return;
  }

  //if string s is not the same as string t, update steps, clear vector p and create temp string equal to t
  if (s.compare(t) != 0) {
    steps = dist[t];
    p.clear();
    string temp = t;

    //reveals path in reverse
    while (temp != s) {
      p.push_back(temp);
      temp = pred[temp];
    }
    //pushing temp into p
    p.push_back(temp);
    reverse(p.begin(), p.end());
    

  } else { // if string s and string t are the same, set steps to 0, clear vector p, push back t into p and return
    steps = 0;
    p.clear();
    p.push_back(t);
    return;
  }

}

// int main(void)
// {
//   int steps = 0;
//   string s, t;
//   vector<string> path;
  
//   cout << "Source: ";
//   cin >> s;

//   cout << "Target: ";
//   cin >> t;

//   wordLadder(s, t, steps, path);

//   if (steps == 0)
//   {
//       cout << "No path!\n";
//   }
//   else
//   {
//       cout << "Steps: " << steps << "\n\n";
//       for (int i=0; i<path.size(); i++)
//       {
//           cout << path[i] << endl;
//       }
//   }
//   return 0;
// }
