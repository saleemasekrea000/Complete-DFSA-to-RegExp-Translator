// Saleem Asekrea CS-04//
#include <bits/stdc++.h>
using namespace std;
/*define array of string for each line
 * which represent the FSA
 * first array collect the name of all state
 * second array collect all possible alpha
 * third for name of the initial state
 * and same for final states
 * alpha_trans collect all the transation in on string
 * state_trans collect all state in trans definition
 * input for take the input line by line
 * string error refer to the error in state the world which happen the error
 * (we will see the latter )
 * nondeterministic to know if the FSA is nondeterministic
 * size refer to the size of the array how many element in the array
 * mp the key is the state and the value is all the transation of this state
 * mp2 use it in determine if the FSA is nondeterministic
 * arr represent the states and transtion in undirected graph
 * the key is the state and the vector is the all connected node with the key
 * arr2 same of arr  but directed graph
 * we will see the details later
*/
string state[100]= {""};
string alpha[100]= {""};
string init_st[100]= {""};
string fin_st[100]= {""};
string trans[100]= {""};
string alpha_trans[100]= {""};
string state_trans[100]= {""};
string input;
string error;
int Non_deterministic= 0;
int size_state;
int size_alpha;
int size_init;
int size_final;
int size_state_trans;
map<string,set<string>> mp;
map<string,set<string>> mp2;
map<string,vector<string>> arr;
map<string,vector<string>> arr2;
map<string,int>indexing;
int count_indexing=0;
vector<vector<string>>R(50,vector<string>(50,""));
// calc the size of array : how many element in the array
int sizeofstr(string arr3[])
{
    int count = 0;
    while(!arr3[count].empty())
    {
        count++;
    }
    return count;
}

//create the graph as map which the key is the node and the vale is set with all
// connected node
/*
 * the state_trans array has all state in trans array
 * like off on off on without the transation
 * so off--->on also we make on---->off (undirected)
 * in the next loop we just make arr2 directed graph
 */
void Make_graph()
{
    int n= sizeofstr(state_trans);
    for(int i=0; i<n; i+=2)
    {
        arr[state_trans[i]].push_back(state_trans[i+1]);
        arr[state_trans[i+1]].push_back(state_trans[i]);
    }
    for(int i=0; i<n; i+=2)
    {
        arr2[state_trans[i]].push_back(state_trans[i+1]);
    }
}

/*
 * this function split the input according to the comma
 * example states=[on,off]
 * the result array is consist of tow element on and off
 */
void transform1(string s[])
{
    bool bt= true;
    int cnt=0;
    for(int i=0; i<input.size(); i++)
    {
        if(input[i]!='[')
        {
            continue;
        }
        else
        {
            i++;
            while(input[i]!=']')
            {
                if(input[i]==',')
                {
                    cnt++;
                    i++;
                }
                else
                {
                    bt=false;
                    s[cnt]+=input[i];
                    i++;
                }
            }
        }
    }
}

/*
 * this array store all the transation of the FSA
 */
void transform2()
{
    int cnt=0;
    int n=sizeofstr(trans);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<trans[i].size(); j++)
        {
            if(trans[i][j]=='>')
            {
                j++;
                while(trans[i][j]!='>')
                {
                    alpha_trans[cnt]+=trans[i][j];
                    j++;
                }
                cnt++;
            }
        }
    }
}


/*
 * this array store all the state  of the FSA
 */
void transform3()
{
    int cnt = 0;
    int n = sizeofstr(trans);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < trans[i].size(); j++)
        {
            while (trans[i][j]!='>')
            {
                state_trans[cnt]+=trans[i][j];
                j++;
            }
            j++;
            cnt++;
            while (trans[i][j]!='>')
            {
                j++;
            }
            j++;
            while (j < trans[i].size())
            {
                state_trans[cnt]+=trans[i][j];
                j++;
            }
            cnt++;

        }
    }
}

/*
 * same procedure but if we add transation exist before so
 * that mean the FSA is Nondeterministic
 */

bool Is_Deterministic()
{
    int n = sizeofstr(state_trans);
    for(int i=0; i<n; i+=2)
    {
        if(mp2[state_trans[i]].count(alpha_trans[i/2])==0)
        {
            mp2[state_trans[i]].insert(alpha_trans[i/2]);
        }
        else
        {
            Non_deterministic++;
        }
    }
    if(Non_deterministic>0)
    {
        return false;
    }
    return true;
}

