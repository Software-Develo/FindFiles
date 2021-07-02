//
//  main.cpp
//  findmaxfile
//
//  Created by Marat Khisamutdinov on 01.07.2021.
//
//
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <libgen.h>
#include <fstream>
#include <string.h>
#include <filesystem>
#include <stdlib.h>
using namespace std;
ofstream file;
ofstream sortfile;

const string name = "/Users/maratkhisamutdinov/Desktop/program/Pathname";
const string sort_name = "/Users/maratkhisamutdinov/Desktop/program/SortPathname";
char start_path[] = "/";
char space[] = "         ";
int enter = 0;

struct St
{
    string name;
    long int size;
};
vector <St> vect;

void sortVect()
{
    for(int startindex = 0; startindex < vect.size() - 1; startindex++)
    {
        int largestindex = startindex;
        for(int currentindex = largestindex + 1; currentindex < vect.size(); currentindex++)
        {
            if(vect[currentindex].size > vect[largestindex].size)
                largestindex = currentindex;

        }
        swap(vect[largestindex], vect[startindex]);
    }

}

void get_list(char path[])
{
    struct dirent *dp;
    DIR *dir;
    St st;
    dir=opendir(path);// Открываем каталог
    if (dir == NULL) return;

    while((dp = readdir(dir)) != NULL)// Читаем директорию, пока она не закончится
    {

        if (strcmp(dp->d_name,".") == 0) continue;
        if (strcmp (dp->d_name,"..") == 0) continue;

        if (dp->d_type == DT_DIR)// Если это папка, то мы записываем путь до нее и входим
        {
            enter++;
            char new_path[256];
            strcpy(new_path, path);

            if(enter != 1)
                strcat(new_path,"/");

            strcat(new_path, dp->d_name);
            file << new_path << endl;// Записываем путь подкаталога
            get_list(new_path);
        }
        else
        {
            struct stat buff;
            char new_path[256];

            strcpy(new_path, path);
            strcat(new_path,"/");
            strcat(new_path, dp->d_name);
            stat(new_path, &buff);

            off_t sizest = buff.st_size;

            st.name = new_path;
            st.size = sizest;
            vect.emplace_back(st);
            file << path << "/"<< dp->d_name << space << sizest << endl;
        }
    }

    return;
}


int main(int argc, const char * argv[]) {
    file.open(name);
    sortfile.open(sort_name);
    if(file.is_open())  get_list(start_path);
    else  cout << "File "  << name << " isn't open" << endl;

    sortVect();

    if(sortfile.is_open()) {
        for(int i = 0; i < vect.size(); i++)
        {
            sortfile << vect[i].name << space << vect[i].size << endl;
        }
    }
    else cout << "File " << sort_name << " isn't open" << endl;

    sortfile.close();
    file.close();
    return 0;
}