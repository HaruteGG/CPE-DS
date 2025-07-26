sort(arr, arr+10);//升序
sort(arr, arr+10, greater<int>());//降序

less<type>()    //从小到大排序 <
greater<type>()  //从大到小排序 >
less_equal<type>()  //  <=
gtater_equal<type>()//  >=
//这四种函数

bool custom_sort_rule(int a, int b) {
    // 获取 a 和 b 的出现次数
    int count_a = frequency_map[a];
    int count_b = frequency_map[b];

    // 判断 a 和 b 是否是“复数个”数字
    bool is_multiple_a = (count_a > 1);
    bool is_multiple_b = (count_b > 1);

    // 规则1: 复数个数字排在单个数字前面
    if (is_multiple_a && !is_multiple_b) {
        return true; // a 是复数个，b 是单个，所以 a 应该在 b 前面
    }
    if (!is_multiple_a && is_multiple_b) {
        return false; // a 是单个，b 是复数个，所以 a 不应该在 b 前面 (b 应该在 a 前面)
    }

    // 规则2: 如果两者都是“复数个”或都是“单个”
    if (is_multiple_a && is_multiple_b) {
        // 两者都是复数个：降序排列 (大的在前)
        return a > b;
    } else { // (!is_multiple_a && !is_multiple_b) => 两者都是单个
        // 两者都是单个：升序排列 (小的在前)
        return a < b;
    }
}
