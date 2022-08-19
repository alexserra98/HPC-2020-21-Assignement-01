#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <string>
#include <functional>
int main(int argc, char** argv){
  std::vector<double> num;
  double tmp;
  std::ofstream myfile;
  std::ifstream tmpf;
  tmpf.open("tmp.txt");
  myfile.open("data.txt",std::ofstream::app);
  if(myfile.is_open()&&tmpf.is_open()){
    while(tmpf>>tmp) num.push_back(tmp);
     double avg =std::accumulate(num.begin(), num.end(), 0.0)/num.size();
     // std::cout<<avg<<std::endl;
     myfile<<argv[1]<<" "<<avg<<std::endl;
  }
  else std::cout<<"Couldn't open the file"<<std::endl;
  myfile.close();
  tmpf.close();
  return 0;
}
