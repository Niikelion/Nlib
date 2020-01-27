#ifndef STRINGTREE_H_INCLUDED
#define STRINGTREE_H_INCLUDED


#include<nlib/utility/nullutil.h>
#include<cinttypes>
#include<string>

template<typename Type>class StringTreeCell
{
    StringTreeCell**_tree;
    size_t id;
    Type data;
public:
    bool find(std::string index)
    {
        StringTreeCell<Type>* cell=this;

        bool last=false;
        for (size_t i=0; i<index.size() && this!=NULL_PTR; ++i)
        {
            if (cell->_tree[static_cast<char>(index[i])]==NULL_PTR)
                return false;
            if (i==index.size()-1)
                last=true;
            cell=cell->_tree[static_cast<char>(index[i])];
        }
        if (last)
        {
            size_t id=cell->id;
            for (size_t i=0; i<256; ++i)
                if (cell->_tree[i]!=NULL_PTR)
                    id-=cell->_tree[i]->id;
            return id==1;
        }
        return false;
    }
    void insert(std:string index,Type dat)
    {
        if (!find(index))
        {
            StringTreeCell<Type>*cell=this;
            cell->id++;
            cell->for (size_t i=0; i<index.size(); ++i)
            {
                if (cell->_tree[index[i]]==NULL_PTR)
                    cell->_tree[index[i]]=new StringTreeCell<Type>();
                cell->_tree[index[i]]->id++;
                cell=cell->_tree[index[i]];
            }
            cell->data=dat;
        }
    }
    void erase(std::string index)
    {
        if (find(index))
        {
            StringTreeCell<Type>*cell=this;
            cell->id--;
            for (size_t i=0; i<index.size(); ++i)
            {
                if (cell->_tree[index[i]]->id==1)
                {
                    delete cell->_tree[index[i]];
                    cell->_tree[index[i]]=NULL_PTR;
                    break;
                }
                cell=cell->_tree[index[i]];
                cell->id--;
            }
        }
    }




    Type & operator [] (std::string index)
    {
        if (!find(index))
            insert(index,T());
        StringTreeCell<Type>*cell=this;
        for (size_t i=0; i<index.size(); ++i)
        {
            cell=cell->_tree[static_cast<char>(index[i])];
        }
        return cell->data;
    }

    StringTreeCell()
    {
        id=0;
        _tree=new StringTreeCell<Type>*[256];
        for (size_t i=0; i<256; ++i)
            _tree[i]=NULL_PTR;
    }
    StringTreeCell(const StringTreeCell<Type> & target)
    {
        id=target.id;
        data=target.data;
        _tree=new StringTreeCell<Type>*[256];
        for (size_t i=0; i<256; ++i)
            if (target._tree[i]!=NULL_PTR)
                _tree[i]=new StringTreeCell<Type>(*target._tree[i]);
            else
                _tree[i]=NULL_PTR
    }
    ~StringTreeCell()
    {
        for (size_t i=0; i<256; ++i)
            if (_tree[i]!=NULL_PTR)
                delete _tree[i];
        delete[] _tree;
    }
};



#endif // STRINGTREE_H_INCLUDED
