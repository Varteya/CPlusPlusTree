#include <dirent.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

int compare(dirent *left, dirent *right) {
    //DT_DIR
    if ((left->d_type == DT_DIR) == (right->d_type == DT_DIR)){
        return string(left->d_name) < string(right->d_name);
    };
    return left->d_type > right->d_type;

}

void read_dir(std::string way, string iter) {
    DIR *dir;
    struct dirent *entry;



    iter = iter + "|-- ";
    dir = opendir(way.c_str());
    if (dir) {
        vector<dirent *> children;
        while ((entry = readdir(dir)) != NULL) {
            if (string(entry->d_name) != ".." && string(entry->d_name) != ".") {
                children.push_back(entry);
            }
        }
        std::sort(children.begin(), children.end(), compare);


        for (int i = 0; i < children.size(); ++i){
            bool last_child = (i == children.size() - 1);

            if (last_child){
                iter = iter.substr(0, iter.size() - 4) + "└-- ";
                std::cout << iter << children[i]->d_name << std::endl;
                iter = iter.substr(0, iter.size() - 4) + "    ";
            } else {
                std::cout << iter << children[i]->d_name << std::endl;
                if (children[i]->d_type == DT_DIR){
                    iter = iter.substr(0, iter.size() - 4) + "|   ";
                }
            }

            read_dir(way + "/" + children[i]->d_name, iter);
        }

    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    read_dir(argv[1], "");
    return 0;
}


