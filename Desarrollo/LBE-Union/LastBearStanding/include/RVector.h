#ifndef RVECTOR_H
#define RVECTOR_H
#include <iostream>

template <class A>
class RVector{
    public:
        explicit RVector(){}
        ~RVector(){
            std::cout<<"HA BORRAR PACK DE "<<m_rs.size()<<std::endl;
            for(unsigned int i = 0 ; i<m_rs.size() ; i++){
                std::cout<<"entro HA BORRAR PACK DE "<<m_rs.size()<<" "<<i<<std::endl;
                if(m_rs.at(i))delete m_rs.at(i);
                std::cout<<"salgo HA BORRAR PACK DE "<<m_rs.size()<<" "<<i<<std::endl;
            }
            m_rs.clear();
            std::cout<<"limpio PACK DE "<<m_rs.size()<<std::endl;
            std::vector<A*>().swap(m_rs);
            std::cout<<"fin packeteado"<<m_rs.size()<<std::endl;
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
