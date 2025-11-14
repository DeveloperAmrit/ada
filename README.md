# Ada Version Control System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

Ada is a mini-Git-like version control system that executes Git functions including init, add, commit, status, log, push, pull, and merge. This project uses data structures like trees, hashmaps, linked lists, and directed acyclic graphs (DAGs).

## ⭐ Why Ada?

- **Educational**: Learn how version control systems work internally
- **Lightweight**: Minimal dependencies, easy to understand codebase
- **GitHub Integration**: Push and pull directly to/from GitHub
- **Cross-Platform**: Works on Linux, macOS, and other Unix-like systems

## Features

✅ **Phase 1: Global Installation**
- Install Ada globally on your system (like Git)
- Works from any directory on your computer
- Easy installation and uninstallation scripts

✅ **Phase 2: GitHub Integration**
- Authenticate with GitHub using personal access tokens
- Automatically create GitHub repositories
- Push and pull from GitHub
- Manage remote repositories

## 🚀 New to Ada?

**→ Start here:** [QUICKSTART.md](QUICKSTART.md) - Get up and running in 5 minutes!

## Quick Start (Fork & Install)

### 1. Fork the Repository

Click the "Fork" button on GitHub to create your own copy of Ada.

### 2. Clone Your Fork

```bash
git clone https://github.com/YOUR_USERNAME/ada.git
cd ada
```

### 3. Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install cmake g++ libcrypto++-dev libcurl4-openssl-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install cmake gcc-c++ cryptopp-devel libcurl-devel
```

**Arch Linux:**
```bash
sudo pacman -S cmake gcc crypto++ curl
```

**macOS (with Homebrew):**
```bash
brew install cmake gcc cryptopp curl
```

### 4. Run the Installation Script

```bash
chmod +x install.sh
./install.sh
```

The script will:
- ✓ Check all dependencies
- ✓ Build the Ada binary
- ✓ Install it to `~/.local/bin` (no sudo required) or `/usr/local/bin`
- ✓ Make it available globally on your system

### 5. Update Your PATH (if needed)

If the installer warns that `~/.local/bin` is not in your PATH:

```bash
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

For zsh users:
```bash
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

### 6. Verify Installation

```bash
ada --version
```

You should see: `Ada version control system v1.0`

## Installation

### Prerequisites

Before installing Ada, make sure you have:
- CMake (version 3.10 or higher)
- C++ compiler with C++17 support
- Crypto++ library
- libcurl library

See the "Quick Start" section above for platform-specific installation commands.

## Uninstallation

To remove Ada from your system:
```bash
chmod +x uninstall.sh
./uninstall.sh
```

## Getting Started

### Basic Usage

1. **Initialize a repository:**
```bash
mkdir my-project
cd my-project
ada init
```

2. **Configure your identity:**
```bash
ada config --global user.name "Your Name"
ada config --global user.email "your.email@example.com"
```

3. **Add files and commit:**
```bash
echo "Hello World" > hello.txt
ada add hello.txt
ada commit
# Enter commit message when prompted
```

4. **Check status:**
```bash
ada status
```

5. **View commit history:**
```bash
ada log
```

## GitHub Integration

### Setup GitHub Authentication

1. **Create a GitHub Personal Access Token:**
   - Go to https://github.com/settings/tokens
   - Click "Generate new token" → "Generate new token (classic)"
   - Give it a name (e.g., "Ada VCS")
   - Select scopes: `repo` (Full control of private repositories)
   - Click "Generate token"
   - **Copy the token** (you won't see it again!)

2. **Configure Ada with your GitHub credentials:**
```bash
ada config --global github.token YOUR_GITHUB_TOKEN
ada config --global github.username YOUR_GITHUB_USERNAME
```

### Working with GitHub

1. **Add a remote repository:**
```bash
ada remote add origin https://github.com/username/repo-name.git
```

2. **Push to GitHub:**
```bash
ada push
```
   - If the repository doesn't exist, Ada will prompt you to create it
   - Say 'y' to create the repository automatically

3. **Pull from GitHub:**
```bash
ada pull
```

4. **View remotes:**
```bash
ada remote
ada remote -v  # Verbose output
```

## Command Reference

### Repository Commands
- `ada init` - Initialize a new ada repository
- `ada add <file>` - Add file to staging area
- `ada commit` - Create a new commit
- `ada status` - Show working tree status
- `ada log` - Show commit history

### Configuration Commands
- `ada config <key> <value>` - Set local config
- `ada config --global <key> <value>` - Set global config
- `ada config --list` - List local config
- `ada config --global --list` - List global config

Common config keys:
- `user.name` - Your name
- `user.email` - Your email
- `github.token` - GitHub personal access token
- `github.username` - GitHub username

### Remote Commands
- `ada remote` - List remotes
- `ada remote -v` - List remotes verbosely
- `ada remote add <name> <url>` - Add a new remote

### Sync Commands
- `ada push` - Push commits to GitHub
- `ada pull` - Pull commits from GitHub

### Help Commands
- `ada --help` - Show help information
- `ada --version` - Show version information

## Project Structure

```
ada/
├── include/          # Header files
│   ├── init.h
│   ├── add.h
│   ├── commit.h
│   ├── status.h
│   ├── log.h
│   ├── config.h
│   ├── remote.h
│   ├── github_auth.h
│   ├── push.h
│   ├── pull.h
│   └── merge.h
├── src/              # Implementation files
│   ├── main.cpp
│   ├── init.cpp
│   ├── add.cpp
│   ├── commit.cpp
│   ├── status.cpp
│   ├── log.cpp
│   ├── config.cpp
│   ├── remote.cpp
│   ├── github_auth.cpp
│   ├── push.cpp
│   ├── pull.cpp
│   └── merge.cpp
├── build/            # Build directory
├── CMakeLists.txt    # Build configuration
├── install.sh        # Installation script
├── uninstall.sh      # Uninstallation script
└── README.md         # This file
```

## How It Works

### Local Repository Structure
When you run `ada init`, it creates a `.ada` directory with:
- `objects/` - Stores file snapshots (hashed)
- `refs/heads/` - Branch references
- `refs/tags/` - Tag references
- `HEAD` - Points to current branch
- `config` - Local repository configuration
- `commits.log` - Commit history

### Global Configuration
Ada stores global configuration in `~/.ada/config`, including:
- User identity (name, email)
- GitHub credentials (token, username)

### GitHub Integration
Ada uses the GitHub REST API to:
- Authenticate users with personal access tokens
- Create repositories programmatically
- Check repository existence
- Synchronize commit data

## Data Structures Used

- **Trees**: Directory structure representation
- **Hash Maps**: Fast object lookup by hash
- **Linked Lists**: Commit history chains
- **DAGs (Directed Acyclic Graphs)**: Branch and merge relationships

## Example Workflow

```bash
# 1. Install Ada globally
./install.sh

