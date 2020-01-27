#ifndef SLIB_H
#define SLIB_H

#include <string>

namespace Nlib
{
    class SharedLib
    {
    private:
        void* handle;
    public:
        void* getAddress(const std::string& name) const;
        template<typename T,typename ... Args> auto getFunction(const std::string& name) const -> T(__cdecl *)(Args...)
        {
            return reinterpret_cast<T(__attribute((__cdecl__)) *)(Args...)>(getAddress(name));
        }

        template<typename T,typename ... Args> auto getFunctionStd(const std::string& name) const -> T(__stdcall *)(Args...)
        {
            return reinterpret_cast<T(__attribute((__stdcall__)) *)(Args...)>(getAddress(name));
        }

        template<typename T,typename ... Args> auto getFunctionFast(const std::string& name) const -> T(__fastcall *)(Args...)
        {
            return reinterpret_cast<T(__attribute((__fastcall__)) *)(Args...)>(getAddress(name));
        }

        bool load(const std::string& path);
        void free();

        SharedLib();
        SharedLib(const SharedLib&) = delete;
        SharedLib(SharedLib&&) noexcept;
        ~SharedLib();
    };
}

#endif // SLIB_H
