

#include <iostream>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

std::string md5(const std::string& str) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    #pragma warning(suppress : 4996)
    MD5(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), digest);

    std::ostringstream oss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(digest[i]);
    }
    return oss.str();
}

int main() {

    std::cout << "Enter some data to hash: ";
    std::string data;
    std::getline(std::cin, data);
    std::string data_to_hash = "", total_hash= "";
    int counter = 0;
    for (int i = 0; i < data.length(); i++) {
        counter++;
        data_to_hash += data[i];
        if (counter == 16) {
            counter = 0;
            std::cout << "hash of another 16 byte ("<< data_to_hash <<") block of data is : " << md5(data_to_hash) << "\n";
            total_hash += md5(data_to_hash);
            data_to_hash = "";
        }
    }
    if (counter != 0) {

        std::cout << "hash of partial (" << data_to_hash << ") block of data is : " << md5(data_to_hash) << "\n";
        total_hash += md5(data_to_hash);
    }
    std::cout << "\nThe total hash of data is: " << total_hash<<"\n";

    return 0;
}
