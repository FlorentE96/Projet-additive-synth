#ifndef MODMATRIX_HPP
#define MODMATRIX_HPP


class modMatrix
{
public:
//    template<typename T1, typename T2>
//    struct Link {
//        T1 * src;
//        T2 * dst;
//        Link(T1 * _src, T2 * _dst) {
//            src = _src;
//            dst = _dst;
//        }
//    };
    template<typename T1, typename T2>
    struct Link {
        T1 * src;
        T2 * dst;
        bool state;
    };
    enum Source { ADSR1=0, ADSR2, LFO1, LFO2, VEL, SRC_SIZE};
    enum Dest { oscFreq=0, oscAmp, filtFreq, filtQ, DST_SIZE};
    modMatrix();
    void connect(Source _src, Dest _dst);
    void disconnect(Source _src, Dest _dst);
    template<typename T1>
    float process(T1 * _dst);
    void reset();
private:
    //std::vector<Link> links;
    Link links[SRC_SIZE][DST_SIZE];
};

#endif // MODMATRIX_HPP
