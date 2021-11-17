#include<bits/stdc++.h>
#include <windows.h>
using namespace std;
//define Q 8
#define K 4
#define neighbor_size 16
int initial_state[14][14];
int next_best_neighbor[14][14];
int s,Q;
class states
{
public:
    put_data(int a[]){
        for(i=0;i<Q;i++){///initializing matrix to 0
            ar[i]=0;
            for(j=0;j<Q;j++){
                q[i][j]=0;
            }
        }
        for(i=0;i<Q;i++){
            ar[i]=a[i];
            q[Q-ar[i]][i]=1;///Putting 1 if queen presence
        }
    }
    print(){
        for(i=0;i<Q;i++){
            cout<<ar[i];
        }

    }
public:
    int q[14][14];
    int ar[14];
    int h,i,j;
    int state_no;
};
states state[neighbor_size];

int check_quality(states obj){ ///heuristic function,,,which find the number of conflicting pair
    int n,h=0,u1,u2,l1,l2,r,i,j;
    for(i=0;i<Q;i++){
        n=Q-obj.ar[i];
        u1=n-1;
        u2=i+1;
        l1=n+1;
        l2=i+1;
        r=i;
        for(j=i;j<Q;j++){
            if(r<Q && r!=i){///checking row
                if(obj.q[n][r]==1){
                    h++;
                }
            }
            r++;
            if(u1>=0 && u2<Q){///checking upper diagonal
                if(obj.q[u1][u2]==1){
                    h++;
                }
            }
            u1--;u2++;

            if(l1<Q && l2<Q){///checking lower diagonal
                if(obj.q[l1][l2]==1){
                    h++;
                }
            }
            l1++;l2++;

        }
    }
    return h;

}
get_neighbor(int a[]){///creating neighbor  randomly ,,,,,for each state we create 4 neighbor
    int position,value,i,j,k;
   // srand();
    for(i=0;i<K;i++){

        for(j=0;j<Q;j++){
                for(k=0;k<Q;k++){
                    position=rand()%Q;
                    value=rand()%Q+1;
                    a[position]=value;
                }
        }

        state[s].put_data(a);
        state[s].h=check_quality(state[s]); ///calculating heuristic value for neighbor
        state[s].state_no=s;
        s++;
    }
}
get_initial_state(){ ///first of all we create 4 random state
    int i,j;
    srand(time(NULL));
    for(i=0;i<K;i++){
        for(j=0;j<Q;j++){
            initial_state[i][j]=rand()%Q+1;
        }

    }
}
print_solution(states s){

    for(int i=0;i<Q;i++){

        for(int j=0;j<Q;j++){
            cout<<"|";
            cout<<s.q[i][j]<<" ";
        }
        cout<<endl;
    }
}
int local_beam_search(){
    int loop=0,i,j,k;
    int temp_ar[8];
    int state_no[neighbor_size];
    int value_h[neighbor_size];
    int temp,temp1;
    s=0;

    for(i=0;i<K;i++){  ///creating neighbor from initial k state
            for(j=0;j<Q;j++){
                 temp_ar[j]=initial_state[i][j];
            }
            get_neighbor(temp_ar);
    }
    while(true){
        if(loop==50){
            cout<<"----------------------------------------------"<<endl;
            cout<<"Global optimal is not found"<<endl;
            cout<<"Local optimal solution is "<<endl;
            cout<<"**********************************************"<<endl;
            for(j=0;j<Q;j++){
                    cout<<next_best_neighbor[0][j];
            }
            cout<<" H : "<<value_h[0]<<endl<<endl;
            cout<<"**********************************************"<<endl;
            break;
        }
        cout<<"----------------------------------------------"<<endl;
        cout<<"Neighbor state: "<<endl;
        cout<<"----------------------------------------------"<<endl;
        for(i=0;i<neighbor_size;i++){
            if(state[i].h==0){      ///checking if any of the neighbor is a solution
                cout<<"**********************************************"<<endl;
                cout<<"Solution found"<<endl;
                cout<<"**********************************************"<<endl;
                for(k=0;k<Q;k++){
                    cout<<state[i].ar[k];
                }
                cout<<" H: "<<state[i].h<<endl;
                cout<<"----------------------------------------------"<<endl;
                print_solution(state[i]);
                return 0;
            }
            value_h[i]=state[i].h;
            state_no[i]=state[i].state_no;
            state[i].print();
            cout<<" H: "<<state[i].h<<endl;
        }
        for(i=0;i<neighbor_size;i++){ ///sorting state according to their value of h
                                      ///for selecting next best K neighbor
            for(j=i+1;j<neighbor_size;j++){
                if(value_h[i]>value_h[j]){
                    temp=value_h[i]; temp1=state_no[i];
                    value_h[i]=value_h[j];state_no[i]=state_no[j];
                    value_h[j]=temp;state_no[j]=temp1;

                }
            }
        }
        for(i=0;i<K;i++){///copying neighbor state for creating neighbor of those neighbor
            for(j=0;j<Q;j++){
                 next_best_neighbor[i][j]=state[state_no[i]].ar[j];
            }
        }
        s=0;
        cout<<"----------------------------------------------"<<endl;
        cout<<endl<<"Best neighbor are: "<<endl;
        cout<<"----------------------------------------------"<<endl;
        for(i=0;i<K;i++){
            for(j=0;j<Q;j++){
                 cout<<next_best_neighbor[i][j];
            }
            cout<<endl;

        }
        //Sleep(2000);
        for(i=0;i<K;i++){///creating neighbor for best 4 neighbor
            for(j=0;j<Q;j++){
                 temp_ar[j]=next_best_neighbor[i][j];
            }
            get_neighbor(temp_ar);
        }
        loop++;
  }
}

int main(){
    int i,j;
    cout<<"Enter the number of queen: ";
    cin>>Q;
    get_initial_state();
    cout<<"----------------------------------------------"<<endl;
    cout<<"Initial state: "<<endl;
    cout<<"----------------------------------------------"<<endl;
      for(i=0;i<K;i++){
        for(j=0;j<Q;j++){
            cout<<initial_state[i][j];
        }
        cout<<endl;
        }

    local_beam_search();

}
