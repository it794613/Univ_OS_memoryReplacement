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
    int max_index;
    int max_value;
    int max = -1;
    cout << "Enter number of frames\n";
    cin >> n;
    cout << "Enter number of processes\n";
    cin >> m;
    vector<int> p(m); // 원소의 개수가 프로세스수 만큼의 백터를 만들고, 0으로 초기화
    cout << "Enter processes\n";
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
    vector<int> check; //참조값 확인용 백터
    vector<int> frame(n, -1);
    //참조 테이블 초기화
    //페이지 참조 횟수 테이블, 참조안되면 ++ 되면 0으로 바꾸고 나머지 ++, 그리고 몇번째 프레임인지 확인하기 위해서 가장 큰 index값 반환.해서 그곳에 replacement 발생시킴
    vector<int> hasrun(m);
    // 프로세스 하나씩 확인하기 시작함.
    //--------------------------------------------여기부터 프레임에 넣기 시작함

    for (i = 0; i < m; i++) //프로세스 배열
    {
        for (j = 0; j < n; j++) //프레임 배열
        {
            if (a[j][i] == p[i]) // 페이지 히트가 발생
            {
                mp[i]++;
                hasrun[i]++;
                break;
            }
            if (hasrun[i] == 0 && a[j][i] == -1) // 페이지 폴트이며, 프레임에 아무것도 없음
            {
                for (int l = i; l < m; l++)
                {
                    a[j][l] = p[i];
                }
                mp[i]++;
                hasrun[i]++;
                frame[j] = p[i];
                break;
                //여기에서 지금 더이상 for문이 완전히 안돌고 바로 그 상위 포문으로 돌아가야함.
            }
        }
        cout << i << "Frame : " << frame[0] << frame[1] << frame[2] << endl;
        for (int ab = 0; ab < n; ab++)
        {
            if (hasrun[i] == 0 && a[ab][i] != -1 && a[ab][i] != p[i]) //빈프레임이 없고, 페이지 폴트가 발생,
            {
                for (int gk = 0; gk < n; gk++)
                {
                    if (max < mp[frame[gk]])
                    {
                        max = mp[frame[gk]]; // 참조 횟수
                        max_index = gk;      // 메모리 리플레이스 먼트 해야하는 인덱스
                    }
                }
                frame[max_index] = p[i];
                cout << "Frame : " << frame[0] << frame[1] << frame[2] << endl;
                for (int e = i; e < m; e++)
                {
                    a[max_index][e] = p[i];
                }
                max = -1; // 초기화
                mp[i]++;
                hasrun[i]++;
                break;
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