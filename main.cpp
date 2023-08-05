#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 28;
const long long inf = 1e18 + 28;
vector <pair<int, int>> g[maxn];
vector <int> ans;
long long dis[maxn];
pair <long long, int> h[maxn]; // heap
set <pair<int, int>> s;
int par[maxn], c = 2;
bool mark[maxn];
vector<string> v;
map<int, string> mp1;
map<string, int> mp2;
struct Node{
    struct Node *child[26];
    bool isword;
};
struct Node *init(){
    struct Node *node =  new Node;

    node->isword = false;

    for (int i = 0; i < 26; i++)
        node->child[i] = NULL;

    return node;
}
void insert(struct Node *root, string s){
    struct Node *tmp = root;
    for(int i = 0; i < s.size(); i++){
        if(!tmp->child[s[i] - 'a'])
            tmp->child[s[i] - 'a'] = init();
        tmp = tmp->child[s[i]-'a'];
    }
    tmp->isword = 1;
}
void dfs(struct Node *node, string s){
    if(node->isword)
        v.push_back(s);
    for(int i = 0; i < 26; i++){
        if(node->child[i]){
            dfs(node->child[i], s + (char)(i + 'a'));
        }
    }
}
bool flag = 0;
void dfs2(struct Node *node, string s){
    if(flag)
        return;
    if(node->isword) {
        v.push_back(s);
        flag = 1;
        //cout << "!@#!@#!@#!@ " << s << "\n";
        return;
    }
    for(int i = 0; i < 26; i++){
        if(node->child[i]){
            dfs2(node->child[i], s + (char)(i + 'a'));
        }
    }
}
bool delflag = 0;
void dfs3(struct Node *node, string s){
    if(delflag)
        return;
    if(node->isword) {
        node->isword = false;
        delflag = 1;
        return;
    }
    for(int i = 0; i < 26; i++){
        if(node->child[i]){
            dfs3(node->child[i], s + (char)(i + 'a'));
        }
    }
}
void search(struct Node *root, string s){
    struct Node *tmp = root;
    for(int i = 0; i < s.size(); i++){
        if(!tmp->child[s[i] - 'a'])
            return;
        tmp = tmp->child[s[i] - 'a'];
    }
    dfs2(tmp, s);
}
void delsearch(struct Node *root, string s){
    struct Node *tmp = root;
    for(int i = 0; i < s.size(); i++){
        if(!tmp->child[s[i] - 'a'])
            return;
        tmp = tmp->child[s[i] - 'a'];
    }
    dfs3(tmp, s);
}

void bu(int i){
    while(h[i / 2] > h[i] && i > 1){
        swap(h[i], h[i / 2]);
        i /= 2;
    }
}

void bd(int i){
    while(h[i] > min(h[i * 2], h[i * 2 + 1])){
        if(h[i * 2].first == inf)
            break;
        else if(h[i * 2 + 1].first == inf){
            swap(h[i * 2], h[i]);
            i *= 2;
        }
        else if(h[i * 2] ==  min(h[i * 2], h[i * 2 + 1])){
            swap(h[i], h[i * 2]);
            i *= 2;
        }
        else{
            swap(h[i], h[i * 2 + 1]);
            i = i * 2 + 1;
        }
    }
}
int main(){
    int n;
    cout << "number of restraunts\n";
    cin >> n;
    cout << "enter " << n << " restaurant names and distances:\n";
    for(int i = 1; i <= n; i++){
        string name;
        cin >> name >> dis[i];
        mp1[i] = name;
        mp2[name] = i;
    }
    for(int i = 0; i < maxn; i++)
        h[i] = {inf, i};

    for(int i = 1; i <= n; i++)
        h[i] = {dis[i], i};

    for(int i = n/2; i >= 1; i--){
        bd(i);
    }
//    for(int i = 1; i <= n; i++)
//        cout << h[i].first << " " << h[i].second << "\n";


    cout << "enter number of queries: \n";
    int t;
    cin >> t;
    c = n;
    struct Node *root = init();
    stack<int> stk;
    stack <pair<int, int>> hipstk;
    int cntt = 1;
    while(t--){
        int k;
        string name;
        cin >> k >> name;
        int dif = k;
        if(!stk.empty()) {
            dif = k - stk.top();
           // cout << k << " " << stk.top() << " $$$$$\n";

        }
        stk.push(k);
        while(dif < 0){
            pair<int, int> tmp = hipstk.top();
            h[c + 1] = tmp;
            bu(c + 1);
            c++;
            delflag = 0;
            delsearch(root, mp1[tmp.second]);
            hipstk.pop();
            dif ++;
        }
        for(int i = 0; i < dif; i++){
            int ind = h[1].second;
            hipstk.push(h[1]);
            insert(root, mp1[ind]);
            swap(h[1], h[c]);
            h[c].first = inf;
            bd(1);
            c--;
        }
        v.clear();
        //cout << cntt++ << ":";
        flag = 0;
        search(root, name);
        int i = 1;
        if(v.empty()){
            cout << "NO restaurant found!\n";
        }
        else{
            for(auto x: v) {
                cout << x << "\n";
            }
        }

        v.clear();

    }
//    struct Node *root = init();
//    int tmp = n;
//    for(int i = 1; i < n; i++){
//        string st = mp1[i];
//        insert(root, st);
//
//    }
//
//    for(int i = 1; i < maxn; i++){
//        dis[i] = inf;
//        if(i != 1){
//            h[i].first = inf;
//        }
//    }
//
//    h[1] = {0, 0};
//    while(h[1].first != inf){
//        int v = h[1].second;
//        swap(h[1], h[c - 1]);
//        h[c - 1].first = inf;
//        bd(1);
//        c--;
//        if(mark[v] == 0){
//            for(auto x: g[v]){
//                int w = x.first, u = x.second;
//                if(dis[u] > dis[v] + w){
//                    dis[u] = dis[v] + w;
//                    h[c] = {dis[u], u};
//                    bu(c);
//                    c++;
//                    par[u] = v;
//                }
//            }
//        }
//        mark[v] = 1;
//    }
//
//    int opt;
//    cout << "choose opt:\n1- find nearest restuarant\n2- find your restaurant\n";
//    cin >> opt;
//    long long mini = inf;
//    int ind;
//    if(opt == 1){
//        for(int i = 1; i < n; i++) {
//            mini = min(mini, dis[i]);
//            if(mini == dis[i])
//                ind = i;
//        }
//        cout << "nearest restuarant is : " << mp1[ind] << " ----- distance to you is : " << dis[ind] << "\n";
//
//    }
//    else{
//        cout << "enter part of restaurant name: \n";
//        string name;
//        cin >> name;
//        search(root, name);
//        cout << "auto : ";
//        int i = 1;
//        cout << "enter one of the restaurants indx:\n";
//        for(auto x: v) {
//            cout << i++ << "-" << x << "\n";
//        }
//        int indx;
//        cin >> indx;
//        indx--;
//        int ind1 = mp2[v[indx]];
//        cout << "restuarant is : " << v[indx] << " ----- distance to you is : " << dis[ind1] << "\n";
//        v.clear();
//    }
}
///////////////////////////////////////////