/*
Author: Fariha Hossain
Course: CSCI-136
Instructor: Melissa Lynch
Assignment: Project 2A

Ask the user for a word.
The program only reports pronunciation as a list of phonemes,



*/

#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
using namespace std;

void splitOnSpace(string s, string & before, string & after) {
  // reset strings
    before = ""; 
    after = "";
  // accumulate before space
    int i = 0;
    while (i < s.size() && not isspace(s[i])) { 
        before = before + s[i]; 
        i++; 
    }
  // skip the space
    i++;
    // accumulate after space
    while (i < s.size()) { 
        after = after + s[i]; 
        i++; 
    }
}

string pronunciation(string word)
{
     // convert word to upper case
    string w_upper;
    for(int i=0;i<word.length();i++) //capitlize it.
    {
        char c=word[i];
        c = toupper(c);
        w_upper += c;
    }
    // cout << "\t debug: upper is: " << wupper << endl;
    word = w_upper;
    // conversion done
    
    string before; //def variable
    string after;
    
    ifstream fin("cmudict.0.7a"); //file open
    if (fin.fail())////copied from lab 3
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    string line;      //def varible
    getline(fin, line);
    
    while(getline(fin,line))//reads line by line
    {
        splitOnSpace(line, before, after);

        if(word==before)
        {
            // cout<< "\t" << before << ", " << w << endl;
            return after;
        }

    }

    fin.close();

    return "";
    


}
string identical (string word, string pron)
{
    // convert word to upper case
    string w_upper = "";
    for(int i=0;i<word.length();i++) //capatilize it
    {
        char c=word[i];
        c = toupper(c);
        w_upper += c;
    }
    // cout << "\t debug: upper is: " << wupper << endl;
    word = w_upper;
    // conversion done

    string dictionary_word; //def variable
    string dictionary_pron;
    string line; 

    ifstream fin("cmudict.0.7a"); //file open
    if (fin.fail())////copied from lab 3
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }    


    while(getline(fin,line)) //read line by line
    {
        splitOnSpace(line, dictionary_word, dictionary_pron);

        if(pron==dictionary_pron && dictionary_word !=word)
        {
            //cout<< "\t" << dictionary_pron << ", " << pron<< endl;
            cout<<dictionary_word << " "; //need space to seperate words.
        }
    }

    cout<<endl;

    fin.close();

    return "";

}

bool valid_checker(string word) //checks if the word is valid to be used
{
    int i;
    
    for(i=0; i<word.length(); i++)
    {
        char c= word[i];

        if(!(!(word[i]=='\'') || (!isalpha(word[i]) ) ))
        {
            return false;
        }
    }

    return true;
}

int count_the_phoneme(string pronunciation) //counts num of phonemes
{
    int count_1; //def variable
    int i;
    int len;

    count_1=0;

    len=pronunciation.length(); //gives the no of characters in a word 

    for(i=0; i<len; i++)
    {
        char c= pronunciation[i];
        
        if(isspace(c))
        {
            count_1++;
        }
    }

    return count_1;


}

bool replace_phoneme(string pron1, string pron2)
{
    int count_2; //def variable & set count to 0
    string var_1;
    string var_2;
    int i;
    string before_1;
    string before_2;
    string after_1;
    string after_2;

    count_2=0;
    var_1=pron1;//store the pron in another variable 
    var_2=pron2;

    
    if(count_the_phoneme(pron1) != count_the_phoneme(pron2))
    {
        return false; //compare num of phonemes 
    }

    for(i=0; i<count_the_phoneme(pron1)+1; i++) //to check each phoneme
    {
        splitOnSpace(var_1, before_1, var_1);
        splitOnSpace(var_2,before_2, var_2);

        if(before_1 != before_2)
        {
            count_2++;
        }
    }

    if(count_2==1)
    {
        return true;
    }

    else
    {
        return false;
    }


}

