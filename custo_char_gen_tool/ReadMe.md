# Automation scripts description
# General Requirements

### - Python 3 installed

### - pip3 installed 
```bash
sudo apt install python3-pip
```
# How to setup environment
### 1. Open automeation script folder in terminal 
### 2. Create Virtual Environment for running the scritps 
 
```bash
python3 -m venv .myVenv
```
### 3. Run environment
```bash
source .myVenv/bin/activate
```
### 3. Instal required dependencies
```bash
pip install -r requirements.txt
```
### 4. If no other operation i venv are requiret, to clos the venv type
```bash
deactivate
```



# How to run the script
### 1. Open automeation script folder in terminal 

### 3. Run virtual environment
```bash
source .myVenv/bin/activate
```
### 3. Run selected script. 
Example:
```bash
python3 -m custom_char_gen
```
### 4. If no other operation i venv are requiret, you can close it by typing
```bash
deactivate
```