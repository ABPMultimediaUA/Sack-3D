#ifndef RVECTOR_H
#define RVECTOR_H
#include <iostream>
template <class A>
class RVector{
    public:
        RVector(const RVector &) = delete; //no copiable
        RVector &operator=(const RVector &) = delete; //no copiable
        explicit RVector(){}
        ~RVector(){
            std::cout<<"Vector a borrar "<<m_rs.size()<<std::endl;
            for(int i = 0 ; i<m_rs.size() ; i++){
                if(m_rs.at(i)){delete m_rs.at(i);}
                }
            m_rs.clear();
            std::vector<A*>().swap(m_rs);
            //std::vector<A*>(m_rs).swap(m_rs);
            //m_rs.shrink_to_fit();
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
        std::vector<A*> m_rs;
};

#endif
