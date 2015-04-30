
#include "Application.h"

int main(int argc, char* argv[])
{
	cout << argv[1] << " " << argv[2] << endl;
	Application app(argv[2]);
	app.run(argv[1]);
	return 0;
}
