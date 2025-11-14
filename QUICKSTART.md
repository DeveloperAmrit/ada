# Quick Start Guide - Ada VCS

Welcome to Ada! This guide will get you up and running in 5 minutes.

## Step 1: Install Ada

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/ada.git
cd ada

# Install dependencies (Ubuntu/Debian example)
sudo apt-get update
sudo apt-get install cmake g++ libcrypto++-dev libcurl4-openssl-dev

# Run the installation script
chmod +x install.sh
./install.sh
```

## Step 2: Configure Ada

```bash
# Set your name and email
ada config --global user.name "Your Name"
ada config --global user.email "your.email@example.com"
```

## Step 3: Create Your First Repository

```bash
# Create a new project folder
mkdir my-first-project
cd my-first-project

# Initialize Ada repository
ada init
```

## Step 4: Make Your First Commit

```bash
# Create a file
echo "# My First Project" > README.md

# Add it to staging
ada add README.md

# Commit (you'll be prompted for a message)
ada commit
# Type: "Initial commit" when prompted
```

## Step 5: Check Status and History

```bash
# View current status
ada status

# View commit history
ada log
```

## Step 6 (Optional): Push to GitHub

### 6a. Set up GitHub authentication

1. Create a GitHub Personal Access Token:
   - Go to https://github.com/settings/tokens
   - Click "Generate new token (classic)"
   - Give it a name like "Ada VCS"
   - Select the `repo` scope
   - Click "Generate token"
   - **Copy the token** (you won't see it again!)

2. Configure Ada with your token:
   ```bash
   ada config --global github.token YOUR_TOKEN_HERE
   ada config --global github.username YOUR_GITHUB_USERNAME
   ```

### 6b. Create a repository on GitHub

1. Go to https://github.com/new
2. Create a repository named "my-first-project"
3. Don't initialize it with anything (no README, no .gitignore)

### 6c. Connect and push

```bash
# Add the remote repository
ada remote add origin https://github.com/YOUR_USERNAME/my-first-project.git

# Push your commits
ada push
```

## Common Commands Cheat Sheet

| Command | Description |
|---------|-------------|
| `ada init` | Initialize a new repository |
| `ada add <file>` | Stage a specific file |
| `ada add .` | Stage all files in current directory |
| `ada commit` | Create a new commit |
| `ada status` | Show what's staged/modified/untracked |
| `ada log` | View commit history |
| `ada remote add origin <url>` | Add a GitHub remote |
| `ada push` | Push commits to GitHub |
| `ada pull` | Pull commits from GitHub |
| `ada --help` | Show help information |

## Example Workflow

```bash
# 1. Initialize
mkdir awesome-app && cd awesome-app
ada init

# 2. Configure (first time only)
ada config --global user.name "Jane Developer"
ada config --global user.email "jane@example.com"

# 3. Create files
echo "console.log('Hello World');" > app.js
echo "# Awesome App" > README.md

# 4. Stage all files
ada add .

# 5. Commit
ada commit
# Enter: "Initial commit with app.js and README"

# 6. Make changes
echo "console.log('Updated!');" >> app.js

# 7. Check what changed
ada status

# 8. Stage and commit changes
ada add app.js
ada commit
# Enter: "Update app.js with new feature"

# 9. View history
ada log
```

## Need Help?

- **Full documentation**: See [README.md](README.md)
- **Contributing**: See [CONTRIBUTING.md](CONTRIBUTING.md)
- **Troubleshooting**: Check the Troubleshooting section in README.md
- **Issues**: Open an issue on GitHub

## What Makes Ada Different?

Ada is a **learning tool** that shows you how version control works under the hood:
- ✓ Simple C++ codebase you can read and understand
- ✓ Direct GitHub integration without Git
- ✓ Perfect for understanding VCS internals
- ✓ Minimal dependencies, easy to build

Happy coding! 🚀
