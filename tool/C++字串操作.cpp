C++字串操作
這次要介紹關於字串的特殊用法,會介紹插入、刪除、修改、比對、取子字串、搜尋、取代、取字元陣列在排序。
 
那我們一一介紹吧~~
 
我先說一下,之後會出現一個叫string::npos的東西,它是用來跑從字串頭到字串尾的東西,表示字串的結尾!!
 
插入:
int main()  
{  
   string s,  target = "book",   ins = "the ";  
   getline(cin,s); //使用者輸入一字串  
   int i,pos = 0;  
   while((i=s.find(target,pos))!=string::npos) //find(要找book,從位置[pos]開始),直到結尾  
   {  
       s.insert(i,ins);  //插入的用法,從第i的位置插入ins字串  
       pos = i + ins.size()+1; //pos是說,我找到第一個,之後還可能有再跑圈,避免重覆要把pos改掉  
   }                                         
   cout << s << endl;  
} 
 

插前插後你就自己想想看啦~~
 
刪除:
int main()  
{  
   string s,ins = "do";  
   getline(cin,s);  
   int i,pos = 0;  
   while((i=s.find(ins,pos))!=string::npos)  
   {  
       s.erase(i,ins.size()); //刪除用法,從找到字的位置後幾個刪掉  
       pos = i + ins.size()+1;  
   }  
   cout << s << endl;  
} 
 

修改:
int main()  
{  
   string s = string();   
   s = "york ";  
   cout << s << endl;  
   s += "is a boy";  
   cout << s << endl;  
  
   s.assign("life is beautiful",8,9); // 從位置8之後取9個字元  
   cout << s <<endl;  
   s.append(" islander",7); //取islander裡的前7個字,加到s字串後  
   cout << s << endl;  
} 

 
比對:
int main()  
{  
   string s1 = "york";  
   string s2 = "york";  
   string s3 = "yorkk";  
   cout << s1.compare(s2) << endl;       //s1和s2比較;s1=s2--->0  
   cout << s1.compare(s3) << endl;       //s1<s3---->-1;出現負值都是右邊比左邊大  
   cout << s1.compare(0,2,s1)<< endl;   //將york從位置0之後取2個子和s1比較;  
   cout << s3.compare(0,4,s1)<< endl;  
}

 
取子字串:
int main()  
{  
   string s = "yorkisaboy";  
   cout << s.substr(0,4) << " "; //位置從0取到4  
   cout << s.substr(4,2) << " ";  
   cout << s.substr(6,1) << " ";  
   cout << s.substr(7,3) << " ";  
}  

 
搜尋  (find()--->左至右搜尋,rfind()----->右至左搜尋):
字串:
int main()  
 
{  
 
   string s = "york is a boy",want;  
 
   cout << "請輸入要找的字";  
 
   cin >> want;  
  
   int i,count = 0,pos = 0;  
 
   while((i=s.find(want,pos))!=string::npos)  
 

   {  
 
       count++;  
 
       cout << "第 " << count << " 次出現[" << want << "]的位置在第 "  
 
       << i+1 << " 個字" << endl;  
 
       pos = i+1;  
 
   }  
 
   if(count == 0)  
 
       cout << "沒符合["<<want << "]的字串";  
 
   else  
 
        cout << "總共找到 "<< count << " 次";  
}

數字(find_first_of----->有出現的任一元素
  find_last_of------>除了這些其他都是):
例如:find_first_of("abc"),則表示找a或b或c;
         find_last_of及find_first_not_of則反之
 
int main()  
 
{  
 
   string s ,target="0123456789";  
 
   cout << "請輸入一個字串:";  
 
   getline(cin,s);  
 
  
   int i,count = 0,pos = 0;  
 
   while((i=s.find_first_of(target,pos))!=string::npos)  
 
   {  
 
       count++;  
 
       pos = i+1;  
 
   }  
 
   cout << endl << "在["<<  s << "]中"; 
 
   if(count == 0)  
 
       cout << "沒有數字字元！！";  
 
   else  
 
        cout << "共有 "<< count << " 個數字字元";  
}

取代:
int main()  
{  
   string s,s1,s2;  
   cout << "請輸入一個字串:";  
   getline(cin,s);  
   cout << "請輸入要替換的字串:";  
   getline(cin,s1);  
   cout << "要將["<< s1 << "]換成？";  
   getline(cin,s2);  
   int i,pos = 0;  
   unsigned int len1= s1.size(),len2 = s2.size();  
   while((i=s.find(s1,pos))!=string::npos)  
   {  
       s.replace(i,len1,s2);   //從位置i到len1換成s2  
       pos = i + len2 + 1;  
   }  
   cout << "新字串："<< s;  
}

取字元陣列在排序:
int main()  
{  
   string s;  
   cout << "請輸入一個字串:";  
   cin >> s;  
   int len = s.size();  
   char *cstr = new char(len+1); //創一個位址給放字串  
   strcpy(cstr,s.c_str());   //#include<cstring>一定要得標頭檔,c_str()就是你輸入的字串  
   for(int i=0;i<len;i++)  
   {  
       for(int j=i+1;j<len;j++) //排序  
       {  
           if(cstr[i]>cstr[j])  
           {  
               char tmp = cstr[i];  
               cstr[i] = cstr[j];  
               cstr[j] = tmp;  
           }  
       }  
   }  
   cout << "將字串內容排序後："<<cstr;  
   delete [] cstr;  
}

其實功能是可以混著用的,蠻多練習題目都是將他們活用,這樣就能省很多程式碼喔
 
do{
        sn.insert(N);//sn是 set<string> sn
    }while(next_permutation(N.begin(), N.end())); 自動將一段字串一直自動排列取得所有排列結果
