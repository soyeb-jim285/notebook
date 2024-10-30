void push(int ind,int l,int r){
    if(lazy[ind]!=0){
        tree[ind]+=(r-l+1)*lazy[ind];
        if(l!=r) lazy[2*ind]+=lazy[ind],lazy[2*ind+1]+=lazy[ind];
        lazy[ind]=0;
    }
}

void update(int ind,int l,int r,int ql,int qr,int val){
    push(ind,l,r);
    if(l>r||l>qr||r<ql) return;
    if(l>=ql&&r<=qr){
        lazy[ind]+=val;
        push(ind,l,r);
        return;
    }
    int mid=(l+r)/2;
    update(2*ind,l,mid,ql,qr,val);
    update(2*ind+1,mid+1,r,ql,qr,val);
    tree[ind]=tree[2*ind]+tree[2*ind+1];
}

int query(int ind,int l,int r,int ql,int qr){
    push(ind,l,r);
    if(l>qr||r<ql) return 0;
    if(l>=ql&&r<=qr) return tree[ind];
    int mid=(l+r)/2;
    return query(2*ind,l,mid,ql,qr)+query(2*ind+1,mid+1,r,ql,qr);
}
