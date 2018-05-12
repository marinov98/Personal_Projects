#include <iostream>
#include <string>
#include <vector>
#include "funcs.h"

using std::cout;
using std::cin;
using std::string;

int main()
{
  std::vector <double> dataset;
  int terms;
  int trials=0;
  double inputnumber;
  string response;
  cout<<"~~~**Welcome to the statisical calculator MPM(beta stage)!**~~~ :D"<<'\n';
  cout<<"What would you like the calculator to do?"<<'\n';
  cout<<"type 'basics'{mean,median,mode,range,standard deviation} or 'other' view more functions"<<'\n';
  cin>>response;
  if (response=="basics")
  {
    cout<<"How many terms are there?"<<'\n';
    cin>>terms;
    cout<<"You may now type the numbers in your data set"<<'\n';
    while (trials!=terms)
    {
      cin>>inputnumber;
      dataset.push_back(inputnumber);
      trials++;
    }
    displayDataset(dataset);
    cout<<"The MEAN of the dataset is: "<<calculateMean(dataset,terms)<<'\n';
    cout<<"The MODE of your dataset is: "<<calculateMode(dataset)<<'\n';
    cout<<"The RANGE of the dataset is: "<<calculateRange(dataset)<<'\n';
    displayMinMax(dataset);
    cout<<'\n'<<"Percentiles: "<<'\n';
    displayPercentiles(dataset);
    cout<<"The INTERQUARTILE RANGE of the dataset is: "<<calculateInterquartileRange(dataset)<<'\n';
    findOutliers(dataset);
    cout<<'\n';
    cout<<"Standard deviation and Variance: "<<'\n';
    displayStandardDeviation(dataset,terms);
    cout<<'\n';
    //erase terms once finished showing numbers to user
    dataset.erase(dataset.begin(),dataset.end());
    //reset the trials
    trials=0;
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
