#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cassert>
#include<algorithm>

#include"../utility.h"

int count_digits(int num) {
    if (num == 0) {
        return 1;
    }
    return int(floor(log10(num))) + 1;
}

std::string trim_space(const std::string& s) {
    std::string ss = s;
    ss.erase(ss.begin(), std::find_if_not(ss.begin(), ss.end(),  [] (unsigned char ch) {
        return std::isspace(ch);
    }));
    ss.erase(std::find_if_not(ss.rbegin(), ss.rend(), [] (unsigned char ch) {
        return std::isspace(ch);
    }).base(), ss.end());
    return ss;
}

class BigInteger {

public:
    int sign = 0;  // 整数 1, 负数 -1, 零 0
    static const int WIDTH = 8;
    static const int BASE = 1e8;
    static const int DEFAULT_SIZE = 8;

    BigInteger() : vec(std::vector<int>()), sign(0) { // -> 0
        vec.reserve(DEFAULT_SIZE);
    }
    explicit BigInteger(long long num) { *this = num; }
    explicit BigInteger(std::string s) { *this = s; }

    bool iszero() const {
        return sign == 0;
    }
    // 需要特别小心 BigInteger 改变之后是否有多余的 leading 0
    void shrink_leading_zero() {
        int i;
        for(i = vec.size()-1; i >= 0 && vec[i] == 0; i--) ;
        vec.resize(i);
        if (vec.size() == 0) {
            sign = 0;
        }
    }
    // reset to zero
    void clear() {
        vec.clear();
        sign = 0;
    }
    size_t size() const {
        return vec.size();
    }
    size_t num_digits() const {
        return num_digits_of_vec(vec);
    }

    // 重载赋值运算符
    BigInteger operator = (long long num) {
        clear();
        if (num < 0) {
            sign = -1;
            num = -num;
        } else if (num > 0) {
            sign = 1;
        }

        bool is_minimum = num == std::numeric_limits<long long>::min();
        int least = num % BASE;
        num /= BASE;
        if (is_minimum) { // 最小负整数无法取反得到绝对值
            least = -least;
            num = -num;
        }
        vec.push_back(least);
        while (num > 0) {
            vec.push_back(static_cast<int>(num % BASE));
            num /= BASE;
        }
        return *this;
    }
    // 不考虑不合法的字符串
    BigInteger operator = (const std::string& str) {
        clear();
        std::string s = trim_space(str);
        if (str[0] == '-') {
            sign = -1;
            s = s.substr(1);
        }
        if (str[0] == '+') {
            sign = 1;
            s = s.substr(1);
        }

        int x = 0;
        int len = (s.length() - 1) / WIDTH + 1;
        for(int i = 0; i < len; i++) {
            int end = s.length() - i*WIDTH;
            int start = std::max(0, end-WIDTH);
            sscanf(s.substr(start, WIDTH).c_str(), "%d", &x);
            vec.push_back(x);
        }
        shrink_leading_zero();
        return *this;
    }

    // 重载逻辑关系运算符
    bool operator == (const BigInteger& b) const {
        return sign == b.sign && vec == b.vec;
    }
    bool operator != (const BigInteger& b) const {
        return !(*this == b);
    }
    bool operator < (const BigInteger& b) const {
        if (sign < b.sign) return true;
        if (sign > b.sign) return false;
        if (sign > 0) return vec_less(vec, b.vec);
        else return vec_less(b.vec, vec);
    }
    bool operator > (const BigInteger& b) const {
        return b < *this;
    }
    bool operator <= (const BigInteger& b) const {
        return !(b < *this);
    }
    bool operator >= (const BigInteger& b) const {
        return !(*this < b);
    }

    // 重载一元算术运算符
    BigInteger operator-() const {
        BigInteger res = *this;
        res.sign *= -1;
        return res;
    }
    // 重载二元算术运算符
    BigInteger operator + (const BigInteger& b) const {
        BigInteger c;
        if (sign == b.sign) {
            BigInteger::vec_add(vec, b.vec, c.vec);
            c.sign = sign;
            return c;
        }
        bool is_ge = vec_less(this->vec, b.vec);
        const BigInteger &large = is_ge ? *this : b; // 绝对值更大的数(>=)
        const BigInteger &small = is_ge ? b : *this;
        vec_sub(large.vec, small.vec, c.vec);
        c.sign = large.sign;
        c.shrink_leading_zero();
        return c;
    }
    BigInteger operator - (const BigInteger& b) const {
        return *this + -b;
    }
    BigInteger operator += (const BigInteger& b) {
        *this = *this + b; return *this;
    }
    BigInteger operator * (const BigInteger& b) const {
        BigInteger sum;
        if (sign == 0 || b.sign == 0) return sum;

        for(int i = 0; i < b.vec.size(); i++) {
            std::vector<int> tmp;
            vec_mul((*this).vec, b.vec[i], tmp);
            vec_add_to(sum.vec, tmp, i);
        }
        sum.sign = sign * b.sign;
        sum.shrink_leading_zero();
        return sum;
    }
//    std::pair<BigInteger, BigInteger> operator / (const BigInteger& b) const {
//
//    }

    // Friend function to overload the << operator
    friend std::ostream& operator<<(std::ostream& out, const BigInteger &x);
    // Friend function to overload the >> operator
    friend std::istream& operator>>(std::istream& in, BigInteger& x);

