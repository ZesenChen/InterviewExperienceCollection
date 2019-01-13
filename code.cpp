#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

//递归的快排 
void quicksort(vector<int>& num, int l, int r){
	if(l>=r) return;
	int i = l, j = r, x = num[l];
	while(i<j){
		while(i<j&&num[j]>=x) --j;
		if(i<j) num[i++] = num[j];
		while(i<j&&num[i]<=x) ++i;
		if(i<j) num[j--] = num[i];
	}
	num[i] = x;
	quicksort(num,l,i-1);
	quicksort(num,i+1,r);
}

void push2(stack<int>& index, int l, int r){
	index.push(r);
	index.push(l);
}
//非递归的快排 
void qsort(vector<int>& num, int l, int r){
	stack<int> s;
	push2(s,l,r);
	while(!s.empty()){
		int l = s.top(); s.pop();
		int r = s.top(); s.pop();
		int i = l, j = r, x = num[l];
		while(i<j){
			while(i<j&&num[j]>=x) --j;
			if(i<j) num[i++] = num[j];
			while(i<j&&num[i]<=x) ++i;
			if(i<j) num[j--] = num[i];
		}
		num[i] = x;
		if(i-1>l) push2(s,l,i-1);
		if(r>i+1) push2(s,i+1,r);
	}
}

//递归归并排序 
void merge(vector<int>& num, int l, int mid, int r){
	int i = l, j = mid+1;
	vector<int> temp;
	while(i<=mid&&j<=r){
		if(num[i]<=num[j]) temp.push_back(num[i++]);
		else temp.push_back(num[j++]);
	}
	while(i<=mid) temp.push_back(num[i++]);
	while(j<=r) temp.push_back(num[j++]);
	for(int i = 0; i < temp.size(); ++ i) num[l+i] = temp[i];
}

void mergesort(vector<int>& num, int l, int r){
	if(l>=r) return;
	int mid = (l+r)/2;
	mergesort(num,l,mid);
	mergesort(num,mid+1,r);
	merge(num,l,mid,r);
}

//非递归归并排序 
void mergesort(vector<int>& num, int n){
	int low = 0, size = 1;
	while(size<=n){
		low = 0;
		while(low+size<=n){
			int mid = low+size-1, high = mid+size;
			if(high>n) high = n;
			merge(num,low,mid,high);
			low = high+1;
		}
		size*=2;
	}
}

//用快排分割思想求topk 
int partition(vector<int>& num, int l, int r){
	int i = l, j = r, x = num[l];
	while(i<j){
		while(i<j&&num[j]>=x) --j;
		if(i<j) num[i++] = num[j];
		while(i<j&&num[i]<=x) ++i;
		if(i<j) num[j--] = num[i];
	}	
	num[i] = x;
	return i;
} 
 
int kthNum(vector<int>& num, int k){
	int l = 0, r = num.size()-1;
	int index = partition(num,l,r);
	while(index!=k-1){
		if(index<k-1) l = index+1;
		else r = index-1;
		index = partition(num,l,r);
	}
	return num[index];
}



//用优先队列实现topk 
struct cmp{
	bool operator()(const int a, const int b){
		return a<b;
	}
};

int kthNum2(vector<int>& num, int k){
	priority_queue<int,vector<int>,cmp> q;
	if(k>num.size()) return -1;
	for(int i = 0; i < num.size(); ++ i){
		q.push(num[i]);
		if(q.size()>k) q.pop();
	}
	return q.top();
}

int main(){
	int a[10] = {10,2,1,3,4,5,9,75,6,8};
	vector<int> num(a,a+10);
	cout << kthNum2(num,3) << endl;
	return 0;
} 
