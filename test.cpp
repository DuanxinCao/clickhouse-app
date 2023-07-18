#include <memory>
#include <iostream>

class A{
public:
    int a=1;
    void seta(){
        a=2;
    }
};
void test(std::shared_ptr<A> &b){
    std::shared_ptr<A> a(new A());
    a->seta();
    b = a;
    std::cout<<"---"<<b->a<<std::endl;
    std::cout<<"---"<<a->a<<std::endl;

}

int main(){
    std::shared_ptr<A> b;
    test(b);
    std::cout<<b->a<<std::endl;

    return 1;
}