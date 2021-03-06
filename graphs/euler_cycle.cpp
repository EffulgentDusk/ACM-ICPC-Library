// Las listas de adyacencia se deben ordenar de forma ascendente para
// obtener el ciclo lexicografico minimo deacuerdo a la numeracion
// de las aristas

#define MAX_V 44
#define MAX_E 1995

int N,deg[MAX_V],eu[MAX_E],ev[MAX_E];
list<int> G[MAX_V],L;
bool visited[MAX_V];
stack<int> S;
queue<int> Q;

bool connected(){
    int cont = 0;
    Q.push(0);
    memset(visited,false,sizeof(visited));
    visited[0] = true;
    
    while(!Q.empty()){
        int v = Q.front(); Q.pop();
        ++cont;
        
        for(list<int>::iterator it = G[v].begin();it!=G[v].end();++it){
        	int e = *it;
        	int w = eu[e]==v? ev[e] : eu[e];
        	
            if(!visited[w]){
                visited[w] = true;
                Q.push(w);
            }
        }
    }
    
    return cont==N;
}

bool eulerian(){
    if(!connected()) return false;
    
    for(int v = 0;v<N;++v)
        if(deg[v]&1)
            return false;
    
    return true;
}

void take_edge(int v, int w){
    --deg[v]; --deg[w];
    int e = G[v].front();
    G[v].pop_front();
    
    for(list<int>::iterator it = G[w].begin();it!=G[w].end();++it){
        if(*it==e){
            G[w].erase(it);
            break;
        }
    }
}

void euler(int v){
    while(true){
        if(G[v].empty()) break;
        int e = G[v].front();
        int w = eu[e]==v? ev[e] : eu[e];
        S.push(e);
        take_edge(v,w);
        v = w;
    }
}

bool find_cycle(int s){
    if(!eulerian()) return false;
    
    int v = s,e;
    L.clear();
    
    do{
        euler(v);
        e = S.top(); S.pop();
        L.push_back(e);
        
        v = eu[e]==v? ev[e] : eu[e];
    }while(!S.empty());
    
    return true;
}

void print_cycle(int s){
    if(!find_cycle(s)) printf("-1\n");
    else{
    	bool first = true;
    	reverse(L.begin(),L.end());
        for(list<int>::iterator e = L.begin();e!=L.end();++e){
        	if(!first) printf(" ");
        	first = false;
            printf("%d",1+(*e));
        }
        printf("\n");
    }
}
