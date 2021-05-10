
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <gmpxx.h>
#include <chrono>

class TBigInt {
private:
    static const long int BASE = 1e7;
    static const int DIGIT_LENGTH = 7;
    std::vector<int> bigInt;
public:
    size_t Size() const {
        return bigInt.size();
    }

    TBigInt() = default;

    TBigInt(int num) {
        if (!num) {
            bigInt.push_back(0);
        }
        else {
            while (num) {
                bigInt.push_back(num % BASE);
                num /= BASE;
            }
        }
    }

    explicit TBigInt(const size_t &size) : bigInt(size, 0) {};

    explicit TBigInt(const std::string &str) {
        bigInt.clear();
        for (int i = (int)str.length(); i > 0; i -= DIGIT_LENGTH)
            if (i < DIGIT_LENGTH)
                bigInt.push_back (atoi(str.substr (0, i).c_str()));
            else
                bigInt.push_back (atoi(str.substr (i-DIGIT_LENGTH, DIGIT_LENGTH).c_str()));
        while (bigInt.size() > 1 && bigInt.back() == 0)
            bigInt.pop_back();
    }
    TBigInt operator = (const TBigInt &other) {
        this->bigInt = other.bigInt;
        return *this;
    }

    friend TBigInt operator + (TBigInt &first, TBigInt &second) {
        if (first.Size() < second.Size()) {
            return second + first;
        }
        TBigInt result = first;
        int carry = 0;
        for (int i = 0; i < std::max(result.Size(), second.Size()) || carry; ++i) {
            if (i == result.Size()) {
                result.bigInt.emplace_back(0);
            }
            result.bigInt[i] += carry + (i < second.Size() ? second.bigInt[i] : 0);
            carry = result.bigInt[i] / BASE;
            result.bigInt[i] %= BASE;
        }
        while (result.bigInt.size() > 1 and result.bigInt.back() == 0) {
            result.bigInt.pop_back();
        }
        return result;
    }

    friend TBigInt operator - (TBigInt &first, TBigInt &second) {
        if (first < second) {
            throw std::runtime_error("error");
        }
        int carry = 0;
        TBigInt result(first);
        for (int i = 0; i < static_cast<int>(second.Size()) || carry; ++i) {
            result.bigInt.at(i) -= carry + (i < static_cast<int>(second.Size()) ? second.bigInt[i] : 0);
            carry = result.bigInt[i] < 0;
            if (carry != 0) {
                result.bigInt.at(i) += BASE;
            }
        }
        while (result.bigInt.size() > 1 and result.bigInt.back() == 0) {
            result.bigInt.pop_back();
        }
        return result;
    }



    friend TBigInt operator * (TBigInt &first, TBigInt &second) {
        TBigInt result(first.Size() + second.Size());
        int carry = 0;
        for (int i = 0; i < first.Size(); ++i) {
            carry = 0;
            for (int j = 0; j < int(second.Size()) || carry; ++j) {
                long long curr = result.bigInt[i + j] + carry + first.bigInt[i] * 1ll * (j < (int)second.Size() ? second.bigInt[j] : 0);
                result.bigInt[i + j] = int(curr % BASE);
                carry = int(curr / BASE);
            }
        }
        while (result.bigInt.size() > 1 and result.bigInt.back() == 0) {
            result.bigInt.pop_back();
        }
        return result;
    }

    friend TBigInt operator * (TBigInt &first, const int &second) {
        TBigInt result(first);
        int carry = 0;
        for (int i = 0; i < result.Size() || carry; ++i) {
            if (i == result.Size()) {
                result.bigInt.push_back(0);
            }
            long long curr = carry + result.bigInt[i] * 1ll * second;
            result.bigInt[i] = int (curr % BASE);
            carry = (int) (curr / BASE);
        }
        while (result.bigInt.size() > 1 and result.bigInt.back() == 0) {
            result.bigInt.pop_back();
        }
        return result;
    }

    friend TBigInt operator / (TBigInt &first, TBigInt &second) {
        if(first < second) {
            return TBigInt("0");
        }
        if((second.Size() == 1) && second.bigInt[0] == 0) {
            throw std::runtime_error("error");
        }
        int norm = BASE / (second.bigInt.back() + 1);
        TBigInt lCopy = first * norm;
        TBigInt rCopy = second * norm;
        TBigInt q(lCopy.Size());
        TBigInt r;
        for (int i = lCopy.Size() - 1; i >= 0; --i) {
            r = r * BASE;
            TBigInt increment(std::to_string(lCopy.bigInt[i]));
            r = r + increment;
            int s1 = r.Size() <= rCopy.Size() ? 0 : r.bigInt[rCopy.Size()];
            int s2 = r.Size() <= rCopy.Size() - 1 ? 0 : r.bigInt[rCopy.Size() - 1];
            int d = static_cast<int>((static_cast<int>(s1) * BASE + s2) / rCopy.bigInt.back());
            TBigInt  tmp = rCopy * d;
            while (tmp > r){
                tmp = tmp - rCopy;
                d--;
            }
            r = r - tmp;
            q.bigInt[i] = d;
        }
        while (q.bigInt.size() > 1 and q.bigInt.back() == 0) {
            q.bigInt.pop_back();
        }
        return q;
    }

