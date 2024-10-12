#include <iostream>
using namespace std;

template <typename Item>
struct node{
		
	Item item;
	node<Item> *next;
	
	node(Item _item, node<Item> *_next){
		item = _item;
		next = _next;
	}

};

template <typename Item>
class list{
	node<Item> *head;
	node<Item> *tail;
	
	public:
		
	list(node<Item> *_head = NULL, node<Item> *_tail = NULL){
		head = _head;
		tail = _tail;
	}		
	
	int longitud();
	void insertaAlInicio(Item item);
	void insertaAlFinal(Item item);
	node<Item>* regresaNth(int N);
	void limpiar();
	node<Item>* primero();
	node<Item>* ultimo();
	void quitaPrimero();
	void quitaUltimo();	
	
	~list(){
		limpiar();
	}
};

template<typename Item>
int list<Item>::longitud(){
	int len=0;
	
	node<Item> *copy = head;
	
	while(copy!=NULL){
		len++;
		copy = copy->next; 
	}
	
	return len;
}

template <typename Item>
void list<Item>::insertaAlInicio(Item item){
	head = new node<Item>(item, head);
	if(tail==NULL)
		tail = head;
	
	return;
}

template <typename Item>
void list<Item>::insertaAlFinal(Item item){
	if(head == NULL){
		insertaAlInicio(item);
		return;
	}
		 
	tail->next = new node<Item>(item, NULL);
	tail = tail->next;
	
	return;
}

template <typename Item>
node<Item>* list<Item>::regresaNth(int N){
	if(N <= 0)
		return NULL;
	
	node<Item> *copy = head;
	
	for(int i=1; i<N && copy != NULL; i++)
		copy = copy->next;
		
	return copy;
}

template <typename Item>
void list<Item>::limpiar(){
	node<Item> *aux;
	
	while (head != NULL){
		aux = head;
		head = aux->next;
		delete aux;
	}
	
	tail=NULL;
	
	return;
}

template <typename Item>
node<Item>* list<Item>::primero(){
	return head;
}

template <typename Item>
node<Item>* list<Item>::ultimo(){
	return tail;
}

template <typename Item>
void list<Item>::quitaPrimero(){
	if(head == NULL)
		return;
	
	if(tail==head)
		tail=NULL;
		
	node<Item> *aux = head;
	head = aux->next;
	
	delete aux;
	
	return;
}

template <typename Item>
void list<Item>::quitaUltimo(){
	
	if(tail == NULL)
		return;	
		
	if(tail==head){
		tail=NULL;
		delete head;
		head=NULL;
		
		return;
	}
		
	node<Item> *copy = head;
		
	while(copy->next != tail)
		copy = copy->next;
			
	delete tail;
	tail = copy;	
	tail->next = NULL;
	
	return;
}

template <typename Item>
class Stack{
	list<Item> stack;
	
	public:
	
	Stack(){
		stack = list<Item>();
	}
	
	void push(Item item){
		stack.insertaAlInicio(item);
		return;
	}
	
	void pop(){
		stack.quitaPrimero();
		return;
	}
	
	int size(){
		return stack.longitud();
	}
	
	Item peek(){
		/*node<Item> *top = lista.regresaNth(1);
		return top == NULL ? 0 : top->item;*/
		return stack.regresaNth(1)->item;
	}
	
	bool empty(){
		return (stack.regresaNth(1) == NULL) ? true : false;
	}
	
	~Stack(){
		stack.limpiar();
	}
};

template <typename Item>
class tree{
	public:
		
	Item item;
	
	tree *left;
	tree *right;
	tree *dad;
	
	tree(){
		left=NULL; right=NULL; dad=NULL;
	}
	
	tree(Item _item, tree<Item> *_left=NULL, tree<Item> *_right=NULL, tree<Item> *_dad=NULL){
		item=_item; left=_left; right=_right; dad=_dad;
	}
	
	void join(tree<Item> *tree1, tree<Item> *tree2){
		left=tree1; right=tree2;
		tree1->dad=this; tree2->dad=this;
	}
	
	bool operator>(const tree<Item> &right){
		return item>right.item;
	}
};

template <typename Item>
class priority_queue{
	Item *pq;
	int maxN, N;
	
	void fixUp(int k){
		while(k>1 && pq[k/2] > pq[k]){
			Item temp=pq[k/2];
			pq[k/2]=pq[k];
			pq[k]=temp;
			
			k=k/2;
		}
	}
	
	void fixDown(int k){
		while(2*k <= N){
			int j=2*k;
			
			if(j<N && pq[j] > pq[j+1])
				j++;
				
			if(!(pq[k]>pq[j]))
				break;
			
			Item temp=pq[k];
			pq[k]=pq[j];
			pq[j]=temp;
			
			k=j;
		}
	}
	public:
	
	priority_queue(int _maxN){
		maxN = _maxN;
		pq=new Item[maxN+1];
		N=0;
	}
	
	~priority_queue(){
		delete[] pq;
	}
	
	void insert(Item x){
		if(N>maxN){
			cout << "priority queue overflow"; return;
		}
			
		pq[++N]=x;
		fixUp(N);
	}
	
	Item delMin(){
		Item min=pq[1];
		pq[1]=pq[N];
		pq[N]=min;
		
		N--;
		fixDown(1);
		
		return min;
	}
	
	int size(){
		return N;
	}
};

class Mask{
	long long unsigned int mask;
	
	public:
		
	Mask(){
		mask=0;
	}
		
	void addBit(int n){
		if(0<=n && n<=63){
			long long unsigned int aux = 1LL<<n;
			mask = mask | aux;	
		}
	}

	void quitBit(int n){
		if(0<=n && n<=63){
			long long unsigned int aux = 1LL<<n;
			aux = ~aux;
			mask = mask & aux;	
		}
	}

	bool ask(int n){
		if(0<=n && n<=63){
			Mask aux; aux.mask=mask;
			aux.addBit(n);
		
			if(aux.mask == mask)
				return true;
		}
		return false;
	}
	
	void reset(){
		mask=0;
	}
	
	long long unsigned int * pointerToMask(){
		return &mask;
	}
};



