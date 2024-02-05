#if false
#endif

#include <iostream>

class Screen {
public:
	virtual void Init() {
		std::cout << "Base Screen Init" << std::endl;
	};
	virtual void Draw() {
		std::cout << "Base Screen Draw" << std::endl;
	};
	virtual void Update() {
		std::cout << "Base Screen Update" << std::endl;
	};
	virtual void Unload() {
		std::cout << "Base Screen Unload" << std::endl;
	};
	virtual int Finish() {
		std::cout << "Base Screen Finish" << std::endl;
		return 0;
	};
};