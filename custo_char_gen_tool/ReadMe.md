# Automation scripts description
# General Requirements

### Python3 installed

### pip3 installed 
```bash
sudo apt install python3-pip
```
### Virtualenv installed
Windows:
```shell
pip install virtualenv
```
Unix:
```bash
pip install python3-venv
```
# How to setup environment
### 1. Open script in terminal 
### 2. Create Virtual Environment for running the scritps 
Win:
```shell
python3 -m virtualenv venv
```
Unix:
```bash
python3 -m venv .myVenv
```
### 3. Run environment

Win:
```shell
venv\Scripts\activate
```
Unix:
```bash
source .myVenv/bin/activate
```
### 3. Instal required dependencies
Unix, Win:
```bash
pip install -r requirements.txt
```
### 4. If no other operation i venv are requiret, to clos the venv type

Unix, Win:
```bash
deactivate
```



# How to run the script
### 1. Open automeation script folder in terminal 

### 3. Run virtual environment

Win:
```shell
venv\Scripts\activate
```
Unix:
```bash
source .myVenv/bin/activate
```
### 3. Run selected script. 
Unix,Win:
```bash
python3 -m custom_char_gen
```
### 4. If no other operation i venv are requiret, you can close it by typing

Unix,Win:
```bash
deactivate
```