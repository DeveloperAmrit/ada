# Contributing to Ada

Thank you for your interest in contributing to Ada! This guide will help you get started.

## Getting Started

### Fork and Clone

1. Fork the repository on GitHub
2. Clone your fork:
   ```bash
   git clone https://github.com/YOUR_USERNAME/ada.git
   cd ada
   ```

### Build from Source

1. Install dependencies (see README.md for platform-specific commands)
2. Create a build directory:
   ```bash
   mkdir -p build
   cd build
   ```
3. Configure and build:
   ```bash
   cmake ..
   make
   ```

### Install Locally for Testing

```bash
./install.sh
```

This will install Ada to `~/.local/bin` for testing your changes.

## Development Workflow

1. Create a new branch for your feature:
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. Make your changes

3. Test your changes:
   ```bash
   cd build
   make
   # Test the binary
   ./ada --version
   ```

4. Commit your changes:
   ```bash
   git add .
   git commit -m "Description of your changes"
   ```

5. Push to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```

6. Create a Pull Request on GitHub

## Project Structure

```
ada/
├── src/               # Source code
│   ├── main.cpp       # Entry point and command dispatcher
│   ├── init.cpp       # Repository initialization
│   ├── add.cpp        # File staging
│   ├── commit.cpp     # Commit creation
│   ├── status.cpp     # Working tree status
│   ├── log.cpp        # Commit history
│   ├── push.cpp       # GitHub push
│   ├── pull.cpp       # GitHub pull
│   └── merge.cpp      # Branch merging
├── include/           # Header files
├── build/             # Build directory (gitignored)
├── CMakeLists.txt     # CMake configuration
├── install.sh         # Installation script
└── uninstall.sh       # Uninstallation script
```

## Coding Guidelines

- Use C++17 features
- Follow existing code style and formatting
- Use meaningful variable and function names
- Add comments for complex logic
- Handle errors gracefully with informative messages

## Testing Your Changes

Before submitting a pull request, test your changes:

1. **Basic commands:**
   ```bash
   mkdir test-project
   cd test-project
   ada init
   ada config --global user.name "Test User"
   ada config --global user.email "test@example.com"
   echo "test" > test.txt
   ada add test.txt
   ada commit
   ada status
   ada log
   ```

2. **GitHub integration (if applicable):**
   ```bash
   ada github login
   ada remote add origin
   ada push
   ```

## Common Development Tasks

### Rebuild after changes:
```bash
cd build
make
cp ada ~/.local/bin/
```

### Clean build:
```bash
cd build
make clean
cmake ..
make
```

### Uninstall:
```bash
./uninstall.sh
```

## Need Help?

- Check existing issues on GitHub
- Review the README.md for usage examples
- Look at existing source code for examples

## License

By contributing to Ada, you agree that your contributions will be licensed under the same license as the project.
