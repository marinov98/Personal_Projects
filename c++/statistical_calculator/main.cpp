#include <iostream>
#include <vector>
#include "basics.h"



int main()
{
  std::vector <double> dataset;
  int terms;
  int trials=0;
  double inputnumber;
  std::string response;
  std::cout<<"~~~**Welcome to the statisical calculator MPM(beta stage)!**~~~"<<'\n';
  std::cout<<"What would you like the calculator to do?"<<'\n';
  std::cout<<"type 'basics'{mean,median,mode,range,standard deviation} or 'other' view more functions"<<'\n';
  std::cin>>response;
  if (response=="basics")
  {
    Basics basics;
    std::cout<<"How many terms are there?"<<'\n';
    std::cin>>terms;
    std::cout<<"You may now type the numbers in your data set"<<'\n';
    while (trials!=terms)
    {
      std::cin>>inputnumber;
      dataset.push_back(inputnumber);
      trials++;
    }
    basics.displayDataset(dataset);
    std::cout<<"The MEAN of the dataset is: "<<basics.calculateMean(dataset,terms)<<'\n';
    std::cout<<"The MODE of your dataset is: "<<basics.calculateMode(dataset)<<'\n';
    std::cout<<"The RANGE of the dataset is: "<<basics.calculateRange(dataset)<<'\n';
    basics.displayMinMax(dataset);
    std::cout<<'\n'<<"Percentiles: "<<'\n';
    basics.displayPercentiles(dataset);
    std::cout<<"The INTERQUARTILE RANGE of the dataset is: "<<basics.calculateInterquartileRange(dataset)<<'\n';
    basics.findOutliers(dataset);
    std::cout<<'\n';
    std::cout<<"Standard deviation and Variance: "<<'\n';
    basics.displayStandardDeviation(dataset,terms);
    std::cout<<'\n';
    //erase terms once finished showing numbers to user
    dataset.erase(dataset.begin(),dataset.end());
    //reset the trials
    trials=0;
  }
  else if (response=="other")
  {
    std::cout<<"sorry I have not made those functions work yet!"<<'\n';
  }
  else
  {
    std::cout<<"Thank you for using this statistical calculator! Come again!"<<'\n';
  }

}
