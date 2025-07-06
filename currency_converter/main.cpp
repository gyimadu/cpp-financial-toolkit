// ============================================
// CURRENCY CONVERTER 
// ============================================
// In this program, I make HTTP requests using cURL library
// and JSON parsing with nlohmann/json
// Error handling and input validation
// Callback functions and memory management

#include <iostream>              // for input/output operations (cout, cin)
#include <string>                // for string manipulation
#include <map>                   // for storing currency exchange rates
#include <iomanip>               // for output formatting (setprecision, fixed)
#include <curl/curl.h>           // cURL library for HTTP requests
#include <nlohmann/json.hpp>     // JSON parsing library

using namespace std;             
using json = nlohmann::json;     // alias for shorter syntax

void displayWelcome();           
void displayMenu();              
double getUserAmount();          // get and validate amount from user
string getUserCurrency(const string& prompt);  // get and validate currency code
void performConversion(double amount, const string& fromCurrency, const string& toCurrency);  // main conversion logic
bool fetchExchangeRates(const string& baseCurrency, map<string, double>& rates);  // fetch live rates from API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp);  // cURL callback function

// ============================================
// MAIN FUNCTION - PROGRAM ENTRY POINT
// ============================================
int main() {
    displayWelcome();
    
    // main program loop - runs until user chooses to exit
    while (true) {
        displayMenu();
        
        int choice;
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        
        if (choice == 1) {
            // ============================================
            // CURRENCY CONVERSION FLOW
            // ============================================
            // 1. get amount from user (with validation)
            double amount = getUserAmount();
            
            // 2. get source currency (e.g., USD, EUR)
            string fromCurrency = getUserCurrency("Enter source currency (e.g., USD, EUR, GBP): ");
            
            // 3. get target currency (e.g., EUR, JPY)
            string toCurrency = getUserCurrency("Enter target currency (e.g., USD, EUR, GBP): ");
            
            // 4. perform conversion with live data
            performConversion(amount, fromCurrency, toCurrency);
        }
        else if (choice == 2) {
            // supported currencies
            cout << "\n=== Supported Currencies ===\n";
            cout << "USD - US Dollar\n";
            cout << "EUR - Euro\n";
            cout << "GBP - British Pound\n";
            cout << "JPY - Japanese Yen\n";
            cout << "CAD - Canadian Dollar\n";
            cout << "AUD - Australian Dollar\n";
            cout << "CHF - Swiss Franc\n";
            cout << "CNY - Chinese Yuan\n";
            cout << "==========================\n\n";
        }
        else if (choice == 3) {
            cout << "Thank you for using Currency Converter!\n";
            break; 
        }
        else {
            cout << "Invalid choice. Please try again.\n\n";
        }
    }
    
    // ============================================
    curl_global_cleanup();  // clean up cURL library resources
    return 0;               
}

// ============================================
// User interface functions
// ============================================

void displayWelcome() {
    cout << "========================================\n";
    cout << "        CONVERTIGO!\n";
    cout << "========================================\n";
    cout << "Welcome! ConvertiGo! converts between\n";
    cout << "popular currencies using live exchange rates.\n\n";
}

void displayMenu() {
    cout << "What would you like to do?\n";
    cout << "1. Convert currency\n";
    cout << "2. View supported currencies\n";
    cout << "3. Exit\n";
}

// ============================================
// Input validation functions
// ============================================

double getUserAmount() {
    double amount;
    
    // loop until we get valid input
    while (true) {
        cout << "Enter amount to convert: ";
        
        // ============================================
        // input validation
        // ============================================
        // cin >> amount returns true if input is valid number
        // amount > 0 ensures positive value
        if (cin >> amount && amount > 0) {
            return amount;  // Valid input, exit loop
        } else {
            cout << "Please enter a valid positive number.\n";
            
            // ============================================
            // clearing invalid input
            // ============================================
            cin.clear();           // clear error flags (e.g., if user entered "abc")
            cin.ignore(10000, '\n'); // remove bad input from buffer (up to 10000 chars or until newline)
        }
    }
}

string getUserCurrency(const string& prompt) {
    string currency;
    cout << prompt;
    cin >> currency;
    
    // ============================================
    // string manipulation - convert to uppercase
    // ============================================
    // range-based for loop
    // char& c means we're modifying the original character (reference)
    // toupper() converts lowercase to uppercase
    for (char& c : currency) {
        c = toupper(c);
    }
    
    return currency;
}

