#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<cstring>
#include<unordered_map>

using namespace std;

vector< vector<char> > G; //文法G[S]产生式 ，~为空字
unordered_map<char, set<char> > ts; //终结符(char)terminal symbol,及它的first集合(set<char>)
unordered_map<char, set<char> > nts; //非终结符(char)non-terminal symbol，及它的first集合(set<char>)
map< map<string, char> , string> table; //LR分析表

struct C { //闭包CLOSURE
    vector< vector<char> > project; //项目集
    vector< set<char> > outlook; //展望串
    unordered_map<char, int> go; //GO函数
};
vector<C> c;

void show_G() {
    cout << "原文法拓广为文法G[M]：" << endl;
    for (unsigned int i = 0; i < G.size(); i++) { //输出G'[S']
        cout << i << "）";
        for (unsigned int j = 0; j < G[i].size(); j++) {
            if (j == 1)cout << "->";
            cout << G[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}

void show_Symbol() {
    for (unordered_map<char, set<char> >::iterator it = nts.begin(); it != nts.end(); it++) { //输出非终结符
        cout << it->first;
    }
    cout << endl;
    for (unordered_map<char, set<char> >::iterator it = ts.begin(); it != ts.end(); it++) { //输出终结符
        cout << it->first;
    }
    cout << endl << endl;
}

void show_First() {
    for (auto it1 : ts) {
        cout << it1.first << ": ";
        for (auto it2 : it1.second) {
            cout << it2 << ",";
        }
        cout << endl;
    }
    cout << endl << endl;
    for (auto it1 : nts) {
        cout << it1.first << ": ";
        for (auto it2 : it1.second) {
            cout << it2 << ",";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void show_Closure() {  //项目集和GO函数输出到Closure.txt文件
    fstream f("Closure.txt", ios::out);
    if (!f) {
        cout << "Closure.txt文件打开出错！" << endl;
        return;
    }
    f << "该文法的项目集和GO函数：" << endl;
    for (unsigned int i = 0; i < c.size(); i++) {
        f << "I" << i << ":" << endl;
        for (unsigned int j = 0; j < c[i].project.size(); j++) {
            for (unsigned int k = 0; k < c[i].project[j].size(); k++) {
                if (k == 1) f << "->";
                if (c[i].project[j][k] == ' ') f << "·";
                else f << c[i].project[j][k];
            }
            f << "，";
            for (auto it : c[i].outlook[j]) {
                if (it == *(c[i].outlook[j].begin())) f << it;
                else f << "/" << it;
            }
            f << endl;
        }
        for (auto it : c[i].go) {
            f <<"GO(I"<<i<<"，"<< it.first << ") = I" << it.second << endl;
        }
        f << endl;
    }
    cout << "已将项目集和GO函数生成到Closure.txt文件中。" << endl << endl;
}

void show_Table() {  //LR分析表输出到LR_Table.txt文件
    fstream f("LR_Table.txt",ios::out);
    if (!f) {
        cout << "LR_Table.txt文件打开出错！" << endl;
        return;
    }
    for (int i = -1; i < (int)c.size(); i++) {
        if(i==-1) f << " " << '\t';
        else f << i << '\t';
        for (auto it : ts) {
            if (i == -1) f << it.first << '\t';
            else {
                map<string, char> m;
                m[to_string(i)] = it.first;
                f<<table[m]<<'\t';
            }
        }
        if (i == -1) f  <<"#"<< '\t';
        else {
            map<string, char> m;
            m[to_string(i)] = '#';
            f << table[m] << '\t';
        }
        for (auto it : nts) {
            if (it.first == 'M') continue;
            if (i == -1)f << it.first << '\t';
            else {
                map<string, char> m;
                m[to_string(i)] = it.first;
                f << table[m] << '\t';
            }
        }
        f << endl;
    }
    f.close();
    cout << "已将LR分析表生成到LR_Table.txt文件中。" << endl << endl;
    /*for (auto it1 : table) {
     for (auto it2 : it1.first) {
     cout << it2.first << it2.second << ":"<<it1.second<<endl;
     }
     }*/
}

void read_G() { //读取文法G[S]->G'[M]，并区分终结符和非终结符
    char ch; //当前读入的字符
    int i = 0; //当前行读取的第i个字符
    vector<char> v; //存放输入的一行产生式
    char X; //若遇到形如X->α|β|……,用于保存X以便消除|
    set<char> m;
    nts['M'] = m;
    while (ch = getchar()) {
        if (ch == '#') break;
        if (ch == '\n') { //换行
            if (!v.empty())G.push_back(v);
            v.clear();
            i = 0;
            continue;
        }
        if (ch != ' ' || ch != '\t') { //去掉空格等多余字符
            if (ch == '|') { //消除元语言符号'或|'
                G.push_back(v);
                v.clear();
                i = 3;
                v.push_back(X);
                continue;
            }
            i++;
            if (i == 1) {
                X = ch;
                nts[ch] = m; //产生式左边(第一个字符)的为非终结符
            }
            else if (i != 2 && i != 3&&ch!='~') ts[ch] = m; //此时ts里既有非终结符又有终结符
            if (i != 2 && i != 3)v.push_back(ch); //去掉产生式的->
        }
    }
    if (G.empty()) exit(0);
    
    //加入新树根M
    v.clear();
    v.push_back('M');
    v.push_back(G[0][0]);
    G.insert(G.begin(), v);
    
    //去掉ts中的非终结符
    for (unordered_map<char, set<char> >::iterator it = nts.begin(); it != nts.end(); it++) {
        unordered_map<char, set<char> >::iterator iter;
        iter = ts.find(it->first);
        if (iter != ts.end())ts.erase(iter);
    }
}

void get_First() { //得到First集合
    for (auto &it : ts) it.second.insert(it.first);//终结符的first集合是它自己
    
    //求非终结符的First集合
    int r = 0;
    int change = 1;
    while (change) {
        if (r == 20)break;
        r++;
        change = 0;
        for (auto &it : nts) { //对每个非终结符
            for (unsigned int i = 0; i < G.size(); i++) { //遍历产生式
                if (G[i][0] == it.first) {
                    unsigned int size = it.second.size(); //操作前First(X)的大小
                    unordered_map<char, set<char> >::iterator iter=ts.find(G[i][1]);
                    if (ts.find(G[i][1]) != ts.end()||G[i][1]=='~') { //形如X->a……或X->空字，把a加入First(X)中
                        it.second.insert(G[i][1]);
                        if (it.second.size() > size) change = 1;
                    }
                    else {  //形如X->Y……，把First(Y)加入First(X)
                        unsigned int col = 1;
                        while(1){ //若X->Y1Y2……,循环把First(Y)加入First(X)
                            int flag = 0; //标记当前First(Y)中是否有空字
                            unordered_map<char, set<char> >::iterator itt= nts.find(G[i][col]);
                            for(auto &iter:itt->second){ //遍历First(Y)
                                if (iter == '~') flag = 1;
                                else it.second.insert(iter);
                            }
                            if (flag) {
                                col++;
                                if (G[i].size() <= col) {
                                    it.second.insert('~'); //形如X->Y,将空字加入First(X)
                                    break;
                                }
                                else if (ts.find(G[i][col]) != ts.end()) { //形如X->Ya……，将a加入First(X)
                                    it.second.insert(G[i][col]);
                                    break;
                                }
                                else { //形如X->YZ……，将First(Z)加入First(X)
                                }
                            }
                            else break;
                        }
                        if (it.second.size() > size) change = 1;
                    }
                }
            }
        }
    }
}

void get_Closure() {  //计算CLOSURE，包括GO
    int i = 0; //闭包编号
    C clo; //生成第一个闭包（I0）
    c.push_back(clo);
    while(1) {
        if (i == c.size()) break; //没有新闭包，跳出循环（即已获得全部闭包及项目）
        if (i == 0) { //确定项目集I0的第一个项目
            vector<char> v(G[0]);
            v.insert(v.begin() + 1, ' ');
            c[i].project.push_back(v);
            set<char> m;
            m.insert('#');
            c[i].outlook.push_back(m);
        }
        for (unsigned int j = 0; j < c[i].project.size(); j++){  //遍历已有项目，生成该闭包所有项目
            for (unsigned int k = 0; k < c[i].project[j].size(); k++) {  //扫描单个项目，找到当前位置·（这里用空格代替）
                if (c[i].project[j][k] == ' ') {
                    if (k == c[i].project[j].size() - 1) break;  //形如X->β·，不会生成新的项目
                    for (unsigned int x = 0; x < G.size(); x++) { //形如X->α·Yβ，  遍历G'[M]，查找所有对应的产生式，以求出新的项目并加入项目集
                        if (G[x][0] == c[i].project[j][k + 1]) { //对应的产生式
                            vector<char> v(G[x]); //用于保存新项目
                            v.insert(v.begin() + 1, ' '); //计算新项目
                            int exist = 0; //标记该新项目是否已存在
                            for (unsigned int y = 0; y < c[i].project.size(); y++) { //遍历已有项目，判断是新项目还是已有项目
                                if (c[i].project[y] == v) { //已有项目，只需保存项目下标（用于添加新的展望串）
                                    exist = y;
                                    break;
                                }
                            }
                            if(exist==0) c[i].project.push_back(v); //新项目，加入项目集
                            set<char> m; //用于保存新展望串
                            //形如【形如X->α·Yβ，a】，计算展望串，即计算First(βa)
                            //情况一：β为空字，First(βa)=a
                            //情况二：β中第一个字符为结束符b，First(βa)=b
                            //情况三：β中第一个字符为非结束符B，若First(B)中没有空字，First(βa)=First(B)；
                            //                                   若First(B)中包含空字，First(βa)=First(B)+First(γa)，其中γ为β除去第一个字符后形成的符号串
                            bool kong = true; //标记情况三B中是否有空字
                            int t = 0; //表示当前符号串γ为β除去第t个字符
                            while (kong) { //若为情况三且B含空字，计算First(γa)
                                kong = false;
                                if (k + t + 1 == c[i].project[j].size() - 1) {  //情况一
                                    for (auto it : c[i].outlook[j]) m.insert(it);
                                }
                                else if (ts.find(c[i].project[j][k + t + 2]) != ts.end()) {  //情况二
                                    m.insert(c[i].project[j][k + 2 + t]);
                                }
                                else {  //情况三
                                    set<char> m1((nts.find(c[i].project[j][k + 2 + t]))->second);
                                    for (auto it : m1) {
                                        if (it== '~') {  //含空字
                                            kong = true;
                                            t++;
                                        }
                                        else { //不含空字
                                            m.insert(it);
                                        }
                                    }
                                }
                            }
                            if (exist) //已存在项目，将新展望串加入原展望串中
                            {
                                for (auto it : m) {
                                    c[i].outlook[exist].insert(it);
                                }
                            }
                            else c[i].outlook.push_back(m); //新项目，新展望串加入展望串集
                        }
                    }
                    break;
                }
            }
        }
        
        for (unsigned int j = 0; j < c[i].project.size(); j++) {  //遍历本闭包的所有项目，计算GO函数，并生成新的闭包
            for (unsigned int k = 0; k < c[i].project[j].size(); k++) {  //扫描单个项目，找到当前位置·（这里用空格代替）
                if (c[i].project[j][k] == ' ') {
                    if (k == c[i].project[j].size() - 1) break; //形如【X->β·】，不会生成新闭包
                    //计算GO函数，并生成新的闭包
                    vector<char> new_closure_pro(c[i].project[j]); //用于保存新项目
                    new_closure_pro[k] = new_closure_pro[k + 1]; //计算新项目
                    new_closure_pro[k + 1] = ' ';
                    set<char> new_closure_search(c[i].outlook[j]); //用于保存新展望串
                    bool dif = false; //标记 生成的新项目是否属于已有的闭包（判断是否需生成新闭包）
                    for (unsigned int x = 0; x < c.size(); x++) { //遍历已有闭包
                        //dif = false;
                        for (unsigned int y = 0; y < c[x].project.size(); y++) { //将新项目和新展望串与已有闭包的所有项目比较，若相同，则属于已有闭包，无需生成新闭包
                            dif = false;
                            if (new_closure_pro == c[x].project[y]) {
                                if (c[x].outlook[0].size() != new_closure_search.size()) { //比较展望串长
                                    dif = true;
                                    continue;
                                }
                                auto iter = c[x].outlook[0].begin();
                                for (auto it : new_closure_search) {  //比较展望串每个字符
                                    if (it!= *iter) {
                                        dif = true;
                                        break;
                                    }
                                    iter++;
                                }
                                if (dif == false) { //属于已有闭包，只计算GO函数
                                    c[i].go[new_closure_pro[k]] = x;
                                    break;
                                }
                            }
                            else dif = true;
                            if (dif == false) break;
                        }
                        if (dif==false) break;
                    }
                    if (c[i].go.count(new_closure_pro[k]) != 0 && dif) { //若有多个形如【X->α·Yβ】的产生式(相互不一样)，它们有同一GO函数(即属于同一闭包)，但生成的新项目不一样
                        c[c[i].go[new_closure_pro[k]]].project.push_back(new_closure_pro); //只需将新项目及新展望串加入GO对应的闭包
                        c[c[i].go[new_closure_pro[k]]].outlook.push_back(new_closure_search);
                        break;
                    }
                    if (dif) { //不属于已有闭包，生成新闭包，并计算GO函数
                        C new_closure;
                        new_closure.project.push_back(new_closure_pro);
                        new_closure.outlook.push_back(new_closure_search);
                        c.push_back(new_closure);
                        c[i].go[new_closure_pro[k]] = c.size() - 1;
                    }
                }
            }
        }
        i++; //下一闭包
    }
}

int get_Table() { //由CLOSURE计算LR(1)分析表table
    for (unsigned int i = 0; i < c.size(); i++) { //遍历所有闭包
        for (unsigned int j = 0; j < c[i].project.size(); j++) { //遍历每个闭包中的所有项目
            for (unsigned int k = 0; k < c[i].project[j].size(); k++) { //扫描该项目,找到当前位置
                if (c[i].project[j][k] == ' ') {
                    //cout << 1 << endl;
                    if (k== c[i].project[j].size()-1) { //形如 【X->α·，β】，归约/acc
                        if (c[i].project[j][0] == 'M'){  //形如 【M->X·，#】，令table[i,#]=acc
                            map<string, char> m;
                            m[to_string(i)] = '#';
                            if (table.find(m) != table.end() && table[m] != "acc") {
                                cout << "该文法不是LR(1)文法，存在多重定义入口！" << endl;
                                return 0;
                            }
                            else table[m] = "acc";
                        }
                        else { //形如 【X->α·，a】，归约，令table[i,a]=rj
                            int id;
                            for (unsigned int x = 0; x < G.size(); x++) { //扫描G'[M]找到对应的产生式的编号
                                vector<char> v(c[i].project[j]);
                                v.pop_back();
                                if (G[x] == v) {
                                    id = x;
                                    break;
                                }
                            }
                            for (auto it : c[i].outlook[j]) {
                                map<string, char> m;
                                m[to_string(i)] = it;
                                if (table.find(m) != table.end() && table[m] != (string)"r" + to_string(id)) {
                                    cout << "该文法不是LR(1)文法，存在多重定义入口！" << endl;
                                    return 0;
                                }
                                else table[m] = (string)"r" + to_string(id);
                            }
                        }
                    }
                    else{ //形如 【X->α·β，γ】
                        char next = c[i].project[j][k + 1];
                        if (ts.find(next) != ts.end()) {  //形如 【X->α·aβ，γ】,令table[i,a]=sj
                            map<string, char> m;
                            m[to_string(i)] = next;
                            if (table.find(m) != table.end()&&table[m]!=(string)"s"+to_string(c[i].go[next])) {
                                cout << "该文法不是LR(1)文法，存在多重定义入口！" << endl;
                                return 0;
                            }
                            else table[m] = (string)"s" + to_string(c[i].go[next]);
                        }
                        else { //形如 【X->α·Yβ，γ】,令table[i,Y]=j
                            map<string, char> m;
                            m[to_string(i)] = next;
                            if (table.find(m) != table.end() && table[m] != to_string(c[i].go[next])) {
                                cout << "该文法不是LR(1)文法，存在多重定义入口！" << endl;
                                return 0;
                            }
                            else table[m] = to_string(c[i].go[next]);
                        }
                    }
                    break;
                }
            }
        }
    }
    return 1;
}

int check(int time) { //输入并分析语句sentence并输出分析过程，成功分析返回1，否则返回0
    string sentence = "\0"; //需要分析的语句
    cin >> sentence;
    fstream f("sentence_"+to_string(time)+".txt", ios::out); //分析过程输出到该文件
    if (!f) {
        cout << "无法打开文件sentence.txt" << endl;
    }
    f << "步骤\t\t状态栈\t\t符号栈\t\t输入串\t\t动作说明" << endl;
    vector<string> status; //状态栈
    vector<char> symbol; //符号栈
    int step = 1; //步骤数
    if (sentence[0] != '#') {
        cout << "语句应以#开头，并以#结束" << endl;
        return 0;
    }
    symbol.push_back('#');
    sentence = sentence.substr(1);
    status.push_back("0");
    while (1) {
        f << step++ << "\t\t"; //输出步骤数
        for (unsigned int i = 0; i < status.size(); i++) //输出状态栈
            if (i == 0) f << status[i];
            else f << " " << status[i];
        f << "\t\t";
        for (unsigned int i = 0; i < symbol.size(); i++) //输出符号栈
            if (i == 0) f << symbol[i];
            else f << " " << symbol[i];
        f << "\t\t";
        for (unsigned int i = 0; i < sentence.length(); i++) //输出输入串
            if (i == 0) f << sentence[i];
            else f << " " << sentence[i];
        f << "\t\t";
        string cur_status = status[status.size() - 1]; //当前状态
        char cur_symbol = sentence[0]; //当前“展望”字符
        string new_status; //下一入栈的新状态
        map<string, char> m;
        m[cur_status] = cur_symbol;
        new_status = table[m];
        if (new_status == "acc") {
            cout << "分析成功，该语句合法！(具体分析过程请查看文件sentence_" << time << ".txt）" << endl << endl;
            f << "acc：分析成功" << endl;
            return 1;
        }
        else if (new_status[0] == 's') { //形如 table[i,b]=sj，状态sj入栈，并读入一个字符
            status.push_back(new_status.substr(1)); //入栈的状态要去掉第一个字符‘s’
            symbol.push_back(cur_symbol); //读入一个字符
            sentence = sentence.substr(1);
            f << "ACTION[" << cur_status << "," << cur_symbol << "]=" << new_status << "，即状态" << new_status << "入栈" << endl;
        }
        else if (new_status[0] == 'r') { //形如 table[i,b]=rj，用产生式G(j)归约，且table[x,y]入栈
            new_status = new_status.substr(1); //去掉‘r’
            f << "r" << new_status << "：用";
            int gid = atoi(new_status.c_str()); //计算产生式编号
            int len = G[gid].size() - 1; //被归约的字符串长度
            char reduced_symbol = G[gid][0]; //归约得到的非终结符
            for (int i = 0; i < len; i++) {
                status.pop_back(); //归约，即去掉栈顶的len个状态项
                symbol.pop_back();
            }
            map<string, char> m;
            m[status[status.size() - 1]] = reduced_symbol;
            new_status = table[m];
            status.push_back(new_status);
            symbol.push_back(reduced_symbol);
            for (unsigned int i = 0; i < G[gid].size(); i++){
                if (i == 1) f << "->";
                f << G[gid][i];
            }
            f << "归约，且GOTO[" << status[status.size() - 1] << "," << reduced_symbol << "]=" << new_status << "入栈" << endl;
        }
        else {
            cout << "该语句有语法错误！（详情请查看分析过程文件sentence_" << time << ".txt）" << endl << endl;
            return 0;
        }
    }
    f.close();
    cout << "该语句有语法错误！（详情请查看分析过程文件sentence_" << time << ".txt）" << endl << endl;
    return 0;
}

int main() {
    cout << "请输入文法(以单行#结束)：" << endl;
    read_G();
    cout << endl;
    show_G();
    
    get_First();
    
    get_Closure();
    show_Closure();
    
    if (get_Table()) {
        show_Table();
        cout << endl;
        
        cout << "请输入需分析的语句（以#开头,并以#结束）：" << endl;
        int time = 0;
        while (1) {
            check(++time);
        }
    }
    system("pause");
}
/*————————————————
版权声明：本文为CSDN博主「xxxckyd灬潇」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_44245118/article/details/106217292
*/
