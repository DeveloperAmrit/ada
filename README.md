# Ada Version Control System# Ada Version Control System



[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)

[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()



Ada is a mini-Git-like version control system that executes Git functions including init, add, commit, status, log, push, pull, and merge. This project uses data structures like trees, hashmaps, linked lists, and directed acyclic graphs (DAGs).Ada is a mini-Git-like version control system that executes Git functions including init, add, commit, status, log, push, pull, and merge. This project uses data structures like trees, hashmaps, linked lists, and directed acyclic graphs (DAGs).



## ⭐ Why Ada?## ⭐ Why Ada?



- **Educational**: Learn how version control systems work internally- **Educational**: Learn how version control systems work internally

- **Lightweight**: Minimal dependencies, easy to understand codebase- **Lightweight**: Minimal dependencies, easy to understand codebase

- **GitHub Integration**: Push and pull directly to/from GitHub- **GitHub Integration**: Push and pull directly to/from GitHub

- **Cross-Platform**: Works on Linux, macOS, and other Unix-like systems- **Cross-Platform**: Works on Linux, macOS, and other Unix-like systems



---## Features



## Table of Contents✅ **Phase 1: Global Installation**

- Install Ada globally on your system (like Git)

1. [Installation](#1-installation)- Works from any directory on your computer

2. [About the Project](#2-about-the-project)- Easy installation and uninstallation scripts

3. [Contributing](#3-contributing)

✅ **Phase 2: GitHub Integration**

---- Authenticate with GitHub using personal access tokens

- Automatically create GitHub repositories

# 1. Installation- Push and pull from GitHub

- Manage remote repositories

## Prerequisites

## 🚀 New to Ada?

Before installing Ada, make sure you have:

- **CMake** (version 3.10 or higher)**→ Start here:** [QUICKSTART.md](QUICKSTART.md) - Get up and running in 5 minutes!

- **C++ compiler** with C++17 support

- **Crypto++** library## Quick Start (Fork & Install)

- **libcurl** library

### 1. Fork the Repository

## Step-by-Step Installation

Click the "Fork" button on GitHub to create your own copy of Ada.

### Step 1: Fork and Clone

### 2. Clone Your Fork

1. Fork this repository by clicking the "Fork" button on GitHub

2. Clone your fork:```bash

git clone https://github.com/YOUR_USERNAME/ada.git

```bashcd ada

git clone https://github.com/YOUR_USERNAME/ada.git```

cd ada

```### 3. Install Dependencies



### Step 2: Install Dependencies**Ubuntu/Debian:**

```bash

Choose the commands for your operating system:sudo apt-get update

sudo apt-get install cmake g++ libcrypto++-dev libcurl4-openssl-dev

**Ubuntu/Debian:**```

```bash

sudo apt-get update**Fedora/RHEL:**

sudo apt-get install cmake g++ libcrypto++-dev libcurl4-openssl-dev```bash

```sudo dnf install cmake gcc-c++ cryptopp-devel libcurl-devel

```

**Fedora/RHEL/CentOS:**

```bash**Arch Linux:**

sudo dnf install cmake gcc-c++ cryptopp-devel libcurl-devel```bash

```sudo pacman -S cmake gcc crypto++ curl

```

**Arch Linux:**

```bash**macOS (with Homebrew):**

sudo pacman -S cmake gcc crypto++ curl```bash

```brew install cmake gcc cryptopp curl

```

**macOS (with Homebrew):**

```bash### 4. Run the Installation Script

brew install cmake gcc cryptopp curl

``````bash

chmod +x install.sh

### Step 3: Run the Installation Script./install.sh

```

```bash

chmod +x install.shThe script will:

./install.sh- ✓ Check all dependencies

```- ✓ Build the Ada binary

- ✓ Install it to `~/.local/bin` (no sudo required) or `/usr/local/bin`

The installation script will:- ✓ Make it available globally on your system

- ✓ Check all required dependencies

- ✓ Build the Ada binary using CMake### 5. Update Your PATH (if needed)

- ✓ Install it to `~/.local/bin` (no sudo required) or `/usr/local/bin`

- ✓ Make it available globally on your systemIf the installer warns that `~/.local/bin` is not in your PATH:



### Step 4: Update Your PATH (if needed)```bash

echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc

If the installer warns that `~/.local/bin` is not in your PATH, add it:source ~/.bashrc

```

**For bash:**

```bashFor zsh users:

echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc```bash

source ~/.bashrcecho 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc

```source ~/.zshrc

```

**For zsh:**

```bash### 6. Verify Installation

echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc

source ~/.zshrc```bash

```ada --version

```

### Step 5: Verify Installation

You should see: `Ada version control system v1.0`

```bash

ada --version## Installation

```

### Prerequisites

You should see: `ada version 1.0.0`

Before installing Ada, make sure you have:

## Uninstallation- CMake (version 3.10 or higher)

- C++ compiler with C++17 support

To remove Ada from your system:- Crypto++ library

- libcurl library

```bash

chmod +x uninstall.shSee the "Quick Start" section above for platform-specific installation commands.

./uninstall.sh

```## Uninstallation



## Troubleshooting InstallationTo remove Ada from your system:

```bash

### Command not found: adachmod +x uninstall.sh

./uninstall.sh

Make sure `~/.local/bin` (or `/usr/local/bin`) is in your PATH:```



```bash## Getting Started

# Check if it's in PATH

echo $PATH | grep -o "$HOME/.local/bin"### Basic Usage



# If not, add it1. **Initialize a repository:**

echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc```bash

source ~/.bashrcmkdir my-project

cd my-project

# Verify the binary existsada init

ls -la ~/.local/bin/ada```

```

2. **Configure your identity:**

### Missing Dependencies```bash

ada config --global user.name "Your Name"

If the installation script reports missing dependencies, install them manually:ada config --global user.email "your.email@example.com"

```

**Ubuntu/Debian:**

```bash3. **Add files and commit:**

sudo apt-get install cmake g++ libcrypto++-dev libcurl4-openssl-dev```bash

```echo "Hello World" > hello.txt

ada add hello.txt

**Fedora/RHEL:**ada commit

```bash# Enter commit message when prompted

sudo dnf install cmake gcc-c++ cryptopp-devel libcurl-devel```

```

4. **Check status:**

**Arch Linux:**```bash

```bashada status

sudo pacman -S cmake gcc crypto++ curl```

```

5. **View commit history:**

**macOS:**```bash

```bashada log

brew install cmake gcc cryptopp curl```

```

## GitHub Integration

### Build Errors

### Setup GitHub Authentication

If you encounter build errors:

1. **Create a GitHub Personal Access Token:**

1. **Clean and rebuild:**   - Go to https://github.com/settings/tokens

   ```bash   - Click "Generate new token" → "Generate new token (classic)"

   rm -rf build   - Give it a name (e.g., "Ada VCS")

   ./install.sh   - Select scopes: `repo` (Full control of private repositories)

   ```   - Click "Generate token"

   - **Copy the token** (you won't see it again!)

2. **Check versions:**

   ```bash2. **Configure Ada with your GitHub credentials:**

   cmake --version  # Should be 3.10+```bash

   g++ --version    # Should support C++17ada config --global github.token YOUR_GITHUB_TOKEN

   ```ada config --global github.username YOUR_GITHUB_USERNAME

```

3. **Manual build for debugging:**

   ```bash### Working with GitHub

   mkdir -p build && cd build

   cmake ..1. **Add a remote repository:**

   make VERBOSE=1```bash

   ```ada remote add origin https://github.com/username/repo-name.git

```

### Permission Denied

2. **Push to GitHub:**

If installation fails due to permissions:```bash

ada push

```bash```

# Install to a user-writable location   - If the repository doesn't exist, Ada will prompt you to create it

mkdir -p ~/bin   - Say 'y' to create the repository automatically

cd build

cp ada ~/bin/3. **Pull from GitHub:**

echo 'export PATH="$HOME/bin:$PATH"' >> ~/.bashrc```bash

source ~/.bashrcada pull

``````



---4. **View remotes:**

```bash

# 2. About the Projectada remote

ada remote -v  # Verbose output

## Quick Start Guide```



### 1. Initialize a Repository## Command Reference



```bash### Repository Commands

mkdir my-project- `ada init` - Initialize a new ada repository

cd my-project- `ada add <file>` - Add file to staging area

ada init- `ada commit` - Create a new commit

```- `ada status` - Show working tree status

- `ada log` - Show commit history

### 2. Configure Your Identity

### Configuration Commands

```bash- `ada config <key> <value>` - Set local config

ada config --global user.name "Your Name"- `ada config --global <key> <value>` - Set global config

ada config --global user.email "your.email@example.com"- `ada config --list` - List local config

```- `ada config --global --list` - List global config



### 3. Add Files and CommitCommon config keys:

- `user.name` - Your name

```bash- `user.email` - Your email

# Create a file- `github.token` - GitHub personal access token

echo "# My Project" > README.md- `github.username` - GitHub username



# Stage the file### Remote Commands

ada add README.md- `ada remote` - List remotes

- `ada remote -v` - List remotes verbosely

# Or stage all files recursively- `ada remote add <name> <url>` - Add a new remote

ada add .

### Sync Commands

# Commit- `ada push` - Push commits to GitHub

ada commit- `ada pull` - Pull commits from GitHub

# Enter commit message when prompted: "Initial commit"

```### Help Commands

- `ada --help` - Show help information

### 4. Check Status- `ada --version` - Show version information



```bash## Project Structure

ada status

``````

ada/

### 5. View Commit History├── include/          # Header files

│   ├── init.h

```bash│   ├── add.h

ada log│   ├── commit.h

```│   ├── status.h

│   ├── log.h

## GitHub Integration│   ├── config.h

│   ├── remote.h

### Setup GitHub Authentication│   ├── github_auth.h

│   ├── push.h

1. **Create a Personal Access Token:**│   ├── pull.h

   - Go to https://github.com/settings/tokens│   └── merge.h

   - Click "Generate new token (classic)"├── src/              # Implementation files

   - Give it a name (e.g., "Ada VCS")│   ├── main.cpp

   - Select the `repo` scope│   ├── init.cpp

   - Click "Generate token"│   ├── add.cpp

   - **Copy the token** (you won't see it again!)│   ├── commit.cpp

│   ├── status.cpp

2. **Configure Ada with your token:**│   ├── log.cpp

   ```bash│   ├── config.cpp

   ada config --global github.token YOUR_TOKEN_HERE│   ├── remote.cpp

   ada config --global github.username YOUR_GITHUB_USERNAME│   ├── github_auth.cpp

   ```│   ├── push.cpp

│   ├── pull.cpp

### Connect to GitHub Repository│   └── merge.cpp

├── build/            # Build directory

1. **Create a repository on GitHub** (or use existing one)├── CMakeLists.txt    # Build configuration

├── install.sh        # Installation script

2. **Add remote:**├── uninstall.sh      # Uninstallation script

   ```bash└── README.md         # This file

   ada remote add origin https://github.com/YOUR_USERNAME/your-repo.git```

   ```

## How It Works

3. **Push to GitHub:**

   ```bash### Local Repository Structure

   ada pushWhen you run `ada init`, it creates a `.ada` directory with:

   ```- `objects/` - Stores file snapshots (hashed)

   - If the repository doesn't exist, Ada will ask if you want to create it- `refs/heads/` - Branch references

- `refs/tags/` - Tag references

4. **Pull from GitHub:**- `HEAD` - Points to current branch

   ```bash- `config` - Local repository configuration

   ada pull- `commits.log` - Commit history

   ```

### Global Configuration

## Complete Workflow ExampleAda stores global configuration in `~/.ada/config`, including:

- User identity (name, email)

```bash- GitHub credentials (token, username)

# 1. Create and initialize project

mkdir awesome-app && cd awesome-app### GitHub Integration

ada initAda uses the GitHub REST API to:

- Authenticate users with personal access tokens

# 2. Configure (first time only)- Create repositories programmatically

ada config --global user.name "Jane Developer"- Check repository existence

ada config --global user.email "jane@example.com"- Synchronize commit data



# 3. Create files## Data Structures Used

echo "console.log('Hello World');" > app.js

echo "# Awesome App" > README.md- **Trees**: Directory structure representation

- **Hash Maps**: Fast object lookup by hash

# 4. Stage all files- **Linked Lists**: Commit history chains

ada add .- **DAGs (Directed Acyclic Graphs)**: Branch and merge relationships



# 5. Commit## Example Workflow

ada commit

# Message: "Initial commit"```bash

# 1. Install Ada globally

# 6. Check status./install.sh

ada status

# 2. Configure your identity

# 7. Make changesada config --global user.name "John Doe"

echo "console.log('Updated!');" >> app.jsada config --global user.email "john@example.com"



# 8. See what changed# 3. Set up GitHub integration

ada statusada config --global github.token ghp_your_token_here

ada config --global github.username johndoe

# 9. Stage and commit

ada add app.js# 4. Create a new project

ada commitmkdir awesome-project

# Message: "Update app.js"cd awesome-project

ada init

# 10. View history

ada log# 5. Work on your project

echo "# Awesome Project" > README.md

# 11. Setup GitHub (if not done already)ada add README.md

ada config --global github.token ghp_your_tokenada commit

ada config --global github.username yourusername# Type: "Initial commit"



# 12. Add remote# 6. Connect to GitHub

ada remote add origin https://github.com/yourusername/awesome-app.gitada remote add origin https://github.com/johndoe/awesome-project.git



# 13. Push to GitHub# 7. Push to GitHub

ada pushada push

```# Answer 'y' to create the repo if it doesn't exist



## Command Reference# 8. Continue working

echo "More content" >> README.md

### Repository Commandsada add README.md

ada commit

| Command | Description |# Type: "Update README"

|---------|-------------|ada push

| `ada init` | Initialize a new Ada repository in current directory |

| `ada add <file>` | Add specific file to staging area |# 9. Pull latest changes (from another machine or collaborator)

| `ada add .` | Add all files recursively to staging area |ada pull

| `ada commit` | Create a new commit (prompts for message) |```

| `ada status` | Show working tree status (staged, modified, untracked files) |

| `ada log` | Display commit history |## Troubleshooting



### Configuration Commands### Command not found: ada

- Make sure `~/.local/bin` (or `/usr/local/bin`) is in your PATH

| Command | Description |- Add to your shell config file:

|---------|-------------|  ```bash

| `ada config <key> <value>` | Set local configuration |  # For bash

| `ada config --global <key> <value>` | Set global configuration |  echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc

| `ada config --list` | List local configuration |  source ~/.bashrc

| `ada config --global --list` | List global configuration |  

  # For zsh

**Common configuration keys:**  echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc

- `user.name` - Your name (for commits)  source ~/.zshrc

- `user.email` - Your email (for commits)  ```

- `github.token` - GitHub personal access token- Verify the binary exists: `ls -la ~/.local/bin/ada`

- `github.username` - GitHub username

### Installation fails - Missing dependencies

### Remote CommandsThe installation script will check for required dependencies. Install them based on your system:



| Command | Description |**Ubuntu/Debian:**

|---------|-------------|```bash

| `ada remote` | List configured remotes |sudo apt-get install cmake g++ libcrypto++-dev libcurl4-openssl-dev

| `ada remote -v` | List remotes with URLs (verbose) |```

| `ada remote add <name> <url>` | Add a new remote repository |

**Fedora/RHEL/CentOS:**

**Example:**```bash

```bashsudo dnf install cmake gcc-c++ cryptopp-devel libcurl-devel

ada remote add origin https://github.com/username/repo.git```

```

**Arch Linux:**

### Sync Commands```bash

sudo pacman -S cmake gcc crypto++ curl

| Command | Description |```

|---------|-------------|

| `ada push` | Push local commits to GitHub |**macOS:**

| `ada pull` | Pull commits from GitHub to local repository |```bash

brew install cmake gcc cryptopp curl

### Help Commands```



| Command | Description |### GitHub authentication failed

|---------|-------------|- Verify your token is correct: `ada config --global --list`

| `ada --help` | Show help information |- Make sure your token has the `repo` scope

| `ada --version` | Show Ada version |- Generate a new token at: https://github.com/settings/tokens

  - Select "Generate new token (classic)"

## Understanding Ada Status Output  - Check the `repo` scope

  - Copy and save the token

When you run `ada status`, you'll see files categorized as:  - Set it: `ada config --global github.token YOUR_TOKEN`



- **Changes to be committed** (staged files):### Build errors

  - `new file:` - File doesn't exist in last commit- Ensure all dependencies are installed (see above)

  - `modified:` - File exists in last commit but has changes- Try a clean rebuild:

  ```bash

- **Changes not staged for commit**:  rm -rf build

  - `modified:` - File is tracked but has unstaged changes  ./install.sh

  ```

- **Untracked files**:- Check CMake version: `cmake --version` (needs 3.10+)

  - Files that Ada isn't tracking yet- Check C++ compiler: `g++ --version` (needs C++17 support)



- **Deleted files**:### Permission denied during installation

  - `deleted:` - File was in last commit but no longer exists- The script tries to install to `~/.local/bin` first (no sudo needed)

- If it falls back to `/usr/local/bin`, you'll need sudo

## Project Structure- Alternatively, manually specify a writable location:

  ```bash

```  mkdir -p ~/bin

ada/  cp build/ada ~/bin/

├── include/              # Header files  export PATH="$HOME/bin:$PATH"

│   ├── init.h           # Repository initialization  ```

│   ├── add.h            # File staging

│   ├── commit.h         # Commit creation### Files not being tracked/pushed

│   ├── status.h         # Status checking- Run `ada status` to see what's staged

│   ├── log.h            # History viewing- Make sure files are added: `ada add <file>` or `ada add .`

│   ├── config.h         # Configuration management- Commit your changes: `ada commit`

│   ├── remote.h         # Remote repository management- Then push: `ada push`

│   ├── github_auth.h    # GitHub authentication

│   ├── push.h           # Push to GitHub## License

│   ├── pull.h           # Pull from GitHub

│   └── merge.h          # Branch mergingThis project is created for educational purposes.

├── src/                 # Implementation files

│   ├── main.cpp         # Entry point and command dispatcher## Contributing

│   ├── init.cpp         # Initialize .ada directory structure

│   ├── add.cpp          # Stage files with SHA-1 hashingFeel free to fork this project and submit pull requests for improvements!

│   ├── commit.cpp       # Create commit objects

│   ├── status.cpp       # Calculate working tree status## Author

│   ├── log.cpp          # Display commit history

│   ├── config.cpp       # Read/write config filesCreated as a demonstration of version control system internals using C++.
│   ├── remote.cpp       # Manage GitHub remotes
│   ├── github_auth.cpp  # GitHub API authentication
│   ├── push.cpp         # Upload files to GitHub
│   ├── pull.cpp         # Download from GitHub
│   └── merge.cpp        # Merge branches
├── build/               # Build directory (gitignored)
├── CMakeLists.txt       # CMake build configuration
├── install.sh           # Installation script
├── uninstall.sh         # Uninstallation script
├── LICENSE              # MIT License
└── README.md            # This file
```

## How Ada Works Internally

Ada uses a `.ada` directory (similar to `.git`) to store:

- **objects/** - Hashed file contents and commit objects
- **refs/** - References to commits (branches)
- **index** - Staging area (files ready to commit)
- **commits.log** - Log of all commits
- **config** - Local repository configuration

**File Hashing:** Ada uses SHA-1 hashing (via Crypto++) to create unique identifiers for file contents.

**Commit Objects:** Each commit contains:
- Commit hash (unique identifier)
- Author name and email
- Timestamp
- Commit message
- List of files with their hashes

**GitHub Integration:** Ada uses the GitHub REST API to:
- Create repositories
- Upload files (via Contents API with base64 encoding)
- Download files
- Authenticate with personal access tokens

## Troubleshooting Common Issues

### GitHub Authentication Failed

```bash
# Verify your configuration
ada config --global --list

# Make sure you see:
# github.token=ghp_...
# github.username=yourusername

# If missing, set them:
ada config --global github.token YOUR_TOKEN
ada config --global github.username YOUR_USERNAME
```

### Files Not Being Tracked/Pushed

```bash
# Check what's staged
ada status

# Add files if needed
ada add <file>
# or
ada add .

# Commit your changes
ada commit

# Then push
ada push
```

### Repository Not Found on GitHub

Make sure:
1. The repository exists on GitHub
2. The remote URL is correct: `ada remote -v`
3. Your GitHub username and token are configured
4. Your token has the `repo` scope

### Commit Message Not Saved

Ada prompts for a commit message interactively. Make sure to:
1. Type your message
2. Press Enter to create a new line with a single `.`
3. Press Enter again to save

---

# 3. Contributing

Thank you for your interest in contributing to Ada! We welcome contributions from everyone.

## Getting Started with Development

### 1. Fork and Clone

```bash
# Fork the repository on GitHub, then:
git clone https://github.com/YOUR_USERNAME/ada.git
cd ada
```

### 2. Install Dependencies

See the [Installation](#1-installation) section for platform-specific dependency installation.

### 3. Build from Source

```bash
# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake ..

# Build
make

# Test the binary
./ada --version
```

### 4. Install Locally for Testing

```bash
# From the project root
./install.sh
```

This installs to `~/.local/bin` so you can test your changes globally.

## Development Workflow

1. **Create a feature branch:**
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make your changes** in the appropriate files:
   - Header files: `include/`
   - Implementation: `src/`

3. **Build and test:**
   ```bash
   cd build
   make
   ./ada --version
   
   # Test with a sample project
   mkdir /tmp/test-ada
   cd /tmp/test-ada
   ada init
   # ... test your changes
   ```

4. **Rebuild and reinstall for testing:**
   ```bash
   cd /path/to/ada/build
   make
   cp ada ~/.local/bin/
   ```

5. **Commit your changes:**
   ```bash
   git add .
   git commit -m "Description of your changes"
   ```

6. **Push to your fork:**
   ```bash
   git push origin feature/your-feature-name
   ```

7. **Create a Pull Request** on GitHub

## Coding Guidelines

### Code Style

- Use **C++17** features and standards
- Follow existing code formatting and style
- Use **meaningful variable and function names**
- Add **comments** for complex logic
- Keep functions **focused and modular**

### Error Handling

- Handle errors gracefully
- Provide **informative error messages** to users
- Check for file I/O errors, invalid inputs, etc.

### Example Code Style

```cpp
// Good: Clear function name, error handling
bool addFileToIndex(const std::string& filepath) {
    if (!std::filesystem::exists(filepath)) {
        std::cerr << "Error: File '" << filepath << "' does not exist\n";
        return false;
    }
    
    // Hash the file content
    std::string hash = calculateSHA1(filepath);
    
    // Add to index
    // ...
    
    return true;
}
```

## Testing Your Changes

Before submitting a pull request, thoroughly test:

### Basic Functionality

```bash
mkdir test-project && cd test-project
ada init
ada config --global user.name "Test User"
ada config --global user.email "test@example.com"

# Test add
echo "test content" > test.txt
ada add test.txt
ada status  # Should show test.txt as staged

# Test commit
ada commit
# Enter message: "Test commit"
ada log  # Should show the commit

# Test status with modifications
echo "more content" >> test.txt
ada status  # Should show test.txt as modified

# Test add .
mkdir subdir
echo "file in subdir" > subdir/file.txt
ada add .
ada status  # Should show both files staged
```

### GitHub Integration (if applicable)

```bash
ada config --global github.token YOUR_TEST_TOKEN
ada config --global github.username YOUR_USERNAME
ada remote add origin https://github.com/YOUR_USERNAME/test-repo.git
ada push
# Verify files appear on GitHub
```

## Common Development Tasks

### Clean Build

```bash
cd build
make clean
cmake ..
make
```

### Full Rebuild

```bash
rm -rf build
mkdir build && cd build
cmake ..
make
```

### Debug Build

```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Check for Compilation Warnings

```bash
cd build
cmake ..
make VERBOSE=1 2>&1 | grep -i warning
```

## Areas for Contribution

We welcome contributions in these areas:

### Features
- Branch management (create, switch, list branches)
- Diff command to show file changes
- `.gitignore` style file ignore patterns
- Interactive rebase
- Stash functionality

### Improvements
- Better error messages
- Performance optimizations
- Cross-platform compatibility (Windows support)
- Unit tests
- Documentation improvements

### Bug Fixes
- Check the GitHub Issues for reported bugs
- Test edge cases and fix any issues found

## Project Architecture

### Command Flow

1. `main.cpp` - Parses command line arguments
2. Dispatches to appropriate handler (init, add, commit, etc.)
3. Handler functions read/write to `.ada` directory
4. GitHub commands use libcurl to make API requests

### Key Components

- **Hashing**: Uses Crypto++ SHA-1 for content addressing
- **Storage**: File-based object storage in `.ada/objects/`
- **Index**: Tracks staged files in `.ada/index`
- **Config**: Global config in `~/.ada/config`, local in `.ada/config`
- **GitHub API**: RESTful API calls with token authentication

## Submitting Pull Requests

### Before Submitting

- ✓ Code builds without errors or warnings
- ✓ Changes are tested with real usage scenarios
- ✓ Code follows the project's style guidelines
- ✓ Commit messages are clear and descriptive

### Pull Request Guidelines

1. **Title**: Clear, concise description of changes
2. **Description**: Explain what changed and why
3. **Testing**: Describe how you tested the changes
4. **Breaking Changes**: Note any breaking changes

### Example PR Description

```
## What Changed
- Added support for branch creation and switching
- Implemented `ada branch` and `ada checkout` commands

## Why
- Users requested ability to work on multiple features simultaneously
- Branches are a core VCS feature

## How Tested
- Created new branches with `ada branch feature1`
- Switched branches with `ada checkout feature1`
- Verified commits go to correct branch
- Tested with multiple branches

## Breaking Changes
None
```

## Getting Help

- **Questions?** Open a GitHub issue with the "question" label
- **Found a bug?** Open a GitHub issue with the "bug" label
- **Want to discuss a feature?** Open a GitHub issue with the "enhancement" label

## Code of Conduct

- Be respectful and inclusive
- Provide constructive feedback
- Focus on the code, not the person
- Help others learn and grow

## License

By contributing to Ada, you agree that your contributions will be licensed under the MIT License.

---

## Additional Resources

- **C++17 Documentation**: https://en.cppreference.com/w/cpp/17
- **CMake Documentation**: https://cmake.org/documentation/
- **GitHub REST API**: https://docs.github.com/en/rest
- **Crypto++ Library**: https://www.cryptopp.com/

---

## Author

Created as an educational project to demonstrate version control system internals.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Happy Coding! 🚀**

If you find Ada useful, please give it a ⭐ on GitHub!
