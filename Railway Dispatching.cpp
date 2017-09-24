#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> res;                            //Save the result
int step = 0;

//Create the matrix according to the rule
void CreateMatrix( int **matrix, int *num, const int cnt )
{
    for ( int i = 0; i < cnt-2; ++i ) {
        for ( int j = i+1; j < cnt-1; ++j ) {
            if ( num[i] < num[j] ) {
                for ( int k = j+1; k < cnt; ++k ) {
                    if ( num[i] > num[k] )
                        matrix[num[i]-1][num[j]-1] = matrix[num[j]-1][num[i]-1] = 1;
                }
            }
        }
    }
}

//Judge whether the 'number' can be pushed into 'oneStack' according to the rule(matrix)
bool Push( stack<int> oneStack, int **matrix, int number )
{
    while ( oneStack.size() != 0 ) {
        if ( matrix[oneStack.top()-1][number-1] == 1 ) {
            return false;
        }
        oneStack.pop();
    }

    return true;
}

//Dispatch the trains(numbers)
//The parameter 'next' represents the number we want next
//The parameter 'curr' represents the index of the number to be process
void Dispatch( vector<stack<int>> &buffers, int **matrix, int *num, const int cnt, int curr, int next )
{
    if ( res.size() == cnt )
        return;

    bool out = false;                       //whether a number is out
    if ( curr < cnt && num[curr] == next ) {

        res.push_back( next++ );
        ++curr;
        out = true;
        cout << "The number " << next-1 << " is poped from original queue." << endl;
        ++step;

    } else if ( !buffers.empty() ) {        //judge whether to pop

        for ( auto it = buffers.begin(); it != buffers.end(); ++it ) {
            if ( it->empty() )
                continue;

            if ( it->top() == next ) {
                res.push_back( next++ );
                it->pop();
                out = true;

                cout << "The number " << next-1 << " is poped from stack[" << it-buffers.begin()+1 << ']' << endl;
                ++step;
            }
        }

    } 

    if ( !out ) {                           //to push ( make sure that curr < cnt )

        bool isPushed = false;
        for ( auto it = buffers.begin(); it != buffers.end(); ++it ) {
            if ( Push( *it, matrix, num[curr] ) ) {
                it->push( num[curr] );
                isPushed = true;

                cout << "The number " << num[curr] << " is pushed into stack[" << it-buffers.begin()+1 << ']' << endl; 
                ++step;

                break;
            }
        }

        if ( !isPushed ) {
            buffers.push_back( stack<int>( {num[curr]} ) );

            cout << "The number " << num[curr] << " is pushed into a new stack[" 
                 << buffers.end()-buffers.begin() << ']' << endl;
            ++step;
        }

        ++curr;

    }

    Dispatch( buffers, matrix, num, cnt, curr, next );
}

int main()
{
    int cnt = 0;
    cin >> cnt;

    int *num = new int[cnt];

    int **matrix = new int* [cnt];
    for ( int i = 0; i < cnt; ++i )
        matrix[i] = new int[cnt]();

    for ( int i = 0; i < cnt; ++i )
        cin >> num[i];
    
    CreateMatrix( matrix, num, cnt );

    vector<stack<int>> buffers;

    // cout << " ";
    // for ( int i = 1; i <= cnt; ++i ) {
    //     cout << "  " << i;
    // }
    // cout << endl << endl;

    // for ( int i = 1; i <= cnt; ++i ) {
    //     cout << i;
    //     for ( int j = 0; j < cnt; ++j ) {
    //          cout << "  " << matrix[i-1][j];
    //     }
    //     cout << endl << endl;
    // }

    Dispatch( buffers, matrix, num, cnt, 0, 1 );

    for ( auto n : res ) {
        cout << n << " ";
    }
    cout << endl;

    cout << "The total number of stacks is " << buffers.size() << '.' << endl
         << "The total number of steps is " << step << '.' << endl;
    
    delete [] num;
    for ( int i = 0; i < cnt; ++i )
        delete [] matrix[i];
    delete [] matrix;

    getchar();
    getchar();

    return 0;
}