#include <iostream>
#include <vector>
#include <string>

std::vector < size_t > prefix (std::string s)
{
    std :: cout << "Building a prefix function for a string " << s << "\n";
    std::vector < size_t > pr(s.size(), 0);
    for (size_t i = 1; i < s.size(); i++)
    {
        size_t j = pr[i - 1];
        while (j > 0 && s[i] != s[j]){
            std :: cout << "Characters are not equal, return to the prefix of the last matched character (" << s [j - 1] << ") \n";
            j = pr[j - 1];
        }
        std :: cout << "\n Compare " << j + 1 << "th character (" << s[j] << ") and " << i + 1 << "th character (" << s[i] << ") lines \n";
        if (s[i] == s[j]) {
            std :: cout << "Characters are equal, comparison continues one position further \n";
            j++;}
        else{
            std :: cout << "Characters are not equal and no matching non-zero prefix was found, shift forward one position \n";
        }
        pr[i] = j;

    }
    std::cout<<"The prefix function is: ";
    for(int i = 0; i < pr.size(); i++){
        std::cout<<pr[i];
    }
    std::cout<<std::endl;
    return pr;
}

std::vector < size_t > kmp (std::string s, std::string t)
{

    std::vector < size_t > prefix_func = prefix(t);
    size_t j = 0;
    std::vector < size_t > find;
    std :: cout << "\n Searches for the pattern " << t << "in the string " << s << "\n";
    for (size_t i = 0; i < s.size(); i++)
    {
        while (j > 0 && t[j] != s[i]){
            if (j < t.size()) {
                std::cout << "The character of the pattern " << t[j] << " with the index " << j << " is not equal to the character of the string " << s[i] << " with the index " << i<<". ";
                std::cout << "A new index is calculated.\n";
            }
            else {
                std::cout << "End of the pattern. New index is calculated.\n";
            }
            j = prefix_func[j - 1];
            std::cout << "New index: " << j<<std::endl;
        }
        if (t[j] == s[i]){

            std :: cout << j << "th character of pattern (" << t[j] << ") and " << i << "th character of string (" << s[i] << ") match \n ";
            j++;
        }
        if (j == t.size())
        {
            std::cout<<"Found pattern in string and added to answer"<<std::endl;
            find.push_back(i + 1 - t.size());
        }
    }
    return find;
}

int main()
{
    std::string s, t;
    std::cin >> t;
    std::cin >> s;
    std::vector < size_t > rez = kmp(s, t);
    if (rez.size() > 0)
    {
        for (size_t i = 0; i < rez.size() - 1; i++)
            std::cout << rez[i] << ",";
        std::cout << rez[rez.size() - 1];
    }
    else std::cout << -1;
}