#include "State.h"

int main(int argc, char* argv[])
{
	State state;

	while (state.isRunning())
	{
		state.loop();
	}
	return 0;
}