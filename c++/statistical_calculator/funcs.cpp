//First personal project:
//aim: create a statistical calculator that provides basic functions for beginner statistics
//project will become more advanced as I learn new concepts in statistics
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::cin;
using std::vector;

void sortVector(vector <double> &v);
double calculateMean();
double calculateRange();
double calculateMedian();

//sorts the vector
void sortVector(vector<double> &v)
{
  double hold;
  for (int x=0;x<v.size();x++)
  {
    for (int y=0;y<v.size()-1;y++)
    {
      if (v[y]>v[y+1])
      {
        hold=v[y];
        v[y]=v[y+1];
        v[y+1]=hold;
      }
    }
  }
}
//finds the mean of the amount of terms inputed by the user
double calculateMean()
{
  double mean;
  double inputnum;

  int trials=0;
  double sum=0;
  int terms;

  cout<<"how many terms do you want?"<<'\n';
  cin>>terms;
  cout<<"you can input your terms now"<<'\n';
//read user's input and add it to the sum
  do
  {
    cin>>inputnum;
    sum+=inputnum;
    trials++;
  }
  while(trials!=terms);

  cout<<"your mean is: ";
  return double(sum/terms);
}

double calculateRange()
{
  vector<double> numbers;
  int trials=0;
  int terms;
  double range;
  double inputnum;

  cout<<"how many terms?"<<'\n';
  cin>>terms;
  cout<<"you may input your numbers now"<<'\n';
  do
  {
    cin>>inputnum;
    numbers.push_back(inputnum);
    trials++;
  }
  while(trials!=terms);
  sortVector(numbers);
  range=numbers[numbers.size()-1]-numbers[0];
  cout<<" your range is : ";
  return range;
}


double calculateMedian()
{
  vector<double> numbers;
  int trials=0;
  int terms;
  double median;
  double inputnum;

  cout<<"how many terms?"<<'\n';
  cin>>terms;
  cout<<"you may input your numbers now"<<'\n';
  do
  {
    cin>>inputnum;
    numbers.push_back(inputnum);
    trials++;
  }
  while(trials!=terms);
  sortVector(numbers);
  if (numbers.size() % 2 == 1 )
  {
    median=numbers[(numbers.size()-1)/2];
    cout<<"your median is: ";
    return median;
  }
  else
  {
    median=((numbers[numbers.size()/2]+numbers[numbers.size()/2-1])/2);
    cout<<"your median is: ";
    return median;
  }
}


double calculateMode()
{
  
}
