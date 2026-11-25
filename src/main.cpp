#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Feedback {
    string id;
    string timestamp;
    string storeId;
    string productId;   
    int score;
    string comment;
};

struct Product {
    string id;
    string name;
    string category;
    string brand;
    string price;       
    string rating;
};


void splitCsv(const string& line, vector<string>& cols) {
    cols.clear();
    size_t start = 0;
    size_t pos = line.find(',', start);
    while (pos != string::npos) {
        cols.push_back(line.substr(start, pos - start));
        start = pos + 1;
        pos = line.find(',', start);
    }
    cols.push_back(line.substr(start));
}


bool parseScore(const string& text, int& score) {
    if (text.empty() || text.size() > 2) return false;
    int value = 0;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') return false;
        value = value * 10 + (text[i] - '0');
    }
    if (value < 0 || value > 10) return false;
    score = value;
    return true;
}


bool productExists(const vector<Product>& products, const string& id) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].id == id) return true;
    }
    return false;
}

bool loadProducts(const string& path, vector<Product>& products) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: cannot open " << path << endl;
        return false;
    }
    string line;
    getline(file, line);                 
    int lineNo = 1;
    vector<string> cols;
    while (getline(file, line)) {
        lineNo++;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        splitCsv(line, cols);
        if (cols.size() != 6) {
            cerr << "Warning " << path << " line " << lineNo
                 << ": wrong column count -> skipped" << endl;
            continue;
        }
        Product p = {cols[0], cols[1], cols[2], cols[3], cols[4], cols[5]};
        products.push_back(p);
    }
    file.close();
    return true;
}

bool loadFeedback(const string& path, const vector<Product>& products,
                  vector<Feedback>& feedbacks) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: cannot open " << path << endl;
        return false;
    }
    string line;
    getline(file, line);                
    int lineNo = 1;
    vector<string> cols;
    while (getline(file, line)) {
        lineNo++;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        splitCsv(line, cols);
        if (cols.size() != 6) {
            cerr << "Warning " << path << " line " << lineNo
                 << ": wrong column count -> skipped" << endl;
            continue;
        }
        int score;
        if (!parseScore(cols[4], score)) {
            cerr << "Warning " << path << " line " << lineNo
                 << ": invalid score '" << cols[4] << "' -> skipped" << endl;
            continue;
        }
        if (cols[3] != "-" && !productExists(products, cols[3])) {
            cerr << "Warning " << path << " line " << lineNo
                 << ": unknown product " << cols[3] << " -> skipped" << endl;
            continue;
        }
        Feedback f = {cols[0], cols[1], cols[2], cols[3], score, cols[5]};
        feedbacks.push_back(f);
    }
    file.close();
    return true;
}


int main(int argc, char* argv[]) {
    string folder = (argc > 1) ? argv[1] : "data/sample";
    vector<Product> products;
    vector<Feedback> feedbacks;
    if (!loadProducts(folder + "/products.csv", products)) return 1;
    if (!loadFeedback(folder + "/feedback.csv", products, feedbacks)) return 1;
    cout << "Loaded " << products.size() << " products, "
         << feedbacks.size() << " feedback" << endl;
    return 0;
}