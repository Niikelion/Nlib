#ifndef ARRWRAP_H
#define ARRWRAP_H

namespace Nlib
{
    template<typename T,unsigned n> class DimensionalArray
    {
    protected:
        T* _data;
        unsigned _dims[n];
    public:
        unsigned* getDimensions() noexcept;
        bool setArray(T data[],unsigned long long size,unsigned dims[n]);
        bool setArrayP(T* data,unsigned long long size,unsigned dims[n]);
        void setArray(unsigned dims[n]);

        T& at(unsigned dims[n]);
    };
}

#endif // ARRWRAP_H