string add_phoneme(string word, string pron)
{
    //cout << "\t\t\t Add Phoneme\n";
    // convert word to upper case
    string w_upper = "";
    for(int i=0;i<word.length();i++) //capatilize it
    {
        char c=word[i];
        c = toupper(c);
        w_upper += c;
    }
    // cout << "\t debug: upper is: " << wupper << endl;
    word = w_upper;
    // conversion done
    
    
    string before_space; 
    string after_space;
    string before_space_1;//for input pronounciation breakdown
    string after_space_1;
    string before_space_2;//for current dictionary pronounciation breakdown
    string after_space_2;
    string line;
    string curr_word; //to store the current dictionary word
    string curr_pron; //to store the current dictionary pronounciation
    string add_ph;
    int phoneme_count_curr_pron; //counts the number of phoneme for current pron (dictionary) by calling the count phoneme function 
    int phoneme_count_input_pron;//counts the number of phoneme for input pron (the pron in the parameter of the add function) by calling the count phoneme function 
    int difference_in_phoneme; //this would be helpful to see the differnce between the number of phoneme bwtween two pron
    
    
    
    ifstream fin("cmudict.0.7a"); //file open
    //ifstream fin("test-dict.txt"); //file open 

    if (fin.fail())////copied from lab 3
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    //this counts the number of phoneme in the input pron
    phoneme_count_input_pron=count_the_phoneme(pron);
    //cout<<"input pron count :"<< " "<<phoneme_count_input_pron<<endl; WORKS!! GIVES 6 COUNT.

    while(getline(fin,line)) //reads line by line
    {   
        bool check_word=true;
        splitOnSpace(line, before_space, after_space);

        for(int i=0; i<before_space.length(); i++)
        {
            if((before_space[i]=='\'') || (isalpha(before_space[i])))
            {

            }
            else
            {
                check_word=false;
            }
        }

        if(check_word==false)
        {
            continue;
        }

        //cout << line << endl;

        splitOnSpace(line,before_space,after_space);

        curr_word=before_space; //store the current word

        
        curr_pron=after_space; //stores the current pronounciation

        //the current word(dictionary word) is different from the input word
        //so they can't be equal
        
        //cout << "word is valid " << valid_checker(curr_word)<<endl;
        if(valid_checker(curr_word) && (curr_word != word))
        {
            //cout<<"curr_word"<<endl;
            phoneme_count_curr_pron=count_the_phoneme(curr_pron); //this would count the number of phoneme of the dictionary pron

            //Next, breakdown the input pronounciation and current prouounciation

            splitOnSpace(pron, before_space_1, after_space_1);
            splitOnSpace(curr_pron,before_space_2, after_space_2);

            splitOnSpace(after_space_1, before_space_1, after_space_1);
            splitOnSpace(after_space_2,before_space_2, after_space_2);

            //So, the objective of this fucntion is to find a word (current word)that has one additional phoneme
            //in their pronounication than the input pronouniation
            //the ideal difference in phoneme should be 1
            
            
        
            if(phoneme_count_input_pron+1==phoneme_count_curr_pron)
            {
                difference_in_phoneme=0;
                //cout<<"prebefore_space_1: "<<before_space_1<< "prebefore_space_2: "<<before_space_2 <<endl;

                while( (before_space_2 != "" && before_space_1 != "")) //the ideal condition for the add_phoneme function
                {   //cout<<"before_space_1: "<< " "<<before_space_1<< "nbefore_space_2: "<<before_space_2 <<endl;
                   
                    if(before_space_1 !=before_space_2) //going through the phoneme since the input word is different from the current(dictionary) word
                    {
                        
                        difference_in_phoneme= difference_in_phoneme+1;
                        splitOnSpace(after_space_2,before_space_2,after_space_2);
                        
                    }

                    else
                    {
                        splitOnSpace(after_space_1,before_space_1,after_space_1);
                        splitOnSpace(after_space_2, before_space_2,after_space_2);
                    }
                }

                if(difference_in_phoneme<2)
                {
                    add_ph +=curr_word + " ";
                }
            }

        }
    }
     
    return add_ph;
}

