#ifndef MODMATRIX_HPP
#define MODMATRIX_HPP


class modMatrix
{
public:
    template<typename T1, typename T2>
    struct Link {
        T1 * src;
        T2 * dst;
        Link(T1 * _src, T2 * _dst) {
            src = _src;
            dst = _dst;
        }
    };
//    enum Source { ADSR1, ADSR2, LFO1, LFO2, VEL };
//    enum Dest { oscFreq, oscAmp, filtFreq, filtQ };
    modMatrix();
    template<typename T1, typename T2>
    void connect(T1 * _src, T2 * _dst);
    template<typename T1, typename T2>
    void disconnect(T1 * _src, T2 * _dst);
    template<typename T1>
    float process(T1 * _dst);
    void reset();
private:
    std::vector<Link> links;
};

#endif // MODMATRIX_HPP
