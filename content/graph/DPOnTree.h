/**
 * Author: Farhan
 * Description:DPonTree
 */
void dfs(int ind, int p)
{
  int tmp = 0;
  int s=1;
  for(auto i: adj[ind])
  {
    if(i!=p)
    {
      dfs(i, ind);
      tmp += (down[i]+sz[i]);
      s+=sz[i];
    }
  }
  sz[ind] = s;
  down[ind] = tmp;
}
void dfs2(int ind, int p)
{
  if(ind!=p)up[ind] += (up[p] + n - sz[p]), up[ind]++;
  int tmp=0;
  for(auto i: adj[ind])
  {
    if(i!=p)
    {
      up[i] += tmp;
      tmp += (down[i]+2LL*sz[i]);
    }
  }
  reverse(adj[ind].begin(), adj[ind].end());
  tmp = 0;
  for(auto i: adj[ind])
  {
    if(i!=p)
    {
      up[i] +=tmp;
      tmp += (down[i]+2LL*sz[i]);
    }
  }
  ans[ind] = down[ind] + up[ind];
  for(auto i: adj[ind])if(i!=p)dfs2(i, ind);
}

