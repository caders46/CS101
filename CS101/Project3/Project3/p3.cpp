#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info* next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact* next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream& os, std::string first, std::string last) {
    Contact* current = headContactList;
    Info* curr;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            os << "Contact Name: " << first << " " << last << endl;
            curr = current->headInfoList;
            while (curr != nullptr) {
                os << "    " << curr->name << " | " << curr->value << endl;
                curr = curr->next;
            }
            return true;
        }
        else {
            current = current->next;
        }
    }
    return false;
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream& os) {
    Contact* current = headContactList;
    Info* curr;
    while (current != nullptr) {
        os << "Contact Name: " << current->first << " " << current->last << endl;
        curr = current->headInfoList;
        while (curr != nullptr) {
            os << "    " << curr->name << " | " << curr->value << endl;
            curr = curr->next;
        }
        current = current->next;
    }
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
    Contact* current = headContactList;
    if (headContactList != nullptr) {
        if (headContactList->first != first || headContactList->last != last) {
            while (current->next != nullptr) {
                if (current->next->first == first && current->next->last == last){
                    return false;
                }
                else {
                    current = current->next;
                }
            }
            current->next = new Contact(first, last, nullptr);
            count++;
            return true;
        }
        else {
            return false;
        }
    }
    else {
        headContactList = new Contact(first, last, nullptr);
        count++;
        return true;
    }
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact* current = headContactList;
    bool isContact = false;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            isContact = true;
            break;
        }
        else {
            current = current->next;
        }
    }
    if (isContact) {
        Info* curr = current->headInfoList;
        if (curr == nullptr) {
            current->headInfoList = new Info(infoName, infoVal, nullptr);
            return true;
        }
        else {
            while (curr != nullptr) {
                if (curr->name == infoName) {
                    curr->value = infoVal;
                    return true;
                }
                curr = curr->next;
            }
            curr = current->headInfoList;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
        }
        curr->next = new Info(infoName, infoVal, nullptr);
        return true;
    }
    else { return false; }
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last) {
    Contact* current = headContactList;
    Contact* curr = headContactList;
    int index = 0;
    if (current == nullptr) {
        headContactList = new Contact(first, last, nullptr);
        count++;
        return true;
    }
    while (current->last < last) {
        if (current->next == nullptr) {
            addContact(first, last);
        }
        else {
            current = current->next;
            index++;
        }
    }
    if (current->last == last) {
        while (current->first < first && current->last == last) {
            if (current->next == nullptr) {
                return addContact(first, last);
            }
            else {
                current = current->next;
                index++;
            }
        }
        if (current->first == first) {
            cout << "HE" << endl;
            return false;
        }
        else {
            if (index == 0) {
                headContactList = new Contact(first, last, headContactList);
                count++;
                return true;
            }
            else {
                Contact* c1 = headContactList;
                Contact* c2 = headContactList->next;
                for (int i = 0; i < index - 1; i++) {
                    c1 = c1->next;
                    c2 = c2->next;
                }
                c1->next = new Contact(first, last, c2);
                count++;
                return true;
            }
        }
    }
    else {
        if (index == 0) {
            headContactList = new Contact(first, last, headContactList);
            count++;
            return true;
        }
        else {
            Contact* c1 = headContactList;
            Contact* c2 = headContactList->next;
            for (int i = 0; i < index-1; i++) {
                c1 = c1->next;
                c2 = c2->next;
            }
            c1->next = new Contact(first, last, c2);
            count++;
            return true;
        }
    }


    return true;
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact* current = headContactList;
    int index = 0;
    bool isContact = false;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            isContact = true;
            break;
        }
        else {
            current = current->next;
        }
    }
    if (isContact) {
        Info* curr = current->headInfoList;
        if (curr == nullptr) {
            current->headInfoList = new Info(infoName, infoVal, nullptr);
            return true;
        }
        else {
            while (curr->name < infoName) {
                if (curr->next == nullptr) {
                    addInfo(first, last, infoName, infoVal);
                }
                else {
                    curr = curr->next;
                    index++;
                }
            }
            if (curr->name == infoName) {
                curr->value = infoVal;
                return true;
            }
            else {
                if (index == 0) {
                    current->headInfoList = new Info(infoName, infoVal, current->headInfoList);
                    return true;
                }
                else {
                    Info* i1 = current->headInfoList;
                    Info* i2 = current->headInfoList->next;
                    for (int i = 0; i < index - 1; i++) {
                        i1 = i1->next;
                        i2 = i2->next;
                    }
                    i1->next = new Info(infoName, infoVal, i2);
                    return true;
                }
            }
        }
    }
    else { return false; }
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    Contact* current = headContactList;
    int index = 0;
    bool isContact = false;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            isContact = true;
            break;
        }
        else {
            current = current->next;
            index++;
        }
    }
    if (isContact) {
        if (index == 0) {
            headContactList = headContactList->next;
        }
        else {
            current = headContactList;
            for (int i = 0; i < index-1; i++) {
                current = current->next;
            }
            current->next = current->next->next;
            count--;
            if(headContactList == nullptr){
                count = 0;
            }
            return true;
        }
    }
    else {
        if(headContactList == nullptr){
                count = 0;
        }
        return false;
    }
    return true;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    Contact* current = headContactList;
    Info* curr;
    int index = 0;
    bool isContact = false;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            isContact = true;
            break;
        }
        else {
            current = current->next;
        }
    }
    if (isContact) {
        bool isInfo = false;
        curr = current->headInfoList;
        while(curr!=nullptr){
            if (curr->name == infoName) {
                isInfo = true;
                break;
            }
            else {
                curr = curr->next;
                index++;
            }
        }
        if(isInfo){
            if (index == 0) {
                current->headInfoList = current->headInfoList->next;
                return true;
            }
            else {
                curr = current->headInfoList;
                for (int i = 0; i < index - 1; i++) {
                    curr = curr->next;
                }
                curr->next = curr->next->next;
                return true;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {
    Contact* current = headContactList;
    while (current != nullptr) {
        Contact* next = current->next;
        removeContact(current->first,current->last);
        current = next;
    }
    headContactList = nullptr;
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList& src) {
    count = src.count;
    if (src.headContactList != nullptr) {
        Contact* tmp = src.headContactList;
        Info* tmp2;
        headContactList = new Contact(src.headContactList->first, src.headContactList->last, nullptr);
        Contact* curr = headContactList;
        if (tmp->headInfoList != nullptr) {
            tmp2 = tmp->headInfoList;
            while (tmp2 != nullptr) {
                addInfo(tmp->first, tmp->last, tmp2->name, tmp2->value);
                tmp2 = tmp2->next;
            }
        }
        tmp = tmp->next;
        while (tmp != nullptr) {
            curr->next = new Contact;
            curr = curr->next;
            curr->first = tmp->first;
            curr->last = tmp->last;
            curr->next = nullptr;
            if (tmp->headInfoList != nullptr) {
                tmp2 = tmp->headInfoList;
                while (tmp2 != nullptr) {
                    addInfo(tmp->first, tmp->last, tmp2->name, tmp2->value);
                    tmp2 = tmp2->next;
                }
            }
            tmp = tmp->next;
        }
    }
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList& ContactList::operator=(const ContactList& src) {
    if (this != &src) {
        Contact* current = headContactList;
        while (current != nullptr) {
            Contact* next = current->next;
            removeContact(current->first, current->last);
            current = next;
        }
        headContactList = nullptr;
        count = src.count;
        if (src.headContactList == nullptr) {
            return *this;
        }
        Contact* tmp = src.headContactList;
        Info* tmp2;
        headContactList = new Contact(src.headContactList->first, src.headContactList->last, nullptr);
        Contact* curr = headContactList;
        if (tmp->headInfoList != nullptr) {
            tmp2 = tmp->headInfoList;
            while (tmp2 != nullptr) {
                addInfo(tmp->first, tmp->last, tmp2->name, tmp2->value);
                tmp2 = tmp2->next;
            }
        }
        tmp = tmp->next;
        while (tmp != nullptr) {
            curr->next = new Contact;
            curr = curr->next;
            curr->first = tmp->first;
            curr->last = tmp->last;
            curr->next = nullptr;
            if (tmp->headInfoList != nullptr) {
                tmp2 = tmp->headInfoList;
                while (tmp2 != nullptr) {
                    addInfo(tmp->first, tmp->last, tmp2->name, tmp2->value);
                    tmp2 = tmp2->next;
                }
            }
            tmp = tmp->next;
        }
    }
    return *this;
}
