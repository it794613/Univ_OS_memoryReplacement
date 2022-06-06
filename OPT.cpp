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

int main()
{
    int n, m, i, j, k;
    int min_index = 0;
    int min_check;
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
    }                           // 가장 최근에 변경된 백터를 확인하기 위해 만든것.
    vector<int> frame(n, -1);   //
    vector<int> check_frame(n); //프레임 몇번이 최근에 교체 된건지 확인하기 위한 벡터
    vector<int> hasrun(m);

    //참조 테이블 초기화
    //페이지 참조 횟수 테이블, 참조안되면 ++ 되면 0으로 바꾸고 나머지 ++, 그리고 몇번째 프레임인지 확인하기 위해서 가장 큰 index값 반환.해서 그곳에 replacement 발생시킴
    // 프로세스 하나씩 확인하기 시작함.
    //--------------------------------------------여기부터 프레임에 넣기 시작함

    //한 로직이 끝날때 마다, 해당 프레임에서 프레임 체크가

    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (a[j][i] == -1)
            { // 비어있으면 넣기
                for (int b = i; b < m; b++)
                {
                    a[j][b] = p[i];
                }
                frame[j] = p[i];
                hasrun[i]++;
                break;
            }
            else if (a[j][i] == p[i])
            { // hit!
                hasrun[i]++;
                break;
            }
        }
        if (hasrun[i] == 0)
        {
            //넣어야 하는 값음 pi 이다.
            // frame 1 2 3 값에서, pi를 순회해서 가장 먼 pi값이랑 동일하면 인덱스를 반환하고 그녀석의 프레임 값을 변경시켜줌
            for (int d = 0; d < n; d++)
            {
                for (int e = i; e < m; e++)
                {
                    if (frame[d] == p[e])
                    {
                        check_frame[d] = e;
                        break;
                    }
                }
            }
            cout << "check frame ; " << check_frame[0] << " " << check_frame[1] << " " << check_frame[2] << endl;
            //체크프레임에 뭐가 가장 큰 값이 바꿔줘야하는 프레임의 index;
            int max_index = max_element(check_frame.begin(), check_frame.end()) - check_frame.begin();
            for (int v = 0; v < n; v++)
            {
                check_frame[v] = INT32_MAX;
            }
            for (int b = i; b < m; b++)
            {
                a[max_index][b] = p[i];
            }
            frame[max_index] = p[i];
            hasrun[i]++;
        }
    }

    // 2022 06 05 문제점, 지금 체크프레임 이라는 부분에서 오류남

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