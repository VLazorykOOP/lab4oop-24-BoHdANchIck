#include <iostream>
#include <map>
#include <string>

class Assoc {
    std::map<std::string, std::string> data;
    int errorCode;

public:
    enum ErrorCodes {
        NO_ERROR = 0,
        EMAIL_NOT_FOUND
    };

    Assoc() : errorCode(NO_ERROR) {}
    void createAssociations(const std::map<std::string, std::string>& associations) {
        data = associations;
    }


    // [] ()
    std::string operator[](const std::string& email) {
        if (data.find(email) != data.end()) {
            return data[email];
        } else {
            errorCode = EMAIL_NOT_FOUND;
            return "";
        }
    }
    std::string operator()(const std::string& email) {
        return (*this)[email];
    }


    int getErrorCode() const {
        return errorCode;
    }


    // << >>
    friend std::ostream& operator<<(std::ostream& os, const Assoc& assoc) {
        for (const auto& pair : assoc.data) {
            os << "Email: " << pair.first << ", Phone: " << pair.second << std::endl;
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Assoc& assoc) {
        std::string email, phone;
        while (is >> email >> phone) {
            assoc.data[email] = phone;
        }
        return is;
    }
};

int main() {
    Assoc contacts;
    
    std::map<std::string, std::string> associations = {
        {"bobr@gmail.com",  "1234567890"},
        {"golub@gmail.com", "4173481342"},
        {"bobik@gmail.com", "1837126542"},
        {"pes_patron@gamil.com", "1341534563"},
        {"kaboom@gamil.com", "7528929101"}
    };
    contacts.createAssociations(associations);

    std::cout << "Associations:\n";
    std::cout << contacts;

    std::cout << "[]:\n";
    std::cout << contacts["bobr@gmail.com"] << std::endl;
    std::cout << contacts["golub@gmail.com"] << std::endl;
    std::cout << contacts["bobik@gmail.com"] << std::endl;
    std::cout << contacts["pes_patron@gamil.com"] << std::endl;
    std::cout << contacts["kaboom@gamil.com"] << std::endl;

    std::cout << "():\n";
    std::cout << contacts("bobr@gmail.com") << std::endl;
    std::cout << contacts("golub@gmail.com") << std::endl;
    std::cout << contacts("bobik@gmail.com") << std::endl;
    std::cout << contacts("pes_patron@gamil.com") << std::endl;
    std::cout << contacts("kaboom@gamil.com") << std::endl;
    return 0;
}
