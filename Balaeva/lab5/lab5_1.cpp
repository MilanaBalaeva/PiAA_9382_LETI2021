#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

#define N 50


class Bohr {
public:
    int next_vertex[N];
    int pattern_num;
    bool flag;
    int suff_link;
    int auto_move[N];
    int parent;
    char symbol;
    Bohr(int p, char c) : parent(p), symbol(c) {
        memset(next_vertex, 255, sizeof(next_vertex));
        flag = false;
        suff_link = -1;
        memset(auto_move, 255, sizeof(auto_move));
    }
};

std::vector<Bohr> bohr;
std::vector<std::string> pattern;
std::vector<std::pair<int, int>> ans;
std::vector<std::string> cross_Patterns;
int cross_count = 0;
int cross_patt = -1;

void init_bohr() {
    std :: cout << "Start building the bohr \n";
    std::cout<<"The root is denoted as #"<< std::endl;
    Bohr v(0,-30);
    bohr.push_back(v);
}


void add_pattern_to_bohr(const std::string& s) {
    int num = 0;
    for (int i = 0; i< s.length(); i++) {

        std :: cout << "Consider the symbol : " << i + 1 <<"th: " << s[i] << "\n";
        char ch = s[i]- 'A';
        if (bohr[num].next_vertex[ch] == -1) {
            Bohr v(num, ch);
            bohr.push_back(v);

            std::cout <<  "A vertex is added to the selection, to which the current symbol of the pattern leads (" << char((v.symbol )+'A') << ") \n";
            bohr[num].next_vertex[ch] = bohr.size() - 1;
        }
        else{
            std::cout << "The vertex (" << s[i] << ") already exists for the current pattern, you are navigating along it \n";}
        num = bohr[num].next_vertex[ch];
    }
    bohr[num].flag = true;
    std::cout << "The vertex to which the transition is made is terminal, the construction of the boron branch is finished \n";
    pattern.push_back(s);
    bohr[num].pattern_num = pattern.size() - 1;

}

int get_auto_move(int v, char ch);


int get_suff_link(int v) {
    std::cout << "Calculating suffix and end links for vertex: " << char (bohr[v].symbol + 'A')<<std::endl;
    if (bohr[v].suff_link == -1)
        if (v == 0 || bohr[v].parent == 0){
            bohr[v].suff_link = 0;
            std :: cout << "Suffix reference points to root(#) \n";
        }
    else{

        std :: cout << "Follow the parent's suffix link \n";
        std::cout<<"Parent is "<< bohr[v].parent << std::endl;
        bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].parent), bohr[v].symbol);
    }
        return bohr[v].suff_link;
}

int get_auto_move(int v, char ch) {

    std::cout << "Looking for a path from the vertex " << char (bohr[v].symbol + 'A') << " along the edge with the symbol " << char(ch +'A')  << ". \n";
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vertex[ch] != -1){
            std :: cout << "Go to the next node with the corresponding character \n";
            bohr[v].auto_move[ch] = bohr[v].next_vertex[ch];
        }
        else
            if (v == 0){
                std :: cout << "The next node with the matching character was not found, go to the root node(#) \n";
                bohr[v].auto_move[ch] = 0;
            }
            else{
                std :: cout << "The next node with the matching character was not found, let's follow the suffix link \n";
                bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
            }
            return bohr[v].auto_move[ch];
}

void checkout(int v, int i) {

    for (int u = v; u != 0; u = get_suff_link(u)) {
        if (bohr[u].flag){
            std :: cout << "Found pattern in text \n";
            std::cout << "Position: " << i - pattern[bohr[u].pattern_num].length() + 1 << ", Number of pattern: " << bohr[u].pattern_num + 1 << "\n";
            ans.push_back(std::pair<int, int>(i - pattern[bohr[u].pattern_num].length() + 1, bohr[u].pattern_num + 1));
            if (cross_patt != -1 && i - cross_count < pattern[bohr[u].pattern_num].length() + pattern[cross_patt].length()) {
                if (std::find(cross_Patterns.begin(), cross_Patterns.end(), pattern[cross_patt]) == cross_Patterns.end())
                    cross_Patterns.push_back(pattern[cross_patt]);
                if (std::find(cross_Patterns.begin(), cross_Patterns.end(), pattern[bohr[u].pattern_num]) == cross_Patterns.end())
                    cross_Patterns.push_back(pattern[bohr[u].pattern_num]);
            }
            cross_patt = bohr[u].pattern_num;
            cross_count = i - pattern[bohr[u].pattern_num].length();

        }

    }
}

void find_all_pos(const std::string& s) {
    int u = 0;
    for (int i = 0; i<s.length(); i++) {
        std::cout << "Consider the line with the current position: ";
            for (int j = 0; j < s.length(); j++)
                if (j == i)
                    std::cout << "'" << s[j] << "'";
                else
                    std::cout << s[j];
        std::cout<<std::endl;
        u = get_auto_move(u, s[i] - 'A');
        checkout(u, i + 1);
    }

}
void printer(const std ::string& s){
    find_all_pos(s);
    std::sort(ans.begin(),ans.end());
    if(ans.size()==0){
        std::cout<<"The search has not given any results."<<std::endl;
    }
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i].first << " " << ans[i].second << std::endl;
    }
    std::cout << "The number of vertices in the automate: " << bohr.size() << "\n";
    std::cout << "List of found patterns that overlap with other found patterns in the search bar";
    if (cross_Patterns.empty())
        std::cout << ", empty\n";
    else {
        std::cout << ":\n";
        for (auto& i : cross_Patterns) {
            std::cout << i << " ";
        }
    }

}


int main()
{

    std::string text;
    std::string pattern;
    int n;
    std::cin >> text >> n ;
    std::cout<<std::endl;
    init_bohr();
    for (int i = 0; i<n; i++) {
        std::cin >> pattern;
        std::cout<<"Pattern number: "<< i + 1 <<": "<<pattern<<std::endl;
        add_pattern_to_bohr(pattern);
    }
    printer(text);

    return 0;
}