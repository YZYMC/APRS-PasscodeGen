#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <Windows.h>

uint16_t get_passcode(const std::string& callsign) {//Generate
    uint16_t tmp_code = 29666;
    if (std::all_of(callsign.begin(), callsign.end(), [](char c) {
        return std::isalnum(c) || c == '-';
        })) {
        std::string upper_callsign;
        for (char c : callsign) {
            upper_callsign += std::toupper(c);
        }
        for (size_t i = 0; i < upper_callsign.length(); i += 2) {
            tmp_code ^= static_cast<uint16_t>(upper_callsign[i]) * 256;
            tmp_code ^= static_cast<uint16_t>(upper_callsign[i + 1]);
        }
        tmp_code &= 32767;
    }
    else {
        throw std::invalid_argument("�ú�����Ч��������һ�Σ�");
    }
    return tmp_code;
}

int main() {
    std::string input;//Input
    std::cout << "APRS Internet Passcode Gen\n������APRS��֤�������\nBy YZYNetwork v1.0" << std::endl << "��ע�⣺������������ںϷ����ŵļ��㣡���߲��е�Υ��ʹ����ɵĺ����" << std::endl << "���ó���������ȹ����������" << std::endl << "������ĺ��� Please input your callsign: ";
    std::getline(std::cin, input);
    try {
        uint16_t passcode = get_passcode(input);
        std::cout << "���APRS Internet��֤����" << passcode << std::endl << "���ڽ���6���رգ�";
        Sleep(6000);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