    static bool is_zero_vec(const std::vector<int> &v) {
        return std::all_of(v.begin(), v.end(), [](int i) { return i == 0; });
    }
    static void vec_add(const std::vector<int> &v1, const std::vector<int> &v2, std::vector<int> &dst) {
        for(int i = 0, g = 0; ; i++) {
            if (g == 0 && i >= v1.size() && i >= v2.size()) break;
            int x = g;
            if (i < v1.size()) x += v1[i];
            if (i < v2.size()) x += v2[i];
            dst.push_back(x % BigInteger::BASE);
            g = x / BigInteger::BASE;
        }
    }
    static void vec_add_to(std::vector<int> &dst, const std::vector<int> &src, int offset) {
        // src 右移 offset 位
        // 将 dst 从 dst.size() 位 扩充到 src.size() + offset
        for (int i = dst.size(); i < src.size()+offset; i++) {
            dst.push_back(0);
        }
        for (int i = 0, g = 0; ; i++) {
            int j = i + offset;
            if (g == 0 && i >= src.size() && j >= dst.size()) break;
            int x = g;
            if (i < src.size()) x += src[i];
            if (j < dst.size()) x += dst[j];
            dst[j] = x % BigInteger::BASE;
            g = x / BigInteger::BASE;
        }
    }
    // vec_sub suppose that v1 >= v2
    static void vec_sub(const std::vector<int> &v1, const std::vector<int> &v2, std::vector<int> &dst) {
        int carry = 0;
        for(int i = 0; i < v1.size(); i++) {
            int t = 0;
            if (i < v2.size()) {
                t = v2[i];
            }
            int res = v1[i] - t + carry;
            if (res < 0) {
                carry = -1;
                res += BASE;
            } else {
                carry = 0;
            }
            dst.push_back(res);
        }
    }
    static void vec_mul(const std::vector<int> &v1, int v2, std::vector<int> &dst) {
        long long g = 0;
        for(int i = 0; ; i++) {
            if (g == 0 && i >= v1.size()) break;
            long long t = g;
            if (i < v1.size()) t += v1[i];
            dst.push_back(int(t % BASE));
            g = t / BASE;
        }
    }
    static int num_digits_of_vec(const std::vector<int> v) {
        int most_significant_bits = count_digits(v.back());
        return WIDTH*(v.size()-1) + most_significant_bits;
    }
    static bool vec_less(const std::vector<int> &v1, const std::vector<int> &v2) {
        int d1 = num_digits_of_vec(v1), d2 = num_digits_of_vec(v2);
        if (d1 != d2) return d1 < d2;
        for(int i = v1.size()-1; i >= 0; i--) {
            if (v1[i] != v2[i]) return v1[i] < v2[i];
        }
        return false; // 相等
    }

    std::vector<int> vec;
};

// 重载输入输出运算
std::ostream& operator << (std::ostream& out, const BigInteger& x) {
    if (x.sign == 0) {
        out << "0";
        return out;
    }
    if (x.sign == -1) {
        out << "-";
    }
    BigInteger a = x;
    a.shrink_leading_zero();
    out << a.vec.back();
    for(int i = a.vec.size()-2; i >= 0; i--) {
        char buf[20];
        snprintf(buf, 20, "%08d", a.vec[i]);
        for(int j = 0; j < strlen(buf); j++) out << buf[j];
    }
    return out;
}

std::istream& operator >> (std::istream& in, BigInteger& x) {
    std::string s;
    if (!(in >> s)) return in;
    x = s;
    return in;
}

void test_ctor() {
    BigInteger x;
    assert(x.iszero());
    assert(x.vec.empty());
    assert(x.vec.capacity() == BigInteger::DEFAULT_SIZE);

    BigInteger y = BigInteger((long long)0);
    assert(y.iszero());
    y = BigInteger(-1111);

}

void test_neg() {

}

void test_assign() {

}

void test_in() {

}

void test_out() {

}

void test_add() {

}

void test_sub() {

}

void test_mul() {

}

int main() {
    BigInteger z;
    BigInteger x(1100), y(30);

    BigInteger::vec_add(x.vec, y.vec, z.vec);
    assert(z == BigInteger(1130));
    BigInteger::vec_add_to(z.vec, y.vec, 2);
    assert(z == BigInteger(301130));
    BigInteger u;
    BigInteger::vec_sub(z.vec, x.vec, u.vec);
    assert(u == BigInteger(300030));
    assert(BigInteger::vec_less(u.vec, z.vec));

    x = BigInteger(1122334455);
    y = BigInteger(99887711);
    assert(BigInteger(0) - BigInteger(5) == BigInteger(-5));
    assert(x - y == BigInteger(1022446744));
    assert(x + y == BigInteger(1222222166));
    assert(x * y == BigInteger(112107419686382505));

//    BigInteger y = (long long) -10304358305350;
//    long long m = std::numeric_limits<long long>::min();
//    BigInteger x = m;
//    assert(x == BigInteger((long long)-9223372036854775808));
//    BigInteger z = std::string("-10304358305350");
//    assert(z == y);
//    BigInteger s = BigInteger("123456789") - BigInteger("1234");

//    BigInteger a(std::string("10924237423075203570"));
//    BigInteger b("23479234701249147104174074914701");
//    BigInteger sum("23479234701260071341597150118271");
//    BigInteger sub("-23479234701238222866750999711131");
//    BigInteger sum1 = a + b;
//    BigInteger sub1 = a - b;
//    assert(sum1 == sum);
//    assert(sub1 == sub);
}