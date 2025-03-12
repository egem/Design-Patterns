#include <iostream>
#include <vector>
#include <list>
#include <memory>
using namespace std;

// Component Interface
class FileSystemItem {
public:
    virtual void showDetails(int depth = 0) const = 0; // Pure virtual function
    virtual ~FileSystemItem() = default;
};

// Leaf class: Represents individual files
class File : public FileSystemItem {
private:
    string name;
public:
    File(string name) : name(name) {}

    void showDetails(int depth = 0) const override {
        cout << string(depth, '-') << " File: " << name << endl;
    }
};

// Composite class: Represents folders that contain files and other folders
class Folder : public FileSystemItem {
private:
    string name;
    list<shared_ptr<FileSystemItem>> items; // Can store both Files and Folders
public:
    Folder(string name) : name(name) {}

    void add(shared_ptr<FileSystemItem> item) {
        items.push_back(item);
    }

    void showDetails(int depth = 0) const override {
        cout << string(depth, '-') << " Folder: " << name << endl;
        for (const auto& item : items) {
            item->showDetails(depth + 2);
        }
    }
};

int main() {
    auto root = make_shared<Folder>("Root");

    auto folder1 = make_shared<Folder>("Documents");
    folder1->add(make_shared<File>("resume.pdf"));
    folder1->add(make_shared<File>("project.docx"));

    auto folder2 = make_shared<Folder>("Pictures");
    folder2->add(make_shared<File>("photo1.jpg"));
    folder2->add(make_shared<File>("photo2.png"));

    auto subfolder = make_shared<Folder>("2024");
    subfolder->add(make_shared<File>("vacation.jpg"));

    folder2->add(subfolder);

    root->add(folder1);
    root->add(folder2);
    root->add(make_shared<File>("README.txt"));

    root->showDetails();

    return 0;
}
