#pragma once


namespace ya
{
    class PseudoString {
    private:
        char* string;
        unsigned int len;

        void Swap(PseudoString& s);
    public:
        PseudoString();

        PseudoString(unsigned int length);

        PseudoString(const char* char_array);

        ~PseudoString();

        PseudoString(const PseudoString& other);

        PseudoString& operator=(PseudoString other);

        char& operator[](int index);

        PseudoString& operator+=(const PseudoString& other);

        PseudoString& operator+=(const char* other);

        PseudoString operator+(const PseudoString& other);

        PseudoString operator+(const char* other);

        PseudoString& operator*=(const unsigned short n);

        PseudoString operator*(const unsigned short n);

        PseudoString Slice(int start, int end, int step=1);

        PseudoString Reversed();

        void Reverse();

        unsigned int getLength();

        void Print();
    };

    PseudoString operator+(const PseudoString& a, const PseudoString& other);

    PseudoString operator+(const char* a, const PseudoString& other);

    PseudoString operator*(const unsigned short n, const PseudoString& string);
}