/*
 * this function check if the input is correct
 * example states=[] all of this character is exist
 * and for all input
 */

bool check(string input1,string cur)
{
    int m=min(input1.size(),cur.size());
    int i=0;
    for( i=0; i<m; i++)
    {
        if(cur[i]!=input1[i])
        {
            return false;
        }
    }
    if(i!=input1.size())
    {
        return false;
    }
    if(cur[cur.size()-1]!=']')
    {
        return false;
    }
    return true;
}

/*
 * this function print the error message for the wrong input format
 */
void print_mal()
{
    cout << "E1: Input file is malformed" << endl;
    exit(0);
}

/*
 * take the input from the user and transfer the input to the array of string
 * and for each string invoke the function which check the validate of the
 * input
 */

void get_input(string s[],int i)
{
    string test1="states=[";
    string test2="alpha=[";
    string test3="initial=[";
    string test4="accepting=[";
    string test5="trans=[";
    getline(cin, input);
    if(i==1)
    {
        if(!check(test1,input))
        {
            print_mal();
        }
    }
    else if(i==2)
    {
        if(!check(test2,input))
        {
            print_mal();
        }
    }
    else if(i==3)
    {
        if(!check(test3,input))
        {
            print_mal();
        }
    }
    else if(i==4)
    {
        if(!check(test4,input))
        {
            print_mal();
        }
    }
    else if(i==5)
    {
        if(!check(test5,input))
        {
            print_mal();
        }
    }

    transform1(s);
}

// check if the state in the given string exist in the array of state
bool E_1_3(string s[],string crr[])
{
    int n = sizeofstr(s);
    int m = sizeofstr(crr);
    bool b=false;
    for(int i=0; i<n; i++)
    {
        b=false;
        for(int j=0; j<m; j++)
        {
            if(s[i]==crr[j])
            {
                b=true;
                break;
            }
            else
            {
                error=s[i];
                b=false;
            }
        }
        if(!b)
        {
            return false;
        }
    }
    return true;
}

/*
 * check if we have more than one initial state
 * by get the size of this array
 */

bool One_Initial()
{
    if(size_init>1)
    {
        return false;
    }
    return true;
}

/*
 * check if the we don't have initial state
 */

bool E_4()
{
    if(size_init==0)
    {
        return false;
    }
    return true;

}

/*
 * check the validate of words inside the [ ]
 * if it belongs to the letter number and _
 * by regular expression
 */

bool E_5()
{
    regex pattern_1("^[a-zA-Z0-9]+$");
    regex pattern_2("^[a-zA-Z0-9_]+$");
    for(int i=0; i<size_state; i++)
    {
        if(!regex_match(state[i], pattern_1))
        {

            return false;
        }
    }
    for(int i=0; i<size_alpha; i++)
    {
        if(!regex_match(alpha[i], pattern_2))
        {
            return false;
        }
    }
    return true;
}

/*
 * if the final state is not define
 * by know the size if the final state array
 */

bool W_1()
{
    if(size_final==0)
    {
        return false;
    }
    return true;
}

/*
 * iterate to the all nodes recursion way
 * just DFS and visited array too know if i visit this node or not
 */

void DFS(string curr_state, set<string> &visited)
{
    visited.insert(curr_state);
    for (auto neighbor : arr[curr_state])
    {
        if (visited.find(neighbor) == visited.end())
        {
            DFS(neighbor, visited);
        }
    }
}

/*
 * to know if some states are disjoint
 * its connected with DFS function
 * take the first state
 * if i didn't visit it yet visit it and go fo all children by DFS function
 * if i have more than one graph then its disjoint
 */

bool isDisjoint()
{
    set<string> visited;
    int num_components = 0;
    for (auto state : arr)
    {
        if (visited.find(state.first) == visited.end())
        {
            DFS(state.first,visited);
            num_components++;
        }
    }
    return num_components > 1;
}

/*
// Kleene's Algorithm to convert a FSA to a regular expression
// initialState: the initial state of the FSA
// finalState: the final state of the FSA
// k: the index of intermediate states to consider
// i: the index of the starting state of the transition
// j: the index of the ending state of the transition
 */
