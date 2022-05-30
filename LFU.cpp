#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

bool compare(int bn, int kz) // 오름차순 정리
{
    return bn > kz;
}

int main()
{
    int n, m, i, j, k;
    int min_index;
    int count = 0;
    cout << "Enter number of frames\n";
    cin >> n;
    cout << "Enter number of processes\n";
    cin >> m;
    vector<int> p(m); // 원소의 개수가 프로세스수 만큼의 백터를 만들고, 0으로 초기화
    cout << "Enter processes\n";
    int max = m;
    for (i = 0; i < m; i++)
    {
        cin >> p[i];
    }
    vector<vector<int> > a(n, vector<int>(m, -1)); // 백터를 넣는 백터a를 만들고 그안에 n개의 자리가 있으며 그것을 백터로 초기화 하는데 이 백터의 길이는m 개이며 -1로 초기화.\
     즉 이중배열 백터를 만든거임, 지금 a[][] 이런 게 있는거임. 백터에서 값을할당했으니까 그냥 인덱스로 접근 가능;
    map<int, int> mp;
    for (int jk = 0; jk < m; jk++)
    {
        mp[jk] = -1;
    }
    vector<int> check(n); // 가장 최근에 변경된 백터를 확인하기 위해 만든것.
    vector<int> frame(n, -1);

    //참조 테이블 초기화
    //페이지 참조 횟수 테이블, 참조안되면 ++ 되면 0으로 바꾸고 나머지 ++, 그리고 몇번째 프레임인지 확인하기 위해서 가장 큰 index값 반환.해서 그곳에 replacement 발생시킴
    vector<int> hasrun(m);
    // 프로세스 하나씩 확인하기 시작함.
    //--------------------------------------------여기부터 프레임에 넣기 시작함

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[j][i] == p[i])
            {
                mp[p[i]]++;
                check[j]++; //체크는 한번 사용할때마다 1올려주기 때문에 높을수록 최근 사용.
                break;
            }
            if (a[j][i] == -1)
            {
                for (int l = i; l < m; l++)
                {
                    a[j][l] = p[i];
                }
                mp[p[i]]++;
                check[j]++;
                frame[j] = p[i]; //현재 프레임 할당을 체크
                break;
            }
            if (a[j][i] != -1 && a[j][i] != p[i])
            {
                for (int gk = 0; gk < n; gk++) // 프레임 에서 가장 낮은 mp값 체크하려고
                {
                    int min = 20000;
                    if (min >= mp[frame[gk]])
                    {
                        min = mp[frame[gk]];
                        min_index = gk;
                        count++; // 동일한 최소값이 있는지 확인하는 값;
                    }
                }
                if (count == 1) // 최소값이 한개면
                {
                    for (int e = i; e < m; e++)
                    {
                        a[min_index][e] = p[i];
                    }
                    mp[p[min_index]]++;
                    check[min_index]++;
                    frame[min_index] = p[i];
                    count = 0;
                    break;
                }
                else
                {
                    int min_check_index;
                    int min_check = 20000;
                    for (int kl = 0; kl < n; kl++)
                    {
                        if (min_check > check[kl])
                        {
                            min_check = check[kl];
                            min_check_index = kl;
                        }
                    }
                    for (int e = i; e < m; e++)
                    {
                        a[min_check_index][e] = p[i];
                    }
                    mp[p[i]]++;
                    check[min_check_index]++;
                    frame[min_check_index] = p[i];
                    count = 0;
                    break;
                }
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
         << "Page Fault Rate : " << float(m - hit) / float(m) * 100 << "%" << endl;
    return 0;
}