#include <SigChld.hpp>

namespace PWRD{

	void SigChld(int _sig UNUSED){

		int status = _sig;

		pid_t w;

		while((w = waitpid(-1, &status, WNOHANG)) > 0){

			if (WIFEXITED(status)) {

				status = WIFEXITED(status);


			}
			else if (WIFSIGNALED(status)) {

				status = WIFSIGNALED(status);


			}
			else if (WIFSTOPPED(status)) {

				status = WIFSTOPPED(status);


			}



		}//While

		//printf("====================================\n");


	} //SigChld

}//PWRD
