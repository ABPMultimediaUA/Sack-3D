#ifndef GAMERESOURCE_H
#define GAMERESOURCE_H

template <class A>
class GameResource{
    public:
        GameResource(const GameResource &) = delete;
	    GameResource &operator=(const GameResource &) = delete;
	    explicit GameResource(A *a = NULL):m_t(a){}
	    void Reset(A *a = NULL){
	        delete m_t;
	        m_t = a;
	    }
	    A *Get() const{
	        return m_t;
	    }
	    ~GameResource(){
	        if(m_t){
	        	delete m_t;
	        }
	    }
    private:
	    A *m_t;
};

#endif
