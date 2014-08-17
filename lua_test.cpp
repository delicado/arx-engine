

#include <iostream>
// binder header.
#include "arx_luabinder.h"

// error callback
void report_error(const char* t)
{
    std::cerr << "-- " << t << std::endl;
}

// para ma-expose ang class, dapat maging base class nya muna ang ScripterData class
// yung parameter ng ScripterData, ang maximum na function na i-expose sa Lua interpreter

struct TT : public ScripterData<15>
{
    std::string str;

    void function1(const char* message)
    {
        std::cout << "function1 called: " << message << std::endl;
    }

    std::string* function2()
    {
        std::cout << "function2 called" << std::endl;
        return &str;
    }

    void function3(const std::string* t)
    {
        std::cout << "function3 called: " << *t << std::endl;
    }

    void function4(const char* t)
    {
        std::cout << "function4 called" << std::endl;
        str = t;
    }
};

int main(int argc, char** argv)
{
    TT  temp;
    if(argc > 1)
    {
        // i suggest you learn Lua. at http://www.lua.org
        ScripterModule lua;
        lua.open_libs();
        lua.error_handler(report_error);
        
        // ScripterReg, class na mag-register ng class na derived sa ScripterData
        ScripterReg<TT> reg(temp, "Entity");

        // ganito mag-add ng function. dapat unique ang ID at name (yung strings).
        reg.add_func<0> (&TT::function1, "test");
        reg.add_func<1> (&TT::function2, "get_data");
        reg.add_func<2> (&TT::function3, "set_data");
        reg.add_func<3> (&TT::function4, "set_text");

        // then register.
        reg.register_type(lua.get_handle());

        // loads a lua file. then runs it.
        lua.run_file(argv[1]);
    }

    return 0;
}
