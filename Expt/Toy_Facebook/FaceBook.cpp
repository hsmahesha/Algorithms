#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

class Node {
    public:
        int uId;
        string name;
        set<Node*> friends;

    public:
        Node(int uId, string name) {
            this->uId = uId;
            this->name = name;
            this->friends = set<Node*>();
        }
};

class FaceBook {
    private:
        int cnt;
        map<string, int> users;
        map<int, string> ids;
        map<int, Node*> usersInfo;

    public:
        FaceBook() {
            this->cnt = 0;
            this->users = map<string, int>();
            this->ids = map<int, string>();
            this->usersInfo = map<int, Node*>();
        }

    public:
        void checkFriends(string n1, string n2) {
            int id1, id2;

            if (this->users.find(n1) != this->users.end()) {
                id1 = this->users[n1];
            } else {
                cout << "User " << n1 << " does not exist\n";
                return;
            }

            if (this->users.find(n2) != this->users.end()) {
                id2 = this->users[n2];
            } else {
                cout << "User " << n2 << " does not exist\n";
                return;
            }

            set<Node*> s1 = usersInfo[id1]->friends;
            set<Node*> s2 = usersInfo[id2]->friends;
            Node* i2 = this->usersInfo[id2];

            vector<Node*> common;
            set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                             back_inserter(common));

            if (s1.find(i2) != s1.end()) {
                cout << "Common Friends:  ";
            } else {
                cout << "Mutual Friends:  ";
            }

            for (int i = 0; i < common.size(); i++) {
                cout << common[i]->name << " ";
            }
            cout << endl;

        }

        void printFriendsList() {
             for (auto p = users.begin(); p != users.end(); p++) {
                  string u = p->first;
                  int id = p->second;
                  Node* uInfo = this->usersInfo[id];

                  cout << u << ":  ";
                  for (auto p = uInfo->friends.begin();
                       p != uInfo->friends.end(); p++) {
                      Node* fInfo = *p;
                      cout << fInfo->name << "  ";
                  }
                  cout << endl;
             }
             cout << endl << endl;
        }

        void constructFriendsList(vector<string> tokens) {
           if (tokens.size() == 0) return;

           string u = tokens[0];
           if (this->users.find(u) == this->users.end()) {
               this->users[u] = ++cnt;
               this->ids[cnt] = u;
               this->usersInfo[cnt] = new Node(cnt, u);
           }
           int cId = this->users[u];

           for (int i = 1; i < tokens.size(); i++) {
			   string f = tokens[i];
			   if (this->users.find(f) == this->users.end()) {
				   this->users[f] = ++cnt;
				   this->ids[cnt] = f;
                   this->usersInfo[cnt] = new Node(cnt, f);
			   }
               int fId = this->users[f];

               Node* uNode = this->usersInfo[cId];
               Node* fNode = this->usersInfo[fId];

               uNode->friends.insert(fNode);
               fNode->friends.insert(uNode);
           }
        }

		vector<string> split(const string &s, char delim) {
			stringstream ss(s);
			string item;
			vector<string> tokens;
			while (getline(ss, item, delim)) {
				tokens.push_back(item);
			}
			return tokens;
		}

        void constructGraphDatabase(string ifile) {
            fstream fh = fstream(ifile);
            if (!fh.is_open()) {
                cout << "error: failed to open input csv file" << endl;
                exit(1);
            }

            for (string line; getline(fh, line);) {
                vector<string> tokens = this->split(line, ',');
                this->constructFriendsList(tokens);
            }
        }

};

FaceBook* constructFBGraph(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "error: invalid command line arguments" << endl;
        exit(1);
    }

    FaceBook* fb = new FaceBook();
    fb->constructGraphDatabase(string(argv[1]));

    return fb;
}

void printFBGraph(FaceBook* const fb) {
    fb->printFriendsList();
}

void explore_friends(FaceBook* const fb) {
    while (true) {
        cout << "enter two names\n";
        string n1, n2;
        cin >> n1 >> n2;
        fb->checkFriends(n1, n2);

        cout << "\ndo you want to continue again?(y/n)\n";
        char c;
        cin >> c;
        if (c != 'y') break;
    }
}

int main(int argc, char* argv[]) {
    FaceBook* fb = constructFBGraph(argc, argv);
    printFBGraph(fb);
    explore_friends(fb);
    return 0;
}
