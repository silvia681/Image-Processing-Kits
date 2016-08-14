#ifndef XYHISTOGRAM
#define XYHISTOGRAM

class Histogram{
public:
    void setHistvalue(unsigned int index, int value);
    void setBarsize(unsigned int width, unsigned int height);

    inline double getBin(){
        return this->bin;
    }

    inline double getUnitHeight(){
        return this->unitHeight;
    }

    inline int getHistvalue(unsigned int index){
        return this->histvalue[ index ];
    }

    inline void setBin(double bin){
        this->bin = bin;
    }

    inline void setUnitHeight(double height){
        this->unitHeight = height;
    }

private:
    int histvalue[256];
    double bin,unitHeight;
};

#endif
