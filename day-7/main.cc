#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stack>
#include <string>
#include <list>
#include <stdbool.h>
#include <unordered_set>
#include <cstring>

class ElfNode
{
    public:
        std::string name;
        uint64_t size;
        ElfNode * parent;
        bool is_dir;
        std::vector<ElfNode *> children;

        ElfNode(
            std::string name,
            uint64_t size,
            ElfNode * parent,
            bool is_dir)
        {
            this->name = name;
            this->size = size;
            this->parent = parent;
            this->is_dir = is_dir;
        }
        
        void add_child(ElfNode * child)
        {
            this->children.push_back(child);
        }

        ElfNode * cd(std::string name)
        {
            for (ElfNode *child : this->children) {
                if (child->name == name)
                    return child;
            }
            return nullptr;
        }

        void print(int depth)
        {
            this->pdp(depth);
            std::cout << "- " << this->name;
            if (this->is_dir) {
                std::cout << " (dir) " << this->size;
            } else {
                std::cout << " (file, size=" << this->size << ")";
            }
            std::cout << std::endl;
            if (this->is_dir) {
                int child_depth = depth+1;
                for (ElfNode * child : this->children) {
                    if (child->is_dir)
                        child_depth = depth + 1;
                    child->print(child_depth);
                }
            }
        }

    private:
        void pdp(int depth)
        {
            std::cout << std::string(depth, ' ');
        }

};

void index_sum(ElfNode * root)
{
    for (ElfNode * child : root->children) {
        index_sum(child);
    }

    if (root->parent) {
        root->parent->size += root->size;
    }
    return;

}

uint64_t atmost(ElfNode * root, uint64_t inclusive, uint64_t sum)
{
    if (root->is_dir) {
        if (root->size <= inclusive) {
            sum += root->size;
        }
    }
    for (ElfNode * child : root->children) {
        if (child->is_dir) {
            sum += atmost(child, inclusive, 0);
        }
    }
    return sum;
}

/* Hard code known Elf Commands. */
#define ELF_CMD_CD_ROOT "$ cd /"
#define ELF_CMD_CD_UP "$ cd .."
#define ELF_CMD_LS "$ ls"
#define ELF_CMD_CD "$ cd "

/* Other. */
#define ELF_OUT_DIR "dir "


int main(int argc, char *argv[]) {
    ElfNode root("/", 0, nullptr, true);
    ElfNode *cwd = &root;;
    std::ifstream infile("input.txt");
    std::string line;
    while(std::getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        if (line.rfind(ELF_CMD_CD_ROOT, 0) == 0) {
            cwd = &root;
            continue;
        }
        if (line.rfind(ELF_CMD_CD_UP, 0) == 0) {
            if (cwd->parent != nullptr)
                cwd = cwd->parent;
            else
                cwd = &root;
            continue;
        }
        if (line.rfind(ELF_CMD_LS, 0) == 0) {
            continue;
        }
        if (line.rfind(ELF_CMD_CD, 0) == 0) {
            int index = strlen(ELF_CMD_CD);
            std::string name = line.substr(index, -1);
            cwd = cwd->cd(name);
            continue;
        }
        // Two cases left (directory or a file).
        // In both cases the second token after a space
        // is the name of the object. Hence, extract the name.
        int space_index = line.find_first_of(" ");
        std::string name = line.substr(space_index + 1, -1);
        uint64_t size = 0;
        bool is_dir = true;
        if (line.rfind(ELF_OUT_DIR, 0) == 0) {
            ;
        } else {
            // Last case implicit: file output.
            // Example line: `14848514 b.txt`
            size = std::stoi(line.substr(0, space_index));
            is_dir = false;
        }
        ElfNode *this_file = new ElfNode(name, size, cwd, is_dir);
        cwd->add_child(this_file);
    }
    //root.print(0);
    index_sum(&root);
    root.print(0);
    uint64_t am = atmost(&root, 100000, 0);
    std::cout << "AT MOST: " << am  << std::endl;
}
