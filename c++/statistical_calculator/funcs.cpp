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

struct Percentile
{
  double q1;
  double q2;
  double q3;
};

//prototypes:
void sortDataset(std::vector <double> &dataset);
void displayDataset(std::vector<double> dataset);
void sd_printSampleAndPop(dataType func);
void displayMinMax(std::vector<double> dataset);
double calculateMean(std::vector <double> dataset,int terms);
double calculateRange(std::vector <double> dataset);
Percentile calculatePercentiles(std::vector <double> dataset);
double calculateMode(std::vector <double> dataset);
dataType calculateStandardDeviation(std::vector <double> dataset,int terms);
double calculateInterquartileRange(std::vector<double> dataset);
void findOutliers(std::vector<double> dataset);



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
  cout<<'\n';
}

void displayMinMax(std::vector<double> dataset)
{
  sortDataset(dataset);
  cout<<"The minimum value of the dataset is: "<<dataset[0]<<'\n';
  cout<<"The maximum value of the dataset is: "<<dataset[dataset.size()-1]<<'\n';
}

void displayPercentiles(std::vector<double> dataset)
{
  Percentile percentile=calculatePercentiles(dataset);
  if (dataset.size()<=3)
  {
    cout<<"The 50th percentile(MEDIAN) of the dataset is: "<<percentile.q2<<'\n';
  }
  else if(dataset.size()>=4)
  {
    cout<<"The 25th percentile of the dataset is: "<<percentile.q1<<'\n';
    cout<<"The 50th percentile(MEDIAN) of the dataset is: "<<percentile.q2<<'\n';
    cout<<"The 75th percentile of the dataset is: "<<percentile.q3<<'\n';
  }
}


void displayStandardDeviation(std::vector <double> dataset,int terms)
{
  dataType sd=calculateStandardDeviation(dataset,terms);
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
  return range;
}


Percentile calculatePercentiles(std::vector <double> dataset)
{
  Percentile percentile;
  sortDataset(dataset);
  if (dataset.size() % 2 == 1 )
  {
    if ((dataset.size()/2-1) % 2 == 1)
    {
      percentile.q1=dataset[(dataset.size()-1)/4];
      percentile.q2=dataset[(dataset.size()-1)/2];
      percentile.q3=dataset[dataset.size()*3/4];
    }
    else
    {
      percentile.q1=((dataset[dataset.size()/4]+dataset[dataset.size()/4-1])/2);
      percentile.q2=dataset[(dataset.size()-1)/2];
      percentile.q3=((dataset[dataset.size()*3/4]+dataset[dataset.size()*3/4-1])/2);
    }
    return percentile;
  }
  else
  {
    if ((dataset.size()/2) % 2 == 1)
    {
      percentile.q1=dataset[(dataset.size()-1)/4];
      percentile.q2=((dataset[dataset.size()/2]+dataset[dataset.size()/2-1])/2);
      percentile.q3=dataset[dataset.size()*3/4];
    }
    else
    {
      percentile.q1=((dataset[dataset.size()/4]+dataset[dataset.size()/4-1])/2);
      percentile.q2=((dataset[dataset.size()/2]+dataset[dataset.size()/2-1])/2);
      percentile.q3=((dataset[dataset.size()*3/4]+dataset[dataset.size()*3/4-1])/2);
    }
    return percentile;
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
  if (maxCount>0)
  {
    return mode;
  }
  else
  {
    cout<<"all numbers repeat equally,returning first term: ";
    return mode;
  }

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

double calculateInterquartileRange(std::vector<double> dataset)
{
  Percentile percentile=calculatePercentiles(dataset);
  double iqr=percentile.q3-percentile.q1;
  return iqr;
}


void findOutliers(std::vector<double> dataset)
{
  std::vector<double>outliers;
  Percentile percentile=calculatePercentiles(dataset);
  double iqr=calculateInterquartileRange(dataset);
  double lower=percentile.q1-(iqr*1.5);
  double upper=percentile.q3+(iqr*1.5);
  for (int i=0;i<dataset.size();i++)
  {
    if (dataset[i]>upper || dataset[i]<lower)
    {
      outliers.push_back(dataset[i]);
    }
  }
  if (outliers.size()>0)
  {
    cout<<"The OUTLIER(S) of this dataset is(are): ";
    for (int j=0;j<outliers.size();j++)
    {
      cout<<outliers[j]<<" ";
    }
  }
  else
  {
    cout<<" No outliers found in the data set";
  }

  cout<<'\n';
}