    friend TBigInt operator / (TBigInt &first, const int &second) {
        if (second == 0) {
            throw std::runtime_error("error");
        }
        int carry = 0;
        TBigInt result(first);
        for (int i = result.Size() - 1; i >= 0; --i) {
            long long curr = result.bigInt[i] + carry *1ll * BASE;
            result.bigInt[i] = int (curr/second);
            carry = int (curr % second);
        }
        while (result.bigInt.size() > 1 and result.bigInt.back() == 0) {
            result.bigInt.pop_back();
        }
        return result;
    }

    friend TBigInt operator ^ (TBigInt &first, TBigInt &second) {
        if ((first.Size() == 1 && first.bigInt[0] == 0) && (second.Size() == 1 && second.bigInt[0] == 0)) {
            throw std::runtime_error("error");
        }
        TBigInt decrement("1");
        TBigInt num(first);
        TBigInt result("1");
        while (!(second.Size() == 1 && second.bigInt[0] == 0)) {
            if ((second.bigInt[0] % 10) % 2 == 0) {
                num = num * num;
                second = second / 2;
            } else {
                result = result * num;
                second = second - decrement;
            }
        }
        while (result.bigInt.size() > 1 and result.bigInt.back() == 0) {
            result.bigInt.pop_back();
        }
        return result;
    }

    friend std::ostream& operator << (std::ostream &os, const TBigInt &num) {
        int num_len = num.Size();
        os << num.bigInt.back();
        for (int i = num_len - 2; i >= 0; --i) {
            os << std::setfill('0') << std::setw(DIGIT_LENGTH) << num.bigInt[i];
        }
        return os;
    }

    friend std::istream& operator >> (std::istream &is, TBigInt &num) {
        std::string str;
        is >> str;
        num = TBigInt(str);
        return is;
    }

    friend bool operator < (const TBigInt &first, const TBigInt &second) {
        if (first.Size() != second.Size()) {
            return first.Size() < second.Size();
        }
        for (int i = first.Size() - 1; i >= 0 ; --i) {
            if (first.bigInt[i] != second.bigInt[i]) {
                return first.bigInt[i] < second.bigInt[i];
            }
        }
        return false;
    }

    friend bool operator > (const TBigInt &first, const TBigInt &second) {
        if (first.Size() != second.Size()) {
            return first.Size() > second.Size();
        }
        for (int i = first.Size() - 1; i >=0 ; --i) {
            if (first.bigInt[i] != second.bigInt[i]) {
                return first.bigInt[i] > second.bigInt[i];
            }
        }
        return false;
    }

    friend bool operator == (const TBigInt &first, const TBigInt &second) {
        if (first.Size() != second.Size()) {
            return false;
        }
        for (int i = first.Size() - 1; i >=0 ; --i) {
            if (first.bigInt[i] != second.bigInt[i]) {
                return false;
            }
        }
        return true;
    }

};

int main() {
    mpz_class a, b;
    char action;
    auto start = std::chrono::steady_clock::now();
    while(!std::cin.eof()) {
        std::cin >> a >> b >> action;
        if (std::cin.eof()) {
            break;
        }
        if (action == '+') {
            std::cout << a + b << "\n";
        } else if (action == '-') {
            try {
                std::cout << a - b << '\n';
            } catch (...) {
                std::cout << "Error\n";
            }
        } else if (action == '*') {
            std::cout << a * b << '\n';
        } else if (action == '/') {
            try {
                std::cout << a / b << '\n';
            } catch (...) {
                std::cout << "Error\n";
            }
        } else if (action == '^') {
            try {
                std::cout << (a ^ b) << '\n';
            } catch (...) {
                std::cout << "Error\n";
            }
        } else if (action == '<') {
            if (a < b) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        } else if (action == '>') {
            if (a > b) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        } else if (action == '=') {
            if (a == b) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
    }
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    std::cerr << "GMP arithmetics " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms" << std::endl;
}
