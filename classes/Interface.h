#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class FastA {
    private:
        string path;

    public:
        FastA(string path);
        void write(map<string, string> records, int length = 80) const;
        map<string, string> parse() const;
};

class Text {
    private:
        // Reference: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
        const string ESCAPE = "\033";
        const string CONTROL = "[";
        const string SEPARATOR = ";";
        const string END = "m";
        const map<string, pair<string, string>> COLORS = {
            {"black",   {"30", "40"}},
            {"red",     {"31", "41"}},
            {"green",   {"32", "42"}},
            {"yellow",  {"33", "43"}},
            {"blue",    {"34", "44"}},
            {"magenta", {"35", "45"}},
            {"cyan",    {"36", "46"}},
            {"white",   {"37", "47"}},
            {"default", {"39", "49"}},
        };
        const map<string, pair<string, string>> MODES {
            {"bold",          {"1", "22"}},
            {"dim",           {"2", "22"}},
            {"italic",        {"3", "23"}},
            {"underline",     {"4", "24"}},
            {"blinking",      {"5", "25"}},
            {"inverse",       {"7", "27"}},
            {"hidden",        {"8", "28"}},
            {"strikethrough", {"9", "29"}},
        };
        const string RESET = "0";
        
        string text;
        string foreground;
        string background;
        set<string> modes;
        string output;
        
    public:
        Text(
            string text = "",
            string foreground = "",
            string background = "",
            set<string> modes = {}
        );

        void render();
        void change(string text);
        
        friend ostream& operator<<(ostream& output, const Text& text);
        friend istream& operator>>(istream& input, Text& text);
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