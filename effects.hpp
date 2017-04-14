#define MAX_DELAY 44100



class Echo{
private:
	
	uint16_t D;
	float G;
	float DryWet;
	void shiftSamples (int16_t delayed_sample[], int16_t input);
	
public:
	uint16_t getD();
	void setD(uint16_t _D);
	int16_t echoCompute (int16_t input);
	Echo(uint16_t _D, float _G, float _DryWet);	
	~Echo();
	
};
