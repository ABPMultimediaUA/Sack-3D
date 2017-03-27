#ifndef RVECTOR_H
#define RVECTOR_H
#include <iostream>

template <class A>
class RVector{
    public:
        explicit RVector(){}
        ~RVector(){
            for(unsigned int i = 0 ; i<m_rs.size() ; i++){
                if(m_rs.at(i))delete m_rs.at(i);
            }
            m_rs.clear();
            std::vector<A*>().swap(m_rs);
        }
        bool Add(A *a = NULL){
            if(a){
                m_rs.push_back(a);
                return true;
            }
            return false;
        }
        void Remove(int i){
        	if(m_rs.at(i))delete m_rs.at(i);
        	m_rs.erase(m_rs.begin()+i);
        }
        std::vector<A*> Get() const{
            return m_rs;
        }
        A* Get(int i){return m_rs.at(i);}
        int Size(){return m_rs.size();}
    private:
        RVector(const RVector &){};
        RVector &operator=(const RVector &){};
        std::vector<A*> m_rs;
};

#endif
