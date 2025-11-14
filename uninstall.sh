#!/bin/bash

# Ada Version Control System - Uninstallation Script
# This script removes ada from your system

echo "======================================"
echo "Ada Version Control - Uninstallation"
echo "======================================"
echo ""

# Check both possible installation locations
FOUND=false

if [ -f "$HOME/.local/bin/ada" ]; then
    echo "Found ada in $HOME/.local/bin"
    rm -f "$HOME/.local/bin/ada"
    echo "✓ Removed ada from $HOME/.local/bin"
    FOUND=true
fi

if [ -f "/usr/local/bin/ada" ]; then
    echo "Found ada in /usr/local/bin"
    sudo rm -f "/usr/local/bin/ada"
    echo "✓ Removed ada from /usr/local/bin"
    FOUND=true
fi

if [ "$FOUND" = false ]; then
    echo "ada is not installed in the standard locations."
    exit 1
fi

echo ""
echo "Ada has been uninstalled successfully."
echo ""
echo "Note: This does not remove:"
echo "  - Your local .ada repositories"
echo "  - Global config at ~/.ada/config"
echo ""
echo "To remove global config, run: rm -rf ~/.ada"
echo ""
