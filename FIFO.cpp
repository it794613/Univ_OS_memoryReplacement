#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
bool compare(int bn, int kz) // 오름차순 정리
{
    return bn > kz;
}
#define TEST 1

int main()
{
    int n, m, i, j, k;
    int min_index = 0;
    int min_check;
    int count = 0;
    vector<int> p;
    if (TEST)
    {
        n = 3;
        m = 20;
        p = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    }
    else
    {
        cout << "Enter number of frames\n";
        cin >> n;
        cout << "Enter number of processes\n";
        cin >> m;
        p.reserve(m); // 원소의 개수가 프로세스수 만큼의 백터를 만들고, 0으로 초기화
        cout << "Enter processes\n";
        for (i = 0; i < m; i++)
        {
            cin >> p[i];
        }
    }
    int max = m;
    vector<vector<int>> a(n, vector<int>(m, -1)); // 백터를 넣는 백터a를 만들고 그안에 n개의 자리가 있으며 그것을 백터로 초기화 하는데 이 백터의 길이는m 개이며 -1로 초기화.\
                                                        즉 이중배열 백터를 만든거임, 지금 a[][] 이런 게 있는거임. 백터에서 값을할당했으니까 그냥 인덱스로 접근 가능;
    map<int, int> mp;
    for (int jk = 0; jk < m; jk++)
    {
        mp[jk] = -1;
    }                           // 가장 최근에 변경된 백터를 확인하기 위해 만든것.
    vector<int> frame(n, -1);   //
    vector<int> check_frame(n); //프레임 몇번이 최근에 교체 된건지 확인하기 위한 벡터
    int index = 0;
    int temp = 0;

    //참조 테이블 초기화
    //페이지 참조 횟수 테이블, 참조안되면 ++ 되면 0으로 바꾸고 나머지 ++, 그리고 몇번째 프레임인지 확인하기 위해서 가장 큰 index값 반환.해서 그곳에 replacement 발생시킴
    // 프로세스 하나씩 확인하기 시작함.
    //--------------------------------------------여기부터 프레임에 넣기 시작함

    //한 로직이 끝날때 마다, 해당 프레임에서 프레임 체크가
    bool hasrun = false;
    queue<int> schedule;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[j][i] == -1)
            {
                for (int b = i; b < m; b++)
                {
                    a[j][b] = p[i];
                }
                hasrun = true;
                count++;
                schedule.push(j);
                break;
            }
            else if (a[j][i] == p[i])
            { // hit
                hasrun = true;
                break;
            }
        }
        if (hasrun == false)
        {
            int pop_frame = schedule.front();
            schedule.pop();
            for (int b = i; b < m; b++)
            {
                a[pop_frame][b] = p[i];
            }
            schedule.push(pop_frame);
        }
        hasrun = false;
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