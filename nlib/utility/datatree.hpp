#ifndef DATATREE_HPP_INCLUDED
#define DATATREE_HPP_INCLUDED

#include<cstdlib>
#include<vector>

#ifndef NULL_PTR
#if __cplusplus < 201103L
#define NULL_PTR __null
#else
#define NULL_PTR nullptr
#endif // __cplusplus
#endif // NULL_PTR

template<unsigned int Min=0,unsigned int Max=256>class SdatabaseCell
{
    SdatabaseCell<Min,Max>**cells;
    unsigned int _shared_;
public:
    SdatabaseCell<Min,Max>*previous;
    const unsigned int & shared;
    bool add(std::string word);
    bool remove(std::string word);
    bool search(std::string word);
    std::vector<std::string>getWords();
    void clear();
    bool operator [] (std::string index)
    {
        return search(index);
    }
    SdatabaseCell():shared(_shared_)
    {
        _shared_=0;
        previous=NULL_PTR;
        cells=new SdatabaseCell<Min,Max>*[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            cells[i]=NULL_PTR;
    }
    SdatabaseCell(SdatabaseCell<Min,Max> * prev):shared(_shared_)
    {
        _shared_=0;
        previous=prev;
        cells=new SdatabaseCell<Min,Max>*[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            cells[i]=NULL_PTR;
    }
    SdatabaseCell(SdatabaseCell<Min,Max> * prev,SdatabaseCell<Min,Max>**chain,unsigned int isShared=0):shared(_shared_)
    {
        previous=prev;
        _shared_=isShared;
        cells=new SdatabaseCell<Min,Max>*[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            if (chain[i]!=NULL_PTR)
            {
                cells[i]=new SdatabaseCell<Min,Max>(this,chain[i],chain[i]->_shared_);
            }
            else
            {
                cells[i]=NULL_PTR;
            }
    }
    SdatabaseCell(const SdatabaseCell<Min,Max> & target):shared(_shared_)
    {
        previous=target.previous;
        cells=new SdatabaseCell<Min,Max>[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            if (target.cells[i]!=NULL_PTR)
            {
                cells[i]=new SdatabaseCell<Max,Min>(this,target.cells[i],target.cells[i]->_shared_);
            }
            else
            {
                cells[i]=NULL_PTR;
            }
        _shared_=target._shared_;
    }
    ~SdatabaseCell()
    {
        for (unsigned int i=0; i<Max-Min; i++)
            if (cells[i]!=NULL_PTR) delete cells[i];
        delete [] cells;
    }
};

template<unsigned int Min,unsigned int Max>bool SdatabaseCell<Min,Max>::add(std::string word)
{
    SdatabaseCell<Min,Max>*next=this;
    if (!search(word))
    {
        for (unsigned int i=0; i<word.size(); i++)
            if (next->cells[word[i]-Min]==NULL_PTR)
            {
                next->cells[word[i]-Min]=new SdatabaseCell<Min,Max>(next);
                next=next->cells[word[i]-Min];
                next->_shared_=1;
            }
            else
            {
                next=next->cells[word[i]-Min];
                next->_shared_++;
            }
        return true;
    }
    return false;
}

template<unsigned int Min,unsigned int Max>bool SdatabaseCell<Min,Max>::remove(std::string word)
{
    if (search(word))
    {
        SdatabaseCell<Min,Max>*next=this;
        for (unsigned int i=0; i<word.size(); ++i)
        {
            next->cells[word[i]-Min]->_shared_--;
            if (next->cells[word[i]-Min]->_shared_==0)
            {
                delete next->cells[word[i]-Min];
                next->cells[word[i]-Min]=NULL_PTR;
                break;
            }
            next=next->cells[word[i]-Min];
        }
        return true;
    }
    return false;
}

template<unsigned int Min,unsigned int Max>bool SdatabaseCell<Min,Max>::search(std::string word)
{
    SdatabaseCell<Min,Max>*next=this;
    for (unsigned int i=0; i<word.size(); i++)
    {
        if (next->cells[word[i]-Min]!=NULL_PTR)
            next=next->cells[word[i]-Min];
        else
            return false;
    }
    for (unsigned int i=0; i<Max-Min; i++)
        if (next->cells[i]!=NULL_PTR and next->cells[i]->_shared_==next->_shared_) return false;
    if (next->_shared_>1)
    {
        unsigned int count=0;
        for (unsigned int i=0; i<Max-Min; i++)
            if (next->cells[i]!=NULL_PTR)
                count+=next->cells[i]->_shared_;
        return next->_shared_-count==1;
    }
    else
        for (unsigned int i=0; i>Max-Min; ++i)
            if (next->cells[i]==NULL_PTR)
                return false;
    return true;
}

template<unsigned int Min,unsigned int Max>std::vector<std::string> SdatabaseCell<Min,Max>::getWords()
{
    std::vector<std::string>words;
    SdatabaseCell<Min,Max>*next=this;
    for (unsigned int i=0; i<Max-Min; ++i)
        if (next->cells[i]!=NULL_PTR)
        {
            unsigned int count=0,normal=0;
            for (unsigned int j=0; j<Max-Min; ++j)
                if (next->cells[i]->cells[j]!=NULL_PTR)
                {
                    count+=next->cells[i]->cells[j]->_shared_;
                    normal++;
                }
            if (next->cells[i]->_shared_>count or !normal)
            {
                words.push_back(std::string());
                SdatabaseCell<Min,Max>*holder=next->cells[i];
                while (holder->previous)
                {
                    for (unsigned int index=0; index<Max-Min; ++index)
                        if (holder->previous->cells[index]==holder)
                        {
                            words[words.size()-1]=std::string()+char(index+Min)+words[words.size()-1];
                            break;
                        }
                    holder=holder->previous;
                }
            }
            std::vector<std::string>_words=next->cells[i]->getWords();
            for (unsigned int j=0; j<_words.size(); ++j)
                words.push_back(_words[j]);
        }
    return words;
}

template<unsigned int Min,unsigned int Max>void SdatabaseCell<Min,Max>::clear()
{
    for (unsigned int i=0; i<Max-Min; i++)
        if (cells[i]!=NULL_PTR)
        {
            delete cells[i];
            cells[i]=NULL_PTR;
        }
}

template<typename Type,unsigned int Min=0,unsigned int Max=256>class DataTreeCell
{
    DataTreeCell<Type,Min,Max>**cells;
    unsigned int _shared_;
public:
    Type * data;
    DataTreeCell<Type,Min,Max>*previous;
    const unsigned int & shared;

    void add(std::string word,Type * Data);
    bool search(std::string word);
    Type * get(std::string word);
    std::vector<std::string>getWords();
    void clear();

    Type * operator [] (std::string index)
    {
        return search(index);
    }

    DataTreeCell():shared(_shared_)
    {
        _shared_=0;
        previous=NULL_PTR;
        data=NULL_PTR;
        cells=new DataTreeCell<Type,Min,Max>*[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            cells[i]=NULL_PTR;
    }
    DataTreeCell(DataTreeCell<Type,Min,Max> * prev):shared(_shared_)
    {
        _shared_=0;
        previous=prev;
        data=NULL_PTR;
        cells=new DataTreeCell<Type,Min,Max>*[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            cells[i]=NULL_PTR;
    }
    DataTreeCell(DataTreeCell<Type,Min,Max> * prev,DataTreeCell<Type,Min,Max>**chain,unsigned int isShared=false,Type * Data=NULL_PTR):shared(_shared_)
    {
        previous=prev;
        _shared_=isShared;
        data=Data;
        cells=new DataTreeCell<Type,Min,Max>*[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            if (chain[i]!=NULL_PTR)
            {
                cells[i]=new DataTreeCell<Type,Min,Max>(this,chain[i],chain[i]->_shared_);
            }
            else
            {
                cells[i]=NULL_PTR;
            }
    }
    DataTreeCell(const DataTreeCell<Type,Min,Max> & target):shared(_shared_)
    {
        previous=target.previous;
        cells=new DataTreeCell<Type,Min,Max>[Max-Min];
        for (unsigned int i=0; i<Max-Min; i++)
            if (target.cells[i]!=NULL_PTR)
            {
                cells[i]=new DataTreeCell<Type,Max,Min>(this,target.cells[i],target.cells[i]->_shared_);
            }
            else
            {
                cells[i]=NULL_PTR;
            }
        _shared_=target._shared_;
    }
    ~DataTreeCell()
    {
        for (unsigned int i=0; i<Max-Min; i++)
            if (cells[i]!=NULL_PTR) delete cells[i];
        delete [] cells;
    }
};

template<typename Type,unsigned int Min,unsigned int Max>void DataTreeCell<Type,Min,Max>::add(std::string word,Type * Data)
{
    DataTreeCell<Type,Min,Max>*next=this;
    for (unsigned int i=0; i<word.size(); i++)
        if (next->cells[word[i]-Min]==NULL_PTR)
        {
            next->cells[word[i]-Min]=new DataTreeCell<Type,Min,Max>;
            next=next->cells[word[i]-Min];
            next->_shared_=1;
        }
        else
        {
            next=next->cells[word[i]-Min];
            next->_shared_++;
        }
    if (word.size()>0)
        next->data=Data;
}

template<typename Type,unsigned int Min,unsigned int Max>bool DataTreeCell<Type,Min,Max>::search(std::string word)
{
    DataTreeCell<Type,Min,Max>*next=this;
    for (unsigned int i=0; i<word.size(); i++)
    {
        if (next->cells[word[i]-Min]!=NULL_PTR)
        {
            next=next->cells[word[i]-Min];
        }
        else
            return false;
    }
    for (unsigned int i=0; i<Max-Min; i++)
        if (next->cells[i]!=NULL_PTR and next->cells[i]->_shared_==next->_shared_) return false;
    if (next->_shared_>1)
    {
        unsigned int count=0;
        for (unsigned int i=0; i<Max-Min; i++)
            if (next->cells[i]!=NULL_PTR)
                count+=next->_shared_-next->cells[i]->_shared_;
        return next->_shared_-count==1;
    }
    return true;
}

template<typename Type,unsigned int Min,unsigned int Max>Type * DataTreeCell<Type,Min,Max>::get(std::string word)
{
    DataTreeCell<Type,Min,Max>*next=this;
    if (search(word))
        for (unsigned int i=0; i<word.size(); i++)
            next=next->cells[word[i]-Min];
    if (word.size()>0)
        return next->data;
    return NULL_PTR;
}

template<typename Type,unsigned int Min,unsigned int Max>void DataTreeCell<Type,Min,Max>::clear()
{
    for (unsigned int i=0; i<Max-Min; i++)
        if (cells[i]!=NULL_PTR)
        {
            delete cells[i];
            cells[i]=NULL_PTR;
        }
}

#endif // DATATREE_HPP_INCLUDED
