//First personal project:
//aim: create a statistical calculator that provides basic functions for beginner statistics
//project will become more advanced as I learn new concepts in statistics
#include <iostream>
#include <vector>
#include <cmath>
#include "basics.h"

Basics::Basics()
{
  sum=0;
  mean=0;
  mode=0;
  range=0;
  iqr=0;

}
//sorts the vector
//TODO:search up better sorting algorithms(std::sort)
void Basics::sortDataset(std::vector<double> &dataset)
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
void Basics::displayDataset(std::vector<double> dataset) {
	sortDataset(dataset);
	// TODO:NOTE(sirflankalot): input -> inputted
	std::cout << "The dataset you input is: " << '\n';
	// TODO:NOTE(sirflankalot): for (auto& number : dataset)
	// TODO:NOTE(sirflankalot): then dataset[index] -> number
	for (int index = 0; index < dataset.size(); index++) {
		std::cout << " " << dataset[index];
	}
	std::cout << '\n';
}


void Basics::displayMinMax(std::vector<double> dataset)
{
  //TODO: NOTE(sirflankalot): dataset.first()
	//TODO: NOTE(sirflankalot): dataset.last()
  sortDataset(dataset);
  std::cout<<"The minimum value of the dataset is: "<<dataset[0]<<'\n';
  std::cout<<"The maximum value of the dataset is: "<<dataset[dataset.size()-1]<<'\n';
}

void Basics::displayPercentiles(std::vector<double> dataset)
{
  // TODO:NOTE(sirflankalot):add a const
  Percentile percentile=calculatePercentiles(dataset);
  if (dataset.size()<=3)
  {
    std::cout<<"The 50th percentile(MEDIAN) of the dataset is: "<<percentile.q2<<'\n';
  }
  else if(dataset.size()>=4)
  {
    std::cout<<"The 25th percentile of the dataset is: "<<percentile.q1<<'\n';
    std::cout<<"The 50th percentile(MEDIAN) of the dataset is: "<<percentile.q2<<'\n';
    std::cout<<"The 75th percentile of the dataset is: "<<percentile.q3<<'\n';
  }
}

// TODO:NOTE(sirflankalot): add a const to terms
void Basics::displayStandardDeviation(std::vector <double> dataset,const int terms)
{
  //TODO: NOTE(sirflankalot): add a const
	dataType sd = calculateStandardDeviation(dataset, terms);
	// TODO:NOTE(sirflankalot): STOP YELLING AT ME
	std::cout << "The SAMPLE STANDARD DEVIATION (Sx) is: " << sd.sample << '\n';
	// TODO:NOTE(sirflankalot): Don't use pow, multiply by itself
	std::cout << "The SAMPLE VARIANCE (Sx^2) is: " << pow(sd.sample, 2) << '\n';
	std::cout << "The POPULATION STANDARD DEVIATION (σ) is: " << sd.population << '\n';
	std::cout << "The POPULATION VARIANCE (σ^2) is: " << pow(sd.population, 2) << '\n';
}
//finds the mean of the amount of terms inputed by the user
double Basics::calculateMean(std::vector <double> dataset,const int terms)
{
  // TODO:NOTE(sirflankalot): std::accumulate in <numeric>
  for (int i=0;i<dataset.size();i++)
  {
    sum+=dataset[i];
  }
  mean=(sum/terms);
  return mean;
}

double Basics::calculateRange(std::vector <double> dataset)
{
  // TODO:NOTE(sirflankalot): dataset.first()
	// TODO:NOTE(sirflankalot): dataset.last()
  sortDataset(dataset);
  range=dataset[dataset.size()-1]-dataset[0];
  return range;
}

//calculates 25th,50th, and 75th percentile of the data set
Percentile Basics::calculatePercentiles(std::vector <double> dataset)
{
  Percentile percentile;
  sortDataset(dataset);
  // TODO:NOTE(sirflankalot): this function is way to unweildy. Factor it out into three separate functions finding q1, q2, and q3.

	// TODO:NOTE(sirflankalot): factor this out into a boolean with a clear name like even_count
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
  // TODO:NOTE(sirflankalot): else is redundant
  else
  {
    // TODO:NOTE(sirflankalot): Index out of range error with input 2 2 2
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


double Basics::calculateMode(std::vector <double> dataset)
{
  // TODO:NOTE(sirflankalot): dataset.first()
  sortDataset(dataset);
  mode = dataset[0];
  int count=1;
  int maxCount=0;
  // TODO:NOTE(sirflankalot): Off by 1 error, you run off the end of the array here.
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
    // TODO:NOTE(sirflankalot): add space after comma
    std::cout<<"all numbers repeat equally,returning first term: ";
    return mode;
  }

}

DataType Basics::calculateStandardDeviation(std::vector <double> dataset,int terms)
{

  mean=calculateMean(dataset,terms);
  DataType sd;
  sd.population=0;
  sd.sample=0;
  // TODO:NOTE(sirflankalot): replace with foreach loop
	// TODO:NOTE(sirflankalot): pow(blah, 2) -> blah * blah, use a temporary value
  for (int i=0;i<dataset.size();i++)
  {
    sd.sample+=pow(dataset[i]-mean,2);
    sd.population+=pow(dataset[i]-mean,2);
  }
  sd.sample=std::sqrt(sd.sample/(terms-1));
  sd.population=std::sqrt(sd.population/(terms));
  return sd;
}

double Basics::calculateInterquartileRange(std::vector<double> dataset)
{
  percentile=calculatePercentiles(dataset);
  iqr=percentile.q3-percentile.q1;
  return iqr;
}


void Basics::findOutliers(std::vector<double> dataset)
{
  // TODO:NOTE(sirflankalot): all 4 variables can be const
  Percentile percentile=calculatePercentiles(dataset);
  double iqr=calculateInterquartileRange(dataset);
  double lower=percentile.q1-(iqr*1.5);
  double upper=percentile.q3+(iqr*1.5);

  // TODO:NOTE(sirflankalot): foreach loop
  for (int i=0;i<dataset.size();i++)
  {
    if (dataset[i]>upper || dataset[i]<lower)
    {
      outliers.push_back(dataset[i]);
    }
  }
  if (!(outliers.empty()))
  {
    std::cout<<"The OUTLIER(S) of this dataset is(are): ";
    for (int j=0;j<outliers.size();j++)
    {
      std::cout<<outliers[j]<<" ";
    }
  }
  else
  {
    std::cout<<"No outliers found in the data set";
  }

  std::cout<<'\n';
}
