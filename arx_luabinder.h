#ifndef SCRIPTER_H_
#define SCRIPTER_H_

#include <cstring>
#include <vector>
#include <stdint.h>

extern "C" {
#include "./depends/lua-5.2.2/lua.h"
#include "./depends/lua-5.2.2/lauxlib.h"
#include "./depends/lua-5.2.2/lualib.h" 
} 

typedef int (*LuaFunction)(lua_State*);

class ScripterFunctionBase
{
    LuaFunction retfunc_;
public:

    LuaFunction get_function()
    {
        return retfunc_;
    }
protected:
    void set_function(LuaFunction func)
    {
        retfunc_ = func;
    }
};

/*******************************************  ScripterLuaHelper *************************************/

/** some template meta-programming stuff **/
template <typename T, bool sz>
struct _IA
{
    typedef T& ThisType;
    static T& RevCaster(void* t)
    {
        return *((T*)t);
    }

    static void* Caster(T t)
    {
        return (void*)&t;
    }
};

template <typename T>
struct _IA<T, true>
{
    typedef T ThisType;
    static  T RevCaster(void* t)
    {
        return T(t);
    }

    static void* Caster(T t)
    {
        return (void*)t;
    }
};

/** ^ **/

template <typename T>
class ScripterLuaHelper
{
public:
    typedef T& ThisType;

    inline static T& pop_data(lua_State* L, long i)
    {
        return *((T*)lua_touserdata(L, i));
    }

    inline static int push_data(lua_State* L, T data)
    {
        lua_pushlightuserdata(L, (void*)(&data));
        return 1;
    }
};

template <typename T>
class ScripterLuaHelper<T*>
{
public:
    typedef T* ThisType;

    inline static T* pop_data(lua_State* L, long i)
    {
        return (T*)lua_touserdata(L, i);
    }

    inline static int push_data(lua_State* L, T* data)
    {
        lua_pushlightuserdata(L, (void*)data);
        return 1;
    }
};

template <>
class ScripterLuaHelper<int>
{
public:

    typedef int ThisType;

    inline static int pop_data(lua_State* L, long i)
    {
        return luaL_checkint(L, i);
    }

    inline static int push_data(lua_State* L, int data)
    {
        lua_pushinteger(L, data);
        return 1;
    }
};

template <>
class ScripterLuaHelper<long>
{
public:

    typedef long ThisType;

    inline static long pop_data(lua_State* L, long i)
    {
        return luaL_checklong(L, i);
    }

    inline static int push_data(lua_State* L, long data)
    {
        lua_pushinteger(L, data);
        return 1;
    }
};

template <>
class ScripterLuaHelper<double>
{
public:

    typedef double ThisType;

    inline static double pop_data(lua_State* L, long i)
    {
        return luaL_checknumber(L, i);
    }

    inline static int push_data(lua_State* L, double data)
    {
        lua_pushnumber(L, data);
        return 1;
    }
};

template <>
class ScripterLuaHelper<float>
{
public:

    typedef float ThisType;

    inline static float pop_data(lua_State* L, long i)
    {
        return float(luaL_checknumber(L, i));
    }

    inline static int push_data(lua_State* L, float data)
    {
        lua_pushnumber(L, (double)data);
        return 1;
    }
};

template <>
class ScripterLuaHelper<const char*>
{
public:

    typedef const char* ThisType;

    inline static const char* pop_data(lua_State* L, long i)
    {
        return luaL_checkstring(L, i);
    }

    inline static int push_data(lua_State* L, const char* data)
    {
        lua_pushstring(L, data);
        return 1;
    }
};

/********************************************   ScripterFunction *************************************/

template <int ID, typename Ctype, typename RetType = int, typename A = int, typename B = int, typename C = int, typename D = int>
class ScripterFunction : public ScripterFunctionBase
{
    typedef ScripterFunction<ID, Ctype, RetType, A, B, C, D>  ThisType;
    typedef RetType (Ctype::*_func0) ();
    typedef RetType (Ctype::*_func1) (A);
    typedef RetType (Ctype::*_func2) (A, B);
    typedef RetType (Ctype::*_func3) (A, B, C);
    typedef RetType (Ctype::*_func4) (A, B, C, D);

    /// no arg
    static int lua_func0_0(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        RetType ret = (t->*((_func0)t->get_function(ID)))();
        ScripterLuaHelper<RetType>::push_data(L, ret);
        return 1;
    }

    static int lua_func0_1(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        RetType ret = (t->*((_func1)t->get_function(ID)))(at);
        ScripterLuaHelper<RetType>::push_data(L, ret);
        return 1;
    }

    static int lua_func0_2(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        typename ScripterLuaHelper<B>::ThisType bt = ScripterLuaHelper<B>::pop_data(L, 3);
        RetType ret = (t->*((_func2)t->get_function(ID)))(at, bt);
        ScripterLuaHelper<RetType>::push_data(L, ret);
        return 1;
    }

