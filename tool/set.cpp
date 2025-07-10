//關於set，必須說明的是set關聯式容器。set作為一個容器也是用來儲存同一資料型別的資料型別，並且能從一個數據集合中取出資料，在set中每個元素的值都唯一，而且系統能根據元素的值自動進行排序。
set<int> s
set<char> s
set<string> s

*s.begin()
*s.end()
s.clear()
s.size()
s.find()
int main() {

    set<int> s1{9,8,1,2,3,4,5,5,5,6,7,7 }; //自動排序，從小到大,剔除相同項

    set<string> s2{ "hello","sysy","school","hello" }; //字典序排序

    s1.insert(9); //有這個值了，do nothing

    s2.insert("aaa"); //沒有這個字串，新增並且排序
}

int main() {
     set<int> s;
     s.insert(1);
     s.insert(2);
     s.insert(3);
     s.insert(1);
     cout<<"set 的 size 值為 ："<<s.size()<<endl;// 3
     cout<<"set 中的第一個元素是 ："<<*s.begin()<<endl;// 1
     cout<<"set 中的最後一個元素是:"<<*s.end()<<endl;// 3
     s.clear();
    
    遍歷
int main() {
	set<int> s = {1, 2, 3};
	set<int> ::iterator it;
	for(it=s.begin(); it!=s.end(); it++) cout << *it << endl;
	//也可以for(auto it=s.begin(); it!=s.end(); it++) cout << *it << endl;
	return 0;
}
    for(auto i:s) cout << i << endl;  //此法較簡便
