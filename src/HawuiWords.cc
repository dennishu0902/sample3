
#include <iostream>
#include <string> 
#include <vector>
#include <cctype>
#include <stdexcept>
#include <map>

using namespace std;

//This function takes in a string (word) and returns the result of making all characters in that word lowercase.
std::string StringToLower(const std::string& word);
//This function takes in a lowercase character (c) and returns true if it’s a valid character in the Hawaiian language, false otherwise.
//a, e, i, o, u, p, k, h, l, m, n, and  '
bool IsValidCharacter(const char& c);
//This function takes in a lowercase string (word) and returns true if every character in word is a valid character in the Hawaiian language, false otherwise.
bool IsValidWord(const std::string& word);
//This function takes in two lowercase characters (v1 and v2) and returns true if the sequence v1 v2 is a vowel group according to the rules above, false otherwise.
//ai ae ao au ei eu iu oi ou ui
bool IsVowelGroup(const char& v1, const char& v2);
//a e i o u
bool IsVowel(const char& v);
//This function takes in a lowercase character (c) and returns true if c is a consonant, false otherwise.
//p, k, h, l, m, n Pronounced like the English versions.
//w — start of word /after the letter 'a' Either pronounced as a w or a v sound. We shall pronounce it as a w sound
//w — after ‘i’ or ‘e’ Pronounced as a v sound.
//w — after ‘u’ or ‘o’ Pronounced as a w sound.
bool IsConsonant(const char& c);
//
char ConsonantPronunciation(const char& c, const char& prev='\0');
std::string VowelGroupPronunciation(const char& v1, const char& v2);
std::string SingleVowelPronunciation(const char& v);
std::string ProcessCharacter(const char& prev, const char& curr, const char& next);
std::string Pronunciation(const std::string& word);
std::string GetPronunciation(const std::string& hawaiian_word);
std::string GetPronunciation(const std::string& hawaiian_word)
{
    std::string hawaiian_word_lower, strpron;
    hawaiian_word_lower = StringToLower(hawaiian_word);
    if(IsValidWord(hawaiian_word_lower))
    {
       strpron = Pronunciation(hawaiian_word_lower);
    }
    else
       throw invalid_argument("Invalid words exception?");
    return strpron;
}
bool IsValidWord(const std::string& word)
{
    size_t i=0;
    if(word.size()==0) return false;
    //check each char if valid
    for(i=0; i< word.size(); i++)
    {
        if(IsValidCharacter(word[i])==false) return false;
    }
    return true;
}
//a, e, i, o, u, p, k, h, l, m, n, and  '
bool IsValidCharacter(const char& c)
{   
    size_t i;
    std::string validch="aeioupkhlmnw'";
    //check if can find the input char in the group of validch
    for(i=0;i<validch.size();i++)
    {
        if(c == validch[i]) return true;
    }
    return false; 
}
//a e i o u
bool IsVowel(const char& v)
{
    unsigned long i;
    std::string validvowel="aeiou";
    //check if can find the input char in the group of validvowel
    for(i=0;i<validvowel.size();i++)
    {
        if(v == validvowel[i]) return true;
    }
    return false; 
}
//ai ae ao au ei eu iu oi ou ui
bool IsVowelGroup(const char& v1, const char& v2)
{
    // use vector and string compare
    std::string str1;
    std::vector<std::string> vowgrp={"ai","ae", "ao", "au", "ei", "eu", "iu", "oi", "ou", "ui" };
    
    str1.push_back(v1);
    str1.push_back(v2);
    /* method 1
     for(i=0; i< vowgrp.size(); i++)
      if(str1 == vowgrp[i]) return true;
      */
     /*method 2
     for(auto it=vowgrp.begin();it<vowgrp.end();it++)
        if(str1 == *it) return true;
        */
     /* for( auto iter:vowgrp)  //do not change the value in vowgrp
          iter = "test";
        for( auto &iter:vowgrp) //will change the value in vowgrp
          iter = "test";  
        for(const auto &iter:vowgrp) //error when compile, must not change the const reference
          iter = "test"; 
        for( const auto &iter:vowgrp) //correct, read only
         std::cout << iter;   
      */
      
      for(const auto &iter:vowgrp)
        if(str1 == iter) return true;
    
    return false;    
    
}
///p, k, h, l, m, n, w
bool IsConsonant(const char& c)
{
    std::string validvowel="pkhlmnw";
    for(size_t i=0;i<validvowel.size();i++)
    {
        if(c == validvowel[i]) return true;
    }
    return false; 
}
std::string StringToLower(const std::string& word)
{
    std::string lowerstr;
    for(size_t i=0; i< word.size();i++)
    {
       lowerstr.push_back(std::tolower(word[i]));     
    }
    return lowerstr;
}
////p, k, h, l, m, n Pronounced like the English versions.
//w — start of word /after the letter 'a' Either pronounced as a w or a v sound. We shall pronounce it as a w sound
//w — after ‘i’ or ‘e’ Pronounced as a v sound.
//w — after ‘u’ or ‘o’ Pronounced as a w sound.
char ConsonantPronunciation(const char& c, const char& prev)
{
    if(c!='w') return c;
    if((prev=='\0') || (prev=='a')) return 'w';
    if((prev=='i') || (prev=='e'))  return 'v';
    if((prev=='u') || (prev=='o'))  return 'w';
    throw invalid_argument("Invalid words exception?");
}
std::string VowelGroupPronunciation(const char& v1, const char& v2)
{
    std::string str1;
    std::string str2;
    //use map
    std::map<std::string,std::string> mymap={{"ai","eye"},{"ae","eye"},{"ao","ow"},{"au","ow"},
                                             {"ei","ay"},{"eu","eh-oo"},
                                             {"iu","ew"},{"oi","oy"},{"ou","ow"},{"ui","ooey"}};
    str2.push_back(v1);
    str2.push_back(v2);
    str1=mymap[str2];
    return str1;
}
std::string SingleVowelPronunciation(const char& v)
{ // a -> ah, e-> eh, i-> ee, o->oh u->oo
  std::string str1;
   //use map
  std::map<char,std::string> mymap={{'a',"ah"},{'e',"eh"},
                                    {'i',"ee"},{'o',"oh"},{'u',"oo"}};
  str1 = mymap[v];
  return str1;
}
std::string Pronunciation(const std::string& word)
{
    char prev='\0';
    std::string strpron;
    for(size_t i=0;i<word.size();)
    {
        if(IsVowelGroup(word[i],word[i+1]))
        {
          strpron.append(VowelGroupPronunciation(word[i],word[i+1]));
          if( (i+2) < word.size()) //word[i+1] is not last char
            { if(word[i+2] != '\'')  // and word[i+2] is not '
                 strpron.append(1,'-'); // string& append (size_t n, char c);
            } 
          prev = word[i+1];
          i = i+2;
        }
        else if(IsVowel(word[i]))
        {
          strpron.append(SingleVowelPronunciation(word[i]));
          if( (i+1) < word.size()) 
            { if(word[i+1] != '\'') strpron.append(1,'-');}
          prev = word[i];
          i = i+1;  
        }
        else if(IsConsonant(word[i]))
        {
          strpron.append(1,ConsonantPronunciation(word[i],prev));
          prev = word[i];
          i = i+1;    
        }
        else if(word[i] == '\'')
        {
           strpron.append(1,'\'');
           prev = '\0';
           i = i + 1;
        }
        else 
          std::cout << "exception" << std::endl;
    }    
    return strpron;
}
std::vector<std::string> Split(const std::string strin)
{   
    std::vector<std::string> words;
    std::string  str1;  
    size_t i=0;
    //split strin by whitespace
    while( i < strin.size())
     {
       if(strin[i] != ' ') 
           {
             str1.push_back(strin[i]);
             i++;
           }
       else
         { 
            i++; 
            if(str1.empty()==true) continue;//white space at first
            words.push_back(str1);
            str1.clear();
        }
     }
     //the end word, no white space
   if(str1.empty() !=true) words.push_back(str1);
   return words;
}
 // How to use exception, https://cplusplus.com/forum/beginner/57892/
int main(int argc, char *argv[])
{
    std::string  strin, str2;  
    std::vector<std::string> words;
    size_t i=0;
    if(argc > 1)
    {
    //split argv[1] by whitespace
    strin = argv[1];
    words = Split(strin);
    
     for(i=0; i< words.size(); i++)
     { 
        try{ 
           str2 = GetPronunciation(words[i]);
           std::cout << str2;
           std::cout << " ";
        }
       catch (const std::invalid_argument& ia) {
	       std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
     }
      std::cout << std::endl ;    
    } 
    else
       std::cout << "Please add parameter" << std::endl;
}
