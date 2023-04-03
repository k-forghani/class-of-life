#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class File {
    protected:
        string path;
    
    public:
        File(string path);
        void write(string content) const;
        string read() const;
};

class FastA : public File {
    public:
        FastA(string path);
        void dump(map<string, string> content) const;
        map<string, string> parse() const;
};

class Text {
    private:
        // Reference: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
        const char escape = '\033';
        const char separator = ';';
        const char end = 'm';
        const map<string, pair<int, int>> colors = {
            {"black",   {30, 40}},
            {"red",     {31, 41}},
            {"green",   {32, 42}},
            {"yellow",  {33, 43}},
            {"blue",    {34, 44}},
            {"magenta", {35, 45}},
            {"cyan",    {36, 46}},
            {"white",   {37, 47}},
            {"default", {39, 49}},
        };
        const map<string, pair<int, int>> modes {
            {"bold",          {1, 22}},
            {"dim",           {2, 22}},
            {"italic",        {3, 23}},
            {"underline",     {4, 24}},
            {"blinking",      {5, 25}},
            {"inverse",       {7, 27}},
            {"hidden",        {8, 28}},
            {"strikethrough", {9, 29}},
        };
        const int reset = 0;
    
    public:
        Text(
            string text,
            string foreground = "",
            string background = "",
            set<string> modes = {}
        );
        
        friend ostream& operator<<(ostream& output, const Text& text);
        friend istream& operator>>(istream& input, const Text& text);
        friend Text operator+(const Text& t1, const Text& t2);
};

class Log {
    private:
        string type;
        Text* text;
    
    public:
        Log(string type, const Text& text);
        void print(bool type) const;
};

class Logger {
    private:
        string root = "";
        vector<Log> logs;
    
    public:
        Logger(string root = "", bool type = false);
        void log(string type, Text text, bool print) const;
};

class Workspace {

};

class Interface {
    
};