string remove_phoneme(string word, string pron)
{
    // convert word to upper case
    string w_upper = "";
    for(int i=0;i<word.length();i++) //capatilize it
    {
        char c=word[i];
        c = toupper(c);
        w_upper += c;
    }
    // cout << "\t debug: upper is: " << wupper << endl;
    word = w_upper;
    // conversion done
    
    
    string before_space; 
    string after_space;
    string before_space_1;//for input pronounciation breakdown
    string after_space_1;
    string before_space_2;//for current dictionary pronounciation breakdown
    string after_space_2;
    string line;
    string curr_word; //to store the current dictionary word
    string curr_pron; //to store the current dictionary pronounciation
    string remove_ph;
    int phoneme_count_curr_pron; //counts the number of phoneme for current pron (dictionary) by calling the count phoneme function 
    int phoneme_count_input_pron;//counts the number of phoneme for input pron (the pron in the parameter of the add function) by calling the count phoneme function 
    int difference_in_phoneme; //this would be helpful to see the differnce between the number of phoneme bwtween two pron
    
    difference_in_phoneme=0;
    
    ifstream fin("cmudict.0.7a"); //file open
    if (fin.fail())////copied from lab 3
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    //this counts the number of phoneme in the input pron
    phoneme_count_input_pron=count_the_phoneme(pron); 

    while(getline(fin,line)) //reads line by line
    {
        bool check_word=true;
        splitOnSpace(line, before_space, after_space);

        for(int i=0; i<before_space.length(); i++)
        {
            if((before_space[i]=='\'') || (isalpha(before_space[i])))
            {

            }
            else
            {
                check_word=false;
            }
        }

        if(check_word==false)
        {
            continue;
        }
        
        splitOnSpace(line,before_space,after_space);

        curr_word=before_space; //store the current word

        
        curr_pron=after_space; //stores the current pronounciation

        //the current word(dictionary word) is different from the input word
        //so they can't be equal
        if(valid_checker(curr_word) && (curr_word !=word))
        {
            phoneme_count_curr_pron=count_the_phoneme(curr_pron); //this would count the number of phoneme of the dictionary pron

            //Next, breakdown the input pronounciation and current prouounciation
            //split it twice since there is an extra space

            splitOnSpace(pron, before_space_1, after_space_1);
            splitOnSpace(curr_pron,before_space_2, after_space_2);

            splitOnSpace(after_space_1, before_space_1, after_space_1);
            splitOnSpace(after_space_2,before_space_2, after_space_2);

            //So, the objective of this fucntion is to find a word (current word)that has one less phoneme
            //in their pronounication than the input pronouniation
            //the ideal difference in phoneme should be 1
            
            
        
            if(phoneme_count_input_pron-1==phoneme_count_curr_pron)
            {
                difference_in_phoneme=0;
                while(difference_in_phoneme<2 && (before_space_2 != "" && before_space_1 != "")) //the ideal condition for the add_phoneme function
                {
                    if(before_space_1 !=before_space_2) //gping through the phoneme since the input word is different from the current(dictionary) word
                    {
                        splitOnSpace(after_space_1,before_space_1,after_space_1);
                        difference_in_phoneme= difference_in_phoneme+1;
                    }

                    else
                    {
                        splitOnSpace(after_space_1,before_space_1,after_space_1);
                        splitOnSpace(after_space_2, before_space_2,after_space_2);
                    }
                }

                if(difference_in_phoneme<2)
                {
                    remove_ph +=curr_word + " ";
                }
            }

        }
    }
     
    return remove_ph;
}        

      

int main()
{
    string w;
    string p;
    
    cin>>w;

    bool check_word=true;

    for(int i=0; i<w.length(); i++)
        {
            if((w[i]=='\'') || (isalpha(w[i])))
            {

            }
            else
            {
                check_word=false;
            }
        }

        if(check_word==false)
        {
            cout<<"Not found";
            return 0;
        }

    // convert w to upper case
    string wupper = "";
    for(int i=0;i<w.length();i++)
    {
        char c=w[i];
        c = toupper(c);
        wupper += c;
    }
    // cout << "\t debug: upper is: " << wupper << endl;
    w = wupper;
    // conversion done
    
    p=pronunciation(w);
    if(p=="")
    {
        cout<<"Not found";
    }
    cout<<"Pronunciation"<< "\t"<<":"<<p<<endl;
    cout<<endl;
    
    cout<< "Identical"<<"\t"<< ":" <<" "<< identical(w,p);

    cout<< "Add phoneme"<<"\t"<< ":" <<" "<< add_phoneme(w,p)<<endl;

    cout<< "Remove phoneme"<<"\t"<< ":" <<" "<< remove_phoneme(w,p)<<endl;

    cout<< "Replace phoneme"<<"\t" << ":"<<" ";
    
    string before;
    string after;
    
    string loose_str;
    
    ifstream fin("cmudict.0.7a");
    if (fin.fail())
    {
        cerr << "File cannot be opened for reading." << endl;
        exit(1);
    }

    string line;      
   // getline(fin, line);
    // w to upper case
    while(getline(fin,line))
    {
        bool check_word=true;
        splitOnSpace(line, before, after);

        for(int i=0; i<before.length(); i++)
        {
            if((before[i]=='\'') || (isalpha(before[i])))
            {

            }
            else
            {
                check_word=false;
            }
        }

        if(check_word==false)
        {
            continue;
        }


        if(replace_phoneme(p, after))
        {
            loose_str += before + " ";
        }
    
    }

    cout<<loose_str;
    cout<<endl;
    
    return 0;
}       
   




