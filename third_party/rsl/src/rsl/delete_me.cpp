
#include "concepts"
#include "delegate"
#include "hash"
#include "primitives"
#include "type_util"
#include "utilities"

#include <iostream>

namespace rsl {
    static void func() {
        std::cout << "function\n";
    }

    struct Object {
        std::vector<int> ints;

        void memberFunc() {
            std::cout << "member function: ";

            for (int& i : ints) {
                i++;
                std::cout << " " << std::to_string(i) << " ";
            }

            std::cout << '\n';
        }

        void memberFunc() const {
            std::cout << "const member function: ";

            for (int i : ints) {
                std::cout << " " << std::to_string(i) << " ";
            }

            std::cout << '\n';
        }
    };

    static std::vector<int> createVec() {
        std::vector<int> vec;
        for (int i = 20; i > 0; i--) {
            vec.push_back(i);
        }
        return vec;
    }

    void sizeTest(size_type s) {
        std::cout << std::to_string(s) << "\n";
    }

    void sizeTest(npos_type np) {
        std::cout << std::to_string(np) << "\n";
    }


    int main() {

        sizeTest(4);
        sizeTest(npos);

        delegate<void()> del;

        {
            del = &func;
        }

        del();

        {
            del = []() {
                std::cout << "stateless lambda\n";
            };
        }

        del();

        {
            std::vector<int> ints = createVec();
            del = [ints]() {
                std::cout << "statefull lambda: ";

                for (int i : ints) {
                    std::cout << " " << std::to_string(i) << " ";
                }

                std::cout << '\n';
            };
        }

        del();

        {
            Object obj{ createVec() };
            {
                del.assign<Object, &Object::memberFunc>(obj);
            }

            del();
        }


        {
            const Object obj{ createVec() };
            {
                del.assign<Object, &Object::memberFunc>(obj);
            }

            del();
        }

        return 0;
    }

}
