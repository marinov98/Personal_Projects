
# Welcome to my Statistics Calculator! :octocat:

## To Do's
- make a website for the calculator
- use cmake to launch
- Extensively test the calculator using the [doctest](https://github.com/onqtam/doctest) testing framework

## Third-Party 
- [termcolor](https://github.com/marinov98/termcolor)

## Requirements 
- **CMake 3.12** or newer
- **C++14** or newer

## Table of Contents
  1. [Goals](#Goals)
  2. [Functionality](#Functionality)
  3. [How To Use](#How-To-Use)

## Goals
- Create a simple calculator that can calculate almost anything you throw at it from your intro to statistics class
- Provide an easy to follow interface 
- Allow users to have all in one program that does everything instead of having them search online for different types of statistic calculators

## Functionality 

### Contains Its own [Formula Sheet](https://github.com/marinov98/Statistical_Calculator/blob/master/src/formulas.txt)!

### Basics: 
- mean, median, mode, range
- Sample/Population standard deviation & variance
- Min and Max
- Percentiles
- Interquartile range
- Outliers

#### Showcase:
![basics](https://user-images.githubusercontent.com/33673401/58147734-f9534c80-7c29-11e9-8a05-96f84acfeffa.png)


### Hypothesis Testing (Advanced)
- calculate z-score and t-score
- one/two sample **t** and **z** tests
  - proportions, pair, difference 
- Chi-square test

### Confidence intervals (Advanced)
- Sampling Distribution
- z/t confidence intervals
  - proportion, sample
  - multple z-critical values
  
### Correlation Coefficient
- correlation coefficient
- slope, y-intercept
- line of best fit

#### Showcase:
![cc](https://user-images.githubusercontent.com/33673401/58147914-a332d900-7c2a-11e9-823a-b9d7ef65ee91.png)

## How-To-Use
- clone this repository
- cd into  Statistical_Calculator
- type ```make```

### 3-ways to use the calculator
##### defeault option:
- This option is if you want to use the calculator's default interface where the calculator asks you for what you want and you answer
- type ```make run``` to execute this option

##### About data.txt
- You will notice the project comes with the txt file [data.txt](https://github.com/marinov98/Statistical_Calculator/blob/master/data.txt)
- You can type any dataset in. However, you **must** make sure the numbers are **separated by a comma** and when you are finished **you end with a ;** (data.txt already has an example provided if you are still confused about the format);

##### Special option #1
- type ```make parse```
- if the file contains an imvalid input, the command will not do anything 
- this command will parse through the data file and every time it finds a ; it will print out every function described in [basics](#Basics).
- You can have multiple datasets typed as long as they each end in ; the command will then print each dataset that it finds

##### Special option #2
- There are multiple commands here but they all work the same
- Here instead of printing all the fucntions described in [basics](#Basics), you pick the specific one 
- Again the command will do this for every dataset it finds in the data.txt file 
- Commands include ``make```:
  - ```mean```
  - ```median```
  - ```percentile```
  - ```mode```
  - ```range```
  - ```min```
  - ```max```
  - ```outliers```
  - ```sd```
 
## Regarding CMake
- right now it is best to compile with the Makefile I made for the project
- The Cmake works just as well
