#include <iostream>
#include <cstdlib>


const int n = 15; // Number of vertices
const int nTri = 35; // Number of triples

bool used[n]; // Has a vertex been used yet

int triples[][3] =  // Array of triples

// Solution #1a to KTS(15) from P67 of Handbook of Combinatorial Designs, 2nd
// edition.
    { {0,1,2},{3,9,13},{4,7,12},{5,8,14},{6,10,11},
      {0,7,8},{2,5,7},{2,12,13},{3,10,14},{5,9,11},
      {0,9,10},{1,12,13},{2,4,5},{3,7,11},{6,8,13},
      {0,3,4},{1,11,13},{2,8,9},{5,10,12},{6,7,14},
      {0,5,6},{1,7,9},{2,11,14},{3,8,12},{4,10,13},
      {0,11,12},{1,8,10},{2,3,6},{4,9,14},{5,7,13},
      {0,13,14},{1,3,5},{2,7,10},{4,8,11},{6,9,12}};
     
int assignment[15]; // 

void print_assignment()
{
  for (int v = 0; v < n; v++)
    std::cout << v << " ";
  std::cout << std::endl;
  for (int v = 0; v < n; v++)
    std::cout << assignment[v] << " ";
  std::cout << std::endl;
}

void fill(int spot)
{
  if (spot == 15)
  {
    print_assignment();
    exit(0);
  }
  for (int v = 0; v < n; v++)
  {
    if (used[v])
      continue;
    used[v] = true;
    bool badChoice = false;
    for (int t = 0; (t < nTri) && (badChoice == false); t++)
    {
      bool skipThisTriple = false;
      bool vInThisTriple = false;
      for (int k = 0; k < 3; k++)
      {
        int now = triples[t][k];
        if (! used[now])
        {
          skipThisTriple = true;
        }
        if (v == now)
          vInThisTriple = true;
      }
      if (!skipThisTriple && vInThisTriple)
      {
        int totalDist = 0;
        for (int k = 0; k < 3; k++)
        {


          int dist = now - triples[t][(k-1)%3];
          if (dist >= n/2)
            dist = n - dist;
          std::cout << "Dist between " << now << " and " << triples[t][(k-1)%3]
            << " is " << dist << std::endl;
          totalDist += dist;
        }
        if (totalDist == 15)  // Note that for long cycles, totalDist = 15.
          badChoice = true;
      }
    }
    if (! badChoice)
    {
      assignment[spot] = v;
      fill(spot+1);
    }
    used[v] = false;
  }
}

int main(int argc, char **argv)
{
  assignment[0] = 0;
  used[0] = true;
  for (int i = 1; i < n; i++)
    used[i] = false;
  fill(1);
}
