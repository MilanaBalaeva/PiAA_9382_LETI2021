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
int Cycle (const std::string & s, const std::string & t)
{
    if (s.size() != t.size()){
        std::cout<<("The string "+s+" is not a circular shift of the string "+ t+  " , because the lengths are different\n");
        return -1;
    }
    std::cout<<("duplicate the line " + s)<<std::endl;
    std::string new_s = s + s;
    std::cout<<("New string:" + new_s);
    std::vector < size_t > prefix_ = prefix(t);
    size_t j = 0;
    size_t find = -1;
    std :: cout << "\n Searches for the pattern " << t << " in the string " << new_s << "\n";
    for (size_t i = 0; i < new_s.size(); i++)
    {
        while (j > 0 && t[j] != new_s[i]) j = prefix_[j - 1];
        if (t[j] == new_s[i]) {
            std :: cout << j << "th character of pattern (" << t[j] << ") and " << i << "th character of string (" << new_s[i] << ") match \n ";
            j++;
        }

        if (j == t.size())
        {
            std::cout<<"Found pattern in string and added to answer"<<std::endl;
            find = (i + 1 - t.length());
            break;
        }
    }
    return find;
}

int main()
{
    std::string s, t;
    std::cin >> t;
    std::cin >> s;
    std::cout << Cycle(t,s);
}