import os
import subprocess
import sys
import venv
import platform

def is_root():
    """
    Checks if the script is running as root.
    Returns True if running as root, False otherwise.
    """
    return os.geteuid() == 0 if platform.system().lower() == "linux" else False

def check_and_install_pip():
    """
    Checks if pip is installed and installs it if necessary.
    Uses 'python3 -m ensurepip' for Windows and 'apt' for Linux.
    """
    try:
        subprocess.run([sys.executable, "-m", "pip", "--version"], check=True)
        print("✅ Pip is already installed.")
    except subprocess.CalledProcessError:
        print("⚠️ Pip is not installed. Installing...")

        system = platform.system().lower()
        use_sudo = [] if is_root() else ["sudo"]  # Skip sudo if running as root

        if system == "linux":
            try:
                print("🔄 Updating package lists and installing pip...")
                subprocess.run(use_sudo + ["apt", "update"], check=True)
                subprocess.run(use_sudo + ["apt", "install", "-y", "python3-pip"], check=True)
                print("✅ Pip has been installed successfully.")
            except subprocess.CalledProcessError:
                print("❌ Failed to install pip using apt.")
                sys.exit(1)

        elif system == "windows":
            try:
                print("🔄 Installing pip using ensurepip...")
                subprocess.run(["python3", "-m", "ensurepip", "--default-pip"], check=True)
                subprocess.run(["python3", "-m", "pip", "install", "--upgrade", "pip"], check=True)
                print("✅ Pip has been installed successfully.")
            except subprocess.CalledProcessError:
                print("❌ Failed to install pip on Windows.")
                sys.exit(1)

        # Restart the script to ensure pip is recognized
        os.execv(sys.executable, [sys.executable] + sys.argv)

def setup_virtualenv(env_dir="../.venv", requirements_file="requirements.txt"):
    """
    Creates and configures a virtual environment.
    Installs required dependencies if a requirements.txt file is provided.
    """
    check_and_install_pip()

    if not os.path.exists(env_dir):
        print(f"🔄 Creating a virtual environment in {env_dir}...")
        venv.create(env_dir, with_pip=True)

    print("📦 Installing required dependencies...")
    python_exec = os.path.join(env_dir, "bin", "python3") if platform.system().lower() == "linux" else os.path.join(env_dir, "Scripts", "python.exe")

    try:
        subprocess.run([python_exec, "-m", "pip", "install", "-r", requirements_file], check=True)
        print("✅ All dependencies have been installed successfully.")
    except subprocess.CalledProcessError:
        print("❌ Error occurred while installing dependencies.")
        sys.exit(1)

if __name__ == "__main__":
    setup_virtualenv("../.venv", "requirements.txt")