# 2. Configure your identity
ada config --global user.name "John Doe"
ada config --global user.email "john@example.com"

# 3. Set up GitHub integration
ada config --global github.token ghp_your_token_here
ada config --global github.username johndoe

# 4. Create a new project
mkdir awesome-project
cd awesome-project
ada init

# 5. Work on your project
echo "# Awesome Project" > README.md
ada add README.md
ada commit
# Type: "Initial commit"

# 6. Connect to GitHub
ada remote add origin https://github.com/johndoe/awesome-project.git

# 7. Push to GitHub
ada push
# Answer 'y' to create the repo if it doesn't exist

# 8. Continue working
echo "More content" >> README.md
ada add README.md
ada commit
# Type: "Update README"
ada push

# 9. Pull latest changes (from another machine or collaborator)
ada pull
```

## Troubleshooting

### Command not found: ada
- Make sure `~/.local/bin` (or `/usr/local/bin`) is in your PATH
- Add to your shell config file:
  ```bash
  # For bash
  echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
  source ~/.bashrc
  
  # For zsh
  echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc
  source ~/.zshrc
  ```
- Verify the binary exists: `ls -la ~/.local/bin/ada`

### Installation fails - Missing dependencies
The installation script will check for required dependencies. Install them based on your system:

**Ubuntu/Debian:**
```bash
sudo apt-get install cmake g++ libcrypto++-dev libcurl4-openssl-dev
```

**Fedora/RHEL/CentOS:**
```bash
sudo dnf install cmake gcc-c++ cryptopp-devel libcurl-devel
```

**Arch Linux:**
```bash
sudo pacman -S cmake gcc crypto++ curl
```

**macOS:**
```bash
brew install cmake gcc cryptopp curl
```

### GitHub authentication failed
- Verify your token is correct: `ada config --global --list`
- Make sure your token has the `repo` scope
- Generate a new token at: https://github.com/settings/tokens
  - Select "Generate new token (classic)"
  - Check the `repo` scope
  - Copy and save the token
  - Set it: `ada config --global github.token YOUR_TOKEN`

### Build errors
- Ensure all dependencies are installed (see above)
- Try a clean rebuild:
  ```bash
  rm -rf build
  ./install.sh
  ```
- Check CMake version: `cmake --version` (needs 3.10+)
- Check C++ compiler: `g++ --version` (needs C++17 support)

### Permission denied during installation
- The script tries to install to `~/.local/bin` first (no sudo needed)
- If it falls back to `/usr/local/bin`, you'll need sudo
- Alternatively, manually specify a writable location:
  ```bash
  mkdir -p ~/bin
  cp build/ada ~/bin/
  export PATH="$HOME/bin:$PATH"
  ```

### Files not being tracked/pushed
- Run `ada status` to see what's staged
- Make sure files are added: `ada add <file>` or `ada add .`
- Commit your changes: `ada commit`
- Then push: `ada push`

## License

This project is created for educational purposes.

## Contributing

Feel free to fork this project and submit pull requests for improvements!

## Author

Created as a demonstration of version control system internals using C++.