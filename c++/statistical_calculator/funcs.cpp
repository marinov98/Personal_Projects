//First personal project:
//aim: create a statistical calculator that provides basic functions for beginner statistics
//project will become more advanced as I learn new concepts in statistics
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::cout;
using std::string;



struct dataType
{
  double population;
  double sample;
};

//prototypes:
void sortDataset(std::vector <double> &dataset);
void displayDataset(std::vector<double> dataset);
void sd_printSampleAndPop(dataType func);
double calculateMean(std::vector <double> dataset,int terms);
double calculateRange(std::vector <double> dataset);
double calculateMedian(std::vector <double> dataset);
double calculateMode(std::vector <double> dataset);
dataType calculateStandardDeviation(std::vector <double> dataset,int terms);



//sorts the vector
void sortDataset(std::vector<double> &dataset)
{
  double hold;
  for (int x=0;x<dataset.size();x++)
  {
    for (int y=0;y<dataset.size()-1;y++)
    {
      if (dataset[y] > dataset[y+1])
      {
        hold=dataset[y];
        dataset[y]=dataset[y+1];
        dataset[y+1]=hold;
      }
    }
  }
}

//displays all the elements in the vector
void displayDataset(std::vector<double> dataset)
{
  sortDataset(dataset);
  cout<<"The dataset you input is: "<<'\n';
  for (int index=0;index<dataset.size();index++)
  {
    cout<<" "<<dataset[index];
  }
}

void sd_printSampleAndPop(dataType sd)
{
  cout<<"The SAMPLE STANDARD DEVIATION (Sx) is: "<<sd.sample<<'\n';
  cout<<"The SAMPLE VARIANCE (Sx^2) is: "<<pow(sd.sample,2)<<'\n';
  cout<<"The POPULATION STANDARD DEVIATION (σ) is: "<<sd.population<<'\n';
  cout<<"The POPULATION VARIANCE (σ^2) is: "<<pow(sd.population,2)<<'\n';
}
//finds the mean of the amount of terms inputed by the user
double calculateMean(std::vector <double> dataset,int terms)
{
  double mean;
  double sum=0;
  for (int i=0;i<dataset.size();i++)
  {
    sum+=dataset[i];
  }
  return double(sum/terms);
}

double calculateRange(std::vector <double> dataset)
{
  sortDataset(dataset);
  double range=dataset[dataset.size()-1]-dataset[0];
  cout<<"The RANGE of the dataset is: ";
  return range;
}


double calculateMedian(std::vector <double> dataset)
{
  double median;

  sortDataset(dataset);
  if (dataset.size() % 2 == 1 )
  {
    median=dataset[(dataset.size()-1)/2];
    cout<<"The MEDIAN of your dataset is: ";
    return median;
  }
  else
  {
    median=((dataset[dataset.size()/2]+dataset[dataset.size()/2-1])/2);
    cout<<"The MEDIAN of your dataset is: ";
    return median;
  }
}


double calculateMode(std::vector <double> dataset)
{
  sortDataset(dataset);
  double mode = dataset[0];
  int count=1;
  int maxCount=0;

  for (int i=1;i<dataset.size();i++)
  {
    if (dataset[i] == dataset[i+1])
    {
      count++;
      if (count > maxCount)
      {
        maxCount=count;
        mode=dataset[i];
      }
    }
    else
    {
      count=1;
    }
  }
  cout<<"The MODE of your dataset is: ";
  return mode;
}

dataType calculateStandardDeviation(std::vector <double> dataset,int terms)
{
  double mean=calculateMean(dataset,terms);
  dataType sd;
  sd.population=0;
  sd.sample=0;
  for (int i=0;i<dataset.size();i++)
  {
    sd.sample+=pow(dataset[i]-mean,2);
    sd.population+=pow(dataset[i]-mean,2);
  }
  sd.sample=sqrt(sd.sample/(terms-1));
  sd.population=sqrt(sd.population/(terms));
  return sd;
}
