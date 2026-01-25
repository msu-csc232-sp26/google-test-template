#!/usr/bin/env bash
set -e

echo "Waiting for VS Code to configure the project..."

# Wait until VS Code creates the build directory
while [ ! -d "build" ]; do
    sleep 1
done

echo "VS Code has configured the project."

echo "Building Doxygen documentation..."
cmake --build build --target doc_doxygen || true

echo "Opening documentation in Live Server..."
code --open-url http://localhost:5500/index.html
