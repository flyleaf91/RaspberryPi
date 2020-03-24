#include <iostream>
#include <memory>

struct Task {
    int mId;

    Task(int id ) :mId(id) {
        std::cout << "Task::Constructor" << std::endl;
    }

    ~Task() {
        std::cout << "Task::Destructor" << std::endl;
    }

    void print(void) {
        std::cout << mId << std::endl;

        return;
    }
};

int main()
{
    // 通过原始指针创建 unique_ptr 实例
    std::unique_ptr<Task> taskPtr(new Task(23));

    //通过 unique_ptr 访问其成员
    std::cout << taskPtr->mId << std::endl;
    taskPtr->print();

    taskPtr->mId = 25;
    Task *ptr = taskPtr.get();
    std::cout << ptr << std::endl;
    ptr->print();

    return 0;
}
