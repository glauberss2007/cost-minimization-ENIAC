# Interative cost control planning problem

## Experiment reproduction on linux (debian based distributions)

Install git and clone this repository to any folder in your linux system using:
```
sudo apt-get install git
sudo git clone https://github.com/glauberss2007/cost-minimization-ENIAC.git
```

Install essential libs and cmake using:
```
sudo apt-get install build-essential
sudo snap install cmake --classic
```
Create folder used to export the experiment files following the structure below:
- .../cost-minimization-ENIAC/experiments/cost-100

Inside project folder, that contains CMakeList.txt execute:
```
sudo cmake .
sudo make
```

As soon as it complete compile and build, you can go to test/benchmark folder and execute the program:
```
sudo .\optimal-nutrition
```

PS: You need to recompile and buil the prejec if some code change were made.




