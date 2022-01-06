#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <stdio.h>
#include <cstdio>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <charconv>

using namespace std;

int main()
{
    cout << "--- Page Replacement algorithm ---" << endl;
    cout << "1. Default referenced sequence" << endl;
    cout << "2. Manual input sequence" << endl;
    cout << "Enter 1 or 2: ";
    int choice, nframe, algorithm;
    vector<int> sequence;
    cin >> choice;
    if (choice == 1)
    {
        cout << "Default sequence: 2 0 5 2 1 5 9 1 0 0 7" << endl;
        for (auto i : {2, 0, 5, 2, 1, 5, 9, 1, 0, 0, 7})
        {
            sequence.push_back(i);
        }
    }
    else
    {
        cout << "Input sequence length: ";
        int n;
        cin >> n;
        sequence.resize(n);
        for (int i = 0; i < n; i++)
        {
            cout << "Input " << i << " element: ";
            cin >> sequence[i];
        }
        cout << "Done!!! Your Sequence is: ";
        for (auto x : sequence)
        {
            cout << x << " ";
        }
        cout << endl;
    }

    cout << endl << "--- Page Replacement algorithm ---" << endl;
    cout << "Input page frames: ";
    cin >> nframe;

    cout << endl << "--- Page Replacement algorithm ---" << endl;
    cout << "1. FIFO algorithm" << endl;
    cout << "2. OPT algorithm" << endl;
    cout << "3. LRU algorithm" << endl;
    cout << "Enter 1 or 2 or 3: ";
    cin >> algorithm;
    while (algorithm != 1 && algorithm != 2 && algorithm != 3)
    {
        cout << "Only accept 1, 2, 3" << endl;
        cout << "Enter 1 or 2 or 3: ";
        cin >> algorithm;
    }

    // Algorithm section

        // Initialization
        int n = sequence.size();
        vector<vector<string>> matrix_result(nframe, vector<string>(n));
        vector<string> page_fault(n);
        int npage_fault = 0;

        map<int, bool> check;
        for (int i = 0; i < n; i++)
        {
            check[sequence[i]] = false;
        }

        int framesize = 0;

        if (algorithm == 1) // FIFO
        {
            vector<pair<int, int>> frame;
            for (int i = 0; i < n; i++)
            {
                if (check[sequence[i]] == false) // Neu tt nay chua xh trong frame
                {
                    if (framesize < nframe) // Neu frame chua day
                    {
                        frame.push_back(make_pair(sequence[i], i));
                        framesize++;
                        page_fault[i] = "*";
                    }
                    else // Neu frame da day Check phan tu de thay the
                    {
                        int first_come = 0; // Vi tri phan tu dc dua vao dau tien trong frame
                        int t = n + 1; // TG phan tu do xh
                        for (int j = 0; j < framesize; j++)
                        {
                            if (t > frame[j].second)
                            {
                                t = frame[j].second;
                                first_come = j;
                            }
                        }

                        check[frame[first_come].first] = false; // Danh dau pt da bi lay ra thanh false
                        frame[first_come] = make_pair(sequence[i], i); // thay the phan tu trong frame
                        page_fault[i] = "*";
                    }
                    npage_fault++;
                }
                else
                {
                    page_fault[i] = " ";
                }

                check[sequence[i]] = true; // Danh dau da xh
                for (int j = 0; j < nframe; j++)
                {
                    if (j < framesize)
                    {
                        matrix_result[j][i] = to_string(frame[j].first);
                    }
                    else
                    {
                        matrix_result[j][i] = " ";
                    }
                }
            }
        }
        else if (algorithm == 2) // OPT
        {
            vector<int> frame;
            for (int i = 0; i < n; i++)
            {
                if (check[sequence[i]] == false) // Neu tt nay chua xh trong frame
                {
                    if (framesize < nframe) // Neu frame chua day
                    {
                        frame.push_back(sequence[i]);
                        framesize++;
                        page_fault[i] = "*";
                    }
                    else // Neu frame da day Check phan tu de thay the
                    {
                        int latest = 0;
                        map<int, int> predict;
                        for (int j = i + 1; j < n; j++)
                        {
                            if (check[sequence[j]] == true)
                            {
                                predict[sequence[j]] = 1;
                                latest++;
                                if (latest == framesize - 1)
                                    break;
                            }
                        }
                        for (int j = 0; j < nframe; j++)
                        {
                            if (predict[frame[j]] == 0)
                            {
                                latest = j;
                                break;
                            }
                        }

                        check[frame[latest]] = false; // Danh dau pt da bi lay ra thanh false
                        frame[latest] = sequence[i]; // thay the phan tu trong frame
                        page_fault[i] = "*";
                    }
                    npage_fault++;
                }
                else // Neu tt da xh trong frame
                {
                    page_fault[i] = " ";
                    // Cap nhat thoi gian dc tham chieu
                }

                check[sequence[i]] = true; // Danh dau da xh
                for (int j = 0; j < nframe; j++)
                {
                    if (j < framesize)
                    {
                        matrix_result[j][i] = to_string(frame[j]);
                    }
                    else
                    {
                        matrix_result[j][i] = " ";
                    }
                }
            }
        }
        else if (algorithm == 3) // LRU
        {
            vector<int> frame;
            for (int i = 0; i < n; i++)
            {
                if (check[sequence[i]] == false) // Neu tt nay chua xh trong frame
                {
                    if (framesize < nframe) // Neu frame chua day
                    {
                        frame.push_back(sequence[i]);
                        framesize++;
                        page_fault[i] = "*";
                    }
                    else // Neu frame da day Check phan tu de thay the
                    {
                        int latest = 0;
                        map<int, int> predict;
                        for (int j = i - 1; j >= 0; j--)
                        {
                            if (check[sequence[j]] == true)
                            {
                                predict[sequence[j]] = 1;
                                latest++;
                                if (latest == framesize - 1)
                                    break;
                            }
                        }
                        for (int j = 0; j < nframe; j++)
                        {
                            if (predict[frame[j]] == 0)
                            {
                                latest = j;
                                break;
                            }
                        }

                        check[frame[latest]] = false; // Danh dau pt da bi lay ra thanh false
                        frame[latest] = sequence[i]; // thay the phan tu trong frame
                        page_fault[i] = "*";
                    }
                    npage_fault++;
                }
                else // Neu tt da xh trong frame
                {
                    page_fault[i] = " ";
                    // Cap nhat thoi gian dc tham chieu
                }

                check[sequence[i]] = true; // Danh dau da xh
                for (int j = 0; j < nframe; j++)
                {
                    if (j < framesize)
                    {
                        matrix_result[j][i] = to_string(frame[j]);
                    }
                    else
                    {
                        matrix_result[j][i] = " ";
                    }
                }
            }
        }

    // Algorithm End

    cout << "--- Result ---" << endl;
    for (auto x : sequence)
    {
        cout << x << " ";
    }
    cout << endl;
    for (int i = 0; i < nframe; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix_result[i][j] << " ";
        }
        cout << endl;
    }
    for (auto x : page_fault)
    {
        cout << x << " ";
    }
    cout << endl;
    cout << "So loi trang: " << npage_fault << endl;
    return 0;
}
