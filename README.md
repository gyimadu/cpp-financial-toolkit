# C++ financial toolkit

This is a collection of a couple of C++ projects focused on financial applications, data analysis, and trading tools.

## 🚀 Projects

### 1. Currency Converter (`currency_converter/`)
a real-time currency conversion tool that fetches live exchange rates from external APIs.

**Features:**
- live exchange rate fetching using cURL
- JSON parsing with nlohmann/json library
- input validation and error handling
- currently only supports a few select currencies, initial test currencies

**Technologies Used:**
- C++17 || cURL library for HTTP requests || nlohmann/json for JSON parsing || standard C++ libraries (iostream, string, map)

**Learning Outcomes:**
- HTTP API integration
- JSON data processing
- Callback functions
- Memory management
- Error handling with try-catch
- Modern C++ features (range-based for loops, auto, references)

## 🛠️ Setup and Installation

### Prerequisites
- C++17 compatible compiler (g++ 7.0+ or clang++) ||  cURL library || nlohmann/json library

### Installation on macOS
```bash
# Install dependencies via Homebrew
brew install curl
brew install nlohmann-json

# Clone the repository
git clone https://github.com/yourusername/cpp-financial-toolkit.git
cd cpp-financial-toolkit
```

### Compilation
```bash
# Compile currency converter
cd currency_converter
g++ -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lcurl -o currency_converter main.cpp

# Run the program
./currency_converter
```

## Objectives

Some objectives I explore in this repository are:
- **modern C++ programming**: C++17/20 features, smart pointers, RAII
- **system programming**: memory management, performance optimization
- **API integration**: HTTP requests, JSON parsing, real-time data
- **financial Programming**: mathematical computations, data analysis
- **software architecture**: modular design, error handling, testing

## Testing

I try to include in each project:
- unit tests for core functionality
- integration tests for API calls
- error handling validation
- performance benchmarks

## 🤝Contributing

This is a personal learning repository of projects, but suggestions and improvements are welcome!


**Michael Gyimadu**
- learning C++ and financial programming
- building practical applications

---
