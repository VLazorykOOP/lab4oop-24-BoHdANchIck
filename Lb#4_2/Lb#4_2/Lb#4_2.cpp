#include <iostream>
#include <string>

class Assoc {
    struct Node {
        std::string email;
        std::string phone;
        Node* next;

        Node(const std::string& e, const std::string& p) : email(e), phone(p), next(nullptr) {}
    };

    Node* head;
    int errorCode;

public:
    enum ErrorCodes {
        NO_ERROR = 0,
        EMAIL_NOT_FOUND
    };

    Assoc() : head(nullptr), errorCode(NO_ERROR) {}

    ~Assoc() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void createAssociations(const std::string& email, const std::string& phone) {
        Node* newNode = new Node(email, phone);
        newNode->next = head;
        head = newNode;
    }

    std::string operator[](const std::string& email) {
        Node* current = head;
        while (current != nullptr) {
            if (current->email == email) {
                errorCode = NO_ERROR;
                return current->phone;
            }
            current = current->next;
        }
        errorCode = EMAIL_NOT_FOUND;
        return "";
    }

    std::string operator()(const std::string& email) {
        return (*this)[email];
    }

    int getErrorCode() const {
        return errorCode;
    }

    friend std::ostream& operator<<(std::ostream& os, const Assoc& assoc) {
        Node* current = assoc.head;
        while (current != nullptr) {
            os << "Email: " << current->email << ", Phone: " << current->phone << std::endl;
            current = current->next;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Assoc& assoc) {
        std::string email, phone;
        while (is >> email >> phone) {
            assoc.createAssociations(email, phone);
        }
        return is;
    }
};

int main() {
    Assoc contacts;

    contacts.createAssociations("bobr@gmail.com", "1234567890");
    contacts.createAssociations("golub@gmail.com", "4173481342");
    contacts.createAssociations("bobik@gmail.com", "1837126542");

    std::cout << "Associations:\n";
    std::cout << contacts;

    std::cout << "[]:\n";
    std::cout << "Phone for bobr@gmail.com: " << contacts["bobr@gmail.com"] << std::endl;
    std::cout << "Phone for golub@gmail.com: " << contacts["golub@gmail.com"] << std::endl;
    std::cout << "Phone for bobik@gmail.com: " << contacts["bobik@gmail.com"] << std::endl;

    std::cout << "():\n";
    std::cout << "Phone for bobr@gmail.com: " << contacts("bobr@gmail.com") << std::endl;
    std::cout << "Phone for golub@gmail.com: " << contacts("golub@gmail.com") << std::endl;
    std::cout << "Phone for bobik@gmail.com: " << contacts("bobik@gmail.com") << std::endl;

    return 0;
}