    static int lua_func0_3(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        typename ScripterLuaHelper<B>::ThisType bt = ScripterLuaHelper<B>::pop_data(L, 3);
        typename ScripterLuaHelper<C>::ThisType ct = ScripterLuaHelper<C>::pop_data(L, 4);
        RetType ret = (t->*((_func3)t->get_function(ID)))(at, bt, ct);
        ScripterLuaHelper<RetType>::push_data(L, ret);
        return 1;
    }

    static int lua_func0_4(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        typename ScripterLuaHelper<B>::ThisType bt = ScripterLuaHelper<B>::pop_data(L, 3);
        typename ScripterLuaHelper<C>::ThisType ct = ScripterLuaHelper<C>::pop_data(L, 4);
        typename ScripterLuaHelper<D>::ThisType dt = ScripterLuaHelper<D>::pop_data(L, 5);
        RetType ret = (t->*((_func4)t->get_function(ID)))(at, bt, ct, dt);
        ScripterLuaHelper<RetType>::push_data(L, ret);
        return 1;
    }
public:
    ScripterFunction(RetType (Ctype::*func)())
    {
        this->set_function(lua_func0_0);
    }

    ScripterFunction(RetType (Ctype::*func)(A))
    {
        this->set_function(lua_func0_1);
    }

    ScripterFunction(RetType (Ctype::*func)(A, B))
    {
        this->set_function(lua_func0_2);
    }

    ScripterFunction(RetType (Ctype::*func)(A, B, C))
    {
        this->set_function(lua_func0_3);
    }

    ScripterFunction(RetType (Ctype::*func)(A, B, C, D))
    {
        this->set_function(lua_func0_4);
    }
};

/*************************** for functions that is 'void' **************************************/

template <int ID, typename Ctype, typename A, typename B, typename C, typename D>
class ScripterFunction<ID, Ctype, void, A, B, C, D> : public ScripterFunctionBase
{
    typedef void (Ctype::*_func0) ();
    typedef void (Ctype::*_func1) (A);
    typedef void (Ctype::*_func2) (A, B);
    typedef void (Ctype::*_func3) (A, B, C);
    typedef void (Ctype::*_func4) (A, B, C, D);

    /// no arg
    static int lua_func0_0(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        (t->*((_func0)t->get_function(ID)))();
        return 0;
    }

    static int lua_func0_1(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        (t->*((_func1)t->get_function(ID)))(at);
        return 0;
    }

    static int lua_func0_2(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        typename ScripterLuaHelper<B>::ThisType bt = ScripterLuaHelper<B>::pop_data(L, 3);
        (t->*((_func2)t->get_function(ID)))(at, bt);
        return 0;
    }

    static int lua_func0_3(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        typename ScripterLuaHelper<B>::ThisType bt = ScripterLuaHelper<B>::pop_data(L, 3);
        typename ScripterLuaHelper<C>::ThisType ct = ScripterLuaHelper<C>::pop_data(L, 4);
        (t->*((_func3)t->get_function(ID)))(at, bt, ct);
        return 0;
    }

    static int lua_func0_4(lua_State* L)
    {
        Ctype* t = (Ctype*) lua_touserdata(L, 1);
        typename ScripterLuaHelper<A>::ThisType at = ScripterLuaHelper<A>::pop_data(L, 2);
        typename ScripterLuaHelper<B>::ThisType bt = ScripterLuaHelper<B>::pop_data(L, 3);
        typename ScripterLuaHelper<C>::ThisType ct = ScripterLuaHelper<C>::pop_data(L, 4);
        typename ScripterLuaHelper<D>::ThisType dt = ScripterLuaHelper<D>::pop_data(L, 5);
        (t->*((_func4)t->get_function(ID)))(at, bt, ct, dt);
        return 0;
    }
public:
    ScripterFunction(void (Ctype::*func)())
    {
        this->set_function(lua_func0_0);
    }

    ScripterFunction(void (Ctype::*func)(A))
    {
        this->set_function(lua_func0_1);
    }

    ScripterFunction(void (Ctype::*func)(A, B))
    {
        this->set_function(lua_func0_2);
    }

    ScripterFunction(void (Ctype::*func)(A, B, C))
    {
        this->set_function(lua_func0_3);
    }

    ScripterFunction(void (Ctype::*func)(A, B, C, D))
    {
        this->set_function(lua_func0_4);
    }
};

template<typename T> class ScripterReg;

template <uint32_t function_count>
class ScripterData
{
    typedef int (ScripterData<function_count>::*_df)();

    static char name_[256];
    static _df  fptr_[function_count];

protected:
    template<typename T> friend class ScripterReg;
public:

    typedef _df FType;

    ScripterData<function_count>::_df get_function(uint32_t index)
    {
        return fptr_[index];
    }

    uint32_t add_func(uint32_t id, int (ScripterData<function_count>::*func)())
    {
        fptr_[id] = (_df)func;
        return id;
    }

