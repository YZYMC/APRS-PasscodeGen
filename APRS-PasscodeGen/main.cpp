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
        throw std::invalid_argument("该呼号无效，请再试一次！");
    }
    return tmp_code;
}

int main() {
    std::string input;//Input
    std::cout << "APRS Internet Passcode Gen\n互联网APRS验证码计算器\nBy YZYNetwork v1.0" << std::endl << "请注意：本软件仅可用于合法呼号的计算！作者不承担违规使用造成的后果！" << std::endl << "适用场景：不想等官网给你计算" << std::endl << "输入你的呼号 Please input your callsign: ";
    std::getline(std::cin, input);
    try {
        uint16_t passcode = get_passcode(input);
        std::cout << "你的APRS Internet验证码是" << passcode << std::endl << "窗口将于6秒后关闭！";
        Sleep(6000);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