string Kleenes_Algorithm(const string& initialState,const string& finalState,int k,int i,int j)
{
    // base case, return the regular expression of the transition i j
    if(k==-1)
    {
        return R[i][j];
    }
    // recursively compute the regular expressions of the transitions
    // from i to j through all possible intermediate states
    // combine the regular expressions and return the final result
    return   "(" + Kleenes_Algorithm(initialState,finalState,k-1,i,k) + ")" +
             "(" + Kleenes_Algorithm(initialState,finalState,k-1,k,k) + ")*"+
             "(" + Kleenes_Algorithm(initialState,finalState,k-1,k,j) + ")" + "|" +
             "(" + Kleenes_Algorithm(initialState,finalState,k-1,i,j) + ")";
}
int main()
{
    freopen("input.txt","r",stdin);
    //freopen("result.txt","w",stdout);
    get_input(state,1);
    get_input(alpha,2);
    get_input(init_st,3);
    get_input(fin_st,4);
    get_input(trans,5);
    transform2();
    transform3();

    size_state = sizeofstr(state);
    size_alpha = sizeofstr(alpha);
    size_init = sizeofstr(init_st);
    size_final = sizeofstr(fin_st);
    size_state_trans = sizeofstr(state_trans);
    Make_graph();

    for(int i=0; i<size_state; i++)
    {
        indexing[state[i]]=i;
    }

// initialize R matrix with the transitions

    for(int i=0; i<size_state_trans; i+=2)
    {
        if( R[indexing[state_trans[i]]][indexing[state_trans[i+1]]]=="")
            R[indexing[state_trans[i]]][indexing[state_trans[i+1]]] =alpha_trans[i/2];
        else
            R[indexing[state_trans[i]]][indexing[state_trans[i+1]]]+="|"+alpha_trans[i/2];
    }
    
    // add epsilon transitions for each state to itself
    // and replace empty transitions with {}
    
    for(int i=0; i<size_state; i++)
    {
        for (int j = 0; j < size_state; j++)
        {

            if(i == j )
                if(R[i][j]=="")
                    R[i][j]+="eps";
                else
                    R[i][j]+="|eps";
                // cout<<" "<<i<<" "<<j<<" ";
                //cout << R[i][j] << " \n";
            else if(R[i][j]=="")
            {
                R[i][j]="{}";
            }
        }
    }

    if(size_state==0)
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;

    }
    if(size_alpha==0)
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;

    }
    if(!E_5())
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }

    if (!One_Initial())
    {
        cout << "E1 :Input file is malformed" << endl;
        return 0;
    }

    if (!E_4())
    {
        cout << "E2: Initial state is not defined" << endl;
        return 0;
    }

    if (!W_1())
    {
        cout << "E3: Set of accepting states is empty" << endl;
        return 0;
    }

    if (!E_1_3(init_st, state))
    {
        cout << "E4: A state '" << error << "' is not in the set of states"<<endl;
        return 0;
    }

    error="";

    if (!E_1_3(fin_st, state))
    {
        cout << "E4: A state '" << error << "' is not in the set of states"<<endl;
        return 0;
    }

    error="";

    if (!E_1_3(state_trans, state))
    {
        cout << "E4: A state '" << error << "' is not in the set of states"<<endl;
        return 0;
    }

    error="";

    if (!E_1_3(alpha_trans, alpha))
    {
        cout << "E5: A transition '" << error << "' is not represented in the alphabet"<<endl;
        return 0;
    }

    if (isDisjoint())
    {
        cout << "E6: Some states are disjoint" << endl;
        return 0;
    }

    if(!Is_Deterministic())
    {
        cout<<"E7: FSA is nondeterministic"<<endl;
        return 0;
    }

    for(int i=0 ; i+1<size_final ; i++)
    {
        cout << "(" << Kleenes_Algorithm(init_st[0],fin_st[i],size_state-1,indexing[init_st[0]],indexing[fin_st[i]]) << ")";
        cout << "|";
    }
    cout << "(" << Kleenes_Algorithm(init_st[0],fin_st[size_final-1],size_state-1,indexing[init_st[0]],indexing[fin_st[size_final-1]]) << ")";

    return 0;
}
