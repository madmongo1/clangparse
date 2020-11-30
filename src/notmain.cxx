#include <string>

enum class MyEnum
{
    x = 10,
    y = 20
};

struct polymorphic {
    polymorphic() noexcept;

    virtual ~polymorphic() = default;

    virtual void
    foo(int i = 0) = 0;
};

struct derived : polymorphic {

    derived(int) : polymorphic() {}

    void
    foo(int) override;

    bool
    operator==(const derived &o) const;
};

template<typename T>
void
bar(T &&t);
