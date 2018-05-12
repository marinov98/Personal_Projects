#include <iostream>
#include <vector>
#include "basics.h"

int main()
{
  std::vector <double> dataset;
  bool repeat;
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
    repeat=true;
    char answer;
    while (repeat==true)
    {
      Basics basics;
      //gets the number of terms in the date set and fills the vector with them
      std::cout<<"How many terms are there?"<<'\n';
      std::cin>>terms;
      std::cout<<"You may now type the numbers in your data set"<<'\n';
      while (trials!=terms)
      {
        std::cin>>inputnumber;
        dataset.push_back(inputnumber);
        trials++;
      }
      //showcases the dataset's mean, mode, and range
      basics.displayDataset(dataset);
      std::cout<<"The MEAN of the dataset is: "<<basics.calculateMean(dataset,terms)<<'\n';
      std::cout<<"The MEDIAN of the data is: "<<basics.calculatePercentiles(dataset).q2<<'\n';
      std::cout<<"The MODE of your dataset is: "<<basics.calculateMode(dataset)<<'\n';
      std::cout<<"The RANGE of the dataset is: "<<basics.calculateRange(dataset)<<'\n';
      basics.displayMinMax(dataset);
      //prints the 25th,50th, and 75th percentile of the dataset
      //basics.displayPercentiles(dataset);
      if (dataset.size()>3)
      {
        std::cout<<'\n'<<"Percentiles: "<<'\n';
        std::cout<<"The INTERQUARTILE RANGE of the dataset is: "<<basics.calculateInterquartileRange(dataset)<<'\n';
        basics.displayPercentiles(dataset);
      }
      basics.findOutliers(dataset);

      std::cout<<'\n';
      //prints standard deviation and variance
      std::cout<<"Standard deviation and Variance: "<<'\n';
      basics.displayStandardDeviation(dataset,terms);
      std::cout<<'\n';
      //erase terms once finished showing numbers to user
      dataset.erase(dataset.begin(),dataset.end());
      //reset the trials
      trials=0;
      std::cout<<"Would like to use this function again? Type 'y' or 'n' "<<'\n';
      std::cin>>answer;
      if (answer=='y')
      {
        repeat=true;
      }
      else
      {
        repeat=false;
      }
    }
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