// ============================================
// Core conversion logic
// ============================================
void performConversion(double amount, const string& fromCurrency, const string& toCurrency) {
    // display what the user wants to convert
    cout << "\n=== Conversion Request ===\n";
    cout << "Amount: " << fixed << setprecision(2) << amount << " " << fromCurrency << "\n";
    cout << "Target: " << toCurrency << "\n";
    cout << "========================\n\n";
    
    // ============================================
    // Step 1: fetch live exchange rates
    // ============================================
    map<string, double> rates;  // will store currency codes and their rates
    cout << "Fetching live exchange rates...\n";
    
    // call the API function to get current rates
    if (!fetchExchangeRates(fromCurrency, rates)) {
        cout << "Error: Could not fetch exchange rates. Please check your internet connection.\n\n";
        return; 
    }
    
    // ============================================
    // Step 2: validate target currency exists
    // ============================================
    // rates.find() returns an iterator
    // rates.end() is a special iterator pointing to "end" of map
    // If find() returns end(), the key wasn't found
    if (rates.find(toCurrency) == rates.end()) {
        cout << "Error: Currency '" << toCurrency << "' not found in exchange rates.\n";
        cout << "Available currencies: ";
        
        // ============================================
        // Range-based for loop with auto
        // ============================================
        // const auto& rate - auto deduces the type, & avoids copying, const prevents modification
        // rate is a pair<string, double> representing currency code and exchange rate
        for (const auto& rate : rates) {
            cout << rate.first << " ";  // rate.first is the currency code (string)
        }
        cout << "\n\n";
        return;
    }
    
    // ============================================
    // Step 3: perform conversion
    // ============================================
    double conversionRate = rates[toCurrency];  
    double convertedAmount = amount * conversionRate; 
    
    // ============================================
    // Step 4: display results with formatting
    // ============================================
    cout << "=== Conversion Result ===\n";
    cout << fixed << setprecision(2);  // show exactly 2 decimal places
    cout << amount << " " << fromCurrency << " = " << convertedAmount << " " << toCurrency << "\n";
    cout << "Exchange Rate: 1 " << fromCurrency << " = " << conversionRate << " " << toCurrency << "\n";
    cout << "========================\n\n";
}

// ============================================
// API integration - fetch live exchange rates
// ============================================
bool fetchExchangeRates(const string& baseCurrency, map<string, double>& rates) {
    // ============================================
    // cURL variables
    // ============================================
    CURL* curl;                    // pointer to cURL handle (like a "session")
    CURLcode res;                  // stores result of cURL operations
    string readBuffer;             // will store the HTTP response (JSON data)

    // ============================================
    // Step 1: initialize cURL library
    // ============================================
    curl_global_init(CURL_GLOBAL_DEFAULT);  // initialize cURL library (required once)
    curl = curl_easy_init();                 // create a new cURL handle

    if(curl) {  // Check if cURL handle was created successfully
        // ============================================
        // Step 2: build the API URL
        // ============================================
        // this API returns all exchange rates relative to the base currency
        string url = "https://api.exchangerate-api.com/v4/latest/" + baseCurrency;
        
        // ============================================
        // Step 3: configure cURL options
        // ============================================
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());           // set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // set our callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);     // pass our buffer to callback
        
        // ============================================
        // Step 4: make the HTTP request
        // ============================================
        res = curl_easy_perform(curl);  // make the request (this calls the callback fxn)
        curl_easy_cleanup(curl);        // clean up this cURL handle

        // ============================================
        // Step 5: check for cURL errors
        // ============================================
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return false;  // return false to indicate failure
        }

        // ============================================
        // Step 6: parse the JSON response
        // ============================================
        try {
            json j = json::parse(readBuffer);  // convert JSON string to JSON object
            
            // check if the JSON contains the "rates" field
            if (j.contains("rates")) {
                // ============================================
                // convert JSON to C++ map
                // ============================================
                rates = j["rates"].get<map<string, double>>();
                return true; 
            } else {
                cerr << "JSON does not contain 'rates' field." << endl;
                return false;
            }
        } catch (const json::parse_error& e) {
            // ============================================
            // exception handling
            // ============================================
            cerr << "JSON parse error: " << e.what() << endl;
            return false;
        }
    }
    return false;  // return false if cURL handle creation failed
}

// ============================================
// Callback function - handles HTTP response data
// ============================================
// this function is called by cURL every time it receives data from the server
// receives data in chunks and appends it to the string buffer

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    // ============================================
    // parameter explanation:
    // ============================================
    // void* contents - raw data from HTTP response (generic pointer)
    // size_t size - size of each data element (usually 1 for char data)
    // size_t nmemb - number of elements in this chunk
    // string* userp - the string buffer (passed via CURLOPT_WRITEDATA)
    
    // ============================================
    // append data to the buffer
    // ============================================
    // cast void* to char* and append to our string
    // size * nmemb gives us total bytes in this chunk
    ((string*)userp)->append((char*)contents, size * nmemb);
    
    // ============================================
    // return value
    // ============================================
    // return how many bytes we successfully processed
    // cURL uses this to detect errors
    return size * nmemb;
}
