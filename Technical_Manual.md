# Compression Detection Application Technical Manual

## Installation/Usage Guide
# Tools Used
* [ns3] (https://www.nsnam.org/) - Network Simulator
* [Python] (https://www.python.org/) - Programming Language

# Prerequisite installation 
* git ```sudo apt install git```  
* python ```sudo apt-get install python```   

# Steps
## 1. Clone GitHub repository
Type the following on the Linux shell:

```cd```   
```mkdir GitHub```   
```cd GitHub```   
```git clone https://github.com/418-teapots/CS621-Project-2.git```   

## 2. NS-3.29
1) ***Install ns-3.29***  
Type the following on the Linux shell:

```cd```  
```mkdir workspace```  
```cd workspace```  
```wget https://www.nsnam.org/release/ns-allinone-3.29.tar.bz2```  
```tar xjf ns-allinone-3.29.tar.bz2```  
  
2) ***Build***  
If you downloaded using a tarball you should have a directory called something like ns-allinone-3.29 under your ~/workspace directory. Type the following:

```cd ns-allinone-3.29```  
```./build.py --enable-examples --enable-tests```  
  
3) ***Test for installation***  
You can run the unit tests of the ns-3 distribution by running the ./test.py script under the ns-3 top directory:  
  
```./test.py```   

4) ***Copy ns-3.29 folder to the github directory***  
Copy the ns-3.29 directory generated to the GitHub repository created earlier.  
Do not overwrite the exisiting files.  

```cp -nr ns-3.29 ~/Github/CS621-Project-2/```

## 3. Application 
1) ***Test***  
Under the ns-3 top directory, you can run the application by typing the following:

``` cd ~/GitHub/CS621-Project-2/ns-3.29```   
```./waf --run "cs621-dev02 --conf=SPQ"```  
  
2) ***Run Simulation***  
You can run the network simulation by using python script. Type the following:  

```cd ~/GitHub/CS621-Project-2/ ```   
```python run.py```  
