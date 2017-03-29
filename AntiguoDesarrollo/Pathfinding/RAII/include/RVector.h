#ifndef RVECTOR_H
#define RVECTOR_H

template <class A>
class RVector{
    public:
        RVector(const RVector &) = delete;
        RVector &operator=(const RVector &) = delete;
        explicit RVector(){}
        ~RVector(){
            for(int i = 0 ; i<m_rs.size() ; i++)
                if(m_rs.at(i))delete m_rs.at(i);
            m_rs.clear();
        }
        bool Add(A *a = nullptr){
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
