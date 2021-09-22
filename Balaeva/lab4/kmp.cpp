#include <iostream>
#include <vector>
#include <string>

std::vector < size_t > prefix (std::string s)
{
    std :: cout << "Building a prefix function for a string" << s << "\n";
    std::vector < size_t > pr(s.size(), 0);
    for (size_t i = 1; i < s.size(); i++)
    {
        size_t j = pr[i - 1];
        while (j > 0 && s[i] != s[j]) j = pr[j - 1];

        std :: cout << "\n Compare" << j + 1 << "th character (" << s[j] << ") and " << i + 1 << "th character (" << s[i] << ") lines \n";
        if (s[i] == s[j]) j++;
        pr[i] = j;
        std :: cout << "Characters are equal, comparison continues one position further \n";
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
    std :: cout << "\n Searches for the pattern" << t << "in the string" << s << "\n";
    for (size_t i = 0; i < s.size(); i++)
    {
        while (j > 0 && t[j] != s[i]) j = prefix_func[j - 1];
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