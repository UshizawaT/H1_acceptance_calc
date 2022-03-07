# H1_acceptance_calc
## Requirement
* ROOT : 6.18 or above
* Geant4 : 4.10 or above
* libxml2 and CLHEP required
## How to build
1. git clone the repo  
```git clone https://github.com/UshizawaT/H1_acceptance_calc.git```
2. go to build dir  
```cd H1_acceptance_calc/build```
3. cmake and make it  
```cmake .. && make```
## How to use
1. write .xml file (ex. setting_test.xml
2. run the Acceptance_calculation  
```./Acceptance_calculation [seed number] [xml file name] [*.mac file]```
   * The inside `[]` is your defined
   * If you want to see visualization, remove `[*.mac file]`  
