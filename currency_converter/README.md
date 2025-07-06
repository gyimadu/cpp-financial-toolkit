# Currency Converter

A real-time currency conversion tool built in C++ that fetches live exchange rates from external APIs. This project demonstrates modern C++ programming concepts including HTTP requests, JSON parsing, and error handling.

## Features

- **Live Exchange Rates**: fetches real-time rates from exchangerate-api.com
- **Multiple Currencies**: supports a few major world currencies (USD, EUR, GBP, JPY, etc.)
- **Input Validation**: error handling for user input
- **Cross-platform**: works on macOS, Linux, and Windows

## 🛠️ Technologies Used

- **C++17**: modern C++ standard with advanced features
- **cURL**: HTTP client library for API requests
- **nlohmann/json**: JSON parsing library
- **Standard C++ Libraries**: iostream, string, map, iomanip

## 📋 Prerequisites

### macOS
```bash
# Install Homebrew if you haven't already
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required libraries
brew install curl
brew install nlohmann-json
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev nlohmann-json3-dev g++
```

### Windows
- Install MinGW or Visual Studio
- Download cURL and nlohmann/json libraries
- Configure include and library paths

## 🔧 Compilation

### macOS/Linux
```bash
# Navigate to the project directory
cd currency_converter

# Compile the program
g++ -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lcurl -o currency_converter main.cpp

# Run the program
./currency_converter
```

### Windows (MinGW)
```bash
g++ -std=c++17 -I"C:\path\to\curl\include" -I"C:\path\to\json\include" -L"C:\path\to\curl\lib" -lcurl -o currency_converter.exe main.cpp
```

## Usage

1. **Run the program:**
   ```bash
   ./currency_converter
   ```

2. **Choose an option:**
   - `1` - Convert currency
   - `2` - View supported currencies
   - `3` - Exit

3. **For currency conversion:**
   - Enter the amount to convert
   - Enter source currency (e.g., USD, EUR, GBP)
   - Enter target currency (e.g., EUR, JPY, CAD)
   - View the conversion result

## Supported currencies

- **USD** - US Dollar
- **EUR** - Euro
- **GBP** - British Pound
- **JPY** - Japanese Yen
- **CAD** - Canadian Dollar
- **AUD** - Australian Dollar
- **CHF** - Swiss Franc
- **CNY** - Chinese Yuan
- many more to be added

## Code ctructure

### Key functions

1. **`main()`**: Program entry point and menu system
2. **`performConversion()`**: Core conversion logic
3. **`fetchExchangeRates()`**: API integration and data fetching
4. **`WriteCallback()`**: cURL callback for handling HTTP responses
5. **`getUserAmount()`**: Input validation for amounts
6. **`getUserCurrency()`**: Input validation for currency codes

### Important Concepts Demonstrated

- **HTTP requests**: using cURL library for API calls
- **JSON parsing**: converting API responses to C++ data structures
- **Callback functions**: handling asynchronous data reception
- **Error handling**: try-catch blocks and input validation
- **Memory management**: proper cleanup of cURL resources
- **Modern C++**: range-based for loops, auto, references

## Testing

### Manual Testing
```bash
# Test basic functionality
./currency_converter
# Choose option 1
# Enter: 100
# Enter: USD
# Enter: EUR
# Verify conversion result

# Test error handling
./currency_converter
# Choose option 1
# Enter: abc (should show error)
# Enter: -50 (should show error)
# Enter: USD
# Enter: INVALID (should show available currencies)
```

### API testing
The program uses the [exchangerate-api.com](https://exchangerate-api.com) service:
- Free tier available
- Real-time exchange rates
- JSON response format
- No API key required for basic usage

## Troubleshooting

### Common Issues

1. **Compilation Error: `curl/curl.h` not found**
   ```bash
   # Make sure cURL is installed
   brew install curl
   
   # Check include path
   ls /opt/homebrew/include/curl/
   ```

2. **Compilation Error: `nlohmann/json.hpp` not found**
   ```bash
   # Make sure nlohmann/json is installed
   brew install nlohmann-json
   
   # Check include path
   ls /opt/homebrew/include/nlohmann/
   ```

3. **Runtime Error: Network connection failed**
   - Check internet connection
   - Verify API endpoint is accessible
   - Check firewall settings

4. **Currency not found error**
   - Verify currency code is correct (3-letter ISO code)
   - Check if currency is supported by the API
   - Use option 2 to see available currencies

## 🔧 Customization

### Adding New Currencies
The program automatically supports all currencies available from the API. No code changes needed.

### Changing API Endpoint
Modify the URL in `fetchExchangeRates()`:
```cpp
string url = "https://api.exchangerate-api.com/v4/latest/" + baseCurrency;
```

### Adding Features
- Historical rate tracking
- Multiple API sources
- Rate alerts
- Export functionality
- GUI interface

## 🤝 Contributing

This is a learning project, but suggestions are welcome:
- Bbugug reports
- feature requests
- code improvements
- documentation enhancements


*Part of the [C++ Financial Toolkit](https://github.com/gyimadu/cpp-financial-toolkit)* 