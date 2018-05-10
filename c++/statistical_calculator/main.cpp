#include <iostream>
#include <string>
#include "funcs.h"

using std::cout;
using std::cin;
using std::string;

int main()
{

  string response;
  cout<<" Welcome to the statisical calculator!"<<'\n';
  cout<<"What do you want to do? type 'mmmr'{mean,median,mode,range} or 'other' view more functions"<<'\n';
  cin>>response;
  if (response=="mmmr")
  {
    cout<<"are you looking to find the mean,median,mode,or range?"<<'\n';
    cin>>response;
    if (response=="mean")
    {
      cout<<calculateMean()<<'\n';
    }
    else if (response=="range")
    {
      cout<<calculateRange()<<'\n';
    }
    else if (response=="median")
    {
      cout<<calculateMedian()<<'\n';
    }
  }
  else if (response=="other")
  {
    cout<<"sorry I have not made those functions work yet!"<<'\n';
  }
  else
  {
    cout<<"Thank you for using this statistical calculator! Come again!"<<'\n';
  }

}
