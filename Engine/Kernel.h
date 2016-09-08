
#ifndef KERNEL_H
#define KERNEL_H

class Kernel
{
	std::shared_ptr<GLFWwindow> context;
	GLFWwindow*dealloc;
	GLuint HEIGHT, WIDTH;
	void init();
	void update();

public:

	
	Kernel();
	void runApp();
	~Kernel();

	std::shared_ptr<GLFWwindow> Kernel::getContext()const;
}; 




#endif // !KERNEL_H


