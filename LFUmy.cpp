#include <iostream>
#include <vector>
#include <queue>
#include <map>
// Step-1 : Initialize count as 0.
// Step-2 : Create a vector / array of size equal to memory capacity.
//             Create a map to store frequency of pages
// Step-3 : Traverse elements of pages[]
// Step-4 : In each traversal:
//        if(element is present in memory):
//             remove the element and push the element at the end
//             increase its frequency
//        else:
//             if(memory is full)
//                  remove the first element and decrease frequency of 1st element
//             Increment count
//             push the element at the end and increase its frequency
//       Compare frequency with other pages starting from the 2nd last page
//       Sort the pages based on their frequency and time at which they arrive
//       if frequency is same, then, the page arriving first must be placed first

// C++ program to illustrate
// page faults in LFU

using namespace std;
int main()
{
    int n, m, i, j, k;
    int max_index;
    cout << "Enter number of frames\n";
    cin >> n;
    cout << "Enter number of processes\n";
    cin >> m;
    vector<int> d(m);
    vector<int> p(m); // 원소의 개수가 프로세스수 만큼의 백터를 만들고, 0으로 초기화
    cout << "Enter processes\n";
    for (i = 0; i < m; i++)
    {
        cin >> p[i];
    }
    vector<vector<int> > a(n, vector<int>(m, -1)); // 백터를 넣는 백터a를 만들고 그안에 n개의 자리가 있으며 그것을 백터로 초기화 하는데 이 백터의 길이는m 개이며 -1로 초기화.\
     즉 이중배열 백터를 만든거임, 지금 a[][] 이런 게 있는거임.
    vector<int> mp(n);                             //페이지 참조 횟수 테이블, 참조안되면 ++ 되면 0으로 바꾸고 나머지 ++, 그리고 몇번째 프레임인지 확인하기 위해서 가장 큰 index값 반환.해서 그곳에 replacement 발생시킴
    map<int, int> lfmp;                            //맵 mp 와 lfmp 두개가 생김

    // 프로세스 하나씩 확인하기 시작함.
    //--------------------------------------------여기부터 프레임에 넣기 시작함
    for (i = 0; i < m; i++) //프로세스 배열
    {
        for (j = 0; j < n; j++) //프레임 배열
        {
            if (a[j][i] == -1) // 페이지 폴트이며, 프레임에 아무것도 없음
            {
                a[j][i] = p[i];
                for (int z = 0; z < n; z++)
                {
                    mp[z]++;
                }
                mp[j] = 0;
                break;
            }
            else if (a[j][i] != -1 && a[j][i] != p[i]) //페이지 폴트가 발생, 프레임에 페이지가 들어가있을시
            {
                int max_index = max_element(mp.begin(), mp.end()) - mp.begin(); // 페이지중 사용이 젤 적게 된, 즉 가장 높은 값을 가진 mp의 인덱스를 반환
                cout << max_index << endl;
                a[max_index][i] = p[i];
                for (int h = 0; h < n; h++)
                {
                    mp[h]++;
                }
                mp[max_index] = 0;
                break;
            }
            if (a[j][i] == p[i]) // 페이지 히트가 발생
            {
                for (int z = 0; z < n; z++)
                {
                    mp[z]++;
                }
                mp[j] = 0;
            }
        }
    }
    //------------------------프로세스 히트 검색

    int hit = 0;
    vector<int> hitv(m);
    for (i = 1; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (p[i] == a[j][i - 1])
            {
                hit++;
                hitv[i] = 1;
                break;
            }
        }
    }

    //----------------------------------------------여기부터 출력임

    cout << "Process ";
    for (i = 0; i < m; i++)
    {
        cout << p[i] << " ";
    }
    cout << '\n';
    for (i = 0; i < n; i++)
    {
        cout << "Frame " << i << " ";
        for (j = 0; j < m; j++)
        {
            if (a[i][j] == -1)
                cout << "E ";
            else
                cout << a[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "HIT     ";
    for (i = 0; i < hitv.size(); i++)
    {
        if (hitv[i] == 0)
            cout << "  ";
        else
            cout << hitv[i] << " ";
    }
    cout << "\n";
    cout << "Hit : " << hit << '\n'
         << "Page Fault : " << m - hit << '\n'
         << "Page Fault Rate : " << float(m - hit) / float(m) << endl;
    return 0;
}