#include <iostream>
#include <cstdlib>
#include <vector>

class WorldMap
{
      public:
             
      WorldMap(int w, int h);
      ~WorldMap();
      
      private:
      int x, y;
      //int geography[w][h];
      //int itemsAndCharacters[w][h];
    // std::vector< std::vector<int> > geography(5, std::vector<int>(5,0));       
      std::vector<std::vector<int> > geography(x, std::vector<int>(y));
    //  void initializeMap();
      
};
