#!/bin/bash

# Ada Version Control System - Installation Script
# This script builds and installs ada globally on your system

set -e

echo "==================================="
echo "Ada Version Control - Installation"
echo "==================================="
echo ""

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

echo "Installing from: $SCRIPT_DIR"
echo ""

# Function to check if a command exists
command_exists() {
    command -v "$1" &> /dev/null
}

# Function to detect package manager
detect_package_manager() {
    if command_exists apt-get; then
        echo "apt"
    elif command_exists yum; then
        echo "yum"
    elif command_exists dnf; then
        echo "dnf"
    elif command_exists pacman; then
        echo "pacman"
    elif command_exists brew; then
        echo "brew"
    else
        echo "unknown"
    fi
}

# Check for required tools
echo "Checking dependencies..."

# Check if cmake is installed
if ! command_exists cmake; then
    echo "Error: cmake is not installed."
    echo "Please install cmake first:"
    PKG_MGR=$(detect_package_manager)
    case $PKG_MGR in
        apt)     echo "  sudo apt-get install cmake" ;;
        yum|dnf) echo "  sudo $PKG_MGR install cmake" ;;
        pacman)  echo "  sudo pacman -S cmake" ;;
        brew)    echo "  brew install cmake" ;;
        *)       echo "  Please install cmake using your package manager" ;;
    esac
    exit 1
fi

# Check if g++ is installed
if ! command_exists g++; then
    echo "Error: g++ compiler is not installed."
    echo "Please install g++ first:"
    PKG_MGR=$(detect_package_manager)
    case $PKG_MGR in
        apt)     echo "  sudo apt-get install g++" ;;
        yum|dnf) echo "  sudo $PKG_MGR install gcc-c++" ;;
        pacman)  echo "  sudo pacman -S gcc" ;;
        brew)    echo "  brew install gcc" ;;
        *)       echo "  Please install g++ using your package manager" ;;
    esac
    exit 1
fi

# Check if cryptopp is installed
if [ ! -f "/usr/include/cryptopp/sha.h" ] && [ ! -f "/usr/local/include/cryptopp/sha.h" ] && [ ! -f "/opt/homebrew/include/cryptopp/sha.h" ]; then
    echo "Error: Crypto++ library not found."
    echo "Please install it first:"
    PKG_MGR=$(detect_package_manager)
    case $PKG_MGR in
        apt)     echo "  sudo apt-get install libcrypto++-dev" ;;
        yum|dnf) echo "  sudo $PKG_MGR install cryptopp-devel" ;;
        pacman)  echo "  sudo pacman -S crypto++" ;;
        brew)    echo "  brew install cryptopp" ;;
        *)       echo "  Please install Crypto++ library using your package manager" ;;
    esac
    exit 1
fi

# Check if libcurl is installed
if ! command_exists curl-config && [ ! -f "/usr/include/curl/curl.h" ] && [ ! -f "/usr/local/include/curl/curl.h" ] && [ ! -f "/opt/homebrew/include/curl/curl.h" ]; then
    echo "Error: libcurl development library not found."
    echo "Please install it first:"
    PKG_MGR=$(detect_package_manager)
    case $PKG_MGR in
        apt)     echo "  sudo apt-get install libcurl4-openssl-dev" ;;
        yum|dnf) echo "  sudo $PKG_MGR install libcurl-devel" ;;
        pacman)  echo "  sudo pacman -S curl" ;;
        brew)    echo "  brew install curl" ;;
        *)       echo "  Please install libcurl development library using your package manager" ;;
    esac
    exit 1
fi

echo "✓ All dependencies found!"
echo ""

# Create build directory if it doesn't exist
echo "Creating build directory..."
mkdir -p build
cd build

# Configure with CMake
echo "Configuring project with CMake..."
cmake ..

# Build the project
echo "Building ada..."
make

# Check if build was successful
if [ ! -f "ada" ]; then
    echo "Error: Build failed. ada binary not found."
    exit 1
fi

echo ""
echo "Build successful!"
echo ""

# Determine installation directory
# Prefer ~/.local/bin if it exists or can be created (no sudo required)
# Otherwise use /usr/local/bin (requires sudo)

if [ -w "$HOME/.local/bin" ] || mkdir -p "$HOME/.local/bin" 2>/dev/null; then
    INSTALL_DIR="$HOME/.local/bin"
    NEED_SUDO=false
else
    INSTALL_DIR="/usr/local/bin"
    NEED_SUDO=true
fi

echo "Installing ada to $INSTALL_DIR..."

# Copy the binary
if [ "$NEED_SUDO" = true ]; then
    sudo cp ada "$INSTALL_DIR/ada"
    sudo chmod +x "$INSTALL_DIR/ada"
else
    cp ada "$INSTALL_DIR/ada"
    chmod +x "$INSTALL_DIR/ada"
fi

echo ""
echo "✓ Installation complete!"
echo ""

# Check if the installation directory is in PATH
if [[ ":$PATH:" == *":$INSTALL_DIR:"* ]]; then
    echo "ada is ready to use!"
else
    echo "Warning: $INSTALL_DIR is not in your PATH"
    echo "Add this line to your ~/.bashrc or ~/.zshrc:"
    echo "    export PATH=\"$INSTALL_DIR:\$PATH\""
    echo ""
    echo "Then run: source ~/.bashrc (or source ~/.zshrc)"
fi

echo ""
echo "Test the installation by running: ada --version"
echo "Or run: ada init"
echo ""
