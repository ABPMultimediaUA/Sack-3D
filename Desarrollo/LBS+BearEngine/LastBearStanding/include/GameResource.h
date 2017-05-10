#ifndef GAMERESOURCE_H
#define GAMERESOURCE_H

template <class A>
class GameResource{
    public:
	    explicit GameResource(A *a = 0):m_t(a){}
	    void Reset(A *a = 0){
	        if(m_t){
	        	delete m_t;
	        }
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
    	GameResource(const GameResource &){}
    	GameResource &operator=(const GameResource &){}
	    A *m_t;
};

#endif

