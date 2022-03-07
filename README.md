# H1_acceptance_calc
## Requirement
* ROOT : 6.18 or above
* Geant4 : 4.10 or above
* libxml2 and CLHEP required
    * recomend to use it on kekcc
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
```./Acceptance_calculation [seed number] [xml file name] [macro file (*.mac)]```
    * The inside `[]` is your defined
    * macro files:  
        * run.mac : run 1e+6 events
        * test_run.mac : run 1e+3 events
        * run4ep.mac : for run prompt positron (1e+7 events)
    * If you want to see visualization, remove `[macro file]`  