    template <typename T>
    void N() { }

    void callfunc(uint32_t i)
    {
        (this->*(this->get_function(i)))();
    }

    uint32_t fsize() const
    {
        return function_count;
    }

    void copy_to(void* mem)
    {
        memcpy(mem, this, sizeof(ScripterData<function_count>));
    }

    int test()
    {
        std::cout << "called." << std::endl;
        return 0;
    }
};

template <uint32_t function_count>
char ScripterData<function_count>::name_[256];

template <uint32_t function_count>
typename ScripterData<function_count>::_df ScripterData<function_count>::fptr_[function_count];


template <typename T>
class ScripterReg
{
    struct lua_reg : public luaL_Reg
    {
    public:
        lua_reg()
        {
            name = NULL;
            func = NULL;
        }

        void set(const char* s, lua_CFunction f)
        {
            name = s;
            func = f;
        }
    };

    T   *ptr_;
    uint32_t index_;

    std::string          clsname_;
    std::vector<lua_reg> array_;
    std::vector<lua_reg> arrayt_;

    static int pf_new(lua_State* s)
    {
        T* t = (T*) lua_newuserdata(s, sizeof(T));
        new ((void*)t) T();
        luaL_getmetatable(s, t->name_);
        lua_setmetatable(s, -2);
        return 1;
    }
public:
    ScripterReg(T& t, const char* name) : index_(0)
    {
        std::string name_ = "LuaBook.";
        name_ += name;
        clsname_ = name;

        ptr_ = &t;
        strcpy(ptr_->name_, name_.c_str());
        array_.resize( t.fsize()+1, lua_reg());
        arrayt_.resize( 2, lua_reg());
        arrayt_[0].set("new", pf_new);
    }

    template <uint32_t ID, typename RetType>
    uint32_t add_func(RetType (T::*func)(), const char* name)
    {
        ScripterFunction<ID, T, RetType> temp(func);
        array_[index_++].set(name, temp.get_function());
        ptr_->add_func(ID, (typename T::FType)func);
        return 0;
    }

    template <uint32_t ID, typename RetType, typename A>
    uint32_t add_func(RetType (T::*func)(A), const char* name)
    {
        ScripterFunction<ID, T, RetType, A> temp(func);
        array_[index_++].set(name, temp.get_function());
        ptr_->add_func(ID, (typename T::FType)func);
        return 0;
    }

    template <uint32_t ID, typename RetType, typename A, typename B>
    uint32_t add_func(RetType (T::*func)(A, B), const char* name)
    {
        ScripterFunction<ID, T, RetType, A, B> temp(func);
        array_[index_++].set(name, temp.get_function());
        ptr_->add_func(ID, (typename T::FType)func);
        return 0;
    }

    template <uint32_t ID, typename RetType, typename A, typename B, typename C>
    uint32_t add_func(RetType (T::*func)(A, B, C), const char* name)
    {
        ScripterFunction<ID, T, RetType, A, B, C> temp(func);
        array_[index_++].set(name, temp.get_function());
        ptr_->add_func(ID, (typename T::FType)func);
        return 0;
    }

    template <uint32_t ID, typename RetType, typename A, typename B, typename C, typename D>
    uint32_t add_func(RetType (T::*func)(A, B, C, D), const char* name)
    {
        ScripterFunction<ID, T, RetType, A, B, C, D> temp(func);
        array_[index_++].set(name, temp.get_function());
        ptr_->add_func(ID, (typename T::FType)func);
        return 0;
    }
    void register_type(lua_State* handle)
    {
        luaL_newmetatable(handle, ptr_->name_);
        lua_pushvalue(handle, -1);
        lua_setfield(handle, -2, "__index");
        luaL_register(handle, NULL, array_.data());
        luaL_register(handle, clsname_.c_str(), arrayt_.data());
    }
};


class ScripterModule
{
    typedef  void (*ft_error)(const char*);

    ft_error  f_error;
    lua_State *L_;
public:
    ScripterModule() : f_error(NULL), L_(NULL)
    {
        L_ = lua_open();
    }

    void open_libs()
    {
        luaL_openlibs(L_);
    }

    virtual ~ScripterModule()
    {
        lua_close(L_);
    }

    operator lua_State*() const
    {
        return L_;
    }

    lua_State *get_handle() const
    {
        return L_;
    }

    void reg_function(int (*func)(lua_State*), const char* name)
    {
        lua_register(L_, name, func);
    }

    void run_file(const char* filename)
    {
        if(luaL_loadfile(L_, filename) == 0)
        {
            if(lua_pcall(L_, 0, LUA_MULTRET, 0) != 0)
            {
                if(f_error != NULL)
                {
                    f_error( lua_tostring(L_, -1) );
                    lua_pop(L_, 1);
                }
            }
        }
    }

    void error_handler(ft_error t)
    {
        f_error = t;
    }
};


#endif
