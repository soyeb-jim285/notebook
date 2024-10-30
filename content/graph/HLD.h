int query(int a, int b)
{
  int res = 0;
  for(;head[a]!=head[b];b = parent[head[b]])
  {
    if(depth[head[a]]>depth[head[b]])
    {
      swap(a, b);
    }
    int cur_path_max = segquery(1, 0, n-1, pos[head[b]], pos[b]);
    res = MAX(res, cur_path_max);
  }
  if(depth[a]>depth[b])
  {
    swap(a, b);
  }
  int cur_path_max = segquery(1, 0, n-1, pos[a]+1, pos[b]);
  res = MAX(res, cur_path_max);
  return res;
}
 
int dfs(int ind, int p)
{
  int sz = 1;
  int mx_sz = 0;
  parent[ind] = p;
  depth[ind] = depth[p]+1; 
  for(auto [x, y]: adj[ind])
  {
    if(x==p)continue;
    int c_size = dfs(x, ind);
    edgVal[x] = y;
    sz += c_size;
    if(c_size>mx_sz)
    {
      heavy[ind] = x;
      mx_sz = c_size;
    }
  }
  return sz;
}
 
void decompose(int ind, int h)
{
  head[ind] = h;
  pos[ind] = cur_pos++;
  euler.push_back(ind);
 
  if(heavy[ind]!=-1)decompose(heavy[ind], h);
  for(auto [x, y]: adj[ind])
  {
    if(x!=heavy[ind] and x!=parent[ind])decompose(x, x);
  }
}
