# Scripts description
# How to run scripts
## In project dev container 
### Create Virtual Environment
### Activate Virtual Environment
### Run Script
## On Windows loca machine in CMD
### Create Virtual Environment
### Activate Virtual Environment
### Run Script
## On Windows loca machine in PowerShell
### Create Virtual Environment
### Activate Virtual Environment
### Run Script
## In Bash
### Create Virtual Environment
### Activate Virtual Environment
### Run Script

# Basic Requiremets to run the script
## Project Dev Container
All requred tools are installed in the dev container.
## Local Machine
* Python3 Installed
* Python3 pip module Installed
* Python3 venv module installed


# Running Python Scripts in a Virtual Environment

This guide provides instructions for creating a virtual environment, activating it, and running Python scripts on different platforms.

## On Windows Local Machine in CMD

### Create Virtual Environment
Open `_config_scipts` directory in **Command Prompt** (CMD), and 
run the following command:
```cmd
python3 -m venv .venv
```

### Activate Virtual Environment
Once the virtual environment is created, activate it using this command:
```cmd
.\.venv\Scripts\activate
```
### Install Dependencies
Ensure the virtual environment is activated and
run the following command to install the dependencies:
```cmd
pip install -r requirements.txt
```
### Run Script
With the virtual environment activated, run your Python script:
```cmd
python3 script_folder/your_script.py
```
### Deactivate Venv
If the virtual environment is no longer needed, you can deactivate it by typing:
```cmd
deactivate
```

## On Windows Local Machine in PowerShell

### Create Virtual Environment
Open `_config_scipts` directory in **PowerShell**, and run the following command:
```powershell
python3 -m venv .venv
```

### Activate Virtual Environment
If your system has a stricter execution policy that prevents running scripts, you may need to temporarily change the execution policy. To do this, run the following command:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process
```
This will allow you to activate the virtual environment for the current session only.

Now, activate the virtual environment with this command:
```powershell
.\.venv\Scripts\Activate
```
### Install Dependencies
Ensure the virtual environment is activated and
run the following command to install the dependencies:
```powershell
pip install -r requirements.txt
```

### Run Script
With the virtual environment activated, run your Python script:
```powershell
python3 script_folder/your_script.py
```
### Deactivate Venv
If the virtual environment is no longer needed, you can deactivate it by typing:
```powershell
deactivate
```

## In Bash and Project DevContainer

### Create Virtual Environment
Open `_config_scipts` directory in **Bash terminal** and run the following command:
```bash
python3 -m venv .venv
```

### Activate Virtual Environment
Once the virtual environment is created, activate it with this command:
```bash
source .venv/bin/activate
```
### Install Dependencies
Ensure the virtual environment is activated and
run the following command to install the dependencies:
```bash
pip install -r requirements.txt
```

### Run Script
With the virtual environment activated, run your Python script:
```bash
python3 script_folder/your_script.py
```
### Deactivate Venv
If the virtual environment is no longer needed, you can deactivate it by typing:
```bash
deactivate
```


