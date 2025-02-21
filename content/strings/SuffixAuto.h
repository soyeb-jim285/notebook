/**
 * Author: Farhan
* Description: Suffix Automaton
* Time: O(N)
*/
struct SuffixAutomaton {
  struct State {
    int len, link;
    map<char, int> next;
    int first_pos;
    ll cnt, cnt_paths;
  };

  vector<State> st;
  int last;

  SuffixAutomaton(string &s){
    st.push_back({0, -1, {}, 0, 0, 0});
    last = 0;
    for(char c : s){
      int cur = st.size(); 
      st.push_back({st[last].len + 1, 0, {}, st[last].len + 1, 1, 0});
      int p = last;
      while(p != -1 && !st[p].next.count(c)){
        st[p].next[c] = cur;
        p = st[p].link;
      }
      if(p == -1){
        st[cur].link = 0;
      } 
      else{
        int q = st[p].next[c];
        if(st[q].len == st[p].len + 1){
          st[cur].link = q;
        }
        else{
          int clone = st.size();
          st.push_back({st[p].len + 1, st[q].link, st[q].next, st[q].first_pos, 0, 0});
          while(p != -1 && st[p].next[c] == q){
            st[p].next[c] = clone;
            p = st[p].link;
          }
          st[q].link = st[cur].link = clone;
        }
      }
      last = cur;
    }
    vector<int> count(st.size(), 0);
    for (int i = 0; i < st.size(); i++) count[st[i].len]++;
    for (int i = 1; i < st.size(); i++) count[i] += count[i - 1];
    vector<int> order(st.size());
    for (int i = st.size() - 1; i >= 0; i--) order[--count[st[i].len]] = i;
    for (int i = st.size() - 1; i > 0; i--) st[st[order[i]].link].cnt += st[order[i]].cnt;
    for(int i = st.size() - 1; i >= 0; i--){
      int v = order[i];
      st[v].cnt_paths = 1;
      for(auto &p : st[v].next){
        st[v].cnt_paths += st[p.second].cnt_paths;
      }
    } 
  }
  bool check_occur(string &t){
    int cur = 0;
    for(char c : t){
      if(!st[cur].next.count(c)) return 0;
      cur = st[cur].next[c];
    }
    return 1;
  }
  ll num_of_occur(string &t){
    int cur = 0;
    for(char c : t){
      if(!st[cur].next.count(c)) return 0;
      cur = st[cur].next[c];
    }
    return st[cur].cnt;
  }
  ll num_of_dif_substr(){
    ll sub = 0;
    for(int i = 1; i < st.size(); i++){
      sub += st[i].len - st[st[i].link].len;
    }
    return sub;
  }
  ll tot_len_of_dif_substr(){
    ll total_length = 0;
    for (int i = 1; i < st.size(); i++) {
      ll shortest_substr_len = st[st[i].link].len + 1;
      ll longest_substr_len = st[i].len;
      ll num_of_substr = longest_substr_len - shortest_substr_len + 1;
      total_length += num_of_substr * (longest_substr_len + shortest_substr_len) / 2LL;
    }
    return total_length;
  }
  string kth_substring(ll k){
    ll tot_substr = 0;
    for(auto &p : st[0].next){
      tot_substr += st[p.second].cnt_paths;
    }
    if(tot_substr < k) return "No such line.";
    string ans = "";
    int cur = 0;
    while(k > 0){
      for(auto &p : st[cur].next){
        int v = p.second;
        if(st[v].cnt_paths >= k){
          ans.push_back(p.first);
          k--;
          cur = v;
          break;
        }
        else{
          k -= st[v].cnt_paths;
        }
      }
    }
    return ans;
  }
  string smallest_cyclic_shift(string &s) {
    string ss = s + s;
    SuffixAutomaton sa(ss);
    int n = s.length();
    string ans = "";
    int cnt = 0, cur = 0;
    while(cnt < n){
      char cur_ch = 'z';
      for(auto &p : sa.st[cur].next){
        if(p.second > 0){
          cur_ch = p.first;
          cur = p.second;
          break;
        }
      }
      ans.push_back(cur_ch);
      cnt++;
    }
    return ans;
  }
  int first_occur(string &t){
    int cur = 0;
    for(char c : t){
      if(!st[cur].next.count(c)) return -1;
      cur = st[cur].next[c];
    }
    return st[cur].first_pos - t.length() + 1;
  }
  string lon_com_substr(string &t){
    int v = 0, l = 0, best = 0, best_pos = 0;
    for(int i = 0; i < t.size(); i++){
      while(v && !st[v].next.count(t[i])){
        v = st[v].link;
        l = st[v].len;
      }
      if(st[v].next.count(t[i])){
        v = st[v].next[t[i]];
        l++;
      }
      if(l > best){
        best = l;
        best_pos = i;
      }
    }
    return t.substr(best_pos - best + 1, best);
  }
  int lon_com_substr_multiple(vector<string> &str){
    int ans = 0;
    vector<int> minmax(st.size(), str[0].size() + 1);
    for(int i = 1; i < str.size(); i++){
      int cur = 0, len = 0;
      vector<int> mx(st.size(), 0);
      for(int j = 0; j < str[i].size(); j++){
        while(cur && !st[cur].next.count(str[i][j])){
          cur = st[cur].link;
          len = st[cur].len;
        }
        if(st[cur].next.count(str[i][j])){
          cur = st[cur].next[str[i][j]];
          len++;
        }
        mx[cur] = max(mx[cur], len);
      }
      for(int i = 1; i < st.size(); i++){
        minmax[i] = min(minmax[i], mx[i]);
      }
    }
    for(int i = 1; i < st.size(); i++){
      ans = max(ans, minmax[i]);
    }
    return ans;
  }
  vector<ll> substr_by_len(int len) {
    vector<ll> res(len + 5, 0);
    vector<int> min_len(st.size(), 0);
//Also can find using bfs. CSES 1st submission
    for(int i = 1; i < st.size(); i++){
      min_len[i] = st[st[i].link].len + 1;
    }
//Also can use seg tree lazy update. As there is only one
//query after all updates. So, this process works.
    for(int i = 1; i < st.size(); i++){
      res[min_len[i]]++;
      res[st[i].len + 1]--;
    }
    for(int i = 1; i <= len; i++){
      res[i] += res[i - 1];
    }
    return res;
  }
  void longest_repeating_substring(string &s) {
    int max_len = 0;
    int best_state = -1;  
    for (int i = 1; i < st.size(); i++) {
      if (st[i].cnt > 1 && st[i].len > max_len) {
        max_len = st[i].len;
        best_state = i;
      } else if (st[i].cnt > 1 && st[i].len == max_len) {
        int len = st[i].len;
        string current_substring = st[best_state].first_pos == -1 ? "" : s.substr(st[best_state].first_pos - len, len);
        string candidate_substring = st[i].first_pos == -1 ? "" : s.substr(st[i].first_pos - len, len);
        if (candidate_substring < current_substring) {
          best_state = i;
        }
      }
    }
    if (best_state == -1) {
      cout << "-1\n";
      return;
    }
    int len = st[best_state].len;
    int pos = st[best_state].first_pos;
    cout << s.substr(pos - len, len) << "\n";
  }
  void display() {
    cout << "State : Link, length, Transitions" << endl;
    for (int i = 0; i < st.size(); i++) {
      cout << i << " : " << st[i].link << ", " << st[i].len << ", ";
      for (auto &p : st[i].next) {
        cout << p.first << "->" << p.second << " ";
      }
      cout << endl;
    }
  }
};
