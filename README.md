# H1_acceptance_calc
## Requirement
* ROOT : 6.18 or above
* Geant4 : 4.10 or above
* libxml2 and CLHEP required
* __recomend to use it on kekcc__
## How to set enviroment on kekcc
* Enter your account on kekcc  
* Follow the bellow steps to create a new file  
```cd $HOME```  
```[vi/emacs] setup_gcc_9_2_0_zsh.sh```  
* Write below letters on `setup_gcc_9_2_0_zsh.sh`  
```#!/bin/sh

cd $(dirname $0)
CUR=$PWD
echo $CUR
# gcc 9.2.0
export PATH=/group/had/g-2/share/gcc/gcc-9.2.0/bin:$PATH
export LD_LIBRARY_PATH=/group/had/g-2/share/gcc/gcc-9.2.0/lib64:/group/had/g-2/share/gcc/gcc-9.2.0/lib:${LD_LIBRARY_PATH}
export CC=`which gcc`
export CXX=`which g++`

# python 2.7.17
export PATH=/group/had/g-2/share/python/python-2.7.17/bin:$PATH
export LD_LIBRARY_PATH=/group/had/g-2/share/python/python-2.7.17/lib:${LD_LIBRARY_PATH}

# cmake 3.15.5
export PATH=/group/had/g-2/share/cmake/cmake-3.15.5/bin:$PATH

# sqlite 3.30.1
export PATH=/group/had/g-2/share/sqlite/sqlite-3.30.1/bin:$PATH
export LD_LIBRARY_PATH=/group/had/g-2/share/sqlite/sqlite-3.30.1/lib:${LD_LIBRARY_PATH}

# root 6.18.04
cd /group/had/g-2/share/root/root-6.18.04
source /group/had/g-2/share/root/root-6.18.04/bin/thisroot.sh
cd $CUR

# xerces-c 3.2.2
export PATH=/group/had/g-2/share/xerces-c/xerces-c-3.2.2/bin:$PATH
export LD_LIBRARY_PATH=/group/had/g-2/share/xerces-c/xerces-c-3.2.2/lib:${LD_LIBRARY_PATH}

# geant4.10.05.p01
cd /group/had/g-2/share/geant4/geant4.10.05.p01/install/bin
source /group/had/g-2/share/geant4/geant4.10.05.p01/install/bin/geant4.sh
cd $CUR

# eigen 3.3.7
export Eigen3_DIR=/group/had/g-2/share/eigen3/eigen-3.3.7/share/eigen3/cmake
export ROOT_INCLUDE_PATH=/group/had/g-2/share/eigen3/eigen-3.3.7/include/eigen3

# Genfit 7833bbda914ed24b420091f302ff3569537edc7e
export GENFIT_DIR=/group/had/g-2/share/genfit/GenFit-7833bbda914ed24b420091f302ff3569537edc7e
export LD_LIBRARY_PATH=${GENFIT_DIR}/lib64:${LD_LIBRARY_PATH}

# git 2.25.0
export PATH=/group/had/g-2/share/git/git-2.25.0/bin:$PATH
export LD_LIBRARY_PATH=/group/had/g-2/share/git/git-2.25.0/libexec:${LD_LIBRARY_PATH}```
* Write below letters on your `.bashrc` or `.zshrc`
```source $HOME/setup_gcc_9_2_0_zsh.sh```
## How to build
1. git clone the repo  
```git clone https://github.com/UshizawaT/H1_acceptance_calc.git```
2. go to build dir  
```cd H1_acceptance_calc/build```
3. cmake and make it  
```cmake .. && make```
## How to use
1. write .xml file (ex. setting_test.xml  
    * you can put whatever you want.
2. run the Acceptance_calculation  
```./Acceptance_calculation [seed number] [xml file name] [macro file (*.mac)]```
    * The inside `[]` is your defined
    * macro files:  
        * run.mac : run 1e+6 events
        * test_run.mac : run 1e+3 events
        * run4ep.mac : for run prompt positron (1e+7 events)
    * If you want to see visualization, remove `[macro file]`