https://mropengate.blogspot.com/2015/07/cc-vector-stl.html

vector<int>
  => vector<int>arr //宣告名為 arr 的 vector<int>
  => arr.push_back(a) // 把 a 放到 arr 的最後面
  => arr.size()
  => arr[1]
  => arr.clear()//清空
  => pop_back() //删除 vector 容器中最後一個元素，該容器的大小（size）會減 1，但容量（capacity）不會發生改變。

arr[i] - 存取索引值為 i 的元素值。
arr.at(i) - 存取索引值為 i 的元素的值，
arr.front() - 回傳 vector 第一個元素的值。
arr.back() - 回傳 vector 最尾元素的值。
  
  vector<int> arr = {5, 4, 1, 7, 3, 8, 9, 10, 6, 2};
  sort(arr.begin(), arr.begin()+10);//升序
  sort(v.begin(), v.end());//升序

  bool mycompare (int a, int b) {
    return a > b; // 降序排列
}
    int arr[] = {5, 4, 1, 7, 3, 8, 9, 10, 6, 2};
    vector<int> v(arr, arr+10);
    sort(v.begin(), v.end(), mycompare);// 降序排列

result = max_element(v.begin(), v.end());//找最大值


pair<int, string> p1; //default constructor 
pair<string, double>p2("zhouyu", 100); // overroad constructor

vector< pair<int, int> > v;
v.push_back(make_pair(int, int)); or v.push_back({int, int});
for(auto i: v) // for cout vector< pair<int, int> > v;

//2d vector
vector<vector<int>> arr(n, vector<int>(m));